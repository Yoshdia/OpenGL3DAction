#include "VertexArray.h"
#include <glew.h>

/**
@param	���_�o�b�t�@�̔z��̃|�C���^
@param	���_��
@param	�C���f�b�N�X�o�b�t�@�̔z��̃|�C���^
@param	�C���f�b�N�X�̐�
*/
VertexArray::VertexArray(const float* _verts, unsigned int _numVerts,
	const unsigned int* _indices, unsigned int _numIndices)
	:numVerts(_numVerts)
	,numIndices(_numIndices)
{
	// ���_�z��̍쐬
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// ���_�o�b�t�@�̍쐬
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _numVerts * 8 * sizeof(float), _verts, GL_STATIC_DRAW);

	// �C���f�N�X�o�b�t�@�̍쐬
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(unsigned int), _indices, GL_STATIC_DRAW);

	//�ŏ��̒��_������L���Ɂi�ʒu���W�j
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,						//���_�����C���f�b�N�X�i�ʒu���W�j
		3,						//�v�f�̐�
		GL_FLOAT,				//�v�f�̌^
		GL_FALSE,				//�iGL_FLOAT�ɂ͎g��Ȃ��j
		sizeof(float) * 8,		//�e���_�̃T�C�Y
		0						//���_�f�[�^�̊J�n�ʒu���炱�̑����܂ł̃I�t�Z�b�g
	);
	//��2�̒��_������L���Ɂi�@���x�N�g���j
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,						//���_�����C���f�b�N�X�i�@���x�N�g���j
		3,						//�v�f�̐�
		GL_FLOAT,				//�v�f�̌^
		GL_FALSE,				//�iGL_FLOAT�ɂ͎g��Ȃ��j
		sizeof(float) * 8,		//�e���_�̃T�C�Y
		reinterpret_cast<void*>(sizeof(float) * 3));	//�I�t�Z�b�g�|�C���^
    //��3�̒��_������L���Ɂi�e�N�X�`�����W�j
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,						//���_�����C���f�b�N�X�i�e�N�X�`�����W�j
        2,						//�v�f�̐��iUV��2�j
        GL_FLOAT,				//�v�f�̌^
        GL_FALSE,				//�iGL_FLOAT�ɂ͎g��Ȃ��j
        sizeof(float) * 8,		//�e���_�̃T�C�Y
        reinterpret_cast<void*>(sizeof(float) * 6));	//�I�t�Z�b�g�|�C���^
}


VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

/**
@brief	���_�z����A�N�e�B�u�ɂ���
*/
void VertexArray::SetActive()
{
	glBindVertexArray(vertexArray);
}
