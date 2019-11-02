#include "ColliderComponent.h"
#include "GameObject.h"
#include "PhysicsWorld.h"

ColliderComponent::ColliderComponent(GameObject * owner, int updateOrder, Vector3 size, int objectId, std::function<void(ColliderComponent*)>TriggerEnter, std::function<void(ColliderComponent*)>TriggerStay, Tag tag) :
	Component(owner, updateOrder)
	, size(size)
	, colliderPos(Vector3(0,0,0))
{
	OnTriggerEnter = TriggerEnter;
	OnTriggerStay = TriggerStay;
	PhysicsWorld::GetInstance()->AddCollider(this);
}

ColliderComponent::ColliderComponent(GameObject * owner, int updateOrder, Vector3 size, int objectId, std::function<void(ColliderComponent*)>TriggerEnter, std::function<void(ColliderComponent*)> TriggerStay, Tag tag, Vector3 colliderPos) :
	Component(owner, updateOrder)
	, size(size)
	, colliderPos(colliderPos)
{
	OnTriggerEnter = TriggerEnter;
	OnTriggerStay = TriggerStay;
	PhysicsWorld::GetInstance()->AddCollider(this);
}

ColliderComponent::~ColliderComponent()
{
	PhysicsWorld::GetInstance()->RemoveCollider(this);
}

void ColliderComponent::OnCollision(ColliderComponent* colliderParter)
{
	CollisionState state = CollisionState::Enter;
	//前Fで同じオブジェクトと接触していた場合StateをStayへ変更させる
	auto iter = hadCollision.find(colliderParter);
	if (iter != hadCollision.end())
	{
		state = CollisionState::Stay;
	}
	//現Fで接触しているリストに挿入
	isCollision.emplace(colliderParter, state);
}

void ColliderComponent::Update(float deltaTime)
{
	CollisionReaction(deltaTime);

	hadCollision.clear();
	hadCollision = isCollision;
	isCollision.clear();

	PhysicsWorld::GetInstance()->Collision(this);
}

float ColliderComponent::GetScale()
{
	return owner->GetScale();
}

Vector3 ColliderComponent::GetPosition()
{
	return owner->GetPosition() + colliderPos;
}

int ColliderComponent::GetId()
{
	return owner->GetObjectId();
}

void ColliderComponent::CollisionReaction(float deltaTime)
{
	//接触したオブジェクト達との接触状態をもとに親GameObjectのリアクション関数に接触相手のTagを渡す
	for (auto iter : isCollision)
	{
		switch (iter.second)
		{
		case(CollisionState::Enter):
			OnTriggerEnter(iter.first);
			OnTriggerStay(iter.first);
			break;
		case(CollisionState::Stay):
			OnTriggerStay(iter.first);

			break;
		}
	}
}

Tag ColliderComponent::GetObjectTag()
{
	return owner->GetTag();
}


