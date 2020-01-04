#include "DroppingDownPlayerAnimation.h"
#include "Renderer.h"


DroppingDownPlayerAnimation::DroppingDownPlayerAnimation()
{
	animation[0].sprite = RENDERER->GetTexture("Assets/Image/drop.png");
	animation[0].waitTimeForNextTexture = 1;
	loop = false;
}


DroppingDownPlayerAnimation::~DroppingDownPlayerAnimation()
{
}
