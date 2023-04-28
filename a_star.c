#include "so_long.h"

// typedef struct Node {
//     int x;
//     int y;

//     int g;
//     int h;
//     int f;

//     struct Node* parent;
// } Node;

void print_map(char **map, int x, int y)
{
    int i = 0;
    int j = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (i == y && j == x)
                printf("\x1b[32m%c\x1b[0m", map[i][j]);
            else
                printf("%c", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

int *astar(char **map, int *start, int *end, int width, int height)
{
    // Create start and end node
    Node *startNode = malloc(sizeof(Node));
    Node *endNode = malloc(sizeof(Node));

    startNode->x = start[0];
    startNode->y = start[1];
    startNode->g = 0;
    startNode->f = 0;
    startNode->h = 0;

    endNode->x = end[0];
    endNode->y = end[1];
    endNode->g = 0;
    endNode->f = 0;
    endNode->h = 0;

    // Initialize both open and closed list
    Node **open_list = malloc(sizeof(Node) * 100);
    // Node** closed_list = malloc(1000);

    // Add the start node
    open_list[0] = startNode;
    open_list[1] = NULL;

    // Adding a stop condition
    int outer_iterations = 0;
    int max_iterations = 10;

    // what squares do we search
    int adjacent_squares[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    printf("start: %d, %d\n", open_list[0]->x, open_list[0]->y);
    printf("end: %d, %d\n", endNode->x, endNode->y);

    int count = 1;
    // Loop until you find the end
    while (count > 0)
    {
        outer_iterations++;
        // Get the current node
        int index = -1;
        int i = -1;
        Node *current_node = open_list[0];
        while (open_list[++index])
            if (open_list[index]->close == 0)
            {
                printf("f : %d, case: %d %d\n", open_list[index]->f, open_list[index]->x, open_list[index]->y);
                current_node = open_list[index];
                break;
            }
        i = 0;
        while (open_list[i])
        {
            if (open_list[i]->close == 0 && open_list[i]->f <= current_node->f)
            {
                printf("use f : %d, Fc : %d case: %d %d\n", open_list[i]->f, current_node->f, open_list[i]->x, open_list[i]->y);
                current_node = open_list[i];
                open_list[index]->close = 1;
            }
            i++;
        }
        print_map(map, current_node->x, current_node->y);

        if (outer_iterations > max_iterations * 1000)
            return (NULL);

        // Set as used
        open_list[0]->close = 1;

        // Found the goal
        if (current_node->x == endNode->x && current_node->y == endNode->y)
        {
            printf("FIND\n");
            return (NULL);
        }

        // Generate children
        Node **children = malloc(5 * sizeof(Node *));

        i = 0;
        int j = 0;
        int adjacent_count = 4;
        while (--adjacent_count >= 0)
        {
            // Get node position
            int node_position_x = current_node->x + adjacent_squares[adjacent_count][0];
            int node_position_y = current_node->y + adjacent_squares[adjacent_count][1];

            // Range crit
            if (!map[node_position_y][node_position_x])
                continue;

            // Walkable
            // printf("c : %d node : %c : %d, %d\n",adjacent_count, map[node_position_y][node_position_x], node_position_x, node_position_y);
            if (map[node_position_y][node_position_x] == '1'){
                continue;}

            // New node
            Node *new_node = malloc(sizeof(Node));
            new_node->parent = current_node;
            new_node->x = node_position_x;
            new_node->y = node_position_y;
            new_node->close = 0;
            children[j] = new_node;
            // printf("add child case: %d %d\n",node_position_x, node_position_y);
            j++;
            // printf("Child born\n");
        }
        int number_of_children = j;
        if (number_of_children == 1)
        {
            printf("Go cback %d %d\n", children[0]->x, children[0]->y);
            current_node->close = 1;
            current_node = current_node->parent;
            continue;
        }

        // Loop through children

        i = 0;
        while (--number_of_children >= 0)
        {
            // Close
            if (children[number_of_children]->close == 1)
                continue;

            // Create the f, g, and h values
            children[number_of_children]->g = current_node->g + 1;
            children[number_of_children]->h = ((children[number_of_children]->x - endNode->x) * (children[number_of_children]->x - endNode->x)) + ((children[number_of_children]->y - endNode->y) * (children[number_of_children]->y - endNode->y));
            children[number_of_children]->f = children[number_of_children]->g + children[number_of_children]->h;
            printf("Child case %d %d f : %d g : %d\n", children[number_of_children]->x, children[number_of_children]->y, children[number_of_children]->f, children[number_of_children]->g);
            // Check if not inside list
            int j = 0;
            int inside = 0;
            while (open_list[j])
            {
                if (open_list[j]->x == children[number_of_children]->x && open_list[j]->y == children[number_of_children]->y)
                {
                    inside = 1;
                    break;
                }
                j++;
            }
            if (inside)
                continue;
            open_list[j] = children[number_of_children];
            open_list[j + 1] = NULL;
            count++;
        }
        //free(children);
        // printf("count : %d\n", count);
        count--;
    }
}