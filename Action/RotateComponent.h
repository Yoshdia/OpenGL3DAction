#pragma once
#include "Component.h"
#include "Math.h"

class DrilObject;

class RotateComponent : public Component
{
public:
	RotateComponent(GameObject* _owner, int _updateOrder = 10);

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Update(float _deltaTime);

	/**
	@brief	���͏���
	@param	InputState�\����
	*/
	virtual void ProcessInput(const struct InputState& _state);

	Vector3 GetCameraUp() const { return Vector3::Transform(Vector3::UnitZ, cameraQuat); }
	Vector3 GetCameraForward() const { return Vector3::Transform(Vector3::UnitX, cameraQuat); }
private:

	void MoveWall();
	void HitRightWall();
	void HitLeftWall();
	void HitTopWall();
	void HitUnderWall();

	bool right;
    Quaternion target;
    float f;
    float addF;
	float moveTorque;
    Quaternion rot;
	Quaternion cameraQuat;
	Quaternion moveRot;
	Vector3 ownerPos;
};

