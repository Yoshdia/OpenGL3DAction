#pragma once
#include "GameObject.h"
class ThrowWeapon :
	public GameObject
{
public:
	ThrowWeapon(const Vector3& _pos);
	~ThrowWeapon();
	void UpdateGameObject(float _deltaTime)override;
private:
	class MeshComponent* meshComponent;

};

