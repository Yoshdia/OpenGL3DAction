#include "ForwardGroundCheck.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"

ForwardGroundCheck::ForwardGroundCheck(GameObject* _parent) :
	GameObject(),
	myPos(Vector3(0,0,0)),
	parent(_parent),
	noGround(true)
{
	SetPosition(myPos + parent->GetPosition());
	std::function<void(ColliderComponent*)>  Enter = std::bind(&ForwardGroundCheck::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&ForwardGroundCheck::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, Enter, Stay, tag, Vector3(0, 0, 0));

	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/untitled.gpmesh"));
}

ForwardGroundCheck::~ForwardGroundCheck()
{
}

void ForwardGroundCheck::UpdateGameObject(float _deltaTime)
{
	SetPosition(myPos + parent->GetPosition());
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
}
