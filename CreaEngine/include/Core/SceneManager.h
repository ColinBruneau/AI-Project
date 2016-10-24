/***************************************************/
/* Nom:	SceneManager.h
/* Description: SceneManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __SceneManager_H_
#define __SceneManager_H_

namespace crea
{
	class State;

	class CREAENGINE_API SceneManager
	{
		SceneManager();

	protected: 
		State* m_pCurrentState;

	public:
		virtual ~SceneManager();

		static SceneManager* getSingleton();

		bool update();

		bool draw();

		void setState(State* s);
	};

} // namespace crea

#endif
