#ifndef __RULE
#define __RULE
#include "../include/global.h"

const  int   INTMAX       = 10;
const  float EPSILON      = 0.000001;

extern float mean (int* pnRandomCount, int nCount, bool& bHaveOne);
extern float variance(int* pnRandomCount, int nCount, float fMean);
extern float threeMatrix(int* pnRandomCount, int nCount, float fVariance, float fMean);
extern float fourMatrix(int* pnRandomCount, int nCount, float fVariance, float fMean);
extern char* statisticsAnFile(int n);

#endif
