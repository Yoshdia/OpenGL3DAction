#pragma once
#include "Component.h"
#include "Math.h"
#include "GameObject.h"
#include <map>
#include<functional>


/*
 @file ColliderComponent名.h
 @fn 衝突機能を所有するオブジェクトに追加させるComponent
 @detail Colliderクラスによって管理され衝突判定が行われる
		衝突に必要な座標、向き、大きさなどをGameObjectからColliderクラスへ受け渡すパイプにも使用
		衝突した相手のObjectTagIdと、それぞれとの接触状態(Enter,Stay,Exit)を記憶しGameObjectへのリアクション関数を呼び出す
 */
class ColliderComponent :
	public Component
{
public:
	/*
	@fn GameObjectから受け取った関数ポインタを保存しPhysicsWorldに自分を追加
　　@param owner 親GameObjectへのポインタ
　　@param updateOrder このComponentの更新順番
　　@param size 当たり判定のサイズ(GameObjectのScaleとは異なる)
　　@param objectId GameObjectに振られる静的な識別番号
　　@param tag GameObjectに振られる静的な列挙型
　　@param colliderPos 衝突判定が存在する中心座標　親GameObjectの座標に足して使用する
	*/
	ColliderComponent(GameObject* owner, int updateOrder, Vector3 size, int objectId, std::function<void(ColliderComponent*)>TriggerEnter, std::function<void(ColliderComponent*)>TriggerStay, Tag tag, Vector3 colliderPos = Vector3(0, 0, 0));

	/*
	@fn PhysicsWorldから自分を削除
	*/
	~ColliderComponent();

	/*
	@fn Colliderクラスにて親Objectが衝突したら呼び出される
	@fn 衝突相手の識別子と相手との衝突状態を記憶する
	@param colliderParter 衝突相手のColliderComponent
	@detail Colliderクラスで親Objectが衝突したことを伝えられ、
		  衝突状態を前Fで衝突していた衝突情報で判断し記憶する関数
	*/
	void OnCollision(ColliderComponent* colliderParter);

	/*
	@fn 毎F更新される関数
	@fn 現在接触しているリストを前フレーム接触していたリストへ移すなどはここで行う
	*/
	void Update(float deltaTime) override;
private:
	/*
	@fn 衝突のリアクション関数
	@sa GameObject.h
	*/
	std::function<void(ColliderComponent*)> OnTriggerEnter;
	/*
	@fn 衝突のリアクション関数
	@sa GameObject.h
	*/
	std::function<void(ColliderComponent*)> OnTriggerStay;
	/*
	@fn 接触したオブジェクト達との接触状態をもとに親GameObjectのリアクション関数に接触相手のTagを渡す
	*/
	void CollisionReaction(float deltaTime);

	//衝突を行うか
	bool doCollision;
	//カメラと衝突していたか(画面内に在るか)
	bool collidedCamera;
	//衝突判定が存在する中心座標　親GameObjectの座標に足して使用する
	Vector3 colliderPos;
	
	/*
	@enum 接触状態、ObjectTagIdとともにmapで管理され、この接触状態を基に親Objectのリアクション関数を選択する
	*/
	enum CollisionState
	{
		//前Fで接触しておらず、接触直後
		Enter,
		//前Fでも接触しており、接触中
		Stay,
	};
	// 当たり判定のサイズ(GameObjectのScaleとは異なる)
	Vector3 size;
	//現在Fで親Objectと接触している相手Objectと接触状態
	std::vector<std::pair<ColliderComponent* ,CollisionState>> nowCollisions;
	//std::map< ColliderComponent*, CollisionState> isCollision;
	//前Fで親Objectと接触していた相手Objectの識別子
	std::vector<std::pair<ColliderComponent* ,CollisionState>> beforeCollisions;
	//std::map< ColliderComponent*, CollisionState> hadCollision;

public: //ゲッターセッター
	/*
	@return 親Objectの座標を返す
	*/
	Vector3 GetPosition();
	/*
	@return 親Objectの識別番号を返す
	*/
	int GetId();
	/*
	@return 当たり判定のサイズ
	*/
	Vector3 GetCollisionSize() { return size; };
	/*
	@fn 当たり判定のサイズ
	*/
	void SetScale(Vector3 _scale) { size = _scale; }

	/*
	@return 親オブジェクトのタグ
	*/
	Tag GetObjectTag();

	/*
	@return 親オブジェクトの状態
	*/
	State GetState();

	/*
	@return 衝突を行うか
	*/
	bool GetDoCollision() { return doCollision; }
	/*
	@fn 衝突を行うか
	*/
	void SetDoCollision(bool _flag) { doCollision = _flag; }

	/*
	@fn カメラと衝突していたか
	@fn カメラと衝突していない状態でも更新したい場合使用
	*/
	void SetCollidedCamera() { collidedCamera = true; }
};

