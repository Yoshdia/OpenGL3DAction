#pragma once
#include "SceneObjectBase.h"
class TitleSceneObject :
	public SceneObjectBase
{
public:
	TitleSceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~TitleSceneObject();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState)override;
};

