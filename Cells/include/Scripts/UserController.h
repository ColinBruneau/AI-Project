/***************************************************/
/* Nom:	UserController.h
/* Description: UserController
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __UserController_H_
#define __UserController_H_

#include "Core\Script.h"
#include "Core\Math.h"

namespace crea
{
	class CharacterController;

	class UserController : public Script
	{
		GameManager* m_pGM;
		CharacterController* m_pCharacterController;

		Vector2f m_vVelocity;

	public:
		UserController();
		virtual ~UserController();

		inline void setCharacterController(CharacterController* _pCharacterController);

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();
	};

} // namespace crea

#endif
