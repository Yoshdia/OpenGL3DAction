#include "AttackPlayerTwice.h"
#include "SDL.h"
#include "WeaponRotationAnimationPlayer.h"

AttackPlayerTwice::AttackPlayerTwice():
	AttackBase()
{
	canNotActionTime = 30;
	waitTimeForNextAttack = 10;
}


AttackPlayerTwice::~AttackPlayerTwice()
{
}

void AttackPlayerTwice::Attack(const Vector3& _ownerPosition)
{
	new WeaponRotationAnimationPlayer(_ownerPosition, 1);
	SDL_Log("Success Attack Twice!");
}
