//name: Azqa Asad
//file: mytest.cpp
//email: azqaa1@umbc.edu
#include "fuel.h"
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
        bool addTankNormaltest();
        bool addTankErrortest();
        bool removeTankNormaltest();
        bool removetankErrortest();
        bool findTankNormaltest();
        bool findTankErrortest();
        bool addPumpNormaltest();
        bool addPumpErrortest();
        bool addPumpErrortestUniqueID();
        bool removePumpNormaltest();
        bool removePumpErrortest();
        bool totalFuelNormaltest();
        bool totalFuelErrortest();
        bool drainNormaltest();
        bool drainErrortest();
        bool fillNormaltest();
        bool fillErrortest();
  bool assignmenttest(); 
};

//function passes
bool Tester::addTankNormaltest(){
    bool result = true;
    FuelSys sys;
    int numTanks = 20;
    
    Random randFuel(MINCAP, DEFCAP);
    for (int i = 0; i < numTanks; i++){
      //adds the tanks
        result = (sys.addTank(i, DEFCAP, randFuel.getRandNum())) && result;
        result = (sys.m_current->m_tankID == i) && result;
    }
    return result;
}

//test passes
bool Tester::addTankErrortest(){
    bool result = true;
    FuelSys sys;
    int numTanks = 20;

    Random randFuel(MINCAP, DEFCAP);
    for (int i = 0; i < numTanks; i++){
        sys.addTank(i, DEFCAP, randFuel.getRandNum()); 
        result = (sys.addTank(i, DEFCAP, randFuel.getRandNum()) == false) && result;

    }
    //adds an invalid tank id
    result = (sys.addTank(-10, DEFCAP, randFuel.getRandNum()) == false) && result;
    result = (sys.m_current->m_tankID != -10) && result;
    result = (sys.addTank(numTanks+1, DEFCAP, DEFCAP+1000) == false) && result;
    result = (sys.m_current->m_tankID!= numTanks+1) && result;
    result = (sys.addTank(25, 0, 1000) == false) && result;


    return result;
}

//test passes
//adds tanks and clears out the entire list
bool Tester::removeTankNormaltest() {
    bool result = true;
    FuelSys sys;
    int numTanks = 20;

    Random randFuel(MINCAP, DEFCAP);
    for (int i = 0; i < numTanks; i++){
        result = (sys.addTank(i, DEFCAP, randFuel.getRandNum())) && result;
        result = (sys.m_current->m_tankID == i) && result;
    }

    for (int i = 0; i < numTanks; i++) {
        //removes all the tanks 
        result = (sys.removeTank(i)) && result;
    }
    //checks if the lists is empty
    if(sys.m_current == nullptr)
        result = true;
  
    return result;

} 

//test passes
//removes a tank that doesnt exist
bool Tester::removetankErrortest(){
    bool result = true;
    FuelSys sys; 
    result = (sys.removeTank(4) == false) && result;

    return result;
    }

//test passes
//checks if currents next tanks id matches the id  being passed in
bool Tester::findTankNormaltest() {
    bool result = true;
    FuelSys sys;
    int numTanks = 10;

    Random randFuel(MINCAP, DEFCAP);
    //adds the tanks
    for (int i = 0; i < numTanks; i++){
        result = (sys.addTank(i, DEFCAP, randFuel.getRandNum())) && result;
    }
    //looks for tank id and checks if the currents next id matches
        sys.findTank(5);
        result = (sys.m_current->m_next->m_tankID == 5) && result;
    
    
    return result;


}

//test passes
//checks an invalid id that doesnt exist
bool Tester::findTankErrortest() {
    bool result = true;
    FuelSys sys;
    int numTanks = 10;

    Random randFuel(MINCAP, DEFCAP);
    //adds the tanks
    for (int i = 0; i < numTanks; i++){
        result = (sys.addTank(i, DEFCAP, randFuel.getRandNum())) && result;
    }
        sys.findTank(-10);
        result = ((sys.m_current->m_next->m_tankID == -10) == false) && result;
    
    
    return result;


}

//test passes
//adds pumps with valid tank ids
bool Tester::addPumpNormaltest() {
    bool result = true;
    FuelSys sys;
    int numTanks = 4;

    Random randFuel(MINCAP, DEFCAP);
   
    //adds the tanks
    for (int i = 1; i <= numTanks; i++){
        result = (sys.addTank(i, DEFCAP, randFuel.getRandNum())) && result;
    }
        result = sys.addPump(1,1,4) && result;
        result = sys.addPump(2,2,1) && result;
        result = sys.addPump(3,3,2)&& result;
        result = sys.addPump(4,3,3)&& result;

    return result;

    }

//test passes
//aads a pump to a tank that doesnt exist
//checks invlaid pump id
    bool Tester::addPumpErrortest(){
        bool result = true;
        FuelSys sys;
        int numTanks = 4;

        Random randFuel(MINCAP, DEFCAP);
   
    //adds the tanks
        for (int i = 1; i <= numTanks; i++){
            result = (sys.addTank(i, DEFCAP, randFuel.getRandNum())) && result;
        }
        //will add to a pump that doesnt exsit
            result = (sys.addPump(6,1,4) == false ) && result ;
	    result = (sys.addPump(1,-1,2) == false ) && result;

        return result;
        }

//test passes
//checks for invlaid pump ids
    bool Tester::addPumpErrortestUniqueID(){
         bool result = true;
        FuelSys sys;
        int numTanks = 4;

        Random randFuel(MINCAP, DEFCAP);
    
        //adds the tanks
        for (int i = 1; i <= numTanks; i++){
            result = (sys.addTank(i, DEFCAP, randFuel.getRandNum())) && result;
        }
        //will add to a pump that doesnt exsit
            result = (sys.addPump(1,1,2)) && result ;
            result = (sys.addPump(2,2,1)) && result ;
            result = (sys.addPump(3,3,4)) && result ;
            //adds with the same pumpID
            result = (sys.addPump(1,1,3) == false ) && result ;
        return result;

      }

//test passes
//removes the middle, tail, and head
    bool Tester::removePumpNormaltest(){
        bool result = true;
        FuelSys sys;
        int numTanks = 3;

        Random randFuel(MINCAP, DEFCAP);
   
    //adds the tanks
        for (int i = 1; i <= numTanks; i++){
            result = (sys.addTank(i, DEFCAP, randFuel.getRandNum())) && result;
        }

            //adds the pumps
            result = sys.addPump(1,1,2) && result;
            result = sys.addPump(1,2,2) && result;
            result = sys.addPump(2,1,1) && result;
	    result = sys.addPump(3,1,1) && result;
            //removes the pump

	    //removes from the middle
            result = sys.removePump(2,1) && result;
	    //removes from the head
            result = sys.removePump(1,1) && result;
            result = sys.removePump(1,2) && result;
	    //removes the only thing/tail
            result = sys.removePump(3,1) && result; 
           
	    //checks if the pumps list is empty 
            result = (sys.m_current->m_pumps == nullptr) && result;

        return result;

    }

//test passes
//removes a tank that doesnt exist
bool Tester::removePumpErrortest() {
   bool result = true;
   FuelSys sys;
   result = (sys.removePump(1,1) == false) && result;
   return result;

    }

//test passes
//gets the total of all tanks
bool Tester::totalFuelNormaltest(){
    bool result = true;
     FuelSys sys;
    
    //adds the tanks
        
    (sys.addTank(1, DEFCAP, 2300)); 
    (sys.addTank(2, DEFCAP,  2500)); 
    (sys.addTank(3, DEFCAP, 4300)); 
    (sys.addTank(4, DEFCAP, 4999));
    //checks the total fuel after adding them
     result = (sys.totalFuel() == 14099) && result; 
        return result; 
    
    }
//test passes
//checks the total of an empty list
bool Tester::totalFuelErrortest(){
    bool result = false;
    FuelSys sys;

    //checks the fuel of en empty list
    if(sys.totalFuel() == 0){

      result = true; 
    }
      return result;
      }

//test passes
//checks for a non existing tank
    bool Tester::drainErrortest(){ 
        //Test whether drain() works correctly for the error cases. 
        //For example, the source tank or the pump or the destination tank does not exist in the system.
        bool result = true;
        FuelSys sys;
        int numTanks = 4;

        Random randFuel(MINCAP, DEFCAP);
    
        //adds the tanks
        for (int i = 1; i <= numTanks; i++){
            result = (sys.addTank(i, DEFCAP, randFuel.getRandNum())) && result;
        }
        
            //tankiD pumpID tagetID

            //adds pumps for each tank
            result = sys.addPump(1,1,4) && result; ;
            result = sys.addPump(2,2,1) && result;
            result = sys.addPump(3,3,2)&& result;
            result = sys.addPump(4,3,3)&& result;
            //drains from non existing pumps and tanks
            result = (sys.drain(5,1,5) == false) && result;
	    //passes a negative fuel
	    result = (sys.drain(1,4,-4) == false) && result;
        return result;
        }

//test passes
//checks multiple cases for drain
    bool Tester::drainNormaltest(){
        //tankID pumpID fuel
        //It transfers the fuel from the source tank to the target tank 
        //correctly where the requested fuel is less than the empty space of the target tank. 
        bool result = true;
        FuelSys sys;
        //adds the tanks
        result = (sys.addTank(1, DEFCAP, 2000)) && result;
        result = (sys.addTank(2, DEFCAP, 3000)) && result;
        result = (sys.addTank(3, DEFCAP, 4000)) && result;
        result = (sys.addTank(4, DEFCAP, 4500)) && result;

    
        //tankiD pumpID tagetID
        //adds pumps for each tank
        result = sys.addPump(1,1,4) && result; 
        result = sys.addPump(2,2,1) && result;
        result = sys.addPump(3,3,2)&& result;
        result = sys.addPump(4,3,3)&& result;

        //drains 200 from tank 1 to tank 4
        result = sys.drain(1,1,200) && result; 
        result = sys.findTank(1) && result;
        //tank 1 lost 200 fuel
        result = (sys.m_current->m_next->m_tankFuel == 1800) && result;
            
        //Another case would be when the amount of fuel is more than the empty space of the target tank.
        result = sys.drain(3,3,3000) && result; 
        result = sys.findTank(3) && result;
        result = (sys.m_current->m_next->m_tankFuel == 2000) && result;

        //fuel is greaster than the parent tank's fueq
        result = sys.drain(2,2,9000) && result;
        result = sys.findTank(2) && result;
        result = (sys.m_current->m_next->m_tankFuel == 1800) && result;


        return result;
        
    }

//test passes
//passes in a valid fuel amount to the tank
    bool Tester::fillNormaltest() {
         bool result = true;
        FuelSys sys;
        //adds the tanks
        result = (sys.addTank(1, DEFCAP, 2000)) && result;
        result = sys.fill(1, 3000) && result;
        result = sys.findTank(1) && result;
        result = (sys.m_current->m_next->m_tankFuel == 5000) && result;
        return result;
    }

//test passes
//fills a tank that doesnt exist
    bool Tester::fillErrortest() {
         bool result = true;
        FuelSys sys;
	result = (sys.addTank(1, 5000, 2000)) && result;
        //fills a tank that doesn't exist
        result = (sys.fill(2, 3000) == false) && result;
	//fills a tank with negative fuel
	result = (sys.fill(1, -10) == false) && result;
        return result;
    }


//function is suppsoed to pass and checks for lhs and rhs
   bool Tester::assignmenttest(){
     bool result = true;
     FuelSys sys;
      Random randFuel(MINCAP, DEFCAP);
     int numTanks = 4;
     for (int i = 1; i <= numTanks; i++){
        result = (sys.addTank(i, DEFCAP, randFuel.getRandNum())) && result;
    }
        result = sys.addPump(1,1,4) && result; 
        result = sys.addPump(2,2,1) && result;
        result = sys.addPump(3,3,2)&& result;
        result = sys.addPump(4,3,3)&& result;

	FuelSys concorde;
	//makes the copy of the lhs
	concorde = sys;

	Tank* currPtr = concorde.m_current;
	Tank* currSysPtr = sys.m_current;

	Pump* pumpPtr = nullptr;
	Pump* pumpSysPtr = nullptr;

	do{
	  
	  if(currPtr == currSysPtr){
	    return false;
	  }

	  //if the ids dont match the fuction returns false
	  if(currPtr->m_tankID != currSysPtr->m_tankID){
	    return false;
	  }
	  pumpPtr = currPtr->m_pumps;
	  pumpSysPtr = currSysPtr->m_pumps;
	  while(pumpPtr != nullptr){
	    if(pumpPtr->m_pumpID != pumpSysPtr->m_pumpID){
	      return false;
	    }
	    //memory adress
	    if(pumpPtr == pumpSysPtr){
	      return false;
	    }
	    pumpPtr = pumpPtr->m_next;
	    pumpSysPtr = pumpSysPtr->m_next;
	    }
	  //moves the pointers
	  currPtr = currPtr->m_next;
	  currSysPtr = currSysPtr->m_next;

	  //big loop for everything
	}while(currPtr != concorde.m_current);
	return result;
     

}


int main(){
    
    Tester tester;
   
    if(tester.addTankNormaltest()) 
        cout << "addTankNormaltest() Passed!" << endl;
    else 
        cout << "addTankNormaltest() Failed!" << endl;
    
    if(tester.addTankErrortest())
        cout << "addTankErrortest() Passed!" << endl;
    else 
        cout << "addTankErrortest() Failed!" << endl;
    cout << endl; 
     if(tester.removeTankNormaltest())
        cout << "removeTankNormaltest() Passed!" << endl;
    else 
        cout << "removeTankNormaltest() Failed!" << endl;

    if(tester.removetankErrortest()) 
        cout << "removeTankErrortest() Passed!" << endl;
    else 
        cout << "removeTankErrortest() Failed!" << endl;
    cout << endl;
     if(tester.findTankNormaltest())
        cout << "findTankNormaltest() Passed!" << endl;
    else 
        cout << "findTankNormaltest() Failed!" << endl;

    if(tester.findTankErrortest())
        cout << "findTankErrortest() Passed!" << endl;
    else 
        cout << "findTankErrortest() Failed!" << endl;
    cout<< endl;
    if(tester.addPumpNormaltest()) 
        cout << "addPumpNormaltest() Passed!" << endl;
    else 
        cout << "addPumpNormaltest() Failed!" << endl;
    
    if(tester.addPumpErrortest()) 
        cout << "addPumpErrortest() Passed!" << endl;
    else 
        cout << "addPumpErrortest() Failed!" << endl;
    
    if(tester.addPumpErrortestUniqueID()) 
        cout << "addPumpErrortestUniqueID() Passed!" << endl;
    else 
        cout << "addPumpErrortestUniqueID() Failed!" << endl;
    cout<<endl;
    
     if(tester.removePumpNormaltest())
        cout << "removePumpNormaltest() Passed!" << endl;
    else 
        cout << "removePumpNormaltest() Failed!" << endl;
        
    
    if(tester.removePumpErrortest()) 
        cout << "removePumpErrortest() Passed!" << endl;
    else 
        cout << "removePumpErrortest() Failed!" << endl;
    cout << endl;
    
    if(tester.totalFuelNormaltest())
        cout << "totalFuelNormaltest() Passed!" << endl;
    else 
        cout << "totalFuelNormaltest() Failed!" << endl;
    
    if(tester.totalFuelErrortest()) 
        cout << "totalFuelErrortest() Passed!" << endl;
    else 
        cout << "totalFuelErrortest() Failed!" << endl;
    cout<< endl;

    if(tester.drainErrortest())
        cout << "drainErrortest() Passed!" << endl;
    else 
        cout << "drainErrortest() Failed!" << endl;

    if(tester.drainNormaltest())
        cout << "drainNormaltest() Passed!" << endl;
    else 
        cout << "drainNormaltest() Failed!" << endl;
    cout<< endl;
    
    if(tester.fillNormaltest())
        cout << "fuelNormaltest() Passed!" << endl;
    else 
        cout << "fuelNormaltest() Failed!" << endl;
    if(tester.fillErrortest())
       cout << "fillErrortest() Passed!" << endl;
    else
      cout << "fillErrortest() Failed!" << endl;
    cout << endl;
    
    if(tester.assignmenttest())
      cout << "assignment operator passed" << endl;
    else
      cout << "assignment operator failed" << endl;
    
    return 0;
}
