#pragma once
#include "GameObject.h"

/*
 @file WeaponRotationAnimationPlayer.h
 @brief 回転しながら前進し、一定位置まで進むと止まるプレイヤーの攻撃
	*/
class WeaponRotationAnimationPlayer :
	public GameObject
{
public:
	/*
	@param _pos 生成する座標
	@param _moveDistance 移動量、範囲は0~2
	*/
	WeaponRotationAnimationPlayer(const Vector3& _pos, const int& _direction, const int& _moveDistanceStage);
	~WeaponRotationAnimationPlayer();
	void UpdateGameObject(float _deltaTime);
private:
	class MeshComponent* meshComponent;
	/*
  @fn 回転
  @brief 回転速度を少しずつ減らしながら回転する
*/
	void Rotate();
	//回転速度。動的に変化
	float rotateSpeed;
	//回転速度の減少率。rotateSpeedが一定値まで減ると数が変化する
	float rotateSpeedSub;
	//移動の目標位置、生成時に_moveDistanceStageをもとに決定
	Vector3 targetPos;
	int direction;
	class RotateComponent* rotateComponent;
};

