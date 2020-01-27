#include "PlaySceneObject.h"
#include "Renderer.h"
#include "StageCreater.h"

#include "TestModel.h"
#include "BackGroundObject.h"
#include "PlayerCharacter.h"
#include "GameEndEventSystem.h"
#include "InputSystem.h"
#include "PauseScreen.h"

#include "DebugBox.h"

PlaySceneObject::PlaySceneObject(std::function<void(SceneName)> _SetSceneFunc) :
	SceneObjectBase(_SetSceneFunc),
	player(nullptr),
	endSystem(nullptr),
	pausingScreen(nullptr)
{
	// Setup lights
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	//new TestModel;
	new BackGroundObject();
	StageCreater* stageCreater = new StageCreater();

	if (!stageCreater->OpenFile())
	{
		player = stageCreater->CreatePlayer();
		stageCreater->CreateStage();
		endSystem = stageCreater->GetEvent();
	}
}


PlaySceneObject::~PlaySceneObject()
{
	if (pausingScreen != nullptr)
	{
		pausingScreen = nullptr;
	}
}

void PlaySceneObject::UpdateGameObject(float _deltaTime)
{
	if (player != nullptr)
	{
		if (player->GetGameEnd())
		{
			player = nullptr;
			SetSceneFunc(SceneName::ResultScene);
		}
	}
	if (endSystem != nullptr)
	{
		if (endSystem->GetEndFlag())
		{
			endSystem = nullptr;
			SetSceneFunc(SceneName::ResultScene);
		}
	}
}

void PlaySceneObject::GameObjectInput(const InputState& _keyState)
{
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_F1))
	{
		if (pausingScreen == nullptr)
		{
			pausingScreen = new PauseScreen();
			pauzingEvent = PauzingEvent::PausingEvent;
		}
	}
}

void PlaySceneObject::PausingUpdateGameObject()
{
	if (pausingScreen != nullptr)
	{
		if (pausingScreen->GetEndPause())
		{
			pauzingEvent = PauzingEvent::NoneEvent;
			delete pausingScreen;
			pausingScreen = nullptr;
		}
	}

}
