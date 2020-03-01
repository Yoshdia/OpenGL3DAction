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

/*
@brief	ゲームオブジェクトの状態
*/
enum State
{
	//アクティブ
	Active,
	//更新が停止している
	Paused,
	//オブジェクトの更新が終了(外部からのみActiveに変更可能)
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

/*
@enum ゲームオブジェクトの更新を停止するイベント名
*/
enum PauzingEvent
{
	//ボスの特殊演出
	SummonMageEvent,
	//ポーズ画面中
	PausingEvent,
	//プレイヤーが撃破されてしまった際の演出
	DeadPlayerEvent,
	//ゲームオーバー時の演出 DeadPlayerEventと関連
	GameOverEvent,
	//ゲームオブジェクトの更新が行われている。
	NoneEvent
};

class GameObject
{
public:
	/*
	@param	ゲームクラスのポインタ
	*/
	GameObject(bool _reUseGameObject = false);
	virtual ~GameObject();

	/*
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void Update(float _deltaTime);

	/*
	@brief	アタッチされてるコンポーネントのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn ゲームオブジェクトが静止中に更新されるアップデート関数
	@brief pauzingUpdateがtrueのときだけ呼ばれる更新関数
	*/
	virtual void PausingUpdateGameObject();

	/*
	@fn 入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
	*/
	void ProcessInput(const InputState& _keyState);

	/*
	@fn 入力を引数で受け取る更新関数
	@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	*/
	virtual void GameObjectInput(const InputState& _keyState);

	/*
	@brief	コンポーネントを追加する
	@param	追加するコンポーネントのポインタ
	*/
	void AddComponent(Component* _component);

	/*
	@brief	コンポーネントを削除する
	@param	削除するコンポーネントのポインタ
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn 現在の仕様上行うことができない処理を外部から強引に行うための関数
	@exsample ゲームオブジェクト全体の更新が停止中に対象のゲームオブジェクトを更新する
	*/
	void ExceptionUpdate();
	/*
	@brief	Transformのワールド変換
	*/
	void ComputeWorldTransform();

	/*
	@brief　オブジェクトのポジションを取得する
	@return	position
	*/
	const Vector3& GetPosition() const { return position; }

	/*
	@brief　オブジェクトのポジションを設定する
	@param	position
	*/
	virtual void SetPosition(const Vector3& _pos) { position = _pos; recomputeWorldTransform = true; }
	bool GetRecomputeWorldTransform() { return recomputeWorldTransform; }

	/*
	@brief　オブジェクトのスケールを取得する
	@return	scale
	*/
	Vector3 GetScaleFloat() const { return scale; }

	/*
	@brief　オブジェクトのスケールを設定する
	@param	scale
	*/
	void SetScale(float _scale) { scale.x = _scale; scale.y = _scale; scale.z = _scale; recomputeWorldTransform = true; }
	void SetScale(Vector3 _scale) { scale.x = _scale.x; scale.y = _scale.y; scale.z = _scale.z; recomputeWorldTransform = true; }

	float GetScale() { return scale.x; }
	/*
	@brief　オブジェクトのクォータニオンを取得する
	@return	rotation（Quaternion型）
	*/
	const Quaternion& GetRotation() const { return rotation; }

	/*
	@brief　オブジェクトのクォータニオンを設定する
	@param	rotation（Quaternion型）
	*/
	virtual void SetRotation(const Quaternion& _qotation) { rotation = _qotation;  recomputeWorldTransform = true; }

	/*
	@brief　オブジェクトの状態を取得する
	@return	state
	*/
	State GetState() const { return state; }

	/*
	@brief　オブジェクトの状態を設定する
	@param	state
	*/
	virtual void SetState(State _state) { state = _state; }

	/*
	@brief　オブジェクトのワールド行列を取得する
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/*
	@brief　オブジェクトの前方を表すベクトルを取得する
	@param	forward(Vector3型)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, rotation); }

	/*
	@brief　オブジェクトの右を表すベクトルを取得する
	@param	right(Vector3型)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, rotation); }

	/*
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
	//ゲームオブジェクトの更新を止めるイベント状態
	static PauzingEvent pauzingEvent;
	//衝突時のリアクション関数(ColliderComponentにこの関数のアドレスを渡す) Enter...衝突した Stay...衝突している
	virtual void OnTriggerEnter(ColliderComponent* colliderPair) {};
	//衝突時のリアクション関数(ColliderComponentにこの関数のアドレスを渡す) Enter...衝突した Stay...衝突している
	virtual void OnTriggerStay(ColliderComponent* colliderPair) {};

	//ゲームオブジェクトの状態
	State state;
	//ゲームオブジェクトのタグ
	Tag tag;
	//ゲームオブジェクトのID、カウント用
	static int gameObjectId;
	//このゲームオブジェクトのID
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

