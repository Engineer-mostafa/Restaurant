#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\LinkedPQueue.h"
#include "..\Generic_DS\ListADT.h"
#include "..\Events\Event.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancelEvent.h"
#include "..\Events\PromotionEvent.h"
#include "Order.h"
#include "Cook.h"
#include<fstream>

// it is the maestro of the project
class Restaurant
{
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	Queue<Order*> wait;

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2

	ListADT<Order*> ON_LIST;
	Queue<Order*> OG_LIST;
	LinkedPQueue<Order*> OV_LIST;
	//Important: This is just for demo
	/// ==>

	Queue<Order*> ORDERS_Queue;
	Queue<Cook*> COOKS_Queue;

	Queue<Cook*> CV_Queue;
	Queue<Cook*> CG_Queue;
	Queue<Cook*> CN_Queue;


	Queue<Order*> wait_N;
	Queue<Order*> wait_V;

	int NORM_BREAK, VIP_BRAEK, VEG_BREAK;

	int Num_Cooks_N, Num_Cooks_V, Num_Cooks_G;
	int AutoP, NUM_ORD;
	int Num_WOrd_N, Num_WOrd_G, Num_WOrd_V;
	int Num_wait;
	//
	// TODO: Add More Data Members As Needed
	//
	Queue<Order*> InService_N;
	Queue<Order*> InService_V;
	Queue<Order*> InService_G;
	//Queue<Order*> Finished_N;
	//Queue<Order*> Finished_V;
	//Queue<Order*> Finished_G;

public:

	Restaurant();
	~Restaurant();

	void ExecuteEvents(int CurrentTimeStep);	//executes all events at current timestep
	void RunSimulation();

	void Load_Data(ifstream& read);

	//	void RunSimulation();

	void Delete_Order(int n);
	void Promote_order(int n, int);

	void FillDrawingList();



	void AddtoORDERsLISTS(Order* po);
	//
	// TODO: Add More Member Functions As Needed
	//

	void Simulation_Function();
	/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	//void Just_A_Demo(ifstream& read);	//just to show a demo and should be removed in phase1 1 & 2
	//void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

	/// ================================================================================================== 



};

#endif