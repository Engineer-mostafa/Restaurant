#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_
#include "..\Events\Event.h"
#include  "..\Rest\Order.h"

//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	//int OrdDistance;	//order distance
	ORD_TYPE OrdType;		//order type: Normal, vegan, VIP	
	Order* order;
	double OrdMoney;//Total order money
	int order_size;                 	
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);
	//Add more constructors if needed
	ArrivalEvent(int eTime, int oID, char oType,int,double);

	virtual void Execute(Restaurant *pRest);	//override execute function

};

#endif