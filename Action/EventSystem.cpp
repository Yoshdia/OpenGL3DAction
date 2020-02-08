#include "EventSystem.h"


/*
@param _pos ���W
*/
EventSystem::EventSystem(const Vector3 & _pos):
	GameObject(),
	trigger(false)
{
	SetPosition(_pos);
}

EventSystem::~EventSystem()
{
}

void EventSystem::UpdateGameObject(float _deltaTime)
{
	UpdateEventObject();
	if (trigger)
	{
		SetState(State::Dead);
	}
}

