#include "DownPlayerAnimationClip.h"
#include "Renderer.h"


DownPlayerAnimationClip::DownPlayerAnimationClip():
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/outi.png");
	animation[0].waitTimeForNextTexture = 110;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/down.png");
	animation[1].waitTimeForNextTexture = 15;
	loop = false;
}


DownPlayerAnimationClip::~DownPlayerAnimationClip()
{
}
