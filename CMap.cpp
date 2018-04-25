#include <iostream>
#include "CMap.h"
#include <vector>
#include "Node.h"
#include "Edge.h"
using namespace std;

//构造函数
CMap::CMap(int capacity)
{
	m_iCapacity = capacity;
	m_iNodeCount = 0;
	m_pNodeArray = new Node[m_iCapacity];   //节点数组
	m_pMatrix = new int[m_iCapacity*m_iCapacity];  //邻接矩阵
	//memset(m_pMatrix,0,m_iCapacity*m_iCapacity*sizeof(int));  //初始化邻接矩阵memset(指针，数值，总内存字节数)：将数字以单个字节逐个拷贝的方式放到指定的内存中去,同下面的循环作用一样
	for (int i = 0; i < m_iCapacity*m_iCapacity; i++)
	{
		m_pMatrix[i] = 0;
	}

	m_pEdge = new Edge[m_iCapacity - 1];  //边的集合，申请内存
}


//析构函数
CMap::~CMap()
{
	delete[]m_pNodeArray;
	delete[]m_pMatrix;
}


bool CMap::addNode(Node *pNode)
{
	m_pNodeArray[m_iNodeCount].m_cData = pNode->m_cData;  //数组下标即索引
	m_iNodeCount++;
	return true;
}

void CMap::resetNode()
{
	for (int i = 0; i < m_iNodeCount; i++)
	{
		m_pNodeArray[i].m_bIsVisited = false;  //false表示未被访问，将图中所有顶点的标识设为false
	}
}

bool CMap::setValueToMatrixForDirectedGraph(int row, int col, int val)  //有向图
{
	if (row < 0 || row >= m_iCapacity)
	{
		return false;
	}
	if (col<0 || col > m_iCapacity)
	{
		return false;
	}
    m_pMatrix[row*m_iCapacity + col] = val;
    return true;
}

bool CMap::setValueToMatrixForUndirectedGraph(int row, int col, int val)  //无向图
{
	if (row < 0 || row >= m_iCapacity)
	{
		return false;
	}
	if (col<0 || col > m_iCapacity)
	{
		return false;
	}
	m_pMatrix[row*m_iCapacity + col] = val;
	m_pMatrix[col*m_iCapacity + row] = val;  //设置对称位置的值
	return true;
}

bool CMap::getValueFromMatrix(int row, int col, int &val)//获取（row, col）位置的值
{
	if (row < 0 || row >= m_iCapacity)
	{
		return false;
	}
	if (col<0 || col > m_iCapacity)
	{
		return false;
	}
	val = m_pMatrix[row*m_iCapacity + col];
	return true;
}

void CMap::printMatrix()
{
	for (int i = 0; i < m_iCapacity; i++)
	{
		for (int k = 0; k < m_iCapacity; k++)
		{
			cout << m_pMatrix[i*m_iCapacity + k] << " ";
		}
		cout << endl;
	}
}


//深度优先遍历
void CMap::depthFirstTraverse(int nodeIndex)
{
	int value = 0;

	cout << m_pNodeArray[nodeIndex].m_cData << " ";  //先根节点
	m_pNodeArray[nodeIndex].m_bIsVisited = true;   //将该节点标识设置为已经访问
	//遍历邻接矩阵，看当前节点和哪些点相连接
	for (int i = 0; i < m_iCapacity; i++)
	{
		getValueFromMatrix(nodeIndex, i, value);//取出相应的弧
		if (value == 1)
		{
			if (m_pNodeArray[i].m_bIsVisited)//当前联通的点已经被访问
			{
				continue;
			}
			else
				depthFirstTraverse(i);
		}
		else
		{
			continue;
		}
	}
}

void CMap::breadthFirstTraverse(int nodeIndex)
{
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	vector<int> curVec;
	curVec.push_back(nodeIndex);  //保存当前节点

	breadthFirthTraverseImpl(curVec);

}

void CMap::breadthFirthTraverseImpl(vector<int> preVec)
{
	int value = 0;
	vector<int> curVec;

	for (int j = 0; j < int(preVec.size()); j++)
	{
		for (int i = 0; i < m_iCapacity; i++)
		{
			getValueFromMatrix(preVec[j], i, value);
			if (value != 0)
			{
				if (m_pNodeArray[i].m_bIsVisited)
				{
					continue;
				}
				else
				{
					cout << m_pNodeArray[i].m_cData << " ";
					m_pNodeArray[i].m_bIsVisited = true;

					curVec.push_back(i);  //将与当前点相连接的点存入curVec
				}
			}
			else
			{
				continue;
			}
		}
	}
	if (curVec.size() == 0)
	{
		return;
	}
	else
	{
		breadthFirthTraverseImpl(curVec);  //递归
	}
}


//普里姆算法实现
void CMap::primTree(int nodeIndex)
{
	int value = 0;  //权值
	int edgeCount = 0;
	vector<int> nodeVec;  //点的集合
	vector<Edge> edgeVec; //边的集合

	cout << m_pNodeArray[nodeIndex].m_cData << endl;

	nodeVec.push_back(nodeIndex);
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	//结束条件:边数=点数-1
	while(edgeCount < m_iCapacity - 1)
	{
		int temp = nodeVec.back();
		for (int i = 0; i < m_iCapacity; i++)
		{
			getValueFromMatrix(temp, i, value);
			if (value != 0)
			{
				if (m_pNodeArray[i].m_bIsVisited)
				{
					continue;
				}
				else
				{
					Edge edge(temp, i, value); //形成边对象
					edgeVec.push_back(edge);  //将边对象存入边集合
				}
			}
		}
		//从候选边集合中选出最小权值的边
		int edgeIndex = getMinEdge(edgeVec);
		edgeVec[edgeIndex].m_bSelected = true;

		cout << edgeVec[edgeIndex].m_iNodeIndexA << "---->" << edgeVec[edgeIndex].m_iNodeIndexB << ": ";
		cout << edgeVec[edgeIndex].m_iWeightValue << endl;

		m_pEdge[edgeCount] = edgeVec[edgeIndex];
		edgeCount++;

		int nextNodeIndex = edgeVec[edgeIndex].m_iNodeIndexB;

		nodeVec.push_back(nextNodeIndex);
		m_pNodeArray[nextNodeIndex].m_bIsVisited = true;
		cout << m_pNodeArray[nextNodeIndex].m_cData << endl;
	}

}

int CMap::getMinEdge(vector<Edge> edgeVec)  //声明获取最小边的函数
{
	int minWeight = 0;
	int edgeIndex = 0;
	int i = 0;
	for (; i < int(edgeVec.size()); i++)
	{
		if (!edgeVec[i].m_bSelected)
		{
			minWeight = edgeVec[i].m_iWeightValue;  //获取权值
			edgeIndex = i;  //获取边的索引
			break;
		}
	}
	//没有取到最小边
	if (minWeight == 0)
	{
		return -1;
	}

	for (; i < int(edgeVec.size()); i++)
	{
		if (edgeVec[i].m_bSelected)
		{
			continue;
		}
		else
		{
			if (minWeight > edgeVec[i].m_iWeightValue)
			{
				minWeight = edgeVec[i].m_iWeightValue;
				edgeIndex = i;
			}
		}
	}


	return edgeIndex;
}


//克鲁斯卡尔算法生成树
void CMap::kruskalTree()
{
	int value = 0;
	int edgeCount = 0;

	vector<vector<int>> nodeSets;

	//第一步：遍历邻接矩阵上三角的数据，取出所有边
	vector<Edge> edgeVec;

	for (int i = 0; i < m_iCapacity; i++)
	{
		for (int k = i + 1; k < m_iCapacity; k++)
		{
			getValueFromMatrix(i, k, value);
			if (value != 0)
			{
				Edge edge(i, k, value);
				edgeVec.push_back(edge);
			}
		}
	}

	//第二步：从所有边中取出组成最小生成树的边

	//1.找到算法结束条件
	while (edgeCount < m_iCapacity - 1)  //最小生成树的边数 = 点数-1
	{

		//2.从边集合中找到最小边
		int minEdgeIndex = getMinEdge(edgeVec);

		edgeVec[minEdgeIndex].m_bSelected = true;

		//3.找出最小边连接的两个点
		int nodeAIndex = edgeVec[minEdgeIndex].m_iNodeIndexA;  //最小边的A点索引
		int nodeBIndex = edgeVec[minEdgeIndex].m_iNodeIndexB;  //最小边的B点索引

		bool nodeAIsInSet = false;
		bool nodeBIsInSet = false;

		int nodeAInSetLable = -1;
		int nodeBInSetLable = -1;

		//4.找出点所在的点集合
		for (int i = 0; i < int(nodeSets.size()); i++)
		{
			nodeAIsInSet = isInSet(nodeSets[i], nodeAIndex);
			if (nodeAIsInSet)
			{
				nodeAInSetLable = i;
			}
		}
		for (int i = 0; i < int(nodeSets.size()); i++)
		{
			nodeBIsInSet = isInSet(nodeSets[i], nodeBIndex);
			if (nodeBIsInSet)
			{
				nodeBInSetLable = i;
			}
		}

		//5.根据点所在集合的不同作出不同处理
		if (nodeAInSetLable == -1 && nodeBInSetLable == -1)
		{
			vector<int> vec;
			vec.push_back(nodeAIndex);
			vec.push_back(nodeBIndex);
			nodeSets.push_back(vec);
		} 

		else if (nodeAInSetLable == -1 && nodeBInSetLable != -1)
		{
			nodeSets[nodeBInSetLable].push_back(nodeAIndex);
		}

		else if (nodeAInSetLable != -1 && nodeBInSetLable == -1)
		{
			nodeSets[nodeAInSetLable].push_back(nodeBIndex);
		}

		else if (nodeAInSetLable != -1 && nodeBInSetLable != -1 && nodeAInSetLable != nodeBInSetLable)
		{
			mergeNodeSet(nodeSets[nodeAInSetLable], nodeSets[nodeBInSetLable]);
			for (int k = nodeBInSetLable; k < int(nodeSets.size()) - 1; k++)
			{
				nodeSets[k] = nodeSets[k + 1];
			}
		}

		else if (nodeAInSetLable != -1 && nodeBInSetLable != -1 && nodeAInSetLable == nodeBInSetLable)
		{
			continue;
		}

		m_pEdge[edgeCount] = edgeVec[minEdgeIndex];
		edgeCount++;
		
		cout << edgeVec[minEdgeIndex].m_iNodeIndexA << "---" << edgeVec[minEdgeIndex].m_iNodeIndexB << ":  ";
		cout << edgeVec[minEdgeIndex].m_iWeightValue << endl;

	}
}

bool CMap::isInSet(vector<int> nodeSet, int target)  //判断顶点是否在点集合中
{
	for (int i = 0; i < int(nodeSet.size()); i++)
	{
		if (nodeSet[i] == target)
		{
			return true;
		}
	}
	return false;
}

void CMap::mergeNodeSet(vector<int> &nodeSetA, vector<int> nodeSetB) //合并两个顶点的集合到nodeSetA
{
	for (int i = 0; i < int(nodeSetB.size()); i++)
	{
		nodeSetA.push_back(nodeSetB[i]);
	}

}