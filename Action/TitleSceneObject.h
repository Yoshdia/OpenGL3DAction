#pragma once
#include "SceneObjectBase.h"

/*
@file TitleSceneObject.h
@brief �^�C�g�����
*/
class TitleSceneObject :
	public SceneObjectBase
{
public:
	TitleSceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~TitleSceneObject();

	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn �w��̓��͂��s��ꂽ�玟�̃V�[���ֈڍs
	*/
	void GameObjectInput(const InputState& _keyState)override;
};

