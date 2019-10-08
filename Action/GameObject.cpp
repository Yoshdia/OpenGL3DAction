#include "Game.h"
#include "Math.h"
#include "GameObject.h"
#include "Component.h"
#include "InputSystem.h"
#include "GameObjectManager.h"

/**
@param	�Q�[���N���X�̃|�C���^
*/
GameObject::GameObject()
	: state(Active)
	, worldTransform()
	, position(Vector3::Zero)
	, scale(1.0f)
	, rotation(Quaternion::Identity)
	, recomputeWorldTransform(true)
{
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
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::Update(float _deltaTime)
{
	if (state == Active)
	{
		ComputeWorldTransform();

		UpdateComponents(_deltaTime);
		UpdateGameObject(_deltaTime);

		ComputeWorldTransform();
	}
}

/**
@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	for (auto itr : components)
	{
		itr->Update(_deltaTime);
	}
}

/**
@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
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

void GameObject::GameObjectInput(const InputState& _keyState)
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
	auto itr = std::find(components.begin(),components.end(), _component);
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
