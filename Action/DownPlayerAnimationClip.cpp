#include "DownPlayerAnimationClip.h"
#include "Renderer.h"


DownPlayerAnimationClip::DownPlayerAnimationClip():
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/outi.png");
	animation[0].waitTimeForNextTexture = 15;
	loop = false;
}


DownPlayerAnimationClip::~DownPlayerAnimationClip()
{
}
