#include "Motorcycle.h"

//You can find the functionality in the declration
Motorcycle::Motorcycle(int id, ORD_TYPE ty, int sp)
{
	ID = id;
	type = ty;
	speed = sp;
	MotoOrder = nullptr;
	//region = r;
}

void Motorcycle::MarkInService()
{
	status = SERV;

}
void Motorcycle::MarkIdle()
{
	status = IDLE;
}
bool Motorcycle::TakeOrderOut()
{
	if (MotoOrder)
	{
		MarkIdle();
		MotoOrder = nullptr;
		return true;
	}
	return false;
}
Order *& Motorcycle::getOrder() 
{
	return MotoOrder;
}
int Motorcycle::getSpeed() const
{
	return speed;
}
ORD_TYPE Motorcycle::getType() const
{
	return type;
}
REGION Motorcycle::getRegion() const
{
	return region;
}
STATUS Motorcycle::getStatus() const
{
	return status;
}
int Motorcycle::getID()const
{
	return ID;
}
bool Motorcycle::AssignOrder(Order * M)
{
	if (!MotoOrder)
	{
		MarkInService();
		MotoOrder = M;
		return true;
	}
return false;
}
Motorcycle::~Motorcycle()
{
}
