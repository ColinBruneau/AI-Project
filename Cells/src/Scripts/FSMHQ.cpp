#include "stdafx.h"

#include "Scripts\FSMHQ.h"
#include "Scripts\Messages.h"
#include <string.h>


//Add new states here
enum States {
	STATE_Spawn,
	STATE_Think,
	STATE_PerformAction,
	STATE_Idle,
};

enum PreconditionAndEffects {
	HqHaveGold,
	HqHaveFirewood,
	HqHaveTool,
	HqHaveLogs,
	HqHaveMoreGold,
	WoodCutterHaveLogs,
	WoodCutterHaveBranches,
	WoodCutterHaveFirewood,
	BlackSmithHaveGold,
	BlackSmithHaveFirewood,
	MinerHaveTool,
	WoodCutterHaveTool,
	BlackSmithHaveTool,
	LoggerHaveTool, 
};

FSMHQ::FSMHQ()
	: m_initState("initState"), m_goalState("goalState")
{

}

FSMHQ::~FSMHQ()
{

}

bool FSMHQ::States(StateMachineEvent _event, Msg* _msg, int _state)
{
	BeginStateMachine

		OnMsg(MSG_ActionCompleted)
		{
			if (_msg->GetSender() == m_pMiner->GetID())
			{
				// mining
				m_initState.setVariable(HqHaveGold, true);
			}
			else if (_msg->GetSender() == m_pWoodCutter->GetID())
			{
				if (m_initState.getVariable(WoodCutterHaveLogs) == false)
				{
					// pickupLogs
					if (m_initState.getVariable(HqHaveLogs) == true)
					{
						m_initState.setVariable(HqHaveLogs, false);
						m_initState.setVariable(WoodCutterHaveLogs, true);
					}
				}

				// Drop FireWood
				if (m_initState.getVariable(WoodCutterHaveFirewood) == true)
				{
					// cutting
					m_initState.setVariable(HqHaveFirewood, true);
					m_initState.setVariable(WoodCutterHaveFirewood, false);
				}
			}
			else if (_msg->GetSender() == m_pBlackSmith->GetID())
			{
				if (m_initState.getVariable(BlackSmithHaveGold) == false
					|| m_initState.getVariable(BlackSmithHaveFirewood) == false
					)
				{
					// pickupGold
					if (m_initState.getVariable(HqHaveGold) == true)
					{
						m_initState.setVariable(HqHaveGold, false);
						m_initState.setVariable(BlackSmithHaveGold, true);
					}
					// pickupFirewood
					if (m_initState.getVariable(HqHaveFirewood) == true)
					{
						m_initState.setVariable(HqHaveFirewood, false);
						m_initState.setVariable(BlackSmithHaveFirewood, true);
					}
				}
				else
				{
					// forging
					m_initState.setVariable(HqHaveTool, true);
				}
			}
			else if (_msg->GetSender() == m_pLogger->GetID())
			{
				// logging
				m_initState.setVariable(HqHaveLogs, true);
			}
			SetState(STATE_Think);
		}

		OnMsg(MSG_ToolBroken)
		{
			if (_msg->GetSender() == m_pMiner->GetID())
			{
				m_initState.setVariable(MinerHaveTool, false);
			}
			else if (_msg->GetSender() == m_pWoodCutter->GetID())
			{
				m_initState.setVariable(WoodCutterHaveTool, false);
			}
			else if (_msg->GetSender() == m_pBlackSmith->GetID())
			{
				// Do not lose tool for BlackSmith
				//m_initState.setVariable(BlackSmithHaveTool, false);
			}
			else if (_msg->GetSender() == m_pLogger->GetID())
			{
				m_initState.setVariable(LoggerHaveTool, false);
			}
		}

		OnMsg(MSG_Think)
			SetState(STATE_Think);

		///////////////////////////////////////////////////////////////
		State(STATE_Spawn)
		OnEnter
			// Get Entity
			m_pEntity = getEntity();

			m_pGM = GameManager::getSingleton();
			m_pMiner = m_pGM->getEntity("miner");
			m_pWoodCutter = m_pGM->getEntity("woodcutter");
			m_pBlackSmith = m_pGM->getEntity("blacksmith");
			m_pLogger = m_pGM->getEntity("logger");

			// Miner
			goap::Action pickupToolMiner("pickupToolMiner", 1);
			pickupToolMiner.setPrecondition(HqHaveTool, true);
			pickupToolMiner.setPrecondition(MinerHaveTool, false);
			pickupToolMiner.setEffect(HqHaveTool, false);
			pickupToolMiner.setEffect(MinerHaveTool, true);
			m_actionsPossible.push_back(pickupToolMiner);

			goap::Action mining("mining", 1);
			//mining.setPrecondition(HqHaveGold, false);
			mining.setPrecondition(MinerHaveTool, true);
			mining.setEffect(HqHaveGold, true); 
			mining.setEffect(HqHaveMoreGold, true);
			m_actionsPossible.push_back(mining);

			// WoodCutter
			goap::Action pickupToolWoodCutter("pickupToolWoodCutter", 1);
			pickupToolWoodCutter.setPrecondition(HqHaveTool, true);
			pickupToolWoodCutter.setPrecondition(WoodCutterHaveTool, false);
			pickupToolWoodCutter.setEffect(HqHaveTool, false);
			pickupToolWoodCutter.setEffect(WoodCutterHaveTool, true);
			m_actionsPossible.push_back(pickupToolWoodCutter);

			goap::Action pickupLogs("pickupLogs", 1);
			pickupLogs.setPrecondition(HqHaveLogs, true);
			pickupLogs.setPrecondition(WoodCutterHaveLogs, false);
			pickupLogs.setEffect(HqHaveLogs, false);
			pickupLogs.setEffect(WoodCutterHaveLogs, true);
			m_actionsPossible.push_back(pickupLogs);

			goap::Action pickupBranches("pickupBranches", 10);
			pickupBranches.setPrecondition(HqHaveLogs, false);
			pickupBranches.setPrecondition(WoodCutterHaveBranches, false);
			pickupBranches.setEffect(WoodCutterHaveBranches, true);
			m_actionsPossible.push_back(pickupBranches);

			goap::Action cutting("cutting", 1);
			cutting.setPrecondition(WoodCutterHaveLogs, true);
			cutting.setPrecondition(WoodCutterHaveTool, true);
			cutting.setEffect(WoodCutterHaveLogs, false);
			cutting.setEffect(HqHaveFirewood, true);
			m_actionsPossible.push_back(cutting);

			goap::Action cuttingBranches("cuttingBranches", 10);
			cuttingBranches.setPrecondition(WoodCutterHaveBranches, true);
			cuttingBranches.setPrecondition(WoodCutterHaveTool, true);
			cuttingBranches.setEffect(WoodCutterHaveBranches, false);
			cuttingBranches.setEffect(HqHaveFirewood, true);
			m_actionsPossible.push_back(cuttingBranches);

			// BlackSmith
			goap::Action pickupToolBlackSmith("pickupToolBlackSmith", 1);
			pickupToolBlackSmith.setPrecondition(HqHaveTool, true);
			pickupToolBlackSmith.setPrecondition(BlackSmithHaveTool, false);
			pickupToolBlackSmith.setEffect(HqHaveTool, false);
			pickupToolBlackSmith.setEffect(BlackSmithHaveTool, true);
			m_actionsPossible.push_back(pickupToolBlackSmith);

			goap::Action pickupGold("pickupGold", 1);
			pickupGold.setPrecondition(HqHaveGold, true);
			pickupGold.setPrecondition(BlackSmithHaveGold, false);
			pickupGold.setEffect(HqHaveGold, false);
			pickupGold.setEffect(BlackSmithHaveGold, true);
			m_actionsPossible.push_back(pickupGold);

			goap::Action pickupFirewood("pickupFirewood", 1);
			pickupFirewood.setPrecondition(HqHaveFirewood, true);
			pickupFirewood.setPrecondition(BlackSmithHaveFirewood, false);
			pickupFirewood.setEffect(HqHaveFirewood, false);
			pickupFirewood.setEffect(BlackSmithHaveFirewood, true);
			m_actionsPossible.push_back(pickupFirewood);

			goap::Action forging("forging", 1);
			forging.setPrecondition(BlackSmithHaveFirewood, true);
			forging.setPrecondition(BlackSmithHaveGold, true);
			forging.setPrecondition(BlackSmithHaveTool, true);
			forging.setPrecondition(HqHaveTool, false);
			forging.setEffect(BlackSmithHaveFirewood, false);
			forging.setEffect(BlackSmithHaveGold, false);
			forging.setEffect(HqHaveTool, true);
			m_actionsPossible.push_back(forging);

			// Logger
			goap::Action pickupToolLogger("pickupToolLogger", 1);
			pickupToolLogger.setPrecondition(HqHaveTool, true);
			pickupToolLogger.setPrecondition(LoggerHaveTool, false);
			pickupToolLogger.setEffect(HqHaveTool, false);
			pickupToolLogger.setEffect(LoggerHaveTool, true);
			m_actionsPossible.push_back(pickupToolLogger);

			goap::Action logging("logging", 1);
			logging.setPrecondition(HqHaveLogs, false);
			logging.setPrecondition(LoggerHaveTool, true);
			logging.setEffect(HqHaveLogs, true);
			m_actionsPossible.push_back(logging);
			
			// Init State
			m_initState.setVariable(HqHaveGold, false);
			m_initState.setVariable(HqHaveFirewood, false);
			m_initState.setVariable(HqHaveTool, false);
			m_initState.setVariable(HqHaveLogs, false);
			m_initState.setVariable(WoodCutterHaveLogs, false);
			m_initState.setVariable(BlackSmithHaveGold, false);
			m_initState.setVariable(BlackSmithHaveFirewood, false);
			m_initState.setVariable(MinerHaveTool, true);
			m_initState.setVariable(WoodCutterHaveTool, true);
			m_initState.setVariable(BlackSmithHaveTool, true);
			m_initState.setVariable(LoggerHaveTool, true);
			m_initState.setVariable(HqHaveMoreGold, false);
			m_initState.setVariable(WoodCutterHaveBranches, false);
			m_initState.setVariable(WoodCutterHaveFirewood, false);

			// Goal State
			//m_goalState.setVariable(HqHaveTool, true); // TD Planning, Q4
			m_goalState.setVariable(HqHaveMoreGold, true); // TD Planning, Q5
			
		OnUpdate
			SetState(STATE_Think);

		///////////////////////////////////////////////////////////////
		State(STATE_Think)
		OnEnter
			m_actionsToDo.clear();
			try {
				m_actionsToDo = m_planner.plan(m_initState, m_goalState, m_actionsPossible);
				if (m_actionsToDo.empty())
				{
					std::cout << "Goal achieved!\n";
					m_initState.setVariable(HqHaveMoreGold, false);
					SendDelayedMsgToMe(0.5f, MSG_Think);
				}
				else
				{
					std::cout << "Found a path!\n";
					for (std::vector<goap::Action>::reverse_iterator rit = m_actionsToDo.rbegin(); rit != m_actionsToDo.rend(); ++rit) {
						std::cout << rit->name() << std::endl;
					}
					SetState(STATE_PerformAction);
				}
			}
			catch (const std::exception&) {
				std::cout << "Sorry, could not find a path!\n";
			}

		OnUpdate

		OnExit

		///////////////////////////////////////////////////////////////
		State(STATE_PerformAction)
		OnEnter
			if (!m_actionsToDo.empty())
			{
				// Send orders
				goap::Action actionToDo = m_actionsToDo.back();
				m_actionsToDo.pop_back();
				if (actionToDo.name() == "mining")
				{
					SendDelayedMsg(0.5f, MSG_Mine, m_pMiner->GetID());
				}
				else if (actionToDo.name() == "cutting")
				{
					m_initState.setVariable(WoodCutterHaveFirewood, true);
					SendDelayedMsg(0.5f, MSG_CutWood, m_pWoodCutter->GetID());
				}
				else if (actionToDo.name() == "cuttingBranches")
				{
					SendDelayedMsg(0.5f, MSG_CutWood, m_pWoodCutter->GetID());
				}
				else if (actionToDo.name() == "pickupBranches")
				{
					m_initState.setVariable(WoodCutterHaveFirewood, true);
					SendDelayedMsg(0.5f, MSG_PickupBranches, m_pWoodCutter->GetID());
				}
				else if (actionToDo.name() == "forging")
				{
					SendDelayedMsg(0.5f, MSG_Build, m_pBlackSmith->GetID());
				}
				else if (actionToDo.name() == "logging")
				{
					SendDelayedMsg(0.5f, MSG_Harvest, m_pLogger->GetID());
				}
				else if (actionToDo.name() == "pickupLogs")
				{
					SendDelayedMsg(0.5f, MSG_GoTo, m_pWoodCutter->GetID());
				}
				else if (actionToDo.name() == "pickupGold")
				{
					SendDelayedMsg(0.5f, MSG_GoTo, m_pBlackSmith->GetID());
				}
				else if (actionToDo.name() == "pickupFirewood")
				{
					SendDelayedMsg(0.5f, MSG_GoTo, m_pBlackSmith->GetID());
				}
				else if (actionToDo.name() == "pickupToolMiner")
				{
					m_initState.setVariable(HqHaveTool, false);
					m_initState.setVariable(MinerHaveTool, true);
					SendDelayedMsg(0.5f, MSG_NewTool, m_pMiner->GetID());
					SendDelayedMsgToMe(0.5f, MSG_Think);
				}
				SetState(STATE_Idle);
			}
			else
			{
				SetState(STATE_Think);
			}

		///////////////////////////////////////////////////////////////
		State(STATE_Idle)
		OnEnter
EndStateMachine
}