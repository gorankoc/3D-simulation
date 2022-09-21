#include "Camera.h"

Camera::Camera()
{
	groundCamHeight = 0;
	groundObjectHeight = 0;
	camSpeed = 0;		
	camDist = - 40;	

	InitPosition();

	camCollision = 0;
	camYDecrement = -0.3;
	dbSetCameraRange ( 0.5f, 20000 );	
}
void Camera::InitPosition(){
	camx = 0;						
	camy = 140;
	camz = 0;
}
void Camera::FollowObject(IEngine* ie, Terrain* terrain)
{	
	groundCamHeight		= dbGetTerrainGroundHeight ( terrain->_ID, camx, camz );
	groundObjectHeight	= dbGetTerrainGroundHeight ( ie->_ID, ie->x, ie->z );
	
	if ( camy < groundCamHeight + 11 )
		 camCollision = 1;
	else
		camCollision = 0;
	
	if ( camy < ie->y ) 
		camCollision = 0;

	if ( camCollision == 1 )
		camy = groundCamHeight + 10;
	
	if ( camCollision == 0 )
	{
		camy += camYDecrement;				// polako se spustaj na visinu aviona//camYDecrement /= 0.9999;
		if( camy <= ie->y )  camy = ie->y;
	}	

	camx = ie->x + dbSin( ie->aturn ) * camDist;	
	camz = ie->z + dbCos( ie->aturn ) * camDist;

	dbPositionCamera( camx, camy, camz );
	dbPointCamera	( ie->x, ie->y, ie->z );// dbPositionCamera ( dbCameraPositionX ( ), fHeight + 3.0f, dbCameraPositionZ ( ) );
}
void Camera::DebugInfo() {
	dbPrint("::::::::::::::Camera"); 	
	dbPrint("__Collision__"); 
	dbPrint("groundCamHgt:"); 
	dbPrint(dbStr(groundCamHeight));
	dbPrint("camCollision:"); 
	dbPrint(dbStr(camCollision));
	dbPrint("===== CamY-Y:"); 
	dbPrint(dbStr(camy));
}