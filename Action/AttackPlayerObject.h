#pragma once
#include "GameObject.h"
#include "ComboItemObjectBase.h"

/*
@file AttackPlayerObject.h
@brief Playerに近接コンボ、遠距離攻撃を行わせるクラス
*/
class AttackPlayerObject :
	public GameObject
{
public:
	/*
	@param _owner 親オブジェクト
	*/
	AttackPlayerObject(GameObject* _owner);
	~AttackPlayerObject();
	void UpdateGameObject(float _deltaTime)override;
	void SetInput(const bool& _lInput, const bool& _rInput) { inputLeftChange = _lInput; inputRightChange =_rInput; }
	/*
	@fn 近距離攻撃
	@param _direction 攻撃時のプレイヤーの向き
	@param _slot 攻撃スロット
	@param _range このコンボが遠距離攻撃かどうか
	@return プレイヤーに付与する行動不可な時間
	*/
	float Attack(const float& _direction, const int& _slot, bool& _range);
private:
	/*
	@fn アイテムと衝突しているときに入力があったら攻撃スロットを変更し元のアイテムをその場に落下させる
	*/
	void OnTriggerStay(ColliderComponent* _colliderPair) ;
	/*
	@fn 現在所持している攻撃クラスを開放しその攻撃クラスのアイテムをその場に設置して引数の攻撃を取得する
	@param _name 取得したアイテム名
	@param _slot 変更を行う攻撃スロットナンバー
	*/
	ComboItemObjectBase* DropComboItem(const ComboItemName& _name,const int& slot);

	/*
	@fn　スロットを解放する
	@param _slot 解放したいスロットナンバー
	*/
	void DeleteSlot(const int& _slot);
	//スロット２のアイコン座標
	static const Vector3 RightIconPos;
	//ｽﾛｯﾄ１のアイコン座標
	static const Vector3 LeftIconPos;
	//アイコン座椅子
	static const float IconSize;
	//スロットアイコンにかぶせる操作ボタンのサイズ
	static const float BottonSize;
	//左スロットを変更するのに必要なボタン
	bool inputLeftChange;
	//右スロットを変更するのに必要なボタン
	bool inputRightChange;
	//親オブジェクト
	GameObject* owner;
	//つけ外しを行う攻撃スロット
	class ComboMeanPlayerBase* firstSlotAttack;
	//つけ外しを行う攻撃スロット
	class ComboMeanPlayerBase* secondSlotAttack;
	//近距離攻撃のコンボを次につなげる猶予時間。これが0になるとコンボ状態をリセットする
	float waitTimeForNextAttack;

	//攻撃の変更に用いる、アイテムの取得インターバルカウント
	int itemChangeWaitCount;
	//左スロットのアイコン
	class UserInterfaceBase* leftIcon;
	//右ｽﾛｯﾄのアイコン
	class UserInterfaceBase* rightIcon;
	//オブジェクト付近に表示するガイドボタン
	class UserInterfaceBase* lButtonGuide;
	//左スロットのアイテムを表示するアイコン
	class UserInterfaceBase* lButtonIcon;
	//オブジェクト付近に表示するガイドボタン
	class UserInterfaceBase* rButtonGuide;
	//右スロットのアイテムを表示するアイコン
	class UserInterfaceBase* rButtonIcon;
	//アイテムと衝突しているか。衝突しているときにGuideUIを表示させる
	bool itemCollided;
};

/*
☆攻撃クラスの追加手順
①矢や剣のような、各々の挙動のみを制御する武器クラス:GameObjectを作成
②武器クラスを受けとった座標、向きに発生させる攻撃クラス:AttackBaseを作成
③攻撃クラスをコンボごとに生成するコンボクラス:ComboMeanPlayerBaseを作成
~付け替えを行う場合~
④ComboItemObjectBase内の列挙型で宣言
⑤このクラスAttackPlayerObject内でその攻撃クラスを付け替えるため関数に文章を加える
*/
