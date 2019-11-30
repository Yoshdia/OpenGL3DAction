#include "SkeltonObjectChecker.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "MeshComponent.h"
//debug
#include "Game.h"

SkeltonObjectChecker::SkeltonObjectChecker(GameObject* _parent, Vector3 _pos, Vector3 _colliderSize, Tag _pairTag) :
	GameObject(),
	offset(_pos),
	parent(_parent),
	pairTag(_pairTag),
	noTargetTouching(true),
	colliderPairPos(Vector3(0, 0, 0)),
	changed(false)
{
	SetPosition(offset + parent->GetPosition());

	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, _colliderSize, myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

		meshComponent = new MeshComponent(this);
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/collisionMask.gpmesh"));
	SetScale(_colliderSize);
}

SkeltonObjectChecker::~SkeltonObjectChecker()
{
}

void SkeltonObjectChecker::UpdateGameObject(float _deltaTime)
{
	if (Game::debug)
	{
		meshComponent->SetVisible(true);
	}
	else
	{
		meshComponent->SetVisible(false);
	}

	SetPosition(offset + parent->GetPosition());

	//接触した際にフラグをリセットしない
	if (!changed)
	{
		noTargetTouching = true;
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
		noTargetTouching = false;
		changed = true;
		colliderPairPos = colliderPair->GetPosition();
	}
}

void SkeltonObjectChecker::OnTriggerEnter(ColliderComponent* colliderPair)
{
	//if (colliderPair->GetObjectTag() == pairTag)
	//{
	//	changed = true;
	//	colliderPairPos = colliderPair->GetPosition();
	//}
}
