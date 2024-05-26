/*
1.�������󤧶��I�������Y�G����B�a�ϡB�Ǫ������ʬO�_�X�z�A����M�Ǫ��I���᪺����
2.�P�_���ʬO�_�X�z�A�^��bool�Ȩ�move.c������y�Ч��ܻP�_���P�_��function
*/

#ifndef COLLISION_H
#define COLLISION_H

//���Ⲿ�ʻP�_(�P�_�U�@�B�M�a�����Y)
bool characterMoveOrNot(void);

//�ھڨ��Ⲿ��(characterMoveOrNot)�A�p�G�U�@�B���O�Ŧa(false)�A�P�_�O�_���q��(�άO��L���ʿﶵ) �^�ǽs��(ex.�q�� == 2)
int nextStepIsComputerOrNot();

//�a�ϲ��ʻP�_(�M���Ⲿ�ʬ���)
bool mapMoveOrNot(void);

//�ѹ����ʻP�_(�M�a�Ϭ���)
bool mouseMoveOrNot(struct mouse *eachMouse);

//����M�Ǫ����I��(�P�_�C�@���ѹ�(���ʫ�)���y�СA�M����(���ʫ�)���y�СA��̦��L���|)
bool characterMeetsMouseOrNot(struct mouse *eachmouse);

//�ƹ��O�_�I��app�ϥ�
int clickAppOrNot(int x, int y);

//�ƹ��O�_�I��wordle option�ϥ�
int clickWordleOptionOrNot(int x, int y);

//�P�_��J�r���M����(����)�O�_�X�z
bool wordleLettersLensIsLegal(int num_column, int num_row, int letter);

#endif