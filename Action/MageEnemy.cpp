#include "MageEnemy.h"
#include "AnimationEnemyComponent.h"
#include "RotateComponent.h"

MageEnemy::MageEnemy(Vector3 _pos):
	EnemyBase(_pos,Vector3(0.8f,0.8f,0.8f),EnemyType::MageType)
{
	moveDirection = EnemyMoveDirection::left;
}

MageEnemy::~MageEnemy()
{
}

void MageEnemy::UpdateEnemyObject(float _deltaTime)
{
}

void MageEnemy::DeadEvent()
{
}

void MageEnemy::HitPlayerAttack(const Vector3 & _pairPos)
{
}
