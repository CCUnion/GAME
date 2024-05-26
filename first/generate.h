/*
1.�⪫��Ϥ��L��ù��W�A���Ǭ��a�O >> ��� >> ���� >>�@�ѹ��@>> ��L����
2.�᭱�L�W�h���Ϥ��|�л\�즳���Ϫ������e�� *�e���Q�л\����m�M���n�O�n�L�W�h���Ϥ��]�w���y�ЩM�j�p
3.����M�ѹ��I���S��(�ȩw)
4.�զѹ������(�^��B���ܡB�b�t)
*/

#ifndef GENERATE_H
#define GENERATE_H

//�a�O
void generateFloor(void);

//�a�Ϫ���
void generateMap(void);

//����
void generateCharacter(dir direction);

//�ѹ�
void generateMouse(void);

//����B�ѹ����I���S��
void crashMessage();

//��q(hp) �a�ϥk�W��(����k)
void generateHP();

//�զѹ������(�^��B���ܡB�b�t) **�����٨S���B�b�t�����٨S��
void luckyDraw();

//�q�����J���ʵe
void computerDesktopLoading();

//�ୱ�MĲ���ﶵ(���ε{��)
void deskTop();

//�ୱapp
void deskTopApp(int x, int y, bool *wordleEvent, bool *itemValue);

//wordle����
void wordlePage(int num_row, int num_column, int wordle_success);

//wordle�ﶵ2(rule�Bquit)���ƥ�(1.�I���d�ݳW�h�B2.�h�Xwordle�^��ୱ)
void wordlePageOptionEvent(int x, int y, bool *wordleQuit, bool *itemValue);

//�D�a�ϫ�e���}�I�]���ʵe
void openBagAnimation();

//���}�I�]
void bagInnerItems();

#endif