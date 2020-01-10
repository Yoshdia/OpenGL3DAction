#include "HammerWeapon.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "RotateComponent.h"
#include "SkeletalMeshComponent.h"
#include "Skeleton.h"

HammerWeapon::HammerWeapon(const Vector3 & _pos, const int & number, const int & _direction, const int& _lifeCount, const int & _waitTime)
	:GameObject(),
	waitTime(_waitTime),
	lifeCount(_lifeCount)
{
	SetPosition(_pos + Vector3(((50 * number)*_direction), 0, 0));
	colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));
	colliderComponent->SetDoCollision(false);

	skeletal = new SkeletalMeshComponent(this);
	skeletal->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Weapon/SK_Forging_ForgeHammer01.gpskel"));
	skeletal->SetMesh(RENDERER->GetMesh("Assets/Model/Weapon/SK_Forging_ForgeHammer01.gpmesh"));
	skeletal->SetVisible(false);

	rotate = new RotateComponent(this);

	if (_direction == 1)
	{

		rotate->SetRotation(90, Vector3::UnitY);
		rotate->SetRotation(150, Vector3::UnitZ);
		rotateSpeed = -1;
	}
	else
	{
		rotate->SetRotation(-90, Vector3::UnitY);
		rotate->SetRotation(-150, Vector3::UnitZ);
		rotateSpeed = 1;
	}
		rotate->SetRotation(90, Vector3::UnitX);

}

HammerWeapon::~HammerWeapon()
{
}

void HammerWeapon::UpdateGameObject(float _deltaTime)
{
	if (waitTime <= 0)
	{
		skeletal->SetVisible(true);
		colliderComponent->SetDoCollision(true);
		rotate->SetRotation(rotateSpeed, Vector3::UnitZ);
		if (waitTime == -15)
			rotateSpeed *= 49;
		if (waitTime == -18)
			rotateSpeed /= 35;
		if (lifeCount <= 0)
		{
			SetState(State::Dead);
		}
		else
		{
			lifeCount--;
		}
	}
	if (waitTime >= -1000)
	{
		waitTime--;
	}
}
