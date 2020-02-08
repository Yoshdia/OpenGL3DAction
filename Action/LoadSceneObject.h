#pragma once
#include "SceneObjectBase.h"
class LoadSceneObject :
	public SceneObjectBase
{
public:
	LoadSceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~LoadSceneObject();

	void UpdateGameObject(float _deltaTime)override;
private:
	int t;
};

