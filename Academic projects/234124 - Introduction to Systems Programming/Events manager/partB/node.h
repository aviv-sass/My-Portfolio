#ifndef NODE_H_
#define NODE_H_
#include <iostream>

using namespace std;

namespace mtm{
    template<class T>
    class PriorityQueue;
    template<class T>
    class Node{
            friend class PriorityQueue<T>;
            T data;
            Node *next;
        public:
            Node():data(nullptr),next(nullptr){}
            Node(Node &copy_node):data(copy_node.data),next(copy_node.next){}
            
            /**
            * nodeSetNext: set the next node after this node.
            * @param Node - Target node to set next.
            */  
            void nodeSetNext(Node *node_next){
                next = node_next;
            }
                        
            /**
            * nodeSetData: set the data node.
            * @param Node - Target data.
            */  
            void nodeSetData(const T& node_data){
                data = node_data;
            }
            Node& operator=(const Node& node){
                data = node.data;
                next = node.next;
                return *this;
            }

            /**
            * nodeGetData: get the data node.
            * @return :
            * 	a data type.
            */  
            T nodeGetData(){
                return data;
            } 

            /**
            * nodeGetNext: get the next node.
            * @return :
            * 	a pointer of node.
            */      
            Node* nodeGetNext(){
                return next;
            }
            ~Node(){}
    };
}
#endif