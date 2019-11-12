#include "ForwardGroundCheck.h"
#include "ColliderComponent.h"

ForwardGroundCheck::ForwardGroundCheck(GameObject* _parent, Vector3 _pos) :
	GameObject(),
	myPos(_pos),
	parent(_parent),
	noGround(true),
	noGroundEnter(true)
{
	SetPosition(myPos + parent->GetPosition());
	std::function<void(ColliderComponent*)>  Enter = std::bind(&ForwardGroundCheck::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&ForwardGroundCheck::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(1, 1, 1), myObjectId, Enter, Stay, tag, Vector3(0, 0, 0));
}

ForwardGroundCheck::~ForwardGroundCheck()
{
}

void ForwardGroundCheck::UpdateGameObject(float _deltaTime)
{
	SetPosition(myPos + parent->GetPosition());
	noGroundEnter = true;
}

void ForwardGroundCheck::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::GroundTag)
	{
		noGround = false;
	}
}

void ForwardGroundCheck::OnTriggerEnter(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::GroundTag)
	{
		noGroundEnter = false;
	}
}
