#include "CancelEvent.h"

CancelEvent::CancelEvent(int et, int id):Event(et,id)
{

}

void CancelEvent::setTimestep(int t)
{
	Timestep =t>0?t:0;
}

int CancelEvent::getTimestep() const
{
	return Timestep;
}

void CancelEvent::setID(int d)
{
	OrderID =( d > 0 && d < 1000) ? d : 0;
}

int CancelEvent::GetID() const
{
	return OrderID;
}

void CancelEvent::Execute(Restaurant* pRest)
{
	 pRest->Delete_Order(OrderID);

}
