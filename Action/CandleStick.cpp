#include "CandleStick.h"
#include "ColliderComponent.h"

#include "Renderer.h"
#include "ParticleComponent.h"
#include "Texture.h"

CandleStick::CandleStick(Vector3 _pos) :
	GameObject(),
	ignition(false)
{
	SetPosition(_pos);
	SetScale(10);
	tag = Tag::CandleStickTag;
	collider = new ColliderComponent(this, 100, Vector3(1, 1, 1), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

	stickParticle = new ParticleComponent(this, 100);
	fire = RENDERER->GetTexture("Assets/image/FireCandle.png");
	Texture* noFire = RENDERER->GetTexture("Assets/image/CandleNoFire.png");
	stickParticle->SetTextureID(noFire->GetTextureID());
	stickParticle->SetScale(10);

	lightParticle = new ParticleComponent(this, 70);
	lightParticle->SetTextureID(RENDERER->GetTexture("Assets/Image/Candle.png")->GetTextureID());
	lightParticle->SetScale(30);
	lightParticle->SetVisible(false);
	lightParticle->SetAlpha(0.3f);
}

CandleStick::~CandleStick()
{
}

void CandleStick::UpdateGameObject(float _deltaTime)
{
	if (ignition)
	{
		lightParticle->SetScale(30.0f + rand() % 2);
	}
}

void CandleStick::OnTriggerEnter(ColliderComponent * colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::PlayerTag && !ignition)
	{
		ignition = true;
		collider->SetScale(Vector3(500, 500, 500));
		lightParticle->SetVisible(true);
		stickParticle->SetTextureID(fire->GetTextureID());
	}
}
