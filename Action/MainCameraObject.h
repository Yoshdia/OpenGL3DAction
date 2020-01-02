#pragma once
#include "GameObject.h"

class MainCameraObject :
	public GameObject
{
public:
	MainCameraObject();
	~MainCameraObject();

	//このクラスはポーズ中に別クラスから更新関数を呼ばれることがある
	void UpdateGameObject(float _deltaTime=1.0f)override;
	void SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos);
private:
	Vector3 offsetPos;
	Vector3 lerpObject;
	bool hasParentObject;
};

