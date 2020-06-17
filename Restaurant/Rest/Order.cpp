#include "Order.h"
//You can find the functionality descriped in the declration
Order::Order(int id, ORD_TYPE r_Type, REGION r_region, int Dist, int Arr, double mon)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;
	if (Dist > 0)
		Distance = Dist;
	else
		Distance = 1;
	ArrTime = Arr;
	totalMoney = mon;
	InServ = false;
	Served = false;
}
void Order::setServe(int speed)
{
	ServTime = 2*Distance/speed;
}
void Order::setFin(int speed,int CurrTS)
{
	setServe(speed);
	setWait(CurrTS);
	FinishTime = WaitingTime+ArrTime+ServTime;
}
void Order::setWait(int CurrTS)
{
	InServ = true;
	WaitingTime = CurrTS-ArrTime;
}
int Order::getFin() const
{
	return FinishTime;
}
void Order::AddExtraMoney(double Ex)
{
	totalMoney += Ex;
	type = TYPE_VIP;
}
Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}

int Order::getArr() const
{
	return ArrTime;
}

int Order::getWait() const
{
	return WaitingTime;
}

double Order::GetTotMoney() const
{
	return totalMoney;
}

int Order::getServ() const
{
	return ServTime/2;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}
int Order::GetServingOuttime() const
{
	return (FinishTime-ServTime/2);
}
void Order::MarkAsServed() 
{
	Served = true;
}
bool Order::getServedStatus() const
{
	return Served;
}
void Order::PromType(double exmon)
{
	type = TYPE_VIP;
	AddExtraMoney(exmon);
}
