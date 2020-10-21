#include <stdio.h>
#include <stdlib.h>

#include "src/ml/network.h"

int main()
{
	char* file_name = "data/networks/test.json";

	struct Network net = LoadNetworkFromJSON(file_name);

	double dataInput[2] = {1,2};

	double *output = CalculateNetworkOutput(net, dataInput);

	for (int i = 0; i < networkNbOutput(net); i++)
	{
		printf("%lf\n",output[i]);
	}
	
}