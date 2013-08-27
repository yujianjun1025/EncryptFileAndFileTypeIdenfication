#ifndef __INVOKENIST
#define __INVOKENIST
#include "../include/global.h"
#include "../include/suiteMethod.h"

extern int  convertToBits(BYTE *x, int xBitLength, int bitsNeeded, int *num_0s, int *num_1s, int *bitsRead);
extern void readHexDigitsInBinaryFormat(FILE *fp, int nDataLen);
extern void test_suite(FILE* fResult, int nRandoms);
extern int invokeTestSuite(int nDataLen, char *streamFile, FILE* fResult);

#endif
