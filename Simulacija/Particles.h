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
	* Setup �estica koje se pojavljuju kada je avion u dodiru sa terenom
	*/
	void setCollisionParticles();
	/**
	* Setup �estica koje se pojavljuju kada je game over
	*/
	void setGameOverParticles();
	void Init();
	/**
	* �estice koje se pojavljuju kada je avion u dodiru sa terenom
	*/
	void DrawCollision(IEngine* ie);
	void StopTerrainParticles();
	/*
	//�estice se pojavljuju kada je game over
	void DrawGameOver(IEngine* ie);
	void StopGameOverParticles();
	*/
};