#include "MovePlayerAnimationClip.h"
#include "Renderer.h"

MovePlayerAnimationClip::MovePlayerAnimationClip() :
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/once.png");
	animation[0].waitTimeForNextTexture = 20;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/twice.png");
	animation[1].waitTimeForNextTexture = 20;
	animation[2].sprite = RENDERER->GetTexture("Assets/Image/third.png");
	animation[2].waitTimeForNextTexture = 20;
	animation[3].sprite = RENDERER->GetTexture("Assets/Image/fourth.png");
	animation[3].waitTimeForNextTexture = 20;
	
	animation[4].sprite = nullptr;
	animation[4].waitTimeForNextTexture = 0;
}

MovePlayerAnimationClip::~MovePlayerAnimationClip()
{
}
