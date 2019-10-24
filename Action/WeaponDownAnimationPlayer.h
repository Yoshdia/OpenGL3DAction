#pragma once
#include "GameObject.h"


class WeaponDownAnimationPlayer :
	public GameObject
{
public:
	WeaponDownAnimationPlayer(const Vector3& pos);
	~WeaponDownAnimationPlayer();
void UpdateGameObject(float _deltaTime); 
private:
	class MeshComponent* meshComponent;
	float rad;
};

