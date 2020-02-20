#include "EnemyBase.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "RotateComponent.h"
#include "EnemyWeapon.h"
#include "BombParticleEffect.h"
#include "MainCameraObject.h"
#include "WeaponBase.h"
#include "DamageSquareEffect.h"

const int EnemyBase::HitPointMaxDefault = 3;

/*
@param _pos ���W
@param _size �T�C�Y
@param _enemyType �G�̎�ށ@������Q�Ƃ����b�V���f�[�^��ύX����
*/
EnemyBase::EnemyBase(Vector3 _pos, Vector3 _scale, EnemyType _type) :
	GameObject(),
	hitPoint(HitPointMaxDefault),
	moveDirection(EnemyMoveDirection::right),
	beforeDirection(moveDirection),
	attackObject(nullptr)
{
	SetScale(_scale);
	SetPosition(_pos);
	tag = Tag::EnemyTag;
	//�Փ˔����u�����S���W(�[���͑���)
	Vector3  collisionPos = Vector3(20, 80, 0);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(120, 160, 70), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, collisionPos);
	//���f���̌�����ύX(�f�t�H���g�͐���)
	rotate = new RotateComponent(this);
	rotate->SetRotation(-90, Vector3::UnitX);
	//�G�l�~�[���Ƃ̎��ʎq����ɃA�j���[�V�����N���X�𐶐�
	animComponent = new AnimationEnemyComponent(this, _type);
	animComponent->SetMove(true);
}

EnemyBase::~EnemyBase()
{
}

/*
@fn �h���N���X�̍X�V�֐����ĂсA�̗͂��Ǘ��������ɑ΂��ĉ�]���s��
*/
void EnemyBase::UpdateGameObject(float _deltaTime)
{
	if (hitPoint <= 0)
	{
		//���j���ꂽ�̂Ń��C���J�����̒����ʒu��1F�ύX���Ռ��̂悤�Ɍ�����
		mainCamera->SetViewMatrixLerpObject(Vector3(0, 0, 0), position);
		//�G�N���X���Ƃ̌��j�C�x���g
		DeadCommonEvent();
		return;
	}
	//�G�N���X���Ƃ̍X�V
	UpdateEnemyObject(_deltaTime);

	//�OF�ƌ������قȂ��Ă����ꍇ��]
	if (beforeDirection != moveDirection)
	{
		rotate->SetRotation(180, Vector3::UnitY);
		beforeDirection = moveDirection;
	}
}

/*
@fn �v���C���[�ɍU�����ꂽ�Ƃ��ɁA���b�V���𔭌��������̕���̍U���͂��������h���N���X�̔�e�֐��֓n��
*/
void EnemyBase::OnTriggerEnter(ColliderComponent* _colliderPair)
{
	//�v���C���[�̍U���ɐڐG�����Ƃ�
	if (_colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		int weaponPower = WeaponBase::SearchWeaponPower(_colliderPair->GetId());
		printf("WeaponPower :: %d \n", weaponPower);
		HitPlayerAttack(_colliderPair->GetPosition(), weaponPower);
	}
}

/*
@fn ���S���̃C�x���g
*/
void EnemyBase::DeadCommonEvent()
{
	if (attackObject != nullptr)
	{
		attackObject->SetState(State::Dead);
	}
	SetState(Dead);
	DeadEvent();
	//��������悤�ȃG�t�F�N�g�𐶐�
	Vector3 effectPos = Vector3(position.x, position.y + 50, position.z);
	new BombParticleEffect(effectPos, Vector3(10, 20, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 20, 0));
	new BombParticleEffect(effectPos, Vector3(10, 18, 0));
	new BombParticleEffect(effectPos, Vector3(10, 14, 0));
	new BombParticleEffect(effectPos, Vector3(10, 11, 0));
	new BombParticleEffect(effectPos, Vector3(10, 8, 0));
	new BombParticleEffect(effectPos, Vector3(10, 5, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 18, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 14, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 1, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 8, 0));
	new BombParticleEffect(effectPos, Vector3(-10, 5, 0));
}

