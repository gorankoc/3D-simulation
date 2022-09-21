#include "IEngine.h"

IEngine::IEngine()
{
	
	LoadString(0, IDS_SMANJITIVISINU, sAltitude, sizeof(sAltitude));

	_ID = 1;		
	_AG = 0.6;		
	_MaxVspeed = 0.3;											// maximalna brzina uspinjanja 0.3
	_AgilityVturn = 0.02;										// 0,002
	_MaxHSpeed = 0.2;											// maximalna horizontala turn brzina
	_AgilityHturn = 0.01; 										// Horizontal _AGility default //0,001
	_HturnSlowDown = 0.001;
	_MaxPitchAngle = 40;
	_MaxY = 310;
	//aturnAdd = 0;
	Init();		
}
void IEngine::Init(){

	_stop = false;
	_IsMaxY = false;

	if(!dbObjectVisible(_ID))
		dbShowObject(_ID);
		
	_speed = 0.8f;												// def 0.2f;

	Vspeed = 0;		
	Hspeed = 0;			
	rotY = 0;
	apitch = 0;								
	aturn = 0;						

	x = 300;
	y = 150;				
	z = 1400;
}
void IEngine::SetWireFrameOn()
{
	dbSetObjectWireframe(_ID, true);
}
void IEngine::SetWireFrameOff()
{
	dbSetObjectWireframe(_ID, false);
}
void IEngine::LoadXModel()
{
	dbLoadObject( PATH_AIRPLANEMODEL, _ID );				// avion model
	dbSetSphereMappingOn ( _ID, 111 );
	dbSetObjectSpecular  ( _ID,0 );	
	dbLoadImage( PATH_AIRPLANETEXTURE, 111);				// dbSetEffectOn( ie._ID, "E:\rainbow\\rainbow.fx", 1 );	//dbSetObjectTexture ( ie._ID, 3, 1 );//dbSetEffectOn ( ie._ID, "E:\\FX\\aniso\\aniso.fx", 1 );
	dbTextureObject ( this->_ID ,111 );						// dbSetObjectLight ( ie._ID , 1 );	//dbSetShadowShadingOn( ie._ID );//dbSetSphereMappingOn ( ie._ID, terrain._IDTERENTEXTUREIMGDETAIL);
}	
void IEngine::Move()
{				
	if(_stop == false)
	{
		this->HorizontalMovement();
		this->VerticalMovement();
		this->NewPos();
	}
}
void IEngine::Stop()
{
	this->_speed = 0;
	this->Vspeed = 0;
	this->Hspeed = 0;		
	_stop = true;
}
void IEngine::Start()
{
	_stop = false;
}
void IEngine::HorizontalMovement()
{
	//rotY = 0;													// rotY = ay + (TurnSpeed/_AG) * 15;	genericki
																// if( dbAbs (TurnSpeed) < 0.1 ) TurnSpeed = 0;		
	if( dbLeftKey() == 1)
	{
		Hspeed -= _AgilityHturn;
		if( Hspeed < -_MaxHSpeed )Hspeed =-_MaxHSpeed;
		if( dbRightKey() != 1 )	  aturn += Hspeed;				// H_AGile = 0.01;
		rotY = Hspeed * 200;
	}		
	if( dbRightKey() == 1 )
	{
		Hspeed += _AgilityHturn;
		if( Hspeed > _MaxHSpeed ) Hspeed = _MaxHSpeed;	
		if( dbLeftKey() != 1 )	  aturn += Hspeed;				// jer ako drzim desni i pritisnem slucajno lijevi kut za skretanje dobije polet Hspeed *2
																// ili kasnije ay = ay + ( TurnSpeed / _AG ); ako je *2
		rotY = Hspeed * 200;
	}	
	if( dbRightKey() == 0 && dbLeftKey() == 0 )
	{
		if( Hspeed < 0 )			
			Hspeed += _HturnSlowDown;							// /4 da 4x sporije se vraca na nultu horizontalnu brzinu
		else 
			Hspeed -= _HturnSlowDown; 
		if( Hspeed < 0.001 && Hspeed > -0.001 ) Hspeed = 0;		// uklanja glitch
			rotY = Hspeed * 200;
		if( rotY < 0.1 && rotY > -0.1 )	rotY = 0;
	}
	aturn += Hspeed;
	dbRotateObject		( _ID, 0, aturn, 0 );					// euler rotacija
	dbRollObjectRight	( _ID, rotY ); 
}
void IEngine::VerticalMovement()
{
	if( Vspeed > _MaxVspeed )		Vspeed =  _MaxVspeed;		// napraviti metodu smanjiZaVPostotak(%)
	if( Vspeed <-_MaxVspeed )		Vspeed = -_MaxVspeed;		// granice max i min brzina
	
	if( dbUpKey() == 1 )
	{			
		Vspeed += _AgilityVturn;						
		if (apitch >= _MaxPitchAngle )	
			apitch =  _MaxPitchAngle;	
		else
			apitch += 0.5; // povecaj pitch }
	}
	if( dbDownKey() == 1 ){
		Vspeed -= _AgilityVturn;			
		if (apitch <= -_MaxPitchAngle)	
			apitch =-_MaxPitchAngle;
		else	
			apitch -= 0.5;										// smanji pitch dbAbs(Vspeed) * 20;
	}
	if( dbDownKey() == 0 && dbUpKey() == 0){					// uvijek smanjuj V brzinu i nagib ako tipke gore i dole nisu pritisnute			
		if ( Vspeed > 0 )		Vspeed -= _AgilityVturn;		//_AgilityVturn
		if ( Vspeed < 0 )		Vspeed += _AgilityVturn;
	
		if ( dbAbs(Vspeed) < _AgilityVturn)	Vspeed = 0;			// drugim rijecima if( Vspeed < 0.1 && Vspeed > -0.1)Vspeed = 0;

		if ( apitch > 0 ) apitch -= 1;			
		if ( apitch < 0 ) apitch += 1;			
																// apitch = apitch * 0,999;
		if ( apitch < 0.2 && apitch > -0.2 ) apitch = 0;			
	}
	
	dbPitchObjectUp	( _ID, apitch);								// nos digni/spusti 
}
void IEngine::NewPos()
{
	x += dbCos ( aturn - 90 ) * _speed;							// x  = dbNewXValue ( x, ay, Speed );
	y += Vspeed;													
	z += dbSin ( aturn + 90 ) * _speed;							// z  = dbNewZValue ( z, ay, Speed );
														
	if ( y > _MaxY )
	{ 	
		_IsMaxY = true;
		//y = _MaxY;											// uvjet sprjecava da avion ne ide previsoko odnosno prenisko
	}
	else
	{
		_IsMaxY = false;
	}
	//if ( y < 5 )	y = 5;							
	dbPositionObject	( _ID, x, y, z );					
}	
bool IEngine::AltitudeTooHigh()
{
	return _altitudemaxed;
}
void IEngine::AltitudeCheck()
{
	if( y > _MaxY - 50 )
	{
		SetTransparencyOn( _MaxY - y );
		dbText( dbScreenWidth()/2 - 30, 80, sAltitude );

	}
	else
	{
		SetTransparencyOff();
	}
	if(	this->y > this->_MaxY)			
	{
		_altitudemaxed = true;
	}
	else
	{
		_altitudemaxed = false;
	}
}
void IEngine::SetTransparencyOn(float Percentage)
{
	dbSetAlphaMappingOn ( _ID, Percentage );				
}
void IEngine::SetTransparencyOff()
{
	dbSetAlphaMappingOn ( _ID, 100 );						
}
void IEngine::DebugInfo(){
	/*
	dbPrint("===== Roty:"); 
	dbPrint(dbStr(this->rotY));	
	dbPrint("===== aPitch:"); 
	dbPrint(dbStr(this->apitch));	
	dbPrint("===== Vspeed:"); 
	dbPrint(dbStr(Vspeed));		
	dbPrint("===== _MaxPitch:");	
	dbPrint(dbStr(_MaxPitchAngle));	
	dbPrint("====== aTurn:"); 
	dbPrint(dbStr(aturn));	
	dbPrint("===== Hspeed:"); 
	dbPrint(dbStr(Hspeed));	
	*/
	/*dbPrint("===== _YMAX:"); 
	dbPrint(dbStr(_MaxY));			*/
}