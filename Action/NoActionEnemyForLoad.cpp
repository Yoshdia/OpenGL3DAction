#include "NoActionEnemyForLoad.h"
#include "AnimationEnemyComponent.h"
#include "RotateComponent.h"

NoActionEnemyForLoad::NoActionEnemyForLoad(const Vector3& _pos, const EnemyType& _enemyType, const bool& _leftDirection) :
	EnemyBase(_pos, Vector3(0.4f, 0.4f, 0.4f), _enemyType)
{
	animComponent->AllFlagReset();
	if (!_leftDirection)
	{
		rotate->SetRotation(90, Vector3::UnitY);
	}
	else
	{
		rotate->SetRotation(180, Vector3::UnitY);
		animComponent->SetMove(true);
	}
}

NoActionEnemyForLoad::~NoActionEnemyForLoad()
{
}

void NoActionEnemyForLoad::UpdateGameObject(float _deltaTime)
{
}
