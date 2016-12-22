#include "stdafx.h"

#include "json\json.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Data\Entity.h"
#include "Core\Component.h"
#include "Physics\Collider.h"
#include "Input\UserController.h"

namespace crea
{
	Entity::Entity()
	{
		m_pParent = nullptr;
		m_szName = "Entity";
	}

	Entity::~Entity()
	{
		clear();
	}

	void Entity::addChild(Entity* _pEntity)
	{
		m_pChildren.push_back(_pEntity);
		_pEntity->setParent(this);
	}

	void Entity::addComponent(Component* _pComponent)
	{
		_pComponent->setEntity(this);
		m_pComponents.push_back(_pComponent);
	}

	void Entity::removeComponent(Component* _pComponent)
	{
		_pComponent->setEntity(nullptr);
		std::remove(m_pComponents.begin(), m_pComponents.end(), _pComponent), m_pComponents.end();
	}

	bool Entity::init()
	{
		// Components
		unsigned int uiSize = m_pComponents.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			m_pComponents[i]->init();
		}

		// Children
		uiSize = m_pChildren.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			m_pChildren[i]->init();
		}

		return true;
	}

	bool Entity::update()
	{
		// Components
		unsigned int uiSize = m_pComponents.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			m_pComponents[i]->update();
		}

		// Children
		uiSize = m_pChildren.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			m_pChildren[i]->update();
		}

		return true;
	}

	bool Entity::draw()
	{
		// Components
		unsigned int uiSize = m_pComponents.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			m_pComponents[i]->draw();
		}

		// Children
		uiSize = m_pChildren.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			m_pChildren[i]->draw();
		}

		return true;
	}

	void Entity::clear()
	{
		// Children
		unsigned int uiSize = m_pChildren.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			delete m_pChildren[i];
		}
		m_pChildren.clear();

		// Components
		uiSize = m_pComponents.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			//delete m_pComponents[i]; // CB: the components are destroyed by managers...
		}
		m_pComponents.clear();
	}

	Entity* Entity::getEntity(string& _szName)
	{
		if (hasName(_szName))
		{
			return this;
		}
		else
		{
			// Children
			unsigned int uiSize = m_pChildren.size();
			for (unsigned int i = 0; i < uiSize; i++)
			{
				Entity* pEntity = m_pChildren[i]->getEntity(_szName);
				if (pEntity)
				{
					return pEntity;
				}
			}
		}
		return nullptr;

	}

	bool Entity::loadFromFileJSON(string& _filename)
	{
		Json::Value root;
		std::ifstream entityStream(_filename, std::ifstream::binary);
		if (entityStream.fail())
		{
			cerr << "Can't open Entity file: " << _filename << endl;
			return false;
		}

		// Parse file
		entityStream >> root;

		crea::GameManager*	pGM = crea::GameManager::getSingleton();

		// Components
		Json::Value components = root["components"];
		for (unsigned int iComponent = 0; iComponent < components.size(); ++iComponent)
		{
			Json::Value component = components[iComponent];

			string szType = component["type"].asString();
			if (szType == "SpriteRenderer")
			{
				string szName = component["name"].asString();
				SpriteRenderer* pSpriteRenderer = pGM->getSpriteRenderer(szName);

				string szSprite = component["sprite"].asString();
				ISprite* pSprite = pGM->getSprite(szSprite);

				pSpriteRenderer->setSprite(pSprite);
				addComponent(pSpriteRenderer);
			}
			else if (szType == "Animator")
			{
				string szName = component["name"].asString();
				Animator* pAnimator = pGM->getAnimator(szName);

				string szSprite = component["sprite"].asString();
				ISprite* pSprite = pGM->getSprite(szSprite);

				pAnimator->setSprite(pSprite);
				addComponent(pAnimator);
			}
			else if (szType == "Collider")
			{
				string szName = component["name"].asString();
				Collider* pCollider = pGM->getCollider(szName);
				addComponent(pCollider);
			}
			else if (szType == "CharacterController")
			{
				string szName = component["name"].asString();
				CharacterController* pCharacterController = pGM->getCharacterController(szName);

				string szAnimator = component["animator"].asString();
				Animator* pAnimator = pGM->getAnimator(szAnimator);
				pCharacterController->setAnimator(pAnimator);

				string szActionTable = component["actiontable"].asString();
				ActionTable* pActionTable = pGM->getActionTable(szActionTable);
				pCharacterController->setActionTable(pActionTable);

				string szCollider = component["collider"].asString();
				Collider* pCollider = pGM->getCollider(szCollider);
				pCharacterController->setCollider(pCollider);

				addComponent(pCharacterController);
			}
			else if (szType == "UserController")
			{
				string szName = component["name"].asString();
				UserController* pUserController = pGM->getUserController(szName);

				string szCharacterController = component["charactercontroller"].asString();
				CharacterController* pCharacterController = pGM->getCharacterController(szCharacterController);
				pUserController->setCharacterController(pCharacterController);

				addComponent(pUserController);
			}
			else if (szType == "Agent")
			{
				string szName = component["name"].asString();
				Agent* pAgent = pGM->getAgent(szName);

				addComponent(pAgent);
			}

		}
		return true;
	}

} // namespace crea
