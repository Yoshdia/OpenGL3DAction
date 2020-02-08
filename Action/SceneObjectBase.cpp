#include "SceneObjectBase.h"


/*
@param _SetSceneFunc �V�[���ύX�֐�
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

