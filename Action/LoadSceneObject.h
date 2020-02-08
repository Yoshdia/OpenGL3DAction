#pragma once
#include "SceneObjectBase.h"
/*
@file LoadSceneObject.h
@brief ƒ[ƒh‰æ–Ê
*/
class LoadSceneObject :
	public SceneObjectBase
{
public:
	LoadSceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~LoadSceneObject();

	void UpdateGameObject(float _deltaTime)override;
private:
	//Œo‰ßŠÔ
	int t;
};

