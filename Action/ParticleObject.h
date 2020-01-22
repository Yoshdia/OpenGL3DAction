#pragma once
#include "GameObject.h"
class ParticleObject :
	public GameObject
{
public:
	ParticleObject(const std::string& _fileName);
	~ParticleObject();
};

