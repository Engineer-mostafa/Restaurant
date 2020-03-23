#include "CancelEvent.h"

CancelEvent::CancelEvent(int et, int id, Order  &c):Event(et,id),Cancel(c)
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
	ID =( d > 0 && d < 1000) ? d : 0;
}

int CancelEvent::GetID() const
{
	return ID;
}

void CancelEvent::Execute(Restaurant* pRest)
{
	if (Cancel.GetType() != TYPE_NRM&&ID!=Cancel.GetID())
		return;
	else 
	{
		//Cancel->setMoney(0);
		Cancel.setStatus(DONE);
		
	}
	



	pRest->ExecuteEvents(Timestep);
}
