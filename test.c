#include <stdio.h>
#include <string.h>


char get_wall_tile(char map[][21], int i, int j) {
    char tile = map[i][j];
    
    if (tile == '1') {
        // Check neighboring tiles to determine wall tile
        if (i > 0 && ((map[i-1][j] < '0' || map[i-1][j] > '9'))) { // Check top tile
            if (j > 0 && (map[i][j-1] < '0' || map[i][j-1] > '9')) { // Check left tile
                tile = '2';
            } else if (j < 19 && (map[i][j+1] < '0' || map[i][j+1] > '9')) { // Check right tile
                tile = '4';
            } else {
                tile = '3';
            }
        }
        else if (i < 9 && (map[i+1][j] < '0' || map[i+1][j] > '9')) { // Check bottom tile
            if (j > 0 && (map[i][j-1] < '0' || map[i][j-1] > '9')) { // Check left tile
                tile = '7';
            } else if (j < 19 && (map[i][j+1] < '0' || map[i][j+1] > '9')) { // Check right tile
                tile = '9';
            } else {
                tile = '8';
            }
        }
        else if (j > 0 && (map[i][j-1] < '0' || map[i][j-1] > '9')) { // Check left tile
            tile = '0';
        }
        else if (j < 19 && (map[i][j+1] < '0' || map[i][j+1] > '9')) { // Check right tile
            tile = '6';
        }
        else tile = '5';
        // if (j > 0 && map[i][j-1] != '1') { // Check left tile
        // }
        // if (j < 19 && map[i][j+1] != '1') { // Check right tile
        // }
    }
    return tile;
}

void change_map(char map[][21]) {
    int i, j;
    
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 20; j++) {
            map[i][j] = get_wall_tile(map, i, j);
        }
    }
}

int main() {
    char map[10][21] = {
        "11111111111111111111",
        "10E00111000C0100P001",
        "10C01010011000C11011",
        "1CC00000C11000111001",
        "1011101000001011C001",
        "10111C100C0000000111",
        "10C00010011100000111",
        "10010000001110010001",
        "1000CCC00000C001C001",
        "11111111111111111111"
    };
    

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            if(map[i][j] == '0')
                map[i][j] = 'X';
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            if (map[i][j] == '1'){
                if ((i > 0 && i < 9) && (map[i-1][j] >= 'A' && map[i+1][j] >= 'A'))
                map[i][j] = 'W';
            else if ((j > 0 && j < 19) && (map[i][j-1] >= 'A' && map[i][j+1] >= 'A'))
                map[i][j] = 'W';
            }
        }
    }
    
    change_map(map);

    for (int i = 0; i < 10; i++) {
        printf("{");
        for (int j = 0; j < 20; j++)
            printf("\"%c\",", map[i][j]);
        printf("},\n");
    }
    
    return 0;
}
