/***************************************************/
/* Nom:	Blackboard.h
/* Description: Blackboard
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Blackboard_H_
#define __Blackboard_H_

namespace crea
{
	class CREAENGINE_API Blackboard : public Singleton <Blackboard>
	{
	protected:
		// Blackboard
		map<string, string> m_variables;

	public:
		Blackboard() {}
		~Blackboard() {}

		void setVariable(const string& _variable, const string& _value) { m_variables[_variable] = _value; }
		string getVariable(const string& _variable) { return m_variables[_variable]; }
		
	};

}

#endif
