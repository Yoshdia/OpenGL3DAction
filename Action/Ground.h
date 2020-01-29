#pragma once
#include "GameObject.h"
class Ground :
	public GameObject
{
public:
	Ground(const Vector3& _p,const Vector3& _size,const Tag& _objectTag=Tag::GroundTag);
	~Ground();
};

