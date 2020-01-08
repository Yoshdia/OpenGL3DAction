#include "TestModel.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "RotateComponent.h"

TestModel::TestModel()
{
	SetPosition(Vector3(-500, 100, 0));
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Weapon/SK_Forging_Mallet_02.gpmesh"));
	RotateComponent* ro= new RotateComponent(this);
	ro->SetRotation(90, Vector3::UnitY);
	SetScale(4);
}


TestModel::~TestModel()
{
}
