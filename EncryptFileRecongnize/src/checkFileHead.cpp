#include "../include/checkFileHead.h"

FileProperty gFileType[] = {
	{"word", 		{208, 207,  17, 224, 161, 177,  26, 225,   0,   0}},
	{"word", 		{ 80,  75,   3,   4,  20,   0,   6,   0,   8,   0}},

	{"jpg", 		{255, 216, 255, 224,   0,  16,  74,  70,  73,  70}},
	{"jpg",  		{255, 216, 255, 225,  20, 247,  69, 120, 105, 102}},
	{"jpg",                 {255, 216, 255, 225,  24,  70,  69, 120, 105, 102}},
	{"jpg",  		{255, 216, 255, 225,  25, 231,  69, 120, 105, 102}},
	
	{"png",                 {137,  80,  78,  71,  13,  10,  26,  10,   0,   0}},

	{"pdf",			{ 37,  80,  68,  70,  45,  49,  46,  49,  10,  37}},
	{"pdf",			{ 37,  80,  68,  70,  45,  49,  46,  50,  10,  37}},
	{"pdf",  		{ 37,  80,  68,  70,  45,  49,  46,  51,  13,  37}},
	{"pdf",                 { 37,  80,  68,  70,  45,  49,  46,  51,  10,  37}},
	{"pdf",			{ 37,  80,  68,  70,  45,  49,  46,  52,  10,  37}},
	{"pdf",                 { 37,  80,  68,  70,  45,  49,  46,  52,  13,  37}},
	{"pdf",                 { 37,  80,  68,  70,  45,  49,  46,  52,  32,  19}},	
	{"pdf",			{ 37,  80,  68,  70,  45,  49,  46,  53,  13,  10}},
	{"pdf",                 { 37,  80,  68,  70,  45,  49,  46,  53,  10,  37}},
        {"pdf",			{ 37,  80,  68,  70,  45,  49,  46,  54,  13,  37}},		
	{"pdf",  		{ 77, 222, 218, 217,  78, 114, 146,  27,  32,  61}},
	{"pdf",  		{ 77, 222, 218, 217,  78, 114, 146,  27, 137, 202}},
	{"pdf",  		{239, 187, 191, 239, 187, 191,  37,  80,  68,  70}},
	{"pdf",  		{122, 254, 151, 117, 190, 161,  73,  58,  75, 166}},
	
	{"exe",                 { 77,  90, 144,   0,   3,   0,   0,   0,   4,   0}},
	{"exe",                 { 77,  90, 160,   0, 181,   0,   0,   0,  32,   0}},
	{"exe",                 { 77,  90, 232,   0,   3,   0,   0,   0,  32,   0}},
	{"exe",                 { 77,  90,  89,   1,   3,   0,   0,   0,  32,   0}},
	{"exe",                 { 77,  90,   2,   0,  53,   0,  11,   0,   7,   0}},
	{"exe",                 { 77,  90, 113,   1,   1,   0,   0,   0,   4,   0}},
	{"exe",                 {255, 216, 255, 224,   0,  16,  74,  70,  73,  70}},
	{"exe",                 { 77,  90,  80,   0,   2,   0,   0,   0,   4,   0}},
	{"exe",                 { 77,  90, 215,   0,   3,   0,   0,   0,  32,   0}},
	{"exe",                 { 77,  90, 186,   0,   6,   0,   0,   0,  32,   0}},
	
	{"rar",  		{ 82,  97, 114,  33,  26,   7,   0, 207, 144, 115}},
	
	{"zip",  		{ 80,  75,   3,   4,  20,   0,   0,   0,   8,   0}},
	{"zipEncrypt",          { 80,  75,   3,   4,  20,   0,   1,   0,   8,   0}}
};



static bool match(unsigned char* pN1, FileProperty& fileType, int nLength)
{
	int i = 0;
	unsigned char*  p1  = pN1;
	for(i = 0; i < nLength; i++){
		if((int)p1[i] != fileType.property[i])
			break;
	}

	return i == nLength;
}

char* matchFileType(unsigned char* strFileHead, int nLength)
{
	for(int i = 0; i < sizeof(gFileType)/sizeof(FileProperty); i++){
		if(match(strFileHead, gFileType[i],nLength)){
			return gFileType[i].type;
		}
	}

	return "unkonw";
}

char* readFileHead(char *streamFile, int nBytes)
{
	FILE* fTobeRead = fopen(streamFile,"r");
	if(fTobeRead == NULL){
		printf("can't open the file\n");
		return "error";
	}
	
	unsigned char strTmp[gnMaxHead] = {'\0'};
	int nNum = fread(strTmp,sizeof(unsigned char),nBytes,fTobeRead);
	fclose(fTobeRead);
	if(nNum < nBytes){
		return "error";	
	}
	else{
		return matchFileType(strTmp,nNum);
	}
}
	





















