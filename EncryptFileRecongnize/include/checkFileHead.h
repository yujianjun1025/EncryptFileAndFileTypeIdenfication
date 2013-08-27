#ifndef _CHECKFILEHEAD
#define _CHECKFILEHEAD
#include <stdio.h>
#include <stdlib.h>

const int gnMaxHead  		= 1000;
const int PROPERTY_LENGTH       = 30;
const int TYPENAME_LENGTH 	= 30;

typedef struct _fileProperty{
	char type[TYPENAME_LENGTH];
	unsigned int property[PROPERTY_LENGTH];
}FileProperty;

extern FileProperty gFileTye[];

extern char* readFileHead(char *streamFile, int nBytes);


#endif
