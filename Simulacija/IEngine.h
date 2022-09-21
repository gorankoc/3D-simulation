#include "DarkGDK.h"
#include "Path.h"
#include "Resource.h"

#define IENGINE_H "IEngine.h"
/**
* IEngine je avion.
* Zove se Iengine jer sam u jednom trenu htio da to bude interface, pa je tako ostalo.
* Namjeravam to promjenit. 
*/
class IEngine{
public:
	//Point p;----------------------------------------------------------------------
	int _ID;
	float _speed;													// d ili radius 
	float _MaxHSpeed;												// max H turn speed
	float _MaxVspeed;
	float _AG;														// _AGILNOST moze biti i varijabilna <0.3,10> 
	float _AgilityHturn;
	float _AgilityVturn;
	float _MaxPitchAngle;
	float _HturnSlowDown;
	float _MaxY;
	bool _IsMaxY;
	float Vspeed;													// KOLIKO BRZO CE SE OKRENUT DESNO I LIJEVO	DIGNUT - OVISI O _AGILITIJU += _AGILITYž
	float Hspeed;
	float rotY;	
	float apitch;													// ax nos gore dole
	float aturn;													// ay lijevo desno
	//float aturnAdd;												// dodavanje kutu y da se vidi bocna strana kod skretanja, nije previse bitno
	//float aroll;													// az kut od aviona
	float x,y,z;													// xyz pozicija aviona
	bool _stop;
	bool _altitudemaxed;
	TCHAR sAltitude[64]; 

	IEngine();
	/**
	* - Pocetne vrijednosti aviona
	* - Brzina aviona:			_speed
	* - Brzina horizontalne:	Hspeed
	* - Brzina vertikale:		Vspeed
	* - Kut pitch-a:			apitch
	* - Kut turn-a:				aturn
	* - rotY:					rotY
	*/ 
	void Init();
	/**
	*	Postavlja avion u wireframe mode
	*/
	void SetWireFrameOn();
	void SetWireFrameOff();
	/**
	* Ucitava .x model i teksturu, postavlja sphere mapping ( tekstura na .x modelu ce stvarati efekt odsjaja svog okolisa ),
	* postavlja odsjaj ( specular )  objekta na oklis
	*/
	void LoadXModel();	
	/**
	* Glavna funkcija za kretnju aviona
	*/
	void Move();
	/**
	* Zaustavlja avion 
	*/
	void Stop();
	void Start();
	/**
	* 
	*/
	void HorizontalMovement();
	void VerticalMovement();
	void NewPos();
	/**
	*	Ideja je da avion ne smije se popet pre visoko jer je game over, tako osiguravam da se ne ide preko granica terena
	*/
	bool AltitudeTooHigh();
	void AltitudeCheck();
	/**
	* Ako avion ipak ode pre visoko ima upozorenje, pomalo postaje proziran cca 1% pa do 50% prozirnost
	*/
	void SetTransparencyOn(float Percentage);
	/**
	* Iskljuèuje transparentnost ( alpha mapping 100 );
	*/
	void SetTransparencyOff();
	void DebugInfo();
};