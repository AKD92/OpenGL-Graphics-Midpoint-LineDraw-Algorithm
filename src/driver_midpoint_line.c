

/************************************************************************************
	Midpoint Line Drawing Algorithm driver C file (MAIN)
	Author:             Ashis Kumar Das
	ID:                 11301002
	Email:              akd.bracu@gmail.com
*************************************************************************************/



#include <time.h>
#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iup.h>                /* For GUI toolkit */
#include <iupgl.h>



/************************************************************************************
*
*   Function Prototypes and Variable Definitions
*
*************************************************************************************/

List pointList;

int main(void);

int util_readFromFile(const char *fileName, List *outList);

void util_generateRandomFloat(float lb, float ub, List *outList);

/*	GUI Toolkit related functions	*/

Ihandle * createMainWindow(void);

int repaint_cb(Ihandle *canvas);

int resize_cb(Ihandle *canvas, int newWidth, int newHeight);

int btnRandLine_cb(Ihandle *btn);

int exit_cb(Ihandle *btn);



/*	OpenGL related functions	*/

void mygl_drawGenericLine(float x0, float y0, float x1, float y1);






/************************************************************************************
*
*   Implementation of midpoint driver routines
*
*************************************************************************************/


Ihandle * createMainWindow(void) {

	const char *winTitle;
	Ihandle *bottomHbox, *mainVbox;
	Ihandle *lblTitle, *glCanvas, *btnRandomLine, *btnClose;
	Ihandle *dialog;

	winTitle = "Graphics Homework 03 (11301002)\nMidpoint LineDraw Algorithm (+Continuous Coloring)";
	lblTitle = IupLabel(winTitle);
	IupSetAttribute(lblTitle, "EXPAND", "HORIZONTAL");
	IupSetAttribute(lblTitle, "ALIGNMENT", "ALEFT:ACENTER");
	IupSetAttribute(lblTitle, "FONTSIZE", "12");

	glCanvas = IupGLCanvas(0);
	IupSetAttribute(glCanvas, "EXPAND", "YES");
	IupSetAttribute(glCanvas, "BORDER", "NO");
	IupSetAttribute(glCanvas, "CANFOCUS", "NO");
/*	IupSetCallback(glCanvas, "RESIZE_CB", (Icallback) resize_cb);*/
	IupSetCallback(glCanvas, "ACTION", (Icallback) repaint_cb);
	IupSetHandle("canvas", glCanvas);

	btnRandomLine = IupButton("Generate Random Lines", 0);
	IupSetAttribute(btnRandomLine, "RASTERSIZE", "180x33");
	IupSetCallback(btnRandomLine, "ACTION", (Icallback) btnRandLine_cb);
	
	btnClose = IupButton("Close", 0);
	IupSetAttribute(btnClose, "RASTERSIZE", "80x33");
	IupSetCallback(btnClose, "ACTION", (Icallback) exit_cb);

	bottomHbox = IupHbox(btnRandomLine, IupFill(), btnClose, 0);
	IupSetAttribute(bottomHbox, "EXPAND", "HORIZONTAL");
	IupSetAttribute(bottomHbox, "NMARGIN", "0x5");

	mainVbox = IupVbox(lblTitle, glCanvas, bottomHbox, 0);
	IupSetAttribute(mainVbox, "NMARGIN", "10x10");
	IupSetAttribute(mainVbox, "NGAP", "10");

	dialog = IupDialog(mainVbox);
	IupSetAttribute(dialog, "TITLE", "GL Lab");
	IupSetAttribute(dialog, "RASTERSIZE", "450x540");
	IupSetAttribute(dialog, "SHRINK", "YES");

	return dialog;
}


int resize_cb(Ihandle *canvas, int newWidth, int newHeight) {

	IupGLMakeCurrent(canvas);

	glViewport(0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) newWidth/5, 0.0, (GLdouble) newHeight/5);

	return IUP_DEFAULT;
}


int repaint_cb(Ihandle *canvas) {

	ListElem *elem;
	float *xy, *xy_2;

	IupGLMakeCurrent(canvas);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(1.0);

	elem = list_head(&pointList);
	glBegin(GL_POINTS);

		while (elem != 0) {
   			xy = (float*) list_data(elem);
			elem = list_next(elem);
			xy_2 = (float*) list_data(elem);
			mygl_drawGenericLine(*xy, *(xy + 1), *xy_2, *(xy_2 + 1));
//			mygl_drawGenericLine(*xy_2, *(xy_2 + 1), *xy, *(xy + 1));
			elem = list_next(elem);
		}

//		mygl_drawGenericLine(0.0, 0.0, 1.0,1.0);
//		mygl_drawGenericLine(-0.5, -0.5, 0.5, -0.5);
//		mygl_drawGenericLine(-0.5, -0.5, -0.5,0.5);

	glEnd();

	glFlush();

	return IUP_DEFAULT;
}


int btnRandLine_cb(Ihandle *btn) {
	
	Ihandle *canvas;
	
	canvas = IupGetHandle("canvas");
	util_generateRandomFloat(-1.0, 1.0, &pointList);
	repaint_cb(canvas);
	printf("%d random floats generated\n", list_size(&pointList));
	
	return IUP_DEFAULT;
}


int exit_cb(Ihandle *btn) {

	return IUP_CLOSE;
}


int main(void) {

	Ihandle *dlg;
	int res;

	srand((unsigned int) time(0));

	list_init(&pointList, 0);
	res = util_readFromFile("coordinates.txt", &pointList);
//	util_generateRandomFloat(48, -1.0, 1.0, &pointList);
	printf("res: %d, list size: %d\n", res, list_size(&pointList));
	
	if (res == -1) {
		printf("File read error\n");\
		getche();
		goto TERMINATE;
	}

	IupOpen(0, 0);
		IupGLCanvasOpen();

		dlg = createMainWindow();
		IupShowXY(dlg, IUP_CENTER, IUP_CENTER);

		IupMainLoop();
	IupClose();
	
	TERMINATE:
	list_destroy(&pointList);
	return 0;
}
