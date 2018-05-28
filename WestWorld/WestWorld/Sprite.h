#include <irrlicht.h>
#ifndef sprite_h
#define sprite_h

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;


class Sprite
{
public:
	ITexture * texture;
	rect<s32> visible_area;
	vector2d<s32> position;
	vector2d<s32> center;
	vector2d<f32> scale;
	f32 rotation;

	Sprite(IVideoDriver *driver);
	~Sprite();
	void draw();
	void scaleToDimensions(dimension2d<u32> size);

	IVideoDriver * driver;
};
#endif
