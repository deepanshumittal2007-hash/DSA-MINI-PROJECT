
#include <stdio.h>

#define V 8

const char *locations[V] = {
    "Main Gate",
    "Library",
    "Block 1",
    "Block 2",
    "Cafeteria",
    "Auditorium",
    "Parking",
    "Lab"
};

/* Adjacency matrix */
int graph[V][V] = {0};

void addEdge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

void displayLocations(void) {
    int i;

    printf("\n===== CAMPUS LOCATIONS =====\n");

    for (i = 0; i < V; i++) {
        printf("%d. %s\n", i, locations[i]);
    }
}

/* BFS: Find shortest path in an unweighted graph */
void BFS(int src, int dest) {
    int queue[V];
    int visited[V] = {0};
    int parent[V];
    int path[V];
    int front = 0, rear = 0;
    int i, u, count = 0;

    for (i = 0; i < V; i++) {
        parent[i] = -1;
    }

    queue[rear++] = src;
    visited[src] = 1;

    while (front < rear) {
        u = queue[front++];

        if (u == dest) {
            break;
        }

        for (i = 0; i < V; i++) {
            if (graph[u][i] == 1 && !visited[i]) {
                visited[i] = 1;
                parent[i] = u;
                queue[rear++] = i;
            }
        }
    }

    if (!visited[dest]) {
        printf("\nNo route available between %s and %s.\n",
               locations[src], locations[dest]);
        return;
    }

    u = dest;

    while (u != -1) {
        path[count++] = u;
        u = parent[u];
    }

    printf("\nShortest Route using BFS:\n");

    for (i = count - 1; i >= 0; i--) {
        printf("%s", locations[path[i]]);

        if (i > 0) {
            printf(" -> ");
        }
    }

    printf("\nNumber of edges: %d\n", count - 1);
}

/* DFS traversal helper */
void DFSUtil(int u, int visited[]) {
    int i;

    visited[u] = 1;

    for (i = 0; i < V; i++) {
        if (graph[u][i] == 1 && !visited[i]) {
            DFSUtil(i, visited);
        }
    }
}

/* Display reachable and disconnected locations */
void DFS(int src) {
    int visited[V] = {0};
    int i;

    DFSUtil(src, visited);

    printf("\nReachable Locations from %s:\n", locations[src]);

    for (i = 0; i < V; i++) {
        if (visited[i]) {
            printf("- %s\n", locations[i]);
        }
    }

    printf("\nDisconnected Locations:\n");

    {
        int found = 0;

        for (i = 0; i < V; i++) {
            if (!visited[i]) {
                printf("- %s\n", locations[i]);
                found = 1;
            }
        }

        if (!found) {
            printf("No disconnected locations. All locations are reachable.\n");
        }
    }
}

int main(void) {
    int choice, src, dest;

    /* Create campus routes */
    addEdge(0, 1);
    addEdge(0, 6);
    addEdge(1, 2);
    addEdge(1, 4);
    addEdge(2, 3);
    addEdge(2, 7);
    addEdge(3, 5);
    addEdge(4, 5);
    addEdge(6, 7);

    do {
        printf("\n=================================\n");
        printf("      CAMPUS ROUTE FINDER\n");
        printf("=================================\n");
        printf("1. Display Campus Locations\n");
        printf("2. Find Shortest Route (BFS)\n");
        printf("3. Find Reachable Locations (DFS)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                displayLocations();
                break;

            case 2:
                displayLocations();

                printf("\nEnter source location number: ");
                if (scanf("%d", &src) != 1) {
                    printf("Invalid input.\n");
                    return 1;
                }

                printf("Enter destination location number: ");
                if (scanf("%d", &dest) != 1) {
                    printf("Invalid input.\n");
                    return 1;
                }

                if (src >= 0 && src < V &&
                    dest >= 0 && dest < V) {
                    BFS(src, dest);
                } else {
                    printf("Invalid location number! Use 0 to 7.\n");
                }
                break;

            case 3:
                displayLocations();

                printf("\nEnter starting location number: ");
                if (scanf("%d", &src) != 1) {
                    printf("Invalid input.\n");
                    return 1;
                }

                if (src >= 0 && src < V) {
                    DFS(src);
                } else {
                    printf("Invalid location number! Use 0 to 7.\n");
                }
                break;

            case 4:
                printf("Thank you for using Campus Route Finder!\n");
                break;

            default:
                printf("Invalid choice! Please select 1 to 4.\n");
        }

    } while (choice != 4);

    return 0;
}

