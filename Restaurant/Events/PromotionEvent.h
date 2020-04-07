#pragma once
#include"Event.h"
#include"..\Rest\Order.h"
#include "..\Rest\Restaurant.h"
class PromotionEvent :public Event
{
protected:
	double ExMoney;
	Order Promote;
public:
	PromotionEvent(int ts, int id, double ex);
	void setExMoney(double E);
	double GetExMoney() const;
	virtual void Execute(Restaurant* pRest);
	
};

