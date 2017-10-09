/***************************************************/
/* Nom:	Messages.h
/* Description: Messages
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Messages_H_
#define __Messages_H_

//Add new messages here
typedef enum {
	MSG_NULL,
	MSG_Randomize,
	MSG_Timeout,
	MSG_ChangeState,
	MSG_Die,
	MSG_Hit,
	MSG_HitStop,
	MSG_Reset,
	MSG_Stop,
	MSG_Start,
	MSG_Teleport
} MSG_Name;

#endif
