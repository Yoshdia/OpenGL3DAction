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
	FootSole(GameObject* _parent);
	~FootSole();

	void UpdateGameObject(float _deltaTime)override;

	bool GetGroundFlag() { return noGround; }
private:
	void OnTriggerStay(ColliderComponent* colliderPair)override;
	GameObject* parent;
	Vector3 parentPos;
	//���M�̍��W�AparentPosition�Ƒ�����position�ɂ���
	Vector3 footPos;
	bool noGround;
};

