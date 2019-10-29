#include "PlayScene.h"
#include "Game.h"
#include "Renderer.h"
#include "Math.h"
#include "Ship.h"
#include "PlayerCharacter.h"
#include "DebugBox.h"

PlayScene::PlayScene()
    :SceneBase()
{
    // Setup lights
    RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
    DirectionalLight& dir = RENDERER->GetDirectionalLight();
    dir.direction = Vector3(1.0f, 0.7f, -0.7f);
    dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);   
    dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	new PlayerCharacter;
	new DebugBox;
}


PlayScene::~PlayScene()
{
}

SceneBase * PlayScene::Update()
{
	return this;
}
