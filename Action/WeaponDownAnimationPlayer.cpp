#include "WeaponDownAnimationPlayer.h"
#include "MeshComponent.h"
#include "Renderer.h"


WeaponDownAnimationPlayer::WeaponDownAnimationPlayer(const Vector3& pos)
{
	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
	SetScale(0.8f);
	rad = 0;
	SetPosition(pos);
}


WeaponDownAnimationPlayer::~WeaponDownAnimationPlayer()
{
}

const Vector3 corner = Vector3(-5, 0, 0);

void WeaponDownAnimationPlayer::UpdateGameObject(float _deltaTime)
{
	Vector3 cornerPos = (corner* (GetForward()*-1)) + GetPosition();

	//Matrix4 nowMatrix= /*GetPosition() - cornerPos*/CreateWorldTransForm~~~~;

	float radian = Math::ToRadians(rad++);
	Quaternion rot = GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

//回転中心座標を宣言
//回転中心座標から原点の距離を求める
//回転中心が原点に来るように移動させる
//回転			↑
//一つ手前の移動量を戻す



//float radian = Math::ToRadians(rad++);
//Quaternion rot = GetRotation();
//Quaternion inc(Vector3::UnitZ, radian);
//Quaternion target = Quaternion::Concatenate(rot, inc);
//SetRotation(target);