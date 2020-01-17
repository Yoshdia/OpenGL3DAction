#include "TestModel.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "RotateComponent.h"

TestModel::TestModel()
{
	SetPosition(Vector3(-500, -9000, 100));
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Stage/SM_Env_Ice_Cliffs_CliffWall_01b.gpmesh"));
	RotateComponent* ro= new RotateComponent(this);
	ro->SetRotation(90, Vector3::UnitY);
	SetScale(Vector3(0.1f,5,5));
}


TestModel::~TestModel()
{
}
