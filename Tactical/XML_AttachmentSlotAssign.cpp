#ifdef PRECOMPILEDHEADERS
	#include "Tactical All.h"
#else
	#include "sgp.h"
	#include "overhead.h"
	#include "weapons.h"
	#include "Debug Control.h"
	#include "expat.h"
	#include "gamesettings.h"
	#include "XML.h"
#endif

struct
{
	PARSE_STAGE	curElement;

	CHAR8		szCharData[MAX_CHAR_DATA_LENGTH+1];

	AttachmentSlotAssignStruct			curAttachmentSlotAssign;
	UINT32			maxArraySize;
	UINT32			curIndex;
	UINT32			currentDepth;
	UINT32			maxReadDepth;
}
typedef attachmentslotassignParseData;

static void XMLCALL
attachmentslotassignStartElementHandle(void *userData, const XML_Char *name, const XML_Char **atts)
{
	attachmentslotassignParseData * pData = (attachmentslotassignParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) //are we reading this element?
	{
		if(strcmp(name, "ATTACHMENTSLOTASSIGNLIST") == 0 && pData->curElement == ELEMENT_NONE)
		{
			pData->curElement = ELEMENT_LIST;

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(strcmp(name, "ATTACHMENTSLOTASSIGN") == 0 && pData->curElement == ELEMENT_LIST)
		{
			pData->curElement = ELEMENT;

			//DebugMsg(TOPIC_JA2, DBG_LEVEL_3,"AttachmentSlotAssignStartElementHandle: setting memory for curAttachmentSlotAssign");

			memset(&pData->curAttachmentSlotAssign.uiAttachmentIndex,0,sizeof(pData->curAttachmentSlotAssign).uiAttachmentIndex);
			memset(&pData->curAttachmentSlotAssign.usAPCost,0,sizeof(pData->curAttachmentSlotAssign).usAPCost);
			memset(&pData->curAttachmentSlotAssign.usAttachmentSlotIndexAssign,0,sizeof(pData->curAttachmentSlotAssign).usAttachmentSlotIndexAssign);
			if(!pData->curAttachmentSlotAssign.usRemovesSlots.empty()){
				for(UINT16 cnt = 0; cnt < pData->curAttachmentSlotAssign.usRemovesSlots.size(); cnt++){
					pData->curAttachmentSlotAssign.usRemovesSlots.pop_back();
				}
			}
			if(!pData->curAttachmentSlotAssign.usAddsSlots.empty()){
				for(UINT16 cnt = 0; cnt < pData->curAttachmentSlotAssign.usAddsSlots.size(); cnt++){
					pData->curAttachmentSlotAssign.usAddsSlots.pop_back();
				}
			}
			//pData->curAttachmentSlotAssign.usRemovesSlots.clear();
			//pData->curAttachmentSlotAssign.usAddsSlots.clear();
			pData->curAttachmentSlotAssign.usRemovesSlots.reserve(MAX_ATTACHMENTS);
			pData->curAttachmentSlotAssign.usAddsSlots.reserve(MAX_ATTACHMENTS);

			pData->maxReadDepth++; //we are not skipping this element
			pData->curIndex++;
		}
		else if(pData->curElement == ELEMENT &&
				(strcmp(name, "attachmentSlotIndexAssign") == 0 ||
				strcmp(name, "attachmentIndex") == 0 ||
				strcmp(name, "APCost") == 0 ||
				strcmp(name, "removesSlot") == 0 ||
				strcmp(name, "addsSlot") == 0 ))
		{
			pData->curElement = ELEMENT_PROPERTY;

			pData->maxReadDepth++; //we are not skipping this element
		}

		pData->szCharData[0] = '\0';
	}

	pData->currentDepth++;

}

static void XMLCALL
attachmentslotassignCharacterDataHandle(void *userData, const XML_Char *str, int len)
{
	attachmentslotassignParseData * pData = (attachmentslotassignParseData *)userData;

	if( (pData->currentDepth <= pData->maxReadDepth) &&
		(strlen(pData->szCharData) < MAX_CHAR_DATA_LENGTH)
	){
		strncat(pData->szCharData,str,__min((unsigned int)len,MAX_CHAR_DATA_LENGTH-strlen(pData->szCharData)));
	}
}


static void XMLCALL
attachmentslotassignEndElementHandle(void *userData, const XML_Char *name)
{
	attachmentslotassignParseData * pData = (attachmentslotassignParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) //we're at the end of an element that we've been reading
	{
		if(strcmp(name, "ATTACHMENTSLOTASSIGNLIST") == 0)
		{
			pData->curElement = ELEMENT_NONE;
		}
		else if(strcmp(name, "ATTACHMENTSLOTASSIGN") == 0)
		{
			pData->curElement = ELEMENT_LIST;

			if(pData->curIndex < pData->maxArraySize)
			{
				pData->curAttachmentSlotAssign.usRemovesSlots.reserve(pData->curAttachmentSlotAssign.usRemovesSlots.size());
				pData->curAttachmentSlotAssign.usAddsSlots.reserve(pData->curAttachmentSlotAssign.usAddsSlots.size());
				//DebugMsg(TOPIC_JA2, DBG_LEVEL_3,"AttachmentSlotAssignStartElementHandle: writing AttachmentSlotAssign to array");
				AttachmentSlotAssign[pData->curIndex].usAttachmentSlotIndexAssign = pData->curAttachmentSlotAssign.usAttachmentSlotIndexAssign; //write the AttachmentSlotAssign into the table
				AttachmentSlotAssign[pData->curIndex].uiAttachmentIndex = pData->curAttachmentSlotAssign.uiAttachmentIndex;
				AttachmentSlotAssign[pData->curIndex].usAPCost = pData->curAttachmentSlotAssign.usAPCost;
				AttachmentSlotAssign[pData->curIndex].usRemovesSlots = pData->curAttachmentSlotAssign.usRemovesSlots;
				AttachmentSlotAssign[pData->curIndex].usAddsSlots = pData->curAttachmentSlotAssign.usAddsSlots;
			}
		}
		else if(strcmp(name, "attachmentSlotIndexAssign") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlotAssign.usAttachmentSlotIndexAssign = (UINT16) atol(pData->szCharData);
		}
		else if(strcmp(name, "attachmentIndex") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlotAssign.uiAttachmentIndex = (UINT16) atol(pData->szCharData);
		}
		else if(strcmp(name, "APCost") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlotAssign.usAPCost = (UINT16) atol(pData->szCharData);
			pData->curAttachmentSlotAssign.usAPCost = (UINT16)DynamicAdjustAPConstants(pData->curAttachmentSlotAssign.usAPCost, pData->curAttachmentSlotAssign.usAPCost);
		}
		else if(strcmp(name, "removesSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlotAssign.usRemovesSlots.push_back((UINT16)atol(pData->szCharData));
		}
		else if(strcmp(name, "addsSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlotAssign.usAddsSlots.push_back((UINT16) atol(pData->szCharData));
		}

		pData->maxReadDepth--;
	}

	pData->currentDepth--;
}




BOOLEAN ReadInAttachmentSlotAssignStats(STR fileName)
{
	HWFILE		hFile;
	UINT32		uiBytesRead;
	UINT32		uiFSize;
	CHAR8 *		lpcBuffer;
	XML_Parser	parser = XML_ParserCreate(NULL);

	attachmentslotassignParseData pData;

	DebugMsg(TOPIC_JA2, DBG_LEVEL_3, "Loading AttachmentSlotAssign.xml" );

	// Open AttachmentSlotAssign file
	hFile = FileOpen( fileName, FILE_ACCESS_READ, FALSE );
	if ( !hFile )
		return( FALSE );

	uiFSize = FileGetSize(hFile);
	lpcBuffer = (CHAR8 *) MemAlloc(uiFSize+1);

	//Read in block
	if ( !FileRead( hFile, lpcBuffer, uiFSize, &uiBytesRead ) )
	{
		MemFree(lpcBuffer);
		return( FALSE );
	}

	lpcBuffer[uiFSize] = 0; //add a null terminator

	FileClose( hFile );


	XML_SetElementHandler(parser, attachmentslotassignStartElementHandle, attachmentslotassignEndElementHandle);
	XML_SetCharacterDataHandler(parser, attachmentslotassignCharacterDataHandle);


	memset(&pData,0,sizeof(pData));
	pData.maxArraySize = MAXATTACHMENTS;
	pData.curIndex = -1;

	XML_SetUserData(parser, &pData);


	if(!XML_Parse(parser, lpcBuffer, uiFSize, TRUE))
	{
		CHAR8 errorBuf[511];

		sprintf(errorBuf, "XML Parser Error in AttachmentSlotAssign.xml: %s at line %d", XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser));
		LiveMessage(errorBuf);

		MemFree(lpcBuffer);
		return FALSE;
	}

	MemFree(lpcBuffer);


	XML_ParserFree(parser);

	return( TRUE );
}
BOOLEAN WriteAttachmentSlotAssignStats()
{
	HWFILE		hFile;

	//Debug code; make sure that what we got from the file is the same as what's there
	// Open a new file
	hFile = FileOpen( "TABLEDATA\\AttachmentSlotAssign out.xml", FILE_ACCESS_WRITE | FILE_CREATE_ALWAYS, FALSE );
	if ( !hFile )
		return( FALSE );

	{
		UINT32 cnt;

		FilePrintf(hFile,"<ATTACHMENTSLOTASSIGNLIST>\r\n");
		for(cnt = 0;cnt < MAXATTACHMENTS;cnt++)
		{
			FilePrintf(hFile,"\t<ATTACHMENTSLOTASSIGN>\r\n");

			FilePrintf(hFile,"\t\t<attachmentSlotIndexAssign>%d</attachmentSlotIndexAssign>\r\n",	AttachmentSlotAssign[cnt].usAttachmentSlotIndexAssign);
			FilePrintf(hFile,"\t\t<attachmentIndex>%d</attachmentIndex>\r\n",						AttachmentSlotAssign[cnt].uiAttachmentIndex);
			FilePrintf(hFile,"\t\t<APCost>%d</APCost>\r\n",											AttachmentSlotAssign[cnt].usAPCost);
			for(UINT16 cnt2 = 0; cnt2 < AttachmentSlotAssign[cnt].usRemovesSlots.size(); cnt2++){
				FilePrintf(hFile,"\t\t<itemSlotAssignIndex>%d</itemSlotAssignIndex>\r\n",			AttachmentSlotAssign[cnt].usRemovesSlots[cnt2]);
			}
			for(UINT16 cnt2 = 0; cnt2 < AttachmentSlotAssign[cnt].usAddsSlots.size(); cnt2++){
				FilePrintf(hFile,"\t\t<itemSlotAssignIndex>%d</itemSlotAssignIndex>\r\n",			AttachmentSlotAssign[cnt].usAddsSlots[cnt2]);
			}

			FilePrintf(hFile,"\t</ATTACHMENTSLOTASSIGN>\r\n");
		}
		FilePrintf(hFile,"</ATTACHMENTSLOTASSIGNLIST>\r\n");
	}
	FileClose( hFile );

	return( TRUE );
}
