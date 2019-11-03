#include "FootSole.h"
#include "ColliderComponent.h"

FootSole::FootSole(Vector3 & _playerPosition, bool & _jumped):
	GameObject()
{
	parentPosition = &_playerPosition;
	noLand = &_jumped;
	footPos = Vector3(0, -25, 0);
	std::function<void(ColliderComponent*)>  Enter = std::bind(&FootSole::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&FootSole::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(0.4f, 30, 0.8f), myObjectId, Enter, Stay, tag);
}

FootSole::~FootSole()
{
}

void FootSole::UpdateGameObject(float _deltaTime)
{
	Vector3 p = *parentPosition;
	SetPosition(p+footPos);
}

void FootSole::OnTriggerStay(ColliderComponent * colliderPair)
{
	if (colliderPair->GetObjectTag())
	{
		*noLand = false;
	}
}
