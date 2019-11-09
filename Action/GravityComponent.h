#pragma once
#include "Component.h"

/*
 @file GravityComponent.h
 @brief �ȒP�Ȑ���
	*/
class GravityComponent :
	public Component
{
public:
	/*
	@param _gravityPower �d�͂̑傫��
*/
	GravityComponent(GameObject* _owner, int _updateOrder, int _gravityPower);
	~GravityComponent();
	/*
	@brief �d��
	*/
	void Update(float _deltaTime)override;
	void Gravity();
private:
	int gravityPower;

};

