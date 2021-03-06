#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
}

ArrivalEvent::ArrivalEvent(int eTime, int oID, char ty, int size, double money):Event(eTime, oID)
{
	OrdMoney = money > 0 ? money : 0;
	order_size = size > 0 ? size : 0;
	switch (ty)
	{
	case 'N':
		OrdType = TYPE_NRM;
		break;
	case'G':
		OrdType = TYPE_VGAN;
		break;
	case 'V':
		OrdType = TYPE_VIP;
		break;
	}
}


void ArrivalEvent::Execute(Restaurant* pRest)
{
	Order* new_order = new Order(OrdType, EventTime, OrderID,order_size,OrdMoney);

	pRest->AddtoORDERsLISTS(new_order);
	
}
