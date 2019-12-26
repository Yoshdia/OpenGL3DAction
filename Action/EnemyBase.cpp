#include "EnemyBase.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "SkeltonObjectChecker.h"
#include "ThrowWeapon.h"
#include "RotateComponent.h"
#include "AnimationEnemyComponent.h"
#include "EnemyWeapon.h"
#include "ParticleEffect.h"
#include "MainCameraObject.h"
#include "WarpPointSearchEnemy.h"

const float EnemyBase::Gravity = 500.0f;
const float EnemyBase::NockBackPower = 1075.0f;
const float EnemyBase::GroundCheckPos = 40;
const int EnemyBase::ActionChangeCountMax = 100;
const Vector3 EnemyBase::footPos = Vector3(0, -15, 0);
const Vector3 EnemyBase::TrackingRange = Vector3(1000, 1000, 1000);
const int EnemyBase::TurnWaitCountMax = 2;
const float EnemyBase::ForwardDownY = -90;

const int EnemyBase::HitPointMax = 3;
const float EnemyBase::AttackingTime = 30;
const float EnemyBase::HittingTime = 40.0f;
const float EnemyBase::WalkSpeed = 125;
const float EnemyBase::ApproachSpeedRatio = 0.8f;
const float EnemyBase::SearchRange = 200;
const float EnemyBase::AttackRange = 75.0f;
const int EnemyBase::AttackIntervalCount = 120;

EnemyBase::EnemyBase(Vector3 _pos,Vector3 _scale,const std::string& meshName) :
	GameObject(),
	actionChangeCount(0),
	moveDirection(EnemyMoveDirection::right),
	beforeDirection(moveDirection),
	actionName(EnemyActions::walk),
	turnWaitCount(0),
	nockBackForce(Vector3::Zero),
	attackingState(false),
	teleportChargingTime(0),
	attackIntervalCount(0),
	attackIntervalCountMax(AttackIntervalCount),
	canNotActionTime(0),
	hitPoint(HitPointMax),
	isLive(false),
	actionChangeCountMax(ActionChangeCountMax),
	attackingTime(AttackingTime),
	hittingTime(HittingTime),
	walkSpeed(WalkSpeed),
	approachSpeedRatio(ApproachSpeedRatio),
	searchRange(SearchRange),
	attackRange(AttackRange),
	warpPositonSearching(false)
{
	SetScale(_scale);
	SetPosition(_pos);
	tag = Tag::EnemyTag;
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(10, 10, 10), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

	footChecker = new SkeltonObjectChecker(this, footPos, Vector3(1, 1, 1), Tag::GroundTag);
	forwardDownGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, ForwardDownY, 0), Vector3(1, 1, 1), Tag::GroundTag);
	forwardGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
	findingPlayerCheck = new SkeltonObjectChecker(this, Vector3(searchRange, 1, 0), Vector3(searchRange, 1, 1), Tag::PlayerTag);
	trackingRange = new SkeltonObjectChecker(this, Vector3::Zero, TrackingRange, Tag::PlayerTag);

	 rotate = new RotateComponent(this);
	rotate->SetRotation(-90, Vector3::UnitX);

	animComponent = new AnimationEnemyComponent(this);
	animComponent->SetMove(true);
	isLive = true;

	warpSearch = new WarpPointSearchEnemy();
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::UpdateGameObject(float _deltaTime)
{
	//�n�ʂƐڐG���Ă��Ȃ��Ƃ��d�͂𓭂�����
	if (footChecker->GetNoTouchingFlag())
	{
		SetPosition(position + Vector3(0, -Gravity * _deltaTime, 0));
	}

	if (!isLive)
	{
		if (animComponent->GetAnimDuration() <= 0)
		{
			SetState(State::Dead);
		}
		return;
	}
	if (hitPoint <= 0)
	{
		isLive = false;
		//���j���ꂽ�̂Ń��C���J�����̒����ʒu��1F�ύX���Ռ��̂悤�Ɍ�����
		mainCamera->SetViewMatrixLerpObject(Vector3(0, 0, 0), position);

		DeadCommonEvent();
		animComponent->SetAttack(true);
		animComponent->SetMove(false);
		return;
	}
	UpdateEnemyObject(_deltaTime);
	NockBack(_deltaTime);
	Action(_deltaTime);

	if (beforeDirection != moveDirection)
	{
		rotate->SetRotation(180, Vector3::UnitY);
		beforeDirection = moveDirection;
	}

	//�ړ������ɕύX����������ۂɂ���������������悤�ɍ��W���X�V��������
	findingPlayerCheck->SetOffset(Vector3((searchRange)*moveDirection, 0, 0));
}


void EnemyBase::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		//printf("\nouti!"); 
	}
}

void EnemyBase::OnTriggerEnter(ColliderComponent* colliderPair)
{
	//�v���C���[�̍U���ɐڐG�����Ƃ�
	if (colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		//�v���C���[�̍U���̕������v�Z��nockBackForce�Ɍv�Z
		double distance = Math::Sqrt((colliderPair->GetPosition().x - position.x) * (colliderPair->GetPosition().x - position.x) + (colliderPair->GetPosition().y - position.y) * (colliderPair->GetPosition().y - position.y));
		Vector3 force = Vector3::Normalize(Vector3((position.x - colliderPair->GetPosition().x),0, (position.z - colliderPair->GetPosition().z)));
		nockBackForce = force * NockBackPower;
		canNotActionTime = hittingTime;
		hitPoint--;
	}
}

void EnemyBase::DeadCommonEvent()
{
	DeadEvent();
	SetState(Dead);
	Vector3 effectPos = Vector3(position.x, position.y + 50, position.z);
	new ParticleEffect(effectPos, Vector3(10, 18, 0));
	new ParticleEffect(effectPos, Vector3(-10, 18, 0));
	new ParticleEffect(effectPos, Vector3(10, 16, 0));
	new ParticleEffect(effectPos, Vector3(10, 12, 0));
	new ParticleEffect(effectPos, Vector3(10, 9, 0));
	new ParticleEffect(effectPos, Vector3(10, 6, 0));
	new ParticleEffect(effectPos, Vector3(10, 3, 0));
	new ParticleEffect(effectPos, Vector3(-10, 16, 0));
	new ParticleEffect(effectPos, Vector3(-10, 12, 0));
	new ParticleEffect(effectPos, Vector3(-10, 9, 0));
	new ParticleEffect(effectPos, Vector3(-10, 6, 0));
	new ParticleEffect(effectPos, Vector3(-10, 3, 0));
}

void EnemyBase::NockBack(float _deltaTime)
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

void EnemyBase::ActionChange()
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

void EnemyBase::Action(float _deltaTime)
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

void EnemyBase::BranchActionChange()
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
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
}

void EnemyBase::ShuffleCountMax()
{
	//���̃A�N�V�����ύX���Ԃ��f�t�H���g+�����Ō���
	actionChangeCountMax = ActionChangeCountMax + ((rand() % 5) * 100);
}

void EnemyBase::NoAttacking(float _deltaTime)
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
					printf("%f,%f\n",forwardDownGroundCheck->GetPosition().x, forwardGroundCheck->GetPosition().x);
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

void EnemyBase::Attacking(float _deltaTime)
{
	//�ǐՑΏۂ̍��W���擾
	Vector3 target = trackingRange->GetColliderPairPosition();
	//�v���C���[�Ƃ̋������v�Z
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
	//���������]���邱�Ƃ����邽�߂��ꂼ���offset���W���X�V����
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
	//��Βl�ɕϊ�
	playerDistance = Math::Abs(playerDistance);

	if (actionName == EnemyActions::approach)
	{
		//�ǐՑΏۂƍ����̍���10�ȏ゠���ԂŃJ�E���g��100�i�ނƒǐՑΏۂ�����ȏ㗣�ꂽ�ʒu�Ƀe���|�[�g
		float heightDistance = Math::Abs(position.y - target.y);
		if (heightDistance > 10 && playerDistance > 100&&!warpPositonSearching)
		{
			teleportChargingTime++;
		}
		else
		{
			teleportChargingTime = 0;
		}
		if (teleportChargingTime > 200&&!warpPositonSearching)
		{ 
 			teleportChargingTime = 0;
 		//	Vector3 teleportPosition = target;
			//teleportPosition.x += (100 * moveDirection) * -1;
			warpSearch->SetFirstPosition(target, position);
  			warpPositonSearching = true;
			//SetPosition(teleportPosition);
		}
		if (warpPositonSearching)
		{
			if (warpSearch->GetEndSearch())
			{
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
		if (playerDistance >= attackRange)
		{
			actionName = EnemyActions::approach;

			animComponent->SetAttack(false);
			animComponent->SetMove(true);

		}
		if (attackIntervalCount <= 0)
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

void EnemyBase::Attack(float _deltaTime)
{
}
