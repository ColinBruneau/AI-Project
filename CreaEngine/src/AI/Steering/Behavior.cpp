#include "stdafx.h"
#include "AI\Steering\Behavior.h"
#include "AI\Steering\Steering.h"
#include "Data\Entity.h"
#include "Physics\Collider.h"

namespace crea
{
	int Swarming::global_counter = 0;

	Behavior::Behavior(Entity* _pEntity)
		: m_pEntity(_pEntity), m_vDesiredVelocity(), m_vSteering(), m_vOffset()
	{
		m_pSteering = m_pEntity->getComponent<Steering>();
	};

	Vector2f& Seek::Update()
	{
		m_pSteering->setTarget(m_target);
		m_pSteering->setTargetOffset(Vector2f(0.f, 0.f));

		m_vDesiredVelocity = m_target->getPosition() - m_pEntity->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pSteering->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
		return m_vSteering;
	}

	Vector2f& Flee::Update()
	{
		m_pSteering->setTarget(m_target);
		m_pSteering->setTargetOffset(Vector2f(0.f, 0.f));

		m_vDesiredVelocity = m_pEntity->getPosition() - m_target->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pSteering->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
		return m_vSteering;
	}

	Vector2f& Pursuit::Update()
	{
		m_pSteering->setTarget(m_target);
		m_pSteering->setTargetOffset(m_target->getVelocity() * m_fC);

		m_vDesiredVelocity = (m_target->getPosition() + m_target->getVelocity() * m_fC) - m_pEntity->getPosition();
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pSteering->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
		return m_vSteering;
	}

	Vector2f& Evasion::Update()
	{
		m_pSteering->setTarget(m_target);
		m_pSteering->setTargetOffset(m_target->getVelocity() * m_fC);

		m_vDesiredVelocity = m_pEntity->getPosition() - (m_target->getPosition() + m_target->getVelocity() * m_fC);
		m_vDesiredVelocity.normalize();
		m_vDesiredVelocity *= m_pSteering->getMaxSpeed();
		m_vSteering = m_vDesiredVelocity - m_pSteering->getVelocity();
		return m_vSteering;
	}

	Vector2f& Arrival::Update()
	{
		m_pSteering->setTarget(m_target);
		m_pSteering->setTargetOffset(Vector2f(0.f, 0.f));

		Vector2f targetOffset = m_target->getPosition() - m_pEntity->getPosition();
		float distance = targetOffset.length();
		float rampedSpeed = m_pSteering->getMaxSpeed() * (distance / m_fSlowingDistance);
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
		std::vector<Entity*>::iterator j;

		// if no target yet
		if (m_pSteering->getTarget() == NULL)
		{
			// Take first... (option 1)
			//m_pSteering->setTarget(*m_obstacles->begin());

			// Compute closest waypoints (option 2)
			float distMin = INFINITY;
			for (std::vector<Entity*>::iterator i = m_obstacles->begin(); i != m_obstacles->end(); i++)
			{
				Vector2f obstaclePosition = (*i)->getPosition();
				float dist = (position - obstaclePosition).length();

				if (dist < distMin) {
					distMin = dist;
					m_pSteering->setTarget(*i);
				}
			}
			
		}

		Collider* pCollider = m_pSteering->getTarget()->getComponent<Collider>();
		CircleCollider* pCircleCollider = (CircleCollider*)pCollider->getCollider();
		float fTargetRadius = pCircleCollider->getRadius();
		
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
			Collider* pCollider = (*i)->getComponent<Collider>();
			CircleCollider* pCircleCollider = (CircleCollider*)pCollider->getCollider();
			float fRadius = pCircleCollider->getRadius();

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

	Vector2f& Swarming::Update()
	{
		Vector2f velocity = m_pEntity->getVelocity();
		velocity.normalize();
		Vector2f velocityTangent(-velocity.getY(), velocity.getX());
		Vector2f vEntityToTarget = m_target->getPosition() - m_pEntity->getPosition();
		if (vEntityToTarget.lengthSq() > m_fSwarmDistanceSquare)
		{
			// Outer zone

			// Increase speed to maximum
			m_vSteering = velocity * m_pSteering->getMaxForce();

			float fAngle = vEntityToTarget.angle(velocity);
			if (fAngle < 0.1f)
			{
				// Vary the steering as a function of the index of the entity
				float fRandTurn = (global_counter - m_iIndex) * 0.01f;
				m_vSteering += velocityTangent * fRandTurn;
			}
			else
			{
				if (vEntityToTarget.isLeft(velocity))
				{
					m_vSteering = velocityTangent * -100.f;
				}
				else
				{
					m_vSteering = velocityTangent * 100.f;
				}
			}
		}
		else
		{
			// Inner zone

			if (vEntityToTarget.isLeft(velocity))
			{
				m_vSteering = velocityTangent * -100.f;
			}
			else
			{
				m_vSteering = velocityTangent * 100.f;
			}
		}
		return m_vSteering;
	}

	Vector2f& FormationV::Update()
	{
		Vector2f forward(1.0f, 0.0f);
		Vector2f right(0.0f, 1.0f);
		if (m_bUseLeaderOrientation)
		{
			forward = m_leader->getVelocity();
			bool bCanNormalize = forward.normalize();
			if (!bCanNormalize)
			{
				forward = m_vOldForward;
			}
			right = Vector2f(forward.getY(), -forward.getX());
			m_vOldForward = forward;
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

		int idRight = (m_id%m_nbInLine) - m_nbInLine / 2;
		int idBack = m_id / m_nbInLine;
		float fX = idRight * m_distanceMax;
		float fY = abs(fX) * (float)tan(m_angle) + idBack * m_distanceMax; // Fleche + recul
		Vector2f arrivalOffset = right * fX - forward * fY;
		Vector2f arrivalPos = m_leader->getPosition() + arrivalOffset;

		//Arrival
		Vector2f target_offset = arrivalPos - m_pEntity->getPosition();
		float distance = target_offset.length();
		float max_speed = m_pSteering->getMaxSpeed();
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
			forward = m_leader->getVelocity();
			forward.normalize();
			right = Vector2f(forward.getY(), -forward.getX());
		}

		int idInCircle = m_id%m_nbInCircle;
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
		float max_speed = m_pSteering->getMaxSpeed();
		float ramped_speed = max_speed * (distance / m_slowingDistance);
		float clipped_speed = (ramped_speed < max_speed) ? ramped_speed : max_speed;
		Vector2f desired_velocity = target_offset * (clipped_speed / distance);
		m_vSteering = desired_velocity - m_pEntity->getVelocity();

		return m_vSteering;
	}

	Vector2f& FormationDynamic::Update()
	{
		Vector2f forward(1.0f, 0.0f);
		Vector2f right(0.0f, 1.0f);
		if (m_bUseLeaderOrientation)
		{
			forward = m_leader->getVelocity();
			forward.normalize();
			right = Vector2f(forward.getY(), -forward.getX());
		}

		//Move slots
		m_angleStart += (float)TimeManager::getSingleton()->getFrameTime().asSeconds();

		//Circle
		int idInCircle = m_id%m_nbInCircle;
		int iCircle = m_id / m_nbInCircle;
		int idMax = (m_maxAngle - m_minAngle) == 360.0f ? m_nbInCircle : m_nbInCircle - 1;
		float angle = m_angleStart + MathTools::lerp(MathTools::degreetoradian(m_minAngle), MathTools::degreetoradian(m_maxAngle), ((float)(idInCircle) / (float)(idMax)));
		float distanceToLeader = m_minRadius + iCircle * m_distanceMax;
		float fX = sin(angle) * distanceToLeader;
		float fY = cos(angle) * distanceToLeader;
		Vector2f arrivalOffset = right * fX + forward * fY;
		Vector2f arrivalPos = m_leader->getPosition() + arrivalOffset;

		//Arrival
		Vector2f target_offset = arrivalPos - m_pEntity->getPosition();
		float distance = target_offset.length();
		float max_speed = m_pSteering->getMaxSpeed();
		float ramped_speed = max_speed * (distance / m_slowingDistance);
		float clipped_speed = (ramped_speed < max_speed) ? ramped_speed : max_speed;
		Vector2f desired_velocity = target_offset * (clipped_speed / distance);
		m_vSteering = desired_velocity - m_pEntity->getVelocity();

		return m_vSteering;
	}

}