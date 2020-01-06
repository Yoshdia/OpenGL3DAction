#include "SceneObjectBase.h"



SceneObjectBase::SceneObjectBase(std::function<void(SceneName)> _SetSceneFunc):
	GameObject()
{
	SetSceneFunc = _SetSceneFunc;
}

SceneObjectBase::~SceneObjectBase()
{
}

