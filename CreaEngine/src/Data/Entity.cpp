#include "stdafx.h"

#include "Data\Entity.h"
#include "Core\Component.h"

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
		m_pComponents.push_back(_pComponent);
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
		// Components
		unsigned int uiSize = m_pComponents.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			delete m_pChildren[i];
		}
		m_pChildren.clear();

		// Children
		uiSize = m_pChildren.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			delete m_pComponents[i];
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
				m_pChildren[i]->getEntity(_szName);
			}
		}
		return nullptr;
	}
} // namespace crea