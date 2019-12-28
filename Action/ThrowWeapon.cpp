#include "ThrowWeapon.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"


ThrowWeapon::ThrowWeapon(const Vector3& _pos, const int& _direction, const int& _waitTime, const Tag& _tag) :
	lifeCount(240),
	direction(_direction),
	velocity(Vector3::Zero),
	collided(false),
	waitTime(_waitTime)
{
	SetPosition(_pos);
	tag = _tag;
	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
	meshComponent->SetVisible(false);
	colliderComponent = new ColliderComponent(this, 100, Vector3(50, 5, 5), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));
	colliderComponent->SetDoCollision(false);

	velocity.x = 30 * direction;
	velocity.y = 4;
}


ThrowWeapon::~ThrowWeapon()
{
}

void ThrowWeapon::UpdateGameObject(float _deltaTime)
{
	if (waitTime <= 0)
	{
		meshComponent->SetVisible(true);
		colliderComponent->SetDoCollision(true);
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
	else
	{
		waitTime--;
	}
}

void ThrowWeapon::OnTriggerEnter(ColliderComponent * _pair)
{
	if (_pair->GetObjectTag() == Tag::GroundTag)
	{
		collided = true;
	}
}
