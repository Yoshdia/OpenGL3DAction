#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "PlayerCharacter.h"

PhysicsWorld* PhysicsWorld::physicsWorld = nullptr;

void PhysicsWorld::CreateInstance()
{
	if (!physicsWorld)
	{
		physicsWorld = new PhysicsWorld();
	}
}

void PhysicsWorld::DeleteInstance()
{
	delete physicsWorld;
	physicsWorld = nullptr;
}

void PhysicsWorld::AddCollider(ColliderComponent * collider)
{
	colliders.emplace_back(collider);
}

void PhysicsWorld::RemoveCollider(ColliderComponent * collider)
{
	auto iter = std::find(colliders.begin(), colliders.end(), collider);
	if (iter != colliders.end())
	{
		std::iter_swap(iter, colliders.end() - 1);
		colliders.pop_back();
	}
}

void PhysicsWorld::Collision(ColliderComponent * collider)
{
	int obj1Id = collider->GetId();
	for (auto collider2 : colliders)
	{
		int obj2Id = collider2->GetId();
		if (obj1Id < obj2Id)
		{
			int hit = false;
			AABB obj1(collider->GetPosition(), collider->GetCollisionSize());
			AABB obj2(collider2->GetPosition(), collider2->GetCollisionSize());

			hit = Intersect(obj1, obj2);

			Tag obj1Tag = collider->GetObjectTag();
			Tag obj2Tag = collider2->GetObjectTag();


			if (hit > 0)
			{
				if (obj1Tag == Tag::PlayerTag&&obj2Tag == Tag::GroundTag)
				{
					dynamic_cast<PlayerCharacter*> (collider->GetOwner())->FixCollision(obj1,obj2);
				}

				printf("\nnice");
				collider->OnCollision(collider2);
				collider2->OnCollision(collider);
			}
		}
		else
		{
			continue;
		}

	}
}

void calcCollisionFixVec(const AABB & movableBox, const AABB & fixedBox, Vector3 & calcFixVec)
{
	calcFixVec = Vector3(0, 0, 0);
	float dx1 = fixedBox.min.x - movableBox.max.x;
	float dx2 = fixedBox.max.x - movableBox.min.x;
	float dy1 = fixedBox.min.y - movableBox.max.y;
	float dy2 = fixedBox.max.y - movableBox.min.y;
	float dz1 = fixedBox.min.z - movableBox.max.z;
	float dz2 = fixedBox.max.z - movableBox.min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		calcFixVec.y = dy;
	}
	else
	{
		calcFixVec.z = dz;
	}

}
