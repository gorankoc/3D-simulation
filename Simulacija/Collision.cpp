#include "Collision.h"

Collision::Collision()
{
	_SCollision = 0;
	_SCollisionCPbool = false;
}
void Collision::SetUpTerrain(Terrain* terrain)
{
	_terrain = terrain;
}
void Collision::SetUpAirplane(IEngine* ie)
{
	_ie = ie;
}
void Collision::Start()
{
	SC_Start();	
	
	SC_SetupObject		 ( this->_ie->_ID, 1, 0);
	SC_SetupComplexObject( this->_terrain->_ID, 1, 2);	// poly 
}	
bool Collision::AirplaneTerrainCollide()
{
	SC_UpdateObject(_ie->_ID);
	_SCollision = SC_ObjectCollision( _terrain->_ID, _ie->_ID );

	if( _SCollision != 0 )
		return true;
	else
		return false;
}
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
void Collision::DebugInfo()
{
	dbPrint("iSphere");
}