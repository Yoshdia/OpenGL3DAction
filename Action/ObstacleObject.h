#pragma once
#include "GameObject.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include <vector>

class MeshComponent;
class BoxCollider;
class PlayerObject;
class ObstacleMapLoder;

namespace StaticObstacle
{
	static const int ObstacleMaxNum = 30;
	static const float ObstacleDistanceNum = 3000.0f;
}

class ObstacleObject : public GameObject
{
public:
	ObstacleObject(int _i);
	~ObstacleObject();

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime) override;

	virtual void SetPosition(const Vector3& _pos) override { position = _pos; recomputeWorldTransform = true; }

private:

	static ObstacleMapLoder* mapLoder;
    void CreateObstacle(float _depth);
	GameObject* player;
	int i;

};