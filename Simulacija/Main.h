#include "Timer.h"
#include "Terrain.h"
#include "Camera.h"
#include "Particles.h"
#include "Game.h"
#include "Collision.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "globstruct.h"
#include "resource.h"

#if !defined CHECKPOINT_H
	#include "CheckPoint.h"
#endif 

#define IDT_SAT 2
#define _RESTART 012345