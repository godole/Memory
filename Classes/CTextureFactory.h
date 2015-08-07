#pragma once
#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class CTextureFactory
{
public :
	static Texture2D* CreateTexture(string filename)
	{
		auto image = new CCImage;
		image->initWithImageFile(filename);

		auto texture = new CCTexture2D;
		texture->initWithImage(image);

		return texture;
	}
};