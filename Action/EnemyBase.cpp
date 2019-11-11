#include "EnemyBase.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "GravityComponent.h"
#include "ColliderComponent.h"
#include "FootSole.h"

const float EnemyBase::NockBackPower = 30;

EnemyBase::EnemyBase(const std::string& meshName) :
	GameObject()
{
	tag = Tag::EnemyTag;
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh(meshName));
	gravityComponent = new GravityComponent(this, 100, 20);

	std::function<void(ColliderComponent*)>  Enter = std::bind(&EnemyBase::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&EnemyBase::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, Enter, Stay, tag, Vector3(0, 0, 0));
	footSole = new FootSole(this);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::UpdateGameObject(float _deltaTime)
{
	UpdateEnemyObject(_deltaTime);
	if (footSole->GetGroundFlag() == true)
	{
		gravityComponent->Gravity();
	}
	NockBack();
}

void EnemyBase::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		//printf("\nouti!"); 
	}
}

void EnemyBase::OnTriggerEnter(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		printf("\nouti!");
		double distance = Math::Sqrt((colliderPair->GetPosition().x - position.x) * (colliderPair->GetPosition().x - position.x) + (colliderPair->GetPosition().y - position.y) * (colliderPair->GetPosition().y - position.y));
		Vector3 force = Vector3::Normalize(Vector3((position.x- colliderPair->GetPosition().x), ( position.y- colliderPair->GetPosition().y), ( position.z- colliderPair->GetPosition().z)));
		forceVector = force * NockBackPower;
	}
}

void EnemyBase::NockBack()
{
	if (forceVector.x >= 0.1f &&forceVector.x<=-0.1f)
	{
		forceVector = Vector3::Zero;
		return;
	}

	forceVector =forceVector/ 2.0f;
	SetPosition(position+forceVector);
}
