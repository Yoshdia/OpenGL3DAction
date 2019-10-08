#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

#define RENDERER Renderer::GetInstance()

//���s�����p�̍\����
struct DirectionalLight
{
    // ���̕���
    Vector3 direction;
    // �g�U���ːF
    Vector3 diffuseColor;
    // ���ʔ��ːF
    Vector3 specColor;
};

class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class Shader;
class VertexArray;

class Renderer
{
public:
	/**
	@brief  �C���X�^���X���擾����
	@return Renderer�N���X�̃C���X�^���X
	*/
	static Renderer* GetInstance() { return renderer; }

	/**
	@brief  �C���X�^���X���쐬����
	*/
	static void CreateInstance();

	/**
	@brief  �C���X�^���X���폜����
	*/
	static void DeleteInstance();

	/**
	@brief  ����������
	@return true : ���� , false : ���s
	*/
    bool Initialize(float _screenWidth, float _screenHeight);
	/**
	@brief  �I������
	*/
    void Shutdown();

	/**
	@brief  ���[�h�����f�[�^�̉��
	*/
    void UnloadData();

	/**
	@brief  �`�揈��
	*/
    void Draw();

	/**
	@brief  �X�v���C�g�̒ǉ�
	@param	�ǉ�����SpriteComponent�N���X�̃|�C���^
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/**
	@brief  �X�v���C�g�̍폜
	@param	�폜����SpriteComponent�N���X�̃|�C���^
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/**
	@brief  �e�N�X�`���̎擾
	@param	�擾�������e�N�X�`���̃t�@�C����
	@return Texture�N���X�̃|�C���^
	*/
	Texture* GetTexture(const std::string& _fileName);

	/**
	@brief  ���b�V���R���|�[�l���g�̒ǉ�
	@param	�ǉ�����MeshComponent�N���X�̃|�C���^
	*/
    void AddMeshComponent(MeshComponent* _meshComponent);

	/**
	@brief  ���b�V���R���|�[�l���g�̍폜
	@param	�폜����MeshComponent�N���X�̃|�C���^
	*/
    void RemoveMeshComponent(MeshComponent* _meshComponent);

	/**
	@brief  ���b�V���̎擾
	@param	�擾���������b�V���̃t�@�C����
	@return Mesh�N���X�̃|�C���^
	*/
    Mesh* GetMesh(const std::string& _fileName);

	/**
	@brief	�r���[�s���ݒ肷��
	@param	�r���[�s��
	*/
    void SetViewMatrix(const Matrix4& _view) { view = _view; }

	/**
	@brief	������ݒ肷��
	@param	Vector3�i������\���j
	*/
    void SetAmbientLight(const Vector3& _ambient) { ambientLight = _ambient; }

	/**
	@brief	���s�����̍\���̂��擾����
	@return	DirectionalLight�i���s�����̍\���́j
	*/
    DirectionalLight& GetDirectionalLight() { return dirLight; }

	/**
	@brief	�X�N���[���̉������擾����
	@return	�X�N���[���̉���
	*/
    float GetScreenWidth() const { return screenWidth; }
	
	/**
	@brief	�X�N���[���̏c�����擾����
	@return	�X�N���[���̏c��
	*/
	float GetScreenHeight() const { return screenHeight; }

private:
	//�R���X�g���N�^�A�f�X�g���N�^�̉B��
	Renderer();
	~Renderer();

	//�����̃C���X�^���X
	static Renderer* renderer;

	/**
	@brief  �V�F�[�_�[�̓ǂݍ���
	@return true : ���� , false : ���s
	*/
    bool LoadShaders();
	/**
	@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
    void CreateSpriteVerts();

	/**
	@brief  ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
	@param  �Z�b�g����Shader�N���X�̃|�C���^
	*/
    void SetLightUniforms(Shader* _shader);

    /**
    @brief  ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
    @param  �Z�b�g����Shader�N���X�̃|�C���^
    */
    void SetWallLightUniforms(Shader* _shader);

    void SetWallDirLight();

    //�t�@�C�����Ń��b�V�����擾���邽�߂̉ϒ��R���e�i
    std::unordered_map<std::string, Mesh*> meshes;
    //���b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
    std::vector<MeshComponent*> meshComponents;
	//�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> sprites;
	//�t�@�C�����Ńe�N�X�`�����擾���邽�߂̉ϒ��R���e�i
	std::unordered_map<std::string, Texture*>textures;

    std::vector<MeshComponent*> wallMeshComponents;

	//�N���X�̃|�C���^

    Shader* spriteShader;
    VertexArray* spriteVerts;
    Shader* meshShader;
    Shader* wallShader;

    //�r���[�s��
    Matrix4 view;
	//�ˉe�s��
    Matrix4 projection;
    //�X�N���[���̉���
    float screenWidth;
	//�X�N���[���̏c��
    float screenHeight;
    //����
    Vector3 ambientLight;
	//���s����
    DirectionalLight dirLight;
    DirectionalLight wallDirLight;
    //�E�B���h�E
    SDL_Window* window;
    //�R���e�L�X�g
    SDL_GLContext context;
};