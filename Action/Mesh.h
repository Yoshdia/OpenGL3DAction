#pragma once

#include <vector>
#include <string>
#include "Math.h"

class Renderer;
class VertexArray;
class Texture;

class Mesh
{
public:
    Mesh();
    ~Mesh();
	/**
	@brief  ���b�V���f�[�^�̓ǂݍ���
	@param	���[�h���������b�V���̃t�@�C����
	@param	Renderer�N���X�̃|�C���^
	@return true : ���� , false : ���s
	*/
    bool Load(const std::string& _fileName, Renderer* _renderer);

	/**
	@brief  ���[�h�������b�V���f�[�^�̉��
	*/
    void Unload();
	
	/**
	@brief	���b�V���̒��_�z����擾����
	@return	VertexArray�^�̃|�C���^
	*/
    VertexArray* GetVertexArray() { return vertexArray; }

	/**
	@brief	�C���f�N�X���烁�b�V���Ɏg���Ă���e�N�X�`�����擾����
	@param	�e�N�X�`���̃C���f�b�N�X
	@return Texture�N���X�̃|�C���^
	*/
    Texture* GetTexture(size_t _index);

	/**
	@brief	�C���f�N�X���烁�b�V���Ɏg���Ă���e�N�X�`�����擾����
	@param	�e�N�X�`���̃C���f�b�N�X
	@return Texture�N���X�̃|�C���^
	*/
    const std::string& GetShaderName() const { return shaderName; }

	/**
	@brief	�I�u�W�F�N�g��Ԃŋ��E���̔��a���擾����
	@return radius�i���a�j
	*/
    float GetRadius() const { return radius; }

	/**
	@brief	���ʔ��ː����̑傫�����擾����
	@return specPower�i���ʔ��ː����j
	*/
    float GetSpecPower() const { return specPower; }

	std::vector<Vector3> GetVerts() {return verts;}

private:
    //���̃��b�V���Ɏg���e�N�X�`���̃|�C���^�̉ϒ��R���e�i
    std::vector<Texture*> textures;
	//���̃��b�V���Ɏg�����_�f�[�^
	std::vector<Vector3> verts;

	//�N���X�̃|�C���^

    VertexArray* vertexArray;

    //���̃��b�V���Ɏg���V�F�[�_�[�̖��O
    std::string shaderName;
    //�I�u�W�F�N�g��Ԃł̋��E���̔��a
    float radius;
    //���ʔ��ː����̑傫��
    float specPower;
};