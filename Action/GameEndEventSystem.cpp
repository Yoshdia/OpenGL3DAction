#include "GameEndEventSystem.h"
#include "ColliderComponent.h"

/*
@param _pos ���W
*/
GameEndEventSystem::GameEndEventSystem(const Vector3 & _pos) :
	EventSystem(_pos),
	end(false)
{
	SetScale(Vector3(500, 500, 500));
	ColliderComponent* collider = new ColliderComponent(this, 100, Vector3(500, 500, 500), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
}

GameEndEventSystem::~GameEndEventSystem()
{
}
/*
@fn �v���C���[�ƏՓ˂����Ƃ��Ƀt���O�����Ă�N���X
*/
void GameEndEventSystem::OnTriggerEnter(ColliderComponent * _pair)
{
	if (_pair->GetObjectTag() == Tag::PlayerTag)
	{
		end = true;
	}
}
