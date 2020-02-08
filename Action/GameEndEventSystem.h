#pragma once
#include "EventSystem.h"
/*
@file GameEndEventSystem.h
@brief �v���C���[�ƏՓ˂����Ƃ��Ƀt���O�����Ă�N���X
*/
class GameEndEventSystem :
	public EventSystem
{
public:
	/*
	@param _pos ���W
	*/
	GameEndEventSystem(const Vector3& _pos);
	~GameEndEventSystem();
private:
	/*
	@fn �v���C���[�ƏՓ˂����Ƃ��Ƀt���O�����Ă�N���X
	*/
	void OnTriggerEnter(ColliderComponent* _pair)override;
	bool end;
public://�Q�b�^�[�Z�b�^�[
	/*
	@return �v���C���[�ƐڐG������
	*/
	bool GetEndFlag() { return end; }
};

