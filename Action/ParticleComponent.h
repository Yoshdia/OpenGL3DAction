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
	ParticleComponent(GameObject* _owner);
	ParticleComponent(GameObject* _owner, const Vector3& _pos, float _scale);
	~ParticleComponent();

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Update(float _deltaTime) override;

	void Draw(class Shader* shader);// �̂��̎��Ƃ� virtual��

private:
	Vector3              position;
	Vector3              color; // �F
	float                scale;
	float                alpha; // ��
	int                  textureID; // �e�N�X�`��ID
	PARTICLE_ENUM        blendType; // �u�����h�^�C�v

	// ���L�X�^�e�B�b�N�����o
	static Matrix4       staticBillboardMat; // �r���{�[�h�s��
	static Vector3       staticCameraWorldPos; // �J�����̃��[���h���W

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

	// �J���������ł̃\�[�g�p
	bool                 operator < (const ParticleComponent& rhs) const;
	bool                 operator > (const ParticleComponent& rhs) const;
};

Matrix4 GetBillboardMatrix();
