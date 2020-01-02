#include "MainCameraObject.h"
#include "Renderer.h"


MainCameraObject::MainCameraObject():
	GameObject()
{
	SetPosition(Vector3::Zero);
}


MainCameraObject::~MainCameraObject()
{
}

void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	if (!hasParentObject)
	{
		printf("Camera[I don't have parent!]");
		return;
	}
	Vector3 pos = offsetPos + position;
	pos.x = lerpObject.x + offsetPos.x;
	pos.y = lerpObject.y + offsetPos.y;
	pos.z = lerpObject.z + offsetPos.z;
	position = Vector3::Lerp(position, pos, _deltaTime * 3.0f);
	Vector3 aa = position;
	aa.z = 0;

	Matrix4 v = Matrix4::CreateLookAt(position, aa, Vector3::UnitY);
	RENDERER->SetViewMatrix(v);
}

void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _offset, const Vector3 & _parentPos)
{
	hasParentObject = true;
	offsetPos = _offset;
	lerpObject = _parentPos;
}
