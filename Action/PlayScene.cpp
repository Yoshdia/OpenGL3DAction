#include "PlayScene.h"
#include "Game.h"
#include "Renderer.h"
#include "Math.h"
#include "Ship.h"
#include "PlayerCharacter.h"
#include "DebugBox.h"
#include "MeleeEnemy.h"
#include "CandleStick.h"
#include "RangeEnemy.h"
#include "TankEnemy.h"
#include "MageEnemy.h"
#include "SpawnEventSystem.h"

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
	//new MeleeEnemy(Vector3(400,80,0));
	//new TankEnemy(Vector3(400, 80, 0));
	//new MageEnemy(Vector3(500, 80, 0));
	new SpawnEventSystem(Vector3(500, 80, 0), Vector3(0, -100, 0));

	//.         .
	//.         .
	//.         .
	//.         .
	//._       _.
	//.         .
	//...........
	new DebugBox(Vector3(0, 400, 0));
	new DebugBox(Vector3(0, 300, 0));
	new DebugBox(Vector3(0, 200, 0));
	new DebugBox(Vector3(0, 100, 0));
	new DebugBox(Vector3(100, 100, 0), Vector3(50, 5, 50),Tag::ThinGroundFloor);
	new DebugBox(Vector3(0, 0, 0));
	new DebugBox(Vector3(-200, -200, 0));
	new DebugBox(Vector3(-100, -200, 0));


	new DebugBox(Vector3(00, -200, 0));
	new DebugBox(Vector3(100, -200, 0));
	new DebugBox(Vector3(200, -200, 0));
	new DebugBox(Vector3(300, -200, 0));
	new DebugBox(Vector3(400, -200, 0));
	new DebugBox(Vector3(500, -200, 0));
	new DebugBox(Vector3(600, -200, 0));
	new DebugBox(Vector3(700, -200, 0));
	new DebugBox(Vector3(800, -200, 0));
	new DebugBox(Vector3(900, -200, 0));

	new DebugBox(Vector3(900, -100, 0));
	new DebugBox(Vector3(900, 0, 0));
	new DebugBox(Vector3(900, 100, 0));
	new DebugBox(Vector3(800, 100, 0), Vector3(50, 5, 50), Tag::ThinGroundFloor);
	new DebugBox(Vector3(900, 200, 0));
	new DebugBox(Vector3(900, 300, 0));
	new DebugBox(Vector3(900, 400, 0));

	new DebugBox(Vector3(-100, 0, 0));
	new DebugBox(Vector3(-200, 0, 0));
	new DebugBox(Vector3(-300, -200, 0));
	new DebugBox(Vector3(-400, -200, 0));
	new DebugBox(Vector3(-500, -200, 0));
	new DebugBox(Vector3(-600, -200, 0));
	new DebugBox(Vector3(-700, -200, 0));

	//        .....
	//        .   .
	//..._  ...   ........
	//  .   .
	//  .....
	//new CandleStick(Vector3(400, 80, 0));
	//
	/*new DebugBox(Vector3(-100, -200, 0));
	new DebugBox(Vector3(-100, -100, 0));
	
	new DebugBox(Vector3(0, 45, 0),Vector3(50,5,50),Tag::ThinGroundFloor);
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
	new DebugBox(Vector3(2000, 0, 0));*/
}


PlayScene::~PlayScene()
{
}

SceneBase* PlayScene::Update()
{
	return this;
}
