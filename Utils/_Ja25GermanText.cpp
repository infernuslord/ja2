// WANNE: Yes, this should be disabled, otherwise we get weird behavior when running the game with a VS 2005 build!
//#pragma setlocale("GERMAN")

#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_Ja25GermanText.h"
#else
	#include "Language Defines.h"
	#ifdef GERMAN
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_Ja25GermanText_public_symbol(void){;}

#ifdef GERMAN

// VERY TRUNCATED FILE COPIED FROM JA2.5 FOR ITS FEATURES FOR JA2 GOLD

//these strings match up with the defines in IMP Skill trait.cpp
STR16 gzIMPSkillTraitsText[]=
{
	L"Schlösser knacken",
	L"Nahkampf",
	L"Elektronik",
	L"Nachteinsatz",
	L"Werfen",
	L"Lehren",
	L"Schwere Waffen",
	L"Autom. Waffen",
	L"Schleichen",
	L"Beidhändig geschickt",
	L"Messer",
	L"Dach-Treffer Bonus",
	L"Getarnt",
	L"Kampfsport",

	L"Keine",
	L"B.S.E. - Spezialisierungen",
	L"(Experte)",
};

//added another set of skill texts for new major traits
STR16 gzIMPSkillTraitsTextNewMajor[]=
{
	L"MG-Schütze",	//LOOTF - Alle Namen sehr gewagt, aber wenigstens volldeutsch.
	L"Grenadier"	,
	L"Präzisionsschütze",
	L"Pfadfinder",
	L"Pistolenschütze",		//Option: Pistolenschütze
	L"Faustkämpfer",
	L"Gruppenführer",		//GrpFhr und ZgFhr sind scheiße, aber mir fällt ohne Dienstgrade nüscht ein
	L"Mechaniker",			//Option: Techniker
	L"Sanitäter",			//Option: Rettungsassistent

	L"Nichts",
	L"B.S.E. Hauptfertigkeiten",

	// second names
	L"MG-Veteran",		//Option "MG-Veteran"?
	L"Artillerist",
	L"Scharfschütze",
	L"Jäger",			//"Ranger" ist toll, aber nicht wirklich deutsch
	L"Revolverheld",
	L"Kampfsportler",		//Kung-Fu-Typ ohne Nennung von Kung-Fu oder Wu-Shu oder derart Zeug, PS: KampfSPORTLER ist kacke
	L"Zugführer",
	L"Ingenieur",
	L"Arzt",
};

//added another set of skill texts for new minor traits
STR16 gzIMPSkillTraitsTextNewMinor[]=
{
	L"Beidhänder",			// alt. "Beidhändig geschickt"
	L"Messerkämpfer",		// alt. "Hieb- und Stichwaffen"	//gesucht: Begriff für Nahkampfwaffenkämpfer
	L"Messerwerfer",		// alt. "Wurfwaffen"
	L"Nachtmensch",			// alt. "Nachteinsatz"
	L"Schleicher",			// alt. "Schleichen"
	L"Läufer",				// alt. "Athletisch"
	L"Kraftsportler",		// alt. "Bodybuilding"
	L"Sprengmeister",		// alt. "Kampfmittel"
	L"Ausbilder",			// alt. "Lehren"
	L"Aufklärer",			// alt. "Spähen"

	L"Keine",
	L"B.S.E. Nebenfertigkeiten",
};

//these texts are for help popup windows, describing trait properties
STR16 gzIMPMajorTraitsHelpTextsAutoWeapons[]=
{
	L"+%d%s Trefferchance mit Sturmgewehren\n",
	L"+%d%s Trefferchance mit Maschinenpistolen\n",
	L"+%d%s Trefferchance mit Maschinengewehren\n",
	L"-%d%s APs benötigt für MG-Feuerstöße (Burst/Auto) abzugeben\n",
	L"-%d%s APs benötigt um Maschinengewehre auszurichten\n",
	L"Trefferratenabzug bei Feuerstößen reduziert um %d%s\n",
	L"Reduzierte Chance bei Feuerstößen ungewollt mehr Schüsse abzugeben\n",


};
STR16 gzIMPMajorTraitsHelpTextsHeavyWeapons[]=
{
	L"-%d%s APs benötigt um Granatwerfer abzufeuern\n",
	L"-%d%s APs benötigt um Raketenwerfer abzufeuern\n",
	L"+%d%s Trefferchance mit Granatwerfern\n",
	L"+%d%s Trefferchance mit Raketenwerfern\n",
	L"-%d%s APs benötigt für den Abschuss von Mörsergranaten\n",
	L"Trefferchancenreduktion für Mörser gesenkt um %d%s\n",
	L"+%d%s Schaden an Panzern mit schweren Waffen, Granaten und Bomben\n",
	L"+%d%s schaden an allen anderen Zielen mit schweren Waffen\n",

};
STR16 gzIMPMajorTraitsHelpTextsSniper[]=
{
	L"+%d%s Trefferchance mit Gewehren\n",
	L"+%d%s Trefferchance mit Scharfschützengewehren\n",
	L"-%d%s effektive Reichweite zum Ziel mit allen Waffen\n",
	L"+%d%s Zielbonus pro Zielerfassungs-Klick (außer für Faustfeuerwaffen)\n",
	L"+%d%s Schaden pro Schuss",
	L" plus",
	L" für jeden Zielerfassungs-Klick",
	L" nach dem ersten",
	L" nach dem zweiten",
	L" nach dem dritten",
	L" nach dem vierten",
	L" nach dem fünften",
	L" nach dem sechsten",
	L" nach dem siebenten",
	L"-%d%s APs benötigt um ein Repetiergewehr erneut fertigzuladen.\n",
	L"Gibt einen weiteren Ziel-Klick für gewehrartige Waffen\n",
	L"Gibt weitere %d Ziel-Klicks für gewehrartige Waffen\n",

};
STR16 gzIMPMajorTraitsHelpTextsRanger[]=
{
	L"+%d%s Trefferchance mit Gewehren\n",
	L"+%d%s Trefferchance mit Schrotflinten\n",
	L"-%d%s APs gebraucht um Schrotflinten zu repetieren\n",
	L"+%d%s Marschgeschwindigkeit der Gruppe zwischen Sektoren zu Fuß\n",
	L"+%d%s Marschgeschwindigkeit der Gruppe zwischen Sektoren bei Benutzung von Fahrzeugen (außer dem Helikopter)\n",
	L"-%d%s weniger Energieverlust beim Reisen zwischen Sektoren\n",
	L"-%d%s Einfluss durch schlechtes Wetter\n",
	L"+%d%s Tarnungs-Effektivität\n",
	L"-%d%s Abnutzung von Gesichtstarnung durch Wasser oder Zeit\n",

};
STR16 gzIMPMajorTraitsHelpTextsGunslinger[]=
{
	L"-%d%s APs benötigt um mit Pistolen oder Revolvern zu schießen\n",
	L"+%d%s effektive Reichweite mit Pistolen und Revolvern\n",
	L"+%d%s Trefferchance mit  mit Pistolen und Revolvern\n",
	L"+%d%s Trefferchance mit vollautomatischen Pistolen",
	L" (nur bei Einzelfeuer)",
	L"+%d%s Zielbonus pro Klick mit Pistolen, vollautomatischen Pistolen und Revolvern\n",
	L"-%d%s APs benötigt um Pistolen und Revolver in Vorhalte zu bringe\n",
	L"-%d%s APs benötigt um Pistolen, vollautomatische Pistolen und Revolver nachzuladen\n",
	L"Gibt für Pistolen, vollautomatische Pistolen und Revolver einen weiteren Zielklick\n",
	L"%d weiteren Zielklick für Pistolen, vollautomatische Pistolen und Revolver\n",

};
STR16 gzIMPMajorTraitsHelpTextsMartialArts[]=
{
	L"-%d%s AP-Kosten für den Faustkampf (bloße Hände oder mit Schlagring)\n",
	L"+%d%s Trefferchance bei Nahkampfangriffen mit bloßen Händen\n",
	L"+%d%s Trefferchance bei Nahkampfangriffen mit dem Schlagring\n",
	L"+%d%s Schaden im Faustkampf (bloße Hände oder mit Schlagring)\n",
	L"+%d%s Ausdauerschaden im Faustkampf (bloße Hände oder mit Schlagring)\n",
	L"Ein im Nahkampf niedergestreckter Gegner braucht etwas länger um sich zu erholen\n",
	L"Ein im Nahkampf niedergestreckter Gegner braucht länger um sich zu erholen\n",
	L"Ein im Nahkampf niedergestreckter Gegner braucht deutlich länger um sich zu erholen\n",
	L"Ein im Nahkampf niedergestreckter Gegner braucht viel länger um sich zu erholen\n",
	L"Ein im Nahkampf niedergestreckter Gegner braucht sehr viel länger um sich zu erholen\n",
	L"Ein im Nahkampf niedergestreckter Gegner schläft wie ein Baby bevor er sich erholt\n",
	L"Ein im Nahkampf niedergestreckter Gegner steht vermutlich erstmal gar nicht mehr auf\n",
	L"Ein gezielter Schlag richtet +%d%s mehr Schaden an\n",
	L"Ein gezielter Tornadotritt richtet +%d%s mehr Schaden an\n",
	L"+%d%s Chance, Schlägen und Tritten auszuweichen\n",
	L"Dazu +%d%s Chance mit freien Händen",
	L" oder nur mit Schlagring",
	L" (+%d%s mit Schlagring)",
	L"+Dazu %d%s Chance, Schlägen und Tritten mit ausgerüstetem Schlagring auszuweichen\n",
	L"+%d%s Chance einem Angriff mit einer beliebigen Nahkampfwaffe auszuweichen\n",
	L"-%d%s APs benötigt um einen Gegner zu entwaffnen\n",
	L"-%d%s APs benötigt um die Körperhaltung zu ändern, sich umzudrehen, auf oder von Dächern zu klettern und Hindernisse zu überspringen\n",
	L"-%d%s APs benötigt um die Körperhaltung zu ändern (stehen, ducken, liegen)\n",
	L"-%d%s APs benötigt um sich umzudrehen\n",
	L"-%d%s APs benötigt um auf oder von Dächern zu klettern und Hindernisse zu überspringen\n",
	L"+%d%s Chance eine Tür erfolgreich einzutreten\n",
	L"Sie erhalten besondere Kung-Fu-Animationen für den Nahkampf\n",

};
STR16 gzIMPMajorTraitsHelpTextsSquadleader[]=
{
	L"+%d%s APs pro Runde für die umgebenden Söldner innerhalb des Einflussbereichs\n",
	L"+%d effektiven Erfahrungslevel für umgebende Söldner im Einflussbereich mit weniger Erfahrungsgrad als der %s\n",
	L"+%d auf den Erfahrungslevel beim Berechnen des Gruppeneffekts auf Unterdrückungsfeuer\n",
	L"+%d%s Resistenz gegen Unterdrückungsfeuer für jeden Söldner im Einflussbereich, auch den %s\n",
	L"+%d Moralgewinn für umgebende Söldner innerhalb des Einflussbereichs\n",
	L"-%d Moralverlust für umgebende Söldner innerhalb des Einflussbereichs\n",
	L"Der Einflussbereich hat einen Radius von %d Feldern",
	L" (%d Felder mit Kopfhörer-Funkgerät)",
	L"(Maximal auf einen Söldner wirkende Boni: %d )\n",
	L"+%d%s Resistenz gegen Angst für %s\n",
	L"Nachteil: %dx Moralverlust bei Tod des %ss für alle anderen Söldner\n",

};
STR16 gzIMPMajorTraitsHelpTextsTechnician[]=
{
	L"+%d%s schnellere Reparaturen\n",
	L"+%d%s mehr Erfolg beim Knacken normaler und elektronischer Schlösser\n",
	L"+%d%s mehr Erfolg beim Entschärfen elektronischer Fallen\n",
	L"+%d%s mehr Erfolg beim Anbringen besonderer Gegenstände und Verbinden von Gerätschaften\n",
	L"+%d%s mehr Erfolg beim Beheben von Waffenstörungen im Gefecht\n",
	L"Der Malus beim Reparieren elektronischer Gegenstände wird um %d%s gesenkt\n",
	L"Erhöhte Chance, Fallen und Minen zu entdecken (+%d zum Erkennungslevel)\n",
	L"+%d%s Trefferchance des Roboters, wenn vom %s gesteuert\n",
	L"Der %s kann den Roboter reparieren\n",
	L"%d%s Reduzierung des Geschwindigkeitsabzugs beim Reparieren des Roboters\n",
};
STR16 gzIMPMajorTraitsHelpTextsDoctor[]=
{
	L"Kann chirurgisch operieren (Benutzung eines Arztkoffers auf einen verletzten Söldner)\n",
	L"Die Operation stellt sofort %d%s der verlorenen Lebenspunkte wieder her.",
	L" (Dieser Vorgang verbraucht einen Großteil des Arztkoffers.)",
	L"Kann verlorene Attributpunkte (von kritischen Treffern) durch",
	L" eine Operation oder",
	L" den Auftrag 'Doktor' wiederherstellen.\n",
	L"+%d%s bessere Heilungsrate beim Einsatz am Patienten\n",
	L"+%d%s schnelleres Anlegen von Wundverbänden\n",
	L"+%d%s natürliche Regenerationsrate aller Söldner im selben Sektor",
	L" (maximal %d Instanzen dieses Bonus pro Sektor)",

};
STR16 gzIMPMajorTraitsHelpTextsNone[]=
{
	L"Keine Boni",
};

STR16 gzIMPMinorTraitsHelpTextsAmbidextrous[]=
{
	L"Die Ungenauigkeit beim Schießen mit zwei Waffen wird um %d%s reduziert\n",
	L"+%d%s schnelleres Nachladen mit Magazinen\n",
	L"+%d%s schnelleres Nachladen mit einzelnen Patronen\n",
	L"-%d%s APs benötigt um Gegenstände aufzuheben\n",
	L"-%d%s APs benötigt für die Handhabe des Rucksacks\n",
	L"-%d%s APs benötigt um mit Türen zu interagieren\n",
	L"-%d%s APs benötigt um Bomben und Minen zu legen oder zu entschärfen\n",
	L"-%d%s APs needed to attach items\n",
};
STR16 gzIMPMinorTraitsHelpTextsMelee[]=
{
	L"-%d%s APs benötigt für den Angriff mit Klingenwaffen\n",
	L"+%d%s Trefferchance mit Klingenwaffen\n",
	L"+%d%s Trefferchance mit Schlagwaffen\n",
	L"+%d%s Schaden mit Klingenwaffen\n",
	L"+%d%s Schaden mit Schlagwaffen\n",
	L"Ein gezielter Hieb mit einer Nahkampfwaffe richtet %d%s mehr Schaden an\n",
	L"+%d%s Chance Angriffen durch Klingenwaffen auszuweichen\n",
	L"Dazu +%d%s Chance Klingenwaffen auszuweichen wenn man selber eine in der Hand hat\n",
	L"+%d%s Chance Angriffen durch Schlagwaffen auszuweichen\n",
	L"Dazu +%d%s Chance Schlagwaffen auszuweichen wenn man eine Klingenwaffe führt\n",

};
STR16 gzIMPMinorTraitsHelpTextsThrowing[]=
{
	L"-%d%s Basis-APs benötigt für den Angriff mit Wurfwaffen\n",
	L"+%d%s maximale Reichweite beim Einsatz von Wurfwaffen\n",
	L"+%d%s Trefferchance mit Wurfwaffen\n",
	L"+%d%s Trefferchance mit Wurfwaffen für jeden Ziel-Klick\n",
	L"+%d%s Schaden geworfener Klingen\n",
	L"+%d%s Schaden geworfener Klingen für jeden Ziel-Klick\n",
	L"+%d%s Chance auf kritischen Treffer beim Angriff mit Wurfwaffen, falls das Ziel den Werfer nicht bemerkt hat\n",
	L"+%d Multiplikator für kritische Treffer durch Wurfwaffen\n",
	L"Gibt einen weiteren Zielklick beim Einsatz von Wurfwaffen\n",
	L"Gibt %d weitere Zielklicks beim Einsatz von Wurfwaffen\n",

};
STR16 gzIMPMinorTraitsHelpTextsNightOps[]=
{
	L"+%d zur effektiven Sichtweite im Dunkeln\n",
	L"+%d zum allgemeinen effektiven Hörweite\n",
	L"Dazu +%d zum effektive Hörweite in der Dunkelheit\n",
	L"+%d zum Unterbrechungs-Modifikator in der Dunkelheit\n",
	L"-%d weniger Schlafbedarf\n",

};
STR16 gzIMPMinorTraitsHelpTextsStealthy[]=
{
	L"-%d%s APs zum Schleichen nötig\n",
	L"+%d%s Chance beim Schleichen kein Geräusch zu erzeugen zu sein\n",
	L"+%d%s Chance, 'unsichtbar' zu sein wenn man sich nicht verrät (schleichen)\n",
	L"Der Abzug der berechneten Sichtdeckung beim Bewegen ist %d%s geringer\n",

};
STR16 gzIMPMinorTraitsHelpTextsAthletics[]=
{
	L"-%d%s APs benötigt für Bewegung (rennen, aufrecht oder geduckt gehen, gleiten, schwimmen, usw.)\n",
	L"-%d%s weniger Ausdauerverbrauch für für Bewegung, Dachklettern, Hindernisse Überwinden, usw.\n",
};
STR16 gzIMPMinorTraitsHelpTextsBodybuilding[]=
{
	L"Hat eine Schadensresistenz von %d%s\n",
	L"+%d%s effektive Stärke für das Berechnen der maximalen Traglast\n",
	L"%d%s weniger Energieverlust beim Erleiden von Schlägen und Tritten\n",
	L"Fällt bei Beintreffern weniger leicht um durch um %d%s erhöhte Schadenstoleranz\n",

};
STR16 gzIMPMinorTraitsHelpTextsDemolitions[]=
{
	L"-%d%s APs benötigt um Handgranaten und Ähnliches zu werfen\n",
	L"+%d%s mehr Reichweite beim Werfen von Handgranaten und Ähnlichem\n",
	L"+%d%s mehr Wurfgenauigkeit beim Einsatz von Handgranaten und Ähnlichem\n",
	L"Gelegte Bomben und Minen sind +%d%s effizienter\n",
	L"+%d%s mehr Erfolg beim Anbringen von Zündern an Sprengstoff\n",
	L"+%d%s mehr Erfolg beim Schärfen und Entschärfen von Bomben\n",
	L"Verringerte Chance, dass der Gegner eigene Bomben und Minen entdeckt (%d zum Bombenlevel)\n",
	L"Erhöhter Erfolg beim Aufbrechen einer Tür mit einer Durchbruchladung (Schaden multipliziert mit %d)\n",

};
STR16 gzIMPMinorTraitsHelpTextsTeaching[]=
{
	L"Bei der Ausbildung von Milizen +%d%s schneller\n",
	L"Bei der Ausbildung von Milizen +%d%s Bonus zur effektiven Führungsfähigkeit\n",
	L"Beim Ausbilden von Söldnern +%d%s schneller\n",
	L"Beim Ausbilden von Söldnern +d% zum effektiven Fähigkeitslevel des Ausbilders\n",
	L"Beim eigenständigen Lernen +%d%s schneller\n",

};
STR16 gzIMPMinorTraitsHelpTextsScouting[]=
{
	L"+%d zur effektiven Sichtweite mit Zielfernrohren an Waffen\n",
	L"+%d zur effektiven Sichtweite mit Doppelfernrohren und losen Zielfernrohren\n",
	L"-%d Tunnelblick mit Doppelfernrohren und losen Zielfernrohren\n",
	L"Auf der Weltkarte wird in angrenzenden Sektoren die genaue Feindstärke (Anzahl) bestimmt\n",
	L"Auf der Weltkarte wird in angrenzenden Sektoren die Präsenz von vorhandenem Feind enthüllt\n",
	L"Verhindert, dass der Feind die Gruppe in den Hinterhalt lockt\n",
	L"Verhindert, das Umzingeln der Gruppe durch Bloodcats\n",

};
STR16 gzIMPMinorTraitsHelpTextsNone[]=
{
	L"Keine Boni",
};

STR16 gzIMPOldSkillTraitsHelpTexts[]=
{
	L"+%d%s Bonus zum Schlösser Knacken\n",		// 0
	L"+%d%s Trefferchance im Faustkampf\n",
	L"+%d%s Schaden im Faustkampf\n",
	L"+%d%s Chance Schlägen auszuweichen\n",
	L"Bei der Reparatur und Bedienung von Elektrotechnik\n(Schlösser, Fallen, Fernzünder, Roboter...) kein Abzug\n",
	L"+%d zur effektiven Sichtweite im Dunkeln\n",
	L"+%d zur allgemeinen effektiven Hörweite\n",
	L"Dazu +%d zur effektiven Hörweite in der Dunkelheit\n",
	L"+%d zum Unterbrechungsmodifikator in der Dunkelheit\n",
	L"-%d weniger Schlafbedarf\n",
	L"+%d%s maximale Reichweite beim Werfen\n",	// 10
	L"+%d%s Trefferchance beim Werfen\n",
	L"+%d%s Chance auf sofortige Tötung mit Wurfmesser wenn unbemerkt\n",
	L"+%d%s Bonus zum Trainieren von Milizen und anderen Söldnern\n",
	L"+%d%s effektive Führungsfertigkeit beim Ausbilden von Milizen\n",
	L"+%d%s Trefferchance mit Raketen-/Granatwerfern und Mörsern\n",
	L"Trefferchancenabzug bei Dauerfeuer und Feuerstoß wird durch %d geteilt\n",
	L"Das Verschießen von zu viel Munition bei Dauerfeuer wird unwahrscheinlicher\n",
	L"+%d%s Chance sich leise zu bewegen\n",
	L"+%d%s stealth (unsichtbar sein, wenn man sich nicht verrät)\n",
	L"Beim Schießen mit zwei Waffen mit jeder so präzise wie mit nur einer\n",	// 20
	L"+%d%s Trefferchance mit Stichwaffen\n",
	L"+%d%s Chance, Stichwaffen auszuweichen, wenn man selber eine führt\n",
	L"+%d%s Chance, Stichwaffen auszuweichen, wenn man etwas anderes in der Hand hat\n",
	L"+%d%s Chance Schlägen auszuweichen, wenn man eine Stichwaffe hält\n",
	L"-%d%s effektive Reichweite zum Ziel mit allen Waffen\n",
	L"+%d%s Bonus zum Zielen pro Mausklick\n",
	L"Immer vollständig getarnt sein\n",
	L"+%d%s Trefferchance im Faustkampf\n",
	L"+%d%s Schaden im Faustkampf\n",
	L"+%d%s Chance, Schläge mit leeren Händen zu blocken\n",	// 30
	L"+%d%s Chance, Schläge mit etwas in der Hand zu blocken\n",
	L"+%d%s Chance, Stichwaffenangriffen auszuweichen\n",
	L"Kann angeschlagenen Gegnern einen Tornadotritt verpassen, der doppelten Schaden anrichtet\n",
	L"Sie erhalten besondere Animationen für den Faustkampf (etwas fernöstlicher)\n",
	L"Keine Boni",
};

STR16 gzIMPNewCharacterTraitsHelpTexts[]=
{
	L"V: Keine Vorteile.\nN: Keine Nachteile.",
	L"V: Hat eine erhöhte Leistung im Verbund mit anderen Söldnern.\nN: Erhält keinen Moralzuwachs, wenn niemand in der Nähe ist.",
	L"V: Hat eine erhöhte Leistung, wenn niemand in der Nähe ist.\nN: Erhält keinen Moralzuwachs im Verbund mit anderen Söldnern.",
	L"V: Seine Moral sinkt etwas langsamer und steigt schneller.\nN: Hat weniger Chance, Fallen und Minen zu entdecken.",
	L"V: Erhält Boni beim Ausbilden von Miliz und kann besser mit Menschen reden.\nN: Erhält keinen Moralzuwachs für Aktionen anderer Söldner.",
	L"V: Lernt etwas schneller in Schulung durch sich selbst oder andere.\nN: Hat weniger Unterdrückungs- und Angstresistenz.",
	L"V: Verbraucht etwas weniger Energie, außer bei Aufgaben in Medizin, Technik oder anspruchsvollen Ausbildung.\nN: Weisheit, Führungskraft, Sprengstoff-, Mechanik- und Medizinkenntnisse entwickeln sich bei ihm langsamer.",
	L"V: Hat eine leicht erhöhte Trefferchance bei Feuerstößen und richtet etwas mehr Schaden im Nahkampf an.\n    Erhält ein wenig mehr Moralzuwachs beim Töten.\nN: Ist schlechter bei Aufgaben, die Geduld erfordern, wie Reparatur, Schlossknacken, Fallen Entschärfen, Patientenbetreuung und Ausbildung von Miliz.",
	L"V: Erhält Boni für Aufgaben mit Geduldsanspruch wie Reparatur, Schlossknacken, Fallen Entschärfen, Patientenbetreuung und Ausbildung von Miliz.\nN: Erhält weniger oft Unterbrechungen im Kampf.",
	L"V: Erhöhte Resistenz gegenüber Unterdrückungsfeuer und Angst.\n    Verliert weniger Moral beim Erleiden von Schaden oder dem Tod von Kameraden.\nN: Wird leichter getroffen, und kann seltener Feindfeuer durch schnelle Bewegung ausweichen.",
	L"V: Erhält Moralzuwachs für Tätigkeiten außerhalb des Kämpfens (außer der Ausbildung von Milizkräften).\nN: Erhält keinerlei Moral beim Töten.",
	L"V: Hat eine höhere Chance, Statusschäden anzurichten und kann besonders fiese Wunden austeilen.\n   Erhält mehr Moral für erfolgreiche Statusschäden.\nN: Kann schlechter mit Leuten reden und seine Moral sinkt schneller, wenn er nicht kämpft.",
	L"V: Hat eine erhöhte Leistung wenn Söldner des anderen Geschlechts in der Nähe sind.\nN: Die Moral anderer naher Söldner des gleichen Geschlechts steigt langsamer.",

};

STR16 gzIMPDisabilitiesHelpTexts[]=
{
	L"Keine Auswirkungen.",
	L"Hat Atemnot und allgemein schlechtere Leistung in tropischen und Wüstensektoren.",
	L"Kann Panikattacken erleiden, wenn in gewissen Situationen auf sich gestellt.",
	L"Zeigt geringere Leistung unter Tage (in Höhlen und Kellern).",
	L"Kann beim Versuch zu schwimmen leicht ertrinken.",
	L"Erträgt den Anblick großer Insekten nicht und\nzeigt verringerte Leistung in tropischen Sektoren.",
	L"Vergisst manchmal seine Befehle und verliert dadurch im Kampf einen Teil seiner APs.",
	L"Dreht im Umgang mit Waffen manchmal durch und gibt Dauerfeuer.\nIst ihm das mit seiner Waffe nicht möglich, kann das zu Moralabzügen führen.",
};



STR16 gzIMPProfileCostText[]=
{
	L"Ein Profil kostet %d$. Genehmigen Sie die Zahlung? ",
};

STR16 zGioNewTraitsImpossibleText[]=
{
	L"Sie können das neue Fertigkeitensystem nicht ohne aktiviertem PROFEX-Utility benutzen. Suchen Sie in Ihrer ja2_options.ini den Eintrag: READ_PROFILE_DATA_FROM_XML.",
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Sie haben sich für den Ironman-Modus entschieden. Mit dieser Einstellung können Sie das Spiel nicht speichern, wenn Feinde im Sektor sind. Sind Sie sicher, dass Sie im Ironman-Modus spielen wollen?",
};

STR16 gzDisplayCoverText[]=
{
	L"Deckung: %d/100 %s, Helligkeit: %d/100",
	L"Waffen-Reichweite: %d/%d Felder, Trefferwahrscheinlichkeit: %d/100",
	L"Waffen-Reichweite: %d/%d Felder, Lauf-Genauigkeit: %d/100",
	L"Deckungsanzeige ausschalten",
	L"Zeige Ansicht für Söldner",
	L"Zeige Gefahrenbereich für Söldner",
	L"Wald", // wanted to use jungle , but wood is shorter in german too (dschungel vs wald)
	L"Stadt",
	L"Wüste",
	L"Schnee", // NOT USED!!!
	L"Wald und Wüste",
	L"" // yes empty for now
};


#endif