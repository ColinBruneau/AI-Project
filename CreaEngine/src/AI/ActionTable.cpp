#include "stdafx.h"

#include "AI\ActionTable.h"
#include "json\json.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace crea
{
	ActionTable::ActionTable()
	{
		m_pGM = crea::GameManager::getSingleton();
	}

	ActionTable::~ActionTable()
	{
		// delete 1st level map
		MapConditionAction::iterator ca_it = m_condActionMap.begin();
		while (ca_it != m_condActionMap.end()) {
			MapActionAnimation* pActionAnimMap = ca_it->second;

			// delete 2nd level map
			MapActionAnimation::iterator aa_it = pActionAnimMap->begin();
			while (aa_it != pActionAnimMap->end()) {
				delete (*aa_it).second;
				aa_it = pActionAnimMap->erase(aa_it);
			}

			delete (*ca_it).second;
			ca_it = m_condActionMap.erase(ca_it);
		}

	}

	void ActionTable::read()
	{

	}

	string* ActionTable::getAnimation(	char _cAnimDir, 
										char _cAnimCond,
										char _cAction, 
										string* _pszActionDesc)
	{
		// CB: use CREATE_KEY(_cAnimDir, _cAnimCond) to get 1 key
		//unsigned long key = CREATE_KEY(_cAnimCond, _cAction);
		MapConditionAction::iterator ca_it;
		MapActionAnimation::iterator aa_it;
		ActionAnimInfo*  pAnimInfo = nullptr;
		int keyDirCond = CREATE_KEY(_cAnimDir, _cAnimCond);
		ca_it = m_condActionMap.find(keyDirCond);
		// Get list of actions for this animation condition
		if (ca_it != m_condActionMap.end())
		{
			MapActionAnimation* pActionAnimMap = ca_it->second;
			aa_it = pActionAnimMap->find(_cAction);
			pAnimInfo = aa_it->second;
			if (_pszActionDesc)
			{
				*_pszActionDesc = pAnimInfo->szActionDesc;
			}
			return &pAnimInfo->szAnimFileName;
		}
		// No animation was found for the specified eAnimCond and eAction, so get default animation
		if (keyDirCond != 0)
		{
			return getAnimation(0, 0, _cAction, _pszActionDesc);
		}
		return nullptr;
	}

	bool ActionTable::addAnimation(	char _cAnimDir, 
									char _cAnimCond,
									char _cAction,
									string* _pszAnimFileName,
									string* _pszActionDesc)
	{
		MapConditionAction::iterator ca_it;
		MapActionAnimation::iterator aa_it;
		ActionAnimInfo*  pAnimInfo = nullptr;
		int keyDirCond = CREATE_KEY(_cAnimDir, _cAnimCond);
		ca_it = m_condActionMap.find(keyDirCond);
		// Get list of actions for this animation condition
		if (ca_it != m_condActionMap.end())
		{
			MapActionAnimation* pActionAnimMap = ca_it->second;
			aa_it = pActionAnimMap->find(_cAction);

			if (aa_it != pActionAnimMap->end())
			{
				// If there is an action for this condition, replace animation
				pAnimInfo = aa_it->second;
			}
			else
			{
				// If there is no action for this condition, add animation
				pAnimInfo = new ActionAnimInfo;
			}
			pAnimInfo->szAnimFileName = *_pszAnimFileName;

			// Load animation
			m_pGM->getAnimation(pAnimInfo->szAnimFileName);

			pAnimInfo->szActionDesc = (_pszActionDesc ? *_pszActionDesc : "");
			(*pActionAnimMap)[_cAction] = pAnimInfo;
			return true;
		}
		// No condition was found so create a new map of actions for this condition
		m_condActionMap[keyDirCond] = new MapActionAnimation;
		//And add the action and animation
		return addAnimation(_cAnimDir, _cAnimCond, _cAction, _pszAnimFileName, _pszActionDesc);
	}

	bool ActionTable::loadFromFileJSON(string& _filename)
	{
		Json::Value root;
		std::ifstream config_doc(_filename, std::ifstream::binary);
		config_doc >> root;

		Json::Value conditions = root["conditions"];

		for (unsigned int iCond = 0; iCond < conditions.size(); ++iCond)
		{
			Json::Value actions = conditions[iCond]["actions"];
			for (unsigned int iAct = 0; iAct < actions.size(); ++iAct)
			{
				Json::Value action = actions[iAct];
				Json::Value animations = action["animations"];
				for (unsigned int iAnimation = 0; iAnimation < animations.size(); ++iAnimation)
				{
					Json::Value animation = animations[iAnimation];
					addAnimation(iAnimation, conditions[iCond]["id"].asInt(), action["id"].asInt(), &animation.asString());
				}
			}
		}

		return true;
	}

} // namespace crea
