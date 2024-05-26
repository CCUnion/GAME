/*
1.��l�ƦU�تF��Gsdl, window�Brenderer�B�y��
2.Ū�����P���a�ϡB�Ϥ�
*/

#ifndef INITIAL_H
#define INITIAL_H

//�q���ୱ�����A
typedef enum computerDeskType{computer_desktop_load, computer_desktop_home, computer_desktop_empty}computerDeskType;
//�q���ୱ���{��
typedef enum computerAppType{computer_app_wordle, computer_app_camera, computer_app_book, computer_app_eCos, computer_app_photo ,computer_app_ecosLoading ,computer_app_404 ,computer_app_toDoList}computerAppType;
//wordle����
typedef enum wordlePageType{wordle_page_rule_click, wordle_page_quit, wordle_page_rule, wordle_page_success, wordle_page_main, wordle_page_gameover}wordlePageType;
//wordle�r���P�_���C��(����@�檺�U�Ӧr��)
typedef enum letterColorType{letter_color_green, letter_color_yellow, letter_color_grey}letterColorType;

//wordle �r��
extern struct wordle_letters_square{
    //�o�Ӧ�m�D�حn�D���r��
    int target_letter;
    //��J���O���Ӧr��
    int input_letter;
    //���S���b���T����m
    bool rightPosition;
    //�r���O�_�s�b
    bool letterInList;
}wordle_letters_square[10][10];


//�ୱ���T�ث���
extern struct computerDesktop{
    computerDeskType type;
    SDL_Texture *threeType;
}computerDesktop[3];

//�ୱ���ε{��*4 + �ۤ�*1 + ���O��*1 + �����ʵe*2
extern struct computerApp{
    computerAppType type;
    SDL_Texture *eightType;
}computerApp[8];

//wordle�D�����B������?(�W�h�����ϥ�)�B�h�X�ϥܡB�W�h�����B���\�e���B���ѵe��
extern struct wordlePageOption{
    wordlePageType type;
    SDL_Texture *sixType;
}wordlePageOption[6];

//wordle�r�������A(��B���B��)
extern struct letterColor{
    letterColorType type;
    SDL_Texture *threeType;
}letterColor[3];

//�I�]�x�s���F��(�r���d **�ȩw����)�A�I�]�e�q�̤j9��(�C�@���ȱ���m�T�w �Q���~�|���)
extern struct bagStore{
    bool gotHint; //���S���Q��� �p�G�Otrue�N�L�X��
    SDL_Texture *hintType; //���ܯȱ�
}bagStore[9];

//��l��sdl, window, renderer
void initBasic(void);

//***�]��function���ƤF�ҥH�o�����ӷ|�A��A�w�Q�Ogame���ط|�P�_���d�A�M������d�Ʀr��Ū��������ɸ��|����***//
//�q�����Ū�J�a�Ϩ�a�ϰ}�C 
void initMap1(void);
void initMap2(void);
void initMap3(void);

//***�o�̤]�O***///
//Ū�����P�a�ϩһݪ��Ϥ�(����B����B�a�O�B��L)
void initPicture1(void);
void initPicture2(void);
void initPicture3(void);

//��l�ƹC���}�l�Ϥ� **�����o�������աA�᭱�A��z
void initStartPicture(void);

//��l��computer�Ϥ� 26�ӭ^��r���d�B3���C��B�q���ù�(3��)
void initWordlePicture();

//�a�ϩM����y�Ъ���l��
void initCoordinate();

//��q����l��(full = 5, empty = 0, dead = false(0))
void initHp();

//�����ѹ��X�{�b�a�ϤW���H���y��, �@�w�ͦ��b�Ŧa, �X�{��m�i�H���|
void initMouse();

//�C�@����wordle��l��(1. 7*7, 2. 4*4�B6*6, 3. 5*5)
void initWordleAns();

//���}�I�](���~��)���Ϥ���l��
void initBagPicture();

//�I��ѹ�������Ϥ�
void initluckyDrawPicture();

//��l�Ʀr��
void initFont();

//��l�ƨC�@�����I�]���ܯȱ�(�r�����Ӷ��ǱƦC ������)
void initBagHintPicture();

#endif

