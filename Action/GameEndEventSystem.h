#pragma once
#include "EventSystem.h"
class GameEndEventSystem :
	public EventSystem
{
public:
	GameEndEventSystem(const Vector3& _pos);
	~GameEndEventSystem();
	bool GetEndFlag() { return end; }
private:
	void OnTriggerEnter(ColliderComponent* _pair)override;
	bool end;
};

