#include "Node.hpp"  
#include <sstream> 


Node::Node(REGISTER r)
{
    stringstream ss;
    ss << r.nomeEstacao;
    nome_estacao = ss.str();    

}
Node::Node(){
    cout << "AAAAAAAAAAAA";
}
