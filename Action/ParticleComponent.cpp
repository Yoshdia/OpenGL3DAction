#include "ParticleComponent.h"
#include "Shader.h"
#include "Renderer.h"
#include "GameObject.h"

Matrix4 ParticleComponent::staticBillboardMat;
Vector3 ParticleComponent::staticCameraWorldPos;

ParticleComponent::ParticleComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner,_updateOrder)
	, position(Vector3(0, 0, 0))
	, scale(1)
	, alpha(1.0f)
	, visible(true)
	, drawOrder(_updateOrder)
	,color(Vector3(1,1,1))
{
	RENDERER->AddParticle(this);
}

ParticleComponent::ParticleComponent(GameObject* _owner, const Vector3& _pos, float _scale, int _updateOrder)
	: Component(_owner, _updateOrder)
	, position(_pos)
	, scale(_scale)
	, alpha(1)
	, blendType(PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA)
	, visible(true)
	, drawOrder(_updateOrder)
	, color(Vector3(1, 1, 1))

{
	RENDERER->AddParticle(this);
}

ParticleComponent::~ParticleComponent()
{
	RENDERER->RemoveParticle(this);
}

void ParticleComponent::Update(float _deltaTime)
{
}

void ParticleComponent::Draw(Shader* shader)
{
	if (owner->GetState() == State::Dead)
	{
		return;
	}
	Matrix4 mat, matScale;
	matScale = Matrix4::CreateScale(scale * owner->GetScale());
	//if (isFollowing)
	//{
	mat = Matrix4::CreateTranslation(position + owner->GetPosition());
	//}
	//else
	//{
		//mat = Matrix4::CreateTranslation(position);
	//}

	shader->SetMatrixUniform("uWorldTransform", matScale * staticBillboardMat * mat);
	shader->SetFloatUniform("uAlpha", alpha);
	shader->SetVectorUniform("uColor", color);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

bool ParticleComponent::operator<(const ParticleComponent& rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - position).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.position).LengthSq();
	return lenThis < lenRhs;
}

bool ParticleComponent::operator>(const ParticleComponent& rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - position).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.position).LengthSq();
	return lenThis > lenRhs;
}


Matrix4 GetBillboardMatrix()
{
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[1][1] *= -1;
	ret.mat[2][2] *= -1;

	return Matrix4(ret);
}
