#pragma once
#include "GameObject.h"

/*
 @file FootSole.h
 @brief GameObject�̑����ɔz�u����p�l����̃I�u�W�F�N�g�AgroundTag���������Ă���I�u�W�F�N�g�ɐڐG����ƃt���O��|��
	*/
class FootSole :
	public GameObject
{
public:
	/*
   @param parentPosition �e�ɂȂ�I�u�W�F�N�g�̍��W�A�h���X
   @param _jumped �e�ɂȂ�I�u�W�F�N�g�̃W�����v�t���O�A�h���X�BFootSole��groundTag�ƐڐG�����Ƃ���false�ɂ���
 */
	FootSole(Vector3& parentPosition, bool& _jumped);
	~FootSole();

	void UpdateGameObject(float _deltaTime)override;
private:
	void OnTriggerStay(ColliderComponent* colliderPair)override;
	//�e�I�u�W�F�N�g�̍��W
	Vector3* parentPosition;
	//groundTag�ƐڐG���Ă��邩
	bool *noLand;
	//���M�̍��W�AparentPosition�Ƒ�����position�ɂ���
	Vector3 footPos;
};

