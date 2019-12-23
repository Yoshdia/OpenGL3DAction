#include "MovePlayerAnimationClip.h"
#include "Renderer.h"

MovePlayerAnimationClip::MovePlayerAnimationClip() :
	AnimationSpriteClip()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/move1.png");
	animation[0].waitTimeForNextTexture = 100;
	animation[1].sprite = RENDERER->GetTexture("Assets/Image/move1.png");
	animation[1].waitTimeForNextTexture = 100;

	loop = true;
}

MovePlayerAnimationClip::~MovePlayerAnimationClip()
{
}
