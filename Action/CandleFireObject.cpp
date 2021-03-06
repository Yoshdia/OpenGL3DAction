#include "CandleFireObject.h"
#include "ParticleComponent.h"

/*
@param _pos 座標
*/
CandleFireObject::CandleFireObject(const Vector3 & _pos):
	ParticleObject(_pos,"Assets/Image/Candle/Fire.png",120.0f,50),
	alfa(1)
{
}

CandleFireObject::~CandleFireObject()
{
}

/*
@fn 透明度を上昇させる
*/
void CandleFireObject::UpdateGameObject(float _deltaTime)
{
	SetPosition(position + Vector3(0, 0.3f, 0));
	if (alfa <= 0.3f)
	{
		SetState(State::Dead);
	}
	else
	{
		alfa-=0.02f;
		particle->SetAlpha(alfa);
	}
}
