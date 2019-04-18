#include "stdafx.h"
#include "AI\Steering\Behavior.h"
#include "AI\Steering\Steering.h"
#include "Core\Entity.h"
#include "Physics\Collider.h"

namespace crea
{
	int Swarming::global_counter = 0;

	Behavior::Behavior(Entity* _pEntity)
		: m_pEntity(_pEntity), m_vDesiredVelocity(), m_vSteering(), m_vOffset()
	{
		m_pSteering = m_pEntity->getComponent<Steering>();
		m_pVehicle = m_pEntity->getComponent<Vehicle>();
	};

	Vector2f& Seek::Update()
	{
		m_pSteering->setTarget(m_target);
		m_pSteering->setTargetOffset(Vector2f(0.f, 0.f));

		m_vDesiredVelocity = m_target->getPosition() - m_pEntity->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pVehicle->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pVehicle->getVelocity();
		return m_vSteering;
	}

	Vector2f& Flee::Update()
	{
		m_pSteering->setTarget(m_target);
		m_pSteering->setTargetOffset(Vector2f(0.f, 0.f));

		m_vDesiredVelocity = m_pEntity->getPosition() - m_target->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pVehicle->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pVehicle->getVelocity();
		return m_vSteering;
	}

	Vector2f& Pursuit::Update()
	{
		Vector2f posToTarget = m_pEntity->getPosition() - m_target->getPosition();
		float v = m_pVehicle->getVelocity().length();
		float t = m_fTimeMax;
		if (v != 0.f)
		{
			t = min(m_fTimeMax, posToTarget.length() / v);
		}

		m_pSteering->setTarget(m_target);
		m_pSteering->setTargetOffset(m_target->getVelocity() * t);

		m_vDesiredVelocity = (m_target->getPosition() + m_target->getVelocity() * t) - m_pEntity->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pVehicle->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pVehicle->getVelocity();
		return m_vSteering;
	}

	Vector2f& Evasion::Update()
	{
		Vector2f posToTarget = m_pEntity->getPosition() - m_target->getPosition();
		float v = m_pVehicle->getVelocity().length();
		float t = m_fTimeMax;
		if (v != 0.f)
		{
			t = min(m_fTimeMax, posToTarget.length() / v);
		}

		m_pSteering->setTarget(m_target);
		m_pSteering->setTargetOffset(m_target->getVelocity() * t);

		m_vDesiredVelocity = m_pEntity->getPosition() - (m_target->getPosition() + m_target->getVelocity() * t);
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pVehicle->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pVehicle->getVelocity();
		return m_vSteering;
	}

	Vector2f& Arrival::Update()
	{
		m_pSteering->setTarget(m_target);
		m_pSteering->setTargetOffset(Vector2f(0.f, 0.f));

		m_vDesiredVelocity = m_target->getPosition() - m_pEntity->getPosition();
		float distance = m_vDesiredVelocity.length();
		float rampedSpeed = m_pVehicle->getMaxSpeed() * (distance / m_fSlowingDistance);
		float clippedSpeed = min(rampedSpeed, m_pVehicle->getMaxSpeed());
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= clippedSpeed;
		m_vSteering = m_vDesiredVelocity - m_pVehicle->getVelocity();
		return m_vSteering;
	}

	Vector2f& Wander::Update()
	{
		Vector2f direction = m_pVehicle->getVelocity();
		direction.normalize();

		Vector2f center = direction * m_radius;

		float value = (float)(rand() % 360);
		Vector2f r(sin(value*PI / 180.0f) * m_littleRadius, cos(value*PI / 180.0f) * m_littleRadius);
		m_vR += r;
		m_vR.normalize();
		m_vR *= m_radius;
		m_vSteering = center + m_vR;

		return m_vSteering;
	}

	PathFollowing::PathFollowing(
		Entity* _Entity,
		Entity* _Target,
		float _fSpeed,
		VectorVector2f* _vPath)
		: Behavior(_Entity), m_pTarget(_Target), m_fSpeed(_fSpeed), m_vPath(_vPath)
	{
		m_fDistanceToP1 = 0.f;
		m_iIndexNext = 0;
		m_fDistanceFromP0 = 0.0f;
		m_fDistanceToP1 = 0.f;
		m_fDistanceP0P1 = 0.f;
		p0 = p1 = nullptr;
	}

	Vector2f& PathFollowing::Update()
	{
		m_fDistanceFromP0 += m_fSpeed * (float)TimeManager::getSingleton()->getFrameTime().asSeconds();

		while (m_fDistanceFromP0 > m_fDistanceP0P1)
		{
			m_iIndexNext++;
			if (m_iIndexNext == m_vPath->size())
			{
				// No more points, stay on last
				m_iIndexNext--;
				m_fDistanceFromP0 = m_fDistanceP0P1;
			}
			else
			{
				// next point
				m_fDistanceFromP0 -= m_fDistanceP0P1;

				p0 = m_vPath->at(m_iIndexNext - 1);
				p1 = m_vPath->at(m_iIndexNext);
				Vector2f p0p1 = *p0 - *p1;
				m_fDistanceP0P1 = p0p1.length();
			}
		}

		Vector2f targetPosition = MathTools::lerp(*p0, *p1, m_fDistanceFromP0 / m_fDistanceP0P1);
		m_pTarget->setPosition(targetPosition);

		// Seek on target
		m_vDesiredVelocity = targetPosition - m_pEntity->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pVehicle->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pVehicle->getVelocity();

		return m_vSteering;
	}

	Vector2f& UnalignedCollisionAvoidance::Update()
	{
		Vector2f nextPosition = m_pEntity->getFuturePosition(m_fFutureTime);
		Vector2f nextPosition2, diff;
		m_vSteering = Vector2f(0.f, 0.f);
		for (std::vector<Entity*>::iterator i = m_entities->begin(); i != m_entities->end(); i++)
		{
			if ((*i) != m_pEntity)
			{
				nextPosition2 = (*i)->getFuturePosition(m_fFutureTime);
				diff = nextPosition - nextPosition2;
				if (diff.length() < m_radius)
				{
					diff.normalize();
					m_vSteering += diff;
				}
			}
		}

		m_vSteering.normalize();
		m_vSteering *= m_pVehicle->getMaxSpeed();
		return m_vSteering;
	}

	Vector2f& ObstacleAvoidance::Update()
	{
		Vector2f position = m_pEntity->getPosition();
		Vector2f look = m_pVehicle->getVelocity();
		look.normalize();
		Vector2f right(look.getY(), -look.getX());

		float distance = INFINITY;
		float fleeDirection;

		MapStringCollider* pStaticColliders = PhysicsManager::getSingleton()->getStaticColliders();
		for (MapStringCollider::iterator it = pStaticColliders->begin(); it != pStaticColliders->end(); ++it)
		{
			Collider* pCollider = (Collider*)(it->second);
			EnumColliderType type = pCollider->getColliderType();
			if (type == Collider_Circle)
			{
				CircleCollider* pCircleCollider = (CircleCollider*)pCollider;
				Vector2f obstaclePosition = pCircleCollider->getWorldCenter();
				float fRadius = pCircleCollider->getRadius();

				Vector2f vPositionToObstacle = obstaclePosition - position;
				float r = vPositionToObstacle.dot(look);
				float s = vPositionToObstacle.dot(right);

				float speedPercent = m_pVehicle->getVelocity().length() / m_pVehicle->getMaxSpeed();

				if (r > 0										// Obstacle in front
					&& r - fRadius < m_farView * speedPercent	// Obstacle in farView 
					&& r + fRadius < distance					// Closest Obstacle
					&& s - fRadius < m_radius					// Obstacle in radius (left)
					&& s + fRadius > -m_radius)					// Obstacle in radius (right) 
				{
					distance = r - fRadius;
					fleeDirection = s;
				}
			}
		}

		if (distance == INFINITY)
		{
			m_vSteering = Vector2f(0.f, 0.f);
		}
		else
		{
			right *= m_pVehicle->getMaxForce();
			if (fleeDirection > 0)
			{
				m_vSteering = -right;
			}
			else
			{
				m_vSteering = right;
			}
		}
		return m_vSteering;
	}

	Vector2f& Separation::Update()
	{
		Vector2f direction;
		float distance;
		m_vSteering = Vector2f(0.f, 0.f);
		for (std::vector<Entity*>::iterator i = m_entities->begin(); i != m_entities->end(); i++)
		{
			if ((*i) != m_pEntity)
			{
				direction = m_pEntity->getPosition() - (*i)->getPosition();
				distance = direction.length();
				if (distance <= m_distanceMax && distance != 0.0f)
				{
					direction.normalize();
					m_vSteering += direction * 1 / distance;
				}
			}
		}
		m_vSteering.normalize();
		m_vSteering *= m_pVehicle->getMaxForce();
		return m_vSteering;
	}

	Vector2f& Cohesion::Update()
	{
		Vector2f direction, center = Vector2f(0.f, 0.f);
		float distance;
		int nbNeighbors = 0;
		for (std::vector<Entity*>::iterator i = m_entities->begin(); i != m_entities->end(); i++)
		{
			if ((*i) != m_pEntity)
			{
				direction = m_pEntity->getPosition() - (*i)->getPosition();
				distance = direction.length();
				if (distance <= m_distanceMax)
				{
					center += (*i)->getPosition();
					nbNeighbors++;
				}
			}
		}
		if (nbNeighbors)
		{
			center /= (float)nbNeighbors;
			m_vSteering = center - m_pEntity->getPosition();
		}

		return m_vSteering;
	}


	Vector2f& Alignment::Update()
	{
		Vector2f direction;
		float distance;
		int nbNeighbors = 0;
		m_vDesiredVelocity = Vector2f(0.f, 0.f);
		for (std::vector<Entity*>::iterator i = m_entities->begin(); i != m_entities->end(); i++)
		{
			if ((*i) != m_pEntity)
			{
				direction = m_pEntity->getPosition() - (*i)->getPosition();
				distance = direction.length();
				if (distance <= m_distanceMax)
				{
					m_vDesiredVelocity += (*i)->getComponent<Vehicle>()->getVelocity();
					nbNeighbors++;
				}
			}
		}
		if (nbNeighbors)
		{
			m_vDesiredVelocity /= (float)nbNeighbors;
			m_vSteering = m_vDesiredVelocity - m_pVehicle->getVelocity();
		}

		return m_vSteering;
	}

	Vector2f& LeadFollowing::Update()
	{
		return m_vSteering;
	}

	Vector2f& Swarming::Update()
	{

		return m_vSteering;
	}

	Vector2f& FormationV::Update()
	{
		Vector2f forward(1.0f, 0.0f);
		Vector2f right(0.0f, 1.0f);
		if (m_bUseLeaderOrientation)
		{
			forward = m_leader->getOrientation();
			bool bCanNormalize = forward.normalize();
			right = Vector2f(forward.getY(), -forward.getX());
		}

		// For V shapes, add 1 unit per line to have an odd number 
		if (m_angle != 0.f && m_nbInLine % 2 == 0)
		{
			m_nbInLine++;
		}

		// Use minimum between nbInLine and max units
		if (m_nbInLine > m_maxId)
		{
			m_nbInLine = m_maxId;
		}

		int id = m_bLeaderInvisible ? m_id + 1 : m_id;
		int idInLine = id % m_nbInLine;
		int leftOrRight = (idInLine % 2) ? -1 : 1;
		int idRight = leftOrRight * ((idInLine + 1) / 2);
		int idBack = id / m_nbInLine;
		float fX = idRight * m_distanceMax;
		float fY = abs(fX) * (float)tan(m_angle) + idBack * m_distanceMax; // Fleche + recul
		Vector2f arrivalOffset = right * fX - forward * fY;
		Vector2f arrivalPos = m_leader->getPosition() + arrivalOffset;

		//Arrival
		Vector2f target_offset = arrivalPos - m_pEntity->getPosition();
		float distance = target_offset.length();
		float max_speed = m_pVehicle->getMaxSpeed();
		float ramped_speed = max_speed * (distance / m_slowingDistance);
		float clipped_speed = (ramped_speed < max_speed) ? ramped_speed : max_speed;
		Vector2f desired_velocity = target_offset * (clipped_speed / distance);
		m_vSteering = desired_velocity - m_pEntity->getVelocity();

		return m_vSteering;
	}

	Vector2f& FormationCircle::Update()
	{
		Vector2f forward(1.0f, 0.0f);
		Vector2f right(0.0f, 1.0f);
		if (m_bUseLeaderOrientation)
		{
			forward = m_leader->getOrientation();
			forward.normalize();
			right = Vector2f(forward.getY(), -forward.getX());
		}

		int idInCircle = m_id % m_nbInCircle;
		int iCircle = m_id / m_nbInCircle;
		int idMax = (m_maxAngle - m_minAngle) == 360.0f ? m_nbInCircle : m_nbInCircle - 1;
		float angle = MathTools::lerp(MathTools::degreetoradian(m_minAngle), MathTools::degreetoradian(m_maxAngle), ((float)(idInCircle) / (float)(idMax)));
		float distanceToLeader = m_minRadius + iCircle * m_distanceMax;
		float fX = sin(angle) * distanceToLeader;
		float fY = cos(angle) * distanceToLeader;
		Vector2f arrivalOffset = right * fX + forward * fY;
		Vector2f arrivalPos = m_leader->getPosition() + arrivalOffset;

		//Arrival
		Vector2f target_offset = arrivalPos - m_pEntity->getPosition();
		float distance = target_offset.length();
		float max_speed = m_pVehicle->getMaxSpeed();
		float ramped_speed = max_speed * (distance / m_slowingDistance);
		float clipped_speed = (ramped_speed < max_speed) ? ramped_speed : max_speed;
		Vector2f desired_velocity = target_offset * (clipped_speed / distance);
		m_vSteering = desired_velocity - m_pEntity->getVelocity();

		return m_vSteering;
	}

}