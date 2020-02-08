#include "LoadSceneObject.h"
#include "NoActionEnemyForLoad.h"
#include "Renderer.h"
#include "MainCameraObject.h"

LoadSceneObject::LoadSceneObject(std::function<void(SceneName)> _SetSceneFunc) :
	SceneObjectBase(_SetSceneFunc)
{
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	mainCamera->SetViewMatrixLerpObject(Vector3(0, 0, 0), Vector3(0, 70, -120));
	//new NoActionEnemyForLoad(Vector3(100, 0, 0), EnemyType::MeleeType,true);
}

LoadSceneObject::~LoadSceneObject()
{
}

void LoadSceneObject::UpdateGameObject(float _deltaTime)
{
	if (t < 0)
	{
		SetSceneFunc(SceneName::PlayScene);
	}
	else
	{
		t--;
	}
}
