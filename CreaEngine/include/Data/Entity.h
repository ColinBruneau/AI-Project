/***************************************************/
/* Nom:	Entity.h
/* Description: Entity
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Entity_H_
#define __Entity_H_

#include "Graphics\Transformable.h"
#include <vector>

namespace crea
{
	class Component;

	class CREAENGINE_API Entity : public Transformable // Every entity is transformable
	{
		// Name
		string m_szName;

		// Composite
		Entity* m_pParent;
		vector<Entity*> m_pChildren;

		// Composition
		vector<Component*> m_pComponents;

	public:
		Entity();
		virtual ~Entity();
		
		inline bool hasName(string& _szName) { return (m_szName == _szName); }

		inline void setName(string& _szName) { m_szName = _szName; }

		inline void setParent(Entity* _pEntity) { m_pParent = _pEntity; }

		Entity* getEntity(string& _szName);

		bool loadFromFileJSON(string& _filename);

		void addChild(Entity* _pEntity);

		void addComponent(Component* _pComponent);

		void removeComponent(Component* _pComponent);

		template<class T> T* getComponent();

		bool init();

		bool update();

		bool draw();

		void clear();
	};

	template<class T> T* Entity::getComponent()
	{
		unsigned int uiSize = m_pComponents.size();
		for (unsigned int i = 0; i < uiSize; i++)
		{
			Component* pComponent = m_pComponents[i];
			T* ptr = dynamic_cast<T*>(pComponent);
			if (ptr != nullptr)
			{
				return ptr;
			}
			else
			{
				// Children
				unsigned int uiSize = m_pChildren.size();
				for (unsigned int i = 0; i < uiSize; i++)
				{
					m_pChildren[i]->getComponent<T>();
				}
			}
		}
		return nullptr;
	}

} // namespace crea

#endif
