#pragma once
#include "GameObject.h"

/*
@file DebugBox.h
@brief �f�o�b�O�p�̃I�u�W�F�N�g
*/
class DebugBox :
	public GameObject
{
public:
	/*
	@param _p ���W
	@param _size �T�C�Y
	@param _tag �^�O
	*/
	DebugBox(Vector3 p,Vector3 _size=Vector3(50,50,50),Tag _tag=Tag::GroundTag);
	~DebugBox();

	void GameObjectInput(const InputState& _keyState)override;
};

