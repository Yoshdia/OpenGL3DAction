#include "MeleeEnemy.h"
#include "SkeltonObjectChecker.h"


MeleeEnemy::MeleeEnemy(Vector3 _pos) :
	EnemyBase("Assets/Model/untitled.gpmesh")
{
	SetScale(25);
	SetPosition(_pos);
	defaultCountMax = 200;
}


MeleeEnemy::~MeleeEnemy()
{
}

void MeleeEnemy::UpdateEnemyObject(float _deltaTime)
{
	float a = Math::Abs(position.x - findingPlayerCheck->GetColliderPairPosition().x);
	switch (actionName)
	{
	case(EnemyActions::walk):
		SetPosition(Vector3(0.5f*moveDirection, 0, 0) + position);
		if (footChecker->GetGround())
		{
			SetPosition(position + Vector3(0, -2, 0));
			if (forwardDownGroundCheck->GetGround() == true /*|| skeltonObjectChecker->GetGroundEnter() == false*/)
			{
				moveDirection = (EnemyMoveDirection)(moveDirection * (EnemyMoveDirection)-1);
				//forwardDownGroundCheck->ResetGroundFlag(false);
				forwardDownGroundCheck->SetCheckPos(Vector3(GroundCheckPos * moveDirection, -90, 0));
			}
			else
			{
				//forwardDownGroundCheck->ResetGroundFlag(true);
			}
		}
		//skeltonObjectChecker->SetCheckPos(Vector3(GroundCheckPos * moveDirection, 0, 0));
		break;
	case(EnemyActions::noActive):
		break;
	case(EnemyActions::foundMove):
		SetPosition(Vector3::Lerp(position, findingPlayerCheck->GetColliderPairPosition(), _deltaTime*0.8f));
		if (a < 75)
		{
			actionName = EnemyActions::attack;
		}
		break;
	case(EnemyActions::attack):
		printf("ATTACK");
		if (a >= 75)
		{
			actionName = EnemyActions::foundMove;
		}
		break;
	}
}

void MeleeEnemy::BranchActionChange()
{
	if (actionName == EnemyActions::attack || actionName == EnemyActions::foundMove)
	{
		return;
	}
	int ra = rand() % 4;

	if (ra <= 4)
	{
		actionName = EnemyActions::walk;
	}
	else
	{
		actionName = EnemyActions::noActive;
	}
	moveDirection = EnemyMoveDirection(rand() % 3);
}

void MeleeEnemy::ShuffleCountMax()
{
	actionChangeCountMax = defaultCountMax + ((rand() % 3) * 100);
}
