#pragma once
#include "GameObject.h"
#include <string>

/*
@file ParticleObject.h
@brief �p�[�e�B�N���I�u�W�F�N�g�B�Œ�I�u�W�F�N�g�ȂǂɎg�p
*/
class ParticleObject :
	public GameObject
{
public:
	/*
	@param _pos ���W
	@param _fileName �摜�A�h���X
	@param _scale �T�C�Y
	@param drawOrder �`�揇
	*/
	ParticleObject(const Vector3& _pos, const std::string& _fileName,const float& _scale,const int& drawOrder=100);
	~ParticleObject();
protected:
	//�p�[�e�B�N���̊Ǘ��ƕ`����s���N���X
	class ParticleComponent* particle;
};

