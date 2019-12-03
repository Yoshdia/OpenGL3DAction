#pragma once

#include <glew.h>
#include <string>
#include "Math.h"

class Shader
{
public:
    Shader();
    ~Shader();
	/**
	@brief	���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�̃��[�h
	@param	���_�V�F�[�_�[�̃t�@�C����
	@param	���_�V�F�[�_�[�̃t�@�C����
	@return	true : ���� , false : ���s
	*/
	bool Load(const std::string& _vertName,const std::string& _fragName);
	/**
	@brief	���[�h�����V�F�[�_�[�̉��
	*/
	void Unload();

	/**
	@brief	�V�F�[�_�[�v���O�������A�N�e�B�u�ɂ���
	*/
	void SetActive();

	/**
	@brief	�s���Uniform�ϐ���ݒ肷��
	@param	�ݒ肷��Uniform�ϐ���
	@param	�ݒ肷��s��
	*/
	void SetMatrixUniform(const char* _name , const Matrix4& _matrix);
	void SetMatrixUniforms(const char* _name, Matrix4* _matrices, unsigned _count);
    /**
    @brief	Vector3��Uniform�ϐ���ݒ肷��
    @param	�ݒ肷��Uniform�ϐ���
    @param	�ݒ肷��Vector3
    */
    void SetVectorUniform(const char* _name, const Vector3& _vector);

    /**
    @brief	float��Uniform�ϐ���ݒ肷��
    @param	�ݒ肷��Uniform�ϐ���
    @param	�ݒ肷��float
    */
    void SetFloatUniform(const char* _name, const float& _value);

private:
	/**
	@brief	�V�F�[�_�[���R���p�C������
	@param	�R���p�C������V�F�[�_�[�̃t�@�C����
	@param	�V�F�[�_�[�̎��
	@param	�V�F�[�_�[��ID�p�̎Q�ƕϐ�
	@return	true : ���� , false : ���s
	*/
	bool CompileShader(const std::string& _fileName,GLenum _shaderType,GLuint& _outShader);

	/**
	@brief	�V�F�[�_�[���R���p�C���o���Ă��邩�m�F
	@param	�V�F�[�_�[��ID
	@return	true : ���� , false : ���s
	*/
	bool IsCompiled(GLuint _shader);
	/**
	@brief	�V�F�[�_�[�������N�o���Ă��邩�m�F
	@param	�V�F�[�_�[��ID
	@return	true : ���� , false : ���s
	*/
	bool IsVaildProgram();

	GLuint vertexShader;
	GLuint fragShader;
	GLuint shaderProgram;
};

