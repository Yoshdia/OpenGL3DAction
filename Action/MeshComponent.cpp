#include "MeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"

/*
@param _skelton �X�P���g���f�[�^��p���邩�B
@sa SkeletalMeshComponent.h
*/
MeshComponent::MeshComponent(GameObject* _owner, bool _skelton)
	:Component(_owner)
	, mesh(nullptr)
	, textureIndex(0)
	, visible(true)
	,isSkelton(_skelton)
{
	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveMeshComponent(this);
}

/*
@brief�@�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
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
