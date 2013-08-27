#ifndef _GLOBAL
#define _GLOBAL  

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>     

#define MAX(x,y)             ((x) <  (y)  ? (y)  : (x))
#define MIN(x,y)             ((x) >  (y)  ? (y)  : (x))
#define isNonPositive(x)     ((x) <= 0.e0 ?   1  : 0)
#define isPositive(x)        ((x) >  0.e0 ?   1 : 0)
#define isNegative(x)        ((x) <  0.e0 ?   1 : 0)
#define isGreaterThanOne(x)  ((x) >  1.e0 ?   1 : 0)
#define isZero(x)            ((x) == 0.e0 ?   1 : 0)
#define isOne(x)             ((x) == 1.e0 ?   1 : 0)

typedef struct _testParameters {
	int		n;
	int		blockFrequencyBlockLength;
	int		nonOverlappingTemplateBlockLength;
	int		overlappingTemplateBlockLength;
	int		serialBlockLength;
	int		linearComplexitySequenceLength;
	int		approximateEntropyBlockLength;
	int		numOfBitStreams;
} TP;

typedef unsigned char   BYTE;
typedef unsigned char	BitSequence;
extern  TP	        tp;
extern  BitSequence	*epsilon;
extern  int             *randoms;
const   int             gFileHead      = 9;
const   int             STRMAXLEN      = 400;
const   float           ALPHA          = 0.01;	
const   int             MAXSEGMENT     = 8*1024;

#endif






























