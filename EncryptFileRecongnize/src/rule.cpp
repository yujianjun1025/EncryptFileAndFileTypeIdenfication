#include "../include/rule.h"

bool IsEqualZero(float fValue)
{
	return (fValue >= -EPSILON  && fValue <= EPSILON ) ? true : false;
}

bool IsFileName(char* str)
{
	return (*str == '/') ? true : false;
}

float mean (int* pnRandomCount, int nCount, bool& bHaveOne)
{
   if(pnRandomCount == NULL){
 		printf("error mean()\n");
		return 0.0;
   }

   int nTotal = 0;
   for(int i = 0; i < nCount; i++){
	    if(pnRandomCount[i] <= 1){
			bHaveOne = true;
	     }
   	    nTotal += pnRandomCount[i];
   }

   return !nCount ? 0 : (nTotal*1.0)/nCount;
}

float variance(int* pnRandomCount, int nCount, float fMean)
{
	
	if(pnRandomCount == NULL){
		printf("error variance()\n");
		return 0.0f;
	}

	if(IsEqualZero(fMean)){
		return 0.0;
	}
	
	float fVariance = 0.0;
	for(int i = 0; i < nCount; i++)
	{
		fVariance += (pnRandomCount[i] - fMean)*(pnRandomCount[i] - fMean);
	}

	return !nCount ? 0 : fVariance/nCount;
}

float threeMatrix(int* pnRandomCount, int nCount, float fVariance, float fMean)
{
	if(pnRandomCount == NULL){
		printf("error threeMatrix()\n");
		return -100.0;
	}

	float fDive        = 0.0;
	float fThreeMatrix = 0.0;
	for(int i = 0; i < nCount; i++)
	{
		fThreeMatrix += pow(pnRandomCount[i] - fMean, 3);
	}

	fThreeMatrix	 /= (1.0*nCount);
        fDive 		  = sqrt(pow(fVariance, 3));

	return IsEqualZero(fDive) ? INTMAX : fThreeMatrix / fDive;

}

float fourMatrix(int* pnRandomCount, int nCount, float fVariance, float fMean)
{
	if(pnRandomCount == NULL){
		printf("error fourMatrix()\n");
		return 0.0;
	}
	
	float fDive       = 0.0;
	float fFourMatrix = 0.0;
	for(int i = 0 ; i < nCount; i++)
	{
		fFourMatrix += pow(pnRandomCount[i] - fMean, 4);
	}

	fFourMatrix      /= nCount;
	fDive             = pow(fVariance, 2);

	return IsEqualZero(fDive) ? 0.0 : fFourMatrix / fDive - 3;
}


char* statisticsAnFile(int nCount)
{
	bool  bHaveOnes    = false;
	float fMean        = mean(randoms,nCount, bHaveOnes);
	float fVariance    = variance(randoms,nCount,fMean);
	float fThreeMatrix = IsEqualZero(fVariance) ? 0.0 : threeMatrix(randoms, nCount, fVariance, fMean);	
	float fFourMatrix  = IsEqualZero(fVariance) ? 3.0 : fourMatrix(randoms,  nCount, fVariance, fMean); 

	if(bHaveOnes || fMean <= 4.5){
		return "NoEncrypt";	
	}
	else{
		return "Encrypt";
	}
}








