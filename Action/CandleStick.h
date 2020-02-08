#pragma once
#include "GameObject.h"

/*
@file CandleStick.h
@bief �v���C���[����x�Փ˂���Ɖ΂�����A�͈͓��̃v���C���[���񕜂���I�u�W�F�N�g
*/
class CandleStick :
	public GameObject
{
public:
	/*
	@param _pos ���W
	*/
	CandleStick(Vector3 _pos=Vector3(0,0,0));
	~CandleStick();
	/*
	@fn ���Ԋu���Ƃɉ���CandleFireObject�N���X�𐶐�����
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	/*
	@fn �v���C���[�ƏՓ˂�����t���O��p���Ă�
	*/
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	//�Փ˔�����s���N���X
	class ColliderComponent* collider;
	//�X�̉摜�N���X
	class ParticleComponent* stickParticle;
	//������������̖�����̉摜�N���X
	class ParticleComponent* lightParticle;
	//�΂��Ƃ�������
	bool ignition;
	//���𐶐�����Ԋu
	int ignitionCount;
};

