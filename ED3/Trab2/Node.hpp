#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <map>

#include "define.h"
using namespace std;



class Node

{	
	public:
		string nome_ProxEstacao;
		int distancia;
		map<string, int> linhas;
		Node(REGISTER r);
		Node(int estInt);

};

typedef map<string, map<string, Node>> Grafo;
typedef map<string, Node>::iterator itr;


#endif