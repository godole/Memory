#include "Box2dSprite.h"
#include "json\document.h"

using namespace rapidjson;


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

void CBox2dSprite::Init(CCSprite* a_Sprite, string jsonData, b2World* a_World, b2BodyType type)
{
	m_pSprite = a_Sprite;

	m_b2Structure.bodyDef.userData = a_Sprite;
	m_b2Structure.bodyDef.type = type;
	m_b2Structure.body = a_World->CreateBody(&m_b2Structure.bodyDef);

	b2PolygonShape shape;

	string fString = jsonData;
	string szData;
	FileUtils* Utils = FileUtils::sharedFileUtils();

	ssize_t fileSize;
	char* stream = (char*)Utils->getFileData(jsonData, "r", &fileSize);
	szData = string(stream);

	string data = string((const char*)stream, fileSize);
	CC_SAFE_DELETE_ARRAY(stream);

	Document doc;
	if (doc.Parse<0>(data.c_str()).HasParseError())
		CCLOG(doc.GetParseError());

	int verticesCount = 0;
	
	auto& rigidBody = doc["rigidBodies"][(SizeType)0];

	CCLOG("%s", rigidBody["name"].GetString());

	CCLOG("%s", rigidBody["shapes"][(SizeType)0]["type"].GetString());

	auto& vertices = rigidBody["shapes"][(SizeType)0]["vertices"];
	verticesCount = vertices.Size();
	b2Vec2* bodyVertices = new b2Vec2[verticesCount];

	if (vertices.IsArray())
	{
		for (SizeType i = 0; i < vertices.Size(); i++)
		{
			float x = vertices[i]["x"].GetDouble();
			float y = vertices[i]["y"].GetDouble();
			CCLOG("%f", x);
			CCLOG("%f", y);
			bodyVertices[i] = b2Vec2(x, y);
		}
	}

	shape.Set(bodyVertices, verticesCount);
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