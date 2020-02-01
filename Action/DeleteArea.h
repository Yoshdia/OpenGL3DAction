#pragma once
#include "GameObject.h"
class DeleteArea :
	public GameObject
{
public:
	DeleteArea(GameObject* _parent);
	~DeleteArea();

	void UpdateGameObject(float _deltaTime)override;
private:
	GameObject* owner;
};

