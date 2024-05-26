/*
�C������B��L��J
//gcc -o main.exe main.c initial.c collision.c move.c generate.c game.c -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

*/

#include "basic.h"
#include "initial.h"
#include "collision.h"
#include "move.h"
#include "generate.h"
#include "game.h"

//�ŧi�Ҧ�extern���ܼ�
struct character character = {.x = CHARACTER_X, .y = CHARACTER_Y, .offset_x = 0, .offset_y = 0};
int map[MAP_HEIGHT / ITEM_SIZE][MAP_WIDTH / ITEM_SIZE];
struct mapPoint mapPoint = {.x = MAPPOINT_X, .y = MAPPOINT_Y, .offset_x = 0, .offset_y = 0};
struct mouse mouse[TOTAL_MOUSE];
struct hp hp = {.full = TOTAL_HP, .empty = 0, .deadOrNot = false};
struct wordle letters[TOTAL_LETTERS];
int whiteMouse;
int blackMouse;
//wordle
int wordle_row, wordle_column;

//lose�Bwin
bool lose;
bool win;

int main(int argc, char *argv[]){
    
    //��l��:�Ыؿù��Mrenderer�B�Ҧ��Ϥ�
    initBasic();
    //�r��
    initFont();
    //��l��wordle���� **����
    initWordlePicture();
    //��l��start�Ϥ�
    initStartPicture();
    //��l��level 1�Ϥ�
    initPicture1();
    //��l�ƭI�]�Ϥ�
    initBagPicture();
    //��l�Ʃ���Ϥ�
    initluckyDrawPicture();

    //start
    start();
    //level_1
    level_1();
    //��ӹC����������O����
    closeSDL();

}
