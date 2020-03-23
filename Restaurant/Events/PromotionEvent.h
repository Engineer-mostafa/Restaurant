#pragma once
#include"Events/Event.h"
#include"Rest/Order.h"
class PromotionEvent :public Event
{
protected:
	double ExMoney;
	Order &Promote;
public:
	PromotionEvent(int ts, int id,Order &p, double ex);
	void setExMoney(double E);
	double GetExMoney() const;
	virtual void Execute(Restaurant* pRest);
	
};

