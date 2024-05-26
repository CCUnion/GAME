/*
1.�Ҧ����󪺭ȡG�]�A�a�ϡB�ù��B����B���......�A�w�q�_�l�y�СB�C�i�Ϥ����j�p�B���󲾰ʪ��첾�q
�B�a�Ϯy�ЩM�첾����b�ù��W������y�нd��

2.�Ҧ�����|�Ψ쪺sdl���СGSDL_window(�Ыص���)�BSDL_Renderer(�N�Ϥ��ƻs��renderer, renderer�A��ܨ�ù��W)
�BSDL_Texture(�Ҧ��Ϥ���texture, �Ntexture�ƻs��renderer)

3.sdl���y�Шt�έ��I�O(0, 0), x�b�q����k���W�Ay�b�q�W��U���W�C*�C�i�Ϥ����y�ЬO�Ϥ������W��
*/

#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>

//�a���`���e
#define MAP_WIDTH 1000
#define MAP_HEIGHT 1000

//�ù����e
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

//����j�p(���B�e���O40) *���󪫥󪺦첾�q = 40
#define ITEM_SIZE 40

//�a�Ϯy�Цb�ù��W���̤j�y�Э���(x�By���O400)
#define MAP_LIMIT 400

//���ʪ���y�Цb�ù��W���̤j�y�Э���(x�By���O560)
#define ITEM_LIMIT 560

//����b�ù��W����l��m�y��(�ù����U��) = (0, 560)
#define CHARACTER_X 0
#define CHARACTER_Y ITEM_LIMIT

//�a�Ϧb�ù��W����l�y��(�����ù����U��) = (0, 400)
#define MAPPOINT_X 0
#define MAPPOINT_Y MAP_LIMIT

//�ѹ����`��(�ȩw �᭱�i�H�令�̾����d���׼W�[ �ѹ��ƶq�]�|�W�[)
#define TOTAL_MOUSE 5
//�C�j300�@��ѹ����ʤ@��
#define MOUSE_MOVE_INTERVAL 300

//�`hp(��q)5����
#define TOTAL_HP 5

//�r���ƶq
#define TOTAL_LETTERS 26

//�¥զѹ����ƶq(�ھ����d���P�i�H�ק�ƶq)
extern int whiteMouse;
extern int blackMouse;

//wordle��l��
extern int wordle_row, wordle_column;

//�C�@�������d���ѧP�_ **�b�C�@�����}�Y���n���m
extern bool lose;
//�C�@�������d���\�P�_(�q�Lwordle)**�b�C�@�����}�Y���n���m
extern bool win;

//sdl ����������
//�Ыص����ϥΪ�����)
SDL_Window *window;

//�N�Ϥ���ܨ�ù��W�һݭn������
SDL_Renderer *renderer;

//�Ҧ��Ϥ���texture�һݪ�����
SDL_Texture *doorTexture;
SDL_Texture *doorOpenTexture;
SDL_Texture *doorCloseTexture;
SDL_Texture *pressToEnterTexture;
SDL_Texture *characterTexture;
SDL_Texture *wallTexture;
SDL_Texture *computerTexture;
SDL_Texture *floorTexture;
SDL_Texture *whiteMouseTexture;
SDL_Texture *blackMouseTexture;
SDL_Texture *crashMessageTexture;
SDL_Texture *hp_fullTexture;
SDL_Texture *hp_emptyTexture;
SDL_Texture *hp_breakTexture;
SDL_Texture *bag1Texture;
SDL_Texture *bag2Texture;
SDL_Texture *bag3Texture;
SDL_Texture *bagInnerTexture;
SDL_Texture *oopsTexture;
SDL_Texture *HPrecoverTexture;
SDL_Texture *gotSomethingTexture;
SDL_Texture *attackedTexture;
//�r��
TTF_Font *font;

//�a�Ϫ��}�C�A�x�s�a�ϭ��n���H���󭱿n���ȡA�]�N�O�a�ϤW�����h�֪���
extern int map[MAP_HEIGHT / ITEM_SIZE][MAP_WIDTH / ITEM_SIZE];

//��J��V�䪺��V
typedef enum dir{character_up, character_left, character_down, character_right}dir;
//�ѹ��H���]����V
typedef enum mouse_dir{mouse_up, mouse_left, mouse_down, mouse_right}mouse_dir;
//�ѹ��C��
typedef enum mouse_color{white, black}mouse_color;
//��q�W�[�δ�֪��P�_
typedef enum hp_event{hp_recovery, hp_reduction}hp_event;
//wordle���r���PA~Z
typedef enum wordle_letter{letter_A, letter_B, letter_C, letter_D, letter_E, letter_F, letter_G, letter_H, letter_I, letter_J, letter_K, letter_L, letter_M, letter_N, letter_O, letter_P, letter_Q, letter_R, letter_S, letter_T, letter_U, letter_V, letter_W, letter_X, letter_Y, letter_Z}wordle_letter;

//���⪺�y�ЩM�첾�q(���򪺲��ʷ|�ե�)
extern struct character{
    int x;
    int y;
    int offset_x;
    int offset_y;
}character;

//�a�ϥ��W�����y�ЩM�첾�q(���򪺲��ʷ|�ե�)
extern struct mapPoint{
    int x;
    int y;
    int offset_x;
    int offset_y;
}mapPoint;

//�ѹ����y�ЩM�첾�q(�H���X�{�b�a�Ϫ��ťդW) //�����ѹ�(�¥��H��)
extern struct mouse{
    mouse_dir mouse_dir;
    mouse_color color;
    int x;
    int y;
    int offset_x;
    int offset_y;
}mouse[TOTAL_MOUSE];

//hp�����A(0<= full�Bempty���ƶq <= 5)
extern struct hp{
    int full;
    int empty;
    //�P�_���L���`(��q�k�s)
    bool deadOrNot;
}hp;

//wordle�Ϥ��qA~Z
extern struct wordle{
    //�o�Ӧ�m�D�حn�D���r��
    wordle_letter target;
    SDL_Texture *wordle_letterTexture;
}letters[TOTAL_LETTERS];


#endif