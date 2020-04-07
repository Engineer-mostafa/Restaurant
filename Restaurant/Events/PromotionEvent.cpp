#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(int ts, int id,double ex=0):Event(ts,id)
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
	
	pRest->Promote_order(OrderID,ExMoney);
}
