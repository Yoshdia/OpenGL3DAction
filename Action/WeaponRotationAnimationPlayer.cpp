#include "WeaponRotationAnimationPlayer.h"
#include "MeshComponent.h"
#include "Renderer.h"

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
	case(0):addDistance.x += 1; break;
	case(1):addDistance.x += 2; break;
	case(2):addDistance.x += 3; break;
	}
	targetPos = pos + addDistance;
}


WeaponRotationAnimationPlayer::~WeaponRotationAnimationPlayer()
{
}

void WeaponRotationAnimationPlayer::UpdateGameObject(float _deltaTime)
{
	Rotate();
	Vector3 ad= Vector3::Lerp(position, targetPos, 1);
	SetPosition(ad + position);
}

void WeaponRotationAnimationPlayer::Rotate()
{
	float radian = Math::ToRadians(50);
	Quaternion rot = GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}
