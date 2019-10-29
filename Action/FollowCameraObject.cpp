#include "FollowCameraObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "FollowCamera.h"
#include "MoveComponent.h"

FollowCameraObject::FollowCameraObject()
	:GameObject()
{
	mMeshComp = new MeshComponent(this);
	mMeshComp->SetMesh(RENDERER->GetMesh("Assets/Sphere.gpmesh"));
	SetPosition(Vector3(0.0f, -0.0f, 100.0f));
	//SetPosition(Vector3(200.0f, -75.0f, 0.0f));
	SetScale(10.0f);

	mMoveComp = new MoveComponent(this);
	mMoveComp->SetForwardKey(SDL_SCANCODE_W);
	mMoveComp->SetBackKey(SDL_SCANCODE_S);
	mMoveComp->SetMaxForwardSpeed(400.0f);
	mCameraComp = new FollowCamera(this);
	mCameraComp->SetForwardKey(SDL_SCANCODE_W);
	mCameraComp->SetBackKey(SDL_SCANCODE_S);
	mCameraComp->SetRightKey(SDL_SCANCODE_D);
	mCameraComp->SetLeftKey(SDL_SCANCODE_A);
	mCameraComp->SnapToIdeal();

}

void FollowCameraObject::SetVisible(bool _visible)
{
	mMeshComp->SetVisible(_visible);
}
