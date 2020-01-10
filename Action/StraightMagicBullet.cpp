#include "StraightMagicBullet.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"

StraightMagicBullet::StraightMagicBullet(const Vector3 & _shotPosition, const Vector3 & _targetPosition, const int & _waitCount) :
	WeaponBase(_shotPosition, _waitCount, 150, 1, Tag::EnemyWeaponTag, 1, Vector3(10, 10, 10), "Assets/Bike.gpmesh", "Assets/Bike.gpskel")
{
	force = Vector3::Normalize(_targetPosition - _shotPosition);
}

StraightMagicBullet::~StraightMagicBullet()
{
}

void StraightMagicBullet::UpdateWeaponGameObject(float _deltaTime)
{
	SetPosition(position + (force * 2));
}
