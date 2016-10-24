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

	string* ActionTable::getAnimation(	char _cAnimCond,
										char _cAction, 
										string* _pszActionDesc)
	{
		//unsigned long key = CREATE_KEY(_cAnimCond, _cAction);
		MapConditionAction::iterator ca_it;
		MapActionAnimation::iterator aa_it;
		ActionAnimInfo*  pAnimInfo = nullptr;
		ca_it = m_condActionMap.find(_cAnimCond);
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
		if (_cAnimCond != 0)
		{
			return getAnimation(0, _cAction, _pszActionDesc);
		}
		return nullptr;
	}

	bool ActionTable::addAnimation(	char _cAnimCond,
									char _cAction,
									string* _pszAnimFileName,
									string* _pszActionDesc)
	{
		MapConditionAction::iterator ca_it;
		MapActionAnimation::iterator aa_it;
		ActionAnimInfo*  pAnimInfo = nullptr;
		ca_it = m_condActionMap.find(_cAnimCond);
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
			pAnimInfo->szActionDesc = (_pszActionDesc ? *_pszActionDesc : "");
			(*pActionAnimMap)[_cAction] = pAnimInfo;
			return true;
		}
		// No condition was found so create a new map of actions for this condition
		m_condActionMap[_cAnimCond] = new MapActionAnimation;
		//And add the action and animation
		return addAnimation(_cAnimCond, _cAction, _pszAnimFileName, _pszActionDesc);
	}

	string getParamInQuotes(string _s)
	{
		string tester = "\""; 
		int startPos = _s.find(":");
		int findPos = _s.find(tester, startPos + 1); //finds first quote mark
		int findPos2 = _s.find(tester, findPos + 1); //finds second quote mark
		return _s.substr(findPos+1, findPos2 - findPos -1);
	}

	int getValue(string _s)
	{
		int startPos = _s.find(":");
		int findPos = _s.find(",", startPos + 1); //finds first quote mark
		return stoi(_s.substr(startPos + 1, findPos - 1));
	}

	bool ActionTable::loadFromFile(string& _filename)
	{
		ifstream isFile;
		char caLine[256];
		string szAnimationName;
		char cConditionId = 0, cActionId = 0;
		bool bInConditions = false;
		bool bInActions = false;
		bool bInAction = false;

		// On ouvre le fichier
		isFile.open(_filename, ios::in);
		if (isFile.fail())
		{
			cerr << "erreur d'ouverture " << _filename << endl;
			return false;
		}

		do
		{
			// On parcourt le fichier
			isFile.getline(caLine, sizeof(caLine));
			string szLine(caLine);
			if (!bInConditions && szLine.find("conditions") != std::string::npos)
			{
				bInConditions = true;
			}
			if (bInConditions && !bInActions && szLine.find("\"id") != std::string::npos)
			{
				cConditionId = getValue(caLine);
			}
			if (bInConditions && szLine.find("actions") != std::string::npos)
			{
				bInActions = true;
			}
			if (bInConditions && bInActions && szLine.find("\"id") != std::string::npos)
			{
				bInAction = true;
				cActionId = getValue(caLine);
			}
			if (bInConditions && bInAction && szLine.find("animation") != std::string::npos)
			{
				szAnimationName = getParamInQuotes(caLine);
				addAnimation(cConditionId, cActionId, &szAnimationName);
				bInAction = false;
			}
			if (bInConditions && bInActions && szLine.find("]") != std::string::npos)
			{
				bInActions = false;
			}
			if (bInConditions && !bInActions && szLine.find("]") != std::string::npos)
			{
				bInConditions = false;
			}
		} while (!isFile.eof());

		isFile.close();

		return true;
	}

	bool ActionTable::loadFromFileJSON(string& _filename)
	{
		Json::Value root;
		std::ifstream config_doc(_filename, std::ifstream::binary);
		config_doc >> root;

		//cout << root << "\n";

		Json::Value conditions = root["conditions"];

		for (unsigned int iCond = 0; iCond < conditions.size(); ++iCond)
		{
			//cout << conditions[index]["actions"];
			Json::Value actions = conditions[iCond]["actions"];
			for (unsigned int iAct = 0; iAct < actions.size(); ++iAct)
			{
				Json::Value action = actions[iAct];
				cout << action["name"] << action["id"] << action["animation"];
				addAnimation(conditions[iCond]["id"].asInt(), action["id"].asInt(), &action["animation"].asString());
			}
		}

		return true;
	}

} // namespace crea
