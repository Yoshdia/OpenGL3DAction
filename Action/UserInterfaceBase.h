#pragma once
#include "GameObject.h"
class UserInterfaceBase :
	public GameObject
{
public:
	UserInterfaceBase(const Vector3& _pos,const std::string& spriteName);
	~UserInterfaceBase();
};

