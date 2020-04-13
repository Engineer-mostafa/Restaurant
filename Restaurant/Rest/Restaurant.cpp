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

void Restaurant::RunSimulation()
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

		break;
	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
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
	for (int i = 0; i < Total; i++)
	{
		if (i < Num_Cooks_N)
		{
			Cook* cook = new Cook('N', N_speed);
			COOKS_Queue.enqueue(cook);
		}
		else if (i < Num_Cooks_V + Num_Cooks_N)
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
	read >> NUM_ORD >> NORM_BREAK >> VIP_BRAEK >> VEG_BREAK;
	read >> AutoP >> numberofevents;
	char event_Type;
	char order_Type;
	int id, ord_size, etime; double money;
	Order* order;
	ArrivalEvent* arr_event;
	for (int i = 0; i < numberofevents; i++)
	{
		read >> event_Type;
		if (event_Type == 'R')
		{
			read >> order_Type >> etime >> id >> ord_size >> money;
			arr_event = new ArrivalEvent(etime, id, order_Type, ord_size, money);
			EventsQueue.enqueue(arr_event);

		}
		else if (event_Type == 'X')
		{
			read >> etime >> id;
			CancelEvent* cancel_event = new CancelEvent(etime, id);
			EventsQueue.enqueue(cancel_event);

		}
		else if (event_Type == 'P')
		{
			read >> etime >> id >> money;
			PromotionEvent* promote_event = new PromotionEvent(etime, id, money);
			EventsQueue.enqueue(promote_event);
		}
	}

}

void Restaurant::Delete_Order(int n)
{
	Order* order = nullptr;
	Queue<Order*> Q_O1, Q_O2;

	while (ON_LIST.DeleteFirst(order)) //looking for the required order
	{
		if (order)
		{
			if (order->GetID() == n && order->getStatus() == WAIT) //check if we can delete the order
			{
				Num_WOrd_N--;
				while (ORDERS_Queue.dequeue(order))               //delete the order from the orders list
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

		ON_LIST.InsertEnd(order); //refill the normal orders list
	}

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




void Restaurant::AddtoORDERsLISTS(Order* po)
{
	ORDERS_Queue.enqueue(po);      //a general list of orders to keep them sorted by their arrival time
	switch (po->GetType())//putting every order in its type list 
	{
	case TYPE_NRM:
		ON_LIST.InsertEnd(po);
		wait.enqueue(po);
		Num_wait++;
		Num_WOrd_N++;
		break;
	case TYPE_VIP:
		OV_LIST.enqueue(po);
		wait.enqueue(po);
		Num_wait++;
		Num_WOrd_V++;
		break;
	case TYPE_VGAN:
		OG_LIST.enqueue(po);
		wait.enqueue(po);
		Num_wait++;
		Num_WOrd_G++;
		break;
	}

}

void Restaurant::Promote_order(int n, int ex)
{
	Order* order = nullptr;
	Queue<Order*> Q_O1;
	while (ON_LIST.DeleteFirst(order))
	{
		if (order)
		{
			if (order->GetID() == n && order->getStatus() == WAIT) //check if we can promote the order
			{
				order->setMoney(order->GetMoney() + ex);
				order->SetType(TYPE_VIP);
				OV_LIST.enqueue(order);
				Num_WOrd_N--;
				Num_WOrd_V++;
			}
			else
				Q_O1.enqueue(order);
		}
	}
	while (Q_O1.dequeue(order))
	{

		ON_LIST.InsertEnd(order);
	}

}




void Restaurant::Simulation_Function()
{
	//nessasry initialization
	Num_wait = 0;
	Num_WOrd_N = 0;
	Num_WOrd_G = 0;
	Num_WOrd_V = 0;
	Queue <Order*> done;
	int num_cook = Num_Cooks_N + Num_Cooks_V + Num_Cooks_G;
	pGUI = new GUI;
	//reading from the textfile
	ifstream read("Data_File.txt");
	int CurrentTimeStep = 1;
	//calling loading function
	Load_Data(read);
	//clearing the screen
	pGUI->ResetDrawingList();
	Order* temp = new Order;









	while (!EventsQueue.isEmpty() || !ON_LIST.isEmpty() || !OG_LIST.isEmpty() ||
		!OV_LIST.isEmpty() || !InService_N.isEmpty() ||
		!InService_V.isEmpty() || !InService_G.isEmpty())
	{
		//it executes the events of this current step as long as there are any
		if (!EventsQueue.isEmpty())
			ExecuteEvents(CurrentTimeStep);
		//each timestep
		//if there are any waiting vegan orders we move them to in service 
		if (!OG_LIST.isEmpty())
		{
			OG_LIST.dequeue(temp);
			InService_G.enqueue(temp);
			temp->setStatus(SRV);
			Num_WOrd_G--;
		}
		////if there are any waiting VIP orders we move them to in service 
		if (!OV_LIST.isEmpty())
		{
			OV_LIST.dequeue(temp);
			temp->setStatus(SRV);
			InService_V.enqueue(temp);
			Num_WOrd_V--;
		}
		//if there are any waiting normal orders we move them to in service 
		if (!ON_LIST.isEmpty())
		{
			ON_LIST.DeleteFirst(temp);
			temp->setStatus(SRV);
			InService_N.enqueue(temp);
			Num_WOrd_N--;
		}
		//every five timesteps
		if (CurrentTimeStep % 5 == 0)
		{
			////if there are any in service vegan orders we move them to finished 
			if (!InService_G.isEmpty())
			{
				InService_G.dequeue(temp);
				done.enqueue(temp);
				temp->setStatus(DONE);
			}
			////if there are any in service normal orders we move them to finished
			if (!InService_N.isEmpty())
			{
				InService_N.dequeue(temp);
				done.enqueue(temp);
				temp->setStatus(DONE);
			}
			////if there are any in service VIP orders we move them to finished
			if (!InService_V.isEmpty())
			{
				InService_V.dequeue(temp);
				done.enqueue(temp);
				temp->setStatus(DONE);
			}
		}

		pGUI->ResetDrawingList();
		FillDrawingList();

		//writing in the status bar number of available cooks of each type and number of waiting orders of each type
		string message;
		message = "TS: " + to_string(CurrentTimeStep) + "       " + "#C: " + to_string(num_cook) + "      " + "#N_C: " + to_string(Num_Cooks_N) + "    " + "#V_C: " + to_string(Num_Cooks_V) + "       " + "#G_C: " + to_string(Num_Cooks_G);
		message = message + "        " + "#W_ORD: " + to_string(Num_WOrd_N + Num_WOrd_V + Num_WOrd_G) + "     " + "#N_ORD: " + to_string(Num_WOrd_N) + "     " + "#G_ORD: " + to_string(Num_WOrd_G) + "    " + "#V_ORD: " + to_string(Num_WOrd_V);
		pGUI->PrintMessage(message);
		//drawing the cooks and orders on the screen in their specific position
		pGUI->UpdateInterface();
		//waiting for mouse click to go to the next timestep
		pGUI->waitForClick();
		CurrentTimeStep++;
		//clearing the screen from the previous timestep
	}
	//nessasry pointers deleting
	
}