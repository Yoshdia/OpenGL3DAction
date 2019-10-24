#include "AttackPlayerTwice.h"
#include "SDL.h"


AttackPlayerTwice::AttackPlayerTwice():
	AttackBase()
{
	canNotActionTime = 50;
	waitTimeForNextAttack = 10;
}


AttackPlayerTwice::~AttackPlayerTwice()
{
}

void AttackPlayerTwice::Attack(const Vector3& _ownerPosition)
{
	SDL_Log("Success Attack Twice!");
}
