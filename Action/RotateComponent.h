#pragma once
#include "Component.h"
#include "Math.h"

/*
 @file RotateComponent.h
 @brief ŠÖ”‚É‰ñ“]‚³‚¹‚½‚¢Šp“x‚ğ“n‚·‚ÆeƒIƒuƒWƒFƒNƒg‚ğ‰ñ“]‚³‚¹‚é
	*/
class RotateComponent :
	public Component
{
public:
	RotateComponent(GameObject* _owner, int _updateOrder=100);
	~RotateComponent();

	/*
	@brief ‰ñ“]‚ğs‚¤
	@param _rotate Šp“x
	@param _axis ‰ñ“]²
	*/
	void SetRotation(const float& _rotate,const Vector3& _axis);
};

