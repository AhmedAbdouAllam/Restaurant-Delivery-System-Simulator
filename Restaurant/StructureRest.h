#pragma once
#include "LinkedList.h"
#include"PrrQueue.h"
#include"Generic_DS/Queue.h"
#include"Rest/Order.h"
#include"Rest/Motorcycle.h"
#include"Rest/Order.h"
//#include"Rest/Restaurant.h"
class Restaurant;
class StructureRest
{
	int ActVIP, ActFroz, ActNorm, ActPol, ActDis;
	int AutoS;
	PrrQueue<Order*> Order_QueueVIP;
	Queue<Order*> Order_QueueFroz;
	LinkedList<Order*> Order_ListNorm;

	LinkedList <Order*> Finish;
	Queue<Motorcycle*> FrozReg;
	Queue<Motorcycle*> NormReg;
	Queue<Motorcycle*> VIPReg;
	////
	PrrQueue<Order*> Order_QueueDisabled;
	PrrQueue<Order*> Order_QueuePoliticians;
	////
	LinkedList<Motorcycle*> AssignedMotoN;
	LinkedList<Motorcycle*> AssignedMotoF;
	LinkedList<Motorcycle*> AssignedMotoV;
	int NoOffinishedOrd;
	int NoOfReqOrders;
	int SpeedNormal, SpeedFrozen, SpeedVIP;
	int NoNormal, NoFrozen, NoVIP;
	int NoNormalServ, NoFrozenServ, NoVIPServ, NoPoliticiansServ, NoDisabledServ;
	Queue<Order*> TransQueue;
	Order* TransOrder;
	//int NoNormalIdle, NoFrozenIdle, NoVIPIdle;
	//Active Orders
public:
	StructureRest();
	void Setter(int NoNorm, int NoFroz, int NoVI, int SNorm, int SVIP, int SFroz,int As);
	void createMotos();
	void AddOrder(Order* Po);
	void RemoveByID(int ID);//Removes an order using it's ID
	void ConvertToVIPById(int ID, double Exmon);//Converts an order from Normal to vip and puts it in vip queue
	bool VDequeue(Order*& Po);
	bool SearchNorm(int ID) const;
	int FindNorm(int ID)const;
	bool FDequeue(Order*& Po);

	bool Venqueue(Order* po);
	bool Fenqueue(Order* po);
	int NormLength() const;
	Order* NormOrderInd(int indx)const;
	int getActFroz()const;
	int getActNorm()const;
	int getActVIP()const;
	int getNoNormal()const;
	int getNoFroz()const;
	int getNoVIP()const;
	bool isThereVIP()const;
	bool isThereFroz()const;
	bool isNoOrders() const;
	////////
	bool DDequeue(Order*& Po);
	bool pDequeue(Order*& Po);
	bool Penqueue(Order* po);
	bool Denqueue(Order* po);
	int getActPoliticians()const;
	int getActDisabled()const;
	bool isTherePoliticians()const;
	bool isThereDisabled()const;
	////////
	bool NoTake(Order*& Po);
	void AssignMotos(int TS);
	void MotoStateFinish(int TS);
	bool ifAreanotClear() const;
	bool ThereIsMotos()const;
	void AutoPromotion(int TS);
	int NumberOfOrder()const;
	float AvWaiting();
	float AvServing();
	Order* FinishIndx(int Indx)const;
	int AssignedNLength()const;
	Order* AssignedNIndx(int Indx)const;
	int AssignedFLength()const;
	Order* AssignedFIndx(int Indx)const;
	int AssignedVLength()const;
	void MarkOrderIsServed(int TS);
	Order* AssignedVIndx(int Indx)const;
	int MotoIDVIP(int indx)const;
	int MotoIDNRM(int indx)const;
	int MotoIDFRZ(int indx)const;
	int FinishLength()const;
	~StructureRest();
};

