#include "BombParticleEffect.h"
#include "ColliderComponent.h"
#include "PhysicsWorld.h"

BombParticleEffect::BombParticleEffect(const Vector3& _pos, const Vector3& _velocity, const bool& _collisionForGround) :
	ParticleEffectBase(_pos, _velocity,75, "Assets/Image/16.png"),
	collisionForGround(_collisionForGround)
{
	tag = (Tag::ParticleEffectTag);
	ColliderComponent* col = new ColliderComponent(this, 100, Vector3(40, 40, 40), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

}


BombParticleEffect::~BombParticleEffect()
{
}



void BombParticleEffect::OnTriggerEnter(ColliderComponent * colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::GroundTag)
	{
		//velocity = Vector3::Zero;
		velocity.y *= -1;
		velocity=velocity * 0.8f;
		//isCollision = true;
	}
}

void BombParticleEffect::UpdateParticleObject(float _deltaTime)
{
		velocity.y -= 100 * _deltaTime;
		LifeCountDown();
}
