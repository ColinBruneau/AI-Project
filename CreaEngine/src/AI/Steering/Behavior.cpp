#include "stdafx.h"
#include "AI\Steering\Behavior.h"
#include "AI\Steering\Steering.h"
#include "Data\Entity.h"
#include "Physics\Collider.h"

namespace crea
{

	Behavior::Behavior(Entity* _pEntity)
		: m_pEntity(_pEntity), m_vDesiredVelocity(), m_vSteering(), m_vOffset()
	{
		m_pSteering = m_pEntity->getComponent<Steering>();
	};

	Vector2f& Seek::Update()
	{
		m_vDesiredVelocity = m_target->getPosition() - m_pEntity->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pSteering->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
		return m_vSteering;
	}

	Vector2f& Flee::Update()
	{
		m_vDesiredVelocity = m_pEntity->getPosition() - m_target->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pSteering->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
		return m_vSteering;
	}

	Vector2f& Pursuit::Update()
	{
		m_vDesiredVelocity = (m_target->getPosition() + m_target->getComponent<Steering>()->getVelocity() * m_fC) - m_pEntity->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pSteering->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
		return m_vSteering;
	}

	Vector2f& Evasion::Update()
	{
		m_vDesiredVelocity = m_pEntity->getPosition() - (m_target->getPosition() + m_target->getComponent<Steering>()->getVelocity() * m_fC);
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pSteering->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
		return m_vSteering;
	}

	Vector2f& Arrival::Update()
	{
		float velocitylength = m_pSteering->getVelocity().length();
		float slowingDistance = velocitylength * velocitylength / (m_pSteering->getMaxForce() / m_pSteering->getMass());

		Vector2f targetOffset = m_target->getPosition() - m_pEntity->getPosition();
		float distance = targetOffset.length();
		float rampedSpeed = m_pSteering->getMaxSpeed() * (distance / slowingDistance);
		float clippedSpeed = min(rampedSpeed, m_pSteering->getMaxSpeed());
		m_vDesiredVelocity = targetOffset * (clippedSpeed / distance);
		m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
		return m_vSteering;
	}

	Vector2f& Wander::Update()
	{
		Vector2f direction = m_pSteering->getVelocity();
		direction.normalize();

		Vector2f center = direction * (m_pSteering->getMaxForce() - m_radius);

		float value = (float)(rand() % 360);
		Vector2f r(sin(value*PI / 180.0f) * m_littleRadius, cos(value*PI / 180.0f) * m_littleRadius);
		Vector2f R = m_pSteering->getLastR();
		R += r;
		R.normalize();
		R *= m_radius;
		m_vSteering = center + R;
		m_pSteering->setLastR(R);

		return m_vSteering;
	}

	Vector2f& PathFollowing::Update()
	{
		Vector2f position = m_pEntity->getPosition() + m_pSteering->getVelocity() * m_fC;
		float distMin = INFINITY;
		std::vector<Entity*>::iterator j;

		// if no target yet
		if (m_pSteering->getTarget() == NULL)
		{
			// Compute closest waypoints
			for (std::vector<Entity*>::iterator i = m_obstacles->begin(); i != m_obstacles->end(); i++)
			{
				Vector2f obstaclePosition = (*i)->getPosition();
				float dist = (position - obstaclePosition).length();

				if (dist < distMin) {
					distMin = dist;
					// take next as target (if one exist)
					j = i;
					j++;
					if (j != m_obstacles->end())
						m_pSteering->setTarget(*j);
					else
						m_pSteering->setTarget(*i);
				}
			}
		}

		float fTargetRadius = m_pSteering->getTarget()->getComponent<CircleCollider>()->getRadius();
		
		if ((m_pSteering->getTarget()->getPosition() - m_pEntity->getPosition()).length() < fTargetRadius)
		{
			// Find next waypoint
			for (std::vector<Entity*>::iterator i = m_obstacles->begin(); i != m_obstacles->end(); i++)
			{
				if (*i == m_pSteering->getTarget())
				{
					// take next as target (if one exist)
					j = i;
					j++;
					if (j != m_obstacles->end())
						m_pSteering->setTarget(*j);
					else
						m_pSteering->setTarget(*i);
					break;
				}
			}
		}

		// Seek on target
		m_vDesiredVelocity = m_pSteering->getTarget()->getPosition() - m_pEntity->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pSteering->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();

		return m_vSteering;
	}

	Vector2f& UnalignedCollisionAvoidance::Update()
	{
		Vector2f nextPosition = m_pEntity->getPosition() + m_pSteering->getVelocity() / 2.0f;
		Vector2f nextPosition2, diff;
		m_vSteering = Vector2f(0.f, 0.f);
		for (std::vector<Entity*>::iterator i = m_entities->begin(); i != m_entities->end(); i++)
		{
			if ((*i) != m_pEntity)
			{
				nextPosition2 = (*i)->getPosition() + (*i)->getComponent<Steering>()->getVelocity() / 2.0f;
				diff = nextPosition - nextPosition2;
				if (diff.length() < m_radius)
				{
					m_vSteering += diff;
				}
			}
		}
		return m_vSteering;
	}

	Vector2f& ObstacleAvoidance::Update()
	{
		Vector2f position = m_pEntity->getPosition();
		Vector2f direction = m_pSteering->getVelocity();
		direction.normalize();
		direction += position;

		float distance = INFINITY;
		float fleeDirection;

		for (std::vector<Entity*>::iterator i = m_obstacles->begin(); i != m_obstacles->end(); i++)
		{
			Vector2f obstaclePosition = (*i)->getPosition();
			float fRadius = (*i)->getComponent<CircleCollider>()->getRadius();

			float r = (position.getY() - obstaclePosition.getY()) * (position.getY() - direction.getY()) - (position.getX() - obstaclePosition.getX()) * (direction.getX() - position.getX());
			float s = (position.getY() - obstaclePosition.getY()) * (direction.getX() - position.getX()) - (position.getX() - obstaclePosition.getX()) * (direction.getY() - position.getY());

			if (r > 0
				&& r - fRadius < m_farView * m_pSteering->getVelocity().length() / m_pSteering->getMaxSpeed()
				&& r + fRadius < distance
				&& s < (m_radius + fRadius)
				&& s > -(m_radius + fRadius)) {
				distance = r - fRadius;
				fleeDirection = s;
			}
		}
		if (distance == INFINITY)
		{
			m_vSteering = Vector2f(0.f, 0.f);
		}
		else
		{
			direction = m_pSteering->getVelocity();
			direction.normalize();
			direction *= m_pSteering->getMaxForce();
			if (fleeDirection > 0)
			{
				m_vSteering = Vector2f(-direction.getY(), direction.getX());
			}
			else
			{
				m_vSteering = Vector2f(direction.getY(), -direction.getX());
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
		m_vSteering *= m_pSteering->getMaxForce();
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
			center /= (float) nbNeighbors;
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
					m_vDesiredVelocity += (*i)->getComponent<Steering>()->getVelocity();
					nbNeighbors++;
				}
			}
		}
		if (nbNeighbors)
		{
			m_vDesiredVelocity /= (float) nbNeighbors;
			m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
		}

		return m_vSteering;
	}

	Vector2f& LeadFollowing::Update()
	{
		Vector2f EntityPosition = m_pEntity->getPosition();
		Vector2f EntityToLeader = EntityPosition - m_leader->getPosition();
		Vector2f leadDirection = m_leader->getComponent<Steering>()->getVelocity();
		leadDirection.normalize();

		float ang = leadDirection.angle(EntityToLeader);
		if (ang < m_angle && EntityToLeader.length() < m_distance)
		{
			// Flee in front of leader
			Vector2f frontOfLeader = (m_leader->getPosition() + leadDirection * m_distanceFlee);
			m_vDesiredVelocity = EntityPosition - frontOfLeader;
			m_vDesiredVelocity.normalize();
			m_vDesiredVelocity *= m_pSteering->getMaxSpeed();
			m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();

		}
		else
		{
			// Arrive behind leader
			Vector2f backOfLeader = (m_leader->getPosition() - leadDirection * m_distanceArrive);
			float velocitylength = m_pSteering->getVelocity().length();
			float slowingDistance = velocitylength * velocitylength / (m_pSteering->getMaxForce() / m_pSteering->getMass());
			Vector2f targetOffset = backOfLeader - m_pEntity->getPosition();
			float distance = targetOffset.length();
			float rampedSpeed = m_pSteering->getMaxSpeed() * (distance / slowingDistance);
			float clippedSpeed = min(rampedSpeed, m_pSteering->getMaxSpeed());
			m_vDesiredVelocity = targetOffset * (clippedSpeed / distance);
			m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
			m_vSteering.normalize();
			m_vSteering *= m_pSteering->getMaxForce();
		}

		return m_vSteering;
	}

}