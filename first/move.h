/*
1.���󲾰ʫ�y�СB�ƭȧ��ܻP�_�A�ھ�collision��bool�^�ǭȧP�_
2.���󪺰����q�k�s
3.�ھڦѹ����H����V�ᤩ�ѹ������������q(�U�@�B�����Ӥ�V���O�H�����Aoffset���Ȯھڤ�V���P�Ӥ��P)
4.����M�ѹ����I���P�_(�P�_�O�_�I�sgenerate.c�������\��(�I���S�ĵ���))
*/

#ifndef MOVE_H
#define MOVE_H

//����y�Ч��ܡG�p�G1.�a�Ϥ��ʡB2.���Ⲿ�ʦX�z 
void characterMove();

//�a�Ϯy�Ч��ܡG�p�G1.���Ⲿ�ʡB2.�a�ϲ��ʦX�z 
void mapMove();

//�p�G�ѹ����ʦX�z �ѹ��y�Ч���
void mousemove(struct mouse *eachMouse);

//���ʫ�a�ϡB���⪺�����q�k�s
void resetOffset();

//�ѹ��C�����ʫ᰾���q�k�s
void resetMouseOffset(void);

//�H���������q
void randomMouseOffset(void);

//�p�G���ʫ᪺�ѹ��M����y�Ц����| �I�sgenerate.c���I���ƥ�
void characterMeetsMouse(struct mouse *eachMouse);

//���⦩��Υ[��
void hpCondition(hp_event event);

//�ھ�collision.c��wordleLettersLensIsLegal�P�_�r����J�O�_���� ����wordle�x�s�����A
void wordleLettersInput(int *num_row, int *num_column, int letter, int *wordle_success);

#endif