#pragma once
#include "ObstacleBox.h"


class MeshComponent;
class BoxCollider;
class PlayerObject;

class SlidingObject : public ObstacleBox
{
public:
	SlidingObject();
	~SlidingObject();

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

	virtual void OnCollision(const GameObject& _hitObject) override;

	void HitObstacle(const ObstacleBox & _hitObstacle);

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	GameObject* player;
};

