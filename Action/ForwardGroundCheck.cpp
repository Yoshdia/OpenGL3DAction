#include "ForwardGroundCheck.h"
#include "ColliderComponent.h"

ForwardGroundCheck::ForwardGroundCheck(GameObject* _parent, Vector3 _pos,Vector3 _colliderSize,Tag _pairTag) :
	GameObject(),
	myPos(_pos),
	parent(_parent),
	pairTag(_pairTag),
	noGround(true),
	noGroundEnter(true),
	colliderPairPos(Vector3(0,0,0))
{
	SetPosition(myPos + parent->GetPosition());
	std::function<void(ColliderComponent*)>  Enter = std::bind(&ForwardGroundCheck::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&ForwardGroundCheck::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, _colliderSize, myObjectId, Enter, Stay, tag, Vector3(0, 0, 0));
}

ForwardGroundCheck::~ForwardGroundCheck()
{
}

void ForwardGroundCheck::UpdateGameObject(float _deltaTime)
{
	SetPosition(myPos + parent->GetPosition());
	if (!noGround || !noGroundEnter)
	{
		colliderPairPos = Vector3(0, 0, 0);
	}

	noGroundEnter = true;
}

void ForwardGroundCheck::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == pairTag)
	{
		noGround = false;
		colliderPairPos = colliderPair->GetPosition();
	}
}

void ForwardGroundCheck::OnTriggerEnter(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == pairTag)
	{
		noGroundEnter = false;
		colliderPairPos = colliderPair->GetPosition() ;
	}
}
