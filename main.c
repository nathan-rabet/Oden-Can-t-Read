#include <stdio.h>
#include <stdlib.h>

#include "src/ml/network.h"

int main()
{
	char* file_name = "data/networks/test.json";

	struct Network *network = LoadNetworkFromJSON(file_name);
	printf("Done!");
}