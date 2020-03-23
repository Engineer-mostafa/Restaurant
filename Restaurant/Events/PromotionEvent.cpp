#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(int ts, int id, Order& p,double ex=0):Event(ts,id),Promote(p)
{
	setExMoney(ex);
}

void PromotionEvent::setExMoney(double E)
{
	ExMoney = E > 0 ? E : 0;
}

double PromotionEvent::GetExMoney() const
{
	return ExMoney;
}

void PromotionEvent::Execute(Restaurant* pRest)
{
	if (Promote.getStatus() != DONE && Promote.GetType() == TYPE_NRM)
	{
		Promote.SetType(TYPE_VIP);
		//Promote.setExtraMoney(ExMoney);

	}
	else
	{
		return;
	}
}
