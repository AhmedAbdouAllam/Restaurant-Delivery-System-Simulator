#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"
#include"Order.h"
#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	Order* MotoOrder;
	
public:
	///A.Allam Added functions
	Motorcycle(int id,ORD_TYPE ty,int sp);
	void MarkInService();//Changes it to InService
	void MarkIdle();//Changes it to idle
	int getID()const;//Returns the ID
	bool AssignOrder(Order* M);
	bool TakeOrderOut();
	Order*& getOrder();
	int getSpeed()const;
	ORD_TYPE getType() const;//Returns The Type
	REGION getRegion() const;//Returns the region
	STATUS getStatus() const;//Returns its status
	virtual ~Motorcycle();
};

#endif