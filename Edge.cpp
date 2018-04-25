#include "Edge.h"

Edge::Edge(int nodeIndexA, int nodeIndexB, int weightValue) //微软的编译器在实现里不能赋予默认值
{
	m_iNodeIndexA = nodeIndexA;
	m_iNodeIndexB = nodeIndexB;
	m_iWeightValue = weightValue;
	m_bSelected = false;
}