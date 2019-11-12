#pragma once
#include "Component.h"

/*
 @file GravityComponent.h
 @brief ŠÈ’P‚Èà–¾
	*/
class GravityComponent :
	public Component
{
public:
	/*
	@param _gravityPower d—Í‚Ì‘å‚«‚³
*/
	GravityComponent(GameObject* _owner, int _updateOrder, int _gravityPower);
	~GravityComponent();
	/*
	@brief d—Í
	*/
	void Update(float _deltaTime)override;
	void Gravity(float _deltaTime);
	void IsGround();

private:
	int gravityPower;
	int noGroundTime;
};

