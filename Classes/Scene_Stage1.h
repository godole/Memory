#pragma once
#include "PlayLayerMainLogic.h"
#include "cocos2d.h"
#include <vector>
#include <string>

class CWindBox;

class Scene_Stage1 :
	public PlayLayerMainLogic
{
public :
	// implement the "static create()" method manually
	CREATE_FUNC(Scene_Stage1);

public :
	virtual void BackgroundInit();
	virtual void ObjectInit();
	virtual void BackgroundUpdate();
	virtual void ObjectUpdate();

public:
	Scene_Stage1();
	~Scene_Stage1();

private :
	void MakeTreeEffect(string texturename, CCPoint a_vPos);

	std::vector<std::shared_ptr<CWindBox>> m_arrWindBox;

	int m_nCloudCount;
	float m_fCloudSpeed;
};

