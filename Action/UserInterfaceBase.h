#pragma once
#include "GameObject.h"
#include <string>

/*
@file UserInterfaceBase.h
@brief UI�̊��N���X
*/
class UserInterfaceBase :
	public GameObject
{
public:
	/*
	@param _pos �X�N���[�����W
	@param _spriteName �摜�ւ̃A�h���X
	@param _size �T�C�Y
	@param _drawOrder �`�揇
	*/
	UserInterfaceBase(const Vector3& _pos,const std::string& _spriteName, const Vector3& _size=Vector3(1,1,1), const int& _drawOrder=100);
	~UserInterfaceBase();
	protected:
	class SpriteComponent* spriteComponent;
};

