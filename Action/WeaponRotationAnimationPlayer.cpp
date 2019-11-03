#include "WeaponRotationAnimationPlayer.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"

WeaponRotationAnimationPlayer::WeaponRotationAnimationPlayer(const Vector3& pos, const int& moveDistanceStage)
{
	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
	SetScale(0.8f);
	rad = 0;
	SetPosition(pos);
	Vector3 addDistance = Vector3(0, 0, 0);
	switch (moveDistanceStage)
	{
	case(0):addDistance.x += 60; break;
	case(1):addDistance.x += 120; break;
	case(2):addDistance.x += 180; break;
	}
	targetPos = pos + addDistance;
	rotateSpeed = 50;
	rotateSpeedSub = 0.45;
	tag = Tag::PlayerWeaponTag;
	std::function<void(ColliderComponent*)>  Enter = std::bind(&WeaponRotationAnimationPlayer::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&WeaponRotationAnimationPlayer::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, Enter, Stay, tag, Vector3(0, 0, 0));
}


WeaponRotationAnimationPlayer::~WeaponRotationAnimationPlayer()
{
}

void WeaponRotationAnimationPlayer::UpdateGameObject(float _deltaTime)
{
    Rotate();
	Vector3 add = Vector3((targetPos.x - position.x) * 0.05f,0,0);
	SetPosition(position+add);
}

void WeaponRotationAnimationPlayer::Rotate()
{
	float radian = Math::ToRadians(rotateSpeed);
	Quaternion rot = GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
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
