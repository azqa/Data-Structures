// Name: Azqa Asad
// File : mytest.cpp
// File for testting show.h

#include "show.h"
#include <random>
using namespace std;


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
        bool checkBSTProperty(Show& aTree);
        bool checkBSTProperty(Drone* aNode);
        bool insertNormal();
        bool insertEdge(); 
        bool insertError();
        bool isBalancedInsert();
        bool isBSTInsert();
        bool findNormal();
        bool findError();
        bool sampleTimeInsert();
        bool sampleTimeRemove();
        bool removeNormal();
        bool removeEdge();
        bool isBalancedRemove();
        bool isBSTRemove();
        bool removeError();
        bool removeLightsOff();
        bool countDronesTest();
        bool clearTest();
        bool setStateTest();
        bool normalAssignmentTest();
        bool errorAssignmentTest();


};

  int main(){
        Tester tester;
        Show show; 
       if(tester.insertNormal()) 
            cout << "Insertnormal() passed" << endl;
        else 
            cout << "Insertnormal() failed" << endl;

        if(tester.insertEdge()) 
            cout << "Insertedge() passed" << endl;
        else    
            cout << "Insertedge() failed" << endl;
        
       if(tester.insertError())
            cout << "Inserterror() passed" << endl;
        else 
            cout << "Inserterror() failed" << endl;

        if(tester.isBalancedInsert())
            cout << "IsBalancedInsert() passed, insert function is balanced" << endl;
        else 
            cout << "IsBalancedInsert() failed, insert function is not balanced" << endl;
        
        if(tester.isBSTInsert())
            cout << "IsBSTInsert() passed, insert function has BST properties" << endl;
        else 
            cout << "IsBSTInsert() failed, insert function does not have BST properties" << endl;

        if(tester.removeNormal())
            cout << "Removenormal() passed" << endl;
        else 
            cout << "Removenormal() failed" << endl;

        if(tester.removeError())
            cout << "Removeerror() passed" << endl;
        else 
            cout << "Removeerror() failed" << endl;

        if(tester.removeEdge())
            cout << "RemoveEdge() passed" << endl;
        else 
            cout << "RemoveEdge() failed" << endl;
        
        if(tester.isBalancedRemove())
            cout << "IsBalancedRemove() passed, remove function is Balanced" << endl;
        else 
            cout << "IsBalancedRemove() failed, remove function is not balanced" << endl;

        if(tester.isBSTRemove())
            cout << "IsBSTRemove passed, remove function has BST properties" << endl;
        else 
            cout << "IsBSTRemove failed, remove function does not have BST properties" << endl;

        if(tester.findNormal())
            cout << "findNormal() test passed" << endl;
        else 
            cout << "findNormal() test failed" << endl;

        if(tester.findError())
            cout << "findError() test passed" << endl;
        else 
            cout << "findError() test failed" << endl;

        if(tester.countDronesTest()) 
            cout << "countDrones() test passed" << endl;
        else 
            cout << "countDrones() test failed" << endl;

        if(tester.removeLightsOff())
            cout << "removeLights() off test passed" << endl;
        else 
            cout << "removeLights() off test failed" << endl;
        
        if(tester.clearTest())
            cout << "clearTest() passed" << endl;
        else 
            cout << "clearTest() failed" << endl; 
        
        if(tester.normalAssignmentTest()) 
            cout << "normalAssignment() test passed" << endl;
        else 
            cout << "normalAssignment() test failed" << endl;

        if(tester.errorAssignmentTest())
            cout << "errorAssignment() test passed" << endl;
        else 
            cout << "errorAssignment() test failed" << endl;

        if(tester.setStateTest())
            cout << "setState() test passed" << endl;
        else 
            cout << "setState() test failed" << endl;
        
        if(tester.sampleTimeInsert())
            cout << "Run time test for insert passed" << endl;
        else 
            cout << "Run time test for insert failed" << endl;

        if(tester.sampleTimeRemove())
            cout << "Run time test for remove passed" << endl; 
        else 
            cout << "Run time test for remove failed" << endl;      
        

        
        return 0;
    }

//function tests the assignment operator for a normal case
//should pass
bool Tester::normalAssignmentTest(){
    Show show;
    bool result = true;
    
    
    Drone drone(MINID + 1,GREEN);
    show.insert(drone);
    Drone drone3(MINID,GREEN);
    show.insert(drone3);
    Drone drone2(MINID + 2,GREEN);
    show.insert(drone2);
    //creates a copy
    Show concorde;
    concorde = show; 
    if(show.m_root->m_id != concorde.m_root->m_id){
        result = false;
    }
    //adress should not match
    if(show.m_root == concorde.m_root){
        result = false;
    }
    return result;

}

//function tests the assignment operator for a error case
//should pass
bool Tester::errorAssignmentTest(){
    //creates an empty copy
    Show show;
    Show concorde;
    concorde = show;
    bool result = true;

    if(concorde.m_root != nullptr)
        result = false;
    return result;
}

//function tests the set state function for a normal test
//should pass
bool Tester::setStateTest(){
    Show show;
    bool result = true;
    Drone drone(MINID, RED, LIGHTOFF);
    show.insert(drone);
    
    //sets the state
    show.setState(MINID, LIGHTON);
    //checks the state
    if(show.m_root->m_state == LIGHTON) 
        result = true;
    else 
        result = false;
    
    return result;

}

//function tests the clear normal case
//should pass
bool Tester::clearTest() {
    Show show;
    //inserts the drones
     for(int i=0;i<20;i++){
        Drone drone(MINID+i,RED, LIGHTOFF);
        show.insert(drone);
     }
    //drones are cleared
    show.clear();
   
   //the root should be null and the children nodes
    if(show.m_root != nullptr){ 
        if(show.m_root->m_left != nullptr || show.m_root->m_right != nullptr)
            return false;
    return false;
    }
    return true;

}

//function test the removeLightOff function for a normal case
bool Tester::removeLightsOff(){

    Show show;
     for(int i=0;i<20;i++){
        Drone drone(MINID+i,RED, LIGHTOFF);
        show.insert(drone);
     }
    //should remove all 20 drones
    show.removeLightOff();

    //no nodes should exist
    if(show.m_root != nullptr){ 
        if(show.m_root->m_left != nullptr || show.m_root->m_right != nullptr)
            return false;
    return false;
    }
    return true;
}

//function test the count drones functionality
//should pass
bool Tester::countDronesTest(){
    Show show;
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); // there are three colors
    int teamSize = 300;
    int ID = 0;

    for(int i=0;i<teamSize;i++){
        ID = idGen.getRandNum();
        //adds all the drones with the same color
        Drone drone(ID,BLUE);
        show.insert(drone);
        result = result && show.balanceBool(show.m_root); 
        result = result && checkBSTProperty(show.m_root);
    }
    //inserts are drone that is not green 
    //Drone drone1(30000, GREEN);
    //show.insert(drone1);
    
    //color should be blue and 300
    int count = show.countDrones(BLUE); 

    if(count == 300)
        result = true;
    else 
        result =  false;
    return result;
}

//function tests normal case for find
//should pass
bool Tester::findNormal() {
    Show show;
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); // there are three colors
    int teamSize = 10;
    int tempID = 0;
    int ID = 0;

     for(int i=0;i<teamSize;i++){
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        
        show.insert(drone);
        result = result && show.balanceBool(show.m_root); 
        result = result && checkBSTProperty(show.m_root);
    }      
    
        //finds a random inserted drone
        result = show.findDrone(tempID) && result; 
    return result;

}

//tests an id that doesnt exist
//should pass
bool Tester::findError(){
    Show show;
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); // there are three colors
    int teamSize = 50;
    int tempID = 0;
    int ID = 0;

     for(int i=0;i<teamSize;i++){
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
    }      
        //finds an id that doesnt exist
        result = (show.findDrone(tempID + 100) == false) && result; 
        result = (show.findDrone(-1) == false) && result; 
        //checks for bst and avl
        result = result && show.balanceBool(show.m_root); 
        result = result && checkBSTProperty(show.m_root);
    return result;

}

//should measure the run time for remove function and should be between .7-1.5
//should pass
bool Tester::sampleTimeRemove() {
    //stores running times
     double T = 0.0;
    double T2 = 0.0;
    
    //stores the clock ticks while running the program
    clock_t start, stop;
    clock_t start2, stop2; 
    int arraySize = 1000; 
    int secondArray = 2000;
    Show show;
    Show show2;
   
    // the algorithm to be measured
    for (int j=0;j<arraySize;j++){
        show.insert(Drone(MINID + j));
    }
    start = clock();
    for(int i = 0; i < arraySize; i++) {
        show.remove(MINID + i);
    }
    stop = clock();
    

    
   
   //second for loop with 2000 drones
    for (int j=0;j<secondArray;j++){
        show.insert(Drone(MINID + j));
    }
     start2 = clock();
     for(int i = 0; i < secondArray; i++) {
        show.remove(MINID + i);
     }
    stop2 = clock();
    

    
    //number of clock ticks the algorithm took
    T = stop - start;
    T2 = stop2 - start2; 
    //times in seconds
    double measureTime = T/CLOCKS_PER_SEC;
    double measureTime2 = T2/CLOCKS_PER_SEC;
    
    //stores the result of the run time
    double result = measureTime2 / (2 * measureTime);
    //cout << result << endl;
    if(result >= 0.7 && result <= 1.5)
        return true;
    return false;
}


//should measure the run time for insert function and should be between .7-1.5
//should pass
bool Tester::sampleTimeInsert(){
    //stores running times
    double T = 0.0;
    double T2 = 0.0;
    //stores the clock ticks while running the program
    clock_t start, stop;
    clock_t start2, stop2; 
    int arraySize = 1000; 
    int secondArray = 2000;
    Show show;
    Show show2;
   
   
    start = clock();
    // the algorithm to be measured
    for (int j=0;j<arraySize;j++){
        show.insert(Drone(MINID + j));
    }
    stop = clock();
   

    show.clear();
    start2 = clock();
     for (int j=0;j<secondArray;j++){
        show.insert(Drone(MINID + j));
    }
    stop2 = clock();
   
    
    //number of clock ticks the algorithm took
    T = stop - start;
    T2 = stop2 - start2; 
    //times in seconds
    double measureTime = T/CLOCKS_PER_SEC;
    double measureTime2 = T2/CLOCKS_PER_SEC;
    
    double result = measureTime2 / (2 * measureTime);
    //cout << result << endl;
    if(result >= 0.7 && result <= 1.5)
        return true;
    return false;
}

//Test whether the tree is balanced after a decent number of insertions, e.g. 300 insertions. (Note: this requires visiting all nodes and checking the height values)
//should pass
bool Tester::isBalancedInsert(){
    Show show;
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); 
    int teamSize = 300;
    int ID = 0;

    for(int i=0;i<teamSize;i++){
        ID = idGen.getRandNum();
        Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
        result = result && show.balanceBool(show.m_root); 
    }
    

    return result;

}

//checks if the insert finction has BST properties
//should pass
bool Tester::isBSTInsert(){
    Show show;
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); 
    int teamSize = 50;

    for(int i=0;i<teamSize;i++){
        Drone drone(MINID + i,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
        //calls the BST helper
        result = result && checkBSTProperty(show.m_root);
    }
       
    return result;

}

//checks the insert function for a normal case
//should pass
bool Tester::insertNormal() {
    Show show;
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); 
    int teamSize = 50;

    for(int i=0;i<teamSize;i++){
        Drone drone(MINID + i,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
        result = result && show.balanceBool(show.m_root); 
        result = result && checkBSTProperty(show.m_root);
    }
     
    //find couples of nodes
    if(show.findDrone(MINID + 5 ) && show.findDrone(MINID + 9) && show.findDrone(MINID + 18) && show.findDrone(MINID + 39))
        result = true;
    else 
        result = false;
    return result;


}

//inserts an invalid id
//should pass
bool Tester::insertError(){
    Show show;
    Random typeGen(0,2); 
    
        //invalid id
        Drone drone(-1,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
        //nothing should exist
        if(show.m_root == nullptr) {
            return true; 
        }
    return false;
}

//inserts duplicates
//should pass
bool Tester::insertEdge(){
    Show show;
    bool result = true;
    
    Drone drone(MINID + 1,GREEN);
    show.insert(drone);
    result = result && show.balanceBool(show.m_root); 
    result = result && checkBSTProperty(show.m_root);
    //duplicate id trying to be added
    Drone drone1(MINID + 1, RED);
    show.insert(drone1);
    result = result && show.balanceBool(show.m_root); 
    result = result && checkBSTProperty(show.m_root);
     
        if(show.m_root != nullptr) {
            if(show.m_root->m_left == nullptr && show.m_root->m_right == nullptr) {
                result = true;
            } 
        }
      
    Drone drone2(MINID + 2,GREEN);
    show.insert(drone2);
    result = result && show.balanceBool(show.m_root); 
    result = result && checkBSTProperty(show.m_root);
    Drone drone3(MINID + 3,GREEN);
    show.insert(drone3);
    result = result && show.balanceBool(show.m_root); 
    result = result && checkBSTProperty(show.m_root);
    
    int count = show.countDrones(GREEN);
    int count2 = show.countDrones(RED);
    
  
    //function only finds 3 greens because the fourth one was duplicate
    if(count == 3 && count2 == 0)
        result = true; 
    else 
        result = false; 

    return result;
       
}

//removes nodes and should not find them using the find drones function
//should pass
bool Tester::removeNormal(){
    Show show;
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); // there are three colors
    int teamSize = 300;
    
    //adds 300 nodes
    for(int i=0;i<teamSize;i++){
        show.insert(Drone(i + MINID));
        result = result && show.balanceBool(show.m_root); 
        result = result && checkBSTProperty(show.m_root);
    }
    //removes all 150 nodes
    for(int i=0;i<150; i++) {
        show.remove(MINID + i);
        result = result && show.balanceBool(show.m_root); 
        result = result && checkBSTProperty(show.m_root); 
    }
    
 
    //will not find the id because it has been removed
    result = result && (show.findDrone(MINID) == false);
    result = result && (show.findDrone(MINID+45) == false);
    result = result && (show.findDrone(MINID+65) == false);
    result = result && (show.findDrone(MINID+142) == false);
    return result;

}

//removes the parent node with multiple nodes
//should pass
bool Tester::removeEdge(){
    Show show;
    bool result = true;


    
    //removes the root wth two children
    Drone drone2(MINID + 6, BLUE, LIGHTOFF);
    show.insert(drone2);
    result = result && show.balanceBool(show.m_root); 
    result = result && checkBSTProperty(show.m_root);
    Drone drone3(MINID + 7, BLUE, LIGHTOFF);
    show.insert(drone3);
    Drone drone4(MINID + 8, BLUE, LIGHTOFF);
    show.insert(drone4);
    
    show.remove(MINID + 6); 
    result = result && show.balanceBool(show.m_root); 
    result = result && checkBSTProperty(show.m_root);
   

    if(show.findDrone(MINID + 6) == false && show.m_root != nullptr && (show.m_root->m_left == nullptr || show.m_root->m_right == nullptr)) 
        result = result && true;
    else 
        result = false; 
  
   

    /*if((show.m_root->m_left == nullptr || show.m_root->m_right == nullptr) && show.balanceBool(show.m_root) == true && checkBSTProperty(show.m_root) == true)
        result = true;
    else 
        result = false; */
    return result;
}

//checks if the remove function is balanced
//should pass
bool Tester::isBalancedRemove(){
    Show show;
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); // there are three colors
    int teamSize = 300;
    
    //after inserting
    for(int i=0;i<teamSize;i++){
        show.insert(Drone(i + MINID));
        result = result && show.balanceBool(show.m_root); 
      
    }
    //after removal
    for(int i=0;i<150; i++) {
        show.remove(MINID + i);
        result = result && show.balanceBool(show.m_root); 
    }
    return result;

 }

//checks if the remove function follows BST property
//should pass
bool Tester::isBSTRemove(){
     Show show;
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); 
    int teamSize = 300;
    
    //inserts 300
    for(int i=0;i<teamSize;i++){
        show.insert(Drone(i + MINID));
        result = result && checkBSTProperty(show.m_root);
    }
    //removes first 150
    for(int i=0;i<150; i++) {
        show.remove(MINID + i);
        result = result && checkBSTProperty(show.m_root); 
    }
    return result;

}

bool Tester::removeError(){
    Show show;

    Drone drone1(MINID + 5, BLUE, LIGHTOFF);
    show.insert(drone1);
    Drone drone2(MINID + 6, BLUE, LIGHTOFF);
    show.insert(drone2);
    Drone drone3(MINID + 7, BLUE, LIGHTOFF);
    show.insert(drone3);
    show.remove(MINID + 86); 
    int count = show.countDrones(BLUE); 
    if(count == 3)
        return true;
    return false;

} 

//helper function tests for a BST tree
bool Tester::checkBSTProperty(Show& aTree){
    return checkBSTProperty(aTree.m_root);
}
bool Tester::checkBSTProperty(Drone* aDrone){

    if(aDrone == nullptr)
        return true;
    
    if(aDrone->m_left != nullptr && aDrone->m_left->m_id > aDrone->m_id)  {
        return false; 
    }

    if(aDrone->m_right != nullptr && aDrone->m_right->m_id < aDrone->m_id) {
        return false;
    }
    if(!checkBSTProperty(aDrone->m_left) || !checkBSTProperty(aDrone->m_right)){
        return false;
    }
    return true; 
    
    
}


  
