#include "StructureRest.h"




StructureRest::StructureRest()
{
	ActVIP=ActNorm= ActFroz=ActDis=ActPol=0;
	NoNormalServ= NoFrozenServ= NoVIPServ=0;
}

void StructureRest::Setter(int NoNorm, int NoFroz, int NoVI, int SNorm, int SVIP, int SFroz,int AS)
{
	NoNormal = NoNorm;
	NoFrozen = NoFroz;
	NoVIP = NoVI;
	SpeedNormal = SNorm;
	SpeedFrozen = SFroz;
	SpeedVIP = SVIP;
	createMotos();
	AutoS = AS;
}

void StructureRest::createMotos()
{
	
	for (int i = 0; i < NoNormal;i++)
	{
		Motorcycle* Added = new Motorcycle(i+1, TYPE_NRM, SpeedNormal);
			NormReg.enqueue(Added);
	}


	for (int i = 0; i < NoFrozen; i++)
	{
		Motorcycle* Added = new Motorcycle(i+1, TYPE_FROZ, SpeedFrozen);
		FrozReg.enqueue(Added);
	}

	for (int i = 0; i < NoVIP; i++)
	{
		Motorcycle* Added = new Motorcycle(i+1, TYPE_VIP, SpeedVIP);
		VIPReg.enqueue(Added);
	}
}


void StructureRest::AddOrder(Order * po)
{
	if (po->GetType() == TYPE_NRM)
	{
		Order_ListNorm.InsertEnd((Order*)po);
		ActNorm++;
	}
	if (po->GetType() == TYPE_VIP)
	{
		int PromEqu = po->GetTotMoney() / po->GetDistance();
		Order_QueueVIP.enqueue(po,PromEqu);
		ActVIP++;
	}
	if (po->GetType() == TYPE_FROZ)
	{
		Order_QueueFroz.enqueue(po);
		ActFroz++;
	}
	if (po->GetType() == TYPE_Politicians)
	{
		Order_QueuePoliticians.enqueue(po);
		ActPol++;
	}
	if (po->GetType() == TYPE_Disabled)
	{
		Order_QueueDisabled.enqueue(po);
		ActDis++;
	}
}

void StructureRest::RemoveByID(int ID)
{
	int Pos = FindNorm(ID);
	if (Pos == -1)return;
	Order_ListNorm.remove(Pos);
	ActNorm--;
}

void StructureRest::ConvertToVIPById(int ID, double Exmon)
{
	int Pos = FindNorm(ID);
	if (Pos == -1)return;
	Order*Mov = Order_ListNorm.GetEntery(Pos);
	int PromEqu = Mov->GetTotMoney() / Mov->GetDistance();
	Mov->PromType(Exmon);
	Order_QueueVIP.enqueue(Mov,PromEqu);
	Order_ListNorm.remove(Pos);
	ActNorm--;
	ActVIP++;
}

bool StructureRest::VDequeue(Order *& Po)
{
	return Order_QueueVIP.dequeue(Po);
}

bool StructureRest::SearchNorm(int ID)const
{
	int Count = Order_ListNorm.getLength();

	for (int i = 1; i <= Count; i++)
	{
		if (Order_ListNorm.GetEntery(i)->GetID() == ID)
		{
			return true;
		}
	}
	return false;
}

int StructureRest::FindNorm(int ID) const
{
	int Count = Order_ListNorm.getLength();

	for (int i = 1; i <= Count; i++)
	{
		if (Order_ListNorm.GetEntery(i)->GetID() == ID)
		{
			return i;
		}
	}
	return -1;
}

bool StructureRest::FDequeue(Order *& Po)
{
 return Order_QueueFroz.dequeue(Po);
}

bool StructureRest::Venqueue(Order * po)
{
	return Order_QueueVIP.enqueue(po);
}

bool StructureRest::Fenqueue(Order * po)
{
	return Order_QueueFroz.enqueue(po);;
}

int StructureRest::NormLength() const
{
	return Order_ListNorm.getLength();
}

Order * StructureRest::NormOrderInd(int indx) const
{
	return Order_ListNorm.GetEntery(indx);
}

int StructureRest::getActFroz() const
{
	return ActFroz;
}

int StructureRest::getActNorm() const
{
	return ActNorm;
}

int StructureRest::getActVIP() const
{
	return ActVIP;
}

int StructureRest::getNoNormal() const
{
	return NoNormal;
}

int StructureRest::getNoFroz() const
{
	return NoFrozen;
}

int StructureRest::getNoVIP() const
{
	return NoVIP;
}

bool StructureRest::isThereVIP() const
{
	return !Order_QueueVIP.isEmpty();
}

bool StructureRest::isThereFroz() const
{
	return !Order_QueueFroz.isEmpty();
}

bool StructureRest::isNoOrders() const
{
	if (Order_QueueFroz.isEmpty() && Order_ListNorm.isEmpty() && Order_QueueVIP.isEmpty())
		return true;
	return false;
}

bool StructureRest::DDequeue(Order *& Po)
{
	return Order_QueueDisabled.dequeue(Po);
}

bool StructureRest::pDequeue(Order *& Po)
{
	return Order_QueuePoliticians.dequeue(Po);
}

bool StructureRest::Penqueue(Order * po)
{
	return Order_QueuePoliticians.enqueue(po);
}

bool StructureRest::Denqueue(Order * po)
{
	return Order_QueueDisabled.enqueue(po);
}

int StructureRest::getActPoliticians() const
{
	return ActPol;
}

int StructureRest::getActDisabled() const
{
	return ActDis;
}



bool StructureRest::isTherePoliticians() const
{
	return !Order_QueuePoliticians.isEmpty();
}

bool StructureRest::isThereDisabled() const
{
	return !Order_QueueDisabled.isEmpty();
}



bool StructureRest::NoTake(Order *& Po)
{
	Po=Order_ListNorm.GetEntery(1);
	
	if (Po)
	{
		Order_ListNorm.remove(1);
		return true;
	}
	return false;
}

void StructureRest::AssignMotos(int CurrTS)
{
	Motorcycle* Assignment;
	Order* Takeout;
	//////
	////Politicians
	while (isTherePoliticians())
	{

		if (!VIPReg.isEmpty())
		{
			Order_QueuePoliticians.dequeue(Takeout);
			VIPReg.dequeue(Assignment);
			Takeout->setFin(Assignment->getSpeed(), CurrTS);
			Assignment->AssignOrder(Takeout);
			AssignedMotoV.InsertEnd(Assignment);
			NoVIP--;
			ActPol--;
			NoPoliticiansServ++;
		}

		else if (!NormReg.isEmpty())
		{
			Order_QueuePoliticians.dequeue(Takeout);
			NormReg.dequeue(Assignment);
			Takeout->setFin(Assignment->getSpeed(), CurrTS);
			Assignment->AssignOrder(Takeout);
			AssignedMotoN.InsertEnd(Assignment);
			NoNormal--;
			ActPol--;
			NoPoliticiansServ++;
			
		}
		else if (!FrozReg.isEmpty())
		{
			Order_QueuePoliticians.dequeue(Takeout);
			FrozReg.dequeue(Assignment);
			Takeout->setFin(Assignment->getSpeed(), CurrTS);
			Assignment->AssignOrder(Takeout);
			AssignedMotoF.InsertEnd(Assignment);
			NoFrozen--;
			ActPol--;
			NoPoliticiansServ++;
		}

		else
			break;
	}
		////Disabled
		while (isThereDisabled())
		{

			if (!VIPReg.isEmpty())
			{
				Order_QueueDisabled.dequeue(Takeout);
				VIPReg.dequeue(Assignment);
				Takeout->setFin(Assignment->getSpeed(), CurrTS);
				Assignment->AssignOrder(Takeout);
				AssignedMotoV.InsertEnd(Assignment);
				NoVIP--;
				ActDis--;
				NoDisabledServ++;
			}

			else if (!NormReg.isEmpty())
			{
				Order_QueueDisabled.dequeue(Takeout);
				NormReg.dequeue(Assignment);
				Takeout->setFin(Assignment->getSpeed(), CurrTS);
				Assignment->AssignOrder(Takeout);
				AssignedMotoN.InsertEnd(Assignment);
				NoNormal--;
				ActDis--;
				NoDisabledServ++;
			}

			else
				break;

		}
	/////
	while (isThereVIP())
	{

		if (!VIPReg.isEmpty())
		{
			Order_QueueVIP.dequeue(Takeout);
			VIPReg.dequeue(Assignment);
			Takeout->setFin(Assignment->getSpeed(), CurrTS);
			Assignment->AssignOrder(Takeout);
			AssignedMotoV.InsertEnd(Assignment);
			NoVIP--;
			ActVIP--;
			NoVIPServ++;
		}

		else if (!NormReg.isEmpty())
		{
			Order_QueueVIP.dequeue(Takeout);
			NormReg.dequeue(Assignment);
			Takeout->setFin(Assignment->getSpeed(), CurrTS);
			Assignment->AssignOrder(Takeout);
			AssignedMotoN.InsertEnd(Assignment);
			NoNormal--;
			ActVIP--;

			NoNormalServ++;
		}

		else if (!FrozReg.isEmpty())
		{
			Order_QueueVIP.dequeue(Takeout);
			FrozReg.dequeue(Assignment);
			Takeout->setFin(Assignment->getSpeed(), CurrTS);
			Assignment->AssignOrder(Takeout);
			AssignedMotoF.InsertEnd(Assignment);
			NoFrozen--;
			ActVIP--;
			NoFrozenServ++;
		}
		else
			break;


	}

	////Frozens
	while (isThereFroz())
	{
		if (!FrozReg.isEmpty())
		{
			Order_QueueFroz.dequeue(Takeout);
			FrozReg.dequeue(Assignment);
			Takeout->setFin(Assignment->getSpeed(), CurrTS);
			Assignment->AssignOrder(Takeout);
			AssignedMotoF.InsertEnd(Assignment);
			NoFrozen--;
			ActFroz--;
			NoFrozenServ++;
		}
		else
			break;
	}
	////Normals
	while (!Order_ListNorm.isEmpty())
	{

		if (!NormReg.isEmpty())
		{
			Takeout = Order_ListNorm.GetEntery(1);
			Order_ListNorm.remove(1);
			NormReg.dequeue(Assignment);
			Takeout->setFin(Assignment->getSpeed(), CurrTS);
			Assignment->AssignOrder(Takeout);
			AssignedMotoN.InsertEnd(Assignment);
			NoNormal--;
			ActNorm--;
			NoNormalServ++;
		}
		else if (!VIPReg.isEmpty())
		{
			Takeout = Order_ListNorm.GetEntery(1);
			Order_ListNorm.remove(1);
			VIPReg.dequeue(Assignment);
			Takeout->setFin(Assignment->getSpeed(), CurrTS);
			Assignment->AssignOrder(Takeout);
			AssignedMotoV.InsertEnd(Assignment);
			NoVIP--;
			ActNorm--;
			NoVIPServ++;
		}
		else 
			break;
	}

	/////////
}	////////////////

void StructureRest::MotoStateFinish(int TS)
{

	while (!AssignedMotoN.isEmpty())
	{
		if (AssignedMotoN.GetEntery(1)->getOrder()->getFin() <= TS)
		{
			Finish.InsertEnd(AssignedMotoN.GetEntery(1)->getOrder());
			AssignedMotoN.GetEntery(1)->TakeOrderOut();
			NormReg.enqueue(AssignedMotoN.GetEntery(1));
			AssignedMotoN.remove(1);
			NoNormal++;
			NoNormalServ--;

		}
		else
			break;
	}
	//////////////
	while (!AssignedMotoF.isEmpty())
	{
		if (AssignedMotoF.GetEntery(1)->getOrder()->getFin() <= TS)
		{
			Finish.InsertEnd(AssignedMotoF.GetEntery(1)->getOrder());
			AssignedMotoF.GetEntery(1)->TakeOrderOut();
			FrozReg.enqueue(AssignedMotoF.GetEntery(1));
			AssignedMotoF.remove(1);
			NoFrozen++;
			NoFrozenServ--;
		}
		else
			break;
	}
	//////////////
	while (!AssignedMotoV.isEmpty())
	{
		if (AssignedMotoV.GetEntery(1)->getOrder()->getFin() <= TS)
		{
			Finish.InsertEnd(AssignedMotoV.GetEntery(1)->getOrder());
			AssignedMotoV.GetEntery(1)->TakeOrderOut();
			VIPReg.enqueue(AssignedMotoV.GetEntery(1));
			AssignedMotoV.remove(1);
			NoVIP++;
			NoVIPServ--;
		}
		else
			break;
	}
	MarkOrderIsServed(TS);
	AssignMotos(TS);
	AutoPromotion(TS);
}

bool StructureRest::ifAreanotClear() const
{
	if (isNoOrders() && AssignedMotoF.isEmpty() && AssignedMotoN.isEmpty() && AssignedMotoV.isEmpty())
		return false;
	return true;
}

bool StructureRest::ThereIsMotos() const
{
	if (FrozReg.isEmpty() && NormReg.isEmpty() && VIPReg.isEmpty())
		return false;
	return true;
}

void StructureRest::AutoPromotion(int TS)
{
	if (!Order_ListNorm.isEmpty())
	{
		int time;
		Order*Mov;
		time = Order_ListNorm.GetEntery(1)->getArr() + AutoS;
		while (time <= TS)
		{
			Mov = Order_ListNorm.GetEntery(1);
			int PromEqu = Order_ListNorm.GetEntery(1)->GetTotMoney() / Order_ListNorm.GetEntery(1)->GetDistance();
			Mov->PromType(0);
			Order_QueueVIP.enqueue(Mov,PromEqu);
			Order_ListNorm.remove(1);
			ActNorm--;
			ActVIP++;
			if (!Order_ListNorm.isEmpty())
			time = Order_ListNorm.GetEntery(1)->getArr() + AutoS;
			else break;
		}
	}
}

int StructureRest::NumberOfOrder() const
{
	return Finish.getLength();
}

float StructureRest::AvWaiting() 
{
	float Numerator=0;
	float ServedNumber = Finish.getLength();
	if(ServedNumber==0)return -1;

	for (int i = 1; i <= ServedNumber; i++)
	{
		Numerator += Finish.GetEntery(i)->getWait();
	}

	return Numerator / ServedNumber;
	
}

float StructureRest::AvServing()
{
	float Numerator = 0;
	float ServedNumber = Finish.getLength();
	if (ServedNumber == 0)return -1;
	for (int i = 1; i <= ServedNumber; i++)
	{
		Numerator += Finish.GetEntery(i)->getServ();
	}

	return Numerator / ServedNumber;
}

Order * StructureRest::FinishIndx(int Indx) const
{
	return Finish.GetEntery(Indx);
}

int StructureRest::AssignedNLength() const
{
	return AssignedMotoN.getLength();
}

Order * StructureRest::AssignedNIndx(int Indx) const
{
	return AssignedMotoN.GetEntery(Indx)->getOrder();
}

int StructureRest::AssignedFLength() const
{
	return AssignedMotoF.getLength();
}

Order * StructureRest::AssignedFIndx(int Indx) const
{
	return AssignedMotoF.GetEntery(Indx)->getOrder();
}

int StructureRest::AssignedVLength() const
{
	return AssignedMotoV.getLength();
}

void StructureRest::MarkOrderIsServed(int TS)
{
	for (int i = 1; i <= AssignedMotoN.getLength(); i++)
	{
		if (AssignedMotoN.GetEntery(i)->getOrder()->GetServingOuttime() <= TS)
		{
	
			AssignedMotoN.GetEntery(i)->getOrder()->MarkAsServed();
		}
		else
			break;
	}
	//////////////
	for (int i = 1; i <= AssignedMotoF.getLength(); i++)
	{
		if (AssignedMotoF.GetEntery(i)->getOrder()->GetServingOuttime() <= TS)
		{
			AssignedMotoF.GetEntery(i)->getOrder()->MarkAsServed();
		}
		else
			break;
	}
	//////////////
	for(int i=1;i<= AssignedMotoV.getLength();i++)
	{
		if (AssignedMotoV.GetEntery(i)->getOrder()->GetServingOuttime() <= TS)
		{
			AssignedMotoV.GetEntery(i)->getOrder()->MarkAsServed();
		}
	}


}


Order * StructureRest::AssignedVIndx(int Indx) const
{
	return AssignedMotoV.GetEntery(Indx)->getOrder();
}

int StructureRest::MotoIDVIP(int Indx) const
{
 return AssignedMotoV.GetEntery(Indx)->getID();
}

int StructureRest::MotoIDNRM(int Indx) const
{
	return AssignedMotoN.GetEntery(Indx)->getID();
}

int StructureRest::MotoIDFRZ(int Indx) const
{
	return AssignedMotoF.GetEntery(Indx)->getID();
}

int StructureRest::FinishLength() const
{
	return Finish.getLength();
}



StructureRest::~StructureRest()
{
}
