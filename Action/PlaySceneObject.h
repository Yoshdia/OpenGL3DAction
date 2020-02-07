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
	//class GameEndEventSystem* endSystem;
	 GameObject* bossEnemy;
	class PauseScreen* pausingScreen;
	void SceneChangeEvents();
	bool EventWordObjectDelay();

	static const Vector3 EventWordObjectPos;
	static const Vector3 EventWordObjectSize;

	bool gameClear;
	bool gameOver;

	int endingCount;
	int endingDelay;
	bool createdEventWordObject;
	Vector3 endEffectPos;
};

