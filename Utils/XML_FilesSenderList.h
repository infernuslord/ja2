#ifndef _XML_FILESSENDERLIST_H
#define _XML_FILESSENDERLIST_H

#include "Types.h"

#define MAX_FILES_SENDER_VALUES_CHARS 128

typedef struct
{
	UINT16	uiIndex; 
	CHAR16	Name[MAX_FILES_SENDER_VALUES_CHARS];

} FILES_SENDER_VALUES;

extern FILES_SENDER_VALUES zFilesSenderList[500];


#endif
