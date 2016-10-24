/***************************************************/
/* Nom:	InputManager.h
/* Description: InputManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __InputMANAGER_H_
#define __InputMANAGER_H_

namespace crea
{

	class CREAENGINE_API InputManager
	{
		InputManager();

	public:
		virtual ~InputManager();

		static InputManager* getSingleton();

		bool update();

		bool isKeyPressed(char _key);
	};

} // namespace crea

#endif
