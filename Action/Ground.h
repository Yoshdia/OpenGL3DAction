#pragma once
#include "GameObject.h"

/*
@file Ground.h
@brief �v���C���[�Ɣ���̂���n�ʃN���X
*/
class Ground :
	public GameObject
{
public:
	/*
	@param _p ���W
	@param _size �T�C�Y
	@param _objectTag �^�O
	*/
	Ground(const Vector3& _p,const Vector3& _size,const Tag& _objectTag=Tag::GroundTag);
	~Ground();
};

