#pragma once
#include "Events\Event.h"
#include "Rest/Restaurant.h"
class CancelationEvent :
	public Event
{
public:
	CancelationEvent(int eTime, int oID);
	virtual void Execute(Restaurant* pRest);//Cancels the event by its id from normal list
	~CancelationEvent();
};

