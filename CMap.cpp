#include <iostream>
#include "CMap.h"
#include <vector>
#include "Node.h"
#include "Edge.h"
using namespace std;

//���캯��
CMap::CMap(int capacity)
{
	m_iCapacity = capacity;
	m_iNodeCount = 0;
	m_pNodeArray = new Node[m_iCapacity];   //�ڵ�����
	m_pMatrix = new int[m_iCapacity*m_iCapacity];  //�ڽӾ���
	//memset(m_pMatrix,0,m_iCapacity*m_iCapacity*sizeof(int));  //��ʼ���ڽӾ���memset(ָ�룬��ֵ�����ڴ��ֽ���)���������Ե����ֽ���������ķ�ʽ�ŵ�ָ�����ڴ���ȥ,ͬ�����ѭ������һ��
	for (int i = 0; i < m_iCapacity*m_iCapacity; i++)
	{
		m_pMatrix[i] = 0;
	}

	m_pEdge = new Edge[m_iCapacity - 1];  //�ߵļ��ϣ������ڴ�
}


//��������
CMap::~CMap()
{
	delete[]m_pNodeArray;
	delete[]m_pMatrix;
}


bool CMap::addNode(Node *pNode)
{
	m_pNodeArray[m_iNodeCount].m_cData = pNode->m_cData;  //�����±꼴����
	m_iNodeCount++;
	return true;
}

void CMap::resetNode()
{
	for (int i = 0; i < m_iNodeCount; i++)
	{
		m_pNodeArray[i].m_bIsVisited = false;  //false��ʾδ�����ʣ���ͼ�����ж���ı�ʶ��Ϊfalse
	}
}

bool CMap::setValueToMatrixForDirectedGraph(int row, int col, int val)  //����ͼ
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

bool CMap::setValueToMatrixForUndirectedGraph(int row, int col, int val)  //����ͼ
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
	m_pMatrix[col*m_iCapacity + row] = val;  //���öԳ�λ�õ�ֵ
	return true;
}

bool CMap::getValueFromMatrix(int row, int col, int &val)//��ȡ��row, col��λ�õ�ֵ
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


//������ȱ���
void CMap::depthFirstTraverse(int nodeIndex)
{
	int value = 0;

	cout << m_pNodeArray[nodeIndex].m_cData << " ";  //�ȸ��ڵ�
	m_pNodeArray[nodeIndex].m_bIsVisited = true;   //���ýڵ��ʶ����Ϊ�Ѿ�����
	//�����ڽӾ��󣬿���ǰ�ڵ����Щ��������
	for (int i = 0; i < m_iCapacity; i++)
	{
		getValueFromMatrix(nodeIndex, i, value);//ȡ����Ӧ�Ļ�
		if (value == 1)
		{
			if (m_pNodeArray[i].m_bIsVisited)//��ǰ��ͨ�ĵ��Ѿ�������
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
	curVec.push_back(nodeIndex);  //���浱ǰ�ڵ�

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

					curVec.push_back(i);  //���뵱ǰ�������ӵĵ����curVec
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
		breadthFirthTraverseImpl(curVec);  //�ݹ�
	}
}


//����ķ�㷨ʵ��
void CMap::primTree(int nodeIndex)
{
	int value = 0;  //Ȩֵ
	int edgeCount = 0;
	vector<int> nodeVec;  //��ļ���
	vector<Edge> edgeVec; //�ߵļ���

	cout << m_pNodeArray[nodeIndex].m_cData << endl;

	nodeVec.push_back(nodeIndex);
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	//��������:����=����-1
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
					Edge edge(temp, i, value); //�γɱ߶���
					edgeVec.push_back(edge);  //���߶������߼���
				}
			}
		}
		//�Ӻ�ѡ�߼�����ѡ����СȨֵ�ı�
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

int CMap::getMinEdge(vector<Edge> edgeVec)  //������ȡ��С�ߵĺ���
{
	int minWeight = 0;
	int edgeIndex = 0;
	int i = 0;
	for (; i < int(edgeVec.size()); i++)
	{
		if (!edgeVec[i].m_bSelected)
		{
			minWeight = edgeVec[i].m_iWeightValue;  //��ȡȨֵ
			edgeIndex = i;  //��ȡ�ߵ�����
			break;
		}
	}
	//û��ȡ����С��
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


//��³˹�����㷨������
void CMap::kruskalTree()
{
	int value = 0;
	int edgeCount = 0;

	vector<vector<int>> nodeSets;

	//��һ���������ڽӾ��������ǵ����ݣ�ȡ�����б�
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

	//�ڶ����������б���ȡ�������С�������ı�

	//1.�ҵ��㷨��������
	while (edgeCount < m_iCapacity - 1)  //��С�������ı��� = ����-1
	{

		//2.�ӱ߼������ҵ���С��
		int minEdgeIndex = getMinEdge(edgeVec);

		edgeVec[minEdgeIndex].m_bSelected = true;

		//3.�ҳ���С�����ӵ�������
		int nodeAIndex = edgeVec[minEdgeIndex].m_iNodeIndexA;  //��С�ߵ�A������
		int nodeBIndex = edgeVec[minEdgeIndex].m_iNodeIndexB;  //��С�ߵ�B������

		bool nodeAIsInSet = false;
		bool nodeBIsInSet = false;

		int nodeAInSetLable = -1;
		int nodeBInSetLable = -1;

		//4.�ҳ������ڵĵ㼯��
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

		//5.���ݵ����ڼ��ϵĲ�ͬ������ͬ����
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

bool CMap::isInSet(vector<int> nodeSet, int target)  //�ж϶����Ƿ��ڵ㼯����
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

void CMap::mergeNodeSet(vector<int> &nodeSetA, vector<int> nodeSetB) //�ϲ���������ļ��ϵ�nodeSetA
{
	for (int i = 0; i < int(nodeSetB.size()); i++)
	{
		nodeSetA.push_back(nodeSetB[i]);
	}

}