#include "StageLine.h"
#include "EBoxDirection.h"
#include "ELineDirection.h"
#include "ConstantValue.h"
#include "Line.h"
#include "DataManager.h"

CStageLine::CStageLine()
{
	m_nLineStart = 0;
	m_nStageCount = 0;
	m_isComplete = false;
}


CStageLine::~CStageLine()
{
}

void CStageLine::SetStage()
{
	for (int i = 0; i < STAGENUM; i++)
	{
		//m_pStage[i]->setOpacity(0);
		//m_pStage[i]->setScale(0.0);
		m_pStage[i]->setVisible(false);
	}

	m_pStage[0]->setTexture("number/number_1.png");
	m_pStage[1]->setTexture("number/number_2.png");
	m_pStage[2]->setTexture("number/number_3.png");
	m_pStage[3]->setTexture("number/number_4.png");
	m_pStage[4]->setTexture("number/number_5.png");
	m_pStage[5]->setTexture("number/number_6.png");
	m_pStage[6]->setTexture("number/number_7.png");
	m_pStage[7]->setTexture("number/number_8.png");
	m_pStage[8]->setTexture("number/number_9.png");
	m_pStage[9]->setTexture("number/number_10.png");
}

void CStageLine::Update()
{
	if (m_isComplete)
		return;

	StageCheck();

	if (!m_vLines[m_nLineStart]->getCompleteVisible())
	{
		m_vLines[m_nLineStart]->ShowLine();
	}
	else
	{
		if (m_nLineStart < m_vLines.size() - 1)
		{	
			m_nLineStart++;
			m_vLines[m_nLineStart]->setWork(true);
		}
		else
		{
			m_nLineStart++;
			m_isComplete = true;
			StageCheck();
		}
	}
}

void CStageLine::StageInit
	(BoxDirection a_eBoxDirection, Layer * a_pParentLayer,
	int a_nStageNum, Vec2 a_Position)
{
	m_eBoxDirection		= a_eBoxDirection;
	m_nStagenum			= a_nStageNum;
	m_pParentLayer		= a_pParentLayer;
	m_Position			= a_Position;

	for (int i = 0; i < STAGENUM; i++)
	{
		m_pStage[i] = Sprite::create();
		a_pParentLayer->addChild(m_pStage[i],2);
	}
	
	SetStage();

	switch (a_eBoxDirection)
	{
	case BoxDirection::Left:
		LeftBoxStageCreator();
		break;

	case BoxDirection::Down:
		DownBoxStageCreator();
		break;

	case BoxDirection::Right:
		RightBoxStageCreator();
		break;
	default:
		break;
	}

	m_vLines[0]->setWork(true);
}

void CStageLine::CreateLine
	(LineDirection a_eLineDirection,Vec2 a_Position, int a_Linesize)
{
	auto temp = new CLine;
	temp->LineInit(m_pParentLayer, a_eLineDirection, a_Position, a_Linesize);
	m_vLines.push_back(temp);
}

void CStageLine::StageCheck()
{
	auto a = ScaleTo::create(0.2, 1.0);
	auto _pFade = FadeIn::create(0.2);
	auto _pScale = Spawn::create(a, _pFade,NULL);

	switch (m_eBoxDirection)
	{
	case BoxDirection::Left:
		switch (m_nLineStart)
		{
		case 2:
			m_pStage[0]->setVisible(true);
			m_pStage[0]->runAction(_pScale);
			break;
		case 3:
			m_pStage[1]->setVisible(true);
			m_pStage[1]->runAction(_pScale);
			break;
		default:
			break;
		}
		break;
	case BoxDirection::Down:

		switch (m_nLineStart)
		{
		case 1:
			m_pStage[0]->setVisible(true);
		//	m_pStage[0]->runAction(_pScale);
			break;
		case 2:
			m_pStage[1]->setVisible(true);
		//	m_pStage[1]->runAction(_pScale);
			break;
		case 3:
			m_pStage[2]->setVisible(true);
		//	m_pStage[2]->runAction(_pScale);
			break;
		case 4:
			m_pStage[3]->setVisible(true);
		//	m_pStage[3]->runAction(_pScale);
			break;
		case 5:
			m_pStage[4]->setVisible(true);
		//	m_pStage[4]->runAction(_pScale);
			break;
		case 6:
			m_pStage[5]->setVisible(true);
		//	m_pStage[5]->runAction(_pScale);
			break;
		case 7:
			m_pStage[6]->setVisible(true);
		//	m_pStage[6]->runAction(_pScale);
			break;
		case 8:
			m_pStage[7]->setVisible(true);
		//	m_pStage[7]->runAction(_pScale);
			break;
		case 9:
			m_pStage[8]->setVisible(true);
			//m_pStage[8]->runAction(_pScale);
			break;
		case 10:
			m_pStage[9]->setVisible(true);
		//	m_pStage[9]->runAction(_pScale);
			break;
			
		}

		break;

	case BoxDirection::Right:
		switch (m_nLineStart)
		{
		case 1:
			m_pStage[0]->setVisible(true);
			m_pStage[0]->runAction(_pScale);
			break;
		case 2:
			m_pStage[1]->setVisible(true);
			m_pStage[1]->runAction(_pScale);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void CStageLine::DownBoxStageCreator()
{
	auto Stage1 = [=]{
		CreateLine(LineDirection::Left, Point(340 + 160, 650 - 20), 400);
		m_pStage[0]->setPosition(Point(117 + 160, 663 - 30));
	};
	auto Stage2 = [=]{
		CreateLine(LineDirection::Down, Point(117 + 160, 663 - 20), 500);
		m_pStage[1]->setPosition(Point(117 + 13 + 160, 415));
	};
	auto Stage3 = [=]{
		CreateLine(LineDirection::Right, Point(117 + 13 + 160, 415), 400);
		m_pStage[2]->setPosition(Point(340 + 160, 415 ));
	};
	auto Stage4 = [=]{
		CreateLine(LineDirection::Right, Point(340 + 160, 415), 400);
		m_pStage[3]->setPosition(Point(563 + 160, 415 ));
	};
	auto Stage5 = [=]{
		CreateLine(LineDirection::Right, Point(563 + 160, 415), 400);
		m_pStage[4]->setPosition(Point(774 + 160, 415 ));
	};
	auto Stage6 = [=]{
		CreateLine(LineDirection::Right, Point(786 + 195, 415), 200);
		m_pStage[5]->setPosition(Point(897.5 + 195, 415 ));
	};
	auto Stage7 = [=]{
		CreateLine(LineDirection::Down, Point(897.5 + 195, 415 + 13), 400);
		m_pStage[6]->setPosition(Point(885.5 + 195, 231));
	};
	auto Stage8 = [=]{
		CreateLine(LineDirection::Left, Point(885.5 + 195, 231), 200);
		m_pStage[7]->setPosition(Point(774 + 155, 231));
	};
	auto Stage9 = [=]
	{
		CreateLine(LineDirection::Left, Point(774 + 195, 231), 400);
		m_pStage[8]->setPosition(Point(551 + 195, 231 ));
	};
	auto Stage10 = [=]
	{
		CreateLine(LineDirection::Left, Point(551 + 195, 231), 400);
		m_pStage[9]->setPosition(Point(328 + 195, 231));
	};

	auto CallStage = [=](int _num){
		switch (_num)
		{
		case 0:Stage1(); break;
		case 1:Stage2(); break;
		case 2:Stage3(); break;
		case 3:Stage4(); break;
		case 4:Stage5(); break;
		case 5:Stage6(); break;
		case 6:Stage7(); break;
		case 7:Stage8(); break;
		case 8:Stage9(); break;
		case 9:Stage10(); break;
		default:
			break;
		}
	};

	for (int i = 0; i <= m_nStagenum; i++)
	{
		CallStage(m_nStageCount);
		m_nStageCount++;
	}
}

void CStageLine::LeftBoxStageCreator()
{
	auto Stage1 = [=]{
		CreateLine(LineDirection::Left, Point(815, 60), 400);
		CreateLine(LineDirection::Up, Point(592, 49), 300);
		m_pStage[0]->setPosition(Point(592, 210));
	};
	auto Stage2 = [=]{
		CreateLine(LineDirection::Up, Point(592, 240), 300);
		m_pStage[1]->setPosition(Point(592, 420));
	};
	auto Stage3 = [=]{

	};
	auto Stage4 = [=]{

	};
	auto Stage5 = [=]{

	};
	auto Stage6 = [=]{

	};
	auto Stage7 = [=]{

	};
	auto Stage8 = [=]{

	};
	auto Stage9 = [=]
	{
	};
	auto Stage10 = [=]
	{

	};

	auto CallStage = [=](int _num){
		switch (_num)
		{
		case 0:Stage1(); break;
		case 1:Stage2(); break;
		case 2:Stage3(); break;
		case 3:Stage4(); break;
		case 4:Stage5(); break;
		case 5:Stage6(); break;
		case 6:Stage7(); break;
		case 7:Stage8(); break;
		case 8:Stage9(); break;
		case 9:Stage10(); break;
		default:
			break;
		}
	};

	for (int i = 0; i <= m_nStagenum; i++)
	{
		CallStage(m_nStageCount);
		m_nStageCount++;
	}
}

void CStageLine::RightBoxStageCreator()
{
	auto Stage1 = [=]{
		CreateLine(LineDirection::Right, Point(200, 560), 400);
		m_pStage[0]->setPosition(Point(443, 560));
	};
	auto Stage2 = [=]{
		CreateLine(LineDirection::Down, Point(443, 573), 400);
		m_pStage[1]->setPosition(Point(443, 340));
	};
	auto Stage3 = [=]{

	};
	auto Stage4 = [=]{

	};
	auto Stage5 = [=]{

	};
	auto Stage6 = [=]{

	};
	auto Stage7 = [=]{

	};
	auto Stage8 = [=]{

	};
	auto Stage9 = [=]
	{
	};
	auto Stage10 = [=]
	{

	};

	auto CallStage = [=](int _num){
		switch (_num)
		{
		case 0:Stage1(); break;
		case 1:Stage2(); break;
		case 2:Stage3(); break;
		case 3:Stage4(); break;
		case 4:Stage5(); break;
		case 5:Stage6(); break;
		case 6:Stage7(); break;
		case 7:Stage8(); break;
		case 8:Stage9(); break;
		case 9:Stage10(); break;
		default:
			break;
		}
	};

	for (int i = 0; i <= m_nStagenum; i++)
	{
		CallStage(m_nStageCount);
		m_nStageCount++;
	}
}