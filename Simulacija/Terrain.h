#include "DarkGDK.h"
#include "Path.h"

#define TERRAIN_H "Terrain.h"

class Terrain{
public:	
	int _ID;
	int _IDIDTERENTEXTUREIMG, _IDTERENTEXTUREIMGDETAIL;
	int planeW, planeH;

	Terrain();

	Terrain(int);
	/**
	* Postavljanje terena:
	* 
	* Teksture
	*/
	void Init();
	void LoadDefaults();
	void SetWireFrameOn();
	void SetWireFrameOff();
	void DebugInfo();
};