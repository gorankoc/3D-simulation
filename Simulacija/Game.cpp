#include "Game.h"
#include "Resource.h"

Game::Game()
{
	_Exit = false;
	_Restart = false;
	_RestartAndWait = false;
}
void Game::Start()
{
	_tmr->Restart();
	_cam->InitPosition();

	_ie->Init();
	_ie->Start();
	_ie->Move();

	_GameOver = false;
	_RestartAndWait = false;
}
void Game::End()
{
	_GameOver = true;
}
void Game::Restart()
{
	Start();
}
bool Game::AirplaneUnderTerrainCheck()
{
	if( dbGetTerrainGroundHeight( _terrain->_ID, _ie->x, _ie->z) > _ie->y )		
	{	
		_GameOver = true;
		return true;					
	}
	else
	{
		_GameOver = false;
		return false;
	}
}
void Game::GameStatus( )
{
	TCHAR s[64]; 
	LoadString( 0, IDS_SAKUPLJENO, s, sizeof(s) );

	char buff[30];
	sprintf( buff,  s, _chkpoint->SakupljenoCP() );

	dbText( 5 , 5, buff);				
	
	if ( _RestartAndWait == false ) 
		 _tmr->Elapsed();
}
int Game::CheckTimeOut()
{
	TCHAR s[64];
	char buff[30];
	
	if( _tmr->TimeOut() )
	{
		_chkpoint->HideAll();
		LoadString(0, IDS_KRAJIGRESAKUPLJENO, s, sizeof(s));
		sprintf( buff,  s, _chkpoint->SakupljenoCP() );
		dbText(300, 300, buff);
		//_terrain->Fade(50);//_tmr->RunningMs());
		return 1;
	}
	return 0;
}
void Game::Exit(bool Exit)
{
	_Exit = Exit; 
}
bool Game::Exit() const
{
	return _Exit;
}
void Game::RestartAndWait()
{	
	Start();
	_ie->Stop();
	_RestartAndWait = true;
} 
void Game::SetTerrainPtr( Terrain* terrain )
{
	_terrain = terrain;
}
void Game::SetAirplanePtr( IEngine* ie )
{
	_ie = ie;
}
void Game::SetParticlesPtr( Particles* particles )
{
	_particles = particles;
}	
void Game::SetCameraPtr( Camera* camera )
{
	_cam = camera;
}
void Game::SetCheckPointPtr( CheckPoint* checkpoint)
{
	_chkpoint = checkpoint;
}
void Game::SetTimerPtr( MyTimer* tmr )
{
	_tmr = tmr;
}
bool Game::GameOver() const
{
	return _GameOver;
}