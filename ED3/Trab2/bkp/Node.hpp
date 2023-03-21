#ifndef NODE_H
#define NODE_H

#include "define.h"


#include <iostream>
#include <string>
#include <vector>


using namespace std;



class adjacentes
{	public:
		string nome_ProxEstacao;
		int distancia;
		vector<string> linhas;

};

class Node  
{
	private:
		string nome_estacao;		
		vector<adjacentes> adj;
		
	public:

		Node(REGISTER r);
		Node();


};




#endif