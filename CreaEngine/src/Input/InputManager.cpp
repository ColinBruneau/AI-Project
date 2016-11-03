#include "stdafx.h"

#include "Input\InputManager.h"

namespace crea
{
	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	InputManager* InputManager::getSingleton()
	{
		static InputManager instanceUnique;
		return
			&instanceUnique;
	}

	bool InputManager::update()
	{
		return true;
	}

	bool InputManager::isKeyPressed(Key _key)
	{
		return IFacade::get().isKeyPressed(_key);
	}
} // namespace crea
