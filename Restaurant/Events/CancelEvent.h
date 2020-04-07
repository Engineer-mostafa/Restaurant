#ifndef __CancelEvent_H_
#define __CancelEvent_H_
#include"Event.h"
#include"..\Rest\Order.h"
#include"..\Rest\Restaurant.h"

class CancelEvent :public Event
{
protected:
    int Timestep;
    int ID;
   // Order Cancel;
public:
    CancelEvent(int et, int id);
    // CancelEvent(int et,int id,Order& c);
    void setTimestep(int t);
    int getTimestep() const;

    void setID(int d);
    int GetID() const;

    virtual void Execute(Restaurant* pRest);






};

















#endif
