#pragma once
#include "Events/Event.h"
#include "Rest/Restaurant.h"
class PromotionEvent :
	public Event
{
	double ExMon;
public:
	PromotionEvent(int eTime, int oID, double Exmon);
	virtual void Execute(Restaurant* pRest);//changes it to vip and removes it from normal list then adds itb to vip queue
	~PromotionEvent();
};

