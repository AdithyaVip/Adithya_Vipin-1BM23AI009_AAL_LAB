INPUT -
#include <stdio.h>
#include <limits.h>

#define V 4

int graph[V][V] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

int minCost = INT_MAX;
int bestPath[V + 1];

void tsp(int city, int visited[], int path[], int count, int cost) {
    if (count == V) {
        if (graph[city][0]) { // Can return to start?
            int totalCost = cost + graph[city][0];
            if (totalCost < minCost) {
                for (int i = 0; i < V; i++) bestPath[i] = path[i];
                bestPath[V] = 0;
                minCost = totalCost;
            }
        }
        return;
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i] && graph[city][i]) {
            int nextCost = cost + graph[city][i];
            if (nextCost < minCost) { // Prune: skip if already worse
                visited[i] = 1;
                path[count] = i;
                tsp(i, visited, path, count + 1, nextCost);
                visited[i] = 0; // Backtrack
            }
        }
    }
}

int main() {
    int visited[V] = {0};
    int path[V + 1];

    visited[0] = 1;
    path[0] = 0;

    tsp(0, visited, path, 1, 0);

    printf("Minimum cost: %d\nPath: ", minCost);
    for (int i = 0; i <= V; i++)
        printf("%d ", bestPath[i]);
    printf("\n");

    return 0;
}



 OUTPUT -

Minimum cost: 80
Path: 0 1 3 2 0 

