#include "EnemyBase.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "GravityComponent.h"
#include "ColliderComponent.h"
#include "FootSole.h"
#include "ForwardGroundCheck.h"

const float EnemyBase::NockBackPower = 30;
const float EnemyBase::GroundCheckPos = 40;

EnemyBase::EnemyBase(const std::string& meshName) :
	GameObject(),
	moveDirection(EnemyMoveDirection::right)
{
	tag = Tag::EnemyTag;
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh(meshName));
	gravityComponent = new GravityComponent(this, 100, 20);

	std::function<void(ColliderComponent*)>  Enter = std::bind(&EnemyBase::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&EnemyBase::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, Enter, Stay, tag, Vector3(0, 0, 0));
	footSole = new FootSole(this);

	forwardDownGroundCheck = new ForwardGroundCheck(this, Vector3(GroundCheckPos, -30, 0));
	forwardGroundCheck = new ForwardGroundCheck(this, Vector3(GroundCheckPos, 0, 0));
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::UpdateGameObject(float _deltaTime)
{
	SetPosition(Vector3(3 * moveDirection, 0, 0) + position);
	UpdateEnemyObject(_deltaTime);

	if (footSole->GetGroundFlag() == true)
	{
		gravityComponent->Gravity(_deltaTime);
	}
	NockBack();

	if (forwardDownGroundCheck->GetGround() == true|| forwardGroundCheck->GetGroundEnter()==false)
	{
		moveDirection = (EnemyMoveDirection)(moveDirection * (EnemyMoveDirection)-1);
		forwardDownGroundCheck->ResetGroundFlag(false);
	}
	else
	{
		forwardDownGroundCheck->ResetGroundFlag(true); 
		//forwardGroundCheck->ResetGroundFlag(true);
	}
	forwardDownGroundCheck->SetCheckPos(Vector3(GroundCheckPos * moveDirection, -30, 0));
	forwardGroundCheck->SetCheckPos(Vector3(GroundCheckPos * moveDirection, 0, 0));
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
		double distance = Math::Sqrt((colliderPair->GetPosition().x - position.x) * (colliderPair->GetPosition().x - position.x) + (colliderPair->GetPosition().y - position.y) * (colliderPair->GetPosition().y - position.y));
		Vector3 force = Vector3::Normalize(Vector3((position.x - colliderPair->GetPosition().x), (position.y - colliderPair->GetPosition().y), (position.z - colliderPair->GetPosition().z)));
		forceVector = force * NockBackPower;
	}
}

void EnemyBase::NockBack()
{
	if (forceVector.x >= 0.1f && forceVector.x <= -0.1f)
	{
		forceVector = Vector3::Zero;
		return;
	}

	forceVector = forceVector / 2.0f;
	SetPosition(position + forceVector);
}
