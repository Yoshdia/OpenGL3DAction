#pragma once
#include "GameObject.h"
class FootSole :
	public GameObject
{
public:
	FootSole(Vector3& _playerPosition, bool& _jumped);
	~FootSole();

	void UpdateGameObject(float _deltaTime)override;
private:
	void OnTriggerStay(ColliderComponent* colliderPair)override;
	Vector3* playerPosition;
	bool *noLand;
	Vector3 footPos;
};

