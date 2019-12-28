#include "ThrowWeapon.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"


ThrowWeapon::ThrowWeapon(const Vector3& _pos, const int& _direction,const Tag& _tag) :
	lifeCount(240),
	direction(_direction),
	velocity(Vector3::Zero),
	collided(false)
{
	SetPosition(_pos);
	tag = _tag;
	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 5, 5), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

	velocity.x = 30 * direction;
	velocity.y = 4;
}


ThrowWeapon::~ThrowWeapon()
{
}

void ThrowWeapon::UpdateGameObject(float _deltaTime)
{
	if (!collided)
	{
		velocity.y -= (34.375f*_deltaTime);
		SetPosition(position + velocity);
	}
		if (lifeCount < 0)
		{
			lifeCount = 0;
			SetState(State::Dead);
		}
		else
		{
			lifeCount--;
		}
}

void ThrowWeapon::OnTriggerEnter(ColliderComponent * _pair)
{
	if (_pair->GetObjectTag() == Tag::GroundTag)
	{
		collided = true;
	}
}
