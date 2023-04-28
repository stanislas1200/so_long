#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 10
#define WALL '1'
#define EMPTY '0'
#define START 'P'
#define END 'E'
#define COLLECTIBLE 'C'

void print_map(char map[][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int write_map_to_file(char map[][WIDTH], int width, int height, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        perror("Failed to open file");
        return 1;
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (fputc(map[i][j], fp) == EOF)
            {
                perror("Failed to write to file");
                fclose(fp);
                return 1;
            }
        }
        if (i < height - 1 && fputc('\n', fp) == EOF)
        {
            perror("Failed to write to file");
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void generate_map(char map[][WIDTH])
{
    srand(time(NULL));

    // Fill with walls
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
            {
                map[i][j] = WALL;
            }
            else
            {
                if (rand() % 100 < 20)
                    map[i][j] = WALL;
                else
                    map[i][j] = EMPTY;
            }
        }
    }

    // Place start and end positions
    int start_x = rand() % (WIDTH - 2) + 1;
    int start_y = rand() % (HEIGHT - 2) + 1;
    int end_x, end_y;
    do
    {
        end_x = rand() % (WIDTH - 2) + 1;
        end_y = rand() % (HEIGHT - 2) + 1;
    } while (end_x == start_x && end_y == start_y);

    map[start_y][start_x] = START;
    map[end_y][end_x] = END;

    // Place collectibles
    int num_collectibles = (WIDTH + HEIGHT) / 2;
    for (int i = 0; i < num_collectibles; i++)
    {
        int collectible_x, collectible_y;
        do
        {
            collectible_x = rand() % (WIDTH - 2) + 1;
            collectible_y = rand() % (HEIGHT - 2) + 1;
        } while (collectible_x == start_x && collectible_y == start_y || collectible_x == end_x && collectible_y == end_y || map[collectible_y][collectible_x] == COLLECTIBLE);

        map[collectible_y][collectible_x] = COLLECTIBLE;
    }
}

int main()
{
    char map[HEIGHT][WIDTH];
    generate_map(map);
    print_map(map);
    if (write_map_to_file(map, WIDTH, HEIGHT, "./data/map/map.txt") != 0)
    {
        fprintf(stderr, "Failed to write map to file\n");
        return 1;
    }

    return 0;
}
