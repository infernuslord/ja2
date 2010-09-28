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

	AlteringAttachmentStruct	curAlteringAttachment;
	AlterationStruct			curAlteration;
	UINT32			maxArraySize;
	UINT32			curIndex;
	UINT32			curAlterationIndex;
	UINT32			currentDepth;
	UINT32			maxReadDepth;
}
typedef alteringattachmentParseData;

static void XMLCALL
alteringattachmentStartElementHandle(void *userData, const XML_Char *name, const XML_Char **atts)
{
	alteringattachmentParseData * pData = (alteringattachmentParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) //are we reading this element?
	{
		if(strcmp(name, "ALTERINGATTACHMENTLIST") == 0 && pData->curElement == ELEMENT_NONE)
		{
			pData->curElement = ELEMENT_LIST;

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(strcmp(name, "ALTERINGATTACHMENT") == 0 && pData->curElement == ELEMENT_LIST)
		{
			pData->curElement = ELEMENT;

			pData->curAlterationIndex = 0;

			//DebugMsg(TOPIC_JA2, DBG_LEVEL_3,"alteringattachmentStartElementHandle: setting memory for curAlteringAttachment");
			pData->curAlteringAttachment.usAttachmentIndex = 0;
			
			//clear vector.
			if(!pData->curAlteringAttachment.Alterations.empty()){
				while(pData->curAlteringAttachment.Alterations.size() > 0){
					pData->curAlteringAttachment.Alterations.pop_back();
				}
			}

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if( pData->curElement == ELEMENT && strcmp(name, "usAttachmentIndex") == 0 )
		{
			pData->curElement = ELEMENT_PROPERTY;

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if( pData->curElement == ELEMENT && strcmp(name, "ALTERATION") == 0 )
		{
			pData->curElement = ELEMENT_SUBLIST;

			if(!pData->curAlteration.usItemInclude.empty()){
				while(pData->curAlteration.usItemInclude.size() > 0){
					pData->curAlteration.usItemInclude.pop_back();
				}
			}
			if(!pData->curAlteration.usItemExclude.empty()){
				while(pData->curAlteration.usItemExclude.size() > 0){
					pData->curAlteration.usItemExclude.pop_back();
				}
			}
			if(!pData->curAlteration.ubWeaponClass.empty()){
				while(pData->curAlteration.ubWeaponClass.size() > 0){
					pData->curAlteration.ubWeaponClass.pop_back();
				}
			}
			if(!pData->curAlteration.usAddsSlots.empty()){
				while(pData->curAlteration.usAddsSlots.size() > 0){
					pData->curAlteration.usAddsSlots.pop_back();
				}
			}
			if(!pData->curAlteration.usRemovesSlots.empty()){
				while(pData->curAlteration.usRemovesSlots.size() > 0){
					pData->curAlteration.usRemovesSlots.pop_back();
				}
			}

			pData->maxReadDepth++; //we are not skipping this element
		}		
		else if( pData->curElement == ELEMENT_SUBLIST &&
			(strcmp(name, "usItemInclude")  == 0 ||
			strcmp(name, "usItemExclude")  == 0 ||
			strcmp(name, "ubWeaponClass")  == 0 ||
			strcmp(name, "addsSlot")  == 0 ||
			strcmp(name, "removesSlot")  == 0 ))
		{
			pData->curElement = ELEMENT_SUBLIST_PROPERTY;

			pData->maxReadDepth++; //we are not skipping this element
		}


		pData->szCharData[0] = '\0';
	}

	pData->currentDepth++;

}

static void XMLCALL
alteringattachmentCharacterDataHandle(void *userData, const XML_Char *str, int len)
{
	alteringattachmentParseData * pData = (alteringattachmentParseData *)userData;

	if( (pData->currentDepth <= pData->maxReadDepth) &&
		(strlen(pData->szCharData) < MAX_CHAR_DATA_LENGTH)
	){
		strncat(pData->szCharData,str,__min((unsigned int)len,MAX_CHAR_DATA_LENGTH-strlen(pData->szCharData)));
	}
}


static void XMLCALL
alteringattachmentEndElementHandle(void *userData, const XML_Char *name)
{
	alteringattachmentParseData * pData = (alteringattachmentParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) //we're at the end of an element that we've been reading
	{
		if(strcmp(name, "ALTERINGATTACHMENTLIST") == 0)
		{
			pData->curElement = ELEMENT_NONE;
		}
		else if(strcmp(name, "ALTERINGATTACHMENT") == 0)
		{
			pData->curElement = ELEMENT_LIST;

			if(pData->curIndex < pData->maxArraySize)
			{
				AlteringAttachments[pData->curIndex].usAttachmentIndex = pData->curAlteringAttachment.usAttachmentIndex;
				AlteringAttachments[pData->curIndex].Alterations = pData->curAlteringAttachment.Alterations;
				pData->curIndex++;
			}
		}
		else if(strcmp(name, "usAttachmentIndex") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAlteringAttachment.usAttachmentIndex = (UINT16) atol(pData->szCharData);
		}
		else if(strcmp(name, "ALTERATION") == 0)
		{
			pData->curElement = ELEMENT;
			//This crashes for some reason.... I don't get why but here's a workaround.
			//pData->curAlteringAttachment.Alterations.push_back( pData->curAlteration );

			//Make it one bigger.
			pData->curAlteringAttachment.Alterations.resize(pData->curAlterationIndex + 1 );
			pData->curAlteringAttachment.Alterations[pData->curAlterationIndex].usItemInclude = pData->curAlteration.usItemInclude;
			pData->curAlteringAttachment.Alterations[pData->curAlterationIndex].usItemExclude = pData->curAlteration.usItemExclude;
			pData->curAlteringAttachment.Alterations[pData->curAlterationIndex].ubWeaponClass	= pData->curAlteration.ubWeaponClass;
			pData->curAlteringAttachment.Alterations[pData->curAlterationIndex].usAddsSlots = pData->curAlteration.usAddsSlots;
			pData->curAlteringAttachment.Alterations[pData->curAlterationIndex].usRemovesSlots = pData->curAlteration.usRemovesSlots;
			
			pData->curAlterationIndex++;
		}
		else if(strcmp(name, "usItemInclude") == 0)
		{
			pData->curElement = ELEMENT_SUBLIST;
			pData->curAlteration.usItemInclude.push_back( (UINT16) atol(pData->szCharData) );
		}
		else if(strcmp(name, "usItemExclude") == 0)
		{
			pData->curElement = ELEMENT_SUBLIST;
			pData->curAlteration.usItemExclude.push_back( (UINT16) atol(pData->szCharData) );
		}
		else if(strcmp(name, "ubWeaponClass") == 0)
		{
			pData->curElement = ELEMENT_SUBLIST;
			pData->curAlteration.ubWeaponClass.push_back( (UINT16) atol(pData->szCharData) );
		}
		else if(strcmp(name, "addsSlot") == 0)
		{
			pData->curElement = ELEMENT_SUBLIST;

			pData->curAlteration.usAddsSlots.push_back( (UINT16) atol(pData->szCharData) );

			//AssertMsg(pData->curAlteringAttachment.usAddsSlots.size() <= MAX_ATTACHMENTS, "Too many addsSlot on one item.");
		}
		else if(strcmp(name, "removesSlot") == 0)
		{
			pData->curElement = ELEMENT_SUBLIST;

			pData->curAlteration.usRemovesSlots.push_back( (UINT16) atol(pData->szCharData) );

			//AssertMsg(pData->curAlteringAttachment.usRemovesSlots.size() <= MAX_ATTACHMENTS, "Too many removesSlot on one item.");
		}

		pData->maxReadDepth--;
	}

	pData->currentDepth--;
}

BOOLEAN ReadInAlteringAttachmentsStats(STR fileName)
{
	HWFILE		hFile;
	UINT32		uiBytesRead;
	UINT32		uiFSize;
	CHAR8 *		lpcBuffer;
	XML_Parser	parser = XML_ParserCreate(NULL);

	alteringattachmentParseData pData;

	DebugMsg(TOPIC_JA2, DBG_LEVEL_3, "Loading AlteringAttachments.xml" );

	// Open itemslotassign file
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


	XML_SetElementHandler(parser, alteringattachmentStartElementHandle, alteringattachmentEndElementHandle);
	XML_SetCharacterDataHandler(parser, alteringattachmentCharacterDataHandle);


	// This should fix the crash in a Release Version with VS 2008
	//memset(&pData,0,sizeof(pData));
	pData.curElement = ELEMENT_NONE;
	pData.szCharData[0] = 0;
	pData.curAlterationIndex = 0;
	pData.currentDepth = 0;
	pData.maxReadDepth = 0;
 	pData.maxArraySize = MAXITEMS;
 	pData.curIndex = 0;

	XML_SetUserData(parser, &pData);


	if(!XML_Parse(parser, lpcBuffer, uiFSize, TRUE))
	{
		CHAR8 errorBuf[511];

		sprintf(errorBuf, "XML Parser Error in AlteringAttachments.xml: %s at line %d", XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser));
		LiveMessage(errorBuf);

		MemFree(lpcBuffer);
		return FALSE;
	}

	MemFree(lpcBuffer);

	XML_ParserFree(parser);

	return( TRUE );
}

BOOLEAN WriteAlteringAttachmentStats()
{
	HWFILE		hFile;

	//Debug code; make sure that what we got from the file is the same as what's there
	// Open a new file
	hFile = FileOpen( "TABLEDATA\\AlteringAttachments out.xml", FILE_ACCESS_WRITE | FILE_CREATE_ALWAYS, FALSE );
	if ( !hFile )
		return( FALSE );

	{
		UINT32 cnt;

		FilePrintf(hFile,"<ALTERINGATTACHMENTLIST>\r\n");
		for(cnt = 0;cnt < MAXATTACHMENTS;cnt++)
		{
			FilePrintf(hFile,"\t<ALTERINGATTACHMENT>\r\n");

			FilePrintf(hFile,"\t\t<usAttachmentIndex>%d</usAttachmentIndex>\r\n",				AlteringAttachments[cnt].usAttachmentIndex);
			for(UINT16 cnt2 = 0; cnt2 < AlteringAttachments[cnt].Alterations.size(); cnt2++){
				FilePrintf(hFile,"\t\t<ALTERATION>\r\n");
				for(UINT16 cnt3 = 0; cnt3 < AlteringAttachments[cnt].Alterations[cnt2].usItemInclude.size(); cnt3++)
				{
					FilePrintf(hFile,"\t\t\t<usItemInclude>%d</usItemInclude>\r\n",		AlteringAttachments[cnt].Alterations[cnt2].usItemInclude[cnt3]);
				}
				for(UINT16 cnt3 = 0; cnt3 < AlteringAttachments[cnt].Alterations[cnt2].usItemExclude.size(); cnt3++)
				{
					FilePrintf(hFile,"\t\t\t<usItemExclude>%d</usItemExclude>\r\n",		AlteringAttachments[cnt].Alterations[cnt2].usItemExclude[cnt3]);
				}
				for(UINT16 cnt3 = 0; cnt3 < AlteringAttachments[cnt].Alterations[cnt2].ubWeaponClass.size(); cnt3++)
				{
					FilePrintf(hFile,"\t\t\t<ubWeaponClass>%d</ubWeaponClass>\r\n",		AlteringAttachments[cnt].Alterations[cnt2].ubWeaponClass[cnt3]);
				}
				for(UINT16 cnt3 = 0; cnt3 < AlteringAttachments[cnt].Alterations[cnt2].usAddsSlots.size(); cnt3++)
				{
					FilePrintf(hFile,"\t\t\t<addsSlot>%d</addsSlot>\r\n",		AlteringAttachments[cnt].Alterations[cnt2].usAddsSlots[cnt3]);
				}
				for(UINT16 cnt3 = 0; cnt3 < AlteringAttachments[cnt].Alterations[cnt2].usRemovesSlots.size(); cnt3++)
				{
					FilePrintf(hFile,"\t\t\t<removesSlot>%d</removesSlot>\r\n",		AlteringAttachments[cnt].Alterations[cnt2].usRemovesSlots[cnt3]);
				}
				FilePrintf(hFile,"\t\t</ALTERATION>\r\n");
			}

			FilePrintf(hFile,"\t</ALTERINGATTACHMENT>\r\n");
		}
		FilePrintf(hFile,"</ALTERINGATTACHMENTLIST>\r\n");
	}
	FileClose( hFile );

	return( TRUE );
}
