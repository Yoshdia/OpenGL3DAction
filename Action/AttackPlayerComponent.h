#pragma once
#include "Component.h"



class AttackPlayerComponent :
	public Component
{
public:
	AttackPlayerComponent(GameObject* _owner, int _updateOrder );
	~AttackPlayerComponent();

	void Update(float _deltaTime);
	float Attack();
private:
	class AttackBase* attack;
};

