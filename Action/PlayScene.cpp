#include "PlayScene.h"
#include "Game.h"
#include "Renderer.h"
#include "Math.h"
#include "Ship.h"
#include "PlayerCharacter.h"
#include "DebugBox.h"
#include "MeleeEnemy.h"

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
	new MeleeEnemy(Vector3(300,50,0));
	new MeleeEnemy(Vector3(0,50,0));
	new MeleeEnemy(Vector3(-200,50,0));
	

	new DebugBox(Vector3(-200, 0, 0));
	new DebugBox(Vector3(-300, 0, 0));

	new DebugBox(Vector3(-100, -200, 0));
	new DebugBox(Vector3(-100, -100, 0));
	new DebugBox(Vector3(-100, 0, 0));

	new DebugBox(Vector3(-100, -200, 0));

	new DebugBox(Vector3(0, -200, 0));
	new DebugBox(Vector3(100, -200, 0));
	new DebugBox(Vector3(200, -200, 0));
	new DebugBox(Vector3(300, -200, 0));
	new DebugBox(Vector3(300, -100, 0));
	new DebugBox(Vector3(300, 0, 0));

	new DebugBox(Vector3(400, 0, 0));
	new DebugBox(Vector3(500, 0, 0));
	new DebugBox(Vector3(600, 0, 0));

	new DebugBox(Vector3(600, 100, 0));
	new DebugBox(Vector3(600, 200, 0));

}


PlayScene::~PlayScene()
{
}

SceneBase* PlayScene::Update()
{
	return this;
}
