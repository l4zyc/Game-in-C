#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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
    system("clear");
}

int generateFoodX() {
    return rand() % ((30 - 1 + 1) + 1);
}

int generateFoodY() {
    return rand() % ((15 - 1 + 1) + 1);
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
    data->prev = tail;
    head = data;
}


void draw() {

    if(curr == NULL) {
        printf("Map not found\n");
        return;
    }

    if(curr->map[playerY][playerX] == '#') {
        gameOver = false;
    }

    if(playerX < 0) {
        playerX = width - 1;
        curr = curr->prev;
    } else if(playerX > width - 1) {
        playerX = 0;
        curr = curr->next;
    }

    printf("Score: %d\n", score);
    while(curr->map[foodY][foodX] == '#' || foodX > 30 || foodY > 15) {
        foodX = generateFoodX();
        foodY = generateFoodY();
    }

    if(playerX == foodX && playerY == foodY) {
        foodX = generateFoodX();
        foodY = generateFoodY();
    }


    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {

            if(playerX == x && playerY == y) {
                printf("0");
            } else if(foodX == x && foodY == y) {
                printf("A");
            } else {
                printf("%c", curr->map[y][x]);
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
                if (curr == head && playerX < 0) {
                    playerX = width - 1;
                    curr = tail;
                }
                break;
            case 'd':
                playerX++;
                if (curr == tail && playerX >= width) {
                    playerX = 0;
                    curr = head;
                }
                break;
            case 's':
                playerY++;
                break;
        }

        if(playerX == foodX && playerY == foodY) {
            score++;
        }
    }

    if(!(gameOver)) {
        clear();
        printf("GAME OVER\n");
        printf("Press enter to continue...");
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