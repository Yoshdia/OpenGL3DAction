#include "AttackPlayerOnce.h"
#include"SDL.h"
#include "WeaponDownAnimationPlayer.h"

AttackPlayerOnce::AttackPlayerOnce() :
	AttackBase()
{
	canNotActionTime = 20;
	waitTimeForNextAttack = 30;
}


AttackPlayerOnce::~AttackPlayerOnce()
{
}

void AttackPlayerOnce::Attack(const Vector3& _ownerPosition)
{
	new WeaponDownAnimationPlayer(_ownerPosition);
	SDL_Log("Success Attack Once!");
}
