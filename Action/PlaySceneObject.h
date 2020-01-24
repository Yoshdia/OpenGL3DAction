#pragma once
#include "SceneObjectBase.h"
class PlaySceneObject :
	public SceneObjectBase
{
public:
	PlaySceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~PlaySceneObject();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState)override;
	void PausingUpdateGameObject()override;
private:
	class PlayerCharacter* player;
	class GameEndEventSystem* endSystem;
	class PauseScreen* pausingScreen;
};

