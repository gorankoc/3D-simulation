#include "DarkGDK.h"
#include "resource.h"
#include "globstruct.h"
#include <stdio.h>
#include <stdlib.h>

#if !defined TERRAIN_H
	#include "Terrain.h"
#endif
#if !defined TIMER_H
	#include "Timer.h"
#endif
#if !defined IENGINE_H
	#include "IEngine.h"
#endif
#if !defined PARTICLES_H
	#include "Particles.h"
#endif
#if !defined IENGINE_H
	#include "IEngine.h"
#endif
#if !defined CAMERA_H
	#include "Camera.h"
#endif
#if !defined CHECKPOINT_H
	#include "Checkpoint.h"
#endif

#define GAME_RESET 13276

class Game
{	
	Camera* _cam;
	IEngine* _ie;
	Particles* _particles;
	Terrain* _terrain;
	MyTimer* _tmr;
	CheckPoint* _chkpoint;
	
	bool _Exit;
	bool _GameOver;
	bool _Restart;	
	bool _RestartAndWait;
	
	//HWND _hwMain;
public:
	/**
	* 	_Exit = false;
		_Restart = false;
		Postavlja se timer igre.
	*/
	Game();
	/**
	* Start igre, inicijalna pozicija kamere, aviona.
	*/
	void Start();
	void End();
	/**
	* Restart igre: poziva se kada se zavrsava sa izradom check pointova ( tj. zapisuje u check point.txt ) ili restart igre
	*/
	void Restart();
	/** 
	* Provjerava da li je avion ispod terena, da li je game over.
	*/
	bool AirplaneUnderTerrainCheck();
	/**
	* Ispisuje koliko je sakupljeno check pointova
	*/
	void GameStatus( );
	void Exit(bool Exit);
	/** 
	* Property Exit
	*/
	bool Exit() const;
	/**
	* Kada je game over i igrac ne zeli ponovo resetirat igru
	*/
	int CheckTimeOut();
	void RestartAndWait();
	void SetTerrainPtr( Terrain* terrain );
	void SetAirplanePtr( IEngine* ie );
	void SetParticlesPtr( Particles* particles );
	void SetCameraPtr( Camera* camera );
	void SetTimerPtr( MyTimer* tmr );
	void Game::SetCheckPointPtr( CheckPoint* checkpoint);
	/** 
	* Property GameOver
	*/
	bool GameOver() const;
};