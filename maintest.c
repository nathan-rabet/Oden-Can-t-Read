#include "src/ml/struct/networks.h"

int main()
{
    size_t npl[] = {2, 3, 4, 1};
    char afpl[] = {0, 2, 2, 2};
    struct Networks *net = generateRandomNetworks(4, npl, afpl);

    SaveNetworksToJSON(net,"ptin.json");

    struct Networks *net2 = LoadNetworksFromJSON("ptin.json");

    return 0;
}