#pragma once
#include "GameObject.h"
#include <functional>

enum SceneName
{
	TitleScene,
	PlayScene,
	ResultScene,
	NoneScene,
};

class SceneObjectBase :
	public GameObject
{
public:
	SceneObjectBase(std::function<void(SceneName)> _SetSceneFunc);
	~SceneObjectBase();

protected:
	std::function<void(SceneName)> SetSceneFunc;
};

