#pragma once
#include "SceneObjectBase.h"
/*
@file LoadSceneObject.h
@brief ���[�h���
*/
class LoadSceneObject :
	public SceneObjectBase
{
public:
	LoadSceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~LoadSceneObject();

	void UpdateGameObject(float _deltaTime)override;
private:
	//�o�ߎ���
	int t;
};

