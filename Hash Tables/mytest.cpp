// CMSC 341 - Spring 2023 - Project 4
// Author: Azqa Asad
// Section : 2
// File: mytest.cpp
// email: azqaa1@umbc.edu

#include "vdetect.h"
#include <random>
#include <vector>
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

unsigned int hashCode(const string str);
string sequencer(int size, int seedNum);

class Tester{
    public:
    bool nonCollidingInsert();
    bool collidingInsert();
    bool quadWithoutRehash();
    bool doubleWithoutRehash();
    bool doublehashTestFullRehash();
    bool quadratictestSingleRehash();
    bool quadratictestFullRehash();
    bool invalidID();
    bool normalRemove();
    bool removeWithNoMethod();
    bool removeWithQuad();
    bool removeWithDoubleHash();
    bool removeWithQuadNoHash();
    bool removeWithDoubleNoHash();
    bool getVirusErrorCase();
    bool getVirusNonColliding();
    bool getVirusCollidingWithoutRehash();

};

//uses double hash probing and a full rehash
bool Tester::doublehashTestFullRehash(){
    vector<Virus> dataList;
    Random RndID(MINID,MAXID);
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);
    bool result = true;
    for (int i=0;i<65;i++){
        // generating random data
        Virus dataObj = Virus("TGCAA", MINID + i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the VDetect object
        vdetect.insert(dataObj);
    }

    for (vector<Virus>::iterator it = dataList.begin(); it != dataList.end(); it++){
        result = result && (*it == vdetect.getVirus((*it).getKey(), (*it).getID()));
    }
   
    if(vdetect.m_currentSize == 65 && result && vdetect.m_oldTable == nullptr)
        return true;
    else
        return false;

}

//uses quadrating probing and a single rehash
bool Tester::quadratictestSingleRehash(){
    vector<Virus> dataList;
    Random RndID(MINID,MAXID);
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);
    bool result = true;
    for (int i=0;i<51;i++){
        // generating random data
        Virus dataObj = Virus("ACGTT", MINID + i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the VDetect object
        vdetect.insert(dataObj);
    }

    for (vector<Virus>::iterator it = dataList.begin(); it != dataList.end(); it++){
        result = result && (*it == vdetect.getVirus((*it).getKey(), (*it).getID()));
    }

    int sz = 51*.25;
    //curr size till the first rehash is 12
    if(vdetect.m_currentSize == sz && result && vdetect.m_oldTable != nullptr)
        return true;
    else
        return false;

}

//uses quadrating probing and a full rehash
bool Tester::quadratictestFullRehash(){
    vector<Virus> dataList;
    Random RndID(MINID,MAXID);
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);
    bool result = true;
    for (int i=0;i<55;i++){
        // generating random data
        Virus dataObj = Virus(sequencer(5, i), MINID + i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the VDetect object
        vdetect.insert(dataObj);
    }

    for (vector<Virus>::iterator it = dataList.begin(); it != dataList.end(); it++){
        result = result && (*it == vdetect.getVirus((*it).getKey(), (*it).getID()));
    }
   //vdetect.dump();
    if(vdetect.m_currentSize == 55 && result && vdetect.m_oldTable == nullptr)
        return true;
    else
        return false;
}




//inserts invalid ids and duplicate virsues
bool Tester::invalidID() {
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);
    bool result = true;


    Virus myVirus("ACGTA", 10);
    Virus myVirus2("ACGTA", -20);
    //inserts invalid ids
    vdetect.insert(myVirus);
    vdetect.insert(myVirus2);
    //inserts duplicate ids
    Virus myVirus3("AGGTT", 1000);
    Virus myVirus4("TCAGA", 1000);
    result = result && vdetect.insert(myVirus3);
    //inserts the duplicate viruses
    result = ((vdetect.insert(myVirus3) == false) && result); 
  
    //size should be one
    if(vdetect.m_currentSize == 1 && vdetect.getVirus("vrs", 10) == EMPTY && vdetect.getVirus("abc", -20) == EMPTY && vdetect.getVirus("xyzab", 1000) == EMPTY && result )
        return true;
    else    
        return false;
   
}

//checks a few non colliding keys for insertion
bool Tester::nonCollidingInsert(){

    VDetect vdetect(MINPRIME, hashCode, NONE);

    Virus myVirus("AGTCA", 1001);
    Virus myVirus2("ACGTA", 2001);
    Virus myVirus3("TTGGA", 3001);


    vdetect.insert(myVirus);
    vdetect.insert(myVirus2);
    vdetect.insert(myVirus3);

    //vdetect.dump();

    //size should be 3 and viruses should be found
    if(vdetect.m_currentSize == 3 && !(vdetect.getVirus("AGTCA", 1001) == EMPTY) && !(vdetect.getVirus("ACGTA", 2001) == EMPTY) && !(vdetect.getVirus("TTGGA", 3001) == EMPTY))
        return true;
    else
        return false;     
     
}

//inserts collding datapoints using doublehash 
bool Tester::collidingInsert(){
    vector<Virus> dataList;
    Random RndID(MINID,MAXID);
    bool result = true;

    int insert = 202;
    int tableSize = insert * 2 - 1;

    VDetect vdetect(tableSize, hashCode, DOUBLEHASH);

    for (int i=0;i<insert;i++){
        // generating random data
        Virus dataObj = Virus("ACCTG", MINID + i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the VDetect object
        vdetect.insert(dataObj);
    }

    for (vector<Virus>::iterator it = dataList.begin(); it != dataList.end(); it++){
        result = result && (*it == vdetect.getVirus((*it).getKey(), (*it).getID()));
    }

    //to check if the rehasing is occuring
    if(vdetect.m_oldTable == nullptr){

        cout << "IN HERE" << endl;
        return false;
    }

    // calculates how many viruses should have been moved
    if(result && vdetect.m_currentSize == vdetect.m_oldNumDeleted + (insert - vdetect.m_oldSize)){

        return true;
    }

    cout << "HERE" << endl;
    return false;

}

//tests quadratic probing without triggering a rehash 
bool Tester::quadWithoutRehash(){
    vector<Virus> dataList;
    Random RndID(MINID,MAXID);
    bool result = true;
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);

      for (int i=0;i<49;i++){
        // generating random data
        Virus dataObj = Virus("ACCTG", MINID + i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the VDetect object
        result = result && vdetect.insert(dataObj);
    }

    //checks if everything is in the correct index
    for(unsigned int i=0;i<dataList.size();i++) {
        for(int j=0;j<MINPRIME;j++) {
            if(vdetect.m_currentTable[vdetect.quadraticHelper(j,dataList[i].getKey())] == EMPTY) {
                return false;
            }
            if(vdetect.m_currentTable[vdetect.quadraticHelper(j,dataList[i].getKey())] == dataList[i] && result) {
                break;
            }


        }
    }
    return true;

}

//tests double probing without rehash
bool Tester::doubleWithoutRehash(){
    vector<Virus> dataList;
    Random RndID(MINID,MAXID);
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

      for (int i=0;i<49;i++){
        // generating random data
        Virus dataObj = Virus("ACCTG", MINID + i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the VDetect object
        vdetect.insert(dataObj);
    }

//checks if everything is in the corrent index
    for(unsigned int i=0;i<dataList.size();i++) {
        for(int j=0;j<MINPRIME;j++) {
            if(vdetect.m_currentTable[vdetect.doubleHashHelper(j,dataList[i].getKey())] == EMPTY) {
                return false;
            }
            if(vdetect.m_currentTable[vdetect.doubleHashHelper(j,dataList[i].getKey())] == dataList[i]) {
                break;
            }


        }
    }
    return true;

}

//a few non colliding keys using insertion
 bool Tester::normalRemove(){
    
    bool result = true;
    Virus myVirus("AGTCA", 1001);
    Virus myVirus2("TGACA", 2001);
    Virus myVirus3("ATCAT", 3001);

    
    VDetect vdetect(MINPRIME, hashCode, NONE);

    vdetect.insert(myVirus);
    vdetect.insert(myVirus2);
    vdetect.insert(myVirus3);

    result = result && vdetect.remove(myVirus2);

    if(vdetect.m_currNumDeleted == 1 && !(vdetect.getVirus("AGTCA", 1001) == EMPTY) && (vdetect.getVirus("TGACA", 2001) == EMPTY) && !(vdetect.getVirus("ATCAT", 3001) == EMPTY) ) 
        return true;
    
    else 
        return false;   
 }

//removes a few colliding keys without nay rehash
bool Tester::removeWithQuadNoHash(){
VDetect vdetect(MINPRIME, hashCode, QUADRATIC);
    Virus myVirus("AGTCA", 1001);
    Virus myVirus2("TGACA", 2001);
    Virus myVirus3("ATCAT", 3001);
    Virus myVirus4("AAATC", 1008);
    Virus myVirus5("TAGCA", 1009);
    

    vdetect.insert(myVirus);
    vdetect.insert(myVirus2);
    vdetect.insert(myVirus3);
    vdetect.insert(myVirus4);
    vdetect.insert(myVirus5);

    
   

    if(vdetect.m_currentSize == 5 && !(vdetect.getVirus("AAATC", 1008) == EMPTY) && !(vdetect.getVirus("ATCAT", 3001) == EMPTY)) {
        vdetect.remove(myVirus);
        vdetect.remove(myVirus3);
        vdetect.remove(myVirus4);
    }
    else 
        return false;

    //since 3 things were deleted its 3
    if(vdetect.m_currNumDeleted == 3 && (vdetect.getVirus("AAATC", 1008) == EMPTY) && !(vdetect.getVirus("TAGCA", 1009) == EMPTY))
        return true;
    
    return false;
}

//uses double hashing without triggering a rehash 
bool Tester::removeWithDoubleNoHash(){
VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);
    Virus myVirus("AGTCA", 1001);
    Virus myVirus2("TGACA", 2001);
    Virus myVirus3("ATCAT", 3001);
    Virus myVirus4("AAATC", 1008);
    Virus myVirus5("TAGCA", 1009);
    

    vdetect.insert(myVirus);
    vdetect.insert(myVirus2);
    vdetect.insert(myVirus3);
    vdetect.insert(myVirus4);
    vdetect.insert(myVirus5);

    
   

    if(vdetect.m_currentSize == 5 && !(vdetect.getVirus("AAATC", 1008) == EMPTY) && !(vdetect.getVirus("ATCAT", 3001) == EMPTY)) {
        vdetect.remove(myVirus);
        vdetect.remove(myVirus3);
        vdetect.remove(myVirus4);
    }
    else 
        return false;
    //simce three things are deleted it should be 3 and removed things shouldnt be found
    if(vdetect.m_currNumDeleted == 3 && (vdetect.getVirus("AAATC", 1008) == EMPTY) && !(vdetect.getVirus("TAGCA", 1009) == EMPTY))
        return true;
    
    return false;
}


//removes a few keys using no probing method
bool Tester::removeWithNoMethod(){
    VDetect vdetect(MINPRIME, hashCode, NONE);
    Virus myVirus("AGTCA", 1001);
    Virus myVirus2("TGACA", 2001);
    Virus myVirus3("ATCAT", 3001);
   Virus myVirus4("AAATC", 1008);
    Virus myVirus5("TAGCA", 1009);
    

    vdetect.insert(myVirus);
    vdetect.insert(myVirus2);
    vdetect.insert(myVirus3);
    vdetect.insert(myVirus4);
    vdetect.insert(myVirus5);

    
   

    if(vdetect.m_currentSize == 5 && !(vdetect.getVirus("AAATC", 1008) == EMPTY) && !(vdetect.getVirus("ATCAT", 3001) == EMPTY)) {
        vdetect.remove(myVirus);
        vdetect.remove(myVirus3);
        vdetect.remove(myVirus4);
    }
    else 
        return false;

    if(vdetect.m_currNumDeleted == 3 && (vdetect.getVirus("AAATC", 1008) == EMPTY) && !(vdetect.getVirus("TAGCA", 1009) == EMPTY))
        return true;
    
    return false;
       
}

//Test the rehash completion after triggering rehash due to delete ratio, 
//i.e. all live data is transferred to the new table and the old table is removed.
bool Tester::removeWithQuad(){
    Random RndID(MINID,MAXID);
    Virus dataObj;

    //change insert to test different sizes
    int insert = 80;
    int table = insert*2 +1;
    int deleted = insert *.8;
    int moved = 0;

    VDetect vdetect(table, hashCode, QUADRATIC);

    Virus dataList[insert];

    //inserts into table
    for (int i=0;i<insert;i++){
        
        dataObj = Virus("AGTCA" + to_string(i), MINID + i);

        // saving data for later use
        dataList[i] = dataObj;

        // inserting data in to the VDetect object
        vdetect.insert(dataObj);        
    }

    //Less than delete factor so should not rehash
    for(int i = 0; i < deleted; i++) {
       vdetect.remove(dataList[i]);
    }

    // if a rehash occured when delete factor < .8
    if(vdetect.m_oldTable != nullptr){

        cout << "Rehash triggered when it shouldn't have" << endl;
        return false;
    }

    //triggers rehash
    vdetect.remove(dataList[deleted]);

    // if a rehash didn't occur when delete factor > .8
    if(vdetect.m_oldTable == nullptr){

        cout << "Rehash didn't trigger" << endl;
        return false;
    }

    moved = vdetect.m_oldSize - (vdetect.m_oldNumDeleted - vdetect.m_currentSize);

    // 25% of viruses or remaining viruses have not moved to the new table
    if(vdetect.m_currentSize != moved){
        cout << moved << endl;
        cout << vdetect.m_currentSize << endl;
        cout << "SIZE IS NOT " << vdetect.m_currentSize << endl;
        return false;
    }

    // if it did rehash and create the m_oldTable then it worked
    if(vdetect.m_oldTable != nullptr){

        return true;
    
    }else{

        cout << "LAST FAIL" << endl;
        return false; 
    }
}

//Test the rehashing is triggered after a descent number of data removal.
bool Tester::removeWithDoubleHash(){
    Random RndID(MINID,MAXID);
    Virus dataObj;

    //change insert to test different sizes
    int insert = 80;
    int table = insert*2 +1;
    int deleted = insert *.8;
    int moved = 0;

    VDetect vdetect(table, hashCode, DOUBLEHASH);

    Virus dataList[insert];

    //inserts into table
    for (int i=0;i<insert;i++){
        
        dataObj = Virus("AGCTA" + to_string(i), MINID + i);

        // saving data for later use
        dataList[i] = dataObj;

        // inserting data in to the VDetect object
        vdetect.insert(dataObj);        
    }

    //Less than delete factor so should not rehash
    for(int i = 0; i < deleted; i++) {
       vdetect.remove(dataList[i]);
    }

    // if a rehash occured when delete factor < .8
    if(vdetect.m_oldTable != nullptr){

        cout << "Rehash triggered when it shouldn't have" << endl;
        return false;
    }

    //triggers rehash
    vdetect.remove(dataList[deleted]);

    // if a rehash didn't occur when delete factor > .8
    if(vdetect.m_oldTable == nullptr){

        cout << "Rehash didn't trigger" << endl;
        return false;
    }

    moved = vdetect.m_oldSize - (vdetect.m_oldNumDeleted - vdetect.m_currentSize);

    // 25% of viruses or remaining viruses have not moved to the new table
    if(vdetect.m_currentSize != moved){
        cout << moved << endl;
        cout << vdetect.m_currentSize << endl;
        cout << "SIZE IS NOT " << vdetect.m_currentSize << endl;
        return false;
    }

    // if it did rehash and create the m_oldTable then it worked
    if(vdetect.m_oldTable != nullptr){

        return true;
    
    }else{

        cout << "LAST FAIL" << endl;
        return false; 
    }
}

//Test the find operation (getVirus(...) function) for an error case, the Virus object does not exist in the database.
bool Tester::getVirusErrorCase(){
    //insert nothing 

    Virus dataObj;
    VDetect vdetect(MINPRIME, hashCode, NONE);
    bool result = true;
    result = result && (vdetect.getVirus("ATCGA", 1005) == EMPTY);
    if(result && vdetect.m_currentSize == 0)
        return true;
    else    
        return false;
    


}
//Test the find operation (getVirus(...) function) with a few non-colliding keys.
bool Tester::getVirusNonColliding(){

    //bool result = true;
    VDetect vdetect(MINPRIME, hashCode, NONE);
    Virus myVirus("AGTCA", 1001);
    Virus myVirus2("TGACA", 2001);
    Virus myVirus3("ATCAT", 3001);
   Virus myVirus4("AAATC", 1008);
    Virus myVirus5("TAGCA", 1009);
    

    vdetect.insert(myVirus);
    vdetect.insert(myVirus2);
    vdetect.insert(myVirus3);
    vdetect.insert(myVirus4);
    vdetect.insert(myVirus5);
   

    if(vdetect.m_currentSize == 5 && (vdetect.getVirus("ATAGA", 1007) == EMPTY) && !(vdetect.getVirus("ATCAT", 3001) == EMPTY))
        return true;
    else    
        return false;

}

//Test the find operation (getVirus(...) function) with a number of colliding keys without triggering a rehash. 
//This also tests whether the insertion works correctly with colliding data.
bool Tester::getVirusCollidingWithoutRehash(){
    vector<Virus> dataList;
    Random RndID(MINID,MAXID);

    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    for (int i=0;i<5;i++){
        // generating random data
        Virus dataObj = Virus("ACATG", MINID + i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the VDetect object
        vdetect.insert(dataObj);
    }
    
    Virus myVirus5("TAGCA", 2000);
    Virus myVirus6("TGCCA", 2001);
    Virus myVirus7("ATAGA", 2007);
    vdetect.insert(myVirus5);
    vdetect.insert(myVirus6);
    vdetect.insert(myVirus7);

    if(vdetect.m_currentSize == 8 && !(vdetect.getVirus("TAGCA", 2000) == EMPTY) && !(vdetect.getVirus("ATAGA", 2007) == EMPTY) && !(vdetect.getVirus( "ACATG", 1003) == EMPTY) && !(vdetect.getVirus( "ACATG", 1002) == EMPTY)  )
        return true;
    else
        return false;


}

int main(){
    Tester test;
    cout << "TESTING INSERT" << endl;
    if (test.nonCollidingInsert())
        cout << "Non colliding data points test passed" << endl;
    else 
        cout << "Non colliding data points test failed" << endl;

    if(test.collidingInsert())
        cout << "Colliding data points test passed" << endl;
    else
        cout << "Colliding data points test failed" << endl;

    if(test.invalidID())
        cout << "Invalid ID test passed" << endl;
    else
        cout << "Invalid ID test failed" << endl;

    if(test.quadratictestSingleRehash())
        cout << "Quadratictest test passed" << endl;
    else 
        cout << "Quadratictest test failed" << endl;
    
    if(test.quadratictestFullRehash())
        cout << "Quadratictest with full rehash test passed" << endl;
    else
        cout << "Quadratictest with full rehash test failed" << endl;
    
    if(test.quadWithoutRehash())
        cout << "QuadWithout rehash test passed" << endl;
    else
        cout << "QuadWithout rehash test failed" << endl;
    
    if(test.doublehashTestFullRehash())
        cout << "Doublehash test passed" << endl;
    else 
        cout << "Doublehash test failed" << endl;
    
    if(test.doubleWithoutRehash())
        cout << "DoublewithoutRehash test passed" << endl;
    else 
        cout << "DoublewithoutRehash test failed" << endl;
    cout << endl;

     cout << "TESTING REMOVE" << endl;
    if(test.normalRemove())
        cout << "Normal non colliding remove test passed" << endl;
    else 
        cout << "Normal non colliding remove test failed" << endl;

    if(test.removeWithNoMethod())
        cout << "Remove with no probing method test passed" << endl;
    else 
        cout << "Remove with no probing method test failed" << endl;

    if(test.removeWithQuad())
        cout << "Remove with quadratic probing test passed" << endl;
    else 
        cout << "Remove with quadratic probing test failed" << endl;

    if(test.removeWithQuadNoHash())
        cout << "Remove with quadratic probing no hash test passed" << endl;
    else 
        cout << "Remove with quadratic probing no hash test failed" << endl;

    if(test.removeWithDoubleHash())
        cout << "Remove with double hash probing test passed" << endl;
    else
        cout << "Remove with double hash probing test failed" << endl;

    if(test.removeWithDoubleNoHash())
        cout << "Remove with double no hash probing test passed" << endl;
    else 
        cout << "Remove with double no hash probing test failed" << endl;
    cout << endl;

    cout << "GET VIRUS " << endl;

    if(test.getVirusErrorCase())
        cout << "GetVirus error case passed" << endl;
    else    
        cout << "GetVirus error case failed" << endl;
    
    if(test.getVirusNonColliding())
        cout << "GetVirus non colliding test passed" << endl;
    else 
        cout << "GetVirus with non colliding test failed" << endl;

    if(test.getVirusCollidingWithoutRehash())
        cout << "GetVirus with colliding without hash test passed" << endl;
    else 
        cout << "GetVirus with colliding without hash test failed" << endl;
          
}

unsigned int hashCode(const string str) {
   unsigned int val = 0 ;
   const unsigned int thirtyThree = 33 ;  // magic number from textbook
   for (int i = 0 ; i < str.length(); i++)
      val = val * thirtyThree + str[i] ;
   return val ;
}

string sequencer(int size, int seedNum){
    //this function returns a random DNA sequence
    string sequence = "";
    Random rndObject(0,3);
    rndObject.setSeed(seedNum);
    for (int i=0;i<size;i++){
        sequence = sequence + ALPHA[rndObject.getRandNum()];
    }
    return sequence;
}
