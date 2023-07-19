
// Author: Azqa Asad
// File: mytest.cpp


#include "cqueue.h"
#include <random>
int priorityFn1(const Order &order);// works with a MAXHEAP
int priorityFn2(const Order &order);// works with a MINHEAP

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

class Tester{
    public:
    bool insertNormalMinLeftisit(); 
    bool insertNormalMaxLeftisit(); 
    bool insertNormalMinSKew(); 
    bool insertNormalMaxSkew(); 
    bool insertError();
    bool setStructToMinLeftist();
    bool setStructToMaxLeftist();
    bool setStructToMinSkew();
    bool setStructToMaxSkew();
    bool normalCountFunction();
    bool edgeCountFunction();
    bool copyConstructorNormal();
    bool copyConstructorEdge();
    bool assignmentNormal();
    bool assignmentEdge();
    bool mergeNormal();
    bool mergeEdge();
    bool selfMerge();
    bool mergeMinMax();
    bool mergeSkewLeftisit(); 
    bool Dequeue();
    bool normalMinGetNextOrder();
    bool normalMaxGetNextOrder();
    bool edgeGetNextOrder();
    bool isHeap(const Node *aNode, CQueue *myCQ); 
    bool isHeap(CQueue &myCQ); 
    bool isValidNPL(Node *aNode);

};


int main(){
    Tester tester;
    cout << "TESTING INSERT FUNCTIONALITY" << endl;
    if(tester.insertNormalMinLeftisit())
        cout << "insertNormalMinLeftist() passed" << endl;
    else 
        cout << "insertNormalMinLeftist() failed" << endl;
    
    if(tester.insertNormalMaxLeftisit())
        cout << "insertNormalMaxLeftist() passed" << endl;
    else 
        cout << "insertNormalMaxLeftist() failed" << endl;
    
    if(tester.insertNormalMinSKew())
        cout << "insertNormalMinSKew() passed" << endl;
    else 
        cout << "insertNormalMinSKew() failed" << endl;
    
    if(tester.insertNormalMaxSkew())
        cout << "insertNormalMaxSKew() passed" << endl;
    else 
        cout << "insertNormalMaxSKew() failed" << endl;
    
    if(tester.insertError())
        cout << "insertInvalid() passed" << endl;
    else 
        cout << "insertInvalid() failed" << endl;
    cout << endl;
    
    cout << "TESTING NORMAL COUNT FUNCTIONALITY" << endl;
    if(tester.normalCountFunction())
        cout << "normalCountFunction() passed" << endl;
    else 
        cout << "normalCountFunction() failed" << endl;

    if(tester.edgeCountFunction())
        cout << "edgeCountFunction() passed" << endl;
    else 
        cout << "edgeCountFunction() failed" << endl;
      cout << endl;

    cout << "TESTING ASSIGNMENT OPERATOR FUNCTIONALITY" << endl;
    if(tester.assignmentNormal())
        cout << "assignmentNormal() passed" << endl;
    else 
        cout << "assignmentNormal() failed" << endl; 
    
    if(tester.assignmentEdge())
        cout << "assignmentEdge() passed" << endl;
    else 
        cout << "assignmentEdge() failed" << endl;
    cout << endl;

    cout << "TESTING COPY CONSTRUCTOR FUNCTIONALITY" << endl;
    if(tester.copyConstructorNormal())
        cout << "copyConstructorNormal() passed" << endl;
    else
        cout << "copyConstructorNormal() failed" << endl;  
    
    if(tester.copyConstructorEdge())
        cout << "copyConstructorEdge() passed" << endl;
    else 
        cout << "copyConstructorEdge() failed" << endl;
    cout << endl;

    cout << "TESTING MERGE FUNCTIONALITY" << endl;
    if(tester.mergeNormal())
        cout << "mergeNormal() passed" << endl;
    else 
        cout << "mergeNormal() failed" << endl; 
    
    if(tester.mergeEdge())
        cout << "mergeEdge() passed" << endl;
    else 
        cout << "mergeEdge() failed" << endl;
    
    if(tester.selfMerge())
        cout << "selfMerge() passed" << endl;
    else 
        cout << "selfMerge() failed" << endl;
    
    if(tester.mergeMinMax())
        cout << "mergeMinMax() passed" << endl;
    else 
        cout << "mergeMinMax() failed" << endl;
        
    
    if(tester.mergeSkewLeftisit())
        cout << "mergeSkewLeftisit() passed" << endl;
    else
        cout << "mergeSkewLeftisit() failed" << endl;
cout << endl;

    cout << "TESTING GET NEXT ORDER FUNCTIONALITY" << endl;
    if(tester.normalMinGetNextOrder())
        cout << "normalMinGetNextOrder() passed" << endl;
    else 
        cout << "normalMinGetNextOrder() failed" << endl;
    
    if(tester.normalMaxGetNextOrder())
        cout << "normalMaxGetNextOrder() passed" << endl;
    else 
        cout << "normalMaxGetNextOrder() failed" << endl;
    
    if(tester.edgeGetNextOrder())
        cout << "edgeGetNextOrder() passed" << endl;
    else 
        cout << "edgeGetNextOrder() failed" << endl;
    
     if(tester.Dequeue())
        cout << "Dequeue() passed" << endl;
    else
        cout << "Dequeue() passed" << endl;
     cout << endl;

    cout << "TESTING SETTING PRIORFUNC/HEAPTYPE FUNCTIONALITY" << endl;
    if(tester.setStructToMaxLeftist())
        cout << "setStructToMaxLeftist() passed" << endl;
    else   
        cout << "setStructToMaxLeftist() failed" << endl;
    
    if(tester.setStructToMinLeftist())
        cout << "setStructToMin() passed" << endl;
    else 
        cout << "setStructToMin() failed" << endl;

    if(tester.setStructToMaxSkew())
        cout << "setStructToMaxRightSkew() passed" << endl;
    else 
        cout << "setStructToMaxRigthSkew() failed" << endl;
    
    if(tester.setStructToMinSkew())
        cout << "setStructToMaxRight() passed" << endl;
    else 
        cout << "setStructToMaxRight() failed" << endl;
    

    return 0;
}

//checks if at every node the npl property is maintained
bool Tester::isValidNPL(Node *aNode) {
    bool result = true; 
    int leftNPL = -1;
    int rightNPL = -1;
    if(aNode == nullptr) result = true;
    if(aNode != nullptr) {
        if(aNode->m_left != nullptr) {
            leftNPL = aNode->m_left->getNPL(); 
        }
        if(aNode->m_right != nullptr) {
            rightNPL = aNode->m_right->getNPL();
        }
        if(leftNPL >= rightNPL) {
            result = true;
        } else {
            result = false;
        }
        
        result = result && isValidNPL(aNode->m_left) && isValidNPL(aNode->m_right);
    }
    return result;

}

//checks if the heap property is maintained 
bool Tester::isHeap(CQueue& myCQ)  {
    return isHeap(myCQ.m_heap, &myCQ);

}
//helper function for testing if the heap property is maintained
bool Tester::isHeap(const Node *aNode, CQueue *myCQ){

    if(aNode == nullptr) return true;

    if(myCQ->getHeapType() == MAXHEAP) {

        //left exists
        if(aNode->m_left != nullptr) {
            //node is less than left 
            if(myCQ->m_priorFunc(aNode->getOrder()) < myCQ->m_priorFunc(aNode->m_left->getOrder())) {
                return false;
            }
        
        }
        //right exists
        if(aNode->m_right != nullptr) {
            //node is less than right
            if(myCQ->m_priorFunc(aNode->getOrder()) < myCQ->m_priorFunc(aNode->m_right->getOrder())) {
                return false;
            }
           
        }
    }
    if (myCQ->getHeapType() == MINHEAP) {
        //left exists
        if(aNode->m_left != nullptr) {
            //node is greater than left 
            if(myCQ->m_priorFunc(aNode->getOrder()) > myCQ->m_priorFunc(aNode->m_left->getOrder())) {
                return false;
            }
        }
        //right exists
        if(aNode->m_right != nullptr) {
            //node is greater than right
            if(myCQ->m_priorFunc(aNode->getOrder()) > myCQ->m_priorFunc(aNode->m_right->getOrder())) {
                return false;
            }
           
        } 
}
    return isHeap(aNode->m_left, myCQ)  && isHeap(aNode->m_right, myCQ);
   
}

//inserts valid ids to a min leftist
bool Tester::insertNormalMinLeftisit() {
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    int numOrders = aQueue.numOrders(); 
    if(numOrders == 300 && isHeap(aQueue) && isValidNPL(aQueue.m_heap)) 
        return true;
    return false;

}

//inserts valid ids to a max leftist
bool Tester::insertNormalMaxLeftisit() {
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    aQueue.setPriorityFn(priorityFn1, MAXHEAP);
    int numOrders = aQueue.numOrders(); 
    if(numOrders == 300 && isHeap(aQueue) && isValidNPL(aQueue.m_heap)) 
        return true;
    return false;

}

//inserts valid ids to a min skew
bool Tester::insertNormalMinSKew() {
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    int numOrders = aQueue.numOrders(); 
    if(numOrders == 300 && isHeap(aQueue)) 
        return true;
    return false;

}

//inserts valid ids to a max skew
bool Tester::insertNormalMaxSkew() {
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, SKEW);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    int numOrders = aQueue.numOrders(); 
    if(numOrders == 300 && isHeap(aQueue)) 
        return true;
    return false;

}

//adds and invalid order and customer id
bool Tester::insertError(){
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, SKEW);
   
    Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MAXCUSTID + 5,
                    MAXORDERID + 5);
        aQueue.insertOrder(anOrder);

       
    //nothing should be added
    int countOrders = aQueue.numOrders();
    if(countOrders == 0 && isHeap(aQueue))
        return true;
    return false; 
    
}

//tests the functionality with min heap
bool Tester::normalMinGetNextOrder(){
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //two orders are removed from the queue
    aQueue.getNextOrder(); 
    aQueue.getNextOrder();

    int count = aQueue.numOrders();
    //size should be decremented
    if(count == 48 && isHeap(aQueue)) 
        return true;
    return false;
}

//tests the functionality with max heap
bool Tester::normalMaxGetNextOrder(){
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, SKEW);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //removes two things from the queue
    aQueue.getNextOrder(); 
    aQueue.getNextOrder();

    int count = aQueue.numOrders();
    //size should be decreased
    if(count == 298 && isHeap(aQueue)) 
        return true;
    return false;
}

//adds and removes one item from the queue
bool Tester::edgeGetNextOrder(){
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);

        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    //removes the item from the queue
    aQueue.getNextOrder(); 
    //nothing should remain
    int count = aQueue.numOrders();
    //orders should be 0, propety should be maintained, and heap should be null
    if(count == 0 && isHeap(aQueue) && isValidNPL(aQueue.m_heap) && aQueue.m_heap == nullptr) 
        return true;
    return false;

}

//the queue is set to maxLeftist from minLeftist
bool Tester::setStructToMaxLeftist(){
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //priority is changed
    aQueue.setPriorityFn(priorityFn1, MAXHEAP);
    //orders should still be the same
    int numOrders = aQueue.numOrders();
    //heap property should be maintained
    if(numOrders == 50 && isHeap(aQueue) && isValidNPL(aQueue.m_heap) && aQueue.m_heapType == MAXHEAP) 
        return true;
    return false;


}

//the queue is set to minLeftist from maxLeftist
bool Tester::setStructToMinLeftist(){
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //priority is changed
    aQueue.setPriorityFn(priorityFn2, MINHEAP);
    //orders should be the same
    int numOrders = aQueue.numOrders();
    //heap property should be maintained
    if(numOrders == 50 && isHeap(aQueue) && isValidNPL(aQueue.m_heap) && aQueue.m_heapType == MINHEAP) 
        return true;
    return false;


}
//adds 50 orders to the queue
bool Tester::normalCountFunction(){
     Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //orders should be 50
    int numOrders = aQueue.numOrders(); 
    

    if(numOrders == 50 && isHeap(aQueue)) 
        return true;
    return false;

}

//empties out the queue and the count should be 0
bool Tester::edgeCountFunction(){
     Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    //clears the queue
    aQueue.clear();
    //orders should be 0 
    int numOrders = aQueue.numOrders(); 
    if(aQueue.m_heap == nullptr && numOrders == 0 && isHeap(aQueue)) 
        return true;
    return false;

}


bool Tester::assignmentNormal(){
    bool result = true;
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MINCUSTID + i,
                    MINORDERID + i);
        aQueue.insertOrder(anOrder);
    }
    //deep copy is made
    CQueue concorde(priorityFn2, MINHEAP, LEFTIST) ;
    concorde = aQueue;
    //all the variables are checked
    if(concorde.m_heap == aQueue.m_heap || concorde.m_heapType != aQueue.m_heapType || concorde.m_structure != aQueue.m_structure)
        result = false; 
    return result;
    



}

//two empty queues set equal to each other
bool Tester::assignmentEdge(){
    bool result = true;
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    CQueue concorde(priorityFn2, MINHEAP, LEFTIST);
    //sets both empty queues to each other
    concorde = aQueue;
    if(concorde.m_heap != aQueue.m_heap || concorde.m_heapType != aQueue.m_heapType || concorde.m_structure != aQueue.m_structure)
        result = false; 
    return result;
}

bool Tester::copyConstructorNormal(){
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MINCUSTID + i,
                    MINORDERID + i);
        aQueue.insertOrder(anOrder);
    }
    //copies over a queue with 50 order
    CQueue myQ(aQueue);
    int count = myQ.numOrders();
    //heap types and structures are compared
    if(count == 50 && isHeap(myQ) && myQ.m_heapType == aQueue.m_heapType && myQ.m_structure == aQueue.m_structure)
        return true;
    return false;

}

bool Tester::copyConstructorEdge(){
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    //copies an empty queue
    CQueue concorde(aQueue);
    int orders = concorde.numOrders();
    //everything should match and there should be no order in the queue
    if(orders == 0 && concorde.m_heapType == aQueue.m_heapType && concorde.m_structure == aQueue.m_structure)
        return true;
    return false;


}

bool Tester::mergeNormal(){
    int count = 50;
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<count;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MINCUSTID + i,
                    MINORDERID + i);
        aQueue.insertOrder(anOrder);
    }

    
    CQueue bQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<count;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MINCUSTID + 55 + i,
                    MINORDERID + 55 + i);
        bQueue.insertOrder(anOrder);
    }
    //both queues have 50 orders
     aQueue.mergeWithQueue(bQueue);
     //counter should be chnaged because two queues were merged
     int counter = aQueue.numOrders(); 
    
    //heap property of both queues is checked
    if(counter == 100 && isHeap(aQueue) && isHeap(bQueue) && isValidNPL(aQueue.m_heap))
        return true;
    return false;

}

//merges an empty queue
bool Tester::mergeEdge(){
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MINCUSTID + i,
                    MINORDERID + i);
        aQueue.insertOrder(anOrder);
    }
    //empty queue
    CQueue bQueue(priorityFn2, MINHEAP, LEFTIST);
    aQueue.mergeWithQueue(bQueue);
    //orders should remain the same
    int countOrders = aQueue.numOrders();
    if(countOrders== 300 && isHeap(aQueue) && isHeap(bQueue) && isValidNPL(aQueue.m_heap) && isValidNPL(bQueue.m_heap))
        return true;
    return false;


}

//tries to merge an exsiting queue with itself and nothing should be changed
bool Tester::selfMerge(){
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MINCUSTID + i,
                    MINORDERID + i);
        aQueue.insertOrder(anOrder);
    }


    aQueue.mergeWithQueue(aQueue);
    //the size should remain the same
    int countOrders = aQueue.numOrders();
    //tests if the heap is vaid and npl property is maintained
    if(countOrders == 300 && isHeap(aQueue) && isValidNPL(aQueue.m_heap) )
        return true;
    return false;
}

//function tries to merge different priorities and heap types 
bool Tester::mergeMinMax(){
   
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MINCUSTID + i,
                    MINORDERID + i);
        aQueue.insertOrder(anOrder);
    }

   
    CQueue bQueue(priorityFn1, MAXHEAP, LEFTIST);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MINCUSTID + 55 + i,
                    MINORDERID + 55 + i);
        bQueue.insertOrder(anOrder);
    }
    try{
        //should not be merged
     aQueue.mergeWithQueue(bQueue);
    //domain error is caught
    } catch (const std::domain_error& error) {
        cerr << "Domain error caught for merging different heap types and priority functions" << endl;
        return true;

   }
   return false;


}

//functions tries merging skew and leftist
bool Tester::mergeSkewLeftisit(){
     Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MINCUSTID + i,
                    MINORDERID + i);
        aQueue.insertOrder(anOrder);
    }

    
    CQueue bQueue(priorityFn2, MINHEAP, SKEW);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    MINCUSTID + 55 + i,
                    MINORDERID + 55 + i);
        bQueue.insertOrder(anOrder);
    }
   
    try{
        //cannot be merged 
     aQueue.mergeWithQueue(bQueue);
     //domain error should be caught here
    } catch (const std::domain_error& error) {
        cerr << "Domain error caught for merging different structures" << endl;
        return true;

   }
   return false;
     

}

//function tests dequeue on an empty queue
bool Tester::Dequeue(){
    
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    try{
    aQueue.getNextOrder();
    //catches the out of range error
    } catch(const std::out_of_range& error) {
        return true;
    }
    return false;

}

bool Tester::setStructToMinSkew(){
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, SKEW);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    aQueue.setPriorityFn(priorityFn2, MINHEAP);
    int numOrders = aQueue.numOrders();
    if(numOrders == 50 && isHeap(aQueue) && aQueue.m_heapType == MINHEAP) 
        return true;
    return false;

}
bool Tester::setStructToMaxSkew(){
      Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, SKEW);
    for (int i=0;i<50;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                    static_cast<COUNT>(countGen.getRandNum()),
                    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                    pointsGen.getRandNum(),
                    customerIdGen.getRandNum(),
                    orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    aQueue.setPriorityFn(priorityFn1, MAXHEAP);
    int numOrders = aQueue.numOrders();
    if(numOrders == 50 && isHeap(aQueue) && aQueue.m_heapType == MAXHEAP) 
        return true;
    return false;

}




int priorityFn1(const Order &order) {
    //this function works with a MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-5003]
    //the highest priority would be 3+5000 = 5003
    //the lowest priority would be 0+0 = 0
    //the larger value means the higher priority
    int priority = static_cast<int>(order.getCount()) + order.getPoints();
    return priority;
}

int priorityFn2(const Order &order) {
    //this funcction works with a MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-10]
    //the highest priority would be 0+0 = 0
    //the lowest priority would be 5+5 =10
    //the smaller value means the higher priority
    int priority = static_cast<int>(order.getItem()) + static_cast<int>(order.getMemebership());
    return priority;
}
