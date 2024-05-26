/*
1.�������󤧶��I�������Y�G����B�a�ϡB�Ǫ������ʬO�_�X�z�A����M�Ǫ��I���᪺����
2.�P�_���ʬO�_�X�z�A�^��bool�Ȩ�move.c��(����y�Ч��ܻP�_���P�_)
*/

#include "basic.h"
#include "initial.h"
#include "collision.h"
#include "move.h"
#include "generate.h"
#include "game.h"


//�P�_���⪺�U�@�B�O�_�ਫ
bool characterMoveOrNot(void){
    int next_x = character.x + character.offset_x;
    int next_y = character.y + character.offset_y;
    //�p�G���⪺�U�@�B�b�a�ϤW����樫(�U�@��O0, �Ŧa)
    if(map[(next_y + mapPoint.y) / ITEM_SIZE][(next_x + mapPoint.x) / ITEM_SIZE] == 0){
        //�p�G�U�@�B�S���W�L��i�a�Ϫ��d��
        if(next_y + mapPoint.y < MAP_HEIGHT && next_x + mapPoint.x < MAP_WIDTH)
            return true;
    }
    return false;
}

//�ھڨ��Ⲿ��(characterMoveOrNot)�A�p�G�U�@�B���O�Ŧa(false)�A�P�_�O�_���q��(�άO��L���ʿﶵ)  �^�ǽs��(ex.�q�� == 2) **����
int nextStepIsComputerOrNot(){
    int next_x = character.x + character.offset_x;
    int next_y = character.y + character.offset_y;
    //2 computer
    if(map[(next_y + mapPoint.y) / ITEM_SIZE][(next_x + mapPoint.x) / ITEM_SIZE] == 2)
        return 2;
    //3 locked door
    else if(map[(next_y + mapPoint.y) / ITEM_SIZE][(next_x + mapPoint.x) / ITEM_SIZE] == 3)
        return 3;
    //���O���ʪ���
    return -1;
    
}

//�ھڨ��Ⲿ�ʡA�P�_�a�ϬO�_����
bool mapMoveOrNot(void){
    //�p�G���Ⲿ��
    if(characterMoveOrNot()){
        //���⪺�U�@�B(x, y)
        int next_x = character.x + character.offset_x;
        int next_y = character.y + character.offset_y;
        //�p�G����U�@�B�b�ù������䤤�u�W�A�Φb�ù�����ɤW **�b���I(0, 560)����ɲ��ʡA�n���a�Ϥ��ʡA(character.x == 0 && character.y + mapPoint.y != MAP_LIMIT + ITEM_LIMIT) || (character.y == ITEM_LIMIT && character.y + mapPoint.y != MAP_LIMIT + ITEM_LIMIT)
        if(next_x + ITEM_SIZE/2 == SCREEN_WIDTH /2 || next_y + ITEM_SIZE/2 == SCREEN_HEIGHT/2 || next_x == ITEM_LIMIT || (next_x == 0 && next_y + mapPoint.y != MAP_LIMIT + ITEM_LIMIT) || (next_y == ITEM_LIMIT && next_y + mapPoint.y != MAP_LIMIT + ITEM_LIMIT) || next_y == 0){
            //�p�G�a�Ϯy��+�첾�q�b�a�Ϯy�нd��
            if(mapPoint.x + mapPoint.offset_x <= MAP_LIMIT && mapPoint.x + mapPoint.offset_x >= 0 && mapPoint.y + mapPoint.offset_y <= MAP_LIMIT && mapPoint.y + mapPoint.offset_y >= 0){
                return true;
            }
        }      
    }
    return false;
}

//�P�_�ѹ����U�@�B�O�_�ਫ
bool mouseMoveOrNot(struct mouse *eachMouse){
    int next_x, next_y;
    next_x = eachMouse -> x + eachMouse -> offset_x;
    next_y = eachMouse -> y + eachMouse -> offset_y;
    //�P�_�U�@�B�O���O�Ŧa
    if(map[next_y][next_x] == 0)
         //�p�G�ѹ��y��+�첾�q�b�a�Ϯy�нd��
        if(next_x < MAP_WIDTH / ITEM_SIZE && next_y < MAP_HEIGHT / ITEM_SIZE )
            return true;
    
    return false;
}

//����M�Ǫ����I��(�P�_�C�@���ѹ�(���ʫ�)���y�СA�M����(���ʫ�)���y�СA��̦��L���|)
bool characterMeetsMouseOrNot(struct mouse *eachmouse){
    //�]���ѹ����y�ЬO�a���x�s�Ϥ����y�� �n * ITEM_SIZE �A - mapPoint�~�O�ù��W���y��
    int mouse_x = eachmouse -> x * ITEM_SIZE - mapPoint.x;
    int mouse_y = eachmouse -> y * ITEM_SIZE - mapPoint.y;
    //�p�G�ѹ��b�ù��W���y�е��󨤦⪺�y�� ���I��
    if(character.x == mouse_x && character.y  == mouse_y)
        return true;

    return false;
}

//�ƹ��O�_�I��app�ϥ�
int clickAppOrNot(int x, int y){
    
    for(int i = 0; i<4; i++){
        //app���y�Фj�p
        SDL_Rect appRect = {.h = 60, .w = 60, .x = 100 + i*80, .y = 100};
        //�p�G�I���ϥܽd��
        if(x >= appRect.x && x <= appRect.x + appRect.w && y >= appRect.y && y <= appRect.y + appRect.h){
            //�P�_�O����app
            return computerApp[i].type;
        }
    }
    //�p�G���S�� �^��-1
    return -1;
}

//�ƹ��O�_�I��wordle option�ϥ�
int clickWordleOptionOrNot(int x, int y){
    for(int i = 0; i<2; i++){
        //wordle option���y�Фj�p
        SDL_Rect optionRect = {.h = 50, .w = 50, .x = 420 + i*80, .y = 30};
        //�p�G�I���ϥܽd��
        if(x >= optionRect.x && x <= optionRect.x + optionRect.w && y >= optionRect.y && y <= optionRect.y + optionRect.h){
            //�P�_�O���ӥ\��ﶵ
            return wordlePageOption[i].type;
        }
    }
    //�p�G���S�� �^��-1
    return -1;
}

//�P�_��J�r���M����(����)�O�_�X�z
bool wordleLettersLensIsLegal(int num_column, int num_row, int letter){
    //1. 7*7
    //�r��
    if(letter >= SDL_SCANCODE_A && letter <= SDL_SCANCODE_Z){
        if(num_column + 1 < 7 && num_row < 7) return true;
        if(num_column + 1 == 7 && num_row < 7) return true;
        return false;
    }
    //backspace ���e�R���@�Ӧr��
    if(letter == SDL_SCANCODE_BACKSPACE){
        if(num_column - 1 >= 0) return true;
        return false;
    }
    //enter(��J�����r�� ���Uenter)
    if(letter == SDL_SCANCODE_RETURN){
        if(num_column == 7 && num_row < 7) return true;
        return false;
    }
}





