#include "CandleStick.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"

CandleStick::CandleStick(Vector3 _pos):
	GameObject(),
	ignition(false)
{
	SetPosition(_pos);
	SetScale(10);
	tag = Tag::CandleStickTag;
	collider = new ColliderComponent(this, 100, Vector3(10, 10, 10), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

	MeshComponent* mesh = new MeshComponent(this);
	mesh->SetMesh(RENDERER->GetMesh("Assets/Model/Stage/untitled.gpmesh"));
}

CandleStick::~CandleStick()
{
}

void CandleStick::UpdateGameObject(float _deltaTime)
{

}

void CandleStick::OnTriggerEnter(ColliderComponent * colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::PlayerTag&&!ignition)
	{
		ignition = true;
		printf("ignition\n");
		SetScale(scale * 5);
		collider->SetScale(Vector3(500,500,500));
	}
}
