#pragma once
#include "Component.h"
#include "Math.h"
class ParticleComponent :
	public Component
{
public:
	typedef enum PARTICLE_BLEND_ENUM
	{
		PARTICLE_BLEND_ENUM_ALPHA,
		PARTICLE_BLEND_ENUM_ADD,
		PARTICLE_BLEND_ENUM_MULT
	}PARTICLE_ENUM;
	ParticleComponent(GameObject* _owner, int _updateOrder=100);
	ParticleComponent(GameObject* _owner, const Vector3& _pos, float _scale,int _updateOrder=100);
	~ParticleComponent();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void Update(float _deltaTime) override;

	void Draw(class Shader* shader);

		/**
	@brief　描画をするかどうかを設定
	@param	true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { visible = _visible; }

	/**
	@brief　描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない
	*/
	bool GetVisible() const { return visible; }

	void SetDrawOrder(int _drawOrder) { drawOrder = _drawOrder; }
	int GetDrawOrder() { return drawOrder; }
private:
	Vector3              position;
	Vector3              color; // 色
	float                scale;
	float                alpha; // α
	int                  textureID; // テクスチャID
	PARTICLE_ENUM        blendType; // ブレンドタイプ
	bool visible;

	// 共有スタティックメンバ
	static Matrix4       staticBillboardMat; // ビルボード行列
	static Vector3       staticCameraWorldPos; // カメラのワールド座標
	//描画順(数字が少ないものから描画される)
	int drawOrder;

public:
	int                  GetTextureID() { return textureID; }
	PARTICLE_ENUM        GetBlendType() { return blendType; }

	void                 SetColor(const Vector3& c) { color = c; }
	void                 SetTextureID(int texID) { textureID = texID; }
	void                 SetAlpha(float _alpha) { alpha = _alpha; }
	void				 SetScale(float _scale) { scale = _scale; }
	void                 SetBillboardMat(const Matrix4& mat)
	{
		staticBillboardMat = mat;
	}
	void                 SetBlendMode(PARTICLE_ENUM _blendType)
	{
		blendType = _blendType;
	}

	// カメラ距離でのソート用
	bool                 operator < (const ParticleComponent& rhs) const;
	bool                 operator > (const ParticleComponent& rhs) const;
};

Matrix4 GetBillboardMatrix();
