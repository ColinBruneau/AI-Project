#include "stdafx.h"

#include "AI\Agent.h"
#include "Core\GameManager.h"

namespace crea
{
	Agent::Agent() : m_iStrength(10), m_iDexterity(10), m_iIntelligence(10), m_iHealth(10)
	{
	}

	Agent::~Agent()
	{
	}

	bool Agent::loadFromFileJSON(const string&_filename)
	{
		Json::Value root;
		std::ifstream config_doc(_filename, std::ifstream::binary);
		config_doc >> root;

		m_iStrength = root["Strength"].asInt();
		m_iDexterity = root["Dexterity"].asInt();
		m_iIntelligence = root["Intelligence"].asInt();
		m_iHealth = root["Health"].asInt();
		m_nSize = (short)root["Size"].asInt();
		m_nCapability = (short)root["Capability"].asInt();

		return true;
	}

	bool Agent::init()
	{
		return true;
	}

	bool Agent::update()
	{
		return true;
	}

	bool Agent::draw()
	{
		return true;
	}

	bool Agent::quit()
	{
		return true;
	}

} // namespace crea
