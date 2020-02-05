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
	Camera = 1,
	SkeletalObjectTag=2,
	PlayerTag = 3,
	PlayerWeaponTag = 4,
	PlayerGuardWeaponTag = 5,
	SubPlayerObject = 6,
	ComboItem = 7,
	CandleStickTag = 8,
	EnemyTag = 9,
	EnemyWeaponTag = 10,
	ParticleEffectTag = 11,
	ThinGroundFloor = 12,
	GroundTag = 13,
	null = 14,
};

enum PauzingEvent
{
	SummonMageEvent,
	DeadPlayerEvent,
	PausingEvent,
	NoneEvent
};

class GameObject
{
public:
	/**
	@param	ゲームクラスのポインタ
	*/
	GameObject(bool _reUseGameObject = false);
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
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn ゲームオブジェクトが静止中に更新されるアップデート関数
	@brief pauzingUpdateがtrueのときだけ呼ばれる更新関数
	*/
	virtual void PausingUpdateGameObject();

	void ProcessInput(const InputState& _keyState);
	virtual void GameObjectInput(const InputState& _keyState);

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
	bool GetRecomputeWorldTransform() { return recomputeWorldTransform; }

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

	float GetScale() { return scale.x; }
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
		
	int GetObjectId() { return myObjectId; };

	bool GetReUseGameObject() { return reUseObject; }

	virtual void FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);

	/*
	@fn 静的なmainCameraを生成する
	*/
	static void CreateMainCamera();
protected:
	std::function<void(ColliderComponent*)> GetTriggerEnterFunc() { return std::bind(&GameObject::OnTriggerEnter, this, std::placeholders::_1); }
	std::function<void(ColliderComponent*)> GetTriggerStayFunc() { return std::bind(&GameObject::OnTriggerStay, this, std::placeholders::_1); }

	//メインカメラ　生成はGameObjectManager生成時に行われる
	static class MainCameraObject* mainCamera;


	static PauzingEvent pauzingEvent;

	virtual void OnTriggerEnter(ColliderComponent* colliderPair) {};
	virtual void OnTriggerStay(ColliderComponent* colliderPair) {};

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
private:
	//シーンを跨ぐ際に開放されるオブジェクトかどうか、カメラなどが対象になる
	bool reUseObject;
};

