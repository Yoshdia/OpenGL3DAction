#include "FootSole.h"
#include "ColliderComponent.h"

FootSole::FootSole(GameObject* _parent):
	GameObject(),
	parent(_parent),
	parentPos(_parent->GetPosition()),
	footPos(Vector3(0, -25, 0)),
	noGround(true)
{
	if (_parent == nullptr)
	{
		printf("Error! FootSole::parent is nullptr");
	}
	SetPosition(parentPos + footPos);

	std::function<void(ColliderComponent*)>  Enter = std::bind(&FootSole::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&FootSole::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(0.4f, 60, 0.8f), myObjectId, Enter, Stay, tag);
}

FootSole::~FootSole()
{
}

void FootSole::UpdateGameObject(float _deltaTime)
{
	noGround = true;
	parentPos = parent->GetPosition();
	SetPosition(parentPos+footPos);
}

void FootSole::OnTriggerStay(ColliderComponent * colliderPair)
{
	if (colliderPair->GetObjectTag()==Tag::GroundTag)
	{
		noGround = false;
	}
}
