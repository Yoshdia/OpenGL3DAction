#pragma once
#include "GameObject.h"
class WeaponRotationAnimationPlayer :
	public GameObject
{
public:
	WeaponRotationAnimationPlayer(const Vector3& _pos ,const int& moveDistanceStage);
	~WeaponRotationAnimationPlayer();
	void UpdateGameObject(float _deltaTime);
private:
	void Rotate();
	class MeshComponent* meshComponent;
	float rad;
	Vector3 targetPos;
};

