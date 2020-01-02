#pragma once
#include "GameObject.h"

class MainCameraObject :
	public GameObject
{
public:
	MainCameraObject();
	~MainCameraObject();

	//���̃N���X�̓|�[�Y���ɕʃN���X����X�V�֐����Ă΂�邱�Ƃ�����
	void UpdateGameObject(float _deltaTime=1.0f)override;
	void SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos);
private:
	Vector3 offsetPos;
	Vector3 lerpObject;
	bool hasParentObject;
};

