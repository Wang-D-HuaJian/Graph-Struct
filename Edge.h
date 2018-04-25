#ifndef EDGE_H
#define EDGE_H




class Edge
{
public:

	Edge(int nodeIndexA = 0, int nodeIndexB = 0, int weightValue = 0);  //构造函数
	int m_iNodeIndexA;  //边的其中一个顶点
	int m_iNodeIndexB;  //边的另一个顶点
	int m_iWeightValue; //权值
	bool m_bSelected;  //边的标识符
};
#endif