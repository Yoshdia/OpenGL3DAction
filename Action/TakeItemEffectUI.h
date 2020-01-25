#pragma once
#include "UserInterfaceBase.h"

class TakeItemEffectUI :
	public UserInterfaceBase
{
public:
	TakeItemEffectUI(const Vector3& _pos);
	~TakeItemEffectUI();

	void UpdateGameObject(float _deltaTime)override;
private:
	float spriteScale;
};

