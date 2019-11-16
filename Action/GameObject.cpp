#include "Game.h"
#include "Math.h"
#include "GameObject.h"
#include "Component.h"
#include "InputSystem.h"
#include "GameObjectManager.h"
#include "PhysicsWorld.h"

int GameObject::gameObjectId = 0;

/**
@param	ゲームクラスのポインタ
*/
GameObject::GameObject()
	: state(Active)
	, worldTransform()
	, position(Vector3::Zero)
	, scale(Vector3(1.0f, 1.0f, 1.0f))
	, rotation(Quaternion::Identity)
	, recomputeWorldTransform(true)
	, myObjectId(gameObjectId)
	,tag(Tag::null)
{
	gameObjectId++;
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

GameObject::~GameObject()
{
    GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!components.empty())
	{
		delete components.back();
	}
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::Update(float _deltaTime)
{
	if (state == Active)
	{
		ComputeWorldTransform();

		UpdateGameObject(_deltaTime);
		UpdateComponents(_deltaTime);

		ComputeWorldTransform();
	}
}

/**
@brief	アタッチされてるコンポーネントのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	for (auto itr : components)
	{
		itr->Update(_deltaTime);
	}
}

void GameObject::UpdateGameObject(float _deltaTime)
{
}

void GameObject::ProcessInput(const InputState& _keyState)
{
	if (state == Active)
	{
		// First process input for components
		for (auto comp : components)
		{
			comp->ProcessInput(_keyState);
		}
		GameObjectInput(_keyState);
	}
}

void GameObject::GameObjectInput(const InputState & _keyState)
{
}

/**
@brief	コンポーネントを追加する
@param	追加するコンポーネントのポインタ
*/
void GameObject::AddComponent(Component * _component)
{
	int order = _component->GetUpdateOder();
	auto itr = components.begin();
	for (;
		itr != components.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	components.insert(itr, _component);
}

/**
@brief	コンポーネントを削除する
@param	削除するコンポーネントのポインタ
*/
void GameObject::RemoveComponent(Component * _component)
{
	auto itr = std::find(components.begin(),components.end(), _component);
	if (itr != components.end())
	{
		components.erase(itr);
	}
}

/**
@brief	Transformのワールド変換
*/
void GameObject::ComputeWorldTransform()
{
	if (recomputeWorldTransform)
	{
		recomputeWorldTransform = false;
		worldTransform = Matrix4::CreateScale(scale);
		worldTransform *= Matrix4::CreateFromQuaternion(rotation);
		worldTransform *= Matrix4::CreateTranslation(position);

		for (auto itr : components)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

void GameObject::FixCollision(const AABB & myAABB, const AABB & pairAABB)
{
	Vector3 ment = Vector3(0, 0, 0);
	calcCollisionFixVec(myAABB, pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}
