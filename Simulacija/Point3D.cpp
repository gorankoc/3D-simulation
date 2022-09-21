#include "Checkpoint.h"

Point3D::Point3D()
{
	x = 0;
	y = 0;
	z = 0;
}
Point3D::Point3D(float X, float Y, float Z): x(X), y(Y), z(Z) {}

std::ostream& operator <<( ostream& o, const Point3D& p ){
	return o << p.x << " " << p.y << " " << p.z << "\n"; 
}
std::istream& operator >>( istream& i, Point3D& p ){ 
	return i >> p.x >> p.y >> p.z; 
}