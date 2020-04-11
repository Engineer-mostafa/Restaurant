#include "Cook.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
Cook::Cook()
{
}


Cook::~Cook()
{
}

Cook::Cook(char ty, int s)
{
	ID = rand() % 50 + 1;
	cout << ID;
	speed = s;
	switch (ty)
	{
	case 'N':
		type = TYPE_NRM;
		break;
	case'G':
		type = TYPE_VGAN;
		break;
	case 'V':
		type = TYPE_VIP;
		break;
	/*case'I':
		type = TYPE_INDN;
		break;
	case'C':
		type = TYPE_CHNS;*/
	}
}

int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

bool Cook::operator<(const Cook& cook)
{
	if (ID < cook.GetID())
		return true;
	return false;

}


