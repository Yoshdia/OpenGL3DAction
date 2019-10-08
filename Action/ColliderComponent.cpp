#include "ColliderComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "PhysicsWorld.h"

/**
@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
*/
ColliderComponent::ColliderComponent(GameObject* _owner, int _updateOrder, int _collisionOrder)
	: Component(_owner, _updateOrder)
	, isTrigger(false)
	, collisionOrder(_collisionOrder)
{
}


ColliderComponent::~ColliderComponent()
{
}

