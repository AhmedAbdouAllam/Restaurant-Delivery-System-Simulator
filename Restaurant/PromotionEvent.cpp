#include "PromotionEvent.h"


//You can find the functionality in declration
PromotionEvent::PromotionEvent(int eTime, int oID,double Exmon) :Event(eTime, oID)
{
	ExMon = Exmon;
}

void PromotionEvent::Execute(Restaurant * pRest)
{
	pRest->ConvertToVIPById(OrderID,ExMon);
}


PromotionEvent::~PromotionEvent()
{
}
