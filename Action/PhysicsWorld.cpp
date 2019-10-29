#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "Collision.h"

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

			if (hit > 0)
			{
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
