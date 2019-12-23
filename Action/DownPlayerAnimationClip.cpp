#include "DownPlayerAnimationClip.h"
#include "Renderer.h"


DownPlayerAnimationClip::DownPlayerAnimationClip():
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/down.png");
	animation[0].waitTimeForNextTexture = 100;
	loop = false;
}


DownPlayerAnimationClip::~DownPlayerAnimationClip()
{
}
