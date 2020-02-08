#include "DoSubActionMagesChild.h"
#include "SkeltonObjectChecker.h"

const float DoSubActionMagesChild::FloatHeight = 150;
const float DoSubActionMagesChild::FloatSpeed = 1;
const float DoSubActionMagesChild::DroppingSpeed = -10;

/*
@param _owner 親となるオブジェクトクラス
*/
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
	rightWallChecker = new SkeltonObjectChecker(this, Vector3(40, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
	leftWallChecker = new SkeltonObjectChecker(this, Vector3(-40, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
}

DoSubActionMagesChild::~DoSubActionMagesChild()
{
}

/*
@fn どの行動を行うか判断し、行う
*/
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

/*
@fn このクラス内の定数分の高さまで浮上する
*/
void DoSubActionMagesChild::StartFloating()
{
	floating = true;
	targetHeight = owner->GetPosition().y + FloatHeight;
}

/*
@fn サブクラスが地面を検知するまで落下する
@sa SkeltonObjectChecker.h
*/
void DoSubActionMagesChild::StartDroppingDown()
{
	droppingDown = true;
}

/*
@fn 水平を指定する変数をもとに移動する。壁に当たると変数を反転する
*/
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
	owner->SetPosition(owner->GetPosition() + Vector3((float)(2 * direction), 0, 0));
}

/*
@fn 垂直を指定する変数をもとに移動する。一定間隔ごとに変数を反転する
*/
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
	owner->SetPosition(owner->GetPosition() + Vector3(0, (float)(0.1* direction), 0));

}
