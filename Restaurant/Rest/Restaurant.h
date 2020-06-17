#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\CancelationEvent.h"
#include "..\PromotionEvent.h"
#include "Order.h"
#include "..\ArrList.h"
#include "..\LinkedList.h"
#include "..\PrrQueue.h"
#include"..\Rest\Motorcycle.h"
#include"..\StructureRest.h"
// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	Queue<Order*> TransQueue;
	Order* TransOrd;

	int AutoS, NoEvents;
	StructureRest A;
	StructureRest B;
	StructureRest C;
	StructureRest D;

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();//Stimulation function

	void Addto(Order* pord);
	int Streaming(string File);//Reads an input file
	
	REGION FindRegofID(int ID)const;//Finds a postion using the ID
	
	void RemoveByID(int ID);//Removes an order using it's ID
	
	void ConvertToVIPById(int ID,double Exmon);//Converts an order from Normal to vip and puts it in vip queue
	void LogicalRun(int TS);
	void CreateMotos();
	
	void RegionPrint(StructureRest &Dummy);
	void RestPrint(int CurrTS);
	bool ifAreNotClear()const;
	void OutputFile(string File);
	float AverageServTotal ();
	float AverageWaitTotal();
	void MainProcedure(PROG_MODE Mod);//Phase One stimulation function/
	void HeadPrint(StructureRest &Dummy, int y)const;
};
#endif