#pragma once
#include "GameObject.h"

class MainCameraObject :
	public GameObject
{
public:
	MainCameraObject();
	~MainCameraObject();

	void UpdateGameObject(float _deltaTime)override;
	void SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos);
private:
	Vector3 offsetPos;
	Vector3 lerpObject;
	bool hasParentObject;
};

