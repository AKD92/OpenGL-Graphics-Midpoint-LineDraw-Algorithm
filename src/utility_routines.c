

/************************************************************************************
	Utility routines to support line drawing
	Author:             Ashis Kumar Das
	ID:                 11301002
	Email:              akd.bracu@gmail.com
*************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <math.h>



/************************************************************************************
*
*   Function Prototypes and Variable Definitions
*
*************************************************************************************/

float random_f(float lb, float ub);

void mygl_coordinateColor4(float x, float y, float *r, float *g, float *b);

void mygl_coordinateColor8(float x, float y, float *r, float *g, float *b);

int util_readFromFile(const char *fileName, List *outList);

void util_generateRandomFloat(float lb, float ub, List *outList);




/************************************************************************************
*
*   Implementation of utility functions, which are called by other routines
*
*************************************************************************************/


float random_f(float lb, float ub) {

	float fr, diff;
	register float rnd_f;

	fr = (float) rand();                        /* Generation of original random value */
	rnd_f = fr / (float) (RAND_MAX);            /* Make this a float for factorization */
	diff = ub - lb;                             /* Calculate factor value */
	rnd_f = rnd_f * diff;						/* Factorizing our random value */
	rnd_f = rnd_f + lb;                         /* Rotating our random value */
	return rnd_f;
}



void mygl_coordinateColor4(float x, float y, float *r, float *g, float *b) {

	unsigned int cod1, cod2, cod3, cod4;

	cod1 = x < 0 && y >= 0 ? 1 : 0;
	cod2 = x < 0 && y < 0 ? 1 : 0;
	cod3 = x >= 0 && y < 0 ? 1 : 0;
	cod4 = x >= 0 && y >= 0 ? 1 : 0;

	if (cod1 == 1) {
			*r = 1.0; *g = 0.0; *b = 0.0;
	}
	if (cod2 == 1) {
		*r = 0.0; *g = 1.0; *b = 0.0;
	}
	if (cod3 == 1) {
		*r = 0.0; *g = 0.0; *b = 1.0;
	}
	if (cod4 == 1) {
		*r  = 1.0; *g = 1.0; *b = 0.0;
	}

	return;
}


void mygl_coordinateColor8(float x, float y, float *r, float *g, float *b) {

	if (y >= 0) {
		if (x > 0) {
			if (x >= y) {                           /* Zone 0 */
				*r = 1.0;
				*g = 1.0;
				*b = 1.0;
			}
			else {                                  /* Zone 1 */
				*r = 0.0;
				*g = 0.0;
				*b = 1.0;
			}
		}
		if (x < 0) {
			if (fabsf(x) > y) {                     /* Zone 3 */
				*r = 0.0;
				*g = 1.0;
				*b = 0.0;
			}
			else {                                  /* Zone 2 */
				*r = 0.0;
				*g = 1.0;
				*b = 1.0;
			}
		}
	}
	else {
		if (x > 0) {                                /* Zone 7 */
			if (x > fabsf(y)) {
				*r = 1.0;
				*g = 0.0;
				*b = 0.0;
			}
			else {                                  /* Zone 6 */
				*r = 1.0;
				*g = 0.0;
				*b = 1.0;
			}
		}
		else {
			if (fabsf(x) > fabsf(y)) {              /* Zone 4 */
				*r = 1.0;
				*g = 1.0;
				*b = 0.0;
			}
			else {                                  /* Zone 5 */
				*r = 0.5;
				*g = 0.5;
				*b = 0.5;
			}
		}
	}

	return;
}



int util_readFromFile(const char *fileName, List *outList) {

	FILE *pFile;
	char data[60];
	char *res;
	float *xy;
	char *format;

	format = "%f %f";
	pFile = fopen(fileName, "r");
	if (pFile == 0)
		return -1;

	list_destroy(outList);
	list_init(outList, free);

	LOOP_START:

		res = fgets(data, 59, pFile);
		
		if (res == 0) goto LOOP_END;
		if (*(data + 0) == '\\') goto LOOP_START;
		
		xy = (float*) malloc(2 * sizeof(float));
		sscanf(data, format, xy, xy + 1);
		
		list_ins_next(outList, list_tail(outList), (const void*) xy);

	goto LOOP_START;

	LOOP_END:
	fclose(pFile);

	return 0;
}


void util_generateRandomFloat(float lb, float ub, List *outList) {
	
	float *xy;                                          /* Pointer to generated XY */
	ListElem *elem;
	
	elem = list_head(outList);
	
	while (elem != 0) {
		xy = (float*) list_data(elem);
		*(xy + 0) = random_f(lb, ub);                   /* Generate random X value */
		*(xy + 1) = random_f(lb, ub);                   /* Generate random Y value */
		elem = list_next(elem);
	}
	
	return;
}
