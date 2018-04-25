#ifndef NODE_H
#define NODE_H

class Node
{
public:

	Node(char data = 0); //构造函数
	char m_cData;        //节点信息成员
	bool m_bIsVisited;   //表示当前节点是否被访问过，是，则true
};




#endif