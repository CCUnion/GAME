/*
1.�C���y�{ : �C���}�l�e���}�l -> ���d1 -> ���d2 -> ���d3 -> (������) -> �u���� -> �C����������O����
2.����(�ɶ��B�S��)�B���s�}�l�B�i�J�U�@��������P�_(enum)
3.��ӹC�������O�o����O����
*/

#ifndef GAME_H
#define GAME_H

//�q��
void computer();

//wordle **�h�Xwordle��wordleEvent == false
void wordle(bool *wordleEvent);

//�C���}�l�e��
void start();

//���d1
void level_1();

//���d2
void level_1();

//���d3
void level_1();

//�u����
void true_end();

//������
void fake_end();

//��ӹC����������O����
void closeSDL();

#endif