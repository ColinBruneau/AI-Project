/***************************************************/
/* Nom:	SceneManager.h
/* Description: SceneManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __SceneManager_H_
#define __SceneManager_H_

namespace crea
{
	class GameState;

	class CREAENGINE_API SceneManager
	{
		SceneManager();

	protected: 
		GameState* m_pCurrentGameState;

	public:
		virtual ~SceneManager();

		static SceneManager* getSingleton();

		bool update();

		bool draw();

		void setGameState(GameState* s);
	};

} // namespace crea

#endif
