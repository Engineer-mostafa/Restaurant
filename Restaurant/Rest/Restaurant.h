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

	int NORM_BREAK, VIP_BRAEK, VEG_BREAK;

	int Num_Cooks_N, Num_Cooks_V, Num_Cooks_G;
	int AutoP, NUM_ORD;
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Restaurant();
	void RunSimulation(ifstream& read);
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void Load_Data(ifstream& read);
	//void setCooks(int s1,int s2,int s3);
	//void setOrders();


	void Delete_Order(int n);

	void FillDrawingList();

	void Just_A_Demo(ifstream& read);

	void Load_Func(ifstream& read);
	void AddtoORDERsLISTS(Order* po);
	void Promote_order(int n,int);
	//
	// TODO: Add More Member Functions As Needed
	//


/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	//void Just_A_Demo(ifstream& read);	//just to show a demo and should be removed in phase1 1 & 2
	//void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

/// ================================================================================================== 



};

#endif