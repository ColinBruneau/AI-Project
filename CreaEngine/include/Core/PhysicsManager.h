/***************************************************/
/* Nom:	PhysicsManager.h
/* Description: PhysicsManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __PhysicsManager_H_
#define __PhysicsManager_H_

namespace crea
{
	class Collider;

	class CREAENGINE_API VectorCollider : public vector<Collider*> {};

	class CREAENGINE_API PhysicsManager
	{
		VectorCollider m_Colliders;

		PhysicsManager();

	public:
		virtual ~PhysicsManager();

		static PhysicsManager* getSingleton();

		void addCollider(Collider* _pCollider);

		bool isColliding(Collider* _pCollider);

		bool draw();

		void clear();
	};

} // namespace crea

#endif
