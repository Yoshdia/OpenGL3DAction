#include "EnemyWeapon.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "Game.h"
#include "MeshComponent.h"

/*
@param _pos ���W
@param _size �T�C�Y
@param _lifeCount ���莞��
@param _waitTime �U�������܂őҋ@����
*/
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

/*
@fn �������Ԃ��������������[���ɂȂ��������̃I�u�W�F�N�g�̍X�V���~�߂�
*/
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
	//�ҋ@���Ԃ����炵������
	if (waitTime < 0)
	{
		//�������Ԃ����炵������
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
