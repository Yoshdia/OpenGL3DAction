#pragma once
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"


class Game;
class Vector3;
class Matrix4;
class Component;
struct InputState;
class ColliderComponent;

/**
@brief	ゲームオブジェクトの状態
*/
enum State
{
	Active,
	Paused,
	Dead
};

/*
	@enum　GameObjectタグ
	衝突相手を判別するために使用
*/
enum Tag
{
	PlayerTag,
	PlayerWeaponTag,
	EnemyTag,
	GroundTag,
	null,
};

class GameObject
{
public:
	/**
	@param	ゲームクラスのポインタ
	*/
	GameObject();
	virtual ~GameObject();

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void Update(float _deltaTime);

	/**
	@brief	アタッチされてるコンポーネントのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateComponents(float _deltaTime);

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime) ;

	void ProcessInput(const InputState& _keyState);
	virtual void GameObjectInput(const InputState& _keyState) ;

	/**
	@brief	コンポーネントを追加する
	@param	追加するコンポーネントのポインタ
	*/
	void AddComponent(Component* _component);

	/**
	@brief	コンポーネントを削除する
	@param	削除するコンポーネントのポインタ
	*/
	void RemoveComponent(Component* _component);

	/**
	@brief	Transformのワールド変換
	*/
	void ComputeWorldTransform();

	/**
	@brief　オブジェクトのポジションを取得する
	@return	position
	*/
    const Vector3& GetPosition() const { return position; }

	/**
	@brief　オブジェクトのポジションを設定する
	@param	position
	*/
    virtual void SetPosition(const Vector3& _pos) { position = _pos; recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトのスケールを取得する
	@return	scale
	*/
    Vector3 GetScaleFloat() const { return scale; }

	/**
	@brief　オブジェクトのスケールを設定する
	@param	scale
	*/
	void SetScale(float _scale) { scale.x = _scale; scale.y = _scale; scale.z = _scale; recomputeWorldTransform = true; }
	void SetScale(Vector3 _scale) { scale.x = _scale.x; scale.y = _scale.y; scale.z = _scale.z; recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトのクォータニオンを取得する
	@return	rotation（Quaternion型）
	*/
    const Quaternion& GetRotation() const { return rotation; }

	/**
	@brief　オブジェクトのクォータニオンを設定する
	@param	rotation（Quaternion型）
	*/
	virtual void SetRotation(const Quaternion& _qotation) { rotation = _qotation;  recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトの状態を取得する
	@return	state
	*/
	State GetState() const { return state; }

	/**
	@brief　オブジェクトの状態を設定する
	@param	state
	*/
	virtual void SetState(State _state) { state = _state; }

	/**
	@brief　オブジェクトのワールド行列を取得する
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/**
	@brief　オブジェクトの前方を表すベクトルを取得する
	@param	forward(Vector3型)
	*/
    Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, rotation); }

	/**
	@brief　オブジェクトの右を表すベクトルを取得する
	@param	right(Vector3型)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, rotation); }

	/**
	@brief　オブジェクトの上を表すベクトルを取得する
	@param	up(Vector3型)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, rotation); }

	Tag GetTag() const { return tag; }

	int GetObjectId() {return myObjectId;};

	void FixCollision(const AABB & myAABB, const AABB & pairAABB);

protected:
	std::function<void(ColliderComponent*)> GetTriggerEnterFunc() { return std::bind(&GameObject::OnTriggerEnter, this, std::placeholders::_1); }
	std::function<void(ColliderComponent*)> GetTriggerStayFunc() { return std::bind(&GameObject::OnTriggerStay, this, std::placeholders::_1); }

	virtual void OnTriggerEnter( ColliderComponent* colliderPair) {};
	virtual void OnTriggerStay( ColliderComponent* colliderPair) {};

	//ゲームオブジェクトの状態
	State state;
	//ゲームオブジェクトのタグ
	Tag tag;
	//ゲームオブジェクトのID
	static int gameObjectId;
	int myObjectId;

	//Transform
	Vector3 position;
	Quaternion rotation;	
	Vector3 scale;
	Matrix4 worldTransform;
	//ワールド変換の処理を行う必要性があるか
	bool recomputeWorldTransform;

	//アタッチされているコンポーネント
	std::vector<class Component*>components;

};

