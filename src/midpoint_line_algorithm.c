

/************************************************************************************
	Midpoint Line Drawing Algorithm implementation C file
	Floating Point, Continuous Coloring version
	Author:             Ashis Kumar Das
	ID:                 11301002
	Email:              akd.bracu@gmail.com
*************************************************************************************/


#include <math.h>
#include <GL\gl.h>
#include <GL\glu.h>

#define FLOAT_DIFF_VALUE .001
#define colorIt mygl_coordinateColor8



/************************************************************************************
*
*   Function Prototypes and Variable Definitions
*
*************************************************************************************/

void mygl_coordinateColor4(float x, float y, float *r, float *g, float *b);
void mygl_coordinateColor8(float x, float y, float *r, float *g, float *b);

void mygl_drawLine0(float x0, float y0, float x1, float y1);

void mygl_drawLine1(float x0, float y0, float x1, float y1);

void mygl_drawLine2(float x0, float y0, float x1, float y1);

void mygl_drawLine3(float x0, float y0, float x1, float y1);

void mygl_drawLine4(float x0, float y0, float x1, float y1);

void mygl_drawLine5(float x0, float y0, float x1, float y1);

void mygl_drawLine6(float x0, float y0, float x1, float y1);

void mygl_drawLine7(float x0, float y0, float x1, float y1);

void mygl_drawGenericLine(float x0, float y0, float x1, float y1);





/************************************************************************************
*
*   Implementation of Midpoint Line Algorithm (Floating Point + Continuous Coloring)
*
*************************************************************************************/


void mygl_drawGenericLine(float x0, float y0, float x1, float y1) {

	register float dx, dy;

	dx = x1 - x0;
	dy = y1 - y0;

	if (fabsf(dx) >= fabsf(dy)) {                   /* Must be in zone 0, 3, 4, 7 */

		if (dx >= 0 && dy >= 0)                     /* Zone 0 */
			mygl_drawLine0(x0, y0, x1, y1);
		if (dx < 0 && dy >= 0)                      /* Zone 3 */
			mygl_drawLine3(x0, y0, x1, y1);
		if (dx < 0 && dy < 0)                       /* Zone 4 aka reverse zone 0 */
//			mygl_drawLine4(x0, y0, x1, y1);
			mygl_drawLine0(x1, y1, x0, y0);
		if (dx >=0 && dy < 0)                       /* Zone 7 aka reverse zone 3 */
//			mygl_drawLine7(x0, y0, x1, y1);
			mygl_drawLine3(x1, y1, x0, y0);
	}
	else {                                          /* Must be in zone 1, 2, 5, 6 */

		if (dx >= 0 && dy >= 0)                     /* Zone 1 */
			mygl_drawLine1(x0, y0, x1, y1);
		if (dx < 0 && dy >= 0)                      /* Zone 2*/
			mygl_drawLine2(x0, y0, x1, y1);
		if (dx < 0 && dy < 0)                       /* Zone 5 aka reverse zone 1 */
//			mygl_drawLine5(x0, y0, x1, y1);
			mygl_drawLine1(x1, y1, x0, y0);
		if (dx >=0 && dy < 0)                       /* Zone 6 aka reverse zone 2 */
//			mygl_drawLine6(x0, y0, x1, y1);
			mygl_drawLine2(x1, y1, x0, y0);
	}

	return;
}


void mygl_drawLine0(float x0, float y0, float x1, float y1) {

	float dx, dy, de, dne;
	register float d, x, y;
	float r, g, b;                      			/*	For coloring vertices	*/

	dx = x1 - x0;
	dy = y1 - y0;
	d = 2 * dy - dx;
	de = 2 * dy;
	dne = 2 * (dy - dx);

	x = x0; y = y0;

	colorIt(x, y, &r, &g, &b);        				/* Select defined color based on xy */
	glColor3f(r, g, b);                             /* Set GL color to the selected one */

	glVertex2f(x, y);

	while (x < x1) {

		if (d <= 0) {
			d = d + de;
			x = x + FLOAT_DIFF_VALUE;
		}
		else {
			d = d + dne;
			x = x + FLOAT_DIFF_VALUE;
			y = y + FLOAT_DIFF_VALUE;
		}
		colorIt(x, y, &r, &g, &b);
		glColor3f(r, g, b);
		glVertex2f(x, y);
	}

	return;
}


void mygl_drawLine1(float x0, float y0, float x1, float y1) {

	float dx, dy, dn, dne;
	register float d, x, y;
	float r, g, b;

	dx = x1 - x0;
	dy = y1 - y0;
	d = dy - 2 * dx;
	dn = -2 * dx;
	dne = 2 * (dy - dx);

	x = x0; y = y0;

	colorIt(x, y, &r, &g, &b);        				/* Select defined color based on xy */
	glColor3f(r, g, b);                             /* Set GL color to the selected one */

	glVertex2f(x, y);

	while (y < y1) {

		if (d >= 0) {
			d = d + dn;
			y = y + FLOAT_DIFF_VALUE;
		}
		else {
			d = d + dne;
			x = x + FLOAT_DIFF_VALUE;
			y = y + FLOAT_DIFF_VALUE;
		}
		colorIt(x, y, &r, &g, &b);
		glColor3f(r, g, b);
		glVertex2f(x, y);
	}

	return;
}


void mygl_drawLine2(float x0, float y0, float x1, float y1) {

	float dx, dy, dn, dnw;
	register float d, x, y;
	float r, g, b;

	dx = x1 - x0;
	dy = y1 - y0;
	d = dy - 2 * dx;
	dn = -2 * dx;
	dnw = -2 * (dy + dx);

	x = x0; y = y0;

	colorIt(x, y, &r, &g, &b);        				/* Select defined color based on xy */
	glColor3f(r, g, b);                             /* Set GL color to the selected one */

	glVertex2f(x, y);

	while (y < y1) {

		if (d <= 0) {
			d = d + dn;
			y = y + FLOAT_DIFF_VALUE;
		}
		else {
			d = d + dnw;
			y = y + FLOAT_DIFF_VALUE;
			x = x - FLOAT_DIFF_VALUE;
		}
		colorIt(x, y, &r, &g, &b);
		glColor3f(r, g, b);
		glVertex2f(x, y);
	}

	return;
}


void mygl_drawLine3(float x0, float y0, float x1, float y1) {

	float dx, dy, dw, dnw;
	register float d, x, y;
	float r, g, b;

	dx = x1 - x0;
	dy = y1 - y0;
	d = -2 * dy + dx;
	dw = -2 * dy;
	dnw = -2 * (dy + dx);

	x = x0; y = y0;

	colorIt(x, y, &r, &g, &b);        				/* Select defined color based on xy */
	glColor3f(r, g, b);                             /* Set GL color to the selected one */

	glVertex2f(x, y);

	while (x > x1) {

		if (d >= 0) {
			d = d + dw;
			x = x - FLOAT_DIFF_VALUE;
		}
		else {
			d = d + dnw;
			x = x - FLOAT_DIFF_VALUE;
			y = y + FLOAT_DIFF_VALUE;
		}
		colorIt(x, y, &r, &g, &b);
		glColor3f(r, g, b);
		glVertex2f(x, y);
	}

	return;
}


void mygl_drawLine4(float x0, float y0, float x1, float y1) {

	float dx, dy, dw, dsw;
	register float d, x, y;
	float r, g, b;

	dx = x1 - x0;
	dy = y1 - y0;
	d = dx - 2 * dy;
	dw = -2 * dy;
	dsw = 2 * (dx - dy);

	x = x0; y = y0;

	colorIt(x, y, &r, &g, &b);        				/* Select defined color based on xy */
	glColor3f(r, g, b);                             /* Set GL color to the selected one */

	glVertex2f(x, y);

	while (x > x1) {

		if (d <= 0) {
			d = d + dw;
			x = x - FLOAT_DIFF_VALUE;
		}
		else {
			d = d + dsw;
			x = x - FLOAT_DIFF_VALUE;
			y = y - FLOAT_DIFF_VALUE;
		}
		colorIt(x, y, &r, &g, &b);
		glColor3f(r, g, b);
		glVertex2f(x, y);
	}

	return;
}


void mygl_drawLine5(float x0, float y0, float x1, float y1) {

	float dx, dy, ds, dsw;
	register float d, x, y;
	float r, g, b;

	dx = x1 - x0;
	dy = y1 - y0;
	d = 2 * dx - dy;
	ds = 2 * dx;
	dsw = 2 * (dx - dy);

	x = x0; y = y0;

	colorIt(x, y, &r, &g, &b);        				/* Select defined color based on xy */
	glColor3f(r, g, b);                             /* Set GL color to the selected one */

	glVertex2f(x, y);

	while (y > y1) {

		if (d >= 0) {
			d = d + ds;
			y = y - FLOAT_DIFF_VALUE;
		}
		else {
			d = d + dsw;
			y = y - FLOAT_DIFF_VALUE;
			x = x - FLOAT_DIFF_VALUE;
		}
		colorIt(x, y, &r, &g, &b);
		glColor3f(r, g, b);
		glVertex2f(x, y);
	}

	return;
}


void mygl_drawLine6(float x0, float y0, float x1, float y1) {

	float dx, dy, ds, dse;
	register float d, x, y;
	float r, g, b;

	dx = x1 - x0;
	dy = y1 - y0;
	d = dy + 2 * dx;
	ds = 2 * dx;
	dse = 2 * (dx + dy);

	x = x0; y = y0;

	colorIt(x, y, &r, &g, &b);        				/* Select defined color based on xy */
	glColor3f(r, g, b);                             /* Set GL color to the selected one */

	glVertex2f(x, y);

	while (y > y1) {

		if (d <= 0) {
			d = d + ds;
			y = y - FLOAT_DIFF_VALUE;
		}
		else {
			d = d + dse;
			y = y - FLOAT_DIFF_VALUE;
			x = x + FLOAT_DIFF_VALUE;
		}
		colorIt(x, y, &r, &g, &b);
		glColor3f(r, g, b);
		glVertex2f(x, y);
	}

	return;
}


void mygl_drawLine7(float x0, float y0, float x1, float y1) {

	float dx, dy, de, dse;
	register float d, x, y;
	float r, g, b;

	dx = x1 - x0;
	dy = y1 - y0;
	d = dx + 2 * dy;
	de = 2 * dy;
	dse = 2 * (dy + dx);

	x = x0; y = y0;

	colorIt(x, y, &r, &g, &b);        				/* Select defined color based on xy */
	glColor3f(r, g, b);                             /* Set GL color to the selected one */

	glVertex2f(x, y);

	while (x < x1) {

		if (d >= 0) {
			d = d + de;
			x = x + FLOAT_DIFF_VALUE;
		}
		else {
			d = d + dse;
			x = x + FLOAT_DIFF_VALUE;
			y = y - FLOAT_DIFF_VALUE;
		}
		colorIt(x, y, &r, &g, &b);
		glColor3f(r, g, b);
		glVertex2f(x, y);
	}

	return;
}


