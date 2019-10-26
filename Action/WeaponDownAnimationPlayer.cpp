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

//const Vector3 corner = Vector3(-15, 0, 0);

void WeaponDownAnimationPlayer::UpdateGameObject(float _deltaTime)
{
	//SetPosition(Vector3::Lerp(Vector3(0, 0, 0), Vector3(10, 10, 10), 0.1));
	//Vector3 cornerPos = (corner* (GetForward()*-1)) + GetPosition();

	//Matrix4 nowMatrix = Matrix4::CreateScale(GetScale());
	//nowMatrix *= Matrix4::CreateFromQuaternion(rotation);
	//nowMatrix *= Matrix4::CreateTranslation(GetPosition() - cornerPos);

	////Vector3 matrixPos = Vector3::Transform(Vector3::UnitY, nowMatrix);

	//Quaternion rooo = Quaternion::MatrixToQuaternion(nowMatrix);
	//float radian = Math::ToRadians(rad+=0.5f);
	//Quaternion rot = rooo;
	//Quaternion inc(Vector3::UnitZ, radian);
	//Quaternion target = Quaternion::Concatenate(rot, inc);

	//nowMatrix = Matrix4::CreateScale(GetScale());
	//nowMatrix *= Matrix4::CreateFromQuaternion(target);
	//nowMatrix *= Matrix4::CreateTranslation(-1*(GetPosition() - cornerPos));
	//rooo = Quaternion::MatrixToQuaternion(nowMatrix);
	//SetPosition(Vector3::Transform(Vector3::UnitZ, rooo));
	//SetRotation(rooo);
	//SetRotation(target);

	float radian = Math::ToRadians(50);
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