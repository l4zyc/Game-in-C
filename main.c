#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#define height 15
#define width 30

const int startX = 15;
const int startY = 7;

int playerX = startX;
int playerY = startY;
int foodX;
int foodY;

int score = 0;
int value = 1;
bool gameOver = true;

char garden[height][width] = {
    "##############################",
    "#            ####            #",
    "#  #     #          #     #  #",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "                              ",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "#  #    #            #    #  #",
    "#  #     #          #     #  #",
    "#            ####            #",
    "##############################",
};

char plaza[height][width] = {
    "##############################",
    "#      #     ###     #       #",
    "#      #     ###     #       #",
    "#      #             #       #",
    "#      #     #####   #       #",
    "#      #         #   #       #",
    "#      #         #   #       #",
    "                              ",
    "#      #         #   #       #",
    "#      #         #   #       #",
    "#      #     #####   #       #",
    "#      #             #       #",
    "#      #     ###     #       #",
    "#      #     ###     #       #",
    "##############################",
};

char town[height][width] = {
    "##############################",
    "#             ###            #",
    "#    #######  ###  #######   #",
    "#    #                #      #",
    "#    #   #########    #      #",
    "#    #   #       #    #      #",
    "#    #   #       #    #      #",
    "                              ",
    "#    #   #       #    #      #",
    "#    #   #       #    #      #",
    "#    #   #########    #      #",
    "#    #                #      #",
    "#    #######  ###  #######   #",
    "#             ###            #",
    "##############################",
};

void clear() {
    system("cls");
}

struct Node {
    char map[height][width];
    struct Node *next, *prev;
} *head = NULL, *tail = NULL, *curr = NULL;

struct Node* newNode(char map[height][width]) {
    struct Node* temp = (struct Node*) malloc(sizeof(struct Node));

    for(int i = 0; i < height; i++) {
        strcpy(temp->map[i], map[i]);
    }  

    temp->next = temp->prev = NULL;

    return temp;
}


void pushTail(char map[height][width]) {
    struct Node* data = newNode(map);

    if(head == NULL) {
        head = tail = data;
        return;
    }
    tail->next = data;
    data->prev = tail;
    data->next = head;
    tail = data;
}

void pushHead(char map[height][width]) {
    struct Node* data = newNode(map);

    if(head == NULL) {
        head = tail = data;
        return;
    }

    struct Node* temp = head;

    data->next = head;
    head = data;
    head->prev = tail;
}


void draw() {

    if(head == NULL) {
        printf("Map not found\n");
        return;
    }

    if(playerX < 0) {
        playerX = width - 1;
        head = head->prev;
    } else if(playerX > width - 1) {
        playerX = 0;
        head = head->next;
    }

    printf("Score: %d\n", score);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {

            if(playerX == x && playerY == y) {
                printf("0");
            } else {
                printf("%c", head->map[y][x]);
            }

            if(head->map[playerY][playerX] == '#') {
                gameOver = false;
            }
        }
        printf("\n");
    }    
}

void play() {
    pushHead(garden);
    pushTail(plaza);
    pushTail(town);
    curr = head;
    char control;

    while(gameOver) {
        clear();
        draw();
        printf("\n");
        printf("Input >> ");
        scanf("%c", &control); fflush(stdin);
        
        switch(control) {
            case 'w':
                playerY--;
                break;
            case 'a':
                playerX--;
                break;
            case 'd':
                playerX++;
                break;
            case 's':
                playerY++;
                break;
        }
    }

    
    if(!(gameOver)) {
        clear();
        printf("Game Over...\n");
        getchar();
    }

}

void menu() {
    clear();
    int choice;
    printf("1. Play\n");
    printf("2. Exit\n");
    printf(">> ");
    scanf("%d", &choice); getchar();

    switch(choice) {
        case 1:
            play();
            break;
        case 2:
            return;
            break;
        default:
            menu();
    }
}

int main() {
    menu();
    return 0;
}
