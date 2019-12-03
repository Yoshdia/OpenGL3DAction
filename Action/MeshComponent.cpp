#include "MeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"

/**
@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
*/
MeshComponent::MeshComponent(GameObject* _owner, bool _skelton)
	:Component(_owner)
	, mMesh(nullptr)
	, mTextureIndex(0)
	, visible(true)
	,isSkelton(_skelton)
{
	RENDERER->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	RENDERER->RemoveMeshComponent(this);
}

/**
@brief�@�`�揈��
@param	�g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void MeshComponent::Draw(Shader* _shader)
{
	if (owner->GetState() != State::Dead)
	{
		if (mMesh)
		{
			// Set the world transform
			_shader->SetMatrixUniform("uWorldTransform",
				owner->GetWorldTransform());
			// Set specular power
			_shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
			// Set the active texture
			Texture* t = mMesh->GetTexture(mTextureIndex);
			if (t)
			{
				t->SetActive();
			}
			// Set the argMesh's vertex array as active
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();
			// Draw
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}
