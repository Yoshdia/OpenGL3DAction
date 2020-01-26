#pragma once
#include "GameObject.h"
#include <string>

class UserInterfaceBase :
	public GameObject
{
public:
	UserInterfaceBase(const Vector3& _pos,const std::string& spriteName, const Vector3& _size=Vector3(1,1,1), const int& _drawOrder=100);
	~UserInterfaceBase();
	protected:
	class SpriteComponent* spriteComponent;
};

