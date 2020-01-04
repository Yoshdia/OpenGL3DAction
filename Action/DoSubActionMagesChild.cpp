#include "DoSubActionMagesChild.h"
#include "SkeltonObjectChecker.h"

const float DoSubActionMagesChild::FloatHeight = 150;
const float DoSubActionMagesChild::FloatSpeed = 1;
const float DoSubActionMagesChild::DroppingSpeed = -10;

DoSubActionMagesChild::DoSubActionMagesChild(GameObject* _owner) :
	GameObject(),
	targetHeight(0),
	floating(false),
	droppingDown(false),
	moveDirection(EnemyMoveDirection::left),
	verticalMoveDirection(EnemyMoveDirection::left),
	verticalInversionCount(0)
{
	owner = _owner;
	footChcker = new SkeltonObjectChecker(this, Vector3(0, -5, 0), Vector3(8, 10, 1), Tag::GroundTag);
	rightWallChecker = new SkeltonObjectChecker(this, Vector3(30, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
	leftWallChecker = new SkeltonObjectChecker(this, Vector3(-30, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
}

DoSubActionMagesChild::~DoSubActionMagesChild()
{
}

void DoSubActionMagesChild::UpdateGameObject(float _deltaTime)
{
	//親オブジェクトを追跡
	SetPosition(owner->GetPosition());
	//どちらかの命令が来ていたか
	if (floating || droppingDown)
	{
		//親オブジェクトの座標
		Vector3 ownerPos = owner->GetPosition();
		if (floating)
		{
			//targetHeightまで浮上
			droppingDown = false;
			if (ownerPos.y <= targetHeight)
			{
				owner->SetPosition(ownerPos += Vector3(0, FloatSpeed, 0));
			}
			else
			{
				floating = false;
			}
		}
		if (droppingDown)
		{
			//地面を検知するまで落下
			floating = false;
			if (footChcker->GetNoTouchingFlag())
			{
				owner->SetPosition(ownerPos + Vector3(0, DroppingSpeed, 0));
			}
			else
			{
				droppingDown = false;
			}
		}
	}
}

void DoSubActionMagesChild::StartFloating()
{
	floating = true;
	targetHeight = owner->GetPosition().y + FloatHeight;
}

void DoSubActionMagesChild::StartDroppingDown()
{
	droppingDown = true;
}

void DoSubActionMagesChild::MoveHorizontal()
{
	if (moveDirection == EnemyMoveDirection::right)
	{

		if (!rightWallChecker->GetNoTouchingFlag())
		{
			moveDirection = EnemyMoveDirection::left;
		}
	}
	else
	{
		if (!leftWallChecker->GetNoTouchingFlag())
		{
			moveDirection = EnemyMoveDirection::right;
		}
	}
	int direction = moveDirection == EnemyMoveDirection::right ? 1 : -1;
	owner->SetPosition(owner->GetPosition() + Vector3(2 * direction, 0, 0));
}

void DoSubActionMagesChild::HuwaHuwa()
{
	if (verticalInversionCount < 0)
	{
		verticalInversionCount = 50;
		verticalMoveDirection = verticalMoveDirection == EnemyMoveDirection::left ? EnemyMoveDirection::right : EnemyMoveDirection::left;
	}
	else
	{
		verticalInversionCount--;
	}
	int direction = verticalMoveDirection == EnemyMoveDirection::right ? 1 : -1;
	owner->SetPosition(owner->GetPosition() + Vector3(0, 0.1* direction, 0));

}
