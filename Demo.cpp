#include <iostream>
#include <stdlib.h>
#include "Node.h"
#include "CMap.h"
#include "Edge.h"
using namespace std;


/********************模拟图的邻接矩阵存储和深度优先遍历和广度优先遍历***************************/
/*
例：图的结构如下：无向图1
                        A
                      /   \
					B      D
				   / \    / \
                  C   F  G - H
				   \ /
					E
					
深度优先遍历：A B C E F D G H (类似于前序遍历：根左右)

广度优先遍历：A B D C F G H E 

图1的邻接矩阵：
   A B C D E F G H
A  0 1 0 1 0 0 0 0
B  1 0 1 0 0 1 0 0
C  0 1 0 0 1 0 0 0
D  1 0 0 0 0 0 1 1
E  0 0 1 0 0 1 0 0
F  0 1 0 0 1 0 0 0
G  0 0 0 1 0 0 0 1
H  0 0 0 1 0 0 1 0

#####################最小生成树###############################
图的结构：无项图2：
               A
			 / | \
		   	B--F--E
			\ / \ /
			 C - D
索引：A B C D E F 
      0 1 2 3 4 5

边上的权值：
 A-B: 6   A-F: 1  A-E: 5
 B-C: 3   B-F: 2
 C-F: 8   C-D: 7
 D-F: 4   D-E: 2
 E-F: 9

 邻接矩阵：
    A B C D E F 
 A  0 6 0 0 5 1 
 B  6 0 3 0 0 2
 C  0 3 0 7 0 8 
 D  0 0 7 0 2 4 
 E  5 0 0 2 0 9 
 F  1 2 8 4 9 0 

 最小生成树：A--F--B--C--D--E


*/


int main(void)
{
	/*******************无向图1的测试代码**********************/
	////定义图指针
	//CMap *pMap = new CMap(8);

	////定义节点
	//Node *pNodeA = new Node('A');
	//Node *pNodeB = new Node('B');
	//Node *pNodeC = new Node('C');
	//Node *pNodeD = new Node('D');
	//Node *pNodeE = new Node('E');
	//Node *pNodeF = new Node('F');
	//Node *pNodeG = new Node('G');
	//Node *pNodeH = new Node('H');

	////增加节点
	//pMap->addNode(pNodeA);
	//pMap->addNode(pNodeB);
	//pMap->addNode(pNodeC);
	//pMap->addNode(pNodeD);
	//pMap->addNode(pNodeE);
	//pMap->addNode(pNodeF);
	//pMap->addNode(pNodeG);
	//pMap->addNode(pNodeH);

	////无向图：设置边的值,形成邻接矩阵
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

	//pMap->depthFirstTraverse(0); //深度优先遍历：以A为起始点，即其索引：1

	//pMap->resetNode();  //将节点进行重置
	//cout << endl;

	//pMap->breadthFirstTraverse(0); //广度优先遍历：设置A为起始点

	//pMap->resetNode();


	/*************************无向图2的测试代码*******************************/

	CMap *pMap = new CMap(6);

	//定义图的节点
	Node *pNodeA = new Node('A');
	Node *pNodeB = new Node('B');
	Node *pNodeC = new Node('C');
	Node *pNodeD = new Node('D');
	Node *pNodeE = new Node('E');
	Node *pNodeF = new Node('F');

	//设置图的节点
	pMap->addNode(pNodeA);
	pMap->addNode(pNodeB);
	pMap->addNode(pNodeC);
	pMap->addNode(pNodeD);
	pMap->addNode(pNodeE);
	pMap->addNode(pNodeF);

	//设置边权值
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