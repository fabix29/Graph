/*parcurgerge  graf cu DFS/BFS*/

//Imi cer scuze in avans

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
} NODE;

typedef struct Graph
{
    int vertices;
    int* visited;
    NODE** adjacency_lists;
} GPH;

NODE* create_node(int v)
{
    NODE* new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH* create_graph(int vertices)
{
    GPH* graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE*));
    graph->visited = malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GPH* graph, int src, int dest)
{
    NODE* new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(int num_vertices, int num_edges, GPH* graph)
{
    int src, dest;
    printf("adauga %d muchii (de la 0 la %d)\n", num_edges, num_vertices - 1);

    for (int i = 0; i < num_edges; i++)
    {
        scanf_s("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int is_empty(NODE* queue)
{
    return queue == NULL;
}

void enqueue(NODE** queue, int data)
{
    NODE* new_node = create_node(data);

    if (*queue == NULL)
    {
        *queue = new_node;
    }
    else
    {
        NODE* temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE** queue)
{
    int data = (*queue)->data;
    NODE* temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void wipe_visited_list(GPH* graph, int num_vertices)
{
    for (int i = 0; i < num_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void DFS(GPH* graph, int vertex)
{
    NODE* temp = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL)
    {
        int connected = temp->data;
        if (graph->visited[connected] == 0)
        {
            DFS(graph, connected);
        }
        temp = temp->next;
    }
}

void BFS(GPH* graph, int start)
{
    NODE* queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE* temp = graph->adjacency_lists[current];
        while (temp)
        {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main()
{
    int num_vertices;
    int num_edges;
    int starting_vertex;

    printf("cate noduri are graful? ");
    scanf_s("%d", &num_vertices);

    printf("cate muchii are graful? ");
    scanf_s("%d", &num_edges);

    GPH* graph = create_graph(num_vertices);
    insert_edges(num_vertices, num_edges, graph);

    printf("de unde plecam in DFS? ");
    scanf_s("%d", &starting_vertex);
    printf("parcurgere cu DFS: ");
    DFS(graph, starting_vertex);

    wipe_visited_list(graph, num_vertices);

    printf("\nde unde plecam in BFS? ");
    scanf_s("%d", &starting_vertex);
    printf("parcurgere cu BFS: ");
    BFS(graph, starting_vertex);

    printf("\n");
    return 0;
}
