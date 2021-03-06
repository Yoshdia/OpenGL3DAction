#include "CandleStick.h"
#include "ColliderComponent.h"

#include "Renderer.h"
#include "ParticleComponent.h"
#include "Texture.h"
#include "CandleFireObject.h"

/*
@param _pos 座標
*/
CandleStick::CandleStick(Vector3 _pos) :
	GameObject(),
	ignition(false),
	ignitionCount(15)
{
	SetPosition(_pos);
	SetScale(10);
	tag = Tag::CandleStickTag;
	collider = new ColliderComponent(this, 100, Vector3(3, 3, 3), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

	stickParticle = new ParticleComponent(this);
	Texture* noFire = RENDERER->GetTexture("Assets/image/Candle/CandleNoFire.png");
	stickParticle->SetTextureID(noFire->GetTextureID());
	stickParticle->SetDrawOrder(100);
	stickParticle->SetScale(10);

	lightParticle = new ParticleComponent(this);
	lightParticle->SetDrawOrder(70);
	lightParticle->SetTextureID(RENDERER->GetTexture("Assets/Image/Candle/Candle.png")->GetTextureID());
	lightParticle->SetScale(30);
	lightParticle->SetVisible(false);
	lightParticle->SetAlpha(0.3f);
}

CandleStick::~CandleStick()
{
}

/*
@fn 一定間隔ごとに炎のCandleFireObjectクラスを生成する
*/
void CandleStick::UpdateGameObject(float _deltaTime)
{
	//火がともっているか
	if (ignition)
	{
		lightParticle->SetScale(30.0f + rand() % 2);

		ignitionCount++;
		if (ignitionCount >= 15)
		{
			ignitionCount = 0;
			new CandleFireObject(position+Vector3(0,-10,0));
		}
	}
}

/*
@fn プレイヤーと衝突したらフラグをp建てる
*/
void CandleStick::OnTriggerEnter(ColliderComponent * colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::PlayerTag && !ignition)
	{
		ignition = true;
		collider->SetScale(Vector3(500, 500, 500));
		lightParticle->SetVisible(true);
	}
}
