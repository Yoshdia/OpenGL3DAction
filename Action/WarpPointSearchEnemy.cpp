#include "WarpPointSearchEnemy.h"
#include "SkeltonObjectChecker.h"

WarpPointSearchEnemy::WarpPointSearchEnemy(Vector3 _pos):
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
	if (!searchedPoint)
	{
		printf("SearchingPosition :: %f , %f \n", position.x, position.y);
		if (!footGroundChecker->GetNoTouchingFlag()||isGround)
		{
			isGround = true;

			SetPosition(position + Vector3((float)(moveDirection*5), 0, 0));
			if (forwardGroundChecker->GetNoTouchingFlag()|| !forwardWallChecker->GetNoTouchingFlag())
			{
				searchedPoint = true;
				printf("Searched Position! \n");
			}
		}
		else
		{
			SetPosition(position+Vector3(0,- 1.0f*5,0));
		}
	}
	else
	{
		SetPosition(Vector3::Zero);
	}
}

void WarpPointSearchEnemy::SetFirstPosition(Vector3 _position,Vector3 _enemyPosition)
{
	searchedPoint = false;
	isGround = false;
	SetPosition(_position);
	float x=_position.x - _enemyPosition.x;
	if (x > 0)
	{
		moveDirection = MoveDirection::left;
	}
	else
	{
		moveDirection = MoveDirection::right;
	}
	//forwardGroundChecker->SetPosition(position+Vector3(moveDirection * 50, -75, 0));
	//forwardWallChecker->SetPosition(position+Vector3(moveDirection * 50, 0, 0));
	forwardGroundChecker->SetOffset(Vector3((float)moveDirection * 50.0f, -75, 0));
	forwardWallChecker->SetOffset(Vector3((float)moveDirection * 50.0f, 30, 0));
	//footGroundChecker->SetPosition(Vector3(0, 0, 0)+position);
}
