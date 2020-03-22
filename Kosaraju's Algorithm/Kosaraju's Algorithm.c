#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 100 //arbitrarily chosen, may be freely changed as needed
#define MAX_NUM_VERTICES 10000 //also arbitrarily chosen

struct vertices_s {
    int visited;
    int deg;
    int adj[MAX_DEGREE];
} vertices[MAX_NUM_VERTICES]; //this struct array is used to save the information of each vertex

struct stack_s {
    int top;
    int items[MAX_NUM_VERTICES];
} stack = {-1, {}};

void stack_push(int v) {
    stack.top++;
    if (stack.top < MAX_NUM_VERTICES)
	stack.items[stack.top] = v;
    else {
		printf("Stack is full!\n");
		exit(1);
    }
}

int stack_pop() {
    return stack.top < 0 ? -1 : stack.items[stack.top--];
}

void dfs(int v, int transpose, int SCC[MAX_NUM_VERTICES], int idx) {
    int i, c, n;
    vertices[v].visited = 1;
    for (i = 0, c = vertices[v].deg; i < c; ++i) {
		n = vertices[v].adj[i] * transpose;
		if (n > 0)
		    /* n - 1 because vertex indexing begins at 0 */
		    if (!vertices[n - 1].visited)
			dfs(n - 1, transpose, SCC, idx);
    }
    if (transpose < 0)
		stack_push(v);
    else{
		SCC[v+1] = idx;
		printf("%d ", v + 1);
    }
}

void reset_visited(int V) {
    int i;
    for (i = 0; i < V; ++i)
	 vertices[i].visited = 0;
}

void order_pass(int V, int SCC[MAX_NUM_VERTICES]) {
    int i;
    for (i = 0; i < V; ++i){
		if (!vertices[i].visited)
	    	dfs(i, -1, SCC, 0);
    }
}

void scc_pass(int SCC[MAX_NUM_VERTICES]) {
    int i = 0, v;
    while((v = stack_pop()) != -1) {
		if (!vertices[v].visited) {
		    printf("scc %d: ", ++i);
		    dfs(v, 1, SCC, i);
		    printf("\n");
		}
    }
}

int main(void) {
	int V, E; //assume that it is an unweighted directed graph
	// for this implementation, vertex's label starts with 1, not zero.
	scanf("%d %d", &V, &E); //number of vertices and edges
	for(int i = 0; i<V; i++){
		vertices[i].visited = 0; //for all of the vertices, initialize its visited vertex(es)
		vertices[i].deg = 0; //and degree as 0
	}
	int a, b; 
	int SCC[V+1];
	for(int i = 0; i<E; i++){
		scanf("%d %d", &a, &b);	//a and b represents an edge from a to b
		vertices[a-1].deg++;
		vertices[b-1].deg++;
		vertices[a-1].adj[vertices[a-1].deg-1] = b;
		vertices[b-1].adj[vertices[b-1].deg-1] = -a; //for incoming edge, set it as negative. 
	}
    order_pass(V, SCC);
    reset_visited(V);
    scc_pass(SCC);
    for(int i = 1; i<=V; i++){
    	printf("vertex %d belongs to SCC %d\n",i, SCC[i]);
    }
    return 0;
}
