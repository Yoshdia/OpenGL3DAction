#include "AttackPlayerOnce.h"
#include"SDL.h"


AttackPlayerOnce::AttackPlayerOnce() :
	AttackBase()
{
	canNotActionTime = 20;
	waitTimeForNextAttack = 30;
}


AttackPlayerOnce::~AttackPlayerOnce()
{
}

void AttackPlayerOnce::Attack()
{
	SDL_Log("Success Attack Once!");
}
