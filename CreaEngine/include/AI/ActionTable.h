/***************************************************/
/* Nom:	ActionTable.h
/* Description: ActionTable
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __ActionTable_H_
#define __ActionTable_H_

namespace crea
{
	#define CREATE_KEY(condition, action) (condition << 16) | action

	class CREAENGINE_API ActionAnimInfo
	{
	public:
		string	szAnimFileName;
		string	szActionDesc;
	};

	class CREAENGINE_API MapActionAnimation : public std::map<char, ActionAnimInfo*> {};
	class CREAENGINE_API MapConditionAction : public std::map<char, MapActionAnimation*> {};

	class CREAENGINE_API ActionTable
	{

	protected:
		MapConditionAction	m_condActionMap;

	public:
		ActionTable();
		virtual ~ActionTable();

		void		read();
		string*		getAnimation(	char _cAnimCond,
									char _cAction,
									string* _pszActionDesc);
		bool		addAnimation(	char _cAnimCond,
									char _cAction,
									string* _pszAnimFileName,
									string* _pszActionDesc = nullptr);

		bool		loadFromFileJSON(string& _filename);

	};

} // namespace crea

#endif
