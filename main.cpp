#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

void calculateMinSteps(const vector<vector<int>>& connections, int origin, vector<int>& stepCount)
{
    size_t vertexCount = connections.size();
    stepCount.assign(vertexCount, INT_MAX);
    stepCount[origin] = 0;

    queue<int> traversalQueue;
    traversalQueue.push(origin);

    // breadth - first traversal of the graph
    while (!traversalQueue.empty())
    {
        int current = traversalQueue.front();
        traversalQueue.pop();

        // processing neighboring vertices
        for (int neighbor : connections[current])
            if (stepCount[neighbor] == INT_MAX)
            {
                stepCount[neighbor] = stepCount[current] + 1;
                traversalQueue.push(neighbor);
            }
    }
}

int main()
{
    ifstream input("graph.txt");

    int nodeCount = 0;
    int edgeCount = 0;
    int originNode = 0;

    input >> nodeCount >> edgeCount; // reading the number of vertices and edges

    vector<vector<int>> network(nodeCount);
    vector<int> pathLengths(nodeCount);

    // reading edges 
    for (int i = 0; i < edgeCount; ++i)
    {
        int from = 0;
        int to = 0;

        input >> from >> to;

        network[from].push_back(to);
        network[to].push_back(from);
    }

    input >> originNode;  // reading starting vertex

    calculateMinSteps(network, originNode, pathLengths); // distances calculation

    for (size_t nodeIndex = 0; nodeIndex < pathLengths.size(); ++nodeIndex)
        cout << pathLengths[nodeIndex] << endl;

    return 0;
}
