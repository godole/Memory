#pragma once
#include "cocos2d.h"
#include <string>

class ShaderNode : public cocos2d::Node
{
public:
	static ShaderNode* shaderNodeWithVertex(const std::string &vert, const std::string &frag);

	virtual void update(float dt);
	virtual void setPosition(const cocos2d::Vec2 &newPosition);
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

protected:
	ShaderNode();
	~ShaderNode();

	bool initWithVertex(const std::string &vert, const std::string &frag);
	void loadShaderVertex(const std::string &vert, const std::string &frag);

	void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);

	cocos2d::Vec2 _center;
	cocos2d::Vec2 _resolution;
	float      _time;
	std::string _vertFileName;
	std::string _fragFileName;
	cocos2d::CustomCommand _customCommand;
};