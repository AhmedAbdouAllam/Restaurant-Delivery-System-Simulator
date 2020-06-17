#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	bool InServ;
	double totalMoney;	//Total order money
	bool Served;
	int ArrTime,WaitingTime, ServTime, FinishTime;	//arrival, service start, and finish times


public:
	Order(int ID, ORD_TYPE r_Type, REGION r_region,int Dist,int Arr,double mon);
	void setServe(int speed);//sets service time
	void setFin(int speed,int CurrTS);//calculates finishing time
	void setWait(int CurrTS);//Sets WaitingTime
	int getFin()const;// gets Finish time
	void AddExtraMoney(double Ex);//Adds extramoney
	virtual ~Order();
	int GetID();//returns the id
	ORD_TYPE GetType() const;//returns the type
	int getArr() const;
	int getWait()const;
	double GetTotMoney()const;
	int getServ()const;
	void PromType(double exmon=0);//pomotes  the order and adds extra money
	REGION GetRegion() const;//returns the region
	void SetDistance(int d);//sets the distance
	int GetDistance() const;//returns the distance
	int GetServingOuttime()const;
	void MarkAsServed();
	bool getServedStatus() const;
};

#endif