#include "CandleStick.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
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

	MeshComponent* mesh = new MeshComponent(this);
	mesh->SetMesh(RENDERER->GetMesh("Assets/Model/Stage/untitled.gpmesh"));

	particle = new ParticleComponent(this, 70);
	particle->SetTextureID(RENDERER->GetTexture("Assets/Image/16.png")->GetTextureID());
	particle->SetScale(30);
	particle->SetVisible(false);
	particle->SetAlpha(0.3f);
}

CandleStick::~CandleStick()
{
}

void CandleStick::UpdateGameObject(float _deltaTime)
{
	if (ignition)
	{
		particle->SetScale(30.0f + rand() % 5);
	}
}

void CandleStick::OnTriggerEnter(ColliderComponent * colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::PlayerTag && !ignition)
	{
		ignition = true;
		collider->SetScale(Vector3(500, 500, 500));
		particle->SetVisible(true);
	}
}
