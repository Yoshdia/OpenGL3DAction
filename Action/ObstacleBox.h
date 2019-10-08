#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class PlayerObject;

class ObstacleBox :public GameObject
{
public:
	ObstacleBox();
	~ObstacleBox();

	virtual void OnCollision(const GameObject& _hitObject) override;

	virtual void ResetObstacle();
	virtual void UseObstacle();

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	GameObject* player;
};

