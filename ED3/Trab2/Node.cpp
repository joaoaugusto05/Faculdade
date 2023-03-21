#include "Node.hpp"  

Node::Node(REGISTER r)
{ 

	distancia = r.distProxEstacao;
	linhas.insert(pair< string, int> (r.nomeLinha, r.codProxEstacao));
    
}

Node::Node(int estInt)
{ 

	distancia = 0;
	linhas.insert(pair< string, int> ("Integracao", estInt));
    
}

