#ifndef CMAP_H
#define CMAP_H
#include "Node.h"
#include<vector>
#include "Edge.h"
using namespace std;

class CMap
{
public:
	CMap(int capacity);  //构造函数
	~CMap();  //析构函数
	bool addNode(Node *pNode);  //向图中加入顶点（节点）
	void resetNode();              //重置顶点，都设为未被访问
	bool setValueToMatrixForDirectedGraph(int row, int col, int val = 1);  //为有向图设置邻接矩阵
	bool setValueToMatrixForUndirectedGraph(int row, int col, int val = 1);//为无向图设置邻接矩阵

	void printMatrix();  //打印邻接矩阵

	void depthFirstTraverse(int nodeIndex);  //深度优先遍历
	void breadthFirstTraverse(int nodeIndex);//广度优先遍历
   
	//最小生成树算法：普利姆算法（按点来寻找最小权值的边）
	void primTree(int nodeIndex);  //nodeIndex为树的第一个点

	//克鲁斯卡尔算法寻找最小生成树
	void kruskalTree();

private:
	bool getValueFromMatrix(int row, int col, int &val);  //从矩阵中获取权值
	void breadthFirthTraverseImpl(vector<int> preVec);  //广度优先遍历实现函数
	int getMinEdge(vector<Edge> edgeVec);  //声明获取最小边的函数
	bool isInSet(vector<int> nodeSet, int target);  //判断顶点是否在点集合中
	void mergeNodeSet(vector<int> &nodeSetA, vector<int> nodeSetB); //合并两个顶点的集合,前面一个为集合的引用，是为了后续的取出操作


private:
	int m_iCapacity;      //图中最多可以容纳的顶点数
	int m_iNodeCount;     //已经添加的顶点数
	Node *m_pNodeArray;   //用来存放顶点矩阵
	int *m_pMatrix;       //用来存放邻接矩阵

	Edge *m_pEdge;  //保存最小权值的边
};



#endif