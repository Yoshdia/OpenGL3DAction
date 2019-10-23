#pragma once
#include "AttackBase.h"

class AttackOnce final:
	public AttackBase
{
public:
	AttackOnce();
	~AttackOnce();

	void Attack() override;

};

