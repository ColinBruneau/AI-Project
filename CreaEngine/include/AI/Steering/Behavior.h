/***************************************************/
/* Nom:	Behavior.h
/* Description: Behavior
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __BEHAVIOR_H_
#define __BEHAVIOR_H_

#include "Core\Math.h"
#include <vector>
#include <random>

namespace crea
{
	class Entity;

	class CREAENGINE_API Behavior
	{
	protected:
		Entity* m_pEntity;
		Steering* m_pSteering; // CB: change this for RigidBody
		Vector2f m_vDesiredVelocity;
		Vector2f m_vSteering;
		Vector2f m_vOffset;
	public:
		Behavior(Entity* _Entity);
		virtual ~Behavior() {}
		void setOffset(Vector2f& _offset) { m_vOffset = _offset; };
		Entity* getEntity() { return m_pEntity; }
		virtual Vector2f& Update() = 0;
	};

	class CREAENGINE_API Seek : public Behavior
	{
		Entity* m_target;
	public:
		Seek(Entity* _Entity, Entity* _target) : Behavior(_Entity), m_target(_target) { };
		Entity* getTarget() { return m_target; }
		Vector2f& Update();
	};

	class CREAENGINE_API Flee : public Behavior
	{
		Entity* m_target;
	public:
		Flee(Entity* _Entity, Entity* _target) : Behavior(_Entity), m_target(_target) { };
		Entity* getTarget() { return m_target; }
		Vector2f& Update();
	};

	class CREAENGINE_API Pursuit : public Behavior
	{
		Entity* m_target;
		float m_fC;
	public:
		Pursuit(Entity* _Entity, Entity* _target, float _fC) : Behavior(_Entity), m_target(_target), m_fC(_fC) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Evasion : public Behavior
	{
		Entity* m_target;
		float m_fC;
	public:
		Evasion(Entity* _Entity, Entity* _target, float _fC) : Behavior(_Entity), m_target(_target), m_fC(_fC) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Arrival : public Behavior
	{
		Entity* m_target;
		float m_fSlowingDistance;
	public:
		Arrival(Entity* _Entity, Entity* _target, float _fSlowingDistance) : Behavior(_Entity), m_target(_target), m_fSlowingDistance(_fSlowingDistance) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Wander : public Behavior
	{
		float m_distance;
		float m_radius;
		float m_littleRadius;
	public:
		Wander(Entity* _Entity, float _distance, float _radius, float _littleRadius)
			: Behavior(_Entity), m_distance(_distance), m_radius(_radius), m_littleRadius(_littleRadius) { };
		Vector2f& Update();
	};

	class CREAENGINE_API PathFollowing : public Behavior
	{
		float m_fC;
		float m_radius;
		float m_farView;
		vector<Entity*>* m_obstacles;
	public:
		PathFollowing(Entity* _Entity, float _fC, float _fRadius, float _fFarView, std::vector<Entity*>* obstacles)
			: Behavior(_Entity), m_fC(_fC), m_radius(_fRadius), m_farView(_fFarView), m_obstacles(obstacles) { };
		Vector2f& Update();
	};

	class CREAENGINE_API UnalignedCollisionAvoidance : public Behavior
	{
		float m_radius;
		vector<Entity*>* m_entities;
	public:
		UnalignedCollisionAvoidance(Entity* _Entity, float radius, std::vector<Entity*>* entities)
			: Behavior(_Entity), m_radius(radius), m_entities(entities) { };
		Vector2f& Update();
	};

	class CREAENGINE_API ObstacleAvoidance : public Behavior
	{
		float m_radius;
		float m_farView;
		vector<Entity*>* m_obstacles;
	public:
		ObstacleAvoidance(Entity* _Entity, float radius, float farView, std::vector<Entity*>* obstacles)
			: Behavior(_Entity), m_radius(radius), m_farView(farView), m_obstacles(obstacles) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Separation : public Behavior
	{
		float m_distanceMax;
		vector<Entity*>* m_entities;
	public:
		Separation(Entity* _Entity, float distanceMax, std::vector<Entity*>* entities)
			: Behavior(_Entity), m_distanceMax(distanceMax), m_entities(entities) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Cohesion : public Behavior
	{
		float m_distanceMax;
		vector<Entity*>* m_entities;
	public:
		Cohesion(Entity* _Entity, float distanceMax, std::vector<Entity*>* entities)
			: Behavior(_Entity), m_distanceMax(distanceMax), m_entities(entities) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Alignment : public Behavior
	{
		float m_distanceMax;
		vector<Entity*>* m_entities;
	public:
		Alignment(Entity* _Entity, float distanceMax, std::vector<Entity*>* entities)
			: Behavior(_Entity), m_distanceMax(distanceMax), m_entities(entities) { };
		Vector2f& Update();
	};

	class CREAENGINE_API LeadFollowing : public Behavior
	{
		Entity* m_leader;
		float m_distance;
		float m_angle;
		float m_distanceFlee;
		float m_distanceArrive;
	public:
		LeadFollowing(Entity* _Entity, Entity* _leader, float _distance, float _angle, float _distanceFlee, float _distanceArrive)
			: Behavior(_Entity), m_leader(_leader), m_distance(_distance), m_angle(_angle), m_distanceFlee(_distanceFlee), m_distanceArrive(_distanceArrive) { };
		Vector2f& Update();
	};

	class CREAENGINE_API Swarming : public Behavior
	{
		Entity* m_target;
		float m_fSwarmDistanceSquare;
		int m_iIndex;

		static int global_counter;
	
	public:
		Swarming(Entity* _entity, int _iIndex, Entity* _target, float _fSwarmDistance) 
			: Behavior(_entity), m_iIndex(_iIndex), m_target(_target), 
			m_fSwarmDistanceSquare(_fSwarmDistance*_fSwarmDistance) 
		{ 
			global_counter++;
		};
		Vector2f& Update();
	};

	class CREAENGINE_API FormationV : public Behavior
	{
		Entity* m_leader;
		bool m_bUseLeaderOrientation;
		unsigned int m_id, m_maxId, m_nbInLine;
		float m_distanceMax, m_slowingDistance;
		float m_angle;
		Vector2f m_vOldForward;

	public:
		FormationV(Entity* _entity, Entity* _leader, bool _bUseLeaderOrientation,
			unsigned int _nbInLine, unsigned int _id, unsigned int _maxId,
			float _distanceMax, float _slowingDistance,
			float _angle)
			: Behavior(_entity), m_leader(_leader), m_bUseLeaderOrientation(_bUseLeaderOrientation),
			m_nbInLine(_nbInLine), m_id(_id), m_maxId(_maxId),
			m_distanceMax(_distanceMax), m_slowingDistance(_slowingDistance),
			m_angle(_angle),
			m_vOldForward(1.0f, 0.0f)
		{};
		Vector2f& Update();
	};

	class CREAENGINE_API FormationCircle : public Behavior
	{
		Entity* m_leader;
		bool m_bUseLeaderOrientation;
		unsigned int m_id, m_maxId, m_nbInCircle;
		float m_distanceMax, m_slowingDistance;
		float m_minAngle, m_maxAngle, m_minRadius;

	public:
		FormationCircle(Entity* _entity, Entity* _leader, bool _bUseLeaderOrientation,
			unsigned int _nbInCircle, unsigned int _id, unsigned int _maxId,
			float _distanceMax, float _slowingDistance,
			float _minAngle, float _maxAngle, float _minRadius)
			: Behavior(_entity), m_leader(_leader), m_bUseLeaderOrientation(_bUseLeaderOrientation),
			m_nbInCircle(_nbInCircle), m_id(_id), m_maxId(_maxId),
			m_distanceMax(_distanceMax), m_slowingDistance(_slowingDistance),
			m_minAngle(_minAngle), m_maxAngle(_maxAngle), m_minRadius(_minRadius)
		{};
		Vector2f& Update();
	};

	class CREAENGINE_API FormationDynamic : public Behavior
	{
		Entity* m_leader;
		bool m_bUseLeaderOrientation;
		unsigned int m_id, m_maxId, m_nbInCircle;
		float m_distanceMax, m_slowingDistance;
		float m_minAngle, m_maxAngle, m_minRadius;

		float m_angleStart;

	public:
		FormationDynamic(Entity* _entity, Entity* _leader, bool _bUseLeaderOrientation,
			unsigned int _nbInCircle, unsigned int _id, unsigned int _maxId,
			float _distanceMax, float _slowingDistance,
			float _minAngle, float _maxAngle, float _minRadius)
			: Behavior(_entity), m_leader(_leader), m_bUseLeaderOrientation(_bUseLeaderOrientation),
			m_nbInCircle(_nbInCircle), m_id(_id), m_maxId(_maxId),
			m_distanceMax(_distanceMax), m_slowingDistance(_slowingDistance),
			m_minAngle(_minAngle), m_maxAngle(_maxAngle), m_minRadius(_minRadius)
		{
			m_angleStart = 0.0f;
		};
		Vector2f& Update();
	};
}

#endif