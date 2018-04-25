#ifndef CMAP_H
#define CMAP_H
#include "Node.h"
#include<vector>
#include "Edge.h"
using namespace std;

class CMap
{
public:
	CMap(int capacity);  //���캯��
	~CMap();  //��������
	bool addNode(Node *pNode);  //��ͼ�м��붥�㣨�ڵ㣩
	void resetNode();              //���ö��㣬����Ϊδ������
	bool setValueToMatrixForDirectedGraph(int row, int col, int val = 1);  //Ϊ����ͼ�����ڽӾ���
	bool setValueToMatrixForUndirectedGraph(int row, int col, int val = 1);//Ϊ����ͼ�����ڽӾ���

	void printMatrix();  //��ӡ�ڽӾ���

	void depthFirstTraverse(int nodeIndex);  //������ȱ���
	void breadthFirstTraverse(int nodeIndex);//������ȱ���
   
	//��С�������㷨������ķ�㷨��������Ѱ����СȨֵ�ıߣ�
	void primTree(int nodeIndex);  //nodeIndexΪ���ĵ�һ����

	//��³˹�����㷨Ѱ����С������
	void kruskalTree();

private:
	bool getValueFromMatrix(int row, int col, int &val);  //�Ӿ����л�ȡȨֵ
	void breadthFirthTraverseImpl(vector<int> preVec);  //������ȱ���ʵ�ֺ���
	int getMinEdge(vector<Edge> edgeVec);  //������ȡ��С�ߵĺ���
	bool isInSet(vector<int> nodeSet, int target);  //�ж϶����Ƿ��ڵ㼯����
	void mergeNodeSet(vector<int> &nodeSetA, vector<int> nodeSetB); //�ϲ���������ļ���,ǰ��һ��Ϊ���ϵ����ã���Ϊ�˺�����ȡ������


private:
	int m_iCapacity;      //ͼ�����������ɵĶ�����
	int m_iNodeCount;     //�Ѿ���ӵĶ�����
	Node *m_pNodeArray;   //������Ŷ������
	int *m_pMatrix;       //��������ڽӾ���

	Edge *m_pEdge;  //������СȨֵ�ı�
};



#endif