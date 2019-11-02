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
	//�OF�œ����I�u�W�F�N�g�ƐڐG���Ă����ꍇState��Stay�֕ύX������
	auto iter = hadCollision.find(colliderParter);
	if (iter != hadCollision.end())
	{
		state = CollisionState::Stay;
	}
	//��F�ŐڐG���Ă��郊�X�g�ɑ}��
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
	//�ڐG�����I�u�W�F�N�g�B�Ƃ̐ڐG��Ԃ����ƂɐeGameObject�̃��A�N�V�����֐��ɐڐG�����Tag��n��
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


