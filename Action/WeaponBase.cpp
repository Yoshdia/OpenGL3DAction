#include "WeaponBase.h"
#include "ColliderComponent.h"
#include "RotateComponent.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Skeleton.h"

std::unordered_map<int, int> WeaponBase::weapons;

WeaponBase::WeaponBase(const Vector3 & _pos, const int & _waitCount, const int & _lifeCount, const int & _direction,
	const Tag& _tag, const int& _weaponName, const Vector3 & _colliderSize, const std::string & _meshFileName, const char * _skeletalFileName) :
	GameObject(),
	waitCount(_waitCount),
	lifeCount(_lifeCount),
	activeCount(0)
{
	int dir = _direction == 1 ? 1 : -1;
	direction = dir;
	SetPosition(_pos);
	tag = _tag;
	rotateComponent = new RotateComponent(this);
	colliderComponent = new ColliderComponent(this, 100, _colliderSize, myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
	colliderComponent->SetDoCollision(false);
	skeletalComponent = new SkeletalMeshComponent(this);
	skeletalComponent->SetSkeleton(RENDERER->GetSkeleton(_skeletalFileName));
	skeletalComponent->SetMesh(RENDERER->GetMesh(_meshFileName));
	skeletalComponent->SetVisible(false);
	if (tag == Tag::PlayerWeaponTag)
	{
		weapons.emplace(myObjectId, _weaponName);
	}
}

WeaponBase::~WeaponBase()
{
}

void WeaponBase::UpdateGameObject(float _deltaTime)
{
	if (waitCount <= 0)
	{
		colliderComponent->SetDoCollision(true);
		skeletalComponent->SetVisible(true);
		UpdateWeaponGameObject(_deltaTime);
		activeCount++;
		if (lifeCount <= 0)
		{
			SetState(State::Dead);
		}
		else
		{
			lifeCount--;
		}
	}
	else
	{
		waitCount--;
	}
}

int WeaponBase::SearchWeaponPower(const int & _objectId)
{
	auto iter = weapons.find(_objectId);
	if (iter != weapons.end())
	{
		int name = iter->second;
		return name;
	}
	return 0;
}
