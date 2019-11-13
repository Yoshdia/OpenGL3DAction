#include "EnemyBase.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "FootSole.h"
#include "ForwardGroundCheck.h"

const float EnemyBase::NockBackPower = 30;
const float EnemyBase::GroundCheckPos = 40;

EnemyBase::EnemyBase(const std::string& meshName) :
	GameObject(),
	moveDirection(EnemyMoveDirection::right),
	actionChangeCount(0),
	defaultCountMax(500),
	actionChangeCountMax(defaultCountMax)
{
	tag = Tag::EnemyTag;
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh(meshName));

	std::function<void(ColliderComponent*)>  Enter = std::bind(&EnemyBase::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&EnemyBase::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, Enter, Stay, tag, Vector3(0, 0, 0));
	footSole = new FootSole(this);

	forwardDownGroundCheck = new ForwardGroundCheck(this, Vector3(GroundCheckPos, -30, 0),Vector3(1,1,1),Tag::GroundTag);
	forwardGroundCheck = new ForwardGroundCheck(this, Vector3(GroundCheckPos, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
	findingPlayerCheck = new ForwardGroundCheck(this, Vector3(100, 1, 0), Vector3(200, 1, 1), Tag::PlayerTag);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::UpdateGameObject(float _deltaTime)
{
	UpdateEnemyObject(_deltaTime);
	NockBack();

	if (footSole->GetGroundFlag() == true)
	{
		SetPosition(position + Vector3(0, -2, 0));
	}

	
	if (!findingPlayerCheck->GetGround())
	{
		actionName = EnemyActions::foundMove;
		findingPlayerCheck->ResetGroundFlag(true);
	}
	findingPlayerCheck->SetCheckPos(Vector3(100 * moveDirection, 0, 0));
	actionChangeCount++;
	ActionChange();
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

void EnemyBase::ActionChange()
{
	if (actionChangeCount > actionChangeCountMax)
	{
		actionChangeCount = 0;
		BranchActionChange();
		ShuffleCountMax();
	}
	else
	{
		actionChangeCount++;
	}
}
