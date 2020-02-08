#pragma once
#include "ParticleObject.h"

/*
@file CandleFireObject.h
@brief CandleStick���甭�����鉊�B�㏸���Ȃ��瓧���ɂȂ�
*/
class CandleFireObject :
	public ParticleObject
{
public:
	/*
	@param _pos ���W
	*/
	CandleFireObject(const Vector3& _pos);
	~CandleFireObject();
	/*
	@fn �����x���㏸������
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	//�����x
	float alfa;
};

