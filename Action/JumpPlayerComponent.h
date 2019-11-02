#pragma once
#include "Component.h"
#include "GameObject.h"

/*
 @file JumpPlayerComponent名.h
 @brief ジャンプする
	*/
class JumpPlayerComponent :
	public Component
{
public:
	/*
	@param _jumpPower ジャンプ力の最大値
	*/
	JumpPlayerComponent(GameObject* _owner, int _updateOrder, float _jumpPower);
	~JumpPlayerComponent();

	/*
  @fn 現ジャンプ力のjumpPowerをリセットする
*/
	void Jump(float _deltaTime);

	/*
  @brief　ジャンプ力を減らし座標を更新させる
*/
	void Update(float _deltaTime)override;
private:
	//動的に変化するジャンプ量
	float jumpPower;
	//ジャンプ力の最大値
	float jumpPowerMax;
};

