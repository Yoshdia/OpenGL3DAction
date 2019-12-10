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
	new MeleeEnemy(Vector3(400,80,0));

	//new MeleeEnemy(Vector3(0,-125,0));
	//new MeleeEnemy(Vector3(-200,50,0));

	new DebugBox(Vector3(-100, -200, 0));
	new DebugBox(Vector3(-100, -100, 0));

	new DebugBox(Vector3(-300, 0, 0));
	new DebugBox(Vector3(-200, 0, 0));
	new DebugBox(Vector3(-100, 0, 0));

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

	new DebugBox(Vector3(700, 200, 0));
	new DebugBox(Vector3(800, 200, 0));
	new DebugBox(Vector3(900, 200, 0));
	new DebugBox(Vector3(1000, 200, 0));
	new DebugBox(Vector3(1100, 200, 0));

	new DebugBox(Vector3(1100, 100, 0));
	new DebugBox(Vector3(1100, 0, 0));
	new DebugBox(Vector3(1200, 0, 0));
	new DebugBox(Vector3(1300, 0, 0));
	new DebugBox(Vector3(1400, 0, 0));
	new DebugBox(Vector3(1500, 0, 0));
	new DebugBox(Vector3(1600, 0, 0));
	new DebugBox(Vector3(1700, 0, 0));
	new DebugBox(Vector3(1800, 0, 0));
	new DebugBox(Vector3(1900, 0, 0));
	new DebugBox(Vector3(2000, 0, 0));

	new DebugBox(Vector3(-200, 100, 0), Tag::EnemyWeaponTag);

}


PlayScene::~PlayScene()
{
}

SceneBase* PlayScene::Update()
{
	return this;
}
