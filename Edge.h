#ifndef EDGE_H
#define EDGE_H




class Edge
{
public:

	Edge(int nodeIndexA = 0, int nodeIndexB = 0, int weightValue = 0);  //���캯��
	int m_iNodeIndexA;  //�ߵ�����һ������
	int m_iNodeIndexB;  //�ߵ���һ������
	int m_iWeightValue; //Ȩֵ
	bool m_bSelected;  //�ߵı�ʶ��
};
#endif