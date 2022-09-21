#include "DarkGDK.h"

#if !defined IENGINE_H
	#include "IEngine.h"
#endif

#if !defined TERRAIN_H
	#include "Terrain.h"
#endif

#if !defined CAMERA_H
#define CAMERA_H "Camera.h"

class Camera
{
float camSpeed;		
float camDist;				
float camx;						
float camy;
float camz;
int	  camCollision;
float groundCamHeight;
float groundObjectHeight;
float camYDecrement;

public:

/** * Konstruktor postavlja inicijalnu poziciju kamere, i raspon (kut gledanja) */
	Camera();
	void InitPosition();
/**
* Funkcija se poziva u main-u, koji objekt æe kamera pratit.
* Da kamera ne bi ulazila u teren, pratit æe reljef terena.
* @param IEngine* objekt kojeg æe kamera pratit, pristupa trenutnim ie kordinatama u XZ.
* @param Terrain* uzima ID terena
*/
	void FollowObject(IEngine* ie, Terrain* terrain);
/*! \brief Brief description.
 *         Brief description continued.
 *
 *  Detailed description starts here.
 */
	void DebugInfo();
};
#endif