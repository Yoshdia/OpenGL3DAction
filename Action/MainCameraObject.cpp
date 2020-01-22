#include "MainCameraObject.h"
#include "Renderer.h"
#include "ColliderComponent.h"

MainCameraObject::MainCameraObject() :
	GameObject(true)
{
	SetPosition(Vector3::Zero);
	tag = Tag::Camera;
	ColliderComponent* comp = new ColliderComponent(this, 100, Vector3(1200, 1200, 800), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag,Vector3(0,0,400));
	comp->SetCollidedCamera();
}


MainCameraObject::~MainCameraObject()
{
}

void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	Vector3 pos = offsetPos + position;
	pos.x = lerpObject.x + offsetPos.x;
	pos.y = lerpObject.y + offsetPos.y;
	pos.z = lerpObject.z + offsetPos.z;
	position = Vector3::Lerp(position, pos, _deltaTime * 3.0f);
	Vector3 aa = position;
	aa.z = 0;

	SetPosition(position);
	Matrix4 v = Matrix4::CreateLookAt(position, aa, Vector3::UnitY);
	RENDERER->SetViewMatrix(v);
}

void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _offset, const Vector3 & _parentPos)
{
	hasParentObject = true;
	offsetPos = _offset;
	lerpObject = _parentPos;
}
