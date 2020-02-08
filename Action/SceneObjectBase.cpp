#include "SceneObjectBase.h"


/*
@param _SetSceneFunc ƒV[ƒ“•ÏXŠÖ”
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

