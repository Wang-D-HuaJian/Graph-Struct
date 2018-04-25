#include "Node.h"


Node::Node(char data)
{
	m_cData = data;
	m_bIsVisited = false;  //初始化为false，表示未被访问
}