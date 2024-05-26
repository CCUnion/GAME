/*
1.���󲾰ʫ�y�СB�ƭȧ��ܻP�_�A�ھ�collision��bool�^�ǭȧP�_
2.���󪺰����q�k�s
3.�ھڦѹ����H����V�ᤩ�ѹ������������q(�U�@�B�����Ӥ�V���O�H�����Aoffset���Ȯھڤ�V���P�Ӥ��P)
4.����M�ѹ����I���P�_(�P�_�O�_�I�sgenerate.c�������\��(�I���S�ĵ���))
*/

#include "basic.h"
#include "initial.h"
#include "collision.h"
#include "move.h"
#include "generate.h"
#include "game.h"

//�P�_����I��ѹ����ƥ� �ƥ�Ĳ�o��L�@�q�N�o(�L��)�ɶ��~�|��U�@���ƥ󦳤���
static bool collisionHappened = false;
//�I���ƥ�p�ɾ�
Uint32 collisionTimer = 0;
//1��N�o
#define COLLISION_COOLDOWN 1000

//�p�G�a�Ϥ��� ���Ⲿ�ʦX�z �y�Ч��� //�p�G���O�Ŧa �P�_�O���O���ʤ��(�q���B��L) �I�s����function
void characterMove(void){
    if(characterMoveOrNot() && mapMoveOrNot() == false){
        character.x += character.offset_x;
        character.y += character.offset_y;
    }
    //�p�G���O�Ŧa �P�_�O���O���ʤ��(�q���B��L)
    else if(!characterMoveOrNot())
        switch(nextStepIsComputerOrNot()){
            //���O���ʪ���
            case -1:
                break;
            //�q��(2)
            case 2:
                //����computer��function(game.c)
                computer();
                break;
            //�W�ꪺ��
            case 3:
                //�p�G�I�]�����_��(index:8), �N��q��)
                if(bagStore[8].gotHint)
                    win = true;
                break;
            default:
                break;
        }
}

//�p�G���Ⲿ�� �a�ϲ��ʦX�z �a�Ϯy�Ч���
void mapMove(void){
    if(mapMoveOrNot()){
        mapPoint.x += mapPoint.offset_x;
        mapPoint.y += mapPoint.offset_y;
    }
}

//�p�G�ѹ����ʦX�z �ѹ��y�Ч���
void mousemove(struct mouse *eachMouse){
        //�p�G��e�ѹ����ʦX�z �y�Ч���
        if(mouseMoveOrNot(eachMouse)){
            eachMouse -> x += eachMouse -> offset_x;
            eachMouse -> y += eachMouse -> offset_y;
        }
    
}

//���ʫ᰾���q�k�s
void resetOffset(){
    character.offset_x = 0;
    character.offset_y = 0;
    mapPoint.offset_x = 0;
    mapPoint.offset_y = 0;
}

//�ѹ��C�����ʰ����q�k�s
void resetMouseOffset(void){
    for(int i = 0; i<TOTAL_MOUSE; i++){
        //�����k�s
        mouse[i].offset_y = 0;
        mouse[i].offset_x = 0;
    }
}

//�ѹ��H���������q
void randomMouseOffset(void){
    //�H���ͦ��Ʀr 0 ~ 3 �N��W���U�k
    for(int i = 0; i<TOTAL_MOUSE; i++){
        mouse[i].mouse_dir = rand() % 4;
        switch(mouse[i].mouse_dir){
        case mouse_up: //up
            mouse[i].offset_y = -1;
            break;
        case mouse_left: //left
            mouse[i].offset_x = -1;
            break;
        case mouse_down: //down
            mouse[i].offset_y = 1;
            break;
        case mouse_right: //right
            mouse[i].offset_x = 1;
            break;
        default:
            break;
        }
    } 
}

//�p�G���ʫ᪺�ѹ��M����y�Ц����| �I�sgenerate.c���I���ƥ�
void characterMeetsMouse(struct mouse *eachMouse){
    if(characterMeetsMouseOrNot(eachMouse) && !collisionHappened){//�p�G�٨S�I��(�Ϊ̬O�L�F�N�o�ɶ�)
        //SDL_Delay(1000);
        //�I�sgenerate���I���S��(�Ϥ�, �Ȱ��Ӥ@��?)
        //crashMessage();
        //�p�G�O�¦ѹ� ���� (�N���P��q���ȧ���)
        if(eachMouse -> color == black)
            hpCondition(hp_reduction);
        //�p�G�O�զѹ� ��� (generate.c�����)
        else
            luckyDraw();
        //�I���o��
        collisionHappened = true;
        //�}�l�I���N�o�ɶ��p��
        collisionTimer = SDL_GetTicks();
    }
    //�p�G�L�F�N�o�ɶ� ���s�I���ƥ�P�_
    if(collisionHappened && SDL_GetTicks() - collisionTimer >= COLLISION_COOLDOWN)
        collisionHappened = false;
}

//���⦩��Υ[��
void hpCondition(hp_event event){
    if(!collisionHappened){
    switch(event){
        //�^��
        case hp_recovery:
            if(hp.full < 5){
                hp.full += 1;
                hp.empty -= 1;
            }
            break;
        //����
        case hp_reduction:
            printf("attacked!\n");
            hp.full -= 1;
            hp.empty += 1;
           //��
            SDL_Rect rect = {.h = 300, .w = 300, .x = 150, .y = 150};
            SDL_RenderCopy(renderer, attackedTexture, NULL, &rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(800);
            //�p�G�S��F ��s���`���A
            if(hp.full == 0)
                hp.deadOrNot = true;
            break;
        default:
            break;
    }
    }
}

//�ھ�collision.c��wordleLettersLensIsLegal�P�_�r����J�O�_���� ����wordle�x�s�����A �٦��P�_wordle���\������
void wordleLettersInput(int *num_row, int *num_column, int letter, int *wordle_success){
    if(wordleLettersLensIsLegal(*num_column, *num_row, letter)){
        //�r��
        if(letter >= SDL_SCANCODE_A && letter <= SDL_SCANCODE_Z){
            //���mwordle_success(�p�G*num_column == 0)
            if(*num_column == 0)
                *wordle_success = 0;

            *num_column += 1;
            wordle_letters_square[*num_row][*num_column].input_letter = letter;
            //�p�G��J�r�����T ��m���T �b��r��(���)
            if(letter == wordle_letters_square[*num_row][*num_column].target_letter){
                wordle_letters_square[*num_row][*num_column].rightPosition = true;
                wordle_letters_square[*num_row][*num_column].letterInList = true;
                //wordle���\����+1
                *wordle_success += 1;
                return;
            }
            //�p�G�r�������T �M���L��m�P�_�r���O�_�b��r��
            else{
                wordle_letters_square[*num_row][*num_column].rightPosition = false;
                for(int i = 1; i<=wordle_column; i++){
                    if(wordle_letters_square[*num_row][i].target_letter == letter){
                        //�r���X�{�b��r��L��m �N��b��r�� ���O��m�����T(����)
                        wordle_letters_square[*num_row][*num_column].letterInList = true;
                        return;
                    }
                }
                //���b���T��m �]�S���X�{�b��r��L��m(�Ǧ�)
                wordle_letters_square[*num_row][*num_column].letterInList = false;
                    return;
            }
        }
            
        //backspace ���e�R����e�r�����A
        if(letter == SDL_SCANCODE_BACKSPACE){
            wordle_letters_square[*num_row][*num_column].input_letter = SDL_SCANCODE_UNKNOWN;
            wordle_letters_square[*num_row][*num_column].rightPosition = false;
            wordle_letters_square[*num_row][*num_column].letterInList = false;
            *num_column -= 1;
            return;
        }
            
        //enter �p�G���F ���U�@��
        if(letter == SDL_SCANCODE_RETURN){
            *num_column = 0;
            *num_row += 1;
            //wordle_success++
            *wordle_success += 1;
            return;
        }

    }
    
    
}




