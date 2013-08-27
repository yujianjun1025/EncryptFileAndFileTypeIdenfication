#include "../include/invokeNist.h"

static int     snCount    = 1;

int convertToBits(BYTE *x, int xBitLength, int bitsNeeded, int *num_0s, int *num_1s, int *bitsRead)
{
	int	i, j, count, bit;
	BYTE	mask;
	int	zeros, ones;

	count = 0;
	zeros = ones = 0;
	for ( i=0; i<(xBitLength+7)/8; i++ ) {
		mask = 0x80;
		for ( j=0; j<8; j++ ) {
			if ( *(x+i) & mask ) {
				bit = 1;
				(*num_1s)++;
				ones++;
			}
			else {
				bit = 0;
				(*num_0s)++;
				zeros++;
			}
			mask >>= 1;
			epsilon[*bitsRead] = bit;
			(*bitsRead)++;
			if ( *bitsRead == bitsNeeded )
				return 1;
			if ( ++count == xBitLength )
				return 0;
		}
	}
	
	return 0;
}

void readHexDigitsInBinaryFormat(FILE *fp, int nDataLen)
{
	int num_0s = 0;
	int num_1s = 0;                                                                       	
	int bitsRead = 0;                                                                     	
	int done = 0;
	BYTE buffer[4];

	if(!fp)
	{
		printf("utilitities line 338 error\n");
		return;
	}
	do {                                                                              	
		if ( fread(buffer, sizeof(unsigned char), 4, fp) != 4 ) {                     	
			printf("READ ERROR:  Insufficient data in file.\n");             
                        return;                                                                   	
		}                                                                             	
		done = convertToBits(buffer, 32, nDataLen, &num_0s, &num_1s, &bitsRead);          	
	} while ( !done );                                                                	
	
}


void test_suite(FILE* fResult, int nSegment)
{
	int	nCount = 0;
	double p_value = 0.0;
	
	if(!fResult){
		printf("fResult == NULL\n");
		exit(0);
	}
	
	p_value = Frequency(tp.n);
	(p_value >= ALPHA) ? ++nCount : nCount ;
	
	p_value = BlockFrequency(tp.blockFrequencyBlockLength, tp.n);
	(p_value >= ALPHA) ? ++nCount : nCount ;
	
	p_value = Runs(tp.n);	
	(p_value >= ALPHA) ? ++nCount : nCount ;
	
	p_value = LongestRunOfOnes(tp.n);
	(p_value >= ALPHA) ? ++nCount : nCount ;

	p_value = Rank(tp.n);
	(p_value >= ALPHA) ? ++nCount : nCount ;
		
	p_value = DiscreteFourierTransform(tp.n);
	(p_value >= ALPHA) ? ++nCount : 1 ;
     //   printf("%-10.6f",p_value);
		
	p_value = ApproximateEntropy(tp.approximateEntropyBlockLength, tp.n);
	(p_value >= ALPHA) ? ++nCount : 1 ;

	
	randoms[nSegment] = nCount;
	snCount %= 20;
	if(snCount)
		fprintf(fResult,"%2d",nCount);
	else
		fprintf(fResult,"%2d\n",nCount);
}

int invokeTestSuite(int nDataLen, char *streamFile, FILE* fResult)
{
	int  i = 0;
	int  nSegment = 0;
	unsigned long  nFileLength = 0;
	int  nRandom = 0;
	FILE* fp = NULL;
	if(!fResult || !streamFile){
		printf("fReslut == NULL\n");
		return 0.0;
	}	

	if ( (fp = fopen(streamFile, "rb")) == NULL ) {
		printf("ERROR IN FUNCTION invokeTestSuite:  file %s could not be opened.\n", streamFile);
		exit(-1);
	}
	fprintf(fResult,"%s\n",streamFile);
	                                                                                                      
	fseek(fp,0,SEEK_END);
	nFileLength = ftell(fp);
	fseek(fp,0,SEEK_SET);
	                                                                                                      
	memset(randoms,0,MAXSEGMENT*sizeof(int));
 	memset(epsilon,0,(tp.n + 1)*sizeof(BitSequence));	
	nSegment    = nFileLength / nDataLen; 
        nSegment    = (nSegment > MAXSEGMENT) ? MAXSEGMENT : nSegment;
	                                                                                                      
                                                                                                   
        snCount = 1;
	for(i = 0; i < nSegment; i++)
	{
		readHexDigitsInBinaryFormat(fp, nDataLen);
		test_suite(fResult, i);
		snCount++;
	}
	fprintf(fResult,"%s","\n");

	if(fp != NULL){
		fclose(fp);
	}
	
	return nSegment;		

}


