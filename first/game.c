/*
1.�C���y�{ : �C���}�l�e���}�l -> ���d1 -> ���d2 -> ���d3 -> (������) -> �u���� -> �C����������O����
2.����(�ɶ��B�S��)�B���s�}�l�B�i�J�U�@��������P�_(enum)
3.��ӹC�������O�o����O���� (**�w�Q�O�W��func���Ϥ��������槹�i�H��free)
*/

#include "basic.h"
#include "initial.h"
#include "collision.h"
#include "move.h"
#include "generate.h"
#include "game.h"
/*wordle

//�ھ��D�ت���r �P�_�C����J�r������m�M�O�_���T
extern struct wordle_letters{
    //�o�Ӧ�m�D�حn�D���r��
    wordle_letter target;
    //��J���O���Ӧr��
    wordle_letter letter;
    //���S���b���T����m
    bool rightPosition;
    //�r���O�_�s�b
    bool letterInList;
    //�O�ĴX�檺��J
    int line;
}wordle_letters;
*/
//�q��
void computer(){
    
    //�q�����J���ʵe
    computerDesktopLoading();
    //�ƹ��M��L��J���ƥ�j��
    bool quit = false;
    //�ƥ��J���P�_
    bool input = false;
    //�I��wordle�i�Jwordle�C�����P�_
    bool wordleEvent = false;
    //�I��app���P�_(�}�ҡB��^)
    int click_x = -1, click_y = -1;
    //�i�Jcomputer()loop�e ������static���ȭn��l��
    bool itemValue = false;
    while(!quit){
        //�o�̤]�n���]�I���y�� ���M�i�hwordle���h�X�|�����D **�ڤ]�����D������ �L�X���ˬd�o�{�ƹ��I�U�h���y�з|�@�������W�@���I���a��
        click_x = -1, click_y = -1;
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                //��L��J
                case SDL_KEYDOWN:
                    if(!input){
                        if(event.key.keysym.sym == SDLK_ESCAPE){
                    quit = true;
                    }   
                }
                break;
                //�ƹ���}(���U��)
                case SDL_MOUSEBUTTONDOWN:
                    if(!input){
                    //�I����m�y��
                    click_x = event.button.x;
                    click_y = event.button.y;
                }
                break;
                default:
                    break;
            }
            input = true;
        }
        /*if(wordleEvent)
        wordle(&wordleEvent);*/
    //�p�G�I��wordle �I�swordle
    
    //���J�ୱ **����    
        SDL_RenderClear(renderer);
        
            deskTop();
        //�P�_�I����app�ƥ�
        deskTopApp(click_x, click_y, &wordleEvent, &itemValue);
        SDL_RenderPresent(renderer);
        //�p�G�I��wordle�ƥ� �I�swordle function(game.c)

        if(wordleEvent)
        wordle(&wordleEvent);
    input = false;
    }
}

//wordle **�h�Xwordle��wordleEvent == false **����
void wordle(bool *wordleEvent){
    
    //��l�ƨC�@����wordle�]�w **�|�A�h�[bool or st
    initWordleAns();
    //initWordleAns();
    /*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    //wordle�e��(�Ĥ@����l7*7)

    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    */

    //�ƹ��M��L��J���ƥ�j��
    bool quit = false;
    //�ƥ��J���P�_
    bool input = false;
    //�I���k�W��(�W�h�B�h�X)���P�_(�}�ҳW�h�B��^�ୱ *wordleEvent = false)
    int click_x = -1, click_y = -1;
    //��L��J������(num_row: �����ơBnum_column:�C�@���J������)
    int num_row = 0, num_column = 0;
    //wordle���\(7����� + enter = 8)
    int wordle_success = 0;
    //�i�Jwordle()loop�e ������static���ȭn��l��
    bool itemValue = false;
    while(!quit){
        click_x = -1, click_y = -1;
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                //��L��J
                case SDL_KEYDOWN:
                    //if(!input){
                        if(event.key.keysym.sym == SDLK_ESCAPE){
                            quit = true;
                    }   
                    //��J���O�^��r���Bbackspace�Benter
                        else if(event.key.keysym.scancode >= SDL_SCANCODE_A && event.key.keysym.scancode <= SDL_SCANCODE_Z || event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE || event.key.keysym.scancode == SDL_SCANCODE_RETURN){
                            //�p�Gwordle�٨S�ѥX�� �~���J
                            if(wordle_success < 8){
                                //�P�_��J�B����wordle struct�x�s���A�P�_
                                wordleLettersInput(&num_row, &num_column, event.key.keysym.scancode, &wordle_success);
                            }     
                    }
                //}
                break;
                //�ƹ���}(���U��)
                case SDL_MOUSEBUTTONDOWN:
                    //�I����m�y��
                    click_x = event.button.x;
                    click_y = event.button.y;
                break;
                default:
                    break;
            }
            input = true;
        }
        //���Jwordle���� **����
    SDL_RenderClear(renderer);
    wordlePage(num_row, num_column, wordle_success);
    //�P�_�I����wordle�\��ﶵ�ƥ�
    wordlePageOptionEvent(click_x, click_y, &quit, &itemValue);
    SDL_RenderPresent(renderer);
    input = false;
    }
    //�h�Xwordle
    *wordleEvent = false;
}

//�C���}�l�e��
void start(){
    //�]�@�Ӥ��ʪ��Ϥ��y��(press)�M���e press�Ϥ��j�p��w = 120, h = 20, �y�Ь�(240, 290)
    struct pressCoordinate{
        int w;
        int h;
        int x;
        int y;
    }pressCoordinate = {.h = 40, .w = 240, .x = 180, .y = 280};

    
    //�ƥ�j��
    bool quit = false;
    //����ƹ��I���ƥ�|����Ĳ�o���Ϳ��~
    bool pressed = false;
    //�������S���b�}�l�Ϫ��d����U�ƹ�
    bool pressToEnter = false;
    while(!quit){
        //�ƹ��ƥ�
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            //�ƹ��I��
            switch(event.type){
                    //�ƹ���}(�}��)
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(event.button.x >= pressCoordinate.x && event.button.x <= pressCoordinate.x + pressCoordinate.w && event.button.y >= pressCoordinate.y && event.button.y <= pressCoordinate.y + pressCoordinate.h){
                        quit = true;
                        pressToEnter = true;
                    }
                    break;
                default :
                    break;
            }
            pressed = true;
        }
        pressed = false;
        //�L
        SDL_Rect doorRect = {.h = SCREEN_HEIGHT, .w = SCREEN_WIDTH, .x = 0, .y = 0};
        SDL_Rect PressRect = {.h = pressCoordinate.h, .w = pressCoordinate.w, .x = pressCoordinate.x, .y = pressCoordinate.y};
        SDL_RenderClear(renderer);
        if(!pressToEnter){
            SDL_RenderCopy(renderer ,doorCloseTexture, NULL, &doorRect);
            SDL_RenderCopy(renderer ,pressToEnterTexture, NULL, &PressRect);
        }
        else
            SDL_RenderCopy(renderer ,doorOpenTexture, NULL, &doorRect);
        
        SDL_RenderPresent(renderer); 
    }

    //�i�J�Ĥ@��������ʵe
    if(pressToEnter){
            SDL_Delay(1000);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            //�i�J�Ĥ@��
        }
}

//���d�@
void level_1(){
    //��l�ƹC�����ѡB���\���P�_
    lose = false;
    win = false;
//read map
    initMap1();
    initCoordinate();
    initMouse();
    initHp();
    //��l�ƨC�@�����I�]���ܯȱ�
    initBagHintPicture();
    
//event loop
    bool quit = false;
    dir direction = character_left;
    //bool moved = false;
    //���}�I�]���P�_
    bool openbag = false;
    //time //unit32 == unsigned int
    Uint32 mouseTimer = 0; //�p�ɾ�
    Uint32 lastTime = 0; //�W�@���������ɶ�
    Uint32 currentTime = 0; //sdl�B���ثe���ɶ�
    while(!quit){
        SDL_Event event;
        //input
        while(SDL_PollEvent(&event)){
            //input event
            switch(event.type){
                case SDL_QUIT:
                    puts("Exited");
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    //if(!moved){
                        if(event.key.keysym.sym == SDLK_ESCAPE){
                            puts("escape");
                            quit = true;
                           // moved = true;
                        }
                        else if(event.key.keysym.scancode == SDL_SCANCODE_W){//up
                            character.offset_y = -40;
                            mapPoint.offset_y = -40;
                            //moved = true;
                        }
                        else if(event.key.keysym.scancode == SDL_SCANCODE_S){//down
                            character.offset_y = 40; 
                            mapPoint.offset_y = 40;
                           // moved = true;
                        }
                        else if(event.key.keysym.scancode == SDL_SCANCODE_A){//left
                            character.offset_x = -40; 
                            mapPoint.offset_x = -40;
                            direction = character_left;
                            //moved = true;
                        }
                        else if(event.key.keysym.scancode == SDL_SCANCODE_D){//right
                            character.offset_x = 40; 
                            mapPoint.offset_x = 40;
                            direction = character_right;
                            //moved = true;
                        }
                        else if(event.key.keysym.scancode == SDL_SCANCODE_E){//right
                            //�p�G�S�����}�I�] ���}�I�]
                            if(!openbag){
                                openbag = true;
                                openBagAnimation();
                            }
                            //�p�G�w�g���}�I�] �A��e��������I�]
                            else if(openbag)
                                openbag = false;
                            //moved = true;
                        }
                        //printf("%d %d\n", character.x, character.y);
                    //}
                    break; 
                default:
                    break;
            }
            //moved = true;
            SDL_Delay(5);   
        }
        //�B���ثe���ɶ�
        currentTime = SDL_GetTicks();
        //�ثe���ɶ���W�@���������ɶ����j
        Uint32 deltaTime = currentTime - lastTime;
        //��s�����ɶ�
        lastTime = currentTime;
        //�p�ɾ��W�[�ɶ�
        mouseTimer += deltaTime;

        //print
        SDL_RenderClear(renderer);
        //
        generateFloor();
        generateMap();
        generateCharacter(direction);
        generateMouse();
        generateHP();
        if(openbag){//��e���}�I�]
            bagInnerItems();
        }
        //�L��ù��W
        SDL_RenderPresent(renderer);
        resetOffset();
        resetMouseOffset();
        
        //�ѹ����ʪ��ɶ����j(300�@��(0.3��)���@���A�@�� = 1/1000��)
        if(mouseTimer >= MOUSE_MOVE_INTERVAL){
            randomMouseOffset(); //�ѹ��H�����Y�Ӥ�V�]
            mouseTimer = 0;// ���m�p�ɾ�
        }
        
        //�p�G�C������(��q0�B�ɶ���) **�o�̭n�K�[�C�����ѿﶵ(���ѵe���B�߰ݬO�_����)  �ثe�ȮɬO�Lgame over���� �M��reset���� �٨S���]�p���Ѫ��ﶵ
        if(lose && win == false){
            SDL_Rect gameover_rect = {.h = 300, .w = 300, .x = 150, .y = 150};
            SDL_RenderCopy(renderer, wordlePageOption[wordle_page_gameover].sixType, NULL, &gameover_rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            initCoordinate();
            initMouse();
            initHp();
            //��l�ƨC�@�����I�]���ܯȱ�
            initBagHintPicture();
            lose = false;
        }
        //�p�G�C���ӧQ(�q�Lwordle�����_�� �i�J��_�Ӫ����A�e�i�U�@��)  **���� �ثe�٨S���U�@��  
        if(win && lose == false){
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            quit = true;
        }
        
            
    }
}


//�C����������O����

void closeSDL(){
    SDL_DestroyTexture(characterTexture);
    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(computerTexture);
    SDL_DestroyTexture(floorTexture);
    SDL_DestroyTexture(whiteMouseTexture);
    SDL_DestroyTexture(blackMouseTexture);
    SDL_DestroyTexture(crashMessageTexture);
    SDL_DestroyTexture(hp_fullTexture);
    SDL_DestroyTexture(hp_emptyTexture);
    SDL_DestroyTexture(hp_breakTexture);
    SDL_DestroyTexture(doorTexture);
    SDL_DestroyTexture(doorCloseTexture);
    SDL_DestroyTexture(doorOpenTexture);
    SDL_DestroyTexture(pressToEnterTexture);
    SDL_DestroyTexture(bag1Texture);
    SDL_DestroyTexture(bag2Texture);
    SDL_DestroyTexture(bag3Texture);
    SDL_DestroyTexture(bagInnerTexture);
    SDL_DestroyTexture(oopsTexture);
    SDL_DestroyTexture(HPrecoverTexture);
    SDL_DestroyTexture(gotSomethingTexture);
    SDL_DestroyTexture(attackedTexture);
    //letter
    for(int i = 0; i<TOTAL_LETTERS; i++)
        SDL_DestroyTexture(letters[i].wordle_letterTexture);
    //3desktop
    for(int i = 0; i<3; i++)
        SDL_DestroyTexture(computerDesktop[i].threeType);
    //���ε{���ϥ�(4�� + 4�i�Ӥ�)
    for(int i = 0; i<8; i++)
        SDL_DestroyTexture(computerApp[i].eightType);
    //wordle(�W�h�I���ϥ�(�ݸ�)�B�h�X�ϥ�)�B���\�e���Bwordle�D����
    for(int i = 0; i<6; i++)
        SDL_DestroyTexture(wordlePageOption[i].sixType);
    //�C�@��r�����A(��B���B��)
    for(int i = 0; i<3; i++)
        SDL_DestroyTexture(letterColor[i].threeType);
    //�I�]
    for(int i = 0; i<9; i++)
        SDL_DestroyTexture(bagStore[i].hintType);
        
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
