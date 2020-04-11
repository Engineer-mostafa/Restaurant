#include <cstdlib>
#include <time.h>
#include <iostream>
#include<fstream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation(ifstream&read)
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		//Interactive
		break;
	case MODE_STEP:
		//StepByStep
		break;
	case MODE_SLNT:
		//Silent
		break;
	case MODE_DEMO:
		Load_Data(read);

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		if (pGUI)
			delete pGUI;
}

void Restaurant::Load_Data(ifstream& read)
{
	
	read >> Num_Cooks_N >> Num_Cooks_V >> Num_Cooks_G;
	int Total = Num_Cooks_N + Num_Cooks_V + Num_Cooks_G;
	int  numberofevents;
	int N_speed, V_speed, G_speed;
	read >> N_speed >> V_speed >> G_speed;
	//cout << Num_Cooks_N << Num_Cooks_V << Num_Cooks_G;
	for (int i = 0; i < Total; i++)
	{
		if (i < Num_Cooks_N)
		{
			Cook* cook = new Cook('N', N_speed);
			COOKS_Queue.enqueue(cook);
		}
		else if(i < Num_Cooks_V + Num_Cooks_N)
		{
			Cook* cook = new Cook('V', V_speed);
			COOKS_Queue.enqueue(cook);
		}
		else 
		{
			Cook* cook = new Cook('G', G_speed);
			COOKS_Queue.enqueue(cook);
		}
	}
	//setCooks(N_speed, V_speed, G_speed);
	read>> NUM_ORD>> NORM_BREAK>>VIP_BRAEK>> VEG_BREAK;
	read >> AutoP >> numberofevents;
	char event_Type;
	char order_Type;
	int id, ord_size, etime; double money;
	Order* order;
	ArrivalEvent* arr_event;
	for (int i = 0; i < numberofevents;i++)
	{
		read >> event_Type;
		if (event_Type == 'R')
		{
			read>> order_Type >> etime >> id >> ord_size >> money;
			arr_event = new ArrivalEvent(etime,id,order_Type,ord_size,money);
			EventsQueue.enqueue(arr_event);
			arr_event->Execute(this);
			pGUI->waitForClick();
		}
		else if (event_Type == 'X')
		{
			read >> etime >> id;
			CancelEvent* cancel_event = new CancelEvent(etime, id);
			EventsQueue.enqueue(cancel_event);
			cancel_event->Execute(this);

		}
		else if (event_Type == 'P')
		{
			read >> etime >> id >> money;
			PromotionEvent* promote_event = new PromotionEvent(etime, id,money);
			EventsQueue.enqueue(promote_event);
			promote_event->Execute(this);
		}
	}
	FillDrawingList();
	pGUI->UpdateInterface();
//	pGUI->waitForClick();

}

void Restaurant::Delete_Order(int n)
{
	Order* order = nullptr, *target = nullptr;
	Queue<Order*> Q_O1, Q_O2;
	//	bool found = false;
	while (ON_LIST.DeleteFirst(order))
	{
		if (order)
		{
			if (order->GetID() == n && order->getStatus() == WAIT)
			{
				while (ORDERS_Queue.dequeue(order))
				{
					if (order->GetID() != n)
					{
						Q_O2.enqueue(order);
					}
				}

				while (Q_O2.dequeue(order))
				{
					ORDERS_Queue.enqueue(order);

				}

			}
			else
				Q_O1.enqueue(order);
		}

	}




	while (Q_O1.dequeue(order))
	{
		ON_LIST.InsertEnd(order);
	}

	pGUI->ResetDrawingList();

	FillDrawingList();
	pGUI->UpdateInterface();
	pGUI->waitForClick();
}


void Restaurant::FillDrawingList()
{
	Order* order;
	Queue<Order*> TEMPO_Queue;
	Cook* cook;
	Queue<Cook*> TEMPC_Queue;

	while (!COOKS_Queue.isEmpty())
	{
		COOKS_Queue.dequeue(cook);
		pGUI->AddToDrawingList(cook);
		TEMPC_Queue.enqueue(cook);
	}

	while (!TEMPC_Queue.isEmpty())
	{
		TEMPC_Queue.dequeue(cook);
		
		COOKS_Queue.enqueue(cook);

	}
	while (!ORDERS_Queue.isEmpty())
	{
		ORDERS_Queue.dequeue(order);
		pGUI->AddToDrawingList(order);
		TEMPO_Queue.enqueue(order);
	}
	while (!TEMPO_Queue.isEmpty())
	{
		TEMPO_Queue.dequeue(order);

		ORDERS_Queue.enqueue(order);

	}
	
}
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);



void Restaurant::AddtoORDERsLISTS(Order* po)
{
	ORDERS_Queue.enqueue(po);
	switch (po->GetType())
	{
	case TYPE_NRM:
		ON_LIST.InsertEnd(po);
		break;
	case TYPE_VIP:
		OV_LIST.enqueue(po);
		break;
	case TYPE_VGAN:
		OG_LIST.enqueue(po);
		break;
	}

	pGUI->ResetDrawingList();
	FillDrawingList();
	pGUI->UpdateInterface();
}

void Restaurant::Promote_order(int n, int ex)
{
	Order* order = nullptr, *target = nullptr;
	Queue<Order*> Q_O1, Q_O2;
	while (ON_LIST.DeleteFirst(order))
	{
		if (order)
		{
			if (order->GetID() == n && order->getStatus() == WAIT)
			{
				order->setMoney(order->GetMoney() + ex);
				order->SetType(TYPE_VIP);
				OV_LIST.enqueue(order);

			}
			else
				Q_O1.enqueue(order);
		}

	}




	while (Q_O1.dequeue(order))
	{

		ON_LIST.InsertEnd(order);
	}
	pGUI->ResetDrawingList();

	FillDrawingList();
	pGUI->UpdateInterface();
	pGUI->waitForClick();
}




