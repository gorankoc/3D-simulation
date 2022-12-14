#include "Checkpoint.h"
#include "Resource.h"

using namespace std;

CheckPoint::CheckPoint():_sakupljenoCP(0), _iSphereMin(SPHERE_MIN), _iSphere(_iSphereMin), _write(false), _hideAll(false){}

void CheckPoint::write()
{
		try
		{
			f_write.open(CHECKPOINTS_TXT); 
			ostream_iterator<Point3D> out( f_write );
			
			if ( !v.size() )
			{
				TCHAR s[64];
				LoadString(0, IDS_ERRWRITEVECTORPRAZAN, s, sizeof(s));
				MessageBox( NULL, s, "Reset !", MB_ICONINFORMATION | MB_OK | MB_APPLMODAL );
			}
			else
			{
				copy( v.begin(), v.end(), out );
			}
		}
		catch(ostream::failure e)
		{
			MessageBox(NULL, e.what(), "Reset !", MB_ICONINFORMATION | MB_OK | MB_APPLMODAL );
		}
		f_write.close();
		SetWriteModeOff();
}
void CheckPoint::read()
{
	f_read.open( CHECKPOINTS_TXT );
	istream_iterator<Point3D> in( f_read );
	istream_iterator<Point3D> eos;

	v_read.begin();

	copy(in, eos, back_inserter( v_read ));
	f_read.close();

	Restart();
}
void CheckPoint::Restart()
{
	_sakupljenoCP = 0;
	Free();
	
	for (It = v_read.begin(); It != v_read.end(); It++)
	{
	      DrawSphere(*It);
		  dbColorObject ( _iSphere-1, dbRGB( 50, 100, 255 ) );
	}
	if(!v_read.size())
	{
		TCHAR s[64]; 
		LoadString(0, IDS_ERRREADVECTORPRAZAN, s, sizeof(s));
		MessageBox(NULL, s, "Reset !", MB_ICONINFORMATION | MB_OK | MB_APPLMODAL );
	}
}
void CheckPoint::InitWriteToRead()
{
	v_read.begin();

	for(It = v.begin(); It != v.end(); It++)
		v_read.push_back(*It);

	if( _iSphere != _iSphereMin)
	{
		for(int i = _iSphereMin; i < _iSphere; ++i)
			dbColorObject ( i, dbRGB( 50, 100, 255 ) );
	}
}
void CheckPoint::Free()
{
	if( _iSphere != _iSphereMin)
	{
		for(int i = _iSphereMin; i < _iSphere; i++)
			dbDeleteObject(i);
			_iSphere = _iSphereMin;
	}
	_sakupljenoCP = 0;
}
void CheckPoint::AddPoint(Point3D &p)
{
	v.push_back( p );
	DrawSphere( p );
	dbColorObject ( _iSphere-1, dbRGB( 255, 10, 50 ) );
}
void CheckPoint::DrawSphere(Point3D& p)
{
	dbMakeObjectSphere		( _iSphere, 15, 8, 8 );	
	dbSetObjectWireframe	( _iSphere, true );		
	dbPositionObject		( _iSphere, p.x, p.y, p.z );
		
	_iSphere++;
}
void CheckPoint::SetWriteModeOn()	
{
	v.clear();
	v_read.clear();
	Free();
	_write = true;

}	
void CheckPoint::SetWriteModeOff()	
{
	_write = false;
}
bool CheckPoint::IsWriteMode() const
{	
	return _write;
}
bool CheckPoint::Delayed_Space_Key(int Duration)//, IEngine* ie) 
{		
	static int starttime = dbTimer();
	static int time = 0;
	static bool space = false;

	if( dbSpaceKey() == 1 && !space) 
	{
		space = true;
		starttime = dbTimer();
		time = 0;
	}
	if( space ) 
	{
		time = dbTimer() - starttime;
		if(time > Duration) 
		{ 
			time = 0;
			starttime = 0; 
			space = false;
					
			//dbPrint("Mouse has been clicked and held"); 
			return true; // dbSpaceKey has been held for Duration.
		}
		if( dbSpaceKey() != 1) { // If dbSpaceKey not held anymore, reset everything and stop counting.
			space = false; 
			starttime = 0;
			time = 0;
		}
	}
	return false; // Mouse not pressed or held long enough.
}
void CheckPoint::DebugInfo()
{
	TCHAR s[64]; 
	LoadString(0, IDS_SAKUPLJENO, s, sizeof(s));
	
	dbPrint(s);
	dbPrint("iSphereMin");
	dbPrint(dbStr(_iSphereMin));
	dbPrint("iSphere");
	dbPrint(dbStr(_iSphere));
	dbPrint("sakupljenoCP");
	dbPrint(dbStr(_sakupljenoCP));
}
void CheckPoint::SetupCollision()
 {
	//SC_Start();

	for(int i = _iSphereMin; i < _iSphere; i++)
		SC_SetupObject(i, 2, 1);	// shpere

}
void CheckPoint::SphereCollisionUpdate( int objectID ) 
{
	if ( _iSphere != _iSphereMin)
	{
		for( int j = _iSphereMin; j < _iSphere; j++ )
		{
  			SC_UpdateObject( j );
			_SCollisionCP = SC_ObjectCollision ( objectID, j ); //_ie->_ID, j );

			if( _SCollisionCP && dbObjectVisible(j) )
				Sakupljeno(j);
		}
	}
	 
}
void CheckPoint::Sakupljeno(int SphereID)
{
	_sakupljenoCP++;
	dbHideObject(SphereID);
	//this->iSphere--;ako je iSphere-- onda kod updateColl se gubi ID u petlji, tj.
	//da ostavim ovak morao bi napravit niz flagova za tu petlju koja bi updateala
	//odredene IDeve, al neka updatea sve ID	
}
void CheckPoint::HideAll()
{
	int k = _iSphereMin;
	while( k < _iSphere )
	{
		dbHideObject(k);
		k++;
	}
}
int CheckPoint::SakupljenoCP()
{
	return _sakupljenoCP;
}