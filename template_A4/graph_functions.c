#include "graph.h"

/* function will display the primary user interface
    This is already done for you*/
void prompt(void)
{

    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename)
{
    // Read the file
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }
    // Read the number of vertices by reading how many lines there are in the file
    int numVertices = getNumVertices(filename);
    if (numVertices == -1)
    {
        printf("Error getting number of vertices.\n");
        fclose(file);
        return NULL;
    }

    // Create the graph
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if(!graph){
        printf("Memory allocation failed for graph.\n");
        fclose(file);
        return NULL;
    }
    graph->numVertices = numVertices;

    // Initialize the adjacency matrix and the adjacency list
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            graph->adjMatrix[i][j] = 0;
        }
        graph->adjList[i] = NULL;
    }

    fclose(file);
    return graph;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    // Implement the function logic here
    Node *newNode = (Node *)malloc(sizeof(Node));
    if(!newNode){
        printf("Memory allocation failed for node.\n");
        return NULL;
    }
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    // Loop over the adjacency list
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%d: ", i);
        Node *current = graph->adjList[i];
        while(current != NULL){
            // Print the vertex number and the weight of the edge
            printf("-> %d(%d) ", current->vertex, graph->adjMatrix[i][current->vertex]);
            current = current->next;
        }
        printf("NULL\n");
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{
    // Loop over the rows of the adjacency matrix
    for (int i = 0; i < graph->numVertices; i++){
        // Loop over the columns of the adjacency matrix
        for (int j = 0; j < graph->numVertices; j++){
            // If the value is not 0, add the edge to the graph list
            if(graph->adjMatrix[i][j] != 0){
                Node *newNode = createNode(j);
                newNode->next = graph->adjList[i];
                graph->adjList[i] = newNode;
            }
        }
    }
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex)
{
    // Initialize visited array
    bool *visitedIndex = (bool *)malloc(graph->numVertices * sizeof(bool));
    if(visitedIndex){
        for (int i = 0; i < graph->numVertices; i++)
        {
            visitedIndex[i] = false;
        }
    }

    // Initialize queue
    int queue[graph->numVertices];
    int front = 0;
    int rear = 0;

    // Enqueue the start vertex
    queue[rear++] = startVertex;
    visitedIndex[startVertex] = true;

    // Process the queue
    while(front < rear){
        // Dequeue the front vertex
        int currentVertex = queue[front++];
        printf("%d ", currentVertex); // Print the current vertex

        // Process the neighbors of the current vertex
        Node *current = graph->adjList[currentVertex];
        while(current != NULL){
            int neighbor = current->vertex;
            if(!visitedIndex[neighbor]){
                queue[rear++] = neighbor; // Enqueue the neighbor
                visitedIndex[neighbor] = true; // Mark the neighbor as visited
            }
            current = current->next;
        }
    }
    printf("\n");
    free(visitedIndex);

}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex)
{
    // Initialize visited array
    bool *visitedIndex = (bool *)malloc(graph->numVertices * sizeof(bool));
    if(visitedIndex){
        for (int i = 0; i < graph->numVertices; i++)
        {
            visitedIndex[i] = false;
        }
    }

    // Create a stack
    int stack[graph->numVertices];
    int top = -1;

    // Push the start vertex
    stack[++top] = startVertex;
    visitedIndex[startVertex] = true;

    while(top >= 0){
        // Pop the top vertex
        int currentVertex = stack[top--];
        printf("%d ", currentVertex); // Print the current vertex

        // Process the neighbors of the current vertex
        if(!visitedIndex[currentVertex]){
            printf("%d ", currentVertex);
            visitedIndex[currentVertex] = true;

            // Push the neighbors of the current vertex
            Node *current = graph->adjList[currentVertex];
            while(current != NULL){
                int neighbor = current->vertex;
                if(!visitedIndex[neighbor]){
                    stack[++top] = neighbor;
                }
            }
            current = current->next; // Move to the next neighbor
        }
    }
    printf("\n");
    free(visitedIndex);
}

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
    // Implement the function logic here
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    if(graph == NULL){
        return;
    }
    // Free the adjacency list
    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *current = graph->adjList[i];
        while(current != NULL){
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    // Free the graph
    free(graph);
}


/**
 * 
 */

int getNumVertices(const char *filename){
    int numVertices = 0;
    char line[256];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }
    while (fgets(line, sizeof(line), file) != NULL)
    {
        numVertices++;
    }
    return numVertices;
}