#include "EnemyBase.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "GravityComponent.h"
#include "ColliderComponent.h"


EnemyBase::EnemyBase(const std::string & meshName) :
	GameObject()
{
	tag = Tag::EnemyTag;
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh(meshName));
	GravityComponent* gravityComponent = new GravityComponent(this, 100, 20);

	std::function<void(ColliderComponent*)>  Enter = std::bind(&EnemyBase::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&EnemyBase::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, Enter, Stay, tag, Vector3(0, 0, 0));
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::OnTriggerStay(ColliderComponent * colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		printf("\nouti!");
	}

}
