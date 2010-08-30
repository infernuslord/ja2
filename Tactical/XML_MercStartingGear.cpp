#ifdef PRECOMPILEDHEADERS
	#include "Tactical All.h"
#else
	#include "sgp.h"
	#include "overhead.h"
	#include "weapons.h"
	#include "Debug Control.h"
	#include "expat.h"
	#include "XML.h"
	#include "Soldier Profile.h"
#endif

struct
{
	PARSE_STAGE	curElement;

	CHAR8				szCharData[MAX_CHAR_DATA_LENGTH+1];
	MERCPROFILEGEAR		curMercStartingGear;
	MERCPROFILEGEAR *	curArray;
	UINT32				maxArraySize;
	
	UINT32				currentDepth;
	UINT32				maxReadDepth;
}
typedef MercStartingGearParseData;

static void XMLCALL 
MercStartingGearStartElementHandle(void *userData, const XML_Char *name, const XML_Char **atts)
{
	MercStartingGearParseData * pData = (MercStartingGearParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) //are we reading this element?
	{
		if(strcmp(name, "MERCGEARLIST") == 0 && pData->curElement == ELEMENT_NONE)
		{
			pData->curElement = ELEMENT_LIST;

			//pData->curArray = &(MERCPROFILEGEAR());
			//memset(pData->curArray,0,sizeof(MERCPROFILEGEAR)*pData->maxArraySize);

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(strcmp(name, "MERCGEAR") == 0 && pData->curElement == ELEMENT_LIST)
		{
			pData->curElement = ELEMENT;

			pData->curMercStartingGear = MERCPROFILEGEAR();
			//memset(&pData->curMercStartingGear,0,sizeof(MERCPROFILEGEAR));

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(pData->curElement == ELEMENT &&
				(strcmp(name, "mIndex") == 0 ||
				strcmp(name, "mName") == 0 ||
				strcmp(name, "mHelmet") == 0 ||
				strcmp(name, "mHelmetStatus") == 0 ||
				strcmp(name, "mHelmetDrop") == 0 ||
				strcmp(name, "mVest") == 0 ||
				strcmp(name, "mVestStatus") == 0 ||
				strcmp(name, "mVestDrop") == 0 ||
				strcmp(name, "mLeg") == 0 ||
				strcmp(name, "mLegStatus") == 0 ||
				strcmp(name, "mLegDrop") == 0 ||
				strcmp(name, "mWeapon") == 0 ||
				strcmp(name, "mWeaponStatus") == 0 ||
				strcmp(name, "mWeaponDrop") == 0 ||
				strcmp(name, "mBig0") == 0 ||
				strcmp(name, "mBig0Quantity") == 0 ||
				strcmp(name, "mBig0Status") == 0 ||
				strcmp(name, "mBig0Drop") == 0 ||
				strcmp(name, "mBig1") == 0 ||
				strcmp(name, "mBig1Quantity") == 0 ||
				strcmp(name, "mBig1Status") == 0 ||
				strcmp(name, "mBig1Drop") == 0 ||
				strcmp(name, "mBig2") == 0 ||
				strcmp(name, "mBig2Quantity") == 0 ||
				strcmp(name, "mBig2Status") == 0 ||
				strcmp(name, "mBig2Drop") == 0 ||
				strcmp(name, "mBig3") == 0 ||
				strcmp(name, "mBig3Quantity") == 0 ||
				strcmp(name, "mBig3Status") == 0 ||
				strcmp(name, "mBig3Drop") == 0 ||
				strcmp(name, "mSmall0") == 0 ||
				strcmp(name, "mSmall0Quantity") == 0 ||
				strcmp(name, "mSmall0Status") == 0 ||
				strcmp(name, "mSmall1") == 0 ||
				strcmp(name, "mSmall1Quantity") == 0 ||
				strcmp(name, "mSmall1Status") == 0 ||
				strcmp(name, "mSmall2") == 0 ||
				strcmp(name, "mSmall2Quantity") == 0 ||
				strcmp(name, "mSmall2Status") == 0 ||
				strcmp(name, "mSmall3") == 0 ||
				strcmp(name, "mSmall3Quantity") == 0 ||
				strcmp(name, "mSmall3Status") == 0 ||
				strcmp(name, "mSmall4") == 0 ||
				strcmp(name, "mSmall4Quantity") == 0 ||
				strcmp(name, "mSmall4Status") == 0 ||
				strcmp(name, "mSmall5") == 0 ||
				strcmp(name, "mSmall5Quantity") == 0 ||
				strcmp(name, "mSmall5Status") == 0 ||
				strcmp(name, "mSmall6") == 0 ||
				strcmp(name, "mSmall6Quantity") == 0 ||
				strcmp(name, "mSmall6Status") == 0 ||
				strcmp(name, "mSmall7") == 0 ||
				strcmp(name, "mSmall7Quantity") == 0 ||
				strcmp(name, "mSmall7Status") == 0 ||
				strcmp(name, "lVest") == 0 ||
				strcmp(name, "lVestStatus") == 0 ||
				strcmp(name, "lLeftThigh") == 0 ||
				strcmp(name, "lLeftThighStatus") == 0 ||
				strcmp(name, "lRightThigh") == 0 ||
				strcmp(name, "lRightThighStatus") == 0 ||
				strcmp(name, "lCPack") == 0 ||
				strcmp(name, "lCPackStatus") == 0 ||
				strcmp(name, "lBPack") == 0 ||
				strcmp(name, "lBPackStatus") == 0 ))
		{
			pData->curElement = ELEMENT_PROPERTY;

			pData->maxReadDepth++; //we are not skipping this element
		}

		pData->szCharData[HELMETPOS] = '\0';
	}

	pData->currentDepth++;

}

static void XMLCALL
MercStartingGearCharacterDataHandle(void *userData, const XML_Char *str, int len)
{
	MercStartingGearParseData * pData = (MercStartingGearParseData *)userData;

	if( (pData->currentDepth <= pData->maxReadDepth) && 
		(strlen(pData->szCharData) < MAX_CHAR_DATA_LENGTH)
	  ){
		strncat(pData->szCharData,str,__min((unsigned int)len,MAX_CHAR_DATA_LENGTH-strlen(pData->szCharData)));
	  }
}


static void XMLCALL
MercStartingGearEndElementHandle(void *userData, const XML_Char *name)
{
	MercStartingGearParseData * pData = (MercStartingGearParseData *)userData;
	char temp;

	if(pData->currentDepth <= pData->maxReadDepth) //we're at the end of an element that we've been reading
	{
		if(strcmp(name, "MERCGEARLIST") == 0)
		{
			pData->curElement = ELEMENT_NONE;
		}
		else if(strcmp(name, "MERCGEAR") == 0)
		{
			pData->curElement = ELEMENT_LIST;

			if(pData->curMercStartingGear.mIndex < pData->maxArraySize)
			{
				pData->curArray[pData->curMercStartingGear.mIndex] = pData->curMercStartingGear; //write the armour into the table
			}
		}
		else if(strcmp(name, "mIndex") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.mIndex   = (UINT16) atol(pData->szCharData);
		}
		else if(strcmp(name, "mName") == 0)
		{
			pData->curElement = ELEMENT;
			if(MAX_CHAR_DATA_LENGTH >= strlen(pData->szCharData))
				strcpy(pData->curMercStartingGear.mName,pData->szCharData);
			else
			{
				strncpy(pData->curMercStartingGear.mName,pData->szCharData,MAX_CHAR_DATA_LENGTH);
				pData->curMercStartingGear.mName[MAX_CHAR_DATA_LENGTH] = '\0';
			}
			for(int i=0;i<min((int)strlen(pData->szCharData),MAX_CHAR_DATA_LENGTH);i++)
			{
				temp = pData->szCharData[i];
				pData->curMercStartingGear.mName[i] = temp;
				//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("itemEndElementHandle: itemname[%d] = %s, temp = %s",i,&pData->curItem.szItemName[i],&temp));
			}
		}
		else if(strcmp(name, "mHelmet") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[HELMETPOS]  = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mVest") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[VESTPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mLeg") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[LEGPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mWeapon") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[HANDPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig0") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[BIGPOCK1POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig1") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[BIGPOCK2POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig2") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[BIGPOCK3POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig3") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[BIGPOCK4POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall0") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[SMALLPOCK1POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall1") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[SMALLPOCK2POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall2") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[SMALLPOCK3POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall3") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[SMALLPOCK4POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall4") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[SMALLPOCK5POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall5") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[SMALLPOCK6POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall6") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[SMALLPOCK7POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall7") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.inv[SMALLPOCK8POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mHelmetStatus") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[HELMETPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mVestStatus") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[VESTPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mLegStatus") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[LEGPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mWeaponStatus") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[HANDPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig0Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[BIGPOCK1POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig1Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[BIGPOCK2POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig2Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[BIGPOCK3POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig3Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[BIGPOCK4POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall0Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[SMALLPOCK1POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall1Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[SMALLPOCK2POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall2Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[SMALLPOCK3POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall3Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[SMALLPOCK4POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall4Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[SMALLPOCK5POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall5Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[SMALLPOCK6POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall6Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[SMALLPOCK7POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall7Status") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iStatus[SMALLPOCK8POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mHelmetDrop") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iDrop[HELMETPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mVestDrop") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iDrop[VESTPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mLegDrop") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iDrop[LEGPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mWeaponDrop") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iDrop[HANDPOS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig0Drop") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iDrop[BIGPOCK1POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig1Drop") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iDrop[BIGPOCK2POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig2Drop") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iDrop[BIGPOCK3POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig3Drop") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iDrop[BIGPOCK4POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig0Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[BIGPOCK1POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig1Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[BIGPOCK2POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig2Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[BIGPOCK3POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mBig3Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[BIGPOCK4POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall0Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[SMALLPOCK1POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall1Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[SMALLPOCK2POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall2Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[SMALLPOCK3POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall3Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[SMALLPOCK4POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall4Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[SMALLPOCK5POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall5Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[SMALLPOCK6POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall6Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[SMALLPOCK7POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "mSmall7Quantity") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.iNumber[SMALLPOCK8POS] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "lVest") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.lbe[0] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "lLeftThigh") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.lbe[1] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "lRightThigh") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.lbe[2] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "lCPack") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.lbe[3] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "lBPack") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.lbe[4] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "lVestStatus") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.lStatus[0] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "lLeftThighStatus") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.lStatus[1] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "lRightThighStatus") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.lStatus[2] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "lCPackStatus") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.lStatus[3] = (int) atol(pData->szCharData);
		}
		else if(strcmp(name, "lBPackStatus") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curMercStartingGear.lStatus[4] = (int) atol(pData->szCharData);
		}

		pData->maxReadDepth--;
	}

	pData->currentDepth--;
}




BOOLEAN ReadInMercStartingGearStats(STR fileName)
{
	HWFILE		hFile;
	UINT32		uiBytesRead;
	UINT32		uiFSize;
	CHAR8 *		lpcBuffer;
	XML_Parser	parser = XML_ParserCreate(NULL);
	
	MercStartingGearParseData pData;

	DebugMsg(TOPIC_JA2, DBG_LEVEL_3, "Loading MercStartingGear.xml" );

	// Open gMercProfileGear file
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

	
	XML_SetElementHandler(parser, MercStartingGearStartElementHandle, MercStartingGearEndElementHandle);
	XML_SetCharacterDataHandler(parser, MercStartingGearCharacterDataHandle);

	
	memset(&pData,0,sizeof(pData));
	pData.curArray = gMercProfileGear;
	pData.maxArraySize = NUM_PROFILES; 
	
	XML_SetUserData(parser, &pData);

	for(int i=0; i<NUM_PROFILES; ++i)
	{
		gMercProfileGear[i].clearInventory();
	}
	if(!XML_Parse(parser, lpcBuffer, uiFSize, TRUE))
	{
		CHAR8 errorBuf[511];

		sprintf(errorBuf, "XML Parser Error in MercStartingGear.xml: %s at line %d", XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser));
		LiveMessage(errorBuf);

		MemFree(lpcBuffer);
		return FALSE;
	}

	MemFree(lpcBuffer);


	XML_ParserFree(parser);


	return( TRUE );
}
BOOLEAN WriteMercStartingGearStats()
{
	//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"writemercstartinggearstats");
	HWFILE		hFile;
	MERCPROFILESTRUCT * pProfile;

	//Debug code; make sure that what we got from the file is the same as what's there
	// Open a new file
	hFile = FileOpen( "TABLEDATA\\MercStartingGear out.xml", FILE_ACCESS_WRITE | FILE_CREATE_ALWAYS, FALSE );
	if ( !hFile )
		return( FALSE );
	
	{
		UINT32 cnt;
		CHAR16 str[100];

		FilePrintf(hFile,"<MERCGEARLIST>\r\n");
		for(cnt = 0;cnt < NUM_PROFILES;cnt++)
		{

			FilePrintf(hFile,"\t<MERCGEAR>\r\n");

			FilePrintf(hFile,"\t\t<mIndex>%d</mIndex>\r\n",								cnt );
//			FilePrintf(hFile,"\t\t<mName>%d</mName>\r\n",								gMercProfileGear[cnt].mName  );

			
			int j = -1;
			for (int i=0;i<80;i++)
			{
				j++;
				if ( i<(int)strlen(gMercProfileGear[cnt].mName))
				{
					str[i] = gMercProfileGear[cnt].mName [j];
				}
				else
				{
					str[i] ='\0';
				}
			}
			STR16 szRemainder = str;
			FilePrintf(hFile,"\t\t<mName>");
			while(szRemainder[HELMETPOS] != '\0')
			{
				UINT32 uiCharLoc = wcscspn(szRemainder, L"&<>\'\"\0");
				CHAR16 invChar = szRemainder[uiCharLoc];
				
				if(uiCharLoc)
				{
					szRemainder[uiCharLoc] = '\0';
					FilePrintf(hFile,"%S",szRemainder);
					szRemainder[uiCharLoc] = invChar;
				}

				szRemainder += uiCharLoc;

				switch(invChar)
				{
					case '&':
						FilePrintf(hFile,"&amp;");
						szRemainder++;
					break;

					case '<':
						FilePrintf(hFile,"&lt;");
						szRemainder++;
					break;

					case '>':
						FilePrintf(hFile,"&gt;");
						szRemainder++;
					break;

					case '\'':
						FilePrintf(hFile,"&apos;");
						szRemainder++;
					break;

					case '\"':
						FilePrintf(hFile,"&quot;");
						szRemainder++;
					break;
				}
			}
			
			FilePrintf(hFile,"</mName>\r\n");
			FilePrintf(hFile,"\t\t<mHelmet>%d</mHelmet>\r\n",					gMercProfiles[cnt].inv[HELMETPOS]  );
			FilePrintf(hFile,"\t\t<mHelmetStatus>%d</mHelmetStatus>\r\n",		gMercProfiles[cnt].bInvStatus[HELMETPOS]   );
			FilePrintf(hFile,"\t\t<mHelmetDrop>1</mHelmetDrop>\r\n");
			FilePrintf(hFile,"\t\t<mVest>%d</mVest>\r\n",						gMercProfiles[cnt].inv[VESTPOS]   );
			FilePrintf(hFile,"\t\t<mVestDrop>1</mVestDrop>\r\n");
			FilePrintf(hFile,"\t\t<mVestStatus>%d</mVestStatus>\r\n",			gMercProfiles[cnt].bInvStatus[VESTPOS]   );
			FilePrintf(hFile,"\t\t<mLeg>%d</mLeg>\r\n",							gMercProfiles[cnt].inv[LEGPOS]   );
			FilePrintf(hFile,"\t\t<mLegDrop>1</mLegDrop>\r\n");	
			FilePrintf(hFile,"\t\t<mLegStatus>%d</mLegStatus>\r\n",				gMercProfiles[cnt].bInvStatus[LEGPOS]   );
			FilePrintf(hFile,"\t\t<mWeapon>%d</mWeapon>\r\n",					gMercProfiles[cnt].inv[HANDPOS]   );
			FilePrintf(hFile,"\t\t<mWeaponDrop>1</mWeaponDrop>\r\n");
			FilePrintf(hFile,"\t\t<mWeaponStatus>%d</mWeaponStatus>\r\n",		gMercProfiles[cnt].bInvStatus[HANDPOS]   );
			FilePrintf(hFile,"\t\t<mBig0>%d</mBig0>\r\n",						gMercProfiles[cnt].inv[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig0Status>%d</mBig0Status>\r\n",			gMercProfiles[cnt].bInvStatus[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig0Quantity>%d</mBig0Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig0Drop>1</mBig0Drop>\r\n");
			FilePrintf(hFile,"\t\t<mBig1>%d</mBig1>\r\n",						gMercProfiles[cnt].inv[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig1Status>%d</mBig1Status>\r\n",			gMercProfiles[cnt].bInvStatus[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig1Quantity>%d</mBig1Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig1Drop>1</mBig1Drop>\r\n");
			FilePrintf(hFile,"\t\t<mBig2>%d</mBig2>\r\n",						gMercProfiles[cnt].inv[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig2Status>%d</mBig2Status>\r\n",			gMercProfiles[cnt].bInvStatus[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig2Quantity>%d</mBig2Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig2Drop>1</mBig2Drop>\r\n");
			FilePrintf(hFile,"\t\t<mBig3>%d</mBig3>\r\n",						gMercProfiles[cnt].inv[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mBig3Status>%d</mBig3Status>\r\n",			gMercProfiles[cnt].bInvStatus[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mBig3Quantity>%d</mBig3Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mBig3Drop>1</mBig3Drop>\r\n");
			FilePrintf(hFile,"\t\t<mSmall0>%d</mSmall0>\r\n",					gMercProfiles[cnt].inv[SMALLPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mSmall0Status>%d</mSmall0Status>\r\n",		gMercProfiles[cnt].bInvStatus[SMALLPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mSmall0Quantity>%d</mSmall0Quantity>\r\n",	gMercProfiles[cnt].bInvNumber[SMALLPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mSmall1>%d</mSmall1>\r\n",					gMercProfiles[cnt].inv[SMALLPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mSmall1Status>%d</mSmall1Status>\r\n",		gMercProfiles[cnt].bInvStatus[SMALLPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mSmall1Quantity>%d</mSmall1Quantity>\r\n",	gMercProfiles[cnt].bInvNumber[SMALLPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mSmall2>%d</mSmall2>\r\n",					gMercProfiles[cnt].inv[SMALLPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mSmall2Status>%d</mSmall2Status>\r\n",		gMercProfiles[cnt].bInvStatus[SMALLPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mSmall2Quantity>%d</mSmall2Quantity>\r\n",	gMercProfiles[cnt].bInvNumber[SMALLPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mSmall3>%d</mSmall3>\r\n",					gMercProfiles[cnt].inv[SMALLPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall3Status>%d</mSmall3Status>\r\n",		gMercProfiles[cnt].bInvStatus[SMALLPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall3Quantity>%d</mSmall3Quantity>\r\n",	gMercProfiles[cnt].bInvNumber[SMALLPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall4>%d</mSmall4>\r\n",					gMercProfiles[cnt].inv[SMALLPOCK5POS]   );
			FilePrintf(hFile,"\t\t<mSmall4Status>%d</mSmall4Status>\r\n",		gMercProfiles[cnt].bInvStatus[SMALLPOCK5POS]   );
			FilePrintf(hFile,"\t\t<mSmall4Quantity>%d</mSmall4Quantity>\r\n",	gMercProfiles[cnt].bInvNumber[SMALLPOCK5POS]   );
			FilePrintf(hFile,"\t\t<mSmall5>%d</mSmall5>\r\n",					gMercProfiles[cnt].inv[SMALLPOCK6POS]   );
			FilePrintf(hFile,"\t\t<mSmall5Status>%d</mSmall5Status>\r\n",		gMercProfiles[cnt].bInvStatus[SMALLPOCK6POS]   );
			FilePrintf(hFile,"\t\t<mSmall5Quantity>%d</mSmall5Quantity>\r\n",	gMercProfiles[cnt].bInvNumber[SMALLPOCK6POS]   );
			FilePrintf(hFile,"\t\t<mSmall6>%d</mSmall6>\r\n",					gMercProfiles[cnt].inv[SMALLPOCK7POS]   );
			FilePrintf(hFile,"\t\t<mSmall6Status>%d</mSmall6Status>\r\n",		gMercProfiles[cnt].bInvStatus[SMALLPOCK7POS]   );
			FilePrintf(hFile,"\t\t<mSmall6Quantity>%d</mSmall6Quantity>\r\n",	gMercProfiles[cnt].bInvNumber[SMALLPOCK7POS]   );
			FilePrintf(hFile,"\t\t<mSmall7>%d</mSmall7>\r\n",					gMercProfiles[cnt].inv[SMALLPOCK8POS]   );
			FilePrintf(hFile,"\t\t<mSmall7Status>%d</mSmall7Status>\r\n",		gMercProfiles[cnt].bInvStatus[SMALLPOCK8POS]   );
			FilePrintf(hFile,"\t\t<mSmall7Quantity>%d</mSmall7Quantity>\r\n",	gMercProfiles[cnt].bInvNumber[SMALLPOCK8POS]   );
			FilePrintf(hFile,"\t\t<lVest>0</lVest>\r\n");
			FilePrintf(hFile,"\t\t<lVestStatus>0</lVestStatus>\r\n");
			FilePrintf(hFile,"\t\t<lLeftThigh>0</lLeftThigh>\r\n");
			FilePrintf(hFile,"\t\t<lLeftThighStatus>0</lLeftThighStatus>\r\n");
			FilePrintf(hFile,"\t\t<lRightThigh>0</lRightThigh>\r\n");
			FilePrintf(hFile,"\t\t<lRightThighStatus>0</lRightThighStatus>\r\n");
			FilePrintf(hFile,"\t\t<lCPack>0</lCPack>\r\n");
			FilePrintf(hFile,"\t\t<lCPackStatus>0</lCPackStatus>\r\n");
			FilePrintf(hFile,"\t\t<lBPack>0</lBPack>\r\n");
			FilePrintf(hFile,"\t\t<lBPackStatus>0</lBPackStatus>\r\n");
			
		/*	FilePrintf(hFile,"</mName>\r\n");
			FilePrintf(hFile,"\t\t<mHelmet>%d</mHelmet>\r\n",						gMercProfiles[cnt].inv[HELMETPOS]  );
			FilePrintf(hFile,"\t\t<mVest>%d</mVest>\r\n",							gMercProfiles[cnt].inv[VESTPOS]   );
			FilePrintf(hFile,"\t\t<mLeg>%d</mLeg>\r\n",								gMercProfiles[cnt].inv[LEGPOS]   );
			FilePrintf(hFile,"\t\t<mWeapon>%d</mWeapon>\r\n",						gMercProfiles[cnt].inv[HANDPOS]   );
			FilePrintf(hFile,"\t\t<mHelmetStatus>%d</mHelmetStatus>\r\n",			gMercProfiles[cnt].bInvStatus[HELMETPOS]   );
			FilePrintf(hFile,"\t\t<mVestStatus>%d</mVestStatus>\r\n",				gMercProfiles[cnt].bInvStatus[VESTPOS]   );
			FilePrintf(hFile,"\t\t<mLegStatus>%d</mLegStatus>\r\n",					gMercProfiles[cnt].bInvStatus[LEGPOS]   );
			FilePrintf(hFile,"\t\t<mWeaponStatus>%d</mWeaponStatus>\r\n",			gMercProfiles[cnt].bInvStatus[HANDPOS]   );
			FilePrintf(hFile,"\t\t<mHelmetDrop>1</mHelmetDrop>\r\n");			//	gMercProfiles[cnt].iDrop[HELMETPOS]   );
			FilePrintf(hFile,"\t\t<mVestDrop>1</mVestDrop>\r\n");				//	gMercProfiles[cnt].iDrop[VESTPOS]   );
			FilePrintf(hFile,"\t\t<mLegDrop>1</mLegDrop>\r\n");					//	gMercProfiles[cnt].iDrop[LEGPOS]   );
			FilePrintf(hFile,"\t\t<mWeaponDrop>1</mWeaponDrop>\r\n");			//	gMercProfiles[cnt].iDrop[HANDPOS]   );
			FilePrintf(hFile,"\t\t<mBig0>%d</mBig0>\r\n",							gMercProfiles[cnt].inv[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig1>%d</mBig1>\r\n",							gMercProfiles[cnt].inv[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig2>%d</mBig2>\r\n",							gMercProfiles[cnt].inv[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig3>%d</mBig3>\r\n",							gMercProfiles[cnt].inv[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mBig0Quantity>%d</mBig0Quantity>\r\n",			gMercProfiles[cnt].bInvNumber[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig1Quantity>%d</mBig1Quantity>\r\n",			gMercProfiles[cnt].bInvNumber[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig2Quantity>%d</mBig2Quantity>\r\n",			gMercProfiles[cnt].bInvNumber[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig3Quantity>%d</mBig3Quantity>\r\n",			gMercProfiles[cnt].bInvNumber[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mBig0Status>%d</mBig0Status>\r\n",				gMercProfiles[cnt].bInvStatus[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig1Status>%d</mBig1Status>\r\n",				gMercProfiles[cnt].bInvStatus[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig2Status>%d</mBig2Status>\r\n",				gMercProfiles[cnt].bInvStatus[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig3Status>%d</mBig3Status>\r\n",				gMercProfiles[cnt].bInvStatus[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mBig0Drop>1</mBig0Drop>\r\n");					//gMercProfiles[cnt].iDrop[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig1Drop>1</mBig1Drop>\r\n");					//gMercProfiles[cnt].iDrop[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig2Drop>1</mBig2Drop>\r\n");					//gMercProfiles[cnt].iDrop[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig3Drop>1</mBig3Drop>\r\n");					//gMercProfiles[cnt].iDrop[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall0>%d</mSmall0>\r\n",						gMercProfiles[cnt].inv[SMALLPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mSmall1>%d</mSmall1>\r\n",						gMercProfiles[cnt].inv[SMALLPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mSmall2>%d</mSmall2>\r\n",						gMercProfiles[cnt].inv[SMALLPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mSmall3>%d</mSmall3>\r\n",						gMercProfiles[cnt].inv[SMALLPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall4>%d</mSmall4>\r\n",						gMercProfiles[cnt].inv[SMALLPOCK5POS]   );
			FilePrintf(hFile,"\t\t<mSmall5>%d</mSmall5>\r\n",						gMercProfiles[cnt].inv[SMALLPOCK6POS]   );
			FilePrintf(hFile,"\t\t<mSmall6>%d</mSmall6>\r\n",						gMercProfiles[cnt].inv[SMALLPOCK7POS]   );
			FilePrintf(hFile,"\t\t<mSmall7>%d</mSmall7>\r\n",						gMercProfiles[cnt].inv[SMALLPOCK8POS]   );
			FilePrintf(hFile,"\t\t<mSmall0Quantity>%d</mSmall0Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[SMALLPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mSmall1Quantity>%d</mSmall1Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[SMALLPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mSmall2Quantity>%d</mSmall2Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[SMALLPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mSmall3Quantity>%d</mSmall3Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[SMALLPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall4Quantity>%d</mSmall4Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[SMALLPOCK5POS]   );
			FilePrintf(hFile,"\t\t<mSmall5Quantity>%d</mSmall5Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[SMALLPOCK6POS]   );
			FilePrintf(hFile,"\t\t<mSmall6Quantity>%d</mSmall6Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[SMALLPOCK7POS]   );
			FilePrintf(hFile,"\t\t<mSmall7Quantity>%d</mSmall7Quantity>\r\n",		gMercProfiles[cnt].bInvNumber[SMALLPOCK8POS]   );
			FilePrintf(hFile,"\t\t<mSmall0Status>%d</mSmall0Status>\r\n",			gMercProfiles[cnt].bInvStatus[SMALLPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mSmall1Status>%d</mSmall1Status>\r\n",			gMercProfiles[cnt].bInvStatus[SMALLPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mSmall2Status>%d</mSmall2Status>\r\n",			gMercProfiles[cnt].bInvStatus[SMALLPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mSmall3Status>%d</mSmall3Status>\r\n",			gMercProfiles[cnt].bInvStatus[SMALLPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall4Status>%d</mSmall4Status>\r\n",			gMercProfiles[cnt].bInvStatus[SMALLPOCK5POS]   );
			FilePrintf(hFile,"\t\t<mSmall5Status>%d</mSmall5Status>\r\n",			gMercProfiles[cnt].bInvStatus[SMALLPOCK6POS]   );
			FilePrintf(hFile,"\t\t<mSmall6Status>%d</mSmall6Status>\r\n",			gMercProfiles[cnt].bInvStatus[SMALLPOCK7POS]   );
			FilePrintf(hFile,"\t\t<mSmall7Status>%d</mSmall7Status>\r\n",			gMercProfiles[cnt].bInvStatus[SMALLPOCK8POS]   );
			
			
			FilePrintf(hFile,"\t\t<lVest>0</lVest>\r\n");							//gMercProfiles[cnt].lbe[0]   );
			FilePrintf(hFile,"\t\t<lLeftThigh>0</lLeftThigh>\r\n");					//gMercProfiles[cnt].lbe[1]   );
			FilePrintf(hFile,"\t\t<lRightThigh>0</lRightThigh>\r\n");				//gMercProfiles[cnt].lbe[2]   );
			FilePrintf(hFile,"\t\t<lCPack>0</lCPack>\r\n");							//gMercProfiles[cnt].lbe[3]   );
			FilePrintf(hFile,"\t\t<lBPack>0</lBPack>\r\n");							//gMercProfiles[cnt].lbe[4]   );
			FilePrintf(hFile,"\t\t<lVestStatus>0</lVestStatus>\r\n");				//gMercProfiles[cnt].lStatus[0]   );
			FilePrintf(hFile,"\t\t<lLeftThighStatus>0</lLeftThighStatus>\r\n");		//gMercProfiles[cnt].lStatus[1]   );
			FilePrintf(hFile,"\t\t<lRightThighStatus>0</lRightThighStatus>\r\n");	//gMercProfiles[cnt].lStatus[2]   );
			FilePrintf(hFile,"\t\t<lCPackStatus>0</lCPackStatus>\r\n");				//gMercProfiles[cnt].lStatus[3]   );
			FilePrintf(hFile,"\t\t<lBPackStatus>0</lBPackStatus>\r\n");				//gMercProfiles[cnt].lStatus[4]   );
/*
/*			FilePrintf(hFile,"\t\t<mHelmet>%d</mHelmet>\r\n",						gMercProfileGear[cnt].inv[HELMETPOS]  );
			FilePrintf(hFile,"\t\t<mVest>%d</mVest>\r\n",							gMercProfileGear[cnt].inv[VESTPOS]   );
			FilePrintf(hFile,"\t\t<mLeg>%d</mLeg>\r\n",								gMercProfileGear[cnt].inv[LEGPOS]   );
			FilePrintf(hFile,"\t\t<mWeapon>%d</mWeapon>\r\n",						gMercProfileGear[cnt].inv[HANDPOS]   );
			FilePrintf(hFile,"\t\t<mHelmetStatus>%d</mHelmetStatus>\r\n",			gMercProfileGear[cnt].iStatus[HELMETPOS]   );
			FilePrintf(hFile,"\t\t<mVestStatus>%d</mVestStatus>\r\n",				gMercProfileGear[cnt].iStatus[VESTPOS]   );
			FilePrintf(hFile,"\t\t<mLegStatus>%d</mLegStatus>\r\n",					gMercProfileGear[cnt].iStatus[LEGPOS]   );
			FilePrintf(hFile,"\t\t<mWeaponStatus>%d</mWeaponStatus>\r\n",			gMercProfileGear[cnt].iStatus[HANDPOS]   );
			FilePrintf(hFile,"\t\t<mHelmetDrop>%d</mHelmetDrop>\r\n",				gMercProfileGear[cnt].iDrop[HELMETPOS]   );
			FilePrintf(hFile,"\t\t<mVestDrop>%d</mVestDrop>\r\n",					gMercProfileGear[cnt].iDrop[VESTPOS]   );
			FilePrintf(hFile,"\t\t<mLegDrop>%d</mLegDrop>\r\n",						gMercProfileGear[cnt].iDrop[LEGPOS]   );
			FilePrintf(hFile,"\t\t<mWeaponDrop>%d</mWeaponDrop>\r\n",				gMercProfileGear[cnt].iDrop[HANDPOS]   );
			FilePrintf(hFile,"\t\t<mBig0>%d</mBig0>\r\n",							gMercProfileGear[cnt].inv[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig1>%d</mBig1>\r\n",							gMercProfileGear[cnt].inv[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig2>%d</mBig2>\r\n",							gMercProfileGear[cnt].inv[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig3>%d</mBig3>\r\n",							gMercProfileGear[cnt].inv[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mBig0Quantity>%d</mBig0Quantity>\r\n",			gMercProfileGear[cnt].iNumber[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig1Quantity>%d</mBig1Quantity>\r\n",			gMercProfileGear[cnt].iNumber[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig2Quantity>%d</mBig2Quantity>\r\n",			gMercProfileGear[cnt].iNumber[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig3Quantity>%d</mBig3Quantity>\r\n",			gMercProfileGear[cnt].iNumber[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mBig0Status>%d</mBig0Status>\r\n",				gMercProfileGear[cnt].iStatus[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig1Status>%d</mBig1Status>\r\n",				gMercProfileGear[cnt].iStatus[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig2Status>%d</mBig2Status>\r\n",				gMercProfileGear[cnt].iStatus[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig3Status>%d</mBig3Status>\r\n",				gMercProfileGear[cnt].iStatus[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mBig0Drop>%d</mBig0Drop>\r\n",					gMercProfileGear[cnt].iDrop[BIGPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mBig1Drop>%d</mBig1Drop>\r\n",					gMercProfileGear[cnt].iDrop[BIGPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mBig2Drop>%d</mBig2Drop>\r\n",					gMercProfileGear[cnt].iDrop[BIGPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mBig3Drop>%d</mBig3Drop>\r\n",					gMercProfileGear[cnt].iDrop[BIGPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall0>%d</mSmall0>\r\n",						gMercProfileGear[cnt].inv[SMALLPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mSmall1>%d</mSmall1>\r\n",						gMercProfileGear[cnt].inv[SMALLPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mSmall2>%d</mSmall2>\r\n",						gMercProfileGear[cnt].inv[SMALLPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mSmall3>%d</mSmall3>\r\n",						gMercProfileGear[cnt].inv[SMALLPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall4>%d</mSmall4>\r\n",						gMercProfileGear[cnt].inv[SMALLPOCK5POS]   );
			FilePrintf(hFile,"\t\t<mSmall5>%d</mSmall5>\r\n",						gMercProfileGear[cnt].inv[SMALLPOCK6POS]   );
			FilePrintf(hFile,"\t\t<mSmall6>%d</mSmall6>\r\n",						gMercProfileGear[cnt].inv[SMALLPOCK7POS]   );
			FilePrintf(hFile,"\t\t<mSmall7>%d</mSmall7>\r\n",						gMercProfileGear[cnt].inv[SMALLPOCK8POS]   );
			FilePrintf(hFile,"\t\t<mSmall0Quantity>%d</mSmall0Quantity>\r\n",		gMercProfileGear[cnt].iNumber[SMALLPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mSmall1Quantity>%d</mSmall1Quantity>\r\n",		gMercProfileGear[cnt].iNumber[SMALLPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mSmall2Quantity>%d</mSmall2Quantity>\r\n",		gMercProfileGear[cnt].iNumber[SMALLPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mSmall3Quantity>%d</mSmall3Quantity>\r\n",		gMercProfileGear[cnt].iNumber[SMALLPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall4Quantity>%d</mSmall4Quantity>\r\n",		gMercProfileGear[cnt].iNumber[SMALLPOCK5POS]   );
			FilePrintf(hFile,"\t\t<mSmall5Quantity>%d</mSmall5Quantity>\r\n",		gMercProfileGear[cnt].iNumber[SMALLPOCK6POS]   );
			FilePrintf(hFile,"\t\t<mSmall6Quantity>%d</mSmall6Quantity>\r\n",		gMercProfileGear[cnt].iNumber[SMALLPOCK7POS]   );
			FilePrintf(hFile,"\t\t<mSmall7Quantity>%d</mSmall7Quantity>\r\n",		gMercProfileGear[cnt].iNumber[SMALLPOCK8POS]   );
			FilePrintf(hFile,"\t\t<mSmall0Status>%d</mSmall0Status>\r\n",			gMercProfileGear[cnt].iStatus[SMALLPOCK1POS]   );
			FilePrintf(hFile,"\t\t<mSmall1Status>%d</mSmall1Status>\r\n",			gMercProfileGear[cnt].iStatus[SMALLPOCK2POS]   );
			FilePrintf(hFile,"\t\t<mSmall2Status>%d</mSmall2Status>\r\n",			gMercProfileGear[cnt].iStatus[SMALLPOCK3POS]   );
			FilePrintf(hFile,"\t\t<mSmall3Status>%d</mSmall3Status>\r\n",			gMercProfileGear[cnt].iStatus[SMALLPOCK4POS]   );
			FilePrintf(hFile,"\t\t<mSmall4Status>%d</mSmall4Status>\r\n",			gMercProfileGear[cnt].iStatus[SMALLPOCK5POS]   );
			FilePrintf(hFile,"\t\t<mSmall5Status>%d</mSmall5Status>\r\n",			gMercProfileGear[cnt].iStatus[SMALLPOCK6POS]   );
			FilePrintf(hFile,"\t\t<mSmall6Status>%d</mSmall6Status>\r\n",			gMercProfileGear[cnt].iStatus[SMALLPOCK7POS]   );
			FilePrintf(hFile,"\t\t<mSmall7Status>%d</mSmall7Status>\r\n",			gMercProfileGear[cnt].iStatus[SMALLPOCK8POS]   );
			FilePrintf(hFile,"\t\t<lVest>%d</lVest>\r\n",							gMercProfileGear[cnt].lbe[0]   );
			FilePrintf(hFile,"\t\t<lLeftThigh>%d</lLeftThigh>\r\n",					gMercProfileGear[cnt].lbe[1]   );
			FilePrintf(hFile,"\t\t<lRightThigh>%d</lRightThigh>\r\n",				gMercProfileGear[cnt].lbe[2]   );
			FilePrintf(hFile,"\t\t<lCPack>%d</lCPack>\r\n",							gMercProfileGear[cnt].lbe[3]   );
			FilePrintf(hFile,"\t\t<lBPack>%d</lBPack>\r\n",							gMercProfileGear[cnt].lbe[4]   );
			FilePrintf(hFile,"\t\t<lVestStatus>%d</lVestStatus>\r\n",				gMercProfileGear[cnt].lStatus[0]   );
			FilePrintf(hFile,"\t\t<lLeftThighStatus>%d</lLeftThighStatus>\r\n",		gMercProfileGear[cnt].lStatus[1]   );
			FilePrintf(hFile,"\t\t<lRightThighStatus>%d</lRightThighStatus>\r\n",	gMercProfileGear[cnt].lStatus[2]   );
			FilePrintf(hFile,"\t\t<lCPackStatus>%d</lCPackStatus>\r\n",				gMercProfileGear[cnt].lStatus[3]   );
			FilePrintf(hFile,"\t\t<lBPackStatus>%d</lBPackStatus>\r\n",				gMercProfileGear[cnt].lStatus[4]   );
*/
			FilePrintf(hFile,"\t</MERCGEAR>\r\n");
		}
		FilePrintf(hFile,"</MERCGEARLIST>\r\n");
	}
	FileClose( hFile );

	return( TRUE );
}
