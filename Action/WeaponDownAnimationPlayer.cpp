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

//��]���S���W��錾
//��]���S���W���猴�_�̋��������߂�
//��]���S�����_�ɗ���悤�Ɉړ�������
//��]			��
//���O�̈ړ��ʂ�߂�



//float radian = Math::ToRadians(rad++);
//Quaternion rot = GetRotation();
//Quaternion inc(Vector3::UnitZ, radian);
//Quaternion target = Quaternion::Concatenate(rot, inc);
//SetRotation(target);