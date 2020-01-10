#include "AttackPlayerThird.h"
#include "SDL.h"
#include "WeaponRotationAnimationPlayer.h"

AttackPlayerThird::AttackPlayerThird() :
	AttackBase()
{
	canNotActionTime = 50;
	waitTimeForNextAttack = 10;
}

AttackPlayerThird::~AttackPlayerThird()
{
}

void AttackPlayerThird::Attack(const Vector3 & _ownerPosition, const int& _direction)
{
	new WeaponRotationAnimationPlayer(_ownerPosition, _direction, 0, 50, 2);

}
