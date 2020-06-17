#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;
	
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	pGUI->PrintMessage("Enter the input file ");
	string File = pGUI->GetString();
	NoEvents = Streaming(File);
	MainProcedure(mode);

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		delete pGUI;
}




//You can find the functionality in declration
int Restaurant::Streaming(string File)
{
	Event* pEv;
	ifstream Input(File);
	char Ty;
	char TYP;
	ORD_TYPE Type;
	int ID, DST, MON, ExMon;
	int TS;
	REGION R;
	char REG;
	if (Input.is_open())
	{
		int SpeedNormal,SpeedFrozen,SpeedVIP,NoNormalA,NoFrozenA,NoVIPA, NoNormalB, NoFrozenB, NoVIPB, NoNormalC, NoFrozenC, NoVIPC,NoNormalD, NoFrozenD, NoVIPD;
		Input >> SpeedNormal;
		Input >> SpeedFrozen;
		Input >> SpeedVIP;
		Input >> NoNormalA;
		Input >> NoFrozenA;
		Input >> NoVIPA;
		Input >> NoNormalB;
		Input >> NoFrozenB;
		Input >> NoVIPB;
		Input >> NoNormalC;
		Input >> NoFrozenC;
		Input >> NoVIPC;
		Input >> NoNormalD;
		Input >> NoFrozenD;
		Input >> NoVIPD;
		Input >> AutoS;
		A.Setter(NoNormalA, NoFrozenA, NoVIPA, SpeedNormal, SpeedVIP, SpeedFrozen,AutoS);
		B.Setter(NoNormalB, NoFrozenB, NoVIPB, SpeedNormal, SpeedVIP, SpeedFrozen,AutoS);
		C.Setter(NoNormalC, NoFrozenC, NoVIPC, SpeedNormal, SpeedVIP, SpeedFrozen,AutoS);
		D.Setter(NoNormalD, NoFrozenD, NoVIPD, SpeedNormal, SpeedVIP, SpeedFrozen,AutoS);
		
		Input >> NoEvents;
		//Here we will Set
		
		
		Ty = 0;
		while (Ty != '-')
		{
			
			
				Input >> Ty;
			if (Ty != '-')
			{
				if (Ty == 'R')
				{
					Input >> TS;
					Input >> TYP;
					if (TYP == 'N')
					{
						Type = TYPE_NRM;
					}
					else if (TYP == 'F')
					{
						Type = TYPE_FROZ;
					}
					else if (TYP == 'V')
					{
						Type = TYPE_VIP;
					}

					else if (TYP == 'P')
					{
						Type = TYPE_Politicians;
					}
					else if (TYP == 'D')
					{
						Type = TYPE_Disabled;
					}
				
					Input >> ID;
					Input >> DST;
					Input >> MON;
					Input >> REG;
					if (REG == 'A')
					{
						R = A_REG;
					}
					else if (REG == 'B')
					{
						R = B_REG;
					}
					else if (REG == 'C')
					{
						R = C_REG;
					}
					else if (REG == 'D')
					{
						R = D_REG;
					}
					pEv = new ArrivalEvent(TS, ID, (ORD_TYPE)Type, (REGION)R, DST, MON);
					AddEvent(pEv);

				}
				else if (Ty == 'X')
				{
					Input >> TS;
					Input >> ID;
					pEv = new CancelationEvent(TS, ID);
					AddEvent(pEv);
				}
				else if (Ty == 'P')
				{
					Input >> TS;
					Input >> ID;
					Input >> ExMon;
					pEv = new PromotionEvent(TS, ID,ExMon);
					AddEvent(pEv);
				}
			}
		}
	}

	//End of Setting


	return NoEvents;
}
REGION Restaurant::FindRegofID(int ID) const
{
	if (A.SearchNorm(ID))
		return A_REG;
	else if (B.SearchNorm(ID))
		return B_REG;
	else if (C.SearchNorm(ID))
		return C_REG;
	else if (D.SearchNorm(ID))
		return D_REG;
	return REG_CNT;
}
void Restaurant::RemoveByID(int ID)
{
	REGION Temp = FindRegofID(ID);
	if (Temp == A_REG)
		A.RemoveByID(ID);
	else if (Temp == B_REG)
		B.RemoveByID(ID);
	else if (Temp == C_REG)
		C.RemoveByID(ID);
	else if (Temp == D_REG)
		D.RemoveByID(ID);
}
void Restaurant::ConvertToVIPById(int ID, double Exmon)
{

	REGION Temp = FindRegofID(ID);
	if (Temp == A_REG)
		A.ConvertToVIPById(ID,Exmon);
	else if (Temp == B_REG)
		B.ConvertToVIPById(ID, Exmon);
	else if (Temp == C_REG)
		C.ConvertToVIPById(ID, Exmon);
	else if (Temp == D_REG)
		D.ConvertToVIPById(ID, Exmon);
}

void Restaurant::LogicalRun(int TS)
{
	A.MotoStateFinish(TS);
	B.MotoStateFinish(TS);
	C.MotoStateFinish(TS);
	D.MotoStateFinish(TS);
}

void Restaurant::CreateMotos()
{
	A.createMotos();
	B.createMotos();
	C.createMotos();
	D.createMotos();
}

void Restaurant::RegionPrint(StructureRest & Dummy)
{
	//In service
	int Count=Dummy.AssignedVLength();
	for (int i = 1; i <= Count; i++)
	{
		if(!Dummy.AssignedVIndx(i)->getServedStatus())
		pGUI->AddOrderForDrawing(Dummy.AssignedVIndx(i));
	}
	 Count = Dummy.AssignedNLength();
	for (int i = 1; i <= Count; i++)
	{
		if (!Dummy.AssignedNIndx(i)->getServedStatus())
		pGUI->AddOrderForDrawing(Dummy.AssignedNIndx(i));
	}
	 Count = Dummy.AssignedFLength();
	for (int i = 1; i <= Count; i++)
	{
		if (!Dummy.AssignedFIndx(i)->getServedStatus())
		pGUI->AddOrderForDrawing(Dummy.AssignedFIndx(i));
	}


	//VIP
	
	while (Dummy.isThereVIP())
	{
		Dummy.VDequeue(TransOrd);
		pGUI->AddOrderForDrawing(TransOrd);
		TransQueue.enqueue(TransOrd);
	}
	while (!TransQueue.isEmpty())
	{
		TransQueue.dequeue(TransOrd);
		Dummy.Venqueue(TransOrd);
	}
	//Normal
	 Count = Dummy.NormLength();
	for (int i = 1; i <= Count; i++)
	{
		pGUI->AddOrderForDrawing(Dummy.NormOrderInd(i));
	}
	////frozen
	while (Dummy.isThereFroz())
	{
		Dummy.FDequeue(TransOrd);
		pGUI->AddOrderForDrawing(TransOrd);
		TransQueue.enqueue(TransOrd);
	}
	while (!TransQueue.isEmpty())
	{
		TransQueue.dequeue(TransOrd);
		Dummy.Fenqueue(TransOrd);
	}
	
}

void Restaurant::RestPrint(int CurrTS)
{
	char timestep[10];
	_itoa(CurrTS, timestep, 10);
	pGUI->PrintMessage("Timestep:");
	pGUI->PrintStatBar(timestep, 70, 0);
	
	pGUI->PrintStatBar("                              Region A                              Region B                              Region C                              Region D", 30, 20);
	pGUI->PrintStatBar("Act VIP Ord's/Mot:", 0, 40);
	pGUI->PrintStatBar("Act Frz Ord's/Mot:", 0, 55);
	pGUI->PrintStatBar("Act Nrm Ord's/Mot:", 0, 70);
	pGUI->PrintStatBar("Act Pol/Dis Ord's:", 0, 85);
	pGUI->PrintStatBar(_itoa(A.getActVIP(), timestep, 10), 163, 40);
	pGUI->PrintStatBar(_itoa(B.getActVIP(), timestep, 10), 345, 40);
	pGUI->PrintStatBar(_itoa(C.getActVIP(), timestep, 10), 530, 40);
	pGUI->PrintStatBar(_itoa(D.getActVIP(), timestep, 10), 715, 40);

	pGUI->PrintStatBar(_itoa(A.getActFroz(), timestep, 10), 163, 55);
	pGUI->PrintStatBar(_itoa(B.getActFroz(), timestep, 10), 345, 55);
	pGUI->PrintStatBar(_itoa(C.getActFroz(), timestep, 10), 530, 55);
	pGUI->PrintStatBar(_itoa(D.getActFroz(), timestep, 10), 715, 55);

	pGUI->PrintStatBar(_itoa(A.getActNorm(), timestep, 10), 163, 70);
	pGUI->PrintStatBar(_itoa(B.getActNorm(), timestep, 10), 345, 70);
	pGUI->PrintStatBar(_itoa(C.getActNorm(), timestep, 10), 530, 70);
	pGUI->PrintStatBar(_itoa(D.getActNorm(), timestep, 10), 715, 70);
	
	pGUI->PrintStatBar(_itoa(A.getNoVIP(), timestep, 10), 193, 40);
	pGUI->PrintStatBar(_itoa(B.getNoVIP(), timestep, 10), 375, 40);
	pGUI->PrintStatBar(_itoa(C.getNoVIP(), timestep, 10), 560, 40);
	pGUI->PrintStatBar(_itoa(D.getNoVIP(), timestep, 10), 745, 40);

	pGUI->PrintStatBar(_itoa(A.getNoFroz(), timestep, 10), 193, 55);
	pGUI->PrintStatBar(_itoa(B.getNoFroz(), timestep, 10), 375, 55);
	pGUI->PrintStatBar(_itoa(C.getNoFroz(), timestep, 10), 560, 55);
	pGUI->PrintStatBar(_itoa(D.getNoFroz(), timestep, 10), 745, 55);

	pGUI->PrintStatBar(_itoa(A.getNoNormal(), timestep, 10), 193, 70);
	pGUI->PrintStatBar(_itoa(B.getNoNormal(), timestep, 10), 375, 70);
	pGUI->PrintStatBar(_itoa(C.getNoNormal(), timestep, 10), 560, 70);
	pGUI->PrintStatBar(_itoa(D.getNoNormal(), timestep, 10), 745, 70);
	////
	pGUI->PrintStatBar(_itoa(A.getActPoliticians(), timestep, 10), 163, 85);
	pGUI->PrintStatBar(_itoa(B.getActPoliticians(), timestep, 10), 345, 85);
	pGUI->PrintStatBar(_itoa(C.getActPoliticians(), timestep, 10), 530, 85);
	pGUI->PrintStatBar(_itoa(D.getActPoliticians(), timestep, 10), 715, 85);

	pGUI->PrintStatBar(_itoa(A.getActDisabled(), timestep, 10), 193, 85);
	pGUI->PrintStatBar(_itoa(B.getActDisabled(), timestep, 10), 375, 85);
	pGUI->PrintStatBar(_itoa(C.getActDisabled(), timestep, 10), 560, 85);
	pGUI->PrintStatBar(_itoa(D.getActDisabled(), timestep, 10), 745, 85);
	
	////
	RegionPrint(A);
	RegionPrint(B);
	RegionPrint(C);
	RegionPrint(D);
	pGUI->ClearHeadBar();
	//HeadPrint(StructureRest& Dummy,int y) const
	pGUI->PrintUpBar("Region A:",0, 0,RED);
	HeadPrint(A, 0);
	pGUI->PrintUpBar("Region B:", 0,12, RED);
	HeadPrint(B, 12);
	pGUI->PrintUpBar("Region C:", 0, 25, RED);
	HeadPrint(C, 25);
	pGUI->PrintUpBar("Region D:", 0, 37, RED);
	HeadPrint(D, 37);
	pGUI->UpdateInterface();
}

bool Restaurant::ifAreNotClear() const
{
	if (A.ifAreanotClear() || B.ifAreanotClear() || C.ifAreanotClear() || D.ifAreanotClear())
		return true;
	return false;
}
float Restaurant::AverageServTotal() 
{
	float TotalOrders = A.FinishLength() + B.FinishLength() + C.FinishLength() + D.FinishLength();
	float x = A.AvServing()*A.FinishLength() + B.AvServing()  *B.FinishLength() + C.AvServing()*C.FinishLength() + D.AvServing()*D.FinishLength();
	return x / TotalOrders;
}

float Restaurant::AverageWaitTotal() 
{
	
	float TotalOrders = A.FinishLength() + B.FinishLength() + C.FinishLength() + D.FinishLength();
	float x = A.AvWaiting()*A.FinishLength() + B.AvWaiting()*B.FinishLength() + C.AvWaiting()*C.FinishLength() + D.AvWaiting()*D.FinishLength();
	return x / TotalOrders;
}
void Restaurant::OutputFile(string File)
{
	ofstream outputfile;
	outputfile.open(File + ".txt", ios::out);
	outputfile << " Region A:" << endl;
	outputfile << "FT" << "   " << "ID" << "   " << "AT" << "   " << " WT" << "   " << "ST" << endl;
	int NoOrdersA = A.FinishLength();
	Order * O;
	int NormA = 0;
	int VipA = 0;
	int FrozA = 0;
	int DisA = 0;
	int PolA = 0;
	for (int i = 1; i <= NoOrdersA; i++)
	{
		O = A.FinishIndx(i);
		outputfile << O->getFin() << "    " << O->GetID() << "    " << O->getArr() << "    " << O->getWait() << "    " << O->getServ() << endl;
		if (O->GetType() == TYPE_NRM)
			NormA++;
		else if (O->GetType() == TYPE_VIP)
			VipA++;
		else if (O->GetType() == TYPE_FROZ)
			FrozA++;
		else if (O->GetType() == TYPE_Disabled)
			DisA++;
		else if (O->GetType() == TYPE_Politicians)
			PolA++;
	}
	outputfile << " Orders: " << NoOrdersA << " " << "[Norm: " << NormA << ", Froz:" << FrozA << ", VIP:" << VipA << ",Politicians: "<<PolA<<"Disabled: "<<DisA<< "]" << endl;
	int motorNA = A.getNoNormal();
	int motorVA = A.getNoVIP();
	int motorFA = A.getNoFroz();
	int noOfAllmotorA = motorNA + motorFA + motorVA;
	outputfile << " MotorC: " << noOfAllmotorA << " " << "[Norm: " << motorNA << ", Froz:" << motorFA << ", VIP:" << motorVA << "]" << endl;
	float avgWA = A.AvWaiting();
	float avgServA = A.AvServing();
	outputfile << "Avg Wait =" << avgWA << ", Avg Serv =" << avgServA << endl;
	outputfile << " Region B:" << endl;
	outputfile << "FT" << "   " << "ID" << "   " << "AT" << "   " << " WT" << "   " << "ST" << endl;
	int NormB = 0;
	int VipB = 0;
	int FrozB = 0;
	int PolB = 0;
	int DisB = 0;
	int NoOrdersB = B.FinishLength();
	for (int i = 1; i <= NoOrdersB; i++)
	{
		O = B.FinishIndx(i);
		outputfile << O->getFin() << "    " << O->GetID() << "    " << O->getArr() << "    " << O->getWait() << "    " << O->getServ() << endl;
		if (O->GetType() == TYPE_NRM)
			NormB++;
		else if (O->GetType() == TYPE_VIP)
			VipB++;
		else if (O->GetType() == TYPE_FROZ)
			FrozB++;
		else if (O->GetType() == TYPE_Disabled)
			DisB++;
		else if (O->GetType() == TYPE_Politicians)
			PolB++;
	}
	outputfile << " Orders: " << NoOrdersB << " " << "[Norm: " << NormB << ", Froz:" << FrozB << ", VIP:" << VipB << ",Politicians: " << PolB << "Disabled: " << DisB << "]" << endl;
	int motorNB = B.getNoNormal();
	int motorVB = B.getNoVIP();
	int motorFB = B.getNoFroz();
	int noOfAllmotorB = motorFB + motorNB + motorVB;
	outputfile << " MotorC: " << noOfAllmotorB << " " << "[Norm: " << motorNB << ", Froz:" << motorFB << ", VIP:" << motorVB << "]" << endl;
	float avgWB = B.AvWaiting();
	float avgServB = B.AvServing();
	outputfile << "Avg Wait =" << avgWB << ", Avg Serv =" << avgServB << endl;
	outputfile << " Region C:" << endl;
	outputfile << "FT" << "    " << "ID" << "    " << "AT" << "    " << " WT" << "    " << "ST" << endl;
	int NormC = 0;
	int VipC = 0;
	int FrozC = 0;
	int PolC = 0;
	int DisC = 0;
	int NoOrdersC = C.FinishLength();
	for (int i = 1; i <= NoOrdersC; i++)
	{
		O = C.FinishIndx(i);
		outputfile << O->getFin() << "    " << O->GetID() << "    " << O->getArr() << "    " << O->getWait() << "    " << O->getServ() << endl;
		if (O->GetType() == TYPE_NRM)
			NormC++;
		else if (O->GetType() == TYPE_VIP)
			VipC++;
		else if (O->GetType() == TYPE_FROZ)
			FrozC++;
		else if (O->GetType() == TYPE_Disabled)
			DisC++;
		else if (O->GetType() == TYPE_Politicians)
			PolC++;
	}
	outputfile << " Orders: " << NoOrdersC << " " << "[Norm: " << NormC << ", Froz:" << FrozC << ", VIP:" << VipC << ",Politicians: " << PolC << ",Disabled: " << DisC << "]" << endl;
	int motorNC = C.getNoNormal();
	int motorVC = C.getNoVIP();
	int motorFC = C.getNoFroz();
	int noOfAllmotorC = motorNC + motorVC + motorFC;
	outputfile << " MotorC: " << noOfAllmotorC << " " << "[Norm: " << motorNC << ", Froz:" << motorFC << ", VIP:" << motorVC << "]" << endl;
	float avgWC = C.AvWaiting();
	float avgServC = C.AvServing();
	outputfile << "Avg Wait =" << avgWC << ", Avg Serv =" << avgServC << endl;
	outputfile << " Region D:" << endl;
	outputfile << "FT" << "  " << "ID" << "  " << "AT" << "  " << " WT" << "  " << "ST" << endl;
	int NormD = 0;
	int VipD = 0;
	int FrozD = 0;
	int PolD = 0;
	int DisD = 0;
	int NoOrdersD = D.FinishLength();
	for (int i = 1; i <= NoOrdersD; i++)
	{
		O = D.FinishIndx(i);
		outputfile << O->getFin() << "    " << O->GetID() << "    " << O->getArr() << "    " << O->getWait() << "    " << O->getServ() << endl;
		if (O->GetType() == TYPE_NRM)
			NormD++;
		else if (O->GetType() == TYPE_VIP)
			VipD++;
		else if (O->GetType() == TYPE_FROZ)
			FrozD++;
		else if (O->GetType() == TYPE_Disabled)
			DisD++;
		else if (O->GetType() == TYPE_Politicians)
			PolD++;
	}
	outputfile << " Orders: " << NoOrdersD << " " << "[Norm: " << NormD << ", Froz:" << FrozD << ", VIP:" << VipD << ",Politicians: " << PolD << ",Disabled: " << DisD << "]" << endl;
	int motorND = D.getNoNormal();
	int motorVD = D.getNoVIP();
	int motorFD = D.getNoFroz();
	int noOfAllmotorD = motorND + motorVD + motorFD;
	outputfile << " MotorC: " << noOfAllmotorD << " " << "[Norm: " << motorND << ", Froz:" << motorFD << ", VIP:" << motorVD << "]" << endl;
	float avgWD = D.AvWaiting();
	float avgServD = D.AvServing();
	outputfile << "Avg Wait =" << avgWD << ", Avg Serv =" << avgServD << endl;
	outputfile << "  informations for whole restaurant : " << endl;
	int Norms = NormA + NormB + NormC + NormD;
	int Froz = FrozA + FrozB + FrozC + FrozD;
	int Vip = VipA + VipB + VipC + VipD;
	int Pol = PolA + PolB + PolC + PolD;
	int Dis = DisA + DisB + DisC + DisD;
	int noOfOrders = NoOrdersA + NoOrdersB + NoOrdersC + NoOrdersD;
	outputfile << " Orders: " << noOfOrders << " " << "[Norm: " << Norms << ", Froz:" << Froz << ", VIP:" << Vip <<",Politicians: "<<Pol<<",Disabled: "<<Dis <<"]" << endl;
	int noOfAllmotor = noOfAllmotorA + noOfAllmotorB + noOfAllmotorC + noOfAllmotorD;
	int motorN = motorNA + motorNB + motorNC + motorND;
	int motorV = motorVA + motorVB + motorVC + motorVD;
	int motorF = motorFA + motorFB + motorFC + motorFD;
	outputfile << " MotorC: " << noOfAllmotor << " " << "[Norm: " << motorN << ", Froz:" << motorF << ", VIP:" << motorV << "]" << endl;
	outputfile << "Avg Wait =" << AverageWaitTotal() << ", Avg Serv =" << AverageServTotal() << endl;
}
//You can find the functionality in declration
void Restaurant::MainProcedure(PROG_MODE Mod)
{
	int CurrentTimeStep = 0;//For Debugging only
	while (!EventsQueue.isEmpty() || ifAreNotClear())
	{
		//print current timestep
		if (!EventsQueue.isEmpty())
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		
		LogicalRun(CurrentTimeStep);
	//This functions print in status bar
	
		///////////////////////////////////////////////

/////////////////
		
		
		 if (Mod == MODE_INTR)
		{
			RestPrint(CurrentTimeStep);
			pGUI->waitForClick();
			pGUI->ResetDrawingList();
		}
		else if (Mod == MODE_STEP)
		{
			RestPrint(CurrentTimeStep);
			Sleep(1000);
			pGUI->ResetDrawingList();
		}
	

//	
		CurrentTimeStep++;	//advance timestep
	}
	

	pGUI->PrintMessage("Enter the Required Output file:");
	string File = pGUI->GetString();
	OutputFile(File);
	pGUI->PrintMessage("The input file is now over click to end the program >>>>>>>>>Thank You <3 <<<<<<<<<<");
	pGUI->waitForClick();

}
void Restaurant::HeadPrint(StructureRest& Dummy,int y) const
{
	//In service
	char timestep[10];

	int Count = Dummy.AssignedVLength();
	int x = 50;
	char St[10];
	
	for (int i = 1; i <= Count; i++)
	{
		if (!Dummy.AssignedVIndx(i)->getServedStatus())
		{
			pGUI->PrintUpBar(itoa(Dummy.AssignedVIndx(i)->GetID(), St, 10), x + 10, y, RED);
			string ADD;
			if (Dummy.AssignedVIndx(i)->GetType() == TYPE_VIP)
				ADD = "(V)";
			else if (Dummy.AssignedVIndx(i)->GetType() == TYPE_FROZ)
				ADD = "(F)";
			else if (Dummy.AssignedVIndx(i)->GetType() == TYPE_NRM)
				ADD = "(N)";
			else if (Dummy.AssignedVIndx(i)->GetType() == TYPE_Politicians)
				ADD = "(P)";
			else if (Dummy.AssignedVIndx(i)->GetType() == TYPE_Disabled)
				ADD = "(D)";
			pGUI->PrintUpBar(ADD, x +24, y, RED);
			pGUI->PrintUpBar(itoa(Dummy.MotoIDVIP(i), St, 10), x + 41, y, RED);
			x += 50;
		}
		
	}
	Count = Dummy.AssignedNLength();
	for (int i = 1; i <= Count; i++)
	{
		if (!Dummy.AssignedNIndx(i)->getServedStatus())
		{
			pGUI->PrintUpBar(itoa(Dummy.AssignedNIndx(i)->GetID(), St, 10), x + 10, y, DARKBLUE);
			string ADD;
			if (Dummy.AssignedNIndx(i)->GetType() == TYPE_VIP)
				ADD = "(V)";
			else if (Dummy.AssignedNIndx(i)->GetType() == TYPE_FROZ)
				ADD = "(F)";
			else if (Dummy.AssignedNIndx(i)->GetType() == TYPE_NRM)
				ADD = "(N)";
			else if (Dummy.AssignedNIndx(i)->GetType() == TYPE_Politicians)
				ADD = "(P)";
			else if (Dummy.AssignedNIndx(i)->GetType() == TYPE_Disabled)
				ADD = "(D)";
			pGUI->PrintUpBar(ADD, x + 24, y, DARKBLUE);
			pGUI->PrintUpBar(itoa(Dummy.MotoIDNRM(i), St, 10), x + 41, y, DARKBLUE);
			x += 50;
		}
		
	}
	Count = Dummy.AssignedFLength();
	for (int i = 1; i <= Count; i++)
	{
		if (!Dummy.AssignedFIndx(i)->getServedStatus())
		{
			pGUI->PrintUpBar(itoa(Dummy.AssignedFIndx(i)->GetID(), St, 10), x + 10, y, VIOLET);
			string ADD;
			if (Dummy.AssignedFIndx(i)->GetType() == TYPE_VIP)
				ADD = "(V)";
			else if (Dummy.AssignedFIndx(i)->GetType() == TYPE_FROZ)
				ADD = "(F)";
			else if (Dummy.AssignedFIndx(i)->GetType() == TYPE_NRM)
				ADD = "(N)";
			else if (Dummy.AssignedFIndx(i)->GetType() == TYPE_Politicians)
				ADD = "(P)";
			else if (Dummy.AssignedFIndx(i)->GetType() == TYPE_Disabled)
				ADD = "(D)";
			pGUI->PrintUpBar(ADD, x + 24, y, VIOLET);
			pGUI->PrintUpBar(itoa(Dummy.MotoIDFRZ(i), St, 10), x + 41, y, VIOLET);
			x += 50;
		}
		
	}
	
}
//You can find the functionality in declration
void  Restaurant::Addto(Order* po)
{
	if (po->GetRegion() == A_REG)
		A.AddOrder(po);
	else if (po->GetRegion() == B_REG)
		B.AddOrder(po);
	else if (po->GetRegion() == C_REG)
		C.AddOrder(po);
	else if (po->GetRegion() == D_REG)
		D.AddOrder(po);
}



