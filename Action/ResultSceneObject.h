#pragma once
#include "SceneObjectBase.h"
class ResultSceneObject :
	public SceneObjectBase
{
public:
	ResultSceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~ResultSceneObject();

	void UpdateGameObject(float _deltaTime)override;
private:
	int t;
};

