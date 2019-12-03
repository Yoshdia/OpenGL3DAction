#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Mesh;

class MeshComponent : public Component
{
public:
	/**
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	*/
    MeshComponent(GameObject* _owner);
    ~MeshComponent();

	/**
	@brief�@�`�揈��
	@param	�g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
    virtual void Draw(Shader* _shader);

	/**
	@brief�@���b�V���R���|�[�l���g���g��Mesh�̐ݒ�
	@param	�ݒ肷��Mesh�N���X�̃|�C���^
	*/
    virtual void SetMesh(Mesh* _mesh) { mMesh = _mesh; }

	virtual Mesh* GetMesh() { return mMesh; }

	/**
	@brief�@���b�V���R���|�[�l���g���g��Texture�C���f�b�N�X�̐ݒ�
	@param	�ݒ肷��Texture�C���f�b�N�X�̐�
	*/
    void SetTextureIndex(size_t _index) { mTextureIndex = _index; }

	/**
	@brief�@�`������邩�ǂ�����ݒ�
	@param	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	void SetVisible(bool _visible) { visible = _visible; }

	/**
	@brief�@�`������邩�ǂ������擾����
	@return	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	bool GetVisible() const { return visible; }

protected:

	//�N���X�̃|�C���^

    Mesh* mMesh;
    size_t mTextureIndex;

	//�`������邩�ǂ���
	bool visible;
};

