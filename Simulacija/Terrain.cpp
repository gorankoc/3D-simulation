#include "Terrain.h"

Terrain::Terrain(){
	_ID = 10;		
	LoadDefaults();

}
/**
* Postavljanje terena:
* Teksture
*/
void Terrain::Init()
{
	dbLoadImage ( PATH_MAPTEXTURE, _IDIDTERENTEXTUREIMG );	// diffuse texture
	dbLoadImage ( PATH_MAPDETAIL,  200 );					// detail texture		
	dbSetupTerrain        ( );								// set up terrain library
	dbMakeObjectTerrain   ( _ID );							// make a new terrain
	dbSetTerrainHeightMap ( _ID, PATH_MAP );				// set the terrain height map
	dbSetTerrainScale     ( _ID, 7, 2, 8 );					// set the scale
	dbSetTerrainSplit     ( _ID, 16 );						// set the split value
	dbSetTerrainTiling    ( _ID, 4 );						// set the detail tiling
	dbSetTerrainLight     ( _ID, 1.0f, -0.25f, 0.0f, 1, 1, 0.78f, 0.5f );	// set the light
	dbSetTerrainTexture   ( _ID, _IDIDTERENTEXTUREIMG, _IDTERENTEXTUREIMGDETAIL );								// set the textures
	dbBuildTerrain        ( _ID );		
	//planeW = 5000;
	//planeH = 1000;
}
Terrain::Terrain(int ID): _ID(ID){}

void Terrain::LoadDefaults(){
	_IDIDTERENTEXTUREIMG = 100;
	_IDTERENTEXTUREIMGDETAIL = 200;
}	
void Terrain::SetWireFrameOn()
{
	dbSetObjectWireframe(_ID, true);
}
void Terrain::SetWireFrameOff()
{
	dbSetObjectWireframe(_ID, false);
}
void Terrain::DebugInfo(){
	//dbPrint("TerrainXZ");
	dbPrint(dbStr(dbGetTerrainXSize(_ID)));
	dbPrint(dbStr(dbGetTerrainZSize(_ID)));
}