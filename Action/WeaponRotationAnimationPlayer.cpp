#include "WeaponRotationAnimationPlayer.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "RotateComponent.h"

WeaponRotationAnimationPlayer::WeaponRotationAnimationPlayer(const Vector3& pos, const int& _direction, const int& _moveDistanceStage) :
	rotateSpeed(50),
	rotateSpeedSub(0.45f),
	direction(_direction)
{
	SetScale(0.5f);
	SetPosition(pos);
	tag = Tag::PlayerWeaponTag;

	Vector3 addDistance = Vector3(0, 0, 0);
	switch (_moveDistanceStage)
	{
	case(0):addDistance.x += 60; break;
	case(1):addDistance.x += 120; break;
	default:addDistance.x += 180; break;
	}
	targetPos = pos + (addDistance*direction);

	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Weapon/SK_Blunt_SpikedClub.gpmesh"));
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));
	rotateComponent = new RotateComponent(this);
	rotateComponent->SetRotation(90, Vector3::UnitY);

	if (_direction == 1)
	{
		rotateComponent->SetRotation(180, Vector3::UnitX);
	}
	rotateDirection = _direction == 1 ? -1 : 1;
}

WeaponRotationAnimationPlayer::~WeaponRotationAnimationPlayer()
{
}

void WeaponRotationAnimationPlayer::UpdateGameObject(float _deltaTime)
{
	Rotate();
	Vector3 add = Vector3((targetPos.x - position.x) * 0.05f, 0, 0);
	SetPosition(position + add);
}

void WeaponRotationAnimationPlayer::Rotate()
{
	rotateComponent->SetRotation(rotateSpeed*rotateDirection, Vector3::UnitZ);
	if (rotateSpeed < 3)
	{
		rotateSpeedSub = 0.1f;
	}
	if (rotateSpeed <= 0)
	{
		SetState(State::Dead);
	}
	rotateSpeed -= rotateSpeedSub;
}
