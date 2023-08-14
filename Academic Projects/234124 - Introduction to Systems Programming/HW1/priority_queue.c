#include "priority_queue.h"
#include <stdlib.h>
#include <stdio.h>

//-------------------------------------------------------------------------------------------

//--------------------------------------help func--------------------------------------------

//-------------------------------------------------------------------------------------------

typedef struct node{
    PQElement element;
    PQElementPriority priority;
    struct node* next;
}*Node;

struct PriorityQueue_t{
    Node head;
    Node iterator;
    int numOfNodes;
    CopyPQElement copyElement; 
    FreePQElement freeElement;
    EqualPQElements equalElement;
    CopyPQElementPriority copyPriority;
    FreePQElementPriority freePriority;
    ComparePQElementPriorities comparePriorities;    
};

//Releases the information within the node.
static void pqFreeNode(PriorityQueue queue, Node node){
    if(!queue || !node){
        return;
    }
    queue->freeElement(node->element);
    node->element = NULL;
    queue->freePriority(node->priority);
    node->priority = NULL;
    node->next = NULL;
    free(node);
}

//Create a new node.
static Node pqNodeCreate(PriorityQueue queue, PQElement element, PQElementPriority priority){ 
    if(!element || !priority){
        return NULL;
    }
    Node node = malloc(sizeof(*node));
    if(!node){
        return NULL;
    }
    PQElement new_element = queue->copyElement(element);
    if(!new_element){
        free(node);
        return NULL;
    }
    PQElementPriority new_priority = queue->copyPriority(priority);
    if(!new_priority){
        queue->freeElement(new_element);
        free(node);
        return NULL;
    }
    node->element = new_element;
    node->priority = new_priority;
    node->next = NULL;
    return node;    
}

//-------------------------------------------------------------------------------------------

//--------------------------------------PQ func--------------------------------------------

//-------------------------------------------------------------------------------------------

PriorityQueue pqCreate(CopyPQElement copy_element,
                       FreePQElement free_element,
                       EqualPQElements equal_element,
                       CopyPQElementPriority copy_priority,
                       FreePQElementPriority free_priority,
                       ComparePQElementPriorities compare_priorities){
    if(!copy_element || !free_element || !equal_element || !copy_priority || !free_priority || !compare_priorities){
        return NULL;
    }
    PriorityQueue priority_queue = malloc(sizeof(*priority_queue));
    if(!priority_queue){
        return NULL;
    }
    priority_queue->iterator = NULL;
    priority_queue->head = NULL;
    priority_queue->numOfNodes = 0;
    priority_queue->copyElement = copy_element;
    priority_queue->freeElement = free_element;
    priority_queue->equalElement = equal_element;
    priority_queue->copyPriority = copy_priority;
    priority_queue->freePriority = free_priority;
    priority_queue->comparePriorities = compare_priorities;
    return priority_queue;
}

void pqDestroy(PriorityQueue queue){
    if(!queue){
        return;
    }
    if(pqClear(queue) == PQ_SUCCESS){
        free(queue);
    }
}

PriorityQueue pqCopy(PriorityQueue queue){
    if(!queue){
        return NULL;
    }
    PriorityQueue queue_copy = pqCreate(queue->copyElement,queue->freeElement,queue->equalElement,
                        queue->copyPriority,queue->freePriority,queue->comparePriorities);
    if(!queue_copy){
        return NULL;
    }
    Node temp_node = queue->head;
    queue->iterator = NULL;
    while(temp_node){
        if(pqInsert(queue_copy,temp_node->element,temp_node->priority) != PQ_SUCCESS){
            pqDestroy(queue_copy);
            return NULL;
        }
        temp_node = temp_node->next;
    }
    return queue_copy;                       
}

int pqGetSize(PriorityQueue queue){
    if(!queue){
        return -1;
    }
    return queue->numOfNodes;
}

bool pqContains(PriorityQueue queue, PQElement element){
    if(!queue || !element){
        return false;
    }
    Node temp_node = queue->head;
    while (temp_node){
        if(queue->equalElement(temp_node->element, element)){ 
            return true;
        }
        temp_node = temp_node->next;  
    }
    return false;
}

PriorityQueueResult pqInsert(PriorityQueue queue, PQElement element, PQElementPriority priority){
    if(!queue || !element || !priority){
        return PQ_NULL_ARGUMENT;
    }
    Node node_to_add = pqNodeCreate(queue,element,priority);
    if(!node_to_add){
        return PQ_OUT_OF_MEMORY;
    }
    queue->numOfNodes++;
    if(!queue->head){
        queue->head= node_to_add;
        queue->iterator = NULL;
        return PQ_SUCCESS;
    }
    else{
        queue->iterator = queue->head;
        Node current = queue->iterator;
        Node previous = NULL;
        while(current){          
            if(queue->comparePriorities(current->priority, priority) < 0){
                if(!previous){
                    node_to_add->next = current;
                    queue->head = node_to_add;
                    break;
                }else{
                    node_to_add->next = previous->next;  
                    previous->next = node_to_add;
                    break;
                }
            }
            if(!current->next){
                current->next = node_to_add;
                break;
            }
            previous = current;
            current = current->next;
        }
    }
    queue->iterator = NULL;
    return PQ_SUCCESS;
}

PriorityQueueResult pqChangePriority(PriorityQueue queue, PQElement element,
                                     PQElementPriority old_priority, PQElementPriority new_priority){
    if(!queue || !element || !old_priority || !new_priority){
        return PQ_NULL_ARGUMENT;
    }
    if( queue->comparePriorities(old_priority, new_priority) == 0){
        return PQ_SUCCESS;
    }
    if(!queue->head){
        return PQ_ELEMENT_DOES_NOT_EXISTS;
    }
    Node node_to_change = queue->head;
    Node previous = NULL;
    while(node_to_change){
        if(queue->comparePriorities(old_priority, node_to_change->priority) == 0){
            if(queue->equalElement(element,node_to_change->element)){
                if(node_to_change == queue->head){
                    queue->head=node_to_change->next;
                }
                if(previous){
                    previous->next = node_to_change->next;
                }
                node_to_change->next = NULL;
                if(pqInsert(queue, node_to_change->element, new_priority) != PQ_SUCCESS){
                    queue->iterator=NULL;
                    return PQ_OUT_OF_MEMORY;
                }
                queue->iterator=NULL;
                pqFreeNode(queue, node_to_change);
                queue->numOfNodes--;
                return PQ_SUCCESS;
            }
        }
        previous = node_to_change;
        node_to_change = node_to_change->next;
    }
    return PQ_ELEMENT_DOES_NOT_EXISTS;
}

PriorityQueueResult pqRemove(PriorityQueue queue){
    if(!queue){
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator = NULL;
    if(!queue->head){
        return PQ_SUCCESS;
    }
    Node to_delete = queue->head;
    return pqRemoveElement(queue, to_delete->element);
}

PriorityQueueResult pqRemoveElement(PriorityQueue queue, PQElement element){

    if(!queue || !element){
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator=NULL;
    if(!queue->head){
        return PQ_ELEMENT_DOES_NOT_EXISTS;
    }
    Node to_delete = queue->head;
    Node previous = NULL;
    while(to_delete){
        if(queue->equalElement(element, to_delete->element)){   
            if(to_delete == queue->head){
                queue->head= to_delete->next;
            }
            if(previous){
                previous->next = to_delete->next;
            }
            to_delete->next = NULL;
            pqFreeNode(queue, to_delete);
            queue->numOfNodes--;
            return PQ_SUCCESS;
        }
        previous = to_delete;
        to_delete = to_delete->next;
    }
    return PQ_ELEMENT_DOES_NOT_EXISTS;
}

PriorityQueueResult pqClear(PriorityQueue queue){
    if(!queue){
        return PQ_NULL_ARGUMENT;
    }
    if(!queue->head){
        return PQ_SUCCESS;
    }
    Node temp_node = queue->head;
    while(temp_node){
        Node to_delete = temp_node;
        temp_node = temp_node->next;
        pqFreeNode(queue,to_delete);
    }
    queue->head = NULL;
    queue->iterator = NULL;
    queue->numOfNodes = 0;
    return PQ_SUCCESS;
}

PQElement pqGetFirst(PriorityQueue queue){
    if(!queue || !queue->head){
        return NULL;
    }
    Node temp_node = queue->head;
    queue->iterator = temp_node;
    return temp_node->element;
}

PQElement pqGetNext(PriorityQueue queue){
    if(!queue || !queue->iterator){
        return NULL;
    }
    Node temp_node = queue->iterator;
    if(!temp_node->next){
        return NULL;
    }
    Node temp_next = temp_node->next;
    queue->iterator = temp_next;
    return temp_next->element;
}

//-------------------------------------------------------------------------------------------

//------------------------------------------end----------------------------------------------

//-------------------------------------------------------------------------------------------