#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Texture;

class SpriteComponent : public Component
{
public:
	/**
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	*/
    SpriteComponent(GameObject* _owner, int _drawOrder = 100);
    ~SpriteComponent();

	/**
	@brief	�`�揈��
	@param	�g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
    virtual void Draw(Shader* _shader);

	/**
	@brief	�g�p����e�N�X�`���̐ݒ�
	@param	�g�p����e�N�X�`���̃|�C���^
	*/
    virtual void SetTexture(Texture* _texture);

	/**
	@brief	�e�N�X�`���̉������擾����
	@return �e�N�X�`���̉���
	*/
    int GetTexWidth() const { return textureWidth; }

	/**
	@brief	�e�N�X�`���̏c�����擾����
	@return �e�N�X�`���̏c��
	*/
    int GetTexHeight() const { return textureHeight; }

	/**
	@brief	DrawOrder���擾����
	@return DrawOrder�i���l�����Ȃ��قǑ����X�V�����j
	*/
	int GetDrawOrder() { return drawOrder; }

protected:

	//�N���X�̃|�C���^

    Texture* texture;

	//�`�悳��鏇�ԁi���l�����Ȃ��قǑ����X�V�����j
    int drawOrder;
	//�e�N�X�`���̉���
    int textureWidth;
	//�e�N�X�`���̏c��
    int textureHeight;
};

