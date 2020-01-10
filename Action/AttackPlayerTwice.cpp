#include "AttackPlayerTwice.h"
#include "SDL.h"
#include "WeaponRotationAnimationPlayer.h"

AttackPlayerTwice::AttackPlayerTwice():
	AttackBase()
{
	canNotActionTime = 20;
	waitTimeForNextAttack = 30;
}


AttackPlayerTwice::~AttackPlayerTwice()
{
}

void AttackPlayerTwice::Attack(const Vector3& _ownerPosition,const int& _direction)
{
	new WeaponRotationAnimationPlayer(_ownerPosition, _direction, 0, 50, 1);

}
