#include "EnemyWeapon.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "Game.h"
#include "MeshComponent.h"

EnemyWeapon::EnemyWeapon() :
	GameObject(),
	lifeCount(100)
{
	tag = Tag::EnemyWeaponTag;
	collisionComp = new ColliderComponent(this, 100, Vector3(1, 1, 1), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/collisionMask.gpmesh"));
}

EnemyWeapon::EnemyWeapon(Vector3 _pos, Vector3 _size, int lifeCount, int _waitTime) :
	GameObject(),
	lifeCount(lifeCount),
	waitTime(_waitTime)
{
	tag = Tag::EnemyWeaponTag;
	SetPosition(_pos);
	collisionComp = new ColliderComponent(this, 100, _size, gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
	collisionComp->SetDoCollision(false);
	SetScale(_size);
	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/collisionMask.gpmesh"));
	meshComponent->SetVisible(false);
}


EnemyWeapon::~EnemyWeapon()
{
}

void EnemyWeapon::UpdateGameObject(float _deltaTime)
{
	if (Game::debug&&lifeCount > 0 && waitTime < 0)
	{
		meshComponent->SetVisible(true);
	}
	else
	{
		meshComponent->SetVisible(false);

	}
	if (waitTime < 0)
	{
		if (lifeCount > 0)
		{
			lifeCount--;
			collisionComp->SetDoCollision(true);
		}
		else
		{
			SetState(Dead);
		}
	}
	else
	{
		waitTime--;
	}
}
