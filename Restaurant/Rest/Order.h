#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	int Order_Size;
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order();
	Order(int ID, ORD_TYPE r_Type);
	Order(ORD_TYPE type, int artime,int id, int size, double money);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;
	void SetType(ORD_TYPE t);

	

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;

	void setMoney(double m);
	double GetMoney();
	void SetArrTime(int t);
	int GetArrTime()const;

	void SetServTime(int t);
	int GetServTime()const;

	void SetFinishTime(int t);
	int GetFinishTime()const;

	void SetOrder_Size(int s);
	int GetOrder_Size()const;
	bool operator<(const Order& order);
	bool operator==(const int&);
	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif