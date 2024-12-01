#include "graph.h"

/*
 * A basic menu based structure has been provided
 */

int main(int argc, char *argv[])
{
    

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    Graph *graph = readGraph(argv[1]);
    createAdjacencyList(graph);

    int choice;
    // int startVertex = 0;
    int startVertext = 1;

    do
    {

        // Display the options
        prompt();

        // Get user input
        printf("Enter a Choice: ");
        scanf("%d", &choice);

        /*
         * You will need to add all the cases here.
         * Call the relevant functions in each case.
         * Make sure to handle invalid inputs or edge cases.
         */

        switch (choice) {
            case 1:
                // Code for case 1
                displayAdjacencyList(graph);
                break;
            case 2:
                // Code for case 2
                bfs(graph, startVertext);
                break;
            case 3:
                // Code for case 3
                dfs(graph, startVertext);
                break;
            case 4:
                // Code for case 4
                dijkstra(graph, startVertext);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                // Code for default case
                break;
        }

    } while (true);
    freeGraph(graph); 

    return 0;
}
