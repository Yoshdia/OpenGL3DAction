#include "AttackPlayerTwice.h"
#include "SDL.h"
#include "WeaponRotationAnimationPlayer.h"

AttackPlayerTwice::AttackPlayerTwice():
	AttackBase()
{
	canNotActionTime = 20;
	waitTimeForNextAttack = 50;
}


AttackPlayerTwice::~AttackPlayerTwice()
{
}

void AttackPlayerTwice::Attack(const Vector3& _ownerPosition,const float& _direction)
{
	new WeaponRotationAnimationPlayer(_ownerPosition, _direction, 0, 120, 1);

}
