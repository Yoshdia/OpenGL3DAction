#pragma once
#include "SceneObjectBase.h"

/*
@file TitleSceneObject.h
@brief タイトル画面
*/
class TitleSceneObject :
	public SceneObjectBase
{
public:
	TitleSceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~TitleSceneObject();

	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn 指定の入力が行われたら次のシーンへ移行
	*/
	void GameObjectInput(const InputState& _keyState)override;
};

