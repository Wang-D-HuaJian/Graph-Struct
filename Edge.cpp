#include "Edge.h"

Edge::Edge(int nodeIndexA, int nodeIndexB, int weightValue) //΢��ı�������ʵ���ﲻ�ܸ���Ĭ��ֵ
{
	m_iNodeIndexA = nodeIndexA;
	m_iNodeIndexB = nodeIndexB;
	m_iWeightValue = weightValue;
	m_bSelected = false;
}