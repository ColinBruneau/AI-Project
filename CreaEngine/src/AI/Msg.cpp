// Portions Copyright (C) Steve Rabin, 2001
#include "stdafx.h"

#include "AI\Msg.h"

namespace crea
{


	Msg::Msg()
	{
		m_Name = MSG_NULL;
		m_Sender = INVALID_OBJECT_ID;
		m_Receiver = INVALID_OBJECT_ID;
		m_State = -1;
		m_DeliveryTime = 0.0f;
	}


	Msg::Msg(float deliveryTime, MSG_Name name, objectID sender, objectID receiver, int state)
	{
		SetDeliveryTime(deliveryTime);
		SetMsgName(name);
		SetSender(sender);
		SetReceiver(receiver);
		SetMsgState(state);
		SetDelivered(false);
	}

}
