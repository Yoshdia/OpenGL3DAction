#include "HammerAttackPlayer.h"
#include "HammerWeapon.h"


HammerAttackPlayer::HammerAttackPlayer(const int& _number):
	AttackBase(),
	number(_number)
{
	canNotActionTime = 40;
	waitTimeForNextAttack = 45;
}


HammerAttackPlayer::~HammerAttackPlayer()
{
}

void HammerAttackPlayer::Attack(const Vector3 & _ownerPosition, const int & _directiron)
{
	new HammerWeapon(_ownerPosition,number,_directiron,30);
}
