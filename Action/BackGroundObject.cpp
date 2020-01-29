#include "BackGroundObject.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "RotateComponent.h"
#include "MainCameraObject.h"

int BackGroundObject::i = 0;

BackGroundObject::BackGroundObject(const Vector3 & _pos, const Vector3 & _size, const std::string & _fileName)
{
	i++;
	n = i;
	SetPosition(_pos);
	SetScale(_size);
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Stage/" + _fileName + ".gpmesh"));
	RotateComponent* ro = new RotateComponent(this);
	//ro->SetRotation(90, Vector3::UnitY);
}

BackGroundObject::~BackGroundObject()
{
}

void BackGroundObject::UpdateGameObject(float deltaTime)
{
	if (n == 3)
	{
		mainCamera->SetViewMatrixLerpObject(Vector3(0, 0, -500), position); 
	}
}
