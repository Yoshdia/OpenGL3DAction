#include "MovePlayerAnimationClip.h"
#include "Renderer.h"

MovePlayerAnimationClip::MovePlayerAnimationClip() :
	AnimationSpriteClip()
{
	fileNameone = "Assets/Image/once.png";
	RENDERER->GetTexture(fileNameone);
	fileNametwo = "Assets/Image/twice.png";
	RENDERER->GetTexture(fileNametwo);

	nowSprite= RENDERER->GetTexture(fileNameone);
}

MovePlayerAnimationClip::~MovePlayerAnimationClip()
{
}

const Texture * MovePlayerAnimationClip::ChangeNextTexture(int & spriteCountMax)
{

	nowSpriteCount++;
	return nowSprite;
}
