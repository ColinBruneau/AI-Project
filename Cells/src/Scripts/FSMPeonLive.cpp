#include "stdafx.h"

#include "Scripts\FSMPeonLive.h"
#include "Scripts\Messages.h"
#include "Scripts\Actions.h"
#include <string.h>


FSMPeonLive::FSMPeonLive()
{
}

FSMPeonLive::~FSMPeonLive()
{

}

bool FSMPeonLive::States(StateMachineEvent _event, Msg* _msg, int _state)
{
	BeginStateMachine

		OnMsg(MSG_Stop);
	SetState(STATE_Idle);

	OnMsg(MSG_GoToWithGold)
		m_pTarget = m_pHQ;
	m_vTarget = m_pTarget->getPosition() + Vector2f(20.f, 40.f);
	//m_pCharacterController->setCondition(kACond_Gold);
	SetState(STATE_GoTo);

	OnMsg(MSG_GoToWithLumber)
		m_pTarget = m_pHQ;
	m_vTarget = m_pTarget->getPosition() + Vector2f(20.f, 40.f);
	//m_pCharacterController->setCondition(kACond_Lumber);
	SetState(STATE_GoTo);

	OnMsg(MSG_GoTo)
		m_pTarget = m_pHQ;
	m_vTarget = m_pTarget->getPosition() + Vector2f(20.f, 40.f);
	//m_pCharacterController->setCondition(kACond_Default);
	SetState(STATE_GoTo);

	OnMsg(MSG_Build)
		m_pTarget = m_pGM->getEntity("forge1");
	m_vTarget = m_pTarget->getPosition() + Vector2f(0.f, 20.f);
	SetState(STATE_GoTo);

	OnMsg(MSG_Mine)
		m_pTarget = m_pGM->getEntity("mine1");
	m_vTarget = m_pTarget->getPosition() + Vector2f(-20.f, 20.f);
	SetState(STATE_GoTo);

	OnMsg(MSG_Harvest)
		m_pTarget = m_pGM->getEntity("tree1");
	m_vTarget = m_pTarget->getPosition() + Vector2f(0.f, 40.f);
	SetState(STATE_GoTo);

	OnMsg(MSG_CutWood)
		m_pTarget = m_pGM->getEntity("lumbermill1");
	m_vTarget = m_pTarget->getPosition() + Vector2f(-20.f, 20.f);
	SetState(STATE_GoTo);

	OnMsg(MSG_Kill)
		SetState(STATE_Kill);

	OnMsg(MSG_Hit)
		SetState(STATE_Hit);

	OnMsg(MSG_HitStop)
		while (SetStateInHistory() == STATE_Hit);

	OnMsg(MSG_ToolUsed)
		m_iToolPV -= 1;
	cout << m_pEntity->getName() << " tool used " << m_iToolPV << endl;
	if (m_iToolPV == 0)
	{
		SendDelayedMsg(0.0f, MSG_ToolBroken, m_pEntity->GetID());
	}

	OnMsg(MSG_NewTool)
		m_iToolPV = 2;

	OnMsg(MSG_ToolBroken)
	{
		Blackboard* pBB = Blackboard::getSingleton();
		if (_msg->GetSender() == m_pMiner->GetID())
		{
			pBB->setVariable("MinerHaveTool", "0");
		}
		else if (_msg->GetSender() == m_pLogger->GetID())
		{
			pBB->setVariable("LoggerHaveTool", "0");
		}
	}

	///////////////////////////////////////////////////////////////
	State(STATE_Init)
		OnEnter
		// Get Entity
		m_pEntity = getEntity();
	// Get CharacterController
	m_pCharacterController = m_pEntity->getComponent<CharacterController>();
	// Get SpriteRenderer
	m_pSpriteRenderer = m_pEntity->getComponent<SpriteRenderer>();
	// Get Agent
	m_pAgent = m_pEntity->getComponent<Agent>();
	// Get HQ
	m_pHQ = m_pGM->getEntity("hq1");
	m_pTree = m_pGM->getEntity("tree1");
	m_pMiner = m_pGM->getEntity("miner");
	m_pWoodCutter = m_pGM->getEntity("woodcutter");
	m_pBlackSmith = m_pGM->getEntity("blacksmith");
	m_pLogger = m_pGM->getEntity("logger");
	// Get Blackboard
	Blackboard* pBB = Blackboard::getSingleton();

	// TD Behavior Tree
	ActionGoTo* pActionGoToHQ = new ActionGoTo(this, MSG_GoTo);
	ActionGoTo* pActionGoToTree = new ActionGoTo(this, MSG_Harvest);
	ActionGoTo* pActionGoToLumberMill = new ActionGoTo(this, MSG_CutWood);
	ActionGoTo* pActionGoToMine = new ActionGoTo(this, MSG_Mine);
	ActionGoTo* pActionGoToForge = new ActionGoTo(this, MSG_Build);
	ActionSetCondition* pActionSetConditionDefault = new ActionSetCondition(m_pCharacterController, kACond_Default);
	ActionSetCondition* pActionSetConditionGold = new ActionSetCondition(m_pCharacterController, kACond_Gold);
	ActionSetCondition* pActionSetConditionLumber = new ActionSetCondition(m_pCharacterController, kACond_Lumber);
	PreCondition* pPreConditionHqHaveNoGold = new PreCondition(pBB, "HqHaveGold", "0");
	PreCondition* pPreConditionHqHaveGold = new PreCondition(pBB, "HqHaveGold", "1");
	Effect* pEffectHqHaveNoGold = new Effect(pBB, "HqHaveGold", "0");
	Effect* pEffectHqHaveGold = new Effect(pBB, "HqHaveGold", "1");
	PreCondition* pPreConditionHqHaveNoLogs = new PreCondition(pBB, "HqHaveLogs", "0");
	PreCondition* pPreConditionHqHaveLogs = new PreCondition(pBB, "HqHaveLogs", "1");
	Effect* pEffectHqHaveNoLogs = new Effect(pBB, "HqHaveLogs", "0");
	Effect* pEffectHqHaveLogs = new Effect(pBB, "HqHaveLogs", "1");
	PreCondition* pPreConditionHqHaveNoFireWood = new PreCondition(pBB, "HqHaveFireWood", "0");
	PreCondition* pPreConditionHqHaveFireWood = new PreCondition(pBB, "HqHaveFireWood", "1");
	Effect* pEffectHqHaveNoFireWood = new Effect(pBB, "HqHaveFireWood", "0");
	Effect* pEffectHqHaveFireWood = new Effect(pBB, "HqHaveFireWood", "1");
	PreCondition* pPreConditionHqHaveNoTool = new PreCondition(pBB, "HqHaveTool", "0");
	PreCondition* pPreConditionHqHaveTool = new PreCondition(pBB, "HqHaveTool", "1");
	Effect* pEffectHqHaveNoTool = new Effect(pBB, "HqHaveTool", "0");
	Effect* pEffectHqHaveTool = new Effect(pBB, "HqHaveTool", "1");

	PreCondition* pPreConditionMinerHaveNoTool = new PreCondition(pBB, "MinerHaveTool", "0");
	PreCondition* pPreConditionMinerHaveTool = new PreCondition(pBB, "MinerHaveTool", "1");
	Effect* pEffectMinerHaveNoTool = new Effect(pBB, "MinerHaveTool", "0");
	Effect* pEffectMinerHaveTool = new Effect(pBB, "MinerHaveTool", "1");

	PreCondition* pPreConditionLoggerHaveNoTool = new PreCondition(pBB, "LoggerHaveTool", "0");
	PreCondition* pPreConditionLoggerHaveTool = new PreCondition(pBB, "LoggerHaveTool", "1");
	Effect* pEffectLoggerHaveNoTool = new Effect(pBB, "LoggerHaveTool", "0");
	Effect* pEffectLoggerHaveTool = new Effect(pBB, "LoggerHaveTool", "1");

	PreCondition* pPreConditionCutterHaveNoTool = new PreCondition(pBB, "CutterHaveTool", "0");
	PreCondition* pPreConditionCutterHaveTool = new PreCondition(pBB, "CutterHaveTool", "1");
	Effect* pEffectCutterHaveNoTool = new Effect(pBB, "CutterHaveTool", "0");
	Effect* pEffectCutterHaveTool = new Effect(pBB, "CutterHaveTool", "1");
	PreCondition* pPreConditionCutterHaveWood = new PreCondition(pBB, "CutterHaveWood", "1");
	Effect* pEffectCutterHaveWood = new Effect(pBB, "CutterHaveWood", "1");

	ActionSendMsg* pUseTool = new ActionSendMsg(this, MSG_ToolUsed);
	ActionSendMsg* pNewTool = new ActionSendMsg(this, MSG_NewTool);

	// Hide2Secs
	FilterTimer* pWait2secs = new FilterTimer(Time(2));
	ActionWait* pActionWait = new ActionWait();
	pWait2secs->addChild(pActionWait);
	ActionActivateSpriteRenderer* pActionDisplay = new ActionActivateSpriteRenderer(m_pSpriteRenderer, true);
	ActionActivateSpriteRenderer* pActionHide = new ActionActivateSpriteRenderer(m_pSpriteRenderer, false);
	bt::Sequence* pHide2Secs = new bt::Sequence();
	pHide2Secs->addChild(pActionHide);
	pHide2Secs->addChild(pWait2secs);
	pHide2Secs->addChild(pActionDisplay);

	// Pickup Tool
	bt::Sequence* pPickupTool = new bt::Sequence();
	pPickupTool->addChild(pActionGoToHQ);
	pPickupTool->addChild(pHide2Secs);
	pPickupTool->addChild(pNewTool);

	// Miner
	if (m_pEntity->getName() == "miner")
	{
		// Get Gold
		bt::Sequence* pGetGold = new bt::Sequence();
		pGetGold->addChild(pActionGoToMine);
		pGetGold->addChild(pHide2Secs);
		pGetGold->addChild(pUseTool);

		// Drop in HQ
		bt::Sequence* pDropInHQ = new bt::Sequence();
		pDropInHQ->addChild(pActionGoToHQ);
		pDropInHQ->addChild(pHide2Secs);

		// Mining
		bt::Sequence* pMining = new bt::Sequence();
		pMining->addChild(pActionSetConditionDefault);
		pMining->addChild(pGetGold);
		pMining->addChild(pActionSetConditionGold);
		pMining->addChild(pDropInHQ);
		pMining->addChild(pActionSetConditionDefault);

		// Get Tool
		bt::Sequence* pGetTool = new bt::Sequence();
		pGetTool->addChild(pPreConditionHqHaveTool);
		pGetTool->addChild(pPickupTool);
		pGetTool->addChild(pEffectHqHaveNoTool);
		pGetTool->addChild(pEffectMinerHaveTool);

		// Have Tool
		bt::Selector* pHaveTool = new bt::Selector();
		pHaveTool->addChild(pPreConditionMinerHaveTool);
		pHaveTool->addChild(pGetTool);

		// Goal HQ have Gold
		bt::Sequence* pGoalHQHaveGold = new bt::Sequence();
		pGoalHQHaveGold->addChild(pHaveTool);
		pGoalHQHaveGold->addChild(pMining);
		pGoalHQHaveGold->addChild(pEffectHqHaveGold);

		m_bt.setRootBehavior(pGoalHQHaveGold);

		// Tests
		pBB->setVariable("MinerHaveTool", "1");
		SendDelayedMsg(0.0f, MSG_NewTool, m_pEntity->GetID());
	}

	// Logger
	if (m_pEntity->getName() == "logger")
	{
		// Chop 3 Secs
		FilterTimer* pChop3secs = new FilterTimer(Time(3));
		ActionSetAction* pActionChop = new ActionSetAction(m_pCharacterController, kAct_Chop);
		pChop3secs->addChild(pActionChop);

		// Get Lumber
		bt::Sequence* pGetLumber = new bt::Sequence();
		pGetLumber->addChild(pActionGoToTree);
		pGetLumber->addChild(pChop3secs);
		pGetLumber->addChild(pUseTool);

		// Drop in HQ
		bt::Sequence* pDropInHQ = new bt::Sequence();
		pDropInHQ->addChild(pActionGoToHQ);
		pDropInHQ->addChild(pHide2Secs);

		// Logging
		bt::Sequence* pLogging = new bt::Sequence();
		pLogging->addChild(pActionSetConditionDefault);
		pLogging->addChild(pGetLumber);
		pLogging->addChild(pActionSetConditionLumber);
		pLogging->addChild(pDropInHQ);
		pLogging->addChild(pActionSetConditionDefault);

		// Get Tool
		bt::Sequence* pGetTool = new bt::Sequence();
		pGetTool->addChild(pPreConditionHqHaveTool);
		pGetTool->addChild(pPickupTool);
		pGetTool->addChild(pEffectHqHaveNoTool);
		pGetTool->addChild(pEffectLoggerHaveTool);

		// Have Tool
		bt::Selector* pHaveTool = new bt::Selector();
		pHaveTool->addChild(pPreConditionLoggerHaveTool);
		pHaveTool->addChild(pGetTool);

		// Goal HQ have Gold
		bt::Sequence* pGoalHQHaveGold = new bt::Sequence();
		pGoalHQHaveGold->addChild(pHaveTool);
		pGoalHQHaveGold->addChild(pLogging);
		pGoalHQHaveGold->addChild(pEffectHqHaveLogs);

		m_bt.setRootBehavior(pGoalHQHaveGold);

		// Tests
		pBB->setVariable("LoggerHaveTool", "1");
		SendDelayedMsg(0.0f, MSG_NewTool, m_pEntity->GetID());
	}

	// WoodCutter
	if (m_pEntity->getName() == "woodcutter")
	{
		// Get FireWood
		bt::Sequence* pGetFireWood = new bt::Sequence();
		pGetFireWood->addChild(pActionGoToLumberMill);
		pGetFireWood->addChild(pHide2Secs);

		// Drop in HQ
		bt::Sequence* pDropInHQ = new bt::Sequence();
		pDropInHQ->addChild(pActionGoToHQ);
		pDropInHQ->addChild(pHide2Secs);

		// Cutting
		bt::Sequence* pCutting = new bt::Sequence();
		pCutting->addChild(pActionSetConditionLumber);
		pCutting->addChild(pGetFireWood);
		pCutting->addChild(pActionSetConditionGold);
		pCutting->addChild(pDropInHQ);
		pCutting->addChild(pActionSetConditionDefault);

		// Get Tool
		bt::Sequence* pGetTool = new bt::Sequence();
		pGetTool->addChild(pPreConditionCutterHaveTool);
		pGetTool->addChild(pPickupTool);
		pGetTool->addChild(pEffectCutterHaveTool);

		// Have Tool
		bt::Selector* pHaveTool = new bt::Selector();
		pHaveTool->addChild(pPreConditionCutterHaveTool);
		pHaveTool->addChild(pGetTool);

		// Pickup Logs
		bt::Sequence* pPickupLogs = new bt::Sequence();
		pPickupLogs->addChild(pActionSetConditionDefault);
		pPickupLogs->addChild(pActionGoToHQ);
		pPickupLogs->addChild(pHide2Secs);
		pPickupLogs->addChild(pActionSetConditionLumber);

		// Get Logs
		bt::Sequence* pGetLogs = new bt::Sequence();
		pGetLogs->addChild(pPreConditionHqHaveLogs);
		pGetLogs->addChild(pPickupLogs);
		pGetLogs->addChild(pEffectHqHaveNoLogs);
		pGetLogs->addChild(pEffectCutterHaveWood);

		// Pickup Branches
		bt::Sequence* pPickupBranches = new bt::Sequence();
		pPickupBranches->addChild(pActionSetConditionDefault);
		pPickupBranches->addChild(pActionGoToTree);
		pPickupBranches->addChild(pHide2Secs);
		pPickupBranches->addChild(pActionSetConditionLumber);

		// Get Branches
		bt::Sequence* pGetBranches = new bt::Sequence();
		pGetBranches->addChild(pPickupBranches);
		pGetLogs->addChild(pEffectCutterHaveWood);

		// Have Wood
		bt::Selector* pHaveWood = new bt::Selector();
		pHaveWood->addChild(pPreConditionCutterHaveWood);
		pHaveWood->addChild(pGetLogs);
		pHaveWood->addChild(pGetBranches);

		// Goal HQ have FireWood
		bt::Sequence* pGoalHQHaveFireWood = new bt::Sequence();
		pGoalHQHaveFireWood->addChild(pHaveTool);
		pGoalHQHaveFireWood->addChild(pHaveWood);
		pGoalHQHaveFireWood->addChild(pCutting);
		pGoalHQHaveFireWood->addChild(pEffectHqHaveFireWood);

		m_bt.setRootBehavior(pGoalHQHaveFireWood);

		// Tests
		pBB->setVariable("CutterHaveTool", "1");
		SendDelayedMsg(0.0f, MSG_NewTool, m_pEntity->GetID());
	}

	// BlackSmith
	if (m_pEntity->getName() == "blacksmith")
	{
		// Pickup fireWood and Gold
		bt::Sequence* pPickupFireWoodAndGold = new bt::Sequence();
		pPickupFireWoodAndGold->addChild(pActionGoToHQ);
		pPickupFireWoodAndGold->addChild(pHide2Secs);

		// Forge Tool
		bt::Sequence* pForgeTool = new bt::Sequence();
		pForgeTool->addChild(pActionGoToForge);
		pForgeTool->addChild(pHide2Secs);

		// Drop in HQ
		bt::Sequence* pDropInHQ = new bt::Sequence();
		pDropInHQ->addChild(pActionGoToHQ);
		pDropInHQ->addChild(pHide2Secs);

		// Forging
		bt::Sequence* pForging = new bt::Sequence();
		pForging->addChild(pActionSetConditionDefault);
		pForging->addChild(pPickupFireWoodAndGold);
		pForging->addChild(pActionSetConditionGold);
		pForging->addChild(pForgeTool);
		pForging->addChild(pActionSetConditionGold);
		pForging->addChild(pDropInHQ);
		pForging->addChild(pActionSetConditionDefault);

		//  Goal HQ Have Tool
		bt::Sequence* pGoalHQHaveTool = new bt::Sequence();
		pGoalHQHaveTool->addChild(pPreConditionHqHaveGold);
		pGoalHQHaveTool->addChild(pPreConditionHqHaveFireWood);
		pGoalHQHaveTool->addChild(pForging);
		pGoalHQHaveTool->addChild(pEffectHqHaveTool);

		m_bt.setRootBehavior(pGoalHQHaveTool);
	}


	m_pEntity->addComponent(&m_bt);

	///////////////////////////////////////////////////////////////
	State(STATE_Idle)
		OnEnter
		m_pCharacterController->setAction(kAct_Default);
	m_pCharacterController->move(Vector2f(0.f, 0.f));

	///////////////////////////////////////////////////////////////
	State(STATE_GoTo)
		OnEnter
		m_pFSMPeonGoTo = new FSMPeonGoTo(m_vTarget);
	m_pEntity->addComponent(m_pFSMPeonGoTo);
	m_pFSMPeonGoTo->Initialize(m_pEntity);

	OnUpdate
		//m_pFSMPeonGoTo->Update();
		/*
		if (m_pFSMPeonGoTo->GetState() == FSMPeonGoTo::STATE_CompletedPath)
		{
		SetState(STATE_Idle);
		}*/
		OnExit
		m_pEntity->removeComponent(m_pFSMPeonGoTo);
	delete m_pFSMPeonGoTo;
	m_pFSMPeonGoTo = nullptr;

	///////////////////////////////////////////////////////////////
	State(STATE_Hit)
		OnEnter
		// CB: a hit is a temporary death...
		SendDelayedMsgToMe(0.5f, MSG_HitStop);
	m_condition = m_pCharacterController->getCondition();

	OnUpdate
		m_pCharacterController->setCondition(kACond_Default);
	m_pCharacterController->setAction(kAct_Die);

	OnExit
		m_pCharacterController->setCondition(m_condition);
	m_pCharacterController->setAction(kAct_Default);

	///////////////////////////////////////////////////////////////
	State(STATE_Kill)
		OnEnter
		m_pCharacterController->setCondition(kACond_Default);
	m_pCharacterController->setAction(kAct_Chop);

	///////////////////////////////////////////////////////////////
	State(STATE_Build)
		OnEnter
		m_pCharacterController->setCondition(kACond_Default);
	m_pCharacterController->setAction(kAct_Chop);

	///////////////////////////////////////////////////////////////
	State(STATE_Mine)
		OnEnter
		m_pCharacterController->setCondition(kACond_Default);
	m_pCharacterController->setAction(kAct_Chop);
	SetState(STATE_GoTo);

	///////////////////////////////////////////////////////////////
	State(STATE_Harvest)
		OnUpdate
		m_pCharacterController->setCondition(kACond_Default);
	m_pCharacterController->setAction(kAct_Chop);


	EndStateMachine
}
