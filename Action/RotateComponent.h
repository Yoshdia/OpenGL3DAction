#pragma once
#include "Component.h"
#include "Math.h"

/*
 @file RotateComponent.h
 @brief 関数に回転させたい角度を渡すと親オブジェクトを回転させる
*/
class RotateComponent :
	public Component
{
public:
	RotateComponent(GameObject* _owner, int _updateOrder=100);
	~RotateComponent();

	/*
	@brief 回転を行う
	@param _rotate 角度
	@param _axis 回転軸
	*/
	void SetRotation(const float& _rotate,const Vector3& _axis);
};

