#pragma once
#include <vector>
#include <functional>
#include "Math.h"

class Game;
class Vector3;
class Matrix4;
class Component;
struct InputState;
class ColliderComponent;

/**
@brief	�Q�[���I�u�W�F�N�g�̏��
*/
enum State
{
	Active,
	Paused,
	Dead
};

/*
	@enum�@GameObject�^�O
	�Փˑ���𔻕ʂ��邽�߂Ɏg�p
*/
enum Tag
{
	PlayerTag,
	GroundTag,
	null,
};

class GameObject
{
public:
	/**
	@param	�Q�[���N���X�̃|�C���^
	*/
	GameObject();
	virtual ~GameObject();

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float _deltaTime);

	/**
	@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateComponents(float _deltaTime);

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime) ;

	void ProcessInput(const InputState& _keyState);
	virtual void GameObjectInput(const InputState& _keyState) ;

	/**
	@brief	�R���|�[�l���g��ǉ�����
	@param	�ǉ�����R���|�[�l���g�̃|�C���^
	*/
	void AddComponent(Component* _component);

	/**
	@brief	�R���|�[�l���g���폜����
	@param	�폜����R���|�[�l���g�̃|�C���^
	*/
	void RemoveComponent(Component* _component);

	/**
	@brief	Transform�̃��[���h�ϊ�
	*/
	void ComputeWorldTransform();

	/**
	@brief�@�I�u�W�F�N�g�̃|�W�V�������擾����
	@return	position
	*/
    const Vector3& GetPosition() const { return position; }

	/**
	@brief�@�I�u�W�F�N�g�̃|�W�V������ݒ肷��
	@param	position
	*/
    virtual void SetPosition(const Vector3& _pos) { position = _pos; recomputeWorldTransform = true; }

	/**
	@brief�@�I�u�W�F�N�g�̃X�P�[�����擾����
	@return	scale
	*/
    float GetScale() const { return scale; }

	/**
	@brief�@�I�u�W�F�N�g�̃X�P�[����ݒ肷��
	@param	scale
	*/
	virtual void SetScale(float _scale) { scale = _scale;  recomputeWorldTransform = true; }

	/**
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I�����擾����
	@return	rotation�iQuaternion�^�j
	*/
    const Quaternion& GetRotation() const { return rotation; }

	/**
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I����ݒ肷��
	@param	rotation�iQuaternion�^�j
	*/
	virtual void SetRotation(const Quaternion& _qotation) { rotation = _qotation;  recomputeWorldTransform = true; }

	/**
	@brief�@�I�u�W�F�N�g�̏�Ԃ��擾����
	@return	state
	*/
	State GetState() const { return state; }

	/**
	@brief�@�I�u�W�F�N�g�̏�Ԃ�ݒ肷��
	@param	state
	*/
	virtual void SetState(State _state) { state = _state; }

	/**
	@brief�@�I�u�W�F�N�g�̃��[���h�s����擾����
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/**
	@brief�@�I�u�W�F�N�g�̑O����\���x�N�g�����擾����
	@param	forward(Vector3�^)
	*/
    Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, rotation); }

	/**
	@brief�@�I�u�W�F�N�g�̉E��\���x�N�g�����擾����
	@param	right(Vector3�^)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, rotation); }

	/**
	@brief�@�I�u�W�F�N�g�̏��\���x�N�g�����擾����
	@param	up(Vector3�^)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, rotation); }

	Tag GetTag() const { return tag; }

	int GetObjectId() {return myObjectId;};
protected:
	virtual void OnTriggerEnter( ColliderComponent* colliderPair) {};
	virtual void OnTriggerStay( ColliderComponent* colliderPair) {};

	//�Q�[���I�u�W�F�N�g�̏��
	State state;
	//�Q�[���I�u�W�F�N�g�̃^�O
	Tag tag;
	//�Q�[���I�u�W�F�N�g��ID
	static int gameObjectId;
	int myObjectId;

	//Transform
	Vector3 position;
	Quaternion rotation;	
	float scale;
	Matrix4 worldTransform;
	//���[���h�ϊ��̏������s���K�v�������邩
	bool recomputeWorldTransform;

	//�A�^�b�`����Ă���R���|�[�l���g
	std::vector<class Component*>components;

};

