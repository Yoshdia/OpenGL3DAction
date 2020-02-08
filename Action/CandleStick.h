#pragma once
#include "GameObject.h"

/*
@file CandleStick.h
@bief プレイヤーが一度衝突すると火が灯り、範囲内のプレイヤーを回復するオブジェクト
*/
class CandleStick :
	public GameObject
{
public:
	/*
	@param _pos 座標
	*/
	CandleStick(Vector3 _pos=Vector3(0,0,0));
	~CandleStick();
	/*
	@fn 一定間隔ごとに炎のCandleFireObjectクラスを生成する
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	/*
	@fn プレイヤーと衝突したらフラグをp建てる
	*/
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	//衝突判定を行うクラス
	class ColliderComponent* collider;
	//蝋の画像クラス
	class ParticleComponent* stickParticle;
	//灯が灯った後の明かりの画像クラス
	class ParticleComponent* lightParticle;
	//火がともったか
	bool ignition;
	//炎を生成する間隔
	int ignitionCount;
};

