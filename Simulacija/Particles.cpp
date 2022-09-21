#include "DarkGDK.h"
#include "Particles.h"
#include "Path.h"

Particles::Particles()
{
	_ImageNumber  = 1;
	_ParticleID = 1;
	_ParticleGameOverID = 2;
	_EmissionsTerrain = 20;
	_EmissionsGameOver = 6000;
	
	dbLoadImage ( PATH_PARTICLETEXTURE, _ImageNumber );	//tekstura èestica
	
	setCollisionParticles();
	setGameOverParticles();
	
}	
void Particles::setCollisionParticles()
{
	dbMakeParticles			( _ParticleID, _ImageNumber, 150, 1 );	
	//dbColorParticles		(  ParticleNumber, 0,50,200 );
	dbSetParticleGravity	( _ParticleID, 2 );
	dbSetParticleSpeed		( _ParticleID, 0.06f );
	dbColorParticles		( _ParticleID, 255, 128, 0 );
	dbSetParticleEmissions	( _ParticleID, 20 );	//This command will set the number of particles emitted from the particles object each cycle. A value of zero will stop the particles object emitting new particles. 
	dbSetParticleLife		( _ParticleID, 3000 );
	
}
void Particles::setGameOverParticles()
{
	dbMakeParticles			( _ParticleGameOverID, _ImageNumber, 200000, 2.5f );	//dbMakeFireParticles	( ParticleGameOverNumber, ImageNumber,15000,15,15,15,15,15,15 );
	dbSetParticleEmissions	( _ParticleGameOverID, _EmissionsGameOver );	
	dbSetParticleSpeed		( _ParticleGameOverID, 0.05f );
	dbSetParticleGravity	( _ParticleGameOverID, 0.8f );
	dbSetParticleChaos		( _ParticleGameOverID, 0.6f );
	dbSetParticleLife		( _ParticleGameOverID, 5000 );
}
void Particles::Init()
{
	StopTerrainParticles();
	//StopGameOverParticles();
}
void Particles::DrawCollision(IEngine* ie)
{ 		
	dbSetParticleEmissions		( _ParticleID, _EmissionsTerrain );
	dbPositionParticleEmissions ( _ParticleID, ie->x, ie->y, ie->z );
}
void Particles::StopTerrainParticles()
{
	dbSetParticleEmissions ( _ParticleID, 0 );
}
/*void Particles::DrawGameOver(IEngine* ie)
{ 		
	dbSetParticleEmissions		( _ParticleGameOverID, _EmissionsGameOver );
	dbPositionParticleEmissions ( _ParticleGameOverID, ie->x, ie->y, ie->z );
}
void Particles::StopGameOverParticles()
{
	dbSetParticleEmissions ( _ParticleGameOverID, 0 );
}*/