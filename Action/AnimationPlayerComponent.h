#pragma once
#include "Component.h"

/*
@enum PlayerAnimationState
@brief プレイヤーのアクション名
*/
enum PlayerAnimationState
{
	//待機
	Idle,
	//移動
	Move,
	//攻撃
	Attack,
	//攻撃ループ
	AttackRoop,
	//遠距離攻撃
	Range,
	//遠距離攻撃ループ
	RangeRoop,
	//ガード
	Guard,
	//ステップ
	Avoidance,
	//ダウン
	Down,
	//被弾
	Outi,
	//ジャンプ
	Jump,
	//落下
	Drop,
};

class AnimationSpriteClip;

/*
@file AnimationPlayerComponent.h
@brief プレイヤーのアニメーション
*/
class AnimationPlayerComponent :
	public Component
{
public:
	/*
	@fn アニメーションクラスの確保
	*/
	AnimationPlayerComponent(GameObject* _owner, int _updateOrder);
	/*
	@fn アニメーションクラスの解放
	*/
	~AnimationPlayerComponent();
	/*
	@fn nowAnimationを更新しながらnextAnimationを参照し変更を行う
	*/
	void Update(float _deltaTime)override;

private:
	//パーティクル
	class ParticleComponent* particleComponent;
	//現在再生中のアニメーション
	AnimationSpriteClip* nowAnimation;
	//待機
	AnimationSpriteClip* idle;
	//移動
	AnimationSpriteClip* move;
	//攻撃
	AnimationSpriteClip* attack;
	//攻撃ループ
	AnimationSpriteClip* attackRoop;
	//遠距離攻撃
	AnimationSpriteClip* rangeAttack;
	//遠距離攻撃ループ
	AnimationSpriteClip* rangeAttackRoop;
	//被弾
	AnimationSpriteClip* outi;
	//ガード
	AnimationSpriteClip* guard;
	//ダウン
	AnimationSpriteClip* down;
	//ジャンプ
	AnimationSpriteClip* jump;
	//落下
	AnimationSpriteClip* dropping;
	//回避
	AnimationSpriteClip* avoidancing;

	//現在再生中のアニメーション名
	PlayerAnimationState nextAnimation;
	//前Fまで再生中だったアニメーション名
	PlayerAnimationState beforeAnimation;
public: //ゲッターセッター
	/*
	@fn 次に再生するアニメーションを設定
	*/
	void SetAnimation(const PlayerAnimationState& _state);
	/*
	@fn パーティクルを反転するか
	*/
	void SetReverce(bool _flag);
};

