#pragma once
#include "SceneObjectBase.h"
class PlaySceneObject :
	public SceneObjectBase
{
public:
	PlaySceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~PlaySceneObject();

	void UpdateGameObject(float _deltaTime)override;
private:
	class PlayerCharacter* player;
};

