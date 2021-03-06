#include "SceneObjectBase.h"


/*
@param _SetSceneFunc シーン変更関数
@sa GameObjectManager.h
*/
SceneObjectBase::SceneObjectBase(std::function<void(SceneName)> _SetSceneFunc):
	GameObject()
{
	SetSceneFunc = _SetSceneFunc;
}

SceneObjectBase::~SceneObjectBase()
{
}

