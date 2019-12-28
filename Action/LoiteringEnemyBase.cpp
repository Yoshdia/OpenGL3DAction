#include "LoiteringEnemyBase.h"
#include "WarpPointSearchEnemy.h"
#include "SkeltonObjectChecker.h"
#include "RotateComponent.h"
#include "AnimationEnemyComponent.h"
#include "EnemyWeapon.h"
const int LoiteringEnemyBase::HitPointMax = 3;
const float LoiteringEnemyBase::AttackingTime = 200;
const float LoiteringEnemyBase::HittingTime = 40;
const float LoiteringEnemyBase::WalkSpeed = 125;
const float LoiteringEnemyBase::ApproachSpeedRatio = 0.8f;
const float LoiteringEnemyBase::SearchRange = 200;
const float LoiteringEnemyBase::AttackRange = 75;
const int LoiteringEnemyBase::AttackIntervalCount = 20;

const float LoiteringEnemyBase::Gravity = 500.0f;
const float LoiteringEnemyBase::NockBackPower = 1075.0f;
const float LoiteringEnemyBase::GroundCheckPos = 40;
const int LoiteringEnemyBase::ActionChangeCountMax = 100;
const Vector3 LoiteringEnemyBase::footPos = Vector3(0, -15, 0);
const Vector3 LoiteringEnemyBase::TrackingRange = Vector3(1000, 1000, 1000);
const int LoiteringEnemyBase::TurnWaitCountMax = 2;
const float LoiteringEnemyBase::ForwardDownY = -90;

LoiteringEnemyBase::LoiteringEnemyBase(Vector3 _pos, Vector3 _scale, EnemyType _type) :
	EnemyBase(_pos, _scale,_type),
	actionChangeCount(0),
	attackingTime(AttackingTime),
	hittingTime(HittingTime),
	walkSpeed(WalkSpeed),
	approachSpeedRatio(ApproachSpeedRatio),
	searchRange(SearchRange),
	attackIntervalCountMax(AttackIntervalCount),
	attackRange(AttackRange),
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
	hitPoint = HitPointMax;
	
	warpSearch = new WarpPointSearchEnemy();
	//InstantiateLoiteringEnemyBase��h���N���X�R���X�g���N�^���ŌĂԂ���
}

void LoiteringEnemyBase::InstantiateLoiteringEnemyBase()
{
	footChecker = new SkeltonObjectChecker(this, footPos, Vector3(1, 1, 1), Tag::GroundTag);
	forwardDownGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, ForwardDownY, 0), Vector3(1, 1, 1), Tag::GroundTag);
	forwardGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
	findingPlayerCheck = new SkeltonObjectChecker(this, Vector3(searchRange / 2, 5, 0), Vector3(searchRange, 15, 1), Tag::PlayerTag);
	trackingRange = new SkeltonObjectChecker(this, Vector3::Zero, TrackingRange, Tag::PlayerTag);
}

LoiteringEnemyBase::~LoiteringEnemyBase()
{
}

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
	UpdateLoiteringEnemyObject(_deltaTime);
}

void LoiteringEnemyBase::UpdateLoiteringEnemyObject(float _deltaTime)
{
}

void LoiteringEnemyBase::HitPlayerAttack(const Vector3& _pairPos)
{
	//�v���C���[�̍U���̕������v�Z��nockBackForce�Ɍv�Z
	double distance = Math::Sqrt((_pairPos.x - position.x) * (_pairPos.x - position.x) + (_pairPos.y - position.y) * (_pairPos.y - position.y));
	Vector3 force = Vector3::Normalize(Vector3((position.x - _pairPos.x), 0, (position.z - _pairPos.z)));
	nockBackForce = force * NockBackPower;
	canNotActionTime = hittingTime;
}

void LoiteringEnemyBase::DeadEvent()
{
}

void LoiteringEnemyBase::NockBack(float _deltaTime)
{
	//nockBackForce�̍ŏ�����ݒ�
	if (nockBackForce.x <= 0.1f && nockBackForce.x >= -0.1f)
	{
		nockBackForce = Vector3::Zero;
		return;
	}
	SetPosition(position + (nockBackForce*_deltaTime));
	//nockBackForce�𔼌�
	nockBackForce = nockBackForce / 2.0f;
}



void LoiteringEnemyBase::ActionChange()
{
	if (actionChangeCount > actionChangeCountMax)
	{
		actionChangeCount = 0;
		BranchActionChange();
		ShuffleCountMax();
	}
	else
	{
		actionChangeCount++;
	}
}

void LoiteringEnemyBase::Action(float _deltaTime)
{
	if (canNotActionTime <= 0)
	{
		if (attackingState)
		{
			Attacking(_deltaTime);
		}
		else
		{
			NoAttacking(_deltaTime);
			ActionChange();
		}
	}
	else
	{
		animComponent->SetAttack(false);
		canNotActionTime--;
	}
	attackIntervalCount--;
}

void LoiteringEnemyBase::BranchActionChange()
{
	//�_�����A���s��ݒ肷�闐��
	int ra = rand() % 6;
	if (ra <= 1)
	{
		actionName = EnemyActions::walk;
		animComponent->SetMove(true);
	}
	else
	{
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
	//�ړ������ɕύX����������ۂɂ���������������悤�ɍ��W���X�V��������
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
	findingPlayerCheck->SetOffset(Vector3((searchRange)*moveDirection, 0, 0));
}

void LoiteringEnemyBase::ShuffleCountMax()
{
}

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
	float heightDistance = Math::Abs(position.y - target.y);
	//���������]���邱�Ƃ����邽�߂��ꂼ���offset���W���X�V����
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
	//��Βl�ɕϊ�
	playerDistance = Math::Abs(playerDistance);

	if (actionName == EnemyActions::approach)
	{
		//�ǐՑΏۂƍ����̍���10�ȏ゠���ԂŃJ�E���g��100�i�ނƒǐՑΏۂ�����ȏ㗣�ꂽ�ʒu�Ƀe���|�[�g

		if( (heightDistance > 25 || playerDistance > attackRange) && !warpPositonSearching)
		{
			teleportChargingTime++;
		}
		else
		{
			teleportChargingTime = 0;
		}
		if (teleportChargingTime > 100 && !warpPositonSearching)
		{
			teleportChargingTime = 0;
			//���[�v�n�_�w��̊J�n
			warpSearch->SetFirstPosition(target, position);
			warpPositonSearching = true;
		}
		if (warpPositonSearching)
		{
			//���[�v�n�_�w�肪�I��������
			if (warpSearch->GetEndSearch())
			{
				//���[�v�n�_�Ƀ��[�v
				SetPosition(warpSearch->GetPosition());
				warpPositonSearching = false;
				teleportChargingTime = 0;
			}
		}
		//�i�s�����ɕǂ����邩||�i�s�����̑����ɒn�ʂ�������
		if (!forwardDownGroundCheck->GetNoTouchingFlag() && forwardGroundCheck->GetNoTouchingFlag())
		{
			//�U���Ώۂɐڋ߂��� ���V�͂ł��Ȃ�����y�����ɂ͒ǐՂ��Ȃ�
			SetPosition(Vector3::Lerp(position, Vector3(target.x, position.y, target.z), _deltaTime * approachSpeedRatio));


			//�U���̎˒������܂Őڋ߂�����A�N�V������ύX����
			if (playerDistance < attackRange)
			{
				actionName = EnemyActions::attack;
				animComponent->SetMove(false);
			}
			animComponent->SetMove(true);

		}
		else
		{
			animComponent->SetMove(false);
		}
	}
	else
	{
		warpPositonSearching = false;
		//�U���̎˒��������痣�ꂽ��A�N�V������ύX����
		if (playerDistance >= attackRange|| heightDistance>25)
		{
			actionName = EnemyActions::approach;

			animComponent->SetAttack(false);
			animComponent->SetMove(true);

		}
		else if (attackIntervalCount <= 0)
		{
			attackIntervalCount = attackIntervalCountMax;
			animComponent->SetAttack(true);
			canNotActionTime = attackingTime;
			printf("%d[Attack!]\n", gameObjectId);
			Attack(_deltaTime);
		}
		else
		{
			animComponent->SetAttack(false);
		}
	}
}

void LoiteringEnemyBase::Attack(float _deltaTime)
{

}

void LoiteringEnemyBase::NoAttacking(float _deltaTime)
{
	if (actionName == EnemyActions::walk)
	{
		//���݋󒆂ɂ��Ȃ���
		if (!footChecker->GetNoTouchingFlag())
		{
			//�i�s�����ɕǂ����邩||�i�s�����̑����ɒn�ʂ�������
			if (forwardDownGroundCheck->GetNoTouchingFlag() || !forwardGroundCheck->GetNoTouchingFlag())
			{
				if (turnWaitCount > TurnWaitCountMax)
				{
					turnWaitCount = 0;
					//�ړ������𔽓]
					moveDirection = (EnemyMoveDirection)(moveDirection * (EnemyMoveDirection)-1);
					//�ړ����������]�����̂ł��ꂼ���offset���W���X�V����
					forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
					forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
					printf("%f,%f\n", forwardDownGroundCheck->GetPosition().x, forwardGroundCheck->GetPosition().x);
				}
			}
			else
			{
				turnWaitCount++;
			}
		}
		//���s
		SetPosition(Vector3((walkSpeed * _deltaTime) * moveDirection, 0, 0) + position);
	}
	else
	{
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