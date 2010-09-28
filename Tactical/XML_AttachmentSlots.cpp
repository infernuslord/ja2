#ifdef PRECOMPILEDHEADERS
	#include "Tactical All.h"
#else
	#include "sgp.h"
	#include "overhead.h"
	#include "weapons.h"
	#include "Debug Control.h"
	#include "expat.h"
	#include "XML.h"
#endif

UINT16 LAST_SLOT_INDEX = 0;

struct
{
	PARSE_STAGE	curElement;

	CHAR8		szCharData[MAX_CHAR_DATA_LENGTH+1];

	AttachmentSlotStruct	curAttachmentSlot;
	AttachmentSlotStruct *	curArray;
	AttachmentAssignStruct		curAttachmentAssign;

	UINT32			maxArraySize;

	UINT32			currentDepth;
	UINT32			maxReadDepth;
}
typedef attachmentslotParseData;

static void XMLCALL
attachmentslotStartElementHandle(void *userData, const XML_Char *name, const XML_Char **atts)
{
	attachmentslotParseData * pData = (attachmentslotParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) //are we reading this element?
	{
		if(strcmp(name, "ATTACHMENTSLOTLIST") == 0 && pData->curElement == ELEMENT_NONE)
		{
			pData->curElement = ELEMENT_LIST;

			//Clear curArray, but avoid memsetting the vector.
			for(UINT32 i = 0; i < pData->maxArraySize; ++i){
				memset(&(pData->curArray[i]),0,SIZEOF_ATTACHMENT_SLOT_STRUCT_POD);
			}

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(strcmp(name, "ATTACHMENTSLOT") == 0 && pData->curElement == ELEMENT_LIST)
		{
			pData->curElement = ELEMENT;

			memset(&pData->curAttachmentSlot,0,SIZEOF_ATTACHMENT_SLOT_STRUCT_POD);

			//clear the vector.
			if(!pData->curAttachmentSlot.AttachmentAssignVector.empty()){
				while(pData->curAttachmentSlot.AttachmentAssignVector.size() > 0){
					pData->curAttachmentSlot.AttachmentAssignVector.pop_back();
				}
			}

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(pData->curElement == ELEMENT &&
				(strcmp(name, "uiSlotIndex") == 0 ||
				//strcmp(name, "szSlotName") == 0 ||
				strcmp(name, "usDescPanelPosX") == 0 ||
				strcmp(name, "usDescPanelPosY") == 0 ||
				strcmp(name, "fLauncherSlot") == 0 ||
				strcmp(name, "fBigSlot") == 0 ||
				strcmp(name, "fDefaultSlot") == 0 ||
				strcmp(name, "fDefaultPistolSlot") == 0 ||
				strcmp(name, "fDefaultMachinePistolSlot") == 0 ||
				strcmp(name, "fDefaultSubMachineGunSlot") == 0 ||
				strcmp(name, "fDefaultRifleSlot") == 0 ||
				strcmp(name, "fDefaultSniperRifleSlot") == 0 ||
				strcmp(name, "fDefaultAssaultRifleSlot") == 0 ||
				strcmp(name, "fDefaultLightMachineGunSlot") == 0 ||
				strcmp(name, "fDefaultShotgunSlot") == 0 ||
				strcmp(name, "fDefaultRocketLauncherSlot") == 0 ||
				strcmp(name, "fDefaultGrenadeLauncherSlot") == 0 ||
				strcmp(name, "fDefaultMortarSlot") == 0 ||
				strcmp(name, "fDefaultHelmetSlot") == 0 ||
				strcmp(name, "fDefaultVestSlot") == 0 ||
				strcmp(name, "fDefaultLeggingsSlot") == 0 ))
		{
			pData->curElement = ELEMENT_PROPERTY;

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(strcmp(name, "ATTACHMENTASSIGN") == 0 && pData->curElement == ELEMENT)
		{
			pData->curElement = ELEMENT_SUBLIST;

			memset(&pData->curAttachmentAssign,0,sizeof(AttachmentAssignStruct));

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(pData->curElement == ELEMENT_SUBLIST &&
				(strcmp(name, "usAttachmentIndex") == 0 ||
				strcmp(name, "APCost") == 0 ))
		{
			pData->curElement = ELEMENT_SUBLIST_PROPERTY;

			pData->maxReadDepth++; //we are not skipping this element
		}
		pData->szCharData[0] = '\0';
	}

	pData->currentDepth++;

}

static void XMLCALL
attachmentslotCharacterDataHandle(void *userData, const XML_Char *str, int len)
{
	attachmentslotParseData * pData = (attachmentslotParseData *)userData;

	if( (pData->currentDepth <= pData->maxReadDepth) &&
		(strlen(pData->szCharData) < MAX_CHAR_DATA_LENGTH)
	){
		strncat(pData->szCharData,str,__min((unsigned int)len,MAX_CHAR_DATA_LENGTH-strlen(pData->szCharData)));
	}
}


static void XMLCALL
attachmentslotEndElementHandle(void *userData, const XML_Char *name)
{
	attachmentslotParseData * pData = (attachmentslotParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) //we're at the end of an element that we've been reading
	{
		if(strcmp(name, "ATTACHMENTSLOTLIST") == 0)
		{
			pData->curElement = ELEMENT_NONE;
		}
		else if(strcmp(name, "ATTACHMENTSLOT") == 0)
		{
			pData->curElement = ELEMENT_LIST;

			if(pData->curAttachmentSlot.uiSlotIndex < pData->maxArraySize)
			{
				pData->curArray[pData->curAttachmentSlot.uiSlotIndex] = pData->curAttachmentSlot; //write the attachmentinfo into the table
				//Save the highest known index up till now.
				if(LAST_SLOT_INDEX < pData->curAttachmentSlot.uiSlotIndex){
					LAST_SLOT_INDEX = (UINT16) pData->curAttachmentSlot.uiSlotIndex;
				}
			}
		}
		else if(strcmp(name, "uiSlotIndex") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.uiSlotIndex	= (UINT32) atol(pData->szCharData);
		}
		/* //This part doesn't work, I don't know why and can't be bothered to find out, because this text is not used anyway.
		else if(strcmp(name, "czSlotName") == 0)
		{
			pData->curElement = ELEMENT;
			MultiByteToWideChar( CP_UTF8, 0, pData->szCharData, -1, pData->curAttachmentSlot.szSlotName, sizeof(pData->curAttachmentSlot.szSlotName)/sizeof(pData->curAttachmentSlot.szSlotName[0]) );
			pData->curAttachmentSlot.szSlotName[sizeof(pData->curAttachmentSlot.szSlotName)/sizeof(pData->curAttachmentSlot.szSlotName[0]) - 1] = '\0';
		}*/
		else if(strcmp(name, "usDescPanelPosX") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.usDescPanelPosX	= (UINT16) atol(pData->szCharData);
		}
		else if(strcmp(name, "usDescPanelPosY") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.usDescPanelPosY	= (UINT16) atol(pData->szCharData);
		}
		else if(strcmp(name, "fLauncherSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fLauncherSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fBigSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fBigSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultPistolSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultPistolSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultMachinePistolSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultMachinePistolSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultSubMachineGunSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultSubMachineGunSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultRifleSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultRifleSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultSniperRifleSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultSniperRifleSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultAssaultRifleSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultAssaultRifleSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultLightMachineGunSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultLightMachineGunSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultShotgunSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultShotgunSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultRocketLauncherSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultRocketLauncherSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultGrenadeLauncherSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultGrenadeLauncherSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultMortarSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultMortarSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultHelmetSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultHelmetSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultVestSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultVestSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "fDefaultLeggingsSlot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.fDefaultLeggingsSlot = (BOOLEAN) atol(pData->szCharData);
		}
		else if(strcmp(name, "ATTACHMENTASSIGN") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curAttachmentSlot.AttachmentAssignVector.push_back(pData->curAttachmentAssign);
		}
		else if(strcmp(name, "usAttachmentIndex") == 0)
		{
			pData->curElement = ELEMENT_SUBLIST;
			pData->curAttachmentAssign.usAttachmentIndex = (UINT16) atol(pData->szCharData);
		}
		else if(strcmp(name, "APCost") == 0)
		{
			pData->curElement = ELEMENT_SUBLIST;
			pData->curAttachmentAssign.usAPCost = (UINT16) atol(pData->szCharData);
		}
		pData->maxReadDepth--;
	}

	pData->currentDepth--;
}


BOOLEAN ReadInAttachmentSlotsStats(STR fileName)
{
	HWFILE		hFile;
	UINT32		uiBytesRead;
	UINT32		uiFSize;
	CHAR8 *		lpcBuffer;
	XML_Parser	parser = XML_ParserCreate(NULL);

	attachmentslotParseData pData;

	DebugMsg(TOPIC_JA2, DBG_LEVEL_3, "Loading AttachmentSlots.xml" );

	// Open attachmentinfo file
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


	XML_SetElementHandler(parser, attachmentslotStartElementHandle, attachmentslotEndElementHandle);
	XML_SetCharacterDataHandler(parser, attachmentslotCharacterDataHandle);


	// This should fix the crash in a Release Version with VS 2008	
	//memset(&pData,0,sizeof(pData));
	pData.curElement = ELEMENT_NONE;
	pData.szCharData[0] = 0;
	pData.currentDepth = 0;
	pData.maxReadDepth = 0;	
 	pData.curArray = AttachmentSlots;
 	pData.maxArraySize = MAXITEMS;


	XML_SetUserData(parser, &pData);


	if(!XML_Parse(parser, lpcBuffer, uiFSize, TRUE))
	{
		CHAR8 errorBuf[511];

		sprintf(errorBuf, "XML Parser Error in AttachmentSlots.xml: %s at line %d", XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser));
		LiveMessage(errorBuf);

		MemFree(lpcBuffer);
		return FALSE;
	}

	MemFree(lpcBuffer);


	XML_ParserFree(parser);

	
	return( TRUE );
}

BOOLEAN WriteAttachmentSlotsStats()
{
	//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"writeattachmentslotstats");
	HWFILE		hFile;

	//Debug code; make sure that what we got from the file is the same as what's there
	// Open a new file
	hFile = FileOpen( "TABLEDATA\\AttachmentSlots out.xml", FILE_ACCESS_WRITE | FILE_CREATE_ALWAYS, FALSE );
	if ( !hFile )
		return( FALSE );

	{
		UINT32 cnt;

		FilePrintf(hFile,"<ATTACHMENTSLOTLIST>\r\n");
		for(cnt = 0;cnt < MAXITEMS;cnt++)
		{

			FilePrintf(hFile,"\t<ATTACHMENTSLOT>\r\n");

			FilePrintf(hFile,"\t\t<uiSlotIndex>%d</uiSlotIndex>\r\n",									AttachmentSlots[cnt].uiSlotIndex					);
			//FilePrintf(hFile,"\t\t<szSlotName>%d</szSlotName>\r\n",									AttachmentSlots[cnt].szSlotName						);
			FilePrintf(hFile,"\t\t<usDescPanelPosX>%d</usDescPanelPosX>\r\n",							AttachmentSlots[cnt].usDescPanelPosX				);
			FilePrintf(hFile,"\t\t<usDescPanelPosY>%d</usDescPanelPosY>\r\n",							AttachmentSlots[cnt].usDescPanelPosY				);
			FilePrintf(hFile,"\t\t<fLauncherSlot>%d</fLauncherSlot>\r\n",								AttachmentSlots[cnt].fLauncherSlot					);
			FilePrintf(hFile,"\t\t<fBigSlot>%d</fBigSlot>\r\n",											AttachmentSlots[cnt].fBigSlot						);
			FilePrintf(hFile,"\t\t<fDefaultSlot>%d</fDefaultSlot>\r\n",									AttachmentSlots[cnt].fDefaultSlot					);
			FilePrintf(hFile,"\t\t<fDefaultPistolSlot>%d</fDefaultPistolSlot>\r\n",						AttachmentSlots[cnt].fDefaultPistolSlot				);
			FilePrintf(hFile,"\t\t<fDefaultMachinePistolSlot>%d</fDefaultMachinePistolSlot>\r\n",		AttachmentSlots[cnt].fDefaultMachinePistolSlot		);
			FilePrintf(hFile,"\t\t<fDefaultSubMachineGunSlot>%d</fDefaultSubMachineGunSlot>\r\n",		AttachmentSlots[cnt].fDefaultSubMachineGunSlot		);
			FilePrintf(hFile,"\t\t<fDefaultRifleSlot>%d</fDefaultRifleSlot>\r\n",						AttachmentSlots[cnt].fDefaultRifleSlot				);
			FilePrintf(hFile,"\t\t<fDefaultSniperRifleSlot>%d</fDefaultSniperRifleSlot>\r\n",			AttachmentSlots[cnt].fDefaultSniperRifleSlot		);
			FilePrintf(hFile,"\t\t<fDefaultAssaultRifleSlot>%d</fDefaultAssaultRifleSlot>\r\n",			AttachmentSlots[cnt].fDefaultAssaultRifleSlot		);
			FilePrintf(hFile,"\t\t<fDefaultLightMachineGunSlot>%d</fDefaultLightMachineGunSlot>\r\n",	AttachmentSlots[cnt].fDefaultLightMachineGunSlot	);
			FilePrintf(hFile,"\t\t<fDefaultShotgunSlot>%d</fDefaultShotgunSlot>\r\n",					AttachmentSlots[cnt].fDefaultShotgunSlot			);
			FilePrintf(hFile,"\t\t<fDefaultRocketLauncherSlot>%d</fDefaultRocketLauncherSlot>\r\n",		AttachmentSlots[cnt].fDefaultRocketLauncherSlot		);
			FilePrintf(hFile,"\t\t<fDefaultGrenadeLauncherSlot>%d</fDefaultGrenadeLauncherSlot>\r\n",	AttachmentSlots[cnt].fDefaultGrenadeLauncherSlot	);
			FilePrintf(hFile,"\t\t<fDefaultMortarSlot>%d</fDefaultMortarSlot>\r\n",						AttachmentSlots[cnt].fDefaultMortarSlot				);
			FilePrintf(hFile,"\t\t<fDefaultHelmetSlot>%d</fDefaultHelmetSlot>\r\n",						AttachmentSlots[cnt].fDefaultHelmetSlot				);
			FilePrintf(hFile,"\t\t<fDefaultVestSlot>%d</fDefaultVestSlot>\r\n",							AttachmentSlots[cnt].fDefaultVestSlot				);
			FilePrintf(hFile,"\t\t<fDefaultLeggingsSlot>%d</fDefaultLeggingsSlot>\r\n",					AttachmentSlots[cnt].fDefaultLeggingsSlot			);
			for(UINT16 cnt2 = 0; cnt2 < AttachmentSlots[cnt].AttachmentAssignVector.size(); cnt2++){
				FilePrintf(hFile,"\t\t<ATTACHMENTASSIGN>\r\n");
				FilePrintf(hFile,"\t\t\t<usAttachmentIndex>%d</usAttachmentIndex>\r\n",					AttachmentSlots[cnt].AttachmentAssignVector[cnt2].usAttachmentIndex	);
				FilePrintf(hFile,"\t\t\t<usAttachmentIndex>%d</usAttachmentIndex>\r\n",					AttachmentSlots[cnt].AttachmentAssignVector[cnt2].usAPCost			);
				FilePrintf(hFile,"\t\t</ATTACHMENTASSIGN>\r\n");
			}

			FilePrintf(hFile,"\t</ATTACHMENTSLOT>\r\n");
		}
		FilePrintf(hFile,"</ATTACHMENTSLOTLIST>\r\n");
	}
	FileClose( hFile );

	return( TRUE );
}
