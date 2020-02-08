#pragma once
#include "GameObject.h"
#include <functional>

/*
@enum SceneName
�V�[����
*/
enum SceneName
{
	TitleScene,
	PlayScene,
	ResultScene,
	LoadScene,
	NoneScene,
};

/*
@file SceneObjectBase.h
@brief �V�[���I�u�W�F�N�g�̊��N���X
@detail �V�[�����I�u�W�F�N�g�ɂ������R�́A�I�u�W�F�N�g�̐����ƃV�[���̕ύX���������s����N���X���K�v�Ȏ��ɃI�u�W�F�N�g�Ƃ��ėp���邱�Ƃ��ł���ƋC�t��������
*/
class SceneObjectBase :
	public GameObject
{
public:
	/*
	@param _SetSceneFunc �V�[���ύX�֐�
	@sa GameObjectManager.h
	*/
	SceneObjectBase(std::function<void(SceneName)> _SetSceneFunc);
	~SceneObjectBase();

protected:
	// �V�[���ύX�֐�
	std::function<void(SceneName)> SetSceneFunc;
};

