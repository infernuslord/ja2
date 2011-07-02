#ifdef PRECOMPILEDHEADERS
	#include "Tactical All.h"
#else
	#include "sgp.h"
	#include "Debug Control.h"
	#include "expat.h"
	#include "XML.h"
	#include "Interface.h"
	#include "Vehicles.h"
#endif

struct
{
	PARSE_STAGE	curElement;

	CHAR8		szCharData[MAX_CHAR_DATA_LENGTH+1];
	NEW_CAR	curNewCar;
	NEW_CAR *	curArray;

	UINT32			maxArraySize;
	UINT32			curIndex;
	UINT32			currentDepth;
	UINT32			maxReadDepth;
}
typedef newCarParseData;

BOOLEAN NewCar_TextOnly;

void InitNewVehicles ();

static void XMLCALL
newCarStartElementHandle(void *userData, const XML_Char *name, const XML_Char **atts)
{
	newCarParseData * pData = (newCarParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) //are we reading this element?
	{
		if(strcmp(name, "VEHICLES") == 0 && pData->curElement == ELEMENT_NONE)
		{
			pData->curElement = ELEMENT_LIST;

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(strcmp(name, "VEHICLE") == 0 && pData->curElement == ELEMENT_LIST)
		{
			pData->curElement = ELEMENT;

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(pData->curElement == ELEMENT &&
			  ( strcmp(name, "uiIndex") == 0 ||
			   strcmp(name, "MvtTypes") == 0 ||
			   strcmp(name, "SeatingCapacities") == 0 ||
			   strcmp(name, "EnterVehicleSndID") == 0 ||
			   strcmp(name, "MoveVehicleSndID") == 0 ||
			   strcmp(name, "VehicleTypeProfileID") == 0 ||
			   strcmp(name, "VehicleArmourType") == 0 ||
			   strcmp(name, "VehicleBodyType") == 0 ||
			   strcmp(name, "VehicleEnabled") == 0 ||
			   strcmp(name, "Pilot") == 0 ||
			   strcmp(name, "StiFaceIcon") == 0 ||	   
			   strcmp(name, "Name") == 0 ||
			   strcmp(name, "LongName") == 0 ||
			   strcmp(name, "ShortName") == 0 ||		   
			   strcmp(name, "Neutral") == 0 ))
		{
			pData->curElement = ELEMENT_PROPERTY;

			pData->maxReadDepth++; //we are not skipping this element
		}

		pData->szCharData[0] = '\0';
	}

	pData->currentDepth++;

}

static void XMLCALL
newCarCharacterDataHandle(void *userData, const XML_Char *str, int len)
{
	newCarParseData * pData = (newCarParseData *)userData;

	if( (pData->currentDepth <= pData->maxReadDepth) &&
		(strlen(pData->szCharData) < MAX_CHAR_DATA_LENGTH)
	){
		strncat(pData->szCharData,str,__min((unsigned int)len,MAX_CHAR_DATA_LENGTH-strlen(pData->szCharData)));
	}
}


static void XMLCALL
newCarEndElementHandle(void *userData, const XML_Char *name)
{

char temp;

	newCarParseData * pData = (newCarParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) 
	{
		if(strcmp(name, "VEHICLES") == 0)
		{
			pData->curElement = ELEMENT_NONE;
		}
		else if(strcmp(name, "VEHICLE") == 0)
		{
			pData->curElement = ELEMENT_LIST;	
			
			if (!NewCar_TextOnly)
				{		
					gNewVehicle[pData->curNewCar.uiIndex].uiIndex = pData->curNewCar.uiIndex;
					gNewVehicle[pData->curNewCar.uiIndex].iNewMvtTypes = pData->curNewCar.iNewMvtTypes;
					gNewVehicle[pData->curNewCar.uiIndex].iNewSeatingCapacities = pData->curNewCar.iNewSeatingCapacities;
					gNewVehicle[pData->curNewCar.uiIndex].iNewEnterVehicleSndID = pData->curNewCar.iNewEnterVehicleSndID;
					gNewVehicle[pData->curNewCar.uiIndex].iNewMoveVehicleSndID = pData->curNewCar.iNewMoveVehicleSndID;
					gNewVehicle[pData->curNewCar.uiIndex].ubNewVehicleTypeProfileID = pData->curNewCar.ubNewVehicleTypeProfileID;
					gNewVehicle[pData->curNewCar.uiIndex].sNewVehicleArmourType = pData->curNewCar.sNewVehicleArmourType;
					gNewVehicle[pData->curNewCar.uiIndex].NewVehicleBodyType = pData->curNewCar.NewVehicleBodyType;	
					gNewVehicle[pData->curNewCar.uiIndex].bNewVehicle = pData->curNewCar.bNewVehicle;
					gNewVehicle[pData->curNewCar.uiIndex].bNewNeutral = pData->curNewCar.bNewNeutral;
					gNewVehicle[pData->curNewCar.uiIndex].NewPilot = pData->curNewCar.NewPilot;	
					strcpy(gNewVehicle[pData->curNewCar.uiIndex].szIconFace, pData->curNewCar.szIconFace);
					gNewVehicle[ pData->curNewCar.uiIndex ].NewCarPortraits = -1;					
					wcscpy(gNewVehicle[pData->curNewCar.uiIndex].NewVehicleStrings, pData->curNewCar.NewVehicleStrings);
					wcscpy(gNewVehicle[pData->curNewCar.uiIndex].NewVehicleName, pData->curNewCar.NewVehicleName);
					wcscpy(gNewVehicle[pData->curNewCar.uiIndex].NewShortVehicleStrings, pData->curNewCar.NewShortVehicleStrings);
					gNewVehicle[ pData->curNewCar.uiIndex ].NewUsed = FALSE;
				}
				else
				{
					wcscpy(gNewVehicle[pData->curNewCar.uiIndex].NewVehicleStrings, pData->curNewCar.NewVehicleStrings);
					wcscpy(gNewVehicle[pData->curNewCar.uiIndex].NewVehicleName, pData->curNewCar.NewVehicleName);
					wcscpy(gNewVehicle[pData->curNewCar.uiIndex].NewShortVehicleStrings, pData->curNewCar.NewShortVehicleStrings);					
				}		
		}
		else if(strcmp(name, "uiIndex") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curNewCar.uiIndex	= (UINT8) atol(pData->szCharData);
		}
		else if(strcmp(name, "MvtTypes") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curNewCar.iNewMvtTypes	= (INT32) atol(pData->szCharData);
		}	
		else if(strcmp(name, "SeatingCapacities") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curNewCar.iNewSeatingCapacities	= (INT32) atol(pData->szCharData);
		}	
		else if(strcmp(name, "EnterVehicleSndID") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curNewCar.iNewEnterVehicleSndID	= (INT32) atol(pData->szCharData);
		}	
		else if(strcmp(name, "MoveVehicleSndID") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curNewCar.iNewMoveVehicleSndID	= (INT32) atol(pData->szCharData);
		}	
	//	else if(strcmp(name, "VehicleTypeProfileID") == 0)
	//	{
	//		pData->curElement = ELEMENT;
	//		pData->curNewCar.ubNewVehicleTypeProfileID	= (UINT8) atol(pData->szCharData);
	//	}	
		else if(strcmp(name, "VehicleArmourType") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curNewCar.sNewVehicleArmourType	= (INT16) atol(pData->szCharData);
		}	
	//	else if(strcmp(name, "VehicleBodyType") == 0)
	//	{
	//		pData->curElement = ELEMENT;
	//		pData->curNewCar.NewVehicleBodyType	= (INT8) atol(pData->szCharData);
	//	}		
		else if(strcmp(name, "VehicleEnabled") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curNewCar.bNewVehicle	= (BOOLEAN) atol(pData->szCharData);
		}	
		else if(strcmp(name, "Neutral") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curNewCar.bNewNeutral	= (BOOLEAN) atol(pData->szCharData);
		}	
		else if(strcmp(name, "Pilot") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curNewCar.NewPilot	= (INT8) atol(pData->szCharData);
		}		
		else if(strcmp(name, "Name") == 0 )
		{
			pData->curElement = ELEMENT;

			MultiByteToWideChar( CP_UTF8, 0, pData->szCharData, -1, pData->curNewCar.NewVehicleName, sizeof(pData->curNewCar.NewVehicleName)/sizeof(pData->curNewCar.NewVehicleName[0]) );
			pData->curNewCar.NewVehicleName[sizeof(pData->curNewCar.NewVehicleName)/sizeof(pData->curNewCar.NewVehicleName[0]) - 1] = '\0';
		}
		else if(strcmp(name, "LongName") == 0 )
		{
			pData->curElement = ELEMENT;

			MultiByteToWideChar( CP_UTF8, 0, pData->szCharData, -1, pData->curNewCar.NewVehicleStrings, sizeof(pData->curNewCar.NewVehicleStrings)/sizeof(pData->curNewCar.NewVehicleStrings[0]) );
			pData->curNewCar.NewVehicleStrings[sizeof(pData->curNewCar.NewVehicleStrings)/sizeof(pData->curNewCar.NewVehicleStrings[0]) - 1] = '\0';
		}
		else if(strcmp(name, "ShortName") == 0 )
		{
			pData->curElement = ELEMENT;

			MultiByteToWideChar( CP_UTF8, 0, pData->szCharData, -1, pData->curNewCar.NewShortVehicleStrings, sizeof(pData->curNewCar.NewShortVehicleStrings)/sizeof(pData->curNewCar.NewShortVehicleStrings[0]) );
			pData->curNewCar.NewShortVehicleStrings[sizeof(pData->curNewCar.NewShortVehicleStrings)/sizeof(pData->curNewCar.NewShortVehicleStrings[0]) - 1] = '\0';
		}
		else if(strcmp(name, "StiFaceIcon") == 0)
		{
			if(MAX_MAIN_VEHICLE_CHARS >= strlen(pData->szCharData))
				strcpy(pData->curNewCar.szIconFace,pData->szCharData);
			else
			{
				strncpy(pData->curNewCar.szIconFace,pData->szCharData,MAX_MAIN_VEHICLE_CHARS);
				pData->curNewCar.szIconFace[MAX_MAIN_VEHICLE_CHARS] = '\0';
			}

			for(int i=0;i<min((int)strlen(pData->szCharData),MAX_MAIN_VEHICLE_CHARS);i++)
			{
				temp = pData->szCharData[i];
				pData->curNewCar.szIconFace[i] = temp;
			}
		}
		
		pData->maxReadDepth--;
	}
	pData->currentDepth--;
}

BOOLEAN ReadInNewCar(STR fileName, BOOLEAN localizedVersion)
{
	HWFILE		hFile;
	UINT32		uiBytesRead;
	UINT32		uiFSize;
	CHAR8 *		lpcBuffer;
	XML_Parser	parser = XML_ParserCreate(NULL);

	newCarParseData pData;

	DebugMsg(TOPIC_JA2, DBG_LEVEL_3, "Loading Vehicles.xml" );

	NewCar_TextOnly = localizedVersion;
	
	// Open file
	hFile = FileOpen( fileName, FILE_ACCESS_READ, FALSE );
	if ( !hFile )
		return( localizedVersion );

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


	XML_SetElementHandler(parser, newCarStartElementHandle, newCarEndElementHandle);
	XML_SetCharacterDataHandler(parser, newCarCharacterDataHandle);


	memset(&pData,0,sizeof(pData));
	XML_SetUserData(parser, &pData);


	if(!XML_Parse(parser, lpcBuffer, uiFSize, TRUE))
	{
		CHAR8 errorBuf[511];

		sprintf(errorBuf, "XML Parser Error in NewCar.xml: %s at line %d", XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser));
		LiveMessage(errorBuf);

		MemFree(lpcBuffer);
		return FALSE;
	}

	MemFree(lpcBuffer);


	XML_ParserFree(parser);


	return( TRUE );
}

void InitNewVehicles ()
{
	UINT32 iCount;
	
		for( iCount=0; iCount<NUM_PROFILES; iCount++ )
		{	
			gNewVehicle[ iCount ].uiIndex = iCount;
			gNewVehicle[ iCount ].iNewMvtTypes = 1; // car
			gNewVehicle[ iCount ].iNewSeatingCapacities = 6;
			gNewVehicle[ iCount ].iNewEnterVehicleSndID = 86;
			gNewVehicle[ iCount ].iNewMoveVehicleSndID  = 83;
			gNewVehicle[ iCount ].ubNewVehicleTypeProfileID = -1;
			gNewVehicle[ iCount ].sNewVehicleArmourType = 164;
			gNewVehicle[ iCount ].NewVehicleBodyType = 0;
			gNewVehicle[ iCount ].bNewNeutral = TRUE;
			gNewVehicle[ iCount ].bNewVehicle = FALSE;
			gNewVehicle[ iCount ].NewPilot = -1;	
			gNewVehicle[ iCount ].NewCarPortraits = -1;
			gNewVehicle[ iCount ].szIconFace[MAX_MAIN_VEHICLE_CHARS] = '\0';
			gNewVehicle[ iCount ].NewVehicleStrings[128] = '\0';
			gNewVehicle[ iCount ].NewVehicleName[128] = '\0';
			gNewVehicle[ iCount ].NewShortVehicleStrings[128] = '\0';	
			gNewVehicle[ iCount ].NewUsed = FALSE;
		}
}

BOOLEAN WriteNewCar(STR fileName)
{
	HWFILE		hFile;

	//Debug code; make sure that what we got from the file is the same as what's there
	// Open a new file
	hFile = FileOpen( fileName, FILE_ACCESS_WRITE | FILE_CREATE_ALWAYS, FALSE );
	if ( !hFile )
		return( FALSE );

	{
		UINT32 cnt;
		
		FilePrintf(hFile,"<VEHICLES>\r\n");
		for(cnt = 0;cnt < NUM_PROFILES;cnt++)
		{
			FilePrintf(hFile,"\t<VEHICLE>\r\n");
			FilePrintf(hFile,"\t\t<uiIndex>%d</uiIndex>\r\n", cnt);
			
			FilePrintf(hFile,"\t\t<Name>");

			STR16 szRemainder = gNewVehicle[cnt].NewVehicleName; //the remaining string to be output (for making valid XML)

			while(szRemainder[0] != '\0')
			{
				//UINT32 uiCharLoc = wcscspn(szRemainder,L"&<>\'\"\0");
				UINT32 uiCharLoc = wcscspn(szRemainder,L"&<>\0");
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

					//case '\'':
					//	FilePrintf(hFile,"&apos;");
					//	szRemainder++;
					//break;

					//case '\"':
					//	FilePrintf(hFile,"&quot;");
					//	szRemainder++;
					//break;
				}
			}

			FilePrintf(hFile,"</Name>\r\n");
			
			FilePrintf(hFile,"\t\t<LongName>");
			
			STR16 szRemainder1 = gNewVehicle[cnt].NewVehicleStrings; //the remaining string to be output (for making valid XML)

			while(szRemainder1[0] != '\0')
			{
				//UINT32 uiCharLoc = wcscspn(szRemainder1,L"&<>\'\"\0");
				UINT32 uiCharLoc = wcscspn(szRemainder1,L"&<>\0");
				CHAR16 invChar = szRemainder1[uiCharLoc];

				if(uiCharLoc)
				{
					szRemainder1[uiCharLoc] = '\0';
					FilePrintf(hFile,"%S",szRemainder1);
					szRemainder1[uiCharLoc] = invChar;
				}

				szRemainder1 += uiCharLoc;

				switch(invChar)
				{
					case '&':
						FilePrintf(hFile,"&amp;");
						szRemainder1++;
					break;

					case '<':
						FilePrintf(hFile,"&lt;");
						szRemainder1++;
					break;

					case '>':
						FilePrintf(hFile,"&gt;");
						szRemainder1++;
					break;

					//case '\'':
					//	FilePrintf(hFile,"&apos;");
					//	szRemainder1++;
					//break;

					//case '\"':
					//	FilePrintf(hFile,"&quot;");
					//	szRemainder1++;
					//break;
				}
			}

			FilePrintf(hFile,"</LongName>\r\n");
			
			FilePrintf(hFile,"\t\t<ShortName>");
			
			STR16 szRemainder2 = gNewVehicle[cnt].NewShortVehicleStrings; //the remaining string to be output (for making valid XML)

			while(szRemainder2[0] != '\0')
			{
				//UINT32 uiCharLoc = wcscspn(szRemainder2,L"&<>\'\"\0");
				UINT32 uiCharLoc = wcscspn(szRemainder2,L"&<>\0");
				CHAR16 invChar = szRemainder2[uiCharLoc];

				if(uiCharLoc)
				{
					szRemainder2[uiCharLoc] = '\0';
					FilePrintf(hFile,"%S",szRemainder2);
					szRemainder2[uiCharLoc] = invChar;
				}

				szRemainder2 += uiCharLoc;

				switch(invChar)
				{
					case '&':
						FilePrintf(hFile,"&amp;");
						szRemainder2++;
					break;

					case '<':
						FilePrintf(hFile,"&lt;");
						szRemainder2++;
					break;

					case '>':
						FilePrintf(hFile,"&gt;");
						szRemainder2++;
					break;

					//case '\'':
					//	FilePrintf(hFile,"&apos;");
					//	szRemainde2r++;
					//break;

					//case '\"':
					//	FilePrintf(hFile,"&quot;");
					//	szRemainder2++;
					//break;
				}
			}

			FilePrintf(hFile,"</ShortName>\r\n");
			
		/*	FilePrintf(hFile,"\t\t<StiFaceIcon>");
			
			STR16 szRemainder3 = gNewVehicle[cnt].szIconFace; //the remaining string to be output (for making valid XML)

			while(szRemainder3[0] != '\0')
			{
				//UINT32 uiCharLoc = wcscspn(szRemainder3,L"&<>\'\"\0");
				UINT32 uiCharLoc = wcscspn(szRemainder3,L"&<>\0");
				CHAR16 invChar = szRemainder3[uiCharLoc];

				if(uiCharLoc)
				{
					szRemainder3[uiCharLoc] = '\0';
					FilePrintf(hFile,"%S",szRemainder3);
					szRemainder3[uiCharLoc] = invChar;
				}

				szRemainder3 += uiCharLoc;

				switch(invChar)
				{
					case '&':
						FilePrintf(hFile,"&amp;");
						szRemainder3++;
					break;

					case '<':
						FilePrintf(hFile,"&lt;");
						szRemainder3++;
					break;

					case '>':
						FilePrintf(hFile,"&gt;");
						szRemainder3++;
					break;

					//case '\'':
					//	FilePrintf(hFile,"&apos;");
					//	szRemainder3++;
					//break;

					//case '\"':
					//	FilePrintf(hFile,"&quot;");
					//	szRemainder3++;
					//break;
				}
			}

			FilePrintf(hFile,"</StiFaceIcon>\r\n");
			*/
			FilePrintf(hFile,"\t\t<MvtTypes>%d</MvtTypes>\r\n",gNewVehicle[cnt].iNewMvtTypes);
			FilePrintf(hFile,"\t\t<SeatingCapacities>%d</SeatingCapacities>\r\n",gNewVehicle[cnt].iNewSeatingCapacities );
			FilePrintf(hFile,"\t\t<EnterVehicleSndID>%d</EnterVehicleSndID>\r\n",gNewVehicle[cnt].iNewEnterVehicleSndID);
			FilePrintf(hFile,"\t\t<MoveVehicleSndID>%d</MoveVehicleSndID>\r\n",gNewVehicle[cnt].iNewMoveVehicleSndID);
			FilePrintf(hFile,"\t\t<VehicleTypeProfileID>%d</VehicleTypeProfileID>\r\n",gNewVehicle[cnt].ubNewVehicleTypeProfileID);
			FilePrintf(hFile,"\t\t<VehicleArmourType>%d</VehicleArmourType>\r\n",gNewVehicle[cnt].sNewVehicleArmourType);
			FilePrintf(hFile,"\t\t<VehicleBodyType>%d</VehicleBodyType>\r\n",gNewVehicle[cnt].NewVehicleBodyType);
			FilePrintf(hFile,"\t\t<Neutral>%d</Neutral>\r\n",gNewVehicle[cnt].bNewNeutral);
			FilePrintf(hFile,"\t\t<VehicleEnabled>%d</VehicleEnabled>\r\n",gNewVehicle[cnt].bNewVehicle);	
			FilePrintf(hFile,"\t\t<Pilot>%d</Pilot>\r\n",gNewVehicle[cnt].NewPilot);				
			FilePrintf(hFile,"\t</VEHICLE>\r\n");
			
	/*
					strcpy(gNewVehicle[pData->curNewCar.uiIndex].szIconFace, pData->curNewCar.szIconFace);				
					wcscpy(gNewVehicle[pData->curNewCar.uiIndex].NewVehicleStrings, pData->curNewCar.NewVehicleStrings);
					wcscpy(gNewVehicle[pData->curNewCar.uiIndex].NewVehicleName, pData->curNewCar.NewVehicleName);
					wcscpy(gNewVehicle[pData->curNewCar.uiIndex].NewShortVehicleStrings, pData->curNewCar.NewShortVehicleStrings);
	*/
		}
		FilePrintf(hFile,"</VEHICLES>\r\n");
		
/*
		FilePrintf(hFile,"<VEHICLES>\r\n");
		for(cnt = 0;cnt < NUM_PROFILES;cnt++)
		{
			FilePrintf(hFile,"\t<VEHICLE>\r\n");
			FilePrintf(hFile,"\t\t<uiIndex>%d</uiIndex>\r\n", cnt);
			FilePrintf(hFile,"\t\t<Name>None</Name>\r\n");
			FilePrintf(hFile,"\t\t<MvtTypes>0</MvtTypes>\r\n");
			FilePrintf(hFile,"\t\t<SeatingCapacities>6</SeatingCapacities>\r\n");
			FilePrintf(hFile,"\t\t<EnterVehicleSndID>86</EnterVehicleSndID>\r\n");
			FilePrintf(hFile,"\t\t<MoveVehicleSndID>83</MoveVehicleSndID>\r\n");
			FilePrintf(hFile,"\t\t<VehicleTypeProfileID>-1</VehicleTypeProfileID>\r\n");
			FilePrintf(hFile,"\t\t<VehicleArmourType>164</VehicleArmourType>\r\n");
			//FilePrintf(hFile,"\t\t<VehicleBodyType>164</VehicleBodyType>\r\n");
			FilePrintf(hFile,"\t\t<Neutral>1</Neutral>\r\n");
			//FilePrintf(hFile,"\t\t<VehicleEnabled>0</VehicleEnabled>\r\n");	
			FilePrintf(hFile,"\t\t<Pilot>-1</Pilot>\r\n");				
			FilePrintf(hFile,"\t</VEHICLE>\r\n");
		}
		FilePrintf(hFile,"</VEHICLES>\r\n");
		
		*/
	}
	FileClose( hFile );

	return( TRUE );
}
