#include "ColliderComponent.h"
#include "GameObject.h"
#include "PhysicsWorld.h"

/*
@fn GameObjectから受け取った関数ポインタを保存しPhysicsWorldに自分を追加
@param owner 親GameObjectへのポインタ
@param updateOrder このComponentの更新順番
@param size 当たり判定のサイズ(GameObjectのScaleとは異なる)
@param objectId GameObjectに振られる静的な識別番号
@param tag GameObjectに振られる静的な列挙型
@param colliderPos 衝突判定が存在する中心座標　親GameObjectの座標に足して使用する
 */
ColliderComponent::ColliderComponent(GameObject * owner, int updateOrder, Vector3 size, int objectId, std::function<void(ColliderComponent*)>TriggerEnter, std::function<void(ColliderComponent*)> TriggerStay, Tag tag, Vector3 colliderPos) :
	Component(owner, updateOrder)
	, size(size)
	, colliderPos(colliderPos)
	, doCollision(true)
	, collidedCamera(false)
{
	OnTriggerEnter = TriggerEnter;
	OnTriggerStay = TriggerStay;
	PhysicsWorld::GetInstance()->AddCollider(this);
}

/*
@fn PhysicsWorldから自分を削除
*/
ColliderComponent::~ColliderComponent()
{
	PhysicsWorld::GetInstance()->RemoveCollider(this);
}

/*
@fn Colliderクラスにて親Objectが衝突したら呼び出される
@fn 衝突相手の識別子と相手との衝突状態を記憶する
@param colliderParter 衝突相手のColliderComponent
@detail Colliderクラスで親Objectが衝突したことを伝えられ、
	  衝突状態を前Fで衝突していた衝突情報で判断し記憶する関数
*/
void ColliderComponent::OnCollision(ColliderComponent* colliderParter)
{
	CollisionState state = CollisionState::Enter;
	//前Fで同じオブジェクトと接触していた場合StateをStayへ変更させる
	for (auto obj : beforeCollisions)
	{
		if (obj.first->GetId() == colliderParter->GetId())
		{
			state = CollisionState::Stay;
			break;
		}
	}
	//auto iter = hadCollision.find(colliderParter);
	//if (iter != hadCollision.end())
	//{
	//	state = CollisionState::Stay;
	//}
	//現Fで接触しているリストに挿入
	nowCollisions.emplace_back(std::make_pair(colliderParter, state));
	//isCollision.emplace(colliderParter, state);
}

/*
@fn 毎F更新される関数
@fn 現在接触しているリストを前フレーム接触していたリストへ移すなどはここで行う
*/
void ColliderComponent::Update(float deltaTime)
{
	CollisionReaction(deltaTime);

	beforeCollisions.clear();
	beforeCollisions = nowCollisions;
	nowCollisions.clear();
	//hadCollision.clear();
	//hadCollision = isCollision;
	//isCollision.clear();
	//衝突を行うか
	if (doCollision)
	{
		//現Fで移動を行ったか(移動を行っていないのに衝突することは無いため)
		if (owner->GetRecomputeWorldTransform())
		{
			PhysicsWorld::GetInstance()->Collision(this);
		}
		//PhysicsWorld::Collision()でカメラの衝突範囲に接触したか;
		if (!collidedCamera)
		{
			//接触していない画面外となり更新が停止する
			owner->SetState(State::Paused);
		}
		else
		{
			//接触した場合更新を再開する
			if (owner->GetTag() != Tag::Camera)
			{
				collidedCamera = false;
			}
		}
	}
}

/*
@fn 接触したオブジェクト達との接触状態をもとに親GameObjectのリアクション関数に接触相手のTagを渡す
*/
void ColliderComponent::CollisionReaction(float deltaTime)
{
	//接触したオブジェクト達との接触状態をもとに親GameObjectのリアクション関数に接触相手のTagを渡す
	for (auto obj : nowCollisions)
	{
		switch (obj.second)
		{
		case(CollisionState::Enter):
			OnTriggerEnter(obj.first);
			OnTriggerStay(obj.first);
			break;
		case(CollisionState::Stay):
			OnTriggerStay(obj.first);

			break;
		}
	}
}

/*
@fn 親Objectの座標を返す
*/
Vector3 ColliderComponent::GetPosition()
{
	return owner->GetPosition() + colliderPos;
}

/*
@fn 親Objectの識別番号を返す
*/
int ColliderComponent::GetId()
{
	return owner->GetObjectId();
}

/*
@fn 親オブジェクトのタグ
*/
Tag ColliderComponent::GetObjectTag()
{
	return owner->GetTag();
}

/*
@fn 親オブジェクトの状態
*/
State ColliderComponent::GetState()
{
	return owner->GetState();
}


