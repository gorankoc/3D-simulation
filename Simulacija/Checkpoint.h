#include "DarkGDK.h"
#include "Path.h"
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>
#include <algorithm>

#define CHECKPOINT_H "Checkpoint.h"
#define SPHERE_MIN 50

#if !defined SPARKY_H 
	#include "Sparky.h"
#endif
using namespace std;

class Point3D{
public:
	float x,y,z;

	Point3D();
	Point3D(float, float, float);

	friend std::ostream& operator <<( ostream&, const Point3D& );
	friend std::istream& operator >>( istream&, Point3D& );
};

class CheckPoint
{
	vector<Point3D> v;
	vector<Point3D> v_read;
	ifstream f_read;
	ofstream f_write;
	
	vector<Point3D>::iterator It;
	vector<Point3D>::iterator debug_It;
	
	int	  _sakupljenoCP;
	int	  _iSphereMin;
	int	  _iSphere;
	bool  _write;
	bool  _hideAll;
	float _SCollisionCP;	
	
public:
	/**
	* Konstruktor postavlja privatne membere:
	* int sakupljenoCP na 0; koliko je avion sakupio check pointova na pocetku
	* int iSphereMin; tu sam stavio da ID sfere poèinje od 50 tj. od iSphereMin odnosno SPHERE_MIN
	* bool _write na false, ne zapisuje u datoteku Checkpointova. 
	*/
	CheckPoint();
	/**
	* Otvara Checkpoint.txt za pisanje i kopira vektor ( member v ) 
	*/
	void write();
	/**
	* Otvara Checkpoint.txt za èitanje i kopira kordinate u read vektor ( member v_read ) 
	*/
	void read();
	/**
	* Brise sve i ponovo crta sve pointove ( iz read vektora )
	*/
	void Restart();
	/**
	* Kada u runtime-u kliknemo Checkpoint start, poènemo crtati pointove sa space-om u write vector (v)
	* i pritisnemo Checkpoint end, zapisu se svi pointovi iz write vektor u Checkpoint.txt.
	* Program se restarta, pointovi se inicijaliziraju; da v_read ne èita iz datoteke ponovo, jednostavno kopira
	* pointove iz write vektora koji je još uvijek pun poslije crtanja sa space-om.
	*/
	void InitWriteToRead();
	/**
	* Briše sa ekrana sve preostale sfere ( pointove ) iz memorije
	*/
	void Free();
	/**
	* U write mode-u CheckPoint start u runtime-u, na space dodaje crveni point u 3d prostor
	* zapisuje u write vektor, da bi se iz tog vektora zapisalo u .txt na Checkpoint end.
	*/
	void AddPoint(Point3D &p);
	/**
	* Crta checkpoint sferu.
	* @param Point& p kordinata sfere
	*/
	void DrawSphere(Point3D &p);
	/**
	* Oznaèava poèetak zapisivanja u write vektor.
	*/
	void SetWriteModeOn();
	/**
	* Oznaèava završetak zapisivanja
	*/
	void SetWriteModeOff();
	/**
	* Property koji vraæa da li je objekt u stanju zapisivanja
	*/
	bool IsWriteMode() const;
	/**
	* Ako je Duration 1000, svaki point ce se nacrtati u razmaku od sekunde, tj. funkcija ne 
	* dozvoljava crtanje 2 pointa unutar sekunde. Da nema ove funkcije igrac bi morao za jednu 
	* nacrtanu sferu pritisnuti i pustiti space u roku od 1/FPS sekundi.
	* @param Duration vrijednost u milisekundama
	*/
	bool Delayed_Space_Key(int Duration);
	void DebugInfo();
	//dodati destruktor
	/**
	*	Priprema sparky dll na rad sa iSphere-iSphereMin pointova, te postavlja objecttype kolizije na sferu
	*/
	void SetupCollision();
	/** 
	* Koristi se u main-u, za svaki LoopGDK korak odosno FPS, provjeravat ce da li je objectID pokupio point
	* @param objectID: koji ce se objekt sudarat sa pointovima
	*/
	void SphereCollisionUpdate( int objectID );
	/**
	* Point je sakupljen, poziva se jedino iz SphereCollisionUpdate
	*/
	void Sakupljeno(int SphereID);
	void HideAll();
	int SakupljenoCP();
};