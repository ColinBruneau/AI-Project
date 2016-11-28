/***************************************************/
/* Nom:	UserController.h
/* Description: UserController
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __UserController_H_
#define __UserController_H_

#include "Core\Component.h"
#include "Core\ICore.h"

namespace crea
{
	class CharacterController;

	class CREAENGINE_API UserController : public Component
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

	class CREAENGINE_API KeyboardUserController : public UserController
	{

	public:
		KeyboardUserController();
		virtual ~KeyboardUserController();

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();
	};

} // namespace crea

#endif
