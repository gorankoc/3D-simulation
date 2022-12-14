#include "Main.h"

	Game game;
	Point3D p;	
	CheckPoint cp;
	Terrain terrain;
	IEngine ie;
	Camera camera;	
	MyTimer* timer;

	float  f;
	bool   SecondPassed;
	bool   WriteCP;
	double time_elapsed;
	double before;
	double after;
	bool   aboutbox;

	bool _MenuItemTicked;
	bool _WireFrameChecked;
	bool _DialogChecked;
	char _DialogText[256];
	int  _DialogNumber;

	HMENU _MyMenu;
	WNDPROC _lpWndProc;		
	LRESULT CALLBACK MainProc(HWND, UINT, WPARAM, LPARAM);
	
	void CheckPointStart();
	void CheckPointEnd();
	void DisplayRestartMessageBox();
	void MainDebugInfo();
	void AboutBox();
	void AfterRestartDialog();

void DarkGDK ( void )
{
	dbSyncOn   ( );
	dbSyncRate ( 60 );	
	dbBackdropOn();
	dbColorBackdrop( dbRGB( 0, 0, 0) );
	dbSetShadowShadingOn ( 1 );		

	timer = new MyTimer(60);

	_MenuItemTicked = true;
	_DialogChecked = false;
	_DialogText[256];
	_DialogNumber = 0;
		
	_MyMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU1));		
	 SetMenu( g_pGlob->hWnd, _MyMenu );
	_lpWndProc = (WNDPROC)SetWindowLong(g_pGlob->hWnd, GWL_WNDPROC, (LONG)MainProc );	

	SetTimer( g_pGlob->hWnd, IDT_SAT, 100, NULL );	
	
	Particles particles;
	particles.Init();
	terrain.Init();
	
	ie.LoadXModel();
	ie.Init();

	game.SetAirplanePtr(&ie);
	game.SetParticlesPtr(&particles);
	game.SetTerrainPtr(&terrain);		
	game.SetCameraPtr(&camera);
	game.SetTimerPtr(timer);
	game.SetCheckPointPtr(&cp);

	Collision collision;
	collision.SetUpAirplane(&ie);
	collision.SetUpTerrain(&terrain);
	collision.Start();

	timer->Restart();

	game.Start();
	cp.read();
	cp.SetupCollision();

	while ( LoopGDK () || game.Exit() ) 
	{		
		MainDebugInfo();	
		
		if( game.GameOver() == false )			
		{
			if( cp.IsWriteMode() )
			{
				if( cp.Delayed_Space_Key(1000) )
				{
					p.x = ie.x;
					p.y = ie.y;
					p.z = ie.z;
    				cp.AddPoint( p );
				}
			}
			else
			{
				if (!game.CheckTimeOut())
				{
					game.AirplaneUnderTerrainCheck();
					
					ie.AltitudeCheck();

					if( ie.AltitudeTooHigh() == true )
						game.End();
					
					cp.SphereCollisionUpdate( ie._ID );
				}
				
			}

			ie.Move();

			camera.FollowObject( &ie, &terrain );

			if( collision.AirplaneTerrainCollide() == true) 
				particles.DrawCollision( &ie);
			else
				particles.StopTerrainParticles();

			game.GameStatus( );

		}
		else
		{	
			SendMessage(g_pGlob->hWnd, _RESTART, 0, 0);
		}

		if ( game.Exit() ) return;

		dbUpdateTerrain( );
		
		dbSync ( );
	}

 	return;
}
LRESULT CALLBACK MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
	switch (uMsg){ 
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{			
				case ID_IGRA_EXIT:
					game.Exit(true);
					break;		

				case ID_GRAFIKA_WIREFRAMEMODE:
					_WireFrameChecked = !_WireFrameChecked;
					if(_WireFrameChecked)
					{
						CheckMenuItem(_MyMenu, ID_GRAFIKA_WIREFRAMEMODE, MF_CHECKED);
						terrain.SetWireFrameOn();
						ie.SetWireFrameOn();
					}
					else
					{
						CheckMenuItem(_MyMenu, ID_GRAFIKA_WIREFRAMEMODE, MF_UNCHECKED);
						terrain.SetWireFrameOff();
						ie.SetWireFrameOff();
					}
					break;	

				case ID_ABOUT:
					AboutBox();
					break;			

				case ID_CHECKPOINT_START:
					CheckPointStart();
					break;

				case ID_CHECKPOINT_END:
					CheckPointEnd();
					break;

				case ID_IGRA_RESTART:
					DisplayRestartMessageBox();						
					break;	

				default:
					//timer->RunPauseTimer(); proba
					break;
			}		
			break;	

		case _RESTART: 
				DisplayRestartMessageBox();
				break;

		case WM_TIMER:          
			switch(LOWORD(wParam))
            {
				case IDT_SAT:    
					if ( aboutbox == false) 
						timer->Run();
				    break;
			}
		default: 
			//timer->Reset2ndTimer(); proba
            break;  
    } 
    return CallWindowProc(_lpWndProc, hwnd, uMsg, wParam, lParam); 
}

void CheckPointStart()
{
	TCHAR s[64]; 
	LoadString(0, IDS_CHKPOINTDODAJ, s, sizeof(s));

	

	int msgboxIDChkP = MessageBox( NULL, s, "Start", MB_ICONINFORMATION | MB_OK | MB_APPLMODAL );

	cp.SetWriteModeOn(); 

	EnableMenuItem (_MyMenu, ID_CHECKPOINT_END, MF_ENABLED );
	EnableMenuItem (_MyMenu, ID_CHECKPOINT_START, MF_DISABLED | MF_GRAYED);
	EnableMenuItem (_MyMenu, ID_IGRA_EXIT,		  MF_DISABLED | MF_GRAYED);
	EnableMenuItem (_MyMenu, ID_IGRA_RESTART,	  MF_DISABLED | MF_GRAYED);
}
void CheckPointEnd()
{
	EnableMenuItem (_MyMenu, ID_CHECKPOINT_END, MF_DISABLED | MF_GRAYED);
	EnableMenuItem (_MyMenu, ID_CHECKPOINT_START, MF_ENABLED );
	EnableMenuItem (_MyMenu, ID_IGRA_EXIT,		  MF_ENABLED );
	EnableMenuItem (_MyMenu, ID_IGRA_RESTART,	  MF_ENABLED );

	cp.write();
	
	TCHAR s[64]; 
	LoadString(0, IDS_CHKPOINTPOSTAVLJENI, s, sizeof(s));

	TCHAR resetCaption[64]; 
	LoadString(0, IDS_CHKPOINTRESETNASLOV, resetCaption, sizeof(resetCaption));

	int msgboxID = MessageBox( NULL, s, resetCaption, MB_ICONINFORMATION | MB_OK | MB_APPLMODAL );

	if( msgboxID == IDOK )
	{
		game.Restart();
		cp.InitWriteToRead();
	}
}
void DisplayRestartMessageBox()
{
	TCHAR s[64]; 
	TCHAR krajCaption[64]; 

	LoadString(0, IDS_KRAJIGRENASLOV, krajCaption, sizeof(krajCaption));
	
	if ( !game.CheckTimeOut() ) 
	{

		LoadString(0, IDS_KRAJIGRE, s, sizeof(s));
		int msgboxID = MessageBox( NULL, s, krajCaption, MB_ICONINFORMATION | MB_YESNO );

		if( msgboxID == IDYES)
		{
			AfterRestartDialog();	
		}

		if( msgboxID == IDNO)
		{
			game.RestartAndWait();
			timer->Stop();
		}
	}
	else
	{
		LoadString(0, IDS_KRAJIGREVRIJEMEISTEKLO, s, sizeof(s));
		int msgboxID = MessageBox( NULL, s, krajCaption, MB_ICONINFORMATION | MB_OK );

		if( msgboxID == IDOK)
		{
			AfterRestartDialog();	
		}
	}
}
void AfterRestartDialog()
{
	game.Restart();
	cp.Restart();		
}

void MainDebugInfo()
{
	dbSetCursor( 0, 0 );	
}
void AboutBox(){

	aboutbox = true;

	TCHAR s[64]; 
	LoadString(0, IDS_INFODIALOG, s, sizeof(s));

	TCHAR aboutboxcaption[64]; 
	LoadString(0, IDS_INFONASLOVRESET , aboutboxcaption, sizeof(aboutboxcaption));
	
	int msgboxID = MessageBox(NULL, s, aboutboxcaption, MB_ICONINFORMATION | MB_OK | MB_APPLMODAL );

	if ( msgboxID == IDOK ) 
		aboutbox = false;	// bug sa timerom
}