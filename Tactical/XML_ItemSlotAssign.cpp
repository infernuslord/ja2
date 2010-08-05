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

	ItemSlotAssignStruct	curItemSlotAssign;
	UINT32			maxArraySize;
	UINT32			curIndex;
	UINT32			currentDepth;
	UINT32			maxReadDepth;
}
typedef itemslotassignParseData;

static void XMLCALL
itemslotassignStartElementHandle(void *userData, const XML_Char *name, const XML_Char **atts)
{
	itemslotassignParseData * pData = (itemslotassignParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) //are we reading this element?
	{
		if(strcmp(name, "ITEMSLOTASSIGNLIST") == 0 && pData->curElement == ELEMENT_NONE)
		{
			pData->curElement = ELEMENT_LIST;

			pData->maxReadDepth++; //we are not skipping this element
		}
		else if(strcmp(name, "ITEMSLOTASSIGN") == 0 && pData->curElement == ELEMENT_LIST)
		{
			pData->curElement = ELEMENT;

			//DebugMsg(TOPIC_JA2, DBG_LEVEL_3,"ItemSlotAssignStartElementHandle: setting memory for curItemSlotAssign");

			memset(&pData->curItemSlotAssign,0,sizeof(pData->curItemSlotAssign));
			pData->curItemSlotAssign.itemSlots.reserve(MAX_ATTACHMENTS);

			pData->maxReadDepth++; //we are not skipping this element
			pData->curIndex++;
		}
		else if(pData->curElement == ELEMENT &&
				(strcmp(name, "itemIndex") == 0				||
				 strcmp(name, "itemSlotAssignIndex") == 0	))
		{
			pData->curElement = ELEMENT_PROPERTY;

			pData->maxReadDepth++; //we are not skipping this element
		}

		pData->szCharData[0] = '\0';
	}

	pData->currentDepth++;

}

static void XMLCALL
itemslotassignCharacterDataHandle(void *userData, const XML_Char *str, int len)
{
	itemslotassignParseData * pData = (itemslotassignParseData *)userData;

	if( (pData->currentDepth <= pData->maxReadDepth) &&
		(strlen(pData->szCharData) < MAX_CHAR_DATA_LENGTH)
	){
		strncat(pData->szCharData,str,__min((unsigned int)len,MAX_CHAR_DATA_LENGTH-strlen(pData->szCharData)));
	}
}


static void XMLCALL
itemslotassignEndElementHandle(void *userData, const XML_Char *name)
{
	itemslotassignParseData * pData = (itemslotassignParseData *)userData;

	if(pData->currentDepth <= pData->maxReadDepth) //we're at the end of an element that we've been reading
	{
		if(strcmp(name, "ITEMSLOTASSIGNLIST") == 0)
		{
			pData->curElement = ELEMENT_NONE;
		}
		else if(strcmp(name, "ITEMSLOTASSIGN") == 0)
		{
			pData->curElement = ELEMENT_LIST;

			if(pData->curIndex < pData->maxArraySize)
			{
				pData->curItemSlotAssign.itemSlots.reserve(pData->curItemSlotAssign.itemSlots.size());
				//DebugMsg(TOPIC_JA2, DBG_LEVEL_3,"ItemSlotAssignStartElementHandle: writing ItemSlotAssign to array");
				ItemSlotAssign[pData->curIndex].itemIndex = pData->curItemSlotAssign.itemIndex; //write the ItemSlotAssign into the table
				ItemSlotAssign[pData->curIndex].itemSlots = pData->curItemSlotAssign.itemSlots;

			}
		}
		else if(strcmp(name, "itemIndex") == 0)
		{
			pData->curElement = ELEMENT;
			pData->curItemSlotAssign.itemIndex = (UINT16) atol(pData->szCharData);
		}
		else if(strcmp(name, "itemSlotAssignIndex") == 0)
		{
			pData->curElement = ELEMENT;

			pData->curItemSlotAssign.itemSlots.push_back((UINT16) atol(pData->szCharData));

			AssertMsg(pData->curItemSlotAssign.itemSlots.size() <= MAX_ATTACHMENTS, "Too many attachments were found");
		}

		pData->maxReadDepth--;
	}

	pData->currentDepth--;
}

//WarmSteel - Adds the default slots as defined in AttachmentSlots.
void AddDefaultSlots(){

	for(UINT32 cnt1 = 1; cnt1 < MAXITEMS; cnt1++)
	{
		//WarmSteel - end of the item list
		if(Item[cnt1].uiIndex == 0)
			break;

		INT32 totalSlots = -1;
		UINT32 cnt2 = 0;

		//Count the amount of slots and store them in totalSlots.
		for(UINT32 cnt2 = 0; cnt2 < MAXATTACHMENTS; cnt2++)
		{
			//WarmSteel - end of this list, or we found the item
			if(Item[cnt1].uiIndex == ItemSlotAssign[cnt2].itemIndex){
				totalSlots = ItemSlotAssign[cnt2].itemSlots.size();
				break;
			} else if (ItemSlotAssign[cnt2].itemIndex == 0){
				break;
			}
		}
		if(Item[cnt1].usItemClass == IC_LBEGEAR && totalSlots > 4){
			AssertMsg(0, String( "Item(%d) is LBE gear, but has more than 4 slots (this is not allowed).", Item[cnt1].uiIndex ));
		}
		//WarmSteel - If no xml entry was found, set the default for the item class. 
		if (totalSlots == -1 && gGameExternalOptions.fNewAttachmentSystem && Item[cnt1].usItemClass != IC_MONEY)
		{
			//search for the first empty spot in .
			UINT32 uiEmptySpot;
			for(uiEmptySpot = 0; uiEmptySpot < MAXATTACHMENTS && ItemSlotAssign[uiEmptySpot].itemIndex != 0; uiEmptySpot++){}

			if(gGameExternalOptions.fUseDefaultSlots){
				//Add slots based on class
				UINT16 ubClassIndex = Item[cnt1].ubClassIndex;
				switch(Item[cnt1].usItemClass){

				case IC_GUN:
					//Guns also have different types.
					switch(Weapon[ubClassIndex].ubWeaponType){

					case GUN_PISTOL:
						//add pistol default slots.
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultPistolSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex; //This may happen multiple times, but it doesn't matter.
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;

					case GUN_M_PISTOL:
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultMachinePistolSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;

					case GUN_SMG:
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultSubMachineGunSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;

					case GUN_RIFLE:
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultRifleSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;

					case GUN_SN_RIFLE:
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultSniperRifleSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;

					case GUN_AS_RIFLE:
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultAssaultRifleSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;

					case GUN_LMG:
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultLightMachineGunSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;

					case GUN_SHOTGUN:
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultShotgunSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;
					}
					break;

				case IC_LAUNCHER:
					// "&& !Item[cnt1].singleshotrocketlauncher" is not strictly needed, but in case anyone ever makes singleshots launchers.
					if(Item[cnt1].rocketlauncher && !Item[cnt1].singleshotrocketlauncher){
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultRocketLauncherSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
					} else if (Item[cnt1].grenadelauncher){
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultGrenadeLauncherSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
					} else {
						//if it's neither of the above, it's likely a mortar.
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultMortarSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
					}
					break;

				case IC_BOMB: //WarmSteel - Unable to properly identify which bombs can have detonators.
					break;

				case IC_ARMOUR:
					switch(Armour[ ubClassIndex ].ubArmourClass){

					case ARMOURCLASS_HELMET:
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultHelmetSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;
					case ARMOURCLASS_VEST:
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultVestSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;
					case ARMOURCLASS_LEGGINGS:
						for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
							if(AttachmentSlots[cnt3].fDefaultLeggingsSlot){
								ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
								ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
							}
						}
						break;
						
					}
					break;
				}
			}

			totalSlots = ItemSlotAssign[uiEmptySpot].itemSlots.size();

			//If we STILL didn't get any default slots, it means there are no default slots for this items class. Define the general ones.
			if(totalSlots < 1){
				//Assign default slots to weapons without XML
				for(UINT32 cnt3 = 1; cnt3 < MAXITEMS && AttachmentSlots[cnt3].uiSlotIndex != 0; cnt3++){
					if(AttachmentSlots[cnt3].fDefaultSlot){
						ItemSlotAssign[uiEmptySpot].itemIndex = Item[cnt1].uiIndex;
						ItemSlotAssign[uiEmptySpot].itemSlots.push_back(AttachmentSlots[cnt3].uiSlotIndex);
					}
				}
			}	
		}
	}
}

BOOLEAN ReadInItemSlotAssignStats(STR fileName)
{
	HWFILE		hFile;
	UINT32		uiBytesRead;
	UINT32		uiFSize;
	CHAR8 *		lpcBuffer;
	XML_Parser	parser = XML_ParserCreate(NULL);

	itemslotassignParseData pData;

	DebugMsg(TOPIC_JA2, DBG_LEVEL_3, "Loading ItemSlotAssign.xml" );

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


	XML_SetElementHandler(parser, itemslotassignStartElementHandle, itemslotassignEndElementHandle);
	XML_SetCharacterDataHandler(parser, itemslotassignCharacterDataHandle);


	memset(&pData,0,sizeof(pData));
	pData.maxArraySize = MAXATTACHMENTS;
	pData.curIndex = -1;

	XML_SetUserData(parser, &pData);


	if(!XML_Parse(parser, lpcBuffer, uiFSize, TRUE))
	{
		CHAR8 errorBuf[511];

		sprintf(errorBuf, "XML Parser Error in ItemSlotAssign.xml: %s at line %d", XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser));
		LiveMessage(errorBuf);

		MemFree(lpcBuffer);
		return FALSE;
	}

	MemFree(lpcBuffer);

	XML_ParserFree(parser);

	//WarmSteel - Add default slots for undefined items.
	//Sorry dunno where else to do this :( This can be moved to somewhere later in the init if you can find a better place.
	AddDefaultSlots();

	return( TRUE );
}

BOOLEAN WriteItemSlotAssignStats()
{
	HWFILE		hFile;

	//Debug code; make sure that what we got from the file is the same as what's there
	// Open a new file
	hFile = FileOpen( "TABLEDATA\\ItemSlotAssign out.xml", FILE_ACCESS_WRITE | FILE_CREATE_ALWAYS, FALSE );
	if ( !hFile )
		return( FALSE );

	{
		UINT32 cnt;

		FilePrintf(hFile,"<ITEMSLOTASSIGNLIST>\r\n");
		for(cnt = 0;cnt < MAXATTACHMENTS;cnt++)
		{
			FilePrintf(hFile,"\t<ITEMSLOTASSIGN>\r\n");

			FilePrintf(hFile,"\t\t<itemIndex>%d</itemIndex>\r\n",				ItemSlotAssign[cnt].itemIndex);
			for(UINT16 cnt2 = 0; cnt2 < ItemSlotAssign[cnt].itemSlots.size(); cnt2++){
				FilePrintf(hFile,"\t\t<itemSlotAssignIndex>%d</itemSlotAssignIndex>\r\n",		ItemSlotAssign[cnt].itemSlots[cnt2]);
			}

			FilePrintf(hFile,"\t</ITEMSLOTASSIGN>\r\n");
		}
		FilePrintf(hFile,"</ITEMSLOTASSIGNLIST>\r\n");
	}
	FileClose( hFile );

	return( TRUE );
}
