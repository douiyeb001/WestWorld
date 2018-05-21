#include "Sprite.h"

Sprite::Sprite(IVideoDriver * driver)
{
	this->driver = driver;
	position = vector2d<s32>(0, 0);
	scale = vector2d<f32>(1.0f, 1.0f);
	rotation = 0;
}

//most of this functions code was found on the forum,
//I just fixed and added some things.

void Sprite::draw()
{
	if (texture != NULL)
	{
		visible_area = rect<s32>(1, 1, texture->getSize().Width, texture->getSize().Height);
		center = vector2d<s32>(position.X, position.Y);
		SMaterial material;

		matrix4 oldProjMat = driver->getTransform(ETS_PROJECTION);
		driver->setTransform(ETS_PROJECTION, matrix4());

		matrix4 oldViewMat = driver->getTransform(ETS_VIEW);
		driver->setTransform(ETS_VIEW, matrix4());

		vector2df corner[4];

		corner[0] = vector2df((f32)position.X - (visible_area.getWidth() * scale.X) / 2, (f32)position.Y - (visible_area.getHeight() * scale.Y) / 2);
		corner[1] = vector2df((f32)position.X + (visible_area.getWidth() * scale.X) / 2, (f32)position.Y - (visible_area.getHeight() * scale.Y) / 2);
		corner[2] = vector2df((f32)position.X - (visible_area.getWidth() * scale.X) / 2, (f32)position.Y + (visible_area.getHeight() * scale.Y) / 2);
		corner[3] = vector2df((f32)position.X + (visible_area.getWidth() * scale.X) / 2, (f32)position.Y + (visible_area.getHeight() * scale.Y) / 2);

		if (rotation != 0.0f)
			for (int x = 0; x < 4; x++)
				corner[x].rotateBy((f32)rotation, vector2df((f32)center.X, (f32)center.Y));

		vector2df uvCorner[4];
		uvCorner[0] = vector2df((f32)visible_area.UpperLeftCorner.X, (f32)visible_area.UpperLeftCorner.Y);
		uvCorner[1] = vector2df((f32)visible_area.LowerRightCorner.X, (f32)visible_area.UpperLeftCorner.Y);
		uvCorner[2] = vector2df((f32)visible_area.UpperLeftCorner.X, (f32)visible_area.LowerRightCorner.Y);
		uvCorner[3] = vector2df((f32)visible_area.LowerRightCorner.X, (f32)visible_area.LowerRightCorner.Y);

		for (int x = 0; x < 4; x++)
		{
			float uvX = uvCorner[x].X / (float)texture->getSize().Width;
			float uvY = uvCorner[x].Y / (float)texture->getSize().Height;
			uvCorner[x] = vector2df(uvX, uvY);
		}

		S3DVertex vertices[4];
		u16 indices[6] = { 0, 1, 2, 3 ,2 ,1 };

		float screenWidth = (float)driver->getScreenSize().Width;
		float screenHeight = (float)driver->getScreenSize().Height;

		for (int x = 0; x < 4; x++)
		{
			float screenPosX = ((corner[x].X / screenWidth) - 0.5f) * 2.0f;
			float screenPosY = ((corner[x].Y / screenHeight) - 0.5f) * -2.0f;
			vertices[x].Pos = vector3df(screenPosX, screenPosY, 1);
			vertices[x].TCoords = uvCorner[x];
			vertices[x].Color = SColor(255, 255, 255, 255);
		}

		material.Lighting = false;
		material.ZWriteEnable = false;
		material.TextureLayer[0].Texture = texture;
		material.ZBuffer = 0;
		//material.TextureLayer[0].TrilinearFilter = true;

		material.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;

		driver->setMaterial(material);
		driver->drawIndexedTriangleList(&vertices[0], 4, &indices[0], 2);

		driver->setTransform(ETS_PROJECTION, oldProjMat);
		driver->setTransform(ETS_VIEW, oldViewMat);
	}
}

void Sprite::scaleToDimensions(dimension2d<u32> size)
{
	dimension2d<u32> original = this->texture->getOriginalSize();
	this->scale.X = (float)(size.Width / (float)original.Width);
	this->scale.Y = (float)(size.Height / (float)original.Height);
}