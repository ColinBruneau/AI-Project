/***************************************************/
/* Nom:	Agent.h
/* Description: Agent
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Agent_H_
#define __Agent_H_

#include "Core\Component.h"

namespace crea
{
	class ISprite;

	class CREAENGINE_API Agent : public Component
	{
		int m_iStrength;
		int m_iDexterity;
		int m_iIntelligence;
		int m_iHealth;

	public:
		Agent();
		virtual ~Agent();

		inline void setStrength(int _iStength) { m_iStrength = _iStength; }
		inline void setDexterity(int _iDexterity) { m_iDexterity = _iDexterity; }
		inline void setIntelligence(int _iIntelligence) { m_iIntelligence = _iIntelligence; }
		inline void setHealth(int _iHealth) { m_iHealth = _iHealth; }

		inline int getStrength() const { return m_iStrength; }
		inline int getDexterity() const { return m_iDexterity; }
		inline int getIntelligence() const { return m_iIntelligence; }
		inline int getHealth() const { return m_iHealth; }

		bool loadFromFileJSON(string _filename);

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();

	};

} // namespace crea

#endif
