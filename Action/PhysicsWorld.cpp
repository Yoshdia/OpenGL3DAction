#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "PlayerCharacter.h"

PhysicsWorld* PhysicsWorld::physicsWorld = nullptr;

void PhysicsWorld::CreateInstance()
{
	if (!physicsWorld)
	{
		physicsWorld = new PhysicsWorld();
		physicsWorld->MakeNoCollisionPair();
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
		if (collider2->GetState() == State::Dead)
		{
			continue;
		}
		int obj2Id = collider2->GetId();
		if (obj1Id < obj2Id)
		{
			if (CheckDontCollisionPair(collider->GetObjectTag(), collider2->GetObjectTag()) ||
				!collider2->GetDoCollision())
			{
				continue;
			}

			int hit = false;
			AABB obj1(collider->GetPosition(), collider->GetCollisionSize());
			AABB obj2(collider2->GetPosition(), collider2->GetCollisionSize());

			hit = Intersect(obj1, obj2);

			Tag obj1Tag = collider->GetObjectTag();
			Tag obj2Tag = collider2->GetObjectTag();


			if (hit > 0)
			{
				if (obj1Tag == Tag::Camera)
				{
					collider2->SetCollidedCamera();
					if (collider2->GetState() == State::Paused)
					{
						collider2->GetOwner()->SetState(State::Active);
					}
					continue;
				}

				if (obj1Tag == Tag::PlayerTag&&obj2Tag == Tag::GroundTag ||
					obj1Tag == Tag::EnemyTag&&obj2Tag == Tag::GroundTag ||
					obj1Tag == Tag::PlayerTag&&obj2Tag == Tag::ThinGroundFloor)
				{
					collider->GetOwner()->FixCollision(obj1, obj2, obj2Tag);
				}
				else if (obj1Tag == Tag::GroundTag && obj2Tag == Tag::ParticleEffectTag)
				{
					collider2->GetOwner()->FixCollision(obj1, obj2, obj2Tag);
				}

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

void PhysicsWorld::MakeNoCollisionPair()
{
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerTag, Tag::PlayerTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerTag, Tag::PlayerWeaponTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerTag, Tag::PlayerGuardWeaponTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerTag, Tag::EnemyTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerTag, Tag::ParticleEffectTag));

	noCollisionPairs.push_back(std::make_pair(Tag::PlayerWeaponTag, Tag::PlayerWeaponTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerWeaponTag, Tag::PlayerGuardWeaponTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerWeaponTag, Tag::ParticleEffectTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerWeaponTag, Tag::ThinGroundFloor));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerWeaponTag, Tag::EnemyWeaponTag));

	noCollisionPairs.push_back(std::make_pair(Tag::PlayerGuardWeaponTag, Tag::PlayerGuardWeaponTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerGuardWeaponTag, Tag::EnemyTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerGuardWeaponTag, Tag::ParticleEffectTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerGuardWeaponTag, Tag::GroundTag));
	noCollisionPairs.push_back(std::make_pair(Tag::PlayerGuardWeaponTag, Tag::ThinGroundFloor));

	noCollisionPairs.push_back(std::make_pair(Tag::EnemyTag, Tag::EnemyTag));
	noCollisionPairs.push_back(std::make_pair(Tag::EnemyTag, Tag::ParticleEffectTag));
	noCollisionPairs.push_back(std::make_pair(Tag::EnemyTag, Tag::EnemyWeaponTag));

	noCollisionPairs.push_back(std::make_pair(Tag::ParticleEffectTag, Tag::ParticleEffectTag));
	noCollisionPairs.push_back(std::make_pair(Tag::ParticleEffectTag, Tag::EnemyWeaponTag));

	noCollisionPairs.push_back(std::make_pair(Tag::GroundTag, Tag::GroundTag));
	noCollisionPairs.push_back(std::make_pair(Tag::GroundTag, Tag::ThinGroundFloor));

	noCollisionPairs.push_back(std::make_pair(Tag::ThinGroundFloor, Tag::ThinGroundFloor));
	noCollisionPairs.push_back(std::make_pair(Tag::ThinGroundFloor, Tag::EnemyWeaponTag));
}

bool PhysicsWorld::CheckDontCollisionPair(const Tag & lTag, const Tag & rTag)
{
	if (lTag == Tag::null || rTag == Tag::null)
	{
		return false;
	}
	for (auto pair : noCollisionPairs)
	{
		if (lTag == pair.first&&rTag == pair.second)
		{
			return true;
		}
		else if (rTag == pair.first&& lTag == pair.second)
		{
			return true;
		}

	}
	return false;
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
