#pragma once
#include "Component.h"
#include "Math.h"

/*
 @file RotateComponent.h
 @brief �֐��ɉ�]���������p�x��n���Ɛe�I�u�W�F�N�g����]������
	*/
class RotateComponent :
	public Component
{
public:
	RotateComponent(GameObject* _owner, int _updateOrder=100);
	~RotateComponent();

	/*
	@brief ��]���s��
	@param _rotate �p�x
	@param _axis ��]��
	*/
	void SetRotation(const float& _rotate,const Vector3& _axis);
};

