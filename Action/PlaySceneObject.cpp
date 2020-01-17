#include "PlaySceneObject.h"
#include "Renderer.h"
#include "StageCreater.h"

#include "TestModel.h"
#include "BackGroundObject.h"
#include "PlayerCharacter.h"

PlaySceneObject::PlaySceneObject(std::function<void(SceneName)> _SetSceneFunc) :
	SceneObjectBase(_SetSceneFunc),
	player(nullptr)
{
	// Setup lights
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	new TestModel;
	StageCreater* stageCreater= new StageCreater();
	
	if (!stageCreater->OpenFile())
	{
		player= stageCreater->CreatePlayer();
		stageCreater->CreateStage();
	}
	//new BackGroundObject();
}


PlaySceneObject::~PlaySceneObject()
{
}

void PlaySceneObject::UpdateGameObject(float _deltaTime)
{
	//if (player->GetGameEnd())
	//{
	//	player = nullptr;
	//	SetSceneFunc(SceneName::ResultScene);
	//}
}
