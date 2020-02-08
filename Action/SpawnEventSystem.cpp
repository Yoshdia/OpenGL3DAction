#include "SpawnEventSystem.h"
#include "ColliderComponent.h"
#include "MageEnemy.h"

#include "Game.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "DebugBox.h"

/*
@param _pos 座標
@param _wallPos プレイヤーが侵入してきたときにふさぐ壁の座標
@param _goalPos MageEnemyが撃破されたときに削除する壁の座標
*/
SpawnEventSystem::SpawnEventSystem(const Vector3& _pos,const Vector3& _wallPos, const Vector3& _goalPos):
	EventSystem(_pos),
	startDirecting(false),
	wallPos(_wallPos)
{
	ColliderComponent* collider = new ColliderComponent(this, 100, Vector3(500, 500, 500), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
	mageEnemy= new MageEnemy(position);

	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/collisionMask.gpmesh"));
	SetScale(Vector3(500,500,500));
	mageEnemy->SetGoalWall(new DebugBox(_goalPos));
}

SpawnEventSystem::~SpawnEventSystem()
{
}
/*
@brief プレイヤーの侵入を検知したときにフラグを建てる
*/
void SpawnEventSystem::OnTriggerEnter(ColliderComponent * _pair)
{
	if (_pair->GetObjectTag() == Tag::PlayerTag)
	{
		mageEnemy->SetAttackState(_pair->GetOwner());
		new DebugBox(wallPos);
		trigger = true;
		//ゲームオブジェクトの更新を止め演出をMageクラスに継いでもらう
		pauzingEvent = PauzingEvent::SummonMageEvent;
	}
}

void SpawnEventSystem::UpdateEventObject()
{
	if (Game::debug)
	{
		meshComponent->SetVisible(true);
	}
	else
	{
		meshComponent->SetVisible(false);
	}
}
