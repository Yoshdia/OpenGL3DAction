#include "LoiteringEnemyBase.h"
#include "WarpPointSearchEnemy.h"
#include "SkeltonObjectChecker.h"
#include "RotateComponent.h"
#include "AnimationEnemyComponent.h"
#include "EnemyWeapon.h"
#include "FloatParticleEffect.h"

const int LoiteringEnemyBase::HitPointMaxDefault = 3;
const int LoiteringEnemyBase::AttackingTimeDefault = 200;
const int LoiteringEnemyBase::HittingTimeDefault = 40;
const float LoiteringEnemyBase::WalkSpeedDefault = 125;
const float LoiteringEnemyBase::ApproachSpeedRatioDefault = 0.8f;
const float LoiteringEnemyBase::SearchRangeDefault = 200;
const float LoiteringEnemyBase::AttackRangeDefault = 75;
const int LoiteringEnemyBase::AttackIntervalCountDefault = 20;

const float LoiteringEnemyBase::Gravity = 550.0f;
const float LoiteringEnemyBase::NockBackPower = 1075.0f;
const float LoiteringEnemyBase::GroundCheckPos = 40.0f;
const int LoiteringEnemyBase::ActionChangeCountMax = 100;
const Vector3 LoiteringEnemyBase::footPos = Vector3(0.0f, -3.0f, 0.0f);
const Vector3 LoiteringEnemyBase::TrackingRange = Vector3(2000.0f, 2000.0f, 2000.0f);
const int LoiteringEnemyBase::TurnWaitCountMax = 2;
const float LoiteringEnemyBase::ForwardDownY = -90.0f;

/*
@param _pos ���W
@param _scale �T�C�Y
@param _type �G�l�~�[�̎��
@sa�@�����͂��ׂ�EnemyBase�ɓn��
*/
LoiteringEnemyBase::LoiteringEnemyBase(Vector3 _pos, Vector3 _scale, EnemyType _type) :
	EnemyBase(_pos, _scale, _type),
	actionChangeCount(0),
	attackingTime(AttackingTimeDefault),
	hittingTime(HittingTimeDefault),
	walkSpeed(WalkSpeedDefault),
	approachSpeedRatio(ApproachSpeedRatioDefault),
	searchRange(SearchRangeDefault),
	attackRange(AttackRangeDefault),
	attackIntervalCountMax(AttackIntervalCountDefault),
	actionName(EnemyActions::walk),
	turnWaitCount(0),
	nockBackForce(Vector3::Zero),
	attackingState(false),
	teleportChargingTime(0),
	attackIntervalCount(0),
	canNotActionTime(0),
	actionChangeCountMax(ActionChangeCountMax),
	warpPositonSearching(false)
{
	hitPoint = HitPointMaxDefault;

	warpSearch = new WarpPointSearchEnemy();
	//InstantiateLoiteringEnemyBase��h���N���X�R���X�g���N�^���ŌĂԂ���
}

/*
@fn �������֐�
@brief �h���N���X���ƂɕύX���s��ꂽ�萔��ʃN���X�ɔ��f�����邽�߂ɕʌɗp��
*/
void LoiteringEnemyBase::InstantiateLoiteringEnemyBase()
{
	//�����̒n�ʔ���
	footChecker = new SkeltonObjectChecker(this, footPos, Vector3(10, 10, 10), Tag::GroundTag);
	//�i�s���������̒n�ʔ���
	forwardDownGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, ForwardDownY, 0), Vector3(10, 10, 10), Tag::GroundTag);
	//�i�s�����̕ǂ𔻕�
	forwardGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, -20, 0), Vector3(10, 10, 10), Tag::GroundTag);
	//�v���C���[��T���A���G�͈�
	findingPlayerCheck = new SkeltonObjectChecker(this, Vector3(searchRange / 1.5f, 5, 0), Vector3(searchRange, 15, 1), Tag::PlayerTag);
	//�v���C���[�𔭌���A�ǐՂ��邽�߂Ƀv���C���[�̍��W���X�V����
	trackingRange = new SkeltonObjectChecker(this, Vector3::Zero, TrackingRange, Tag::PlayerTag);
}

LoiteringEnemyBase::~LoiteringEnemyBase()
{
}

/*
@fn ���̃I�u�W�F�N�g���g���܂킵�����Ƃ��ɌĂ΂�A�p�����[�^������������
@param _pos ���W
@param _hitPoint �̗�
@brief ���MageEnemy�ɏ��������悤�Ɏg�p�����
@sa MageEnemy.h
*/
void LoiteringEnemyBase::SpawnSummoned(const Vector3& _pos, const int& _hitPoint)
{
	//�����̍��W���Z�b�g
	SetPosition(_pos);
	//�X�V��Ԃ��A�N�e�B�u��
	SetState(State::Active);
	//�e�T�u�N���X�̍��W���Z�b�g���S�ăA�N�e�B�u��
	trackingRange->SetPosition(_pos);
	trackingRange->SetState(State::Active);
	footChecker->SetPosition(_pos);
	footChecker->SetState(State::Active);
	forwardDownGroundCheck->SetPosition(_pos);
	forwardDownGroundCheck->SetState(State::Active);
	forwardGroundCheck->SetPosition(_pos);
	forwardGroundCheck->SetState(State::Active);
	findingPlayerCheck->SetPosition(_pos);
	findingPlayerCheck->SetState(State::Active);

	//�����̗̑͂��Z�b�g
	hitPoint = _hitPoint;
	//�s���s���Ԃ�ǉ�
	canNotActionTime = 200;
	//�A�j���[�V�����N���X�̃t���O�����Z�b�g
	animComponent->AllFlagReset();
	//�N���A�j���[�V����
	animComponent->SetSpawn(true);
	//�N���A�j���[�V�����̑��x���Z�b�g
	animComponent->SetSubDuration(0.01f);
	//������Ԃ�ǐՂ�
	actionName = EnemyActions::approach;
	//�U����Ԃ��A�N�e�B�u��
	attackingState = true;
	//�ϐ���̌����Ɗp�x��̌��������킹��(�E�������Ȃ��獶�ɐi�s���邱�Ƃ�����������)
	if (moveDirection == EnemyMoveDirection::right)
	{
		moveDirection = EnemyMoveDirection::left;
		beforeDirection = moveDirection;
		rotate->SetRotation(180, Vector3::UnitY);
	}
}

/*
@fn ���̜p�j�G�l�~�[���ʂ̍X�V�֐�
*/
void LoiteringEnemyBase::UpdateEnemyObject(float _deltaTime)
{
	//�n�ʂƐڐG���Ă��Ȃ��Ƃ��d�͂𓭂�����
	if (footChecker->GetNoTouchingFlag())
	{
		SetPosition(position + Vector3(0, -Gravity * _deltaTime, 0));
	}
	//�m�b�N�o�b�N
	NockBack(_deltaTime);
	//�p�j��U���Ȃǂ̃A�N�V����
	Action(_deltaTime);
	//�h���N���X�̍X�V�֐�
	UpdateLoiteringEnemyObject(_deltaTime);
}

/*
@fn �h���N���X�̍X�V�֐�
*/
void LoiteringEnemyBase::UpdateLoiteringEnemyObject(float _deltaTime)
{
}

void LoiteringEnemyBase::PausingUpdateGameObject()
{
}

/*
@fn �v���C���[�ɍU�����ꂽ
@brief �̗͂����炵�A��U���Ԑ��������ꍇ�U���Ԑ��Ɉڍs�A�m�b�N�o�b�N����e���̓A�N�V�����o���Ȃ��Ȃ�
@param _pairPos �Փˑ���̍��W
@param _power �_���[�W
*/
void LoiteringEnemyBase::HitPlayerAttack(const Vector3& _pairPos, const int& _power)
{
	//��e���̔������J�n
	animComponent->SetStartFlash();
	//�����Ŏ󂯎��������̈З͂ő̗͂����炷
	hitPoint -= _power;
	//�U����ԂłȂ��Ƃ��ɔ�e�����ꍇ�v���C���[�𔭌�������ԂɂȂ�
	if (!attackingState)
	{
		attackingState = true;
		actionName = EnemyActions::approach;
	}
	//�v���C���[�̍U���̕������v�Z��nockBackForce�Ɍv�Z
	double distance = Math::Sqrt((_pairPos.x - position.x) * (_pairPos.x - position.x) + (_pairPos.y - position.y) * (_pairPos.y - position.y));
	//distance�����Ƀm�b�N�o�b�N��������𐳋K��
	Vector3 force = Vector3::Normalize(Vector3((position.x - _pairPos.x), 0, (position.z - _pairPos.z)));
	//�m�b�N�o�b�N�͂��v�Z
	nockBackForce = force * NockBackPower;
	//�d�����łȂ��ꍇ��e���̍d����t�^(��ʂ̍d���𓾂Ă���Ƃ��ɔ�e����Ƒ��s���ł��Ă��܂�����
	if (canNotActionTime < hittingTime)
	{
		canNotActionTime = hittingTime;
	}
}

/*
@fn ���j�C�x���g
*/
void LoiteringEnemyBase::DeadEvent()
{
}

/*
@fn �m�b�N�o�b�N
*/
void LoiteringEnemyBase::NockBack(float _deltaTime)
{
	//nockBackForce�̍ŏ�����ݒ�
	if (nockBackForce.x <= 0.1f && nockBackForce.x >= -0.1f)
	{
		nockBackForce = Vector3::Zero;
		return;
	}
	//�m�b�N�o�b�N
	SetPosition(position + (nockBackForce * _deltaTime));
	//nockBackForce�𔼌�
	nockBackForce = nockBackForce / 2.0f;
}

/*
@fn �A�N�V�����ύX
*/
void LoiteringEnemyBase::ActionChange()
{
	//�A�N�V�����ύX�̑ҋ@���ԃJ�E���g
	if (actionChangeCount > actionChangeCountMax)
	{
		actionChangeCount = 0;
		//�A�N�V�����ύX
		BranchActionChange();
	}
	else
	{
		actionChangeCount++;
	}
}

/*
@fn�A�N�V�������Ƃ̏���
*/
void LoiteringEnemyBase::Action(float _deltaTime)
{
	//�d�����łȂ���
	if (canNotActionTime <= 0)
	{
		//�U����Ԃł��邩
		if (attackingState)
		{
			Attacking(_deltaTime);
		}
		else
		{
			NoAttacking(_deltaTime);
			//��U����Ԃ̂��߁A�s���������_���ŕύX����
			ActionChange();
		}
	}
	else
	{
		//�d��������Ƃ��ɖ_���������邽�ߍł����U���t���O�����Z�b�g
		animComponent->SetAttack(false);
		//�d���J�E���g�����Z�b�g
		canNotActionTime--;
	}
	//�U���C���^�[�o��������
	attackIntervalCount--;
}

/*
@fn ���s���A�N�V�������ύX�����֐�
*/
void LoiteringEnemyBase::BranchActionChange()
{
	//�_�����A���s��ݒ肷�闐��
	int ra = rand() % 6;
	if (ra <= 1)
	{
		//�p�j
		actionName = EnemyActions::walk;
		animComponent->SetMove(true);
	}
	else
	{
		//�_����
		actionName = EnemyActions::noActive;
		animComponent->SetMove(false);
	}
	//�����������_���Ō���
	if ((rand() % 100) < 50)
	{
		moveDirection = EnemyMoveDirection::left;
	}
	else
	{
		moveDirection = EnemyMoveDirection::right;
	}
	//�ړ������ɕύX����������ۂɂ��������������悤�ɍ��W���X�V��������
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
	findingPlayerCheck->SetOffset(Vector3((searchRange)*moveDirection, 0, 0));
}

/*
@fn �U���Ԑ��̏���
*/
void LoiteringEnemyBase::Attacking(float _deltaTime)
{
	//�ǐՑΏۂ̍��W���擾
	Vector3 target = trackingRange->GetColliderPairPosition();
	//�v���C���[�Ƃ�x���W�Ԃ̋������v�Z
	float playerDistance = position.x - target.x;
	//�v���C���[�̈ʒu�Ō�����ύX
	if (playerDistance >= 0)
	{
		moveDirection = EnemyMoveDirection::left;
	}
	else
	{
		moveDirection = EnemyMoveDirection::right;
	}
	//�W�I�Ƃ̍����̍����v�Z
	float heightDistance = Math::Abs(position.y - target.y);
	//���������]���邱�Ƃ����邽�߂��ꂼ���offset���W���X�V����
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
	//��Βl�ɕϊ�
	playerDistance = Math::Abs(playerDistance);
	//�W�I�ɐڋߒ�
	if (actionName == EnemyActions::approach)
	{
		//�ǐՑΏۂƍ����̍���10�ȏ゠���ԂŃJ�E���g��100�i�ނƒǐՑΏۂ�����ȏ㗣�ꂽ�ʒu�Ƀe���|�[�g
		if ((heightDistance > 25 || playerDistance > attackRange * 10) && !warpPositonSearching)
		{
			teleportChargingTime++;
		}
		else
		{
			teleportChargingTime = 0;
		}
		//���W���������łȂ��J�E���g�����ȏ�ɂȂ����Ƃ�
		if (teleportChargingTime > 100 && !warpPositonSearching)
		{
			teleportChargingTime = 0;
			//���[�v�n�_�w��̊J�n
			warpSearch->SetFirstPosition(target, position);
			warpPositonSearching = true;
		}
		//���W��������
		if (warpPositonSearching)
		{
			//���[�v�n�_�w�肪�I��������
			if (warpSearch->GetEndSearch())
			{
				//���[�v�G�t�F�N�g
				new FloatParticleEffect(Vector3(45, 0, 0) + position, Vector3(0, 2, 0));
				new FloatParticleEffect(Vector3(-45, 0, 0) + position, Vector3(0, 2, 0));
				new FloatParticleEffect(Vector3(45, 0, 0) + position, Vector3(0, 2, 0));
				new FloatParticleEffect(Vector3(-45, 0, 0) + position, Vector3(0, 2, 0));
				//�����n�_�Ƀ��[�v
				SetPosition(warpSearch->GetPosition());
				//���[�v�㑦�U���ł��Ȃ��悤�d����ǉ�
				canNotActionTime = 50;
				warpPositonSearching = false;
				teleportChargingTime = 0;
			}
		}
		//�i�s�����ɕǂ����邩||�i�s�����̑����ɒn�ʂ�������
		if (!forwardDownGroundCheck->GetNoTouchingFlag() && !forwardGroundCheck->GetNoTouchingFlag())
		{
			//�U���Ώۂɐڋ߂��� ���V�͂ł��Ȃ�����y�����ɂ͒ǐՂ��Ȃ�
			SetPosition(Vector3::Lerp(position, Vector3(target.x, position.y, target.z), _deltaTime * approachSpeedRatio));
			animComponent->SetMove(true);
		}
		else
		{
			animComponent->SetMove(false);
		}
		//�U���̎˒������܂Őڋ߂�����A�N�V������ύX����
		if (playerDistance < attackRange)
		{
			actionName = EnemyActions::attack;
			animComponent->SetMove(false);
		}
	}
	else
	{
		warpPositonSearching = false;
		//�U���̎˒��������痣�ꂽ��A�N�V������ύX����
		if (playerDistance >= attackRange || heightDistance > 25)
		{
			//�p�j
			actionName = EnemyActions::approach;
			animComponent->SetAttack(false);
			if (teleportChargingTime <= 0)
			{
				animComponent->SetMove(true);
			}
		}
		else if (attackIntervalCount <= 0)
		{
			attackIntervalCount = attackIntervalCountMax;
			animComponent->SetAttack(true);
			animComponent->SetSubDuration(0.016f);
			animComponent->SetMove(false);
			canNotActionTime = attackingTime;
			Attack(_deltaTime);
		}
		else
		{
			animComponent->SetAttack(false);
		}
	}
}

/*
@fn �U�����s���֐�
@sa EnemyWeapon.h
*/
void LoiteringEnemyBase::Attack(float _deltaTime)
{

}
/*
@fn ��U���Ԑ�
*/
void LoiteringEnemyBase::NoAttacking(float _deltaTime)
{
	if (actionName == EnemyActions::walk)
	{
		//���݋󒆂ɂ��Ȃ���
		if (!footChecker->GetNoTouchingFlag())
		{
			//�i�s�����ɕǂ����邩||�i�s�����̑����ɒn�ʂ�������
			if (!forwardDownGroundCheck->GetNoTouchingFlag() && !forwardGroundCheck->GetNoTouchingFlag())
			{
				turnWaitCount++;
			}
			else
			{
				if (turnWaitCount > TurnWaitCountMax)
				{
					turnWaitCount = 0;
					//�ړ������𔽓]
					moveDirection = (EnemyMoveDirection)(moveDirection * (EnemyMoveDirection)-1);
					//�ړ����������]�����̂ł��ꂼ���offset���W���X�V����
					forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
					forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
				}
			}
		}
		//���s
		SetPosition(Vector3((walkSpeed * _deltaTime) * moveDirection, 0, 0) + position);
	}
	else
	{
		SetPosition(position);
		//�������Ȃ�
	}
	//�U���Ώۂ𔭌������Ƃ��ɃA�N�V������ύX����
	if (!findingPlayerCheck->GetNoTouchingFlag())
	{
		actionName = EnemyActions::approach;
		attackingState = true;
		animComponent->SetMove(true);
	}
}
