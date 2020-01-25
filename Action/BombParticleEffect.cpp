#include "BombParticleEffect.h"
#include "ColliderComponent.h"
#include "PhysicsWorld.h"

BombParticleEffect::BombParticleEffect(const Vector3& _pos, const Vector3& _velocity, const bool& _collisionForGround) :
	ParticleEffectBase(_pos, _velocity,20, "Assets/Image/16.png"),
	collisionForGround(_collisionForGround),
	isCollision(false)
{
	tag = (Tag::ParticleEffectTag);
	ColliderComponent* col = new ColliderComponent(this, 100, Vector3(40, 40, 40), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

}


BombParticleEffect::~BombParticleEffect()
{
}

void BombParticleEffect::FixCollision(const AABB & myAABB, const AABB & pairAABB, const Tag & _pairTag)
{
	if (collisionForGround)
	{
		if (!isCollision)
		{
			Vector3 ment = Vector3(0, 0, 0);
			calcCollisionFixVec(myAABB, pairAABB, ment);
			SetPosition(GetPosition() + (ment));
		}
		else
		{
		}
	}
}

void BombParticleEffect::OnTriggerEnter(ColliderComponent * colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::GroundTag)
	{
		velocity = Vector3::Zero;
		isCollision = true;
	}
}

void BombParticleEffect::UpdateParticleObject(float _deltaTime)
{
	if (!isCollision)
	{
		velocity.y -= 100 * _deltaTime;

	}
	else
	{
		LifeCountDown();
	}
}
