#include "Order.h"

#include <iostream>
using namespace std;
Order::Order()
{
}

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0 && id<1000) ? id : 0;	//1<ID<999
	type = r_Type;
	status = WAIT;
}

Order::Order(ORD_TYPE r_Type, int arrtime, int id, int size, double money)
{
	//cout << "order constructor\n";
	ID = id>0 ? id : 0;
	FinishTime = 0;
	ServTime = 0;
	status = WAIT;
	ArrTime = arrtime >= 0 ? arrtime : 0;
	Order_Size = size>0 ? size : 0;
	totalMoney = money>0 ? money : 0;
	type = r_Type;
}
Order::~Order()
{
}

void Order::SetType(ORD_TYPE t)
{
	type = t;
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}





void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

void Order::setMoney(double m)
{
	totalMoney = m;
}

double Order::GetMoney()
{
	return totalMoney;
}

bool Order::operator<(const Order& order)
{
	int p1 = totalMoney / (ArrTime* Order_Size);
	int p2 = order.totalMoney / (order.ArrTime * order.Order_Size);
	if (p1 < p2)
		return true;
	return false;
}

bool Order::operator==(const int& n)
{
	if (ID == n)
		return true;
	return false;
}
