#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "../partA/exceptions.h"
#include "node.h"
#include <iostream>
#include <ostream>
using std::cout;
using std::endl;
using namespace std;

namespace mtm{
    template<class T>
    class PriorityQueue{
        private:
            Node<T>* head;
            Node<T>* tail;
            Node<T>* iter = nullptr;
            int numOfNode;
            
        public:
            PriorityQueue():head(nullptr), tail(nullptr), numOfNode(0){}
            PriorityQueue (const PriorityQueue& pq_copy):head(nullptr),tail(nullptr),numOfNode(pq_copy.numOfNode){
                Node<T>* iterator = pq_copy.head;
                while(iterator != nullptr){
                    Node<T>* new_node = new Node<T>();
                    new_node->nodeSetData(iterator->data);
                    pqAddTail(new_node);
                    iterator = iterator->next;
                }
            }
            void pqAddTail(Node<T> *new_node){
                if (tail != nullptr){
                    tail->nodeSetNext(new_node);
                }
                tail = new_node;
                if (head == nullptr) {
                    head = new_node;
                }
            }
            bool pqContains(T data);
            void pqAddNode(T data);
            void pqRemoveNode(T data);
            int pqGetSize();
            Node<T>* pqGetFirstNode();
            T pqGetFirst();
            T pqGetLast();
            T pqGetNext();
            ~PriorityQueue();
    };

/**
* pqContains: check if the list contains the node.
* @param data - Target data.
* @return :
* 	true if the list is contains.
* 	Otherwise false.
*/
    template<class T>
    bool PriorityQueue<T>::pqContains(T data){
            Node<T>* node_temp = head;
            if(node_temp == nullptr){
                return false;
            }
            while(node_temp){
                if(*node_temp->data == *data){
                    return true;
                }
                node_temp = node_temp->next;
            }
            return false;
        }

/**
* pqAddNode: add the node to list, if data is NULL should do nothing.
* @param data - Target data.
*/
    template<class T>
    void PriorityQueue<T>::pqAddNode(T data){
        if(pqContains(data)){
            throw AlreadyRegistered();
        }
        numOfNode++;
        iter = nullptr;
        Node<T>* node_to_add = new Node<T>();//
        node_to_add->nodeSetData(data);
        if(head == nullptr){
            pqAddTail(node_to_add);
            return;
        }
        Node<T>* node_temp = head;
        if(head == tail){
            if(*data > *node_temp->data){
                pqAddTail(node_to_add);
                return;
            }
            head = node_to_add;
            head->nodeSetNext(tail);
            return;
        }
        Node<T>* node_prev = nullptr;
        Node<T>* node_current = head;
        while(*node_current->data < *data){
            if(node_current->next == nullptr){
                pqAddTail(node_to_add);
                return;
            }
            node_prev = node_current;
            node_current = node_current->next;
        }
        node_to_add->nodeSetNext(node_current);
        if(node_prev == nullptr){
            head = node_to_add;
            return;
        }
        node_prev->nodeSetNext(node_to_add);  
    }

/**
* pqRemoveNode: remove the node from the list, if data is NULL should do nothing.
* @param data - Target data.
*/
    template<class T>
    void PriorityQueue<T>::pqRemoveNode(T data){
            if(!pqContains(data)){
                throw NotRegistered();
            }
            iter = nullptr;
            if(numOfNode == 1){
                head = nullptr;
                tail = nullptr;
                numOfNode--;
                return;
            }
            numOfNode--;
            Node<T>* node_prev = nullptr;
            Node<T>* node_current = head; 
            Node<T>* node_next = head->next;
            while(*node_current->data != *data){
                node_prev = node_current;
                node_current = node_next;
                node_next = node_next->next;
            }
            if(node_current == head){
                head = node_next;
                delete node_current;
                return;
            }
            node_prev->nodeSetNext(node_next); 
            if(node_current == tail){
                tail = node_prev;
            }   
            node_current->nodeSetNext(nullptr);
            delete node_current;
        }

/**
* pqGetSize: get the size of the list.
* @return :
* 	a integer number.
*/
    template<class T>
    int PriorityQueue<T>::pqGetSize(){
        return numOfNode;
    }

/**
* pqGetFirstNode: get the first node in list.
* @return :
* 	a node type.
*/    
    template<class T>
    Node<T>* PriorityQueue<T>::pqGetFirstNode(){
        if(head == nullptr){
            return nullptr;
        }
        iter = head;
        return iter;
    }

/**
* pqGetFirst: get the first data (in first node) in list.
* @return :
* 	a data type.
*/  
    template<class T>
    T PriorityQueue<T>::pqGetFirst(){
        if(head == nullptr){
            return nullptr;
        }
        iter = head;
        return iter->data;
    }

/**
* pqGetLast: get the past-the-end element in list.
* @return :
* 	NULL.
*/  
    template<class T>
    T PriorityQueue<T>::pqGetLast(){
        return NULL;
    }

/**
* pqGetNext: get the next data in list.
* @return :
* 	a data type.
*/  
    template<class T>                                                      
    T PriorityQueue<T>::pqGetNext(){                          
        if(iter == nullptr){                                          
            return nullptr;                                               
        }                                                           
        if(iter->next == nullptr){                                    
            return nullptr;                                         
        }                                                              
        iter = iter->next;                                             
        return iter->data;                                       
    }                                                                     

    template<class T>
    PriorityQueue<T>::~PriorityQueue(){
        Node<T>* current = head;
        while(current != nullptr){
            Node<T>* next = current->next;
            current->~Node();
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        iter = nullptr;
    }
}


#endif //PRIORITY_QUEUE_H