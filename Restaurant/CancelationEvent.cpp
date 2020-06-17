#include "CancelationEvent.h"


//You can find the functionality in declration
CancelationEvent::CancelationEvent(int eTime, int oID) :Event(eTime, oID)
{
}

void CancelationEvent::Execute(Restaurant* pRest)
{
	pRest->RemoveByID(OrderID);
}
CancelationEvent::~CancelationEvent()
{
}
