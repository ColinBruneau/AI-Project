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

		Map* m_pCurrentMap; // Physics materials

		PhysicsManager();

	public:
		virtual ~PhysicsManager();

		static PhysicsManager* getSingleton();

		void addCollider(Collider* _pCollider);

		bool isColliding(Collider* _pCollider);

		void setCurrentMap(Map* _pMap);

		Map* getCurrentMap();

		bool init();
			
		bool draw();

		void clear();
	};

} // namespace crea

#endif
