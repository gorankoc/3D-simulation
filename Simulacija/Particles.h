#include "DarkGDK.h"

#if !defined IENGINE_H
	#include "IEngine.h"
#endif

#define PARTICLES_H "Particles.h"

class Particles
{
public:
	int _ImageNumber;
	int _ParticleID;
	int _ParticleGameOverID;
	int _EmissionsTerrain;
	int _EmissionsGameOver;

	Particles();
	/**
	* Setup èestica koje se pojavljuju kada je avion u dodiru sa terenom
	*/
	void setCollisionParticles();
	/**
	* Setup èestica koje se pojavljuju kada je game over
	*/
	void setGameOverParticles();
	void Init();
	/**
	* Èestice koje se pojavljuju kada je avion u dodiru sa terenom
	*/
	void DrawCollision(IEngine* ie);
	void StopTerrainParticles();
	/*
	//Èestice se pojavljuju kada je game over
	void DrawGameOver(IEngine* ie);
	void StopGameOverParticles();
	*/
};