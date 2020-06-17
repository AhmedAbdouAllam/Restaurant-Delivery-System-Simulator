#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"

//You can find the functionality in declration
ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg,int  DST,double MON):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	OrdMoney = MON;
	OrdDistance = DST;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{

	Order* pord = new Order(OrderID, OrdType, OrdRegion, OrdDistance, EventTime, OrdMoney);
	pRest->Addto(pord);
}
