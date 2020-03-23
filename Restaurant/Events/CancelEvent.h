#ifndef __CancelEvent_H_
#define __CancelEvent_H_
#include"Events/Event.h"
#include"Rest/Restaurant.h"
class CancelEvent :public Event
{
protected:
    int Timestep;
    int ID;
    Order&Cancel;
public:
    CancelEvent(int et,int id,Order& c);
    void setTimestep(int t);
    int getTimestep() const;

    void setID(int d);
    int GetID() const;

    virtual void Execute(Restaurant* pRest);






};

















#endif
