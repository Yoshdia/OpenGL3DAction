#include "NockBackPlayerAnimationClip.h"
#include "Renderer.h"



NockBackPlayerAnimationClip::NockBackPlayerAnimationClip():
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/Outi.png");
	animation[0].waitTimeForNextTexture = 100;
	loop = false;
}


NockBackPlayerAnimationClip::~NockBackPlayerAnimationClip()
{
}
