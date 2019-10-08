#pragma once
class VertexArray
{
public:
	/**
	@param	���_�o�b�t�@�̔z��̃|�C���^
	@param	���_��
	@param	�C���f�b�N�X�o�b�t�@�̔z��̃|�C���^
	@param	�C���f�b�N�X�̐�
	*/
	VertexArray(const float* _verts, unsigned int _numVerts,
		const unsigned int* _indices, unsigned int _numIndices);
	~VertexArray();

	/**
	@brief	���_�z����A�N�e�B�u�ɂ���i�`��Ɏg�p�ł���悤�ɂ���j
	*/
	void SetActive();

	/**
	@brief	�C���f�b�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐����擾����
	@return numIndices�i�C���f�b�N�X�̐��j
	*/
	unsigned int GetNumIndices() const { return numIndices; }

	/**
	@brief	���_�o�b�t�@�ɂ��钸�_�̐����擾����
	@return numVerts�i���_�̐��j
	*/
	unsigned int GetNumVerts() const { return numVerts; }

private:
	//���_�o�b�t�@�ɂ��钸�_�̐�
	unsigned int numVerts;
	//�C���f�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐�
	unsigned int numIndices;
	//���_�o�b�t�@��OpenGL ID
	unsigned int vertexBuffer;
	//�C���f�b�N�X�o�b�t�@��OpenGL ID
	unsigned int indexBuffer;
	//���_�z��I�u�W�F�N�g��OpenGL ID
	unsigned int vertexArray;
};

