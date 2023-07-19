// CMSC 341 - Spring 2023 - Project 3
// Author: Azqa Asad
// File: cqueue.cpp
// email: azqaa1@umbc.edu
// Section: 2
// Description: cpp file for cqueue.h

#include "cqueue.h"
//This is the constructor. It must be provided with a pointer to the prioritization function, 
//the type of heap, and the desired data structure.
CQueue::CQueue(prifn_t priFn, HEAPTYPE heapType, STRUCTURE structure){
    //sets all members vars to the default value
    m_priorFunc = priFn;
    m_heapType = heapType;
    m_structure = structure;
    m_heap = nullptr;
    m_size = 0;

}
CQueue::~CQueue(){
    clear();
  
}
void CQueue::clear() {
    clearHelper(m_heap);
    
}

void CQueue::clearHelper(Node* &aNode){
    if(aNode != nullptr) {
        //recursively clear all nodes
        clearHelper(aNode->m_left);
        clearHelper(aNode->m_right);
        delete aNode;
      
    }
    aNode = nullptr;
}

//The copy constructor must make a deep copy of the rhs object.
// It must function correctly if rhs is empty. This function creates an exact same copy of rhs.
CQueue::CQueue(const CQueue& rhs){
  
    if(rhs.m_heap == nullptr) {
        m_heap = nullptr;
        //m_size = 0;
     
    }
    //call to helper function
    m_heap = copyOfContents(rhs.m_heap);
    //sets everthing equal to rhs
    m_size = rhs.m_size;
    m_structure = rhs.m_structure;
    m_priorFunc = rhs.m_priorFunc;
    m_heapType = rhs.m_heapType;
}

//helper function for assignment operator
Node* CQueue::copyContents(Node* aNode, const Node* bNode){
    if(aNode == nullptr) return nullptr;
    // otherwise memory is allocated
    aNode = new Node(aNode->getOrder());
    //recursive calls
    aNode->m_left = copyContents(aNode->m_left, bNode->m_left);
    aNode->m_right = copyContents(aNode->m_right, bNode->m_right);
    return aNode;  
}
////helper function for copy constructor
Node* CQueue::copyOfContents(Node* bNode){
    if(bNode == nullptr) return nullptr;
    // otherwise memory is allocated
    Node* newNode = new Node(bNode->getOrder());
    //recursive calls
    newNode->m_left = copyOfContents(bNode->m_left);
    newNode->m_right = copyOfContents(bNode->m_right);
    return newNode;  
}


//The assignment operator creates an exact same copy of rhs. 
//You should not call the copy constructor in the implementation of the assignment operator.
CQueue& CQueue::operator=(const CQueue& rhs) {
    if(rhs.m_heap == nullptr) m_heap = nullptr;

    if(this != &rhs) {
        clear();
        //m_size = 0;
        //m_heap = nullptr;
       
        //m_structure = rhs.m_structure;
        m_heap = copyContents(m_heap, rhs.m_heap);
        m_size = rhs.m_size;

    }

    return *this;
}
//This function returns the heap type, i.e. it is either MINHEAP or MAXHEAP.
HEAPTYPE CQueue::getHeapType() const{
    return m_heapType;
}

//This function merges the host queue with the rhs; it leaves rhs empty. 
//Two heaps can only be merged if they have the same priority function and they are of the same data structure. 
//If the user attempts to merge queues with different priority functions, or two different data structures a domain_error exception should be thrown. 
//This function requires protection against self-merging. Merging a heap with itself is not allowed.
void CQueue::mergeWithQueue(CQueue& rhs) {

//stops from self merging
if(this != &rhs) {
    //if the required vars aren;t the same then dones't merge
    if(rhs.m_priorFunc != m_priorFunc || rhs.m_heapType != m_heapType || rhs.m_structure != m_structure)  {
        throw std::domain_error("Queues are not allowed to be merged");
    }
    
    //calls skew helper if the structre is skew
    else if(m_structure == SKEW) {
            m_heap = skewHelper(rhs.m_heap, m_heap); 
            m_size = m_size + rhs.m_size; 
            rhs.m_heap = nullptr;
            rhs.m_size = 0;
    }
    //calls leftist helper if the structre is leftist
    else if(m_structure == LEFTIST) {
            m_heap = leftistHelper(rhs.m_heap, m_heap);
            m_size = m_size + rhs.m_size; 
            rhs.m_heap = nullptr;
            rhs.m_size = 0;
    }
}
    
  
}

//helper function for skew merging
Node* CQueue::skewHelper(Node* node1, Node* node2){
    if(node1 == nullptr) return node2; 
    if(node2 == nullptr) return node1; 

    //if p1 > p2 for minheap then the nodes are swapped
    if(m_priorFunc(node1->getOrder()) > m_priorFunc(node2->getOrder()) && m_heapType == MINHEAP) {
        swap(node1, node2); 
    }
        //if p1 < p2 for maxheap then the nodes are swapped
    if(m_priorFunc(node1->getOrder()) < m_priorFunc(node2->getOrder()) && m_heapType == MAXHEAP) {
        swap(node1, node2); 
    }
    //swapping left and right children
    swap(node1->m_left, node1->m_right); 
    //recursive call
    node1->m_left = skewHelper(node1->m_left, node2);
    
    return node1; 


}

//helper function for leftist merge
Node* CQueue::leftistHelper(Node* node1, Node* node2){
    if(node1 == nullptr) return node2; 
    if(node2 == nullptr) return node1;

    if(m_priorFunc(node1->getOrder()) > m_priorFunc(node2->getOrder())  && m_heapType == MINHEAP) {
        swap(node1, node2);
    } 
    if(m_priorFunc(node1->getOrder()) < m_priorFunc(node2->getOrder())  && m_heapType == MAXHEAP) {
        swap(node1, node2);
    } 
    //recursive call on the right child because the node is merged on the right
    node1->m_right = leftistHelper(node1->m_right, node2);
   

    if(node1->m_right != nullptr) {
        //left child exists 
        if(node1->m_left != nullptr) {
            //npl is compared before swapping
            //if the right node has a higher npl then its swapped
            if(node1->m_right->getNPL() >  node1->m_left->getNPL()) {
                swap(node1->m_left, node1->m_right);  
                
        }
        //no left child
    }   else {
            swap(node1->m_left, node1->m_right); 
    }
    } 
    //sets the npl
    node1->setNPL(nullPointerLength(node1)); 
    return  node1; 
}




//npl is for leftist 
int CQueue::nullPointerLength(Node* node){
    if(node == nullptr) return -1;
    
    //only right exists
    else if(node->m_right != nullptr) {
        return 1 + node->m_right->getNPL();
    }
    //right doesnt exist
    return 0;  
}


//Inserts an order into the queue. Must maintain the min-heap or the max-heap property depending on the settings.
// Moreover, if the selected data structure is leftist heap, it needs to maintain a correct value of Null Path Length (NPL) in the node.
void CQueue::insertOrder(const Order& order) {

    //valid customer and order ids    
    if(order.m_orderID >= MINORDERID && order.m_orderID <= MAXORDERID && order.m_customerID >= MINCUSTID && order.m_customerID <= MAXCUSTID) {
        //memory is allocated
    Node* newNode = new Node(order); 
    //leftsit functionality is called
    if(m_structure == LEFTIST) {
        m_heap = leftistHelper(m_heap, newNode);
        m_size++; 
    }
    //skew functionality is called
    if(m_structure == SKEW) {
        m_heap = skewHelper(m_heap, newNode);
        m_size++; 
    }
    }
   
}


//It returns the current number of orders in the queue.
int CQueue::numOrders() const
{
    //passed by reference
    int numOrders = 0;
    return numOrdersHelper(m_heap, numOrders); 
  
}

//in order helper function to count the number of orders
int CQueue::numOrdersHelper(Node* node, int &order)const{
    if(node != nullptr) {
        //recurvie calls
        numOrdersHelper(node->m_left, order);
        order++;
        numOrdersHelper(node->m_right, order);
    }
    return order;
}


//This function returns the current priority function.
prifn_t CQueue::getPriorityFn() const {
    return m_priorFunc;
  
}

//This function extracts (removes the node) and returns the highest priority order from the queue. 
//It must maintain the min-heap or max-heap property. 
//The function throws an out_of_range exception if the queue is empty when the function is called.
Order CQueue::getNextOrder() {
    //checks for exceptions 
    if(m_heap == nullptr) {
          throw std::out_of_range("Queues is empty");
    }
    //copies all elements of the heap in a temp heap
    Order tempHeap = m_heap->getOrder();
    Node *leftChild = m_heap->m_left;
    Node *rightChild = m_heap->m_right;
    //actual heap is deleted
    delete m_heap;
    //merge funtions are called accodingly
    if(m_structure == LEFTIST) {
        m_heap = leftistHelper(leftChild, rightChild);  
    }

    if(m_structure == SKEW) {
        m_heap = skewHelper(leftChild, rightChild);
    }
    //size is decremented because orders are being removed 
    m_size--; 
    return tempHeap; 

}
//This function sets a new priority function and its corresponding heap type (min-heap or max-heap). 
//It must rebuild the heap!
void CQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {

    m_priorFunc = priFn;
    m_heapType = heapType;
    //store the copy of the heap
   CQueue *temp = new CQueue(priFn, heapType, m_structure);

   while(m_size > 0) {
    temp->insertOrder(getNextOrder()); 
   }
    m_size = temp->m_size; 
   m_heap = temp->m_heap;
   temp->m_heap = nullptr; 
   delete temp;  
   
 
}

//This function sets the data structure, i.e. it is either SKEW or LEFTIST. 
//It must rebuild a heap with the new structure using the nodes in the current data structure.
void CQueue::setStructure(STRUCTURE structure){
    m_structure = structure;
     //store the copy of the heap
   CQueue *temp = new CQueue(m_priorFunc, m_heapType, m_structure);

    while(m_size > 0) {
    temp->insertOrder(getNextOrder()); 
   }

   m_size = temp->m_size; 
   m_heap = temp->m_heap;
   temp->m_heap = nullptr; 
   delete temp;  

   
}

//This function returns the data structure of the type STRUCTURE, i.e. it is either SKEW or LEFTIST.
STRUCTURE CQueue::getStructure() const {
  return m_structure;
}

//It prints the contents of the queue using preorder traversal. 
//Although the first order printed should have the highest priority, 
//the remaining orders will not necessarily be in priority order. 
//Please refer to the sample output file (driver.txt) for the format of this function's output.
void CQueue::printOrdersQueue() const {
    printHelper(m_heap);
}
//helper for printOrdersQueue
//uses preorder traversal
void CQueue::printHelper(Node* aNode) const{
    if(aNode != nullptr) {
        //uses the overloaded operator 
        cout << "[" << m_priorFunc(aNode->getOrder()) << "] " << aNode->getOrder() << endl;
        printHelper(aNode->m_left);
        printHelper(aNode->m_right);
    }

}

void CQueue::dump() const {
  if (m_size == 0) {
    cout << "Empty heap.\n" ;
  } else {
    dump(m_heap);
  }
  cout << endl;
}
void CQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    if (m_structure == SKEW)
        cout << m_priorFunc(pos->m_order) << ":" << pos->m_order.getOrderID();
    else
        cout << m_priorFunc(pos->m_order) << ":" << pos->m_order.getOrderID() << ":" << pos->m_npl;
    dump(pos->m_right);
    cout << ")";
  }
}
ostream& operator<<(ostream& sout, const Order& order) {
  sout << "Order ID: " << order.getOrderID() 
        << ", customer ID: " << order.getCustomerID()
        << ", # of points: " << order.getPoints()
        << ", membership tier: " << order.getTierString()
        << ", item ordered: " << order.getItemString()
        << ", quantity: " << order.getCountString();
  return sout;
}
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getOrder();
  return sout;
}
