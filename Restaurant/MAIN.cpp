//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include<fstream>
int main()
{

	Restaurant* pRest = new Restaurant;
	pRest->Simulation_Function();
	/*
	ifstream read("Data_File.txt");
	pRest->RunSimulation(read);
	int clk = 0;
	*/

	delete pRest;

	return 0;
}
