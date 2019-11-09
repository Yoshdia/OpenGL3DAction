#pragma once
#include "Component.h"

/*
 @file GravityComponent.h
 @brief 簡単な説明
	*/
class GravityComponent :
	public Component
{
public:
	/*
	@param _gravityPower 重力の大きさ
*/
	GravityComponent(GameObject* _owner, int _updateOrder, int _gravityPower);
	~GravityComponent();
	/*
	@brief 重力
	*/
	void Update(float _deltaTime)override;
	void Gravity();
private:
	int gravityPower;

};

