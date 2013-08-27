#ifndef __SUITEMETHOD
#define __SUITEMETHOD
#include "../include/global.h"
#include "../include/cephes.h"
#include "../include/matrix.h"

extern double   Frequency(int n);
extern double   BlockFrequency(int M, int n);
extern double   Runs(int n);
extern double	LongestRunOfOnes(int n);
extern double	Rank(int n);
extern double	DiscreteFourierTransform(int n);
extern double	ApproximateEntropy(int m, int n);

#endif
