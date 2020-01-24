#include "Game.h"
#include "Math.h"
#include "GameObject.h"
#include "Component.h"
#include "InputSystem.h"
#include "GameObjectManager.h"
#include "PhysicsWorld.h"
#include "MainCameraObject.h"

int GameObject::gameObjectId = 0;
MainCameraObject* GameObject::mainCamera = nullptr;
PauzingEvent GameObject::pauzingEvent = PauzingEvent::NoneEvent;

/**
@param	�Q�[���N���X�̃|�C���^
*/
GameObject::GameObject(bool _reUseGameObject)
	: state(Active)
	, worldTransform()
	, position(Vector3::Zero)
	, scale(Vector3(1.0f, 1.0f, 1.0f))
	, rotation(Quaternion::Identity)
	, recomputeWorldTransform(true)
	, myObjectId(gameObjectId)
	, tag(Tag::null)
	, reUseObject(_reUseGameObject)
{
	gameObjectId++;
	GAME_OBJECT_MANAGER->AddGameObject(this);
	//if (mainCamera == nullptr)
	//{
	//	mainCamera = new MainCameraObject();
	//}
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
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::Update(float _deltaTime)
{
	if (pauzingEvent == PauzingEvent::NoneEvent)
	{
		if (state == Active)
		{
			ComputeWorldTransform();
			
			UpdateGameObject(_deltaTime);
			UpdateComponents(_deltaTime);

			ComputeWorldTransform();
		}
	}
	else
	{
		PausingUpdateGameObject();
		UpdateComponents(_deltaTime);
	}
}

/**
@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	if (state != State::Dead)
	{
	
		for (auto itr : components)
		{
			itr->Update(_deltaTime);
		}
	}
}

void GameObject::UpdateGameObject(float _deltaTime)
{
}

void GameObject::PausingUpdateGameObject()
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
@brief	�R���|�[�l���g��ǉ�����
@param	�ǉ�����R���|�[�l���g�̃|�C���^
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
@brief	�R���|�[�l���g���폜����
@param	�폜����R���|�[�l���g�̃|�C���^
*/
void GameObject::RemoveComponent(Component * _component)
{
	auto itr = std::find(components.begin(), components.end(), _component);
	if (itr != components.end())
	{
		components.erase(itr);
	}
}

/**
@brief	Transform�̃��[���h�ϊ�
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

void GameObject::FixCollision(const AABB & myAABB, const AABB & pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	calcCollisionFixVec(myAABB, pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

void GameObject::CreateMainCamera()
{
	mainCamera = new MainCameraObject();
}
