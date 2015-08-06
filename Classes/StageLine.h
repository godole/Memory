#pragma once
#include "cocos2d.h"
#include "Update.h"

USING_NS_CC;

enum class BoxDirection;
enum class LineDirection;
class CLine;

class CStageLine : public IUpdate
{
public:
	CStageLine();
	~CStageLine();

public:
	void setCursor(Point a_pPoint) { m_pCursorPos = a_pPoint; }

	// IUpdate
	virtual void Update() override;

	void StageInit(BoxDirection a_eBoxDirection,
		Layer * a_pParentLayer,int a_nStagenum, Vec2 a_pPosition);
	
private:
	std::vector<CLine*> m_vLines;
	Sprite *		  m_pStage[10];
	CLine *			  m_pLine;
	Layer *			  m_pParentLayer;
	Vec2			  m_Position;
	Point			  m_pCursorPos;
	BoxDirection	  m_eBoxDirection;

	int				  m_nStagenum;
	int				  m_nStageCount;
	int				  m_nLineStart;
	bool			  m_isComplete;

private:
	// 스테이지의 각 이미지 로드
	void SetStage();
	// 스테이지를 표시함
	void StageCheck();
	void CreateLine(LineDirection, Vec2, int);

private:
	void RightBoxStageCreator();
	void LeftBoxStageCreator();
	void DownBoxStageCreator();
};