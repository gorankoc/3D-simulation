#include "DarkGDK.h"

#if !defined TERRAIN_H
	#include "Terrain.h"
#endif

#if !defined IENGINE_H
	#include "IEngine.h"
#endif

#if !defined SPARKY_H
	#include "Sparky.h"
#endif

class Collision
{	
public:
IEngine* _ie;
Terrain* _terrain; 
float _SCollision;
bool  _SCollisionCPbool;

	Collision();
	void SetUpTerrain(Terrain* terrain);
	void SetUpAirplane(IEngine* ie);
	/**
	* Poziva se jednom u mainu, na startu programa
	* Govori sparky dll-u da ce u igri biti 2 objekta:
	* - avion: na njega je primjenjena polygon kolizija, sparky provjeravat ce svaki poligon u objektu
	* - za teren koristi SC_SetupComplexObject cija su performanse razlicite od SC_SetupObject ako je u pitanju više poligona
	*/
	void Start();
	/**
	* Provjerava sudar aviona sa terenom, ovu funkciju koristio sam u mainu za izcrtavanje iskri kao 
	* upozorenje, ali ne i konacni sudar. Konacni sudar podrazumijeva kada centralna toèka aviona uðe
	* ispod terena (tocnije ispod trenutnog poligona terena). 
	*/
	bool AirplaneTerrainCollide();
/*
	bool IsAirplaneUnderTerrain(){
		if( this->_SCollision != 0 ){	
			// drugio dio uvjeta popravlja bug kada avion ude ispod terena, jer prestaje kolizija 
			// ie.SetTransparencyOn();
			return true;
		}
		else
		{
			return false;
		}
	}*/
	void DebugInfo();
	/*
	destrukt SC_removeObject 
	*/
};