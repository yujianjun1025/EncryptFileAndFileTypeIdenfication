#include "../include/checkFileHead.h"
#include "../include/invokeNist.h"
#include "../include/rule.h"

TP	      tp;
FILE*         fResult                       = NULL;
int*          randoms                       = NULL;
BitSequence*  epsilon   	            = NULL; 

int           gEncrypt                	    = 0;
int           gNoEncrypt                    = 0;
int           gKnownType                    = 0;
char          strTmp[STRMAXLEN]      	    = {'\0'};
char          strFileType[STRMAXLEN]        = {'\0'};
char	      strInputFilePath[STRMAXLEN]   = {'\0'};
char   	      strOutputFilePath[STRMAXLEN]  = {'\0'};



void Init(int argc, char* argv[])
{
	if ( argc != 2 ) {
		printf("Usage: %s <stream length>\n", argv[0]);
		printf("   <stream length> is the length of the individual bit stream(s) to be processed\n");
		exit(-1);
	}

	
	tp.blockFrequencyBlockLength          = 128;
	tp.nonOverlappingTemplateBlockLength  = 9;
	tp.overlappingTemplateBlockLength     = 9;
	tp.approximateEntropyBlockLength      = 10;
	tp.serialBlockLength                  = 16;
	tp.linearComplexitySequenceLength     = 500;
	tp.numOfBitStreams                    = 1;
	tp.n                                  = atoi(argv[1]);

	

        epsilon = new BitSequence [tp.n + 1];
	randoms = new int [MAXSEGMENT];
	if(epsilon == NULL || randoms == NULL){                                                                               	
		printf("BITSTREAM DEFINITION:  Insufficient memory available.\n");          	
		exit(-1);                                                                   	
	}  
}

DIR* GetFolder()
{
	DIR* dir = NULL;
	memset(strInputFilePath,0,strlen(strInputFilePath));
	memset(strTmp,0,strlen(strTmp));
	while(!dir)
	{
		memset(strInputFilePath,0,strlen(strInputFilePath));
		printf("please input an regular filename in /home/yujj/Desktop/TestData/FileSet\n");		
		strcpy(strInputFilePath,"/home/yujj/Desktop/TestData/FileSet/");
		scanf("%s",strTmp);
		
		strcat(strInputFilePath,strTmp);
		dir = opendir(strInputFilePath);
	}

                                                                                                                                         
	memset(strOutputFilePath,0,strlen(strOutputFilePath));
	strcpy(strOutputFilePath,"/home/yujj/Desktop/TestData/FileRandomCount/");
	strcat(strOutputFilePath,strTmp);
	
        fResult = fopen(strOutputFilePath, "w+");
	if(!fResult){
		printf("can't open the toLoadResult file\n");
		exit(-1);
	}

	return dir;
}

void Deal(DIR* dir)
{
	struct  dirent* ptr                   = NULL;

	memset(strTmp,0,strlen(strTmp));
	memset(strFileType,0,sizeof(strFileType));
	while((ptr = readdir(dir)) != NULL)
	{
		if(ptr->d_name[0] == '.')
			continue;
		else{
			sprintf(strTmp,"%s/%s",strInputFilePath,ptr->d_name);
			strcpy(strFileType,readFileHead(strTmp,gFileHead));
			
			if(strcmp(strFileType, "unkonw") == 0){
				int nRandoms = invokeTestSuite(tp.n, strTmp, fResult);
				strcpy(strTmp, statisticsAnFile(nRandoms) );
                                if(strcmp(strTmp, "Encrypt") == 0){
					gEncrypt ++;				
				}
				else if(strcmp(strTmp, "NoEncrypt") == 0){
					gNoEncrypt++;
				}
			}
			else if(strcmp(strFileType, "error") == 0){
				printf("the file is illegal\n");
			}
			else{
                                printf("the fileType is %s\n",strFileType);
				gKnownType++;			
			}
				
			memset(strTmp,0,sizeof(strTmp));
			memset(strFileType,0,sizeof(strFileType));
		}
	}
}

void Over()
{
	printf("Encrypt NUMs:   %5d\n",gEncrypt);
	printf("NoEncrypt NUMs: %5d\n",gNoEncrypt);
	printf("KnownType NUMs: %5d\n",gKnownType);

	if(fResult != NULL){
		fclose(fResult);
	}
	
    	delete [] epsilon;
	delete [] randoms;

}

int  main(int argc, char *argv[])
{
	DIR*    dir = NULL;
	
	Init(argc, argv);
	dir = GetFolder();
	Deal(dir);	
	Over();

	return 0;
}



	
