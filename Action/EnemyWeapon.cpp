#include "EnemyWeapon.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "Game.h"
#include "MeshComponent.h"

/*
@param _pos 座標
@param _size サイズ
@param _lifeCount 判定時間
@param _waitTime 攻撃発生まで待機時間
*/
EnemyWeapon::EnemyWeapon(Vector3 _pos, Vector3 _size, int lifeCount, int _waitTime) :
	GameObject(),
	lifeCount(lifeCount),
	waitTime(_waitTime)
{
	tag = Tag::EnemyWeaponTag;
	SetPosition(_pos);
	collisionComp = new ColliderComponent(this, 100, _size, gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
	collisionComp->SetDoCollision(false);
	SetScale(_size);
	meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/collisionMask.gpmesh"));
	meshComponent->SetVisible(false);
}

EnemyWeapon::~EnemyWeapon()
{
}

/*
@fn 生存時間を減少させ続けゼロになった時このオブジェクトの更新を止める
*/
void EnemyWeapon::UpdateGameObject(float _deltaTime)
{
	if (Game::debug&&lifeCount > 0 && waitTime < 0)
	{
		meshComponent->SetVisible(true);
	}
	else
	{
		meshComponent->SetVisible(false);
	}
	//待機時間を減らし続ける
	if (waitTime < 0)
	{
		//生存時間を減らし続ける
		if (lifeCount > 0)
		{
			lifeCount--;
			collisionComp->SetDoCollision(true);
		}
		else
		{
			SetState(Dead);
		}
	}
	else
	{
		waitTime--;
	}
}
