#pragma once

#include <string>

class Texture
{
public:
    Texture();
    ~Texture();
	/**
	@brief	�e�N�X�`���̃��[�h
	@param	�e�N�X�`���̃t�@�C����
	@return	true : ���� , false : ���s
	*/
	bool Load(const std::string& _fileName);
	/**
	@brief	���[�h�����e�N�X�`���̉��
	*/
	void Unload();

	/**
	@brief	�e�N�X�`�����A�N�e�B�u�ɂ���
	*/
	void SetActive();

	/**
	@brief	�e�N�X�`���̉������擾����
	@return ����
	*/
	int GetWidth() const { return width; }

	/**
	@brief	�e�N�X�`���̏c�����擾����
	@return �c��
	*/
	int GetHeight() const { return height; }

private:
	unsigned int textureID;

	//�e�N�X�`���̉���
	int width;
	//�e�N�X�`���̏c��
	int height;
};

