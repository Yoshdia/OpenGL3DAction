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

/*
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
	//GameObjectManager�Ƀ|�C���^��n��
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

GameObject::~GameObject()
{
	//GameObjectManager����|�C���^���폜����
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!components.empty())
	{
		delete components.back();
	}
}

/*
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::Update(float _deltaTime)
{
	//�X�V��~�̃C�x���g���łȂ���(�|�[�Y��ʂȂ�)
	if (pauzingEvent == PauzingEvent::NoneEvent)
	{
		//�X�V��Ԃ��A�N�e�B�u
		if (state == Active)
		{
			//Transform�̃��[���h�ϊ�
			ComputeWorldTransform();
			//�Q�[���I�u�W�F�N�g�̍X�V
			UpdateGameObject(_deltaTime);
			//���̃Q�[���I�u�W�F�N�g�ɕt������R���|�[�l���g�̍X�V
			UpdateComponents(_deltaTime);
			//Transform�̃��[���h�ϊ�
			ComputeWorldTransform();
		}
	}
	//�|�[�Y��ʂ̂Ƃ��R���|�[�l���g���X�V�����Ȃ�(�A�j���[�V�����Ȃǂ��~�߂邽��)
	else if(pauzingEvent== PauzingEvent::PausingEvent)
	{
		PausingUpdateGameObject();
	}
	else
	{
		PausingUpdateGameObject();
		UpdateComponents(_deltaTime);
	}
}

/*
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
/*
@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateGameObject(float _deltaTime)
{
}
/*
@fn �Q�[���I�u�W�F�N�g���Î~���ɍX�V�����A�b�v�f�[�g�֐�
@brief pauzingUpdate��true�̂Ƃ������Ă΂��X�V�֐�
*/
void GameObject::PausingUpdateGameObject()
{
}

/*
@fn ���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
*/
void GameObject::ProcessInput(const InputState& _keyState)
{
	if (state == Active)
	{
		//�R���|�[�l���g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
		for (auto comp : components)
		{
			comp->ProcessInput(_keyState);
		}
		//�Q�[���I�u�W�F�N�g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
		GameObjectInput(_keyState);
	}
}

/*
@fn ���͂������Ŏ󂯎��X�V�֐�
@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
*/
void GameObject::GameObjectInput(const InputState & _keyState)
{
}

/*
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

/*
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

/*
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
