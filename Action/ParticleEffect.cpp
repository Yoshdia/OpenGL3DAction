#include "ParticleEffect.h"
#include "PhysicsWorld.h"
#include "ParticleComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "ColliderComponent.h"

ParticleEffect::ParticleEffect(Vector3 _pos, Vector3 _velocity, bool _collionForGround) :
	GameObject(),
	collisionForGround(_collionForGround),
	velocity(_velocity),
	lifeCount(15),
	direction(1),
	isCollision(false)
{
	tag = (Tag::ParticleEffectTag);
	direction = _velocity.x > 0 ? 1 : -1;
	SetPosition(_pos);
	ParticleComponent* pa = new ParticleComponent(this);
	pa->SetTextureID(RENDERER->GetTexture("Assets/Image/16.png")->GetTextureID());
	pa->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	pa->SetScale(10);
	ColliderComponent* col = new ColliderComponent(this, 100, Vector3(40, 40, 40), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
}

ParticleEffect::~ParticleEffect()
{
}

void ParticleEffect::UpdateGameObject(float _deltaTime)
{
	SetPosition(position + velocity);

	//velocity.y = -15;
	//SetState(Dead);

	if (!isCollision)
	{
		velocity.y -= 100 * _deltaTime;
	}
	else
	{
		if (lifeCount > 0)
		{
			lifeCount--;
		}
		else
		{
			state = Dead;
		}

	}


	if (direction == 0)
	{

	}
	else if (direction == 1)
	{
		//if (velocity.x >= 2.0f * direction)
		//{
		//	velocity.x = velocity.x / (direction * 1.3f);
		//}
	}
	else
	{
		//if (velocity.x <= 2.0f * direction)
		//{
		//	velocity.x = velocity.x / (-direction * 1.3f);
		//}
	}

}

void ParticleEffect::FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag)
{
	if (collisionForGround)
	{
		Vector3 ment = Vector3(0, 0, 0);
		calcCollisionFixVec(myAABB, pairAABB, ment);
		int i = 0;
		//SetPosition(GetPosition() + (ment));
		//velocity += ment;
	}
}

void ParticleEffect::OnTriggerEnter(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::GroundTag)
	{
		//velocity.y = 0;
		velocity = Vector3::Zero;
		isCollision = true;
	}
}
