#pragma once
#include "SceneObjectBase.h"
/*
@file LoadSceneObject.h
@brief ロード画面
*/
class LoadSceneObject :
	public SceneObjectBase
{
public:
	LoadSceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~LoadSceneObject();

	void UpdateGameObject(float _deltaTime)override;
private:
	//経過時間
	int t;
};

