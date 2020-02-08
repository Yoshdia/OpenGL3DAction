#include "MeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"

/*
@param _skelton スケルトンデータを用いるか。
@sa SkeletalMeshComponent.h
*/
MeshComponent::MeshComponent(GameObject* _owner, bool _skelton)
	:Component(_owner)
	, mesh(nullptr)
	, textureIndex(0)
	, visible(true)
	,isSkelton(_skelton)
{
	//レンダラーにポインターを送る
	RENDERER->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveMeshComponent(this);
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void MeshComponent::Draw(Shader* _shader)
{
	if (owner->GetState() != State::Dead)
	{
		if (mesh)
		{
			// Set the world transform
			_shader->SetMatrixUniform("uWorldTransform",
				owner->GetWorldTransform());
			// Set specular power
			_shader->SetFloatUniform("uSpecPower", mesh->GetSpecPower());
			// Set the active texture
			Texture* t = mesh->GetTexture(textureIndex);
			if (t)
			{
				t->SetActive();
			}
			// Set the argMesh's vertex array as active
			VertexArray* va = mesh->GetVertexArray();
			va->SetActive();
			// Draw
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}
