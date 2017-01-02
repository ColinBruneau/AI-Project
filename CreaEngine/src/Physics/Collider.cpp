#include "stdafx.h"

#include "Physics\Collider.h"
#include "Graphics\ISprite.h"
#include "json\json.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace crea
{
	Collider::Collider(EnumColliderType _eColliderType)
	{
		m_pSprite = nullptr;
		m_bIsColliding = false;
		setType(_eColliderType);
	}

	Collider::~Collider()
	{
		delete m_pCollider;
	}

	void Collider::setType(EnumColliderType _eColliderType)
	{
		if (m_pCollider)
		{
			delete m_pCollider;
		}

		m_eColliderType = _eColliderType;

		if (m_eColliderType == Collider_Box)
		{
			m_pCollider = new BoxCollider;
			m_pSprite = crea::GameManager::getSingleton()->getSprite("debug/boxcollider");
			m_pSprite->setTexture(crea::GameManager::getSingleton()->getTexture("debug/boxcollider.png"));
		}
		else
		{
			m_pCollider = new CircleCollider;
			m_pSprite = crea::GameManager::getSingleton()->getSprite("debug/circlecollider");
			m_pSprite->setTexture(crea::GameManager::getSingleton()->getTexture("debug/circlecollider.png"));
		}
	}

	void* Collider::getCollider()
	{
		return m_pCollider;
	}

	// Move the controller by a vector, only constrained by collisions
	bool Collider::isColliding(Collider* _pCollider)
	{
		if (m_eColliderType == Collider_Box)
		{
			if (_pCollider->m_eColliderType == Collider_Box)
			{
				m_bIsColliding = collisionBoxBox(this, _pCollider);
			}
			else if (_pCollider->m_eColliderType == Collider_Circle)
			{
				m_bIsColliding = collisionBoxCircle(this, _pCollider);
			}
		}
		else if (m_eColliderType == Collider_Circle)
		{
			if (_pCollider->m_eColliderType == Collider_Box)
			{
				m_bIsColliding = collisionBoxCircle(_pCollider, this);
			}
			else if (_pCollider->m_eColliderType == Collider_Circle)
			{
				m_bIsColliding = collisionCircleCircle(_pCollider, this);
			}
		}

		_pCollider->m_bIsColliding = m_bIsColliding;

		return m_bIsColliding;
	}

	bool Collider::loadFromFileJSON(string _filename)
	{
		Json::Value root;
		std::ifstream config_doc(_filename, std::ifstream::binary);
		config_doc >> root;

		string szType = root["type"].asString();
		if (szType == "Circle")
		{
			setType(Collider_Circle);
			CircleCollider* pCircleCollider = (CircleCollider*) m_pCollider;
			pCircleCollider->getCenter() = Vector2f(root["x"].asFloat(), root["y"].asFloat());
			pCircleCollider->getRadius() = root["radius"].asFloat();
		}
		else if (szType == "Box")
		{
			setType(Collider_Box);
			BoxCollider* pBoxCollider = (BoxCollider*)m_pCollider;
			pBoxCollider->getOrigin() = Vector2f(root["x"].asFloat(), root["y"].asFloat());
			pBoxCollider->getSize() = Vector2f(root["w"].asFloat(), root["h"].asFloat());
		}
		
		return true;
	}

	bool Collider::init()
	{
		return true;
	}

	bool Collider::update()
	{
		return true;
	}

	bool Collider::draw()
	{
		if (m_pSprite)
		{
			if (m_eColliderType == Collider_Box)
			{
				BoxCollider* pCollider = (BoxCollider*)m_pCollider;
				Vector2f vOrigin = pCollider->getOrigin();
				Vector2f vSize = pCollider->getSize();
				m_pSprite->setPosition(vOrigin.getX(), vOrigin.getY());
				m_pSprite->setScale(ONEOVER128*vSize.getX(), ONEOVER128*vSize.getY());
				m_pSprite->draw();
			}
			else
			{
				Entity* pEntity1 = getEntity();
				Vector2f vPos1 = pEntity1 ? pEntity1->getPosition() : Vector2f(0.f, 0.f); 
				CircleCollider* pCollider = (CircleCollider*)m_pCollider;
				Vector2f vCenter = vPos1 + pCollider->getCenter();
				float fRadius = pCollider->getRadius();

				m_pSprite->setPosition(vCenter.getX() - fRadius + 1.f, vCenter.getY() - fRadius + 1.f);
				m_pSprite->setScale(ONEOVER128*(2*fRadius-1), ONEOVER128*(2*fRadius-1));
				m_pSprite->draw();
			}


		}
		return true;
	}

	bool Collider::quit()
	{
		return true;
	}

	bool Collider::collisionBoxBox(Collider* _pCollider1, Collider* _pCollider2)
	{
		Entity* pEntity1 = _pCollider1->getEntity();
		Entity* pEntity2 = _pCollider2->getEntity();
		Vector2f vPos1 = pEntity1 ? pEntity1->getPosition() : Vector2f(0.f, 0.f);
		Vector2f vPos2 = pEntity2 ? pEntity2->getPosition() : Vector2f(0.f, 0.f);
		BoxCollider* pBox1 = (BoxCollider*)_pCollider1->m_pCollider;
		BoxCollider* pBox2 = (BoxCollider*)_pCollider2->m_pCollider;
		
		Vector2f vWorldMin1 = vPos1 + pBox1->getMin();
		Vector2f vWorldMax1 = vPos1 + pBox1->getMax();
		Vector2f vWorldMin2 = vPos2 + pBox2->getMin();
		Vector2f vWorldMax2 = vPos2 + pBox2->getMax();

		for (char i = 0; i < 2; i++)
		{
			if (vWorldMax1.get(i) < vWorldMin2.get(i))
			{
				return false;
			}
			else if (vWorldMin1.get(i) > vWorldMax2.get(i))
			{
				return false;
			}
		}
		return true;
	}

	bool Collider::collisionBoxCircle(Collider* _pCollider1, Collider* _pCollider2)
	{
		Entity* pEntity1 = _pCollider1->getEntity();
		Entity* pEntity2 = _pCollider2->getEntity();
		Vector2f vPos1 = pEntity1 ? pEntity1->getPosition() : Vector2f(0.f, 0.f);
		Vector2f vPos2 = pEntity2 ? pEntity2->getPosition() : Vector2f(0.f, 0.f);
		BoxCollider* pBox1 = (BoxCollider*)_pCollider1->m_pCollider;
		CircleCollider* pCircle2 = (CircleCollider*)_pCollider2->m_pCollider;

		Vector2f vWorldMin1 = vPos1 + pBox1->getMin();
		Vector2f vWorldMax1 = vPos1 + pBox1->getMax();
		Vector2f vWorldCenter2 = vPos2 + pCircle2->getCenter();
		float fRadius = pCircle2->getRadius();

		float s, d = 0;
		//find the square of the distance
		//from the sphere to the box
		for (char i = 0; i<2; i++)
		{
			if (vWorldCenter2.get(i) < vWorldMin1.get(i))
			{
				s = vWorldCenter2.get(i) - vWorldMin1.get(i);
				d += s*s;
			}
			else if (vWorldCenter2.get(i) > vWorldMax1.get(i))
			{
				s = vWorldCenter2.get(i) - vWorldMax1.get(i);
				d += s*s;
			}
		}
		return d <= (fRadius*fRadius);
	}

	bool Collider::collisionCircleCircle(Collider* _pCollider1, Collider* _pCollider2)
	{
		Entity* pEntity1 = _pCollider1->getEntity();
		Entity* pEntity2 = _pCollider2->getEntity();
		Vector2f vPos1 = pEntity1 ? pEntity1->getPosition() : Vector2f(0.f, 0.f);
		Vector2f vPos2 = pEntity2 ? pEntity2->getPosition() : Vector2f(0.f, 0.f);
		CircleCollider* pCircle1 = (CircleCollider*)_pCollider1->m_pCollider;
		CircleCollider* pCircle2 = (CircleCollider*)_pCollider2->m_pCollider;

		Vector2f vWorldCenter1 = vPos1 + pCircle1->getCenter();
		Vector2f vWorldCenter2 = vPos2 + pCircle2->getCenter();
		float fRadius1 = pCircle1->getRadius();
		float fRadius2 = pCircle2->getRadius();

		float fDistSq = vWorldCenter1.distSq(vWorldCenter2);
		float fRadiuses = fRadius1 + fRadius2;
		if (fDistSq < (fRadiuses*fRadiuses))
		{
			return true;
		}
		return false;
	}

	BoxCollider::BoxCollider()
	{
	}

	BoxCollider::~BoxCollider()
	{
	}

	CircleCollider::CircleCollider()
		: m_fRadius(0.f)
	{
	}

	CircleCollider::~CircleCollider()
	{
	}

} // namespace crea
