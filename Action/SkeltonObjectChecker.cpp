#include "SkeltonObjectChecker.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "MeshComponent.h"

SkeltonObjectChecker::SkeltonObjectChecker(GameObject* _parent, Vector3 _pos, Vector3 _colliderSize, Tag _pairTag) :
	GameObject(),
	myPos(_pos),
	parent(_parent),
	pairTag(_pairTag),
	noGround(true),
	noGroundEnter(true),
	colliderPairPos(Vector3(0, 0, 0))
{
	SetPosition(myPos + parent->GetPosition());

	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, _colliderSize, myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/collisionMask.gpmesh"));
	SetScale(_colliderSize);
	changed = false;
}

SkeltonObjectChecker::~SkeltonObjectChecker()
{
}

void SkeltonObjectChecker::UpdateGameObject(float _deltaTime)
{
	SetPosition(myPos + parent->GetPosition());
	if (!noGround || !noGroundEnter)
	{
		colliderPairPos = Vector3(0, 0, 0);
	}

	if (changed)
	{
		printf("true\n");
	}
	else
	{
		printf("false\n");

	}
	if (!changed)
	{
		noGround = true;
		noGroundEnter = true;
	}
	else
	{
		changed = false;
	}
}

void SkeltonObjectChecker::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == pairTag)
	{
		noGround = false;
		changed = true;
		colliderPairPos = colliderPair->GetPosition();
	}
}

void SkeltonObjectChecker::OnTriggerEnter(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == pairTag)
	{
		noGroundEnter = false;
		changed = true;
		colliderPairPos = colliderPair->GetPosition();
	}
}
