#include "Box2dSprite.h"


CBox2dSprite::CBox2dSprite()
{
}


CBox2dSprite::~CBox2dSprite()
{
}

void CBox2dSprite::Init(CCSprite* a_Sprite, b2World* a_World, b2BodyType type, CCPoint a_vAnchor)
{
	m_pSprite = a_Sprite;

	m_b2Structure.bodyDef.userData = a_Sprite;
	m_b2Structure.bodyDef.type = type;
	m_b2Structure.body = a_World->CreateBody(&m_b2Structure.bodyDef);
	b2PolygonShape shape;
	float centerX = (0.5f - a_vAnchor.x) * a_Sprite->getContentSize().width / PTM_RATIO;
	float centerY = (0.5f - a_vAnchor.y) * a_Sprite->getContentSize().height / PTM_RATIO;
	shape.SetAsBox((a_Sprite->getContentSize().width / 2) / PTM_RATIO, (a_Sprite->getContentSize().height / 2) / PTM_RATIO,
	{ centerX, centerY }, 0);
	m_b2Structure.fixture = m_b2Structure.body->CreateFixture(&shape, 0.0);

	m_fWidth = a_Sprite->getContentSize().width;
	m_fHeight = a_Sprite->getContentSize().height;

	m_vAnchorPoint = a_vAnchor;
}

void CBox2dSprite::Init(CCSprite* a_Sprite, b2World* a_World, b2BodyType type, float width, float height, CCPoint a_vAnchor)
{
	m_pSprite = a_Sprite;

	m_fWidth = width;
	m_fHeight = height;

	m_vAnchorPoint = a_vAnchor;

	m_b2Structure.bodyDef.userData = a_Sprite;
	m_b2Structure.bodyDef.type = type;
	m_b2Structure.body = a_World->CreateBody(&m_b2Structure.bodyDef);
	b2PolygonShape shape;
	float centerX = (0.5f - a_vAnchor.x) * width / PTM_RATIO;
	float centerY = (0.5f - a_vAnchor.y) * height / PTM_RATIO;
	shape.SetAsBox(width / 2 / PTM_RATIO, (height / 2) / PTM_RATIO,
	{ centerX, centerY }, 0);
	m_b2Structure.fixture = m_b2Structure.body->CreateFixture(&shape, 0.0);
}

void CBox2dSprite::setPositionTo(CCPoint a_vPos)
{
	m_b2Structure.body->SetTransform(ChangeVecTob2Vec2(a_vPos), 0);
}

void CBox2dSprite::setPositionBy(CCPoint a_vPos)
{
	m_b2Structure.body->SetTransform(ChangeVecTob2Vec2(a_vPos) + m_b2Structure.body->GetTransform().p, 0);
}

CCRect CBox2dSprite::getBoundingBox()
{
	CCRect r;
	r.setRect(m_pSprite->getPositionX() - (1.0 - m_vAnchorPoint.x) * m_fWidth, m_pSprite->getPositionY() - (1.0 - m_vAnchorPoint.y) * m_fHeight, m_fWidth, m_fHeight);
	return r;
}