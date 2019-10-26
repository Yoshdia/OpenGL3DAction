#include "AttackPlayerOnce.h"
#include"SDL.h"
#include "WeaponRotationAnimationPlayer.h"

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
	new WeaponRotationAnimationPlayer(_ownerPosition,0);
	SDL_Log("Success Attack Once!");
}
