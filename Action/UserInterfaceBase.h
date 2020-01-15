#pragma once
#include "GameObject.h"
class UserInterfaceBase :
	public GameObject
{
public:
	UserInterfaceBase(const Vector3& _pos,const std::string& spriteName, const int& _drawOrder=100);
	~UserInterfaceBase();
};

