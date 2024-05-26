/*
1.�⪫��Ϥ��L��ù��W�A���Ǭ��a�O >> ��� >> ���� >>�@�ѹ��@>> ��L���� 
2.�᭱�L�W�h���Ϥ��|�л\�즳���Ϫ������e�� *�e���Q�л\����m�M���n�O�n�L�W�h���Ϥ��]�w���y�ЩM�j�p(rect)
3.����M�ѹ��I���S��(�ȩw)
4.�զѹ������(�^��B���ܡB�b�t)
*/

#include "basic.h"
#include "initial.h"
#include "collision.h"
#include "move.h"
#include "generate.h"
#include "game.h"

//�I��զѹ������
typedef enum luckyDrawType{draw_recovery, draw_hint, draw_so_sad}luckyDrawType;
//�a�O
void generateFloor(void){
    SDL_Rect floorRect = {.h = SCREEN_HEIGHT, .w = SCREEN_WIDTH};
    SDL_RenderCopy(renderer, floorTexture, NULL, &floorRect);
}

//�a�Ϫ���
void generateMap(){
    //�P�_�a�Ϯy�Ц��S������
    mapMove();
    
    //�ھڦa�Ϫ�����s���L�X�a�� *�a�ϰ}�C��x, y�n�Msdl�e����x, y�ۤ�
    for(int i = mapPoint.x / 40; i<(mapPoint.x + SCREEN_WIDTH) / 40; i++){
        for(int j = mapPoint.y / 40; j<(mapPoint.y + SCREEN_HEIGHT) / 40; j++){
            if(map[j][i] == 1){
                SDL_Rect wallRect = {.h = ITEM_SIZE, .w = ITEM_SIZE, .x = i * ITEM_SIZE - mapPoint.x, .y = j * ITEM_SIZE- mapPoint.y};
                SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
            }
            else if(map[j][i] == 2){
                SDL_Rect computerRect = {.h = ITEM_SIZE, .w = ITEM_SIZE, .x = i * ITEM_SIZE - mapPoint.x, .y = j * ITEM_SIZE - mapPoint.y};
                SDL_RenderCopy(renderer, computerTexture, NULL, &computerRect);
            }
            else if(map[j][i] == 3){ //�W�ꪺ��
                SDL_Rect doorRect = {.h = ITEM_SIZE, .w = ITEM_SIZE, .x = i * ITEM_SIZE - mapPoint.x, .y = j * ITEM_SIZE - mapPoint.y};
                SDL_RenderCopy(renderer, doorTexture, NULL, &doorRect);
            }
        }
    }
}

//����
void generateCharacter(dir direction){
    characterMove();
    SDL_Rect characterRect = {.h = ITEM_SIZE, .w = ITEM_SIZE, .x = character.x, .y = character.y};
    //�P�_��J����V��A�M�w���⭱�V����
    switch(direction)
    {
    case character_up:
        SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect);
        break;
    case character_left:
        SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect);
        break;
    case character_down:
        SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect);
        break;
    case character_right:
        SDL_RenderCopyEx(renderer, characterTexture, NULL, &characterRect, 0, NULL, SDL_FLIP_HORIZONTAL);
        break;
    default:
        break;
    }
}

//�ѹ�
void generateMouse(void){
    for(int i = 0; i<TOTAL_MOUSE; i++){
        mousemove(&mouse[i]);
        //�ѹ��y��
        SDL_Rect mouseRect = {.h = ITEM_SIZE, .w = ITEM_SIZE, .x = mouse[i].x * ITEM_SIZE - mapPoint.x, .y = mouse[i].y * ITEM_SIZE- mapPoint.y};
        //1.�C��2.��V
        switch(mouse[i].color){
            case white:
                //��V
                switch(mouse[i].mouse_dir){
                    case mouse_up://up
                        SDL_RenderCopy(renderer, whiteMouseTexture, NULL, &mouseRect);
                        break;
                    case mouse_left://left
                        SDL_RenderCopyEx(renderer, whiteMouseTexture, NULL, &mouseRect, -90, NULL, SDL_FLIP_NONE);
                        break;
                    case mouse_down:
                        SDL_RenderCopyEx(renderer, whiteMouseTexture, NULL, &mouseRect, 0, NULL, SDL_FLIP_VERTICAL);
                        break;
                    case mouse_right:
                        SDL_RenderCopyEx(renderer, whiteMouseTexture, NULL, &mouseRect, 90, NULL, SDL_FLIP_NONE);
                        break;
                    default:
                        break;
                }
                //SDL_RenderCopy(renderer, whiteMouseTexture, NULL, &mouseRect);
                break;
            case black:
                switch(mouse[i].mouse_dir){
                    case mouse_up://up
                        SDL_RenderCopy(renderer, blackMouseTexture, NULL, &mouseRect);
                        break;
                    case mouse_left://left
                        SDL_RenderCopyEx(renderer, blackMouseTexture, NULL, &mouseRect, -90, NULL, SDL_FLIP_NONE);
                        break;
                    case mouse_down:
                        SDL_RenderCopyEx(renderer, blackMouseTexture, NULL, &mouseRect, 0, NULL, SDL_FLIP_VERTICAL);
                        break;
                    case mouse_right:
                        SDL_RenderCopyEx(renderer, blackMouseTexture, NULL, &mouseRect, 90, NULL, SDL_FLIP_NONE);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        characterMeetsMouse(&mouse[i]);
    }
}

//����B�ѹ����I���S��
void crashMessage(){
    SDL_Rect rect = {.h = 80, .w = 200, .x = character.x, .y = character.y};
    SDL_RenderCopy(renderer, crashMessageTexture, NULL, &rect);
}

//��q(hp) �a�ϥk�W��(����k)
void generateHP(){
    int HP_x = 400, HP_y = 0; //y�b����
    //empty
    for(int i = 0; i<hp.empty; i++){
        SDL_Rect rect = {.h = 40, .w = 40, .x = HP_x, .y = HP_y};
        SDL_RenderCopy(renderer, hp_emptyTexture, NULL, &rect);
        HP_x += ITEM_SIZE;
    }
     //full
    for(int i = 0; i<hp.full; i++){
        SDL_Rect rect = {.h = 40, .w = 40, .x = HP_x, .y = HP_y};
        SDL_RenderCopy(renderer, hp_fullTexture, NULL, &rect);
        HP_x += ITEM_SIZE;
    }
    //�p�G��q��0(���`) lose�]��true
    if(hp.deadOrNot == true){
        lose = true;
    }
}

//�զѹ������(�^��B���ܡB�b�t) **�����٨S��
void luckyDraw(){
    //�ĴX�����P�_(�ھڨC�@����wordle���� ����������)
    //�H�����
    luckyDrawType luckyOrNot = rand() % 3;
    switch(luckyOrNot){
        case draw_recovery:{
            hpCondition(hp_recovery);
            SDL_Rect rect = {.h = 300, .w = 300, .x = 150, .y = 150};
            SDL_RenderCopy(renderer, HPrecoverTexture, NULL, &rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(800);
            printf("recover!\n");
            }
            break;
        case draw_hint:{
            //�H������ **�I�]
            //�Ĥ@���I�]���ܯȱ���8��
            int hint = rand() % 8; // bagStore[0] ~ [7]
            //�p�G�٨S�Q��L �аO��true �b�I�]���L�X��
            if(bagStore[hint].gotHint == false)
                bagStore[hint].gotHint = true;
            //��
            SDL_Rect rect = {.h = 300, .w = 300, .x = 150, .y = 150};
            SDL_RenderCopy(renderer, gotSomethingTexture, NULL, &rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(800);
            printf("got a letter!\n");
            }
            break;
        case draw_so_sad:{
            //��
            SDL_Rect rect = {.h = 300, .w = 300, .x = 150, .y = 150};
            SDL_RenderCopy(renderer, oopsTexture, NULL, &rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(800);
            printf("oops...qq\n");
            }
            break;
        default:
            break;
    }
}

//�q�����J���ʵe
void computerDesktopLoading(){
    //�q��loading�e��

    //�ɶ������̱`����
    int timeLine = 380;
    //�ɶ��������n�M�y��
    SDL_Rect timeRect = {.h = 20, .w = 2, .x = 100, .y = 400};
    SDL_Rect desktopRect = {.h = SCREEN_HEIGHT, .w = SCREEN_WIDTH, .x = 0, .y = 0};
    bool quit = false;
    while(!quit){
        //loading�e��
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, computerDesktop[computer_desktop_load].threeType, NULL, &desktopRect);
        //�]�w�զ�
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //�ɶ�����R���զ�
        SDL_RenderFillRect(renderer, &timeRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        //�ɶ����b�e�׭������
        if(timeRect.w < timeLine)
            timeRect.w ++;
        else
            quit = true;
    }
    SDL_Delay(1000);
}

//�ୱ�MĲ���ﶵ(���ε{��)
void deskTop(){
    //�ୱ
    SDL_Rect deskRect = {.h = SCREEN_HEIGHT, .w = SCREEN_WIDTH, .x = 0, .y = 0};
    SDL_RenderCopy(renderer, computerDesktop[computer_desktop_home].threeType, NULL, &deskRect);
    //���ε{��*4
    for(int i = 0; i<4; i++){
        SDL_Rect appRect = {.h = 60, .w = 60, .x = 100 + i*80, .y = 100};
        SDL_RenderCopy(renderer, computerApp[i].eightType, NULL, &appRect);       
    }  
}

//�ୱapp
void deskTopApp(int x, int y, bool *wordleEvent, bool *itemValue){
    //�ƹ��O�_�I��app�ϥ� �I�scollision.c�P�_
    
    //ecos���ʵe���P�_
    bool static load = false;
    //�����I����app����
    static int appItem = -1;

    if(*itemValue == false){
        appItem = -1;
        *itemValue = true;
    }
    //
    if(appItem == computer_app_wordle && *wordleEvent == false)
        appItem = -1;
    //�p�Gclick_x && click_y == -1 �N��S���I��
    if(x != -1 && y != -1)
        appItem = clickAppOrNot(x, y);

    switch(appItem){
        case -1://�S���I����ϥ�
            //��_�@�F�����ʵe
            load = false;
            break;
        case computer_app_wordle:{//wordle�C��()
            *wordleEvent = true;
            break;
        }
            
        case computer_app_camera:{
            //�ۤ�
            SDL_Rect rect = {.h = SCREEN_HEIGHT, .w = SCREEN_WIDTH, .x = 0, .y = 0};
            SDL_RenderCopy(renderer, computerApp[computer_app_photo].eightType, NULL, &rect);
            break;
            }
            
        case computer_app_book:{
            //to do list
            SDL_Rect rect = {.h = SCREEN_HEIGHT, .w = SCREEN_WIDTH, .x = 0, .y = 0};
            SDL_RenderCopy(renderer, computerApp[computer_app_toDoList].eightType, NULL, &rect);  
            break;
        }
            
        case computer_app_eCos:{
            //ecos loading
            if(!load){
            SDL_Rect rect = {.h = SCREEN_HEIGHT, .w = SCREEN_WIDTH, .x = 0, .y = 0};
            SDL_RenderCopy(renderer, computerApp[computer_app_ecosLoading].eightType, NULL, &rect);
            SDL_RenderPresent(renderer);
            //����@��
            SDL_Delay(1000);
            load = true;
            }
            //404
            SDL_Rect rect = {.h = SCREEN_HEIGHT, .w = SCREEN_WIDTH, .x = 0, .y = 0};
            SDL_RenderCopy(renderer, computerApp[computer_app_404].eightType, NULL, &rect);
            break;
        }
        default:
            break;
    }
}

//wordle����
void wordlePage(int num_row, int num_column, int wordle_success){
    //�¦�
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //wordle����
    SDL_Rect rect = {.h = SCREEN_HEIGHT, .w = SCREEN_WIDTH, .x = 0, .y = 0};
    SDL_RenderCopy(renderer, wordlePageOption[wordle_page_main].sixType, NULL, &rect);

    //�ﶵ2(rule�Bquit)
    for(int i = 0; i<2; i++){
        SDL_Rect optionRect = {.h = 50, .w = 50, .x = 420 + i*80, .y = 30};
        SDL_RenderCopy(renderer, wordlePageOption[i].sixType, NULL, &optionRect);       
    }  
    //wordle�Ů�(���d�@ 7*7)

    //�L�X�w�s�b�������ƪ����p(���:��m���T�B�r���b��r���A����:��m���~�B�r���b��r���A�Ǧ�:�����b)
    for(int i = 0; i<num_row; i++){
        for(int j = 1; j<=wordle_column; j++){
            //���
            if(wordle_letters_square[i][j].rightPosition && wordle_letters_square[i][j].letterInList){
                SDL_Rect rect = {.h = 60, .w = 60, .x = 55 + 70*(j - 1), .y = 110 + 70*(i)};
                SDL_RenderCopy(renderer, letterColor[letter_color_green].threeType, NULL, &rect);
            }
            //����
            else if(wordle_letters_square[i][j].rightPosition == false && wordle_letters_square[i][j].letterInList){
                SDL_Rect rect = {.h = 60, .w = 60, .x = 55 + 70*(j - 1), .y = 110 + 70*(i)};
                SDL_RenderCopy(renderer, letterColor[letter_color_yellow].threeType, NULL, &rect);
            }
            //�Ǧ�
            else{
                SDL_Rect rect = {.h = 60, .w = 60, .x = 55 + 70*(j - 1), .y = 110 + 70*(i)};
                SDL_RenderCopy(renderer, letterColor[letter_color_grey].threeType, NULL, &rect);
            }

        }
    }
   //wordle���ťծ�l �Ĥ@��7*7 �٦��C����J���r��
    for(int i = 0; i<wordle_row; i++){
        for(int j = 1; j<=wordle_column; j++){
            //��l
            SDL_Rect rect = {.h = 60, .w = 60, .x = 55 + 70*(j - 1), .y = 110 + 70*(i)};
            SDL_RenderDrawRect(renderer, &rect);
            //�r��
            
            //�r���C��¦�
            SDL_Color textColor = {0, 0, 0, 255};
            //�P�_��r(A == 65 scancode_a == 4 �ҥH��61�h�[scancode)
            char input_letter;
            //�p�G�o�@�檺�r���s�b
            if(wordle_letters_square[i][j].input_letter != SDL_SCANCODE_UNKNOWN){
                input_letter = 'A' + wordle_letters_square[i][j].input_letter - 4;
                SDL_Surface *textSurface = TTF_RenderText_Solid(font, &input_letter, textColor);
                if(textSurface == NULL){
                    printf("unable to load textSurface, %s\n", SDL_GetError());
                    exit(1);
                }
            //texture
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if(textTexture == NULL){
                    printf("unable to load textTexture, %s\n", SDL_GetError());
                    exit(1);
                }
            SDL_FreeSurface(textSurface);
            //�r����m
            SDL_Rect textRect = {.h = 60, .w = 60, .x = 55 + 70*(j - 1), .y = 110 + 70*(i)};
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }     
    }
}
    //wordle_success(8�� �L�X���\�e��)
    if(wordle_success == 8){
        SDL_Rect success_rect = {.h = 300, .w = 300, .x = 150, .y = 150};
        SDL_RenderCopy(renderer, wordlePageOption[wordle_page_success].sixType, NULL, &success_rect);
        //�I�]�����_��(index:8)�]��true
        bagStore[8].gotHint = true;
    }
    //wordle game over(�p�Gnum_row == 7�Bwordle_success != 8)
    if(num_row == 7 && wordle_success != 8){
        SDL_Rect gameover_rect = {.h = 300, .w = 300, .x = 150, .y = 150};
        SDL_RenderCopy(renderer, wordlePageOption[wordle_page_gameover].sixType, NULL, &gameover_rect);
    }
    
}

//wordle�ﶵ2(rule�Bquit)���ƥ�(1.�I���d�ݳW�h�B2.�h�Xwordle�^��ୱ)
void wordlePageOptionEvent(int x, int y, bool *wordleQuit, bool *itemValue){
    //�ƹ��O�_�I��wordle�\�� �I�scollision.c�P�_
    
    //�����I��������
    static int optionItem = -1;

    if(*itemValue == false){
        optionItem = -1;
        *itemValue = true;
    }
    //�p�Gclick_x && click_y == -1 �N��S���I��
    if(x != -1 && y != -1)
        optionItem = clickWordleOptionOrNot(x, y);
   
    switch(optionItem){
        case -1://�S���I����ϥ�
            break;
        case wordle_page_rule_click:{//�I���W�h(?)
            //�W�h�e��
            SDL_Rect rect = {.h = SCREEN_HEIGHT, .w = SCREEN_WIDTH, .x = 0, .y = 0};
            SDL_RenderCopy(renderer, wordlePageOption[wordle_page_rule].sixType, NULL, &rect);
            break;
        }
        case wordle_page_quit:{//�I���h�X
            //�h�Xwordle�C�� �^��ୱ
            *wordleQuit = true;
            break;
            }
        default:
            break;
    }
}

//�D�a�ϫ�e���}�I�]���ʵe
void openBagAnimation(){
    SDL_Rect rect = {.h = 300, .w = 300, .x = 150, .y = 150};
    SDL_RenderCopy(renderer, bag1Texture, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(800);
    SDL_RenderCopy(renderer, bag2Texture, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(800);
    SDL_RenderCopy(renderer, bag3Texture, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(800);
    
}

//���}�I�]
void bagInnerItems(){
    //�I�]��Ũ
    SDL_Rect rect = {.h = 400, .w = 400, .x = 100, .y = 100};
    SDL_RenderCopy(renderer, bagInnerTexture, NULL, &rect);
    //�I�]�����ȱ��B�_��
    for(int i = 0; i<9; i++){
        switch(i){
            case 0:
                if(bagStore[i].gotHint){
                    SDL_Rect rect = {.h = 60, .w = 120, .x = 100, .y = 170};
                    SDL_RenderCopy(renderer, bagStore[i].hintType, NULL, &rect);
                }
                break;
            case 1:
                if(bagStore[i].gotHint){
                    SDL_Rect rect = {.h = 60, .w = 120, .x = 240, .y = 170};
                    SDL_RenderCopy(renderer, bagStore[i].hintType, NULL, &rect);
                }
                break;
            case 2:
                if(bagStore[i].gotHint){
                    SDL_Rect rect = {.h = 60, .w = 120, .x = 380, .y = 170};
                    SDL_RenderCopy(renderer, bagStore[i].hintType, NULL, &rect);
                }
                break;
            case 3:
                if(bagStore[i].gotHint){
                    SDL_Rect rect = {.h = 60, .w = 120, .x = 100, .y = 270};
                    SDL_RenderCopy(renderer, bagStore[i].hintType, NULL, &rect);
                }
                break;
            case 4:
                if(bagStore[i].gotHint){
                    SDL_Rect rect = {.h = 60, .w = 120, .x = 240, .y = 270};
                    SDL_RenderCopy(renderer, bagStore[i].hintType, NULL, &rect);
                }
                break;
            case 5:
                if(bagStore[i].gotHint){
                    SDL_Rect rect = {.h = 60, .w = 120, .x = 380, .y = 270};
                    SDL_RenderCopy(renderer, bagStore[i].hintType, NULL, &rect);
                }
                break;
            case 6:
                if(bagStore[i].gotHint){
                    SDL_Rect rect = {.h = 60, .w = 120, .x = 100, .y = 360};
                    SDL_RenderCopy(renderer, bagStore[i].hintType, NULL, &rect);
                }
                break;
            case 7:
                if(bagStore[i].gotHint){
                    SDL_Rect rect = {.h = 60, .w = 120, .x = 240, .y = 360};
                    SDL_RenderCopy(renderer, bagStore[i].hintType, NULL, &rect);
                }
                break;
            case 8: //�x�s�_��
                if(bagStore[i].gotHint){
                    SDL_Rect rect = {.h = 60, .w = 120, .x = 360, .y = 360};
                    SDL_RenderCopy(renderer, bagStore[i].hintType, NULL, &rect);
                }
                break;
            default:
                break;
        }
    }

}




