#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "PlayerCharacter.h"

PhysicsWorld* PhysicsWorld::physicsWorld = nullptr;

/*
@fn PhysicsWorld生成
*/
void PhysicsWorld::CreateInstance()
{
	if (!physicsWorld)
	{
		physicsWorld = new PhysicsWorld();
	}
}

/*
@fn PhysicsWorld解放
*/
void PhysicsWorld::DeleteInstance()
{
	delete physicsWorld;
	physicsWorld = nullptr;
}

/*
@fn 生成されたColliderComponentをcollidersへ追加
@param _collider PhysicsWorldクラスに追加したいクラス
*/
void PhysicsWorld::AddCollider(ColliderComponent* _collider)
{
	colliders.emplace_back(_collider);
}

/*
　@fn 生成されているColliuderComponentをcollidersから削除
 @param _collider PhysicsWorldクラスから解放したいクラス
*/
void PhysicsWorld::RemoveCollider(ColliderComponent* _collider)
{
	auto iter = std::find(colliders.begin(), colliders.end(), _collider);
	if (iter != colliders.end())
	{
		std::iter_swap(iter, colliders.end() - 1);
		colliders.pop_back();
	}
}

/*
@fn 衝突判定
@param _collider 衝突を行う、ColliderComponentから呼ばれる衝突関数
*/
void PhysicsWorld::Collision(ColliderComponent* _collider)
{
	Tag obj1Tag = _collider->GetObjectTag();
	for (auto collider2 : colliders)
	{
		Tag obj2Tag = collider2->GetObjectTag();
		//オブジェクトごとの列挙型を比較し衝突の優先順位ごとに衝突を行う
		if (obj1Tag < obj2Tag)
		{
			if (_collider->GetObjectTag() != Tag::Camera)
			{
				if (collider2->GetState() == State::Paused)
				{
					continue;
				}
			}
			//衝突計算相手が無更新状態でないか
			if (collider2->GetState() == State::Dead)
			{
				continue;
			}
			//衝突予定相手が衝突を行うか
			if (!collider2->GetDoCollision())
			{
				continue;
			}

			//衝突したか
			int hit = false;

			AABB obj1(_collider->GetPosition(), _collider->GetCollisionSize());
			AABB obj2(collider2->GetPosition(), collider2->GetCollisionSize());

			hit = Intersect(obj1, obj2);

			//衝突していたら
			if (hit > 0)
			{
				//カメラが衝突した相手でかつ前Fまで画面外ポーズだったオブジェクトを活動させる
				if (obj1Tag == Tag::Camera)
				{
					if (obj2Tag != Tag::ParticleEffectTag)
					{
						collider2->SetCollidedCamera();
						if (collider2->GetState() == State::Paused)
						{
							collider2->GetOwner()->SetState(State::Active);
						}
					}
				}

				//プレイヤー、エネミーは地面とのめり込み補正を行いプレイヤーは薄床とめり込み補正を行う
				if (obj1Tag == Tag::PlayerTag && obj2Tag == Tag::GroundTag ||
					obj1Tag == Tag::EnemyTag && obj2Tag == Tag::GroundTag ||
					obj1Tag == Tag::PlayerTag && obj2Tag == Tag::ThinGroundFloor)
				{
					_collider->GetOwner()->FixCollision(obj1, obj2, obj2Tag);
				}
				else if (obj1Tag == Tag::GroundTag && obj2Tag == Tag::ParticleEffectTag)
				{
					collider2->GetOwner()->FixCollision(obj1, obj2, obj2Tag);
				}

				_collider->OnCollision(collider2);
				collider2->OnCollision(_collider);
			}
		}
		else
		{
			continue;
		}

	}
}

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}
