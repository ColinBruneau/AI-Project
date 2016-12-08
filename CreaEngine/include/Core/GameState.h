/***************************************************/
/* Nom:	GameState.h
/* Description: GameState
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __GameState_H_
#define __GameState_H_

namespace crea
{

	class CREAENGINE_API GameState
	{

	public:
		GameState();
		virtual ~GameState();

		virtual bool onInit() = 0;
		virtual bool onUpdate() = 0;
		virtual bool onDraw() = 0;
		virtual bool onQuit() = 0;

	};

} // namespace crea

#endif
