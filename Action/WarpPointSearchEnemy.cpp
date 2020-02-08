#include "WarpPointSearchEnemy.h"
#include "SkeltonObjectChecker.h"

/*
@param _pos 座標
*/
WarpPointSearchEnemy::WarpPointSearchEnemy(Vector3 _pos) :
	GameObject(),
	searchedPoint(true),
	moveDirection(MoveDirection::left),
	isGround(false)
{
	footGroundChecker = new SkeltonObjectChecker(this, Vector3(0, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
	forwardGroundChecker = new SkeltonObjectChecker(this, Vector3((float)moveDirection * 50.0f, -75, 0), Vector3(1, 1, 1), Tag::GroundTag);
	forwardWallChecker = new SkeltonObjectChecker(this, Vector3((float)moveDirection * 50.0f, 30, 0), Vector3(1, 1, 1), Tag::GroundTag);
}

WarpPointSearchEnemy::~WarpPointSearchEnemy()
{
}

void WarpPointSearchEnemy::UpdateGameObject(float _deltaTime)
{
	//検索が終了していないか
	if (!searchedPoint)
	{
		//地面を検索し終えたか
		if (!footGroundChecker->GetNoTouchingFlag() || isGround)
		{
		
			SetPosition(position + Vector3((float)(moveDirection * 5), 0, 0));
			//進行方向に壁がある。又は進行方向の下に床が無いとき検索を終了する
			if (forwardGroundChecker->GetNoTouchingFlag() || !forwardWallChecker->GetNoTouchingFlag())
			{
				searchedPoint = true;
				printf("Searched Position! \n");
			}
			isGround = true;
		}
		else
		{
			SetPosition(position + Vector3(0, -1.0f * 6.0f, 0));
		}
	}
	else
	{
		SetPosition(Vector3::Zero);
	}
}
/*
@fn 座標の検索を開始する
@brief 地面を検索した後に左右どちらかに進むか決定する
@param _position 検索開始地点
@param _enemyPosition このオブジェクトを使用しているエネミーの座標
*/
void WarpPointSearchEnemy::SetFirstPosition(Vector3 _position, Vector3 _enemyPosition)
{
	searchedPoint = false;
	isGround = false;
	SetPosition(_position);
	float x = _position.x - _enemyPosition.x;
	if (x > 0)
	{
		moveDirection = MoveDirection::left;
	}
	else
	{
		moveDirection = MoveDirection::right;
	}
	forwardGroundChecker->SetOffset(Vector3((float)moveDirection * 50.0f, -75, 0));
	forwardGroundChecker->SetPosition(_position);
	forwardWallChecker->SetOffset(Vector3((float)moveDirection * 50.0f, 30, 0));
	forwardWallChecker->SetPosition(_position);
	footGroundChecker->SetPosition(Vector3(0, 0, 0) + position);
	printf("Search Start %f.%f\n", position.x, position.y);
	}
