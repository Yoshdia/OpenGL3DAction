#pragma once
#include "ParticleObject.h"

/*
@file CandleFireObject.h
@brief CandleStickから発生する炎。上昇しながら透明になる
*/
class CandleFireObject :
	public ParticleObject
{
public:
	/*
	@param _pos 座標
	*/
	CandleFireObject(const Vector3& _pos);
	~CandleFireObject();
	/*
	@fn 透明度を上昇させる
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	//透明度
	float alfa;
};

