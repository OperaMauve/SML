/*
 * Starter file for Assignment 1 Part 1
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Lachlan Rowles <l.rowles@unimelb.edu.au>
 * Implementation by YOUR NAME HERE.
 * The type definitions for a graph, including edges, edge lists, and the graph
 * itself. Graph implemented with adjacency lists.
 * Functions for creating and manipulating the graph.
 */

 #ifndef EDGE_T
 #define EDGE_T
 /* Definition of an edge. */
 typedef struct edge {
   int start;
   int end;
   int length;
 }edge_t;
 #endif
 
 #ifndef EDGELIST_T
 #define EDGELIST_T
 /* The linked list of edges. */
 typedef struct edgeList {
   edge_t *edge;
   struct edgeList *next;
 }edgeList_t;
 #endif
 
 
 #ifndef GRAPH_T
 #define GRAPH_T
 /* Definition of a graph. */
 typedef struct graph {
   int numLakes;
   int numRivers;
   // List of adjacency lists, indexable by the `from` lake
   edgeList_t **adjLists;
 }graph_t;
 #endif
 
 
 /* Generates a new graph, with `numLakes` adjacency lists allocated */
 graph_t *newGraph(int numLakes, int numRivers);
 
 
 /* Adds an edge to the given adjacency list */
 void addEdge(edgeList_t **adjList, int fromLake, int toLake, int length);
 
 /* Get a new empty list. */
 edgeList_t *newlist(edge_t *edge);
 
 /* Add an item to the head of the list. Returns the new list. */
 edgeList_t *prependList(edgeList_t *list,  edge_t *edge);
 
 /* Gets the first item from the list. */
 edge_t *peekHead(edgeList_t *list);
 
 /* Takes the first item from the list, updating the list pointer and returns
   the item stored. */
 edge_t *deleteHead(edgeList_t **list);
 
 /* Free all list items. */
 void freeList(edgeList_t *list);
 
 /* Frees the given graph and all of the adjacency lists */
 void freeGraph(graph_t *graph);
 
 /* =====================================================================
    This skeleton/program is compiled by the comp20007 teaching team,
    the university of Melbourne.
    Last Updated: 24/02/2025
    ================================================================== */
 
 int cycleCheck(graph_t *graph) {
     // Implement function here
     // Allocate space for visited graph
     int* visited = (int*)malloc(sizeof(int)*graph->numLakes);
     if (visited == NULL){
         printf("Out of memory!");
         exit(1);
     }
     // Set all to unvisited
     for (int i = 0; i < graph->numLakes; i++){
         visited[i] = 0;
     }
     // For every node run dfs to find cycle
     for (int i = 0; i < graph->numLakes; i++){
         if (visited[i] == 0){
             // They are not visited >:(
             if (dfs(i, -1, &visited, graph) == 1){
                 // Exit as soon as cycle is found
                 free(visited);
                 return 1;
             }
         }
     }    
     // Free memory
     free(visited);
     return 0;
 }
 
 int dfs(int start, int parent, int **visited, graph_t *graph){
     // Mark the current one as visited
     (*visited)[start] = 1;
 
     // Find the starting point.
     edgeList_t curr = graph->adjLists[start];
 
     while(curr.edge != NULL){
         if ((*visited)[curr->edge.end] == 0){
             if (dfs(curr->edge.end, start, visited, graph)){
                 return 1;
             }
         } else if (curr->edge.end != parent){
             return 1;
         }
         curr = curr.next;
     }
 
     return 0;
 }