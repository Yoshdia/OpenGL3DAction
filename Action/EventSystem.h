#pragma once
#include "GameObject.h"

class EventSystem :
	public GameObject
{
public:
	EventSystem(const Vector3& _pos);
	~EventSystem();

	void UpdateGameObject(float _deltaTime)override;
protected:
	bool trigger;
private:
	virtual void UpdateEventObject() {};
};

