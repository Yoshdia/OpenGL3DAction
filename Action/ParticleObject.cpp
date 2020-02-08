#include "ParticleObject.h"
#include "ParticleComponent.h"
#include "Texture.h"
#include "Renderer.h"

/*
@param _pos 座標
@param _fileName 画像アドレス
@param _scale サイズ
@param drawOrder 描画順
*/
ParticleObject::ParticleObject(const Vector3& _pos, const std::string& _fileName, const float& _scale, const int& drawOrder):
	GameObject()
{
	SetPosition(_pos);
	particle = new ParticleComponent(this);
	particle->SetDrawOrder(drawOrder);
	particle->SetTextureID(RENDERER->GetTexture(_fileName)->GetTextureID());
	particle->SetScale(_scale);
}

ParticleObject::~ParticleObject()
{
}

