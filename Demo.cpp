#include <iostream>
#include <stdlib.h>
#include "Node.h"
#include "CMap.h"
#include "Edge.h"
using namespace std;


/********************ģ��ͼ���ڽӾ���洢��������ȱ����͹�����ȱ���***************************/
/*
����ͼ�Ľṹ���£�����ͼ1
                        A
                      /   \
					B      D
				   / \    / \
                  C   F  G - H
				   \ /
					E
					
������ȱ�����A B C E F D G H (������ǰ�������������)

������ȱ�����A B D C F G H E 

ͼ1���ڽӾ���
   A B C D E F G H
A  0 1 0 1 0 0 0 0
B  1 0 1 0 0 1 0 0
C  0 1 0 0 1 0 0 0
D  1 0 0 0 0 0 1 1
E  0 0 1 0 0 1 0 0
F  0 1 0 0 1 0 0 0
G  0 0 0 1 0 0 0 1
H  0 0 0 1 0 0 1 0

#####################��С������###############################
ͼ�Ľṹ������ͼ2��
               A
			 / | \
		   	B--F--E
			\ / \ /
			 C - D
������A B C D E F 
      0 1 2 3 4 5

���ϵ�Ȩֵ��
 A-B: 6   A-F: 1  A-E: 5
 B-C: 3   B-F: 2
 C-F: 8   C-D: 7
 D-F: 4   D-E: 2
 E-F: 9

 �ڽӾ���
    A B C D E F 
 A  0 6 0 0 5 1 
 B  6 0 3 0 0 2
 C  0 3 0 7 0 8 
 D  0 0 7 0 2 4 
 E  5 0 0 2 0 9 
 F  1 2 8 4 9 0 

 ��С��������A--F--B--C--D--E


*/


int main(void)
{
	/*******************����ͼ1�Ĳ��Դ���**********************/
	////����ͼָ��
	//CMap *pMap = new CMap(8);

	////����ڵ�
	//Node *pNodeA = new Node('A');
	//Node *pNodeB = new Node('B');
	//Node *pNodeC = new Node('C');
	//Node *pNodeD = new Node('D');
	//Node *pNodeE = new Node('E');
	//Node *pNodeF = new Node('F');
	//Node *pNodeG = new Node('G');
	//Node *pNodeH = new Node('H');

	////���ӽڵ�
	//pMap->addNode(pNodeA);
	//pMap->addNode(pNodeB);
	//pMap->addNode(pNodeC);
	//pMap->addNode(pNodeD);
	//pMap->addNode(pNodeE);
	//pMap->addNode(pNodeF);
	//pMap->addNode(pNodeG);
	//pMap->addNode(pNodeH);

	////����ͼ�����ñߵ�ֵ,�γ��ڽӾ���
	//pMap->setValueToMatrixForUndirectedGraph(0, 1);
	//pMap->setValueToMatrixForUndirectedGraph(0, 3);
	//pMap->setValueToMatrixForUndirectedGraph(1, 2);
	//pMap->setValueToMatrixForUndirectedGraph(1, 5);
	//pMap->setValueToMatrixForUndirectedGraph(2, 4);
	//pMap->setValueToMatrixForUndirectedGraph(3, 6);
	//pMap->setValueToMatrixForUndirectedGraph(3, 7);
	//pMap->setValueToMatrixForUndirectedGraph(4, 5);
	//pMap->setValueToMatrixForUndirectedGraph(6, 7);

	//pMap->printMatrix();

	//cout << endl;

	//pMap->depthFirstTraverse(0); //������ȱ�������AΪ��ʼ�㣬����������1

	//pMap->resetNode();  //���ڵ��������
	//cout << endl;

	//pMap->breadthFirstTraverse(0); //������ȱ���������AΪ��ʼ��

	//pMap->resetNode();


	/*************************����ͼ2�Ĳ��Դ���*******************************/

	CMap *pMap = new CMap(6);

	//����ͼ�Ľڵ�
	Node *pNodeA = new Node('A');
	Node *pNodeB = new Node('B');
	Node *pNodeC = new Node('C');
	Node *pNodeD = new Node('D');
	Node *pNodeE = new Node('E');
	Node *pNodeF = new Node('F');

	//����ͼ�Ľڵ�
	pMap->addNode(pNodeA);
	pMap->addNode(pNodeB);
	pMap->addNode(pNodeC);
	pMap->addNode(pNodeD);
	pMap->addNode(pNodeE);
	pMap->addNode(pNodeF);

	//���ñ�Ȩֵ
	pMap->setValueToMatrixForUndirectedGraph(0, 1, 6);
	pMap->setValueToMatrixForUndirectedGraph(0, 5, 1);
	pMap->setValueToMatrixForUndirectedGraph(0, 4, 5);
	pMap->setValueToMatrixForUndirectedGraph(1, 2, 3);
	pMap->setValueToMatrixForUndirectedGraph(1, 5, 2);
	pMap->setValueToMatrixForUndirectedGraph(2, 5, 8);
	pMap->setValueToMatrixForUndirectedGraph(2, 3, 7);
	pMap->setValueToMatrixForUndirectedGraph(3, 5, 4);
	pMap->setValueToMatrixForUndirectedGraph(3, 4, 2);
	pMap->setValueToMatrixForUndirectedGraph(4, 5, 9);

  //pMap->printMatrix();

  //pMap->primTree(0);
	pMap->kruskalTree();
	


	system("pause");
	return 0;
}