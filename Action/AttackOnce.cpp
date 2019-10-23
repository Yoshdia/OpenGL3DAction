#include "AttackOnce.h"
#include "SDL.h"


AttackOnce::AttackOnce()
{
	canNotActionTime = 20.0;
	waitTimeForNextAttack = 0;
}


AttackOnce::~AttackOnce()
{
}

void AttackOnce::Attack()
{
	SDL_Log("Success Attack Once!!!!!!!!!!!NICE!!!!!!!!!!!!!!!!!!!!!!!");
}
