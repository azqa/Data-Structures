
// Name: Azqa Asad
// File: fuel.h

#include "fuel.h"



//Default constructor creates an empty object and initializes member variables.
FuelSys::FuelSys(){
    m_current = nullptr;
   
}

//Destrcutor 
FuelSys::~FuelSys(){
    clear();
  
    }

//helper function for the destructor 
void FuelSys::clear() {
    Tank* currTank = m_current;
    Pump* tempPump = nullptr; 
    Tank* tempTank = nullptr;

    if(m_current != nullptr){
        
        while(currTank->m_next != m_current){
            tempTank = currTank; 
        

        //deletes the pumps
            while(tempTank->m_pumps != nullptr) {
            tempPump = tempTank->m_pumps;
            tempTank->m_pumps = tempTank->m_pumps->m_next;
            delete tempPump; 
            }
             currTank = currTank->m_next;
             delete tempTank;
        }
	//deletes the current pointers pumps outside
         while(currTank->m_pumps != nullptr) {
            tempPump = currTank->m_pumps;
            currTank->m_pumps = currTank->m_pumps->m_next;
            delete tempPump; 
            }
            delete currTank;

    } 

}



//This function creates and inserts a new Tank object after the current 
//location of the list and makes the node the current location. 
//If the insertion is successful the function returns true, otherwise it returns false. 
//Since the tank IDs must be unique in the list this function will not insert the tank if it already exists. 
//In such a failure case the function returns false. The tankCap cannot be less than the min capacity. 
//The amount of fuel cannot exceed the tank capacity.
bool FuelSys::addTank(int tankID, int tankCap, int tankFuel = 0) {
    //pointers and vars necessary for the function
    Tank *currTank = m_current; 
    bool result = false; 

    //only gonna run the function if the tank ID already doesnt exist
    if(!findTank(tankID)){
      
    
    
    //if the list is empty
    if(m_current == nullptr) {
      //if the tank capacity is > than mincap and tank fuel <= tankCap
        if(tankCap >= MINCAP && tankFuel <= tankCap && tankID >= 0) {
	   Tank* newTank = new Tank(tankID, tankCap, tankFuel);
	  m_current = newTank;
            m_current->m_next = m_current;
            
            return true;
        }
           
    }
    //list isn't empty and you're gonna add to the tail
    else {
       
        if(tankCap >= MINCAP && tankFuel <= tankCap && tankID >= 0)  {
	  //allocates memory 
	        Tank* newTank = new Tank(tankID, tankCap, tankFuel);

                newTank->m_next = m_current->m_next;
                m_current -> m_next = newTank;
                m_current = newTank; 
                return true;
              
            }
    
        }
    }
    m_current = currTank;
    return result;
   
}

//This function removes the tank with tankID from the list. 
//If the requested tank is removed the function returns true otherwise it returns false, i.e. 
//if tankID does not exists the function returns false. 
//Note, if the tank has pumps the list of pumps must be removed too.
bool FuelSys::removeTank(int tankID){
  //tank id found
  if(findTank(tankID)){
    Tank *nextTank = m_current->m_next;
     Pump* temp = nullptr;
    Tank* prev = m_current; 

    //list is not empty
    if(m_current!=nullptr) {

        //one node in the list and check if it is the ID of the tank 
        if(m_current == nextTank) {
           
            if(m_current->m_tankID == tankID) {
                delete nextTank;
                m_current = nullptr; 
                return true;
            }
        //more than one node    
        }else{
        
             
               Tank* toDelete = prev->m_next; 
                prev->m_next = toDelete->m_next;
                

                    //delete pumps here 
                  
                   while(toDelete->m_pumps != nullptr) {
                        temp = toDelete->m_pumps; 
                         toDelete->m_pumps = toDelete->m_pumps->m_next;
                          delete temp; 
                        }
                  
                    //deletes the tank
                    delete toDelete;
                    return true;

                } 
           

                }
    }
    
    return false;
    
}

//This function searches the list for tankID. 
//If the ID is found the function makes it the next of current location and it returns true.
// If the ID is not found the function returns false.
bool FuelSys::findTank(int tankID){
   
    //while the list isn't empty
    if(m_current!=nullptr) {
        Tank *nextTank = m_current->m_next; 
    
       
        //one thing in the list
        if(nextTank==m_current) {
            if(nextTank->m_tankID == tankID) {
                m_current = nextTank;
                return true;
   
            }
        }
        else {
            //make the current location the node before the found one
            //only when there are more than one nodes 
            Tank *currTank = m_current; 

            while(m_current->m_tankID != currTank->m_next->m_tankID) {
                //beginning of the id is found
                if(currTank->m_next->m_tankID == tankID) {
                    //sets it to the next of the found tank
                    m_current = currTank; 
                    return true;
                }
                //moves the pointers
                currTank = currTank->m_next;
 
            }

            //if m_current is the id we are looking for
            if (m_current->m_tankID == tankID) {
               
                m_current = currTank; 
                 return true;

            }
     
           
        }
    }
   
    return false;  

 
}

//This function finds the tankID and adds a pump with pumpID to the tank's pump list. 
//The targetTank is the tank ID that will receive fuel from the parent of the pump in the case of transfer requests. 
//Both tankID and targetID must exist in the list in order to add the pump. In the case of success the function returns true, 
//otherwise it returns false. 
//The pump must be added to the head of the pump list.
bool FuelSys::addPump(int tankID, int pumpID, int targetTank){
   
   //function returns true
    if(findTank(targetTank)){
        if(findTank(tankID)){
    //gives the tank we want to remove because curr is set to the tank before it
    //therefore get the next to get the tank we are looking for
	 
    Pump* currPump = nullptr;
    Tank* temp = m_current->m_next; 
    bool pumpFLAG = true; 
     bool flag = true;

        //checks for tanks IDs
     if(targetTank == tankID){
         
          return false;
     }
     

    if(flag && pumpID >= 0) {
        //pumps list is empty 
        if(temp->m_pumps == nullptr) {
            Pump* newPump = new Pump(pumpID, targetTank, temp->m_pumps); 
            temp->m_pumps = newPump;
           

            return true;
        }
        //more than one pump 
        else  {
             currPump = temp->m_pumps; 
            //while the ids are unique
          
            while(pumpFLAG && currPump != nullptr){
                if(currPump->m_pumpID == pumpID){
                   
                    return false;
                    
                }
                currPump = currPump->m_next;
            }

            //allocates memory before adding the pumps
            Pump* newPump = new Pump(pumpID, targetTank, temp->m_pumps); 
            newPump->m_next = temp->m_pumps;
            temp->m_pumps = newPump;
            
            return true;
            
            
        }
    }
   
}
    } 
return false; 
}

//This function removes the pumpID from the tankID. 
//If the remove operation is successful the function returns true. 
//If either tankID or pumpID does not exist it is a failure and the function returns false.
bool FuelSys::removePump(int tankID, int pumpID){

    //if the tank has been found 
    if(findTank(tankID)){
    //gives the tank we want to remove because curr is set to the tank before it
    //therefore get the next to get the tank we are looking for
    Tank* temp = m_current->m_next;
    //stores the found pump
    Pump* toDel = temp->m_pumps;
   
    Pump* prev = nullptr;

    //Only one pump in the list 
        if(toDel->m_next == nullptr && toDel->m_pumpID == pumpID) {
            delete toDel;
            toDel = nullptr;
            temp->m_pumps = nullptr; 
            return true;

        //removes at the head
        } else if(toDel->m_next != nullptr && toDel->m_pumpID == pumpID) {
            temp->m_pumps = toDel->m_next;
            delete toDel;
            toDel = nullptr;
            return true;

        }
        //more than one pump in the list
      else {

            while(toDel != nullptr) {
                
                //removes from tail
                if(toDel->m_next == nullptr && toDel->m_pumpID == pumpID) {
                    delete toDel; 
                    toDel = nullptr;
                    prev->m_next = nullptr; 
                    return true;
                }
                //removes from the middle
                else if(toDel->m_next != nullptr && toDel->m_pumpID == pumpID) {
                    prev->m_next = toDel->m_next; 
                    delete toDel;
                    toDel = nullptr;
                    return true; 
                }
                prev = toDel;
                toDel = toDel->m_next;

             
        }
    } 

    }
    return false;
    
}

//This function calculates and returns the total amount of current fuel in the airplane. 
//The total amount of fuel is the sum of fuel in all tanks
int FuelSys::totalFuel() const{

    int totalFuel = 0;
    Tank* currTank = m_current; 

    if(m_current == nullptr) 
        return totalFuel;
    //one tank in the list    
    else if(m_current->m_tankID == currTank->m_next->m_tankID) 
        totalFuel += currTank->m_tankFuel;
    else { 

    //more than one tank in the list
    while(m_current->m_tankID != currTank->m_next->m_tankID) {
        totalFuel = totalFuel + currTank->m_tankFuel; 
        currTank = currTank->m_next;

    }
        totalFuel = totalFuel + currTank->m_tankFuel; 
    }
    return totalFuel;
    
}

//This function transfers the fuel from tankID to the targetID specified in the pumpID. 
//If the amount of requested transfer is more than the current empty space in the target tank, the function fills the target tank and returns true.
// If the amount of requested transfer is less than the empty space of the target tank the function transfers all and returns true. 
//If the amount of requested transfer is greater than the current fuel in the source tank, the function performs the transfer and makes the source tank empty. 
//In a case of failure that either tank or the pump does not exist the function returns false.
bool FuelSys::drain(int tankID, int pumpID, int fuel){

  //invalid fuel amount
  if(fuel < 0){
    return false;
  }
    //this means the tank exists
    if(findTank(tankID)){
        Tank* currTank = m_current->m_next;
        Pump* currPump = currTank->m_pumps; 
       
        bool foundPump = false;
        //while the list isnt empty
        if(currPump != nullptr) {

            //while the next node isnt pointing to null
            while(currPump != nullptr && foundPump == false) {
                //finds the pump with the id
                if(currPump->m_pumpID == pumpID){
                    foundPump = true;
                } else {
                currPump = currPump->m_next; 
                }
            //end of while loop
            }
            //finds the target tank
            if(foundPump) {
            if(findTank(currPump->m_target)) {
	      if(fuel >= 0){
                Tank* targetTank = m_current->m_next; 
            //If the amount of requested transfer is less than the empty space of the target tank the function transfers all and returns true. 

                if(targetTank->m_tankCapacity - targetTank->m_tankFuel > fuel) {
                    //if the requested transfer is more than the fuel of the current tank
                    if(fuel > currTank->m_tankFuel ) {
                        targetTank->m_tankFuel = targetTank->m_tankFuel + currTank->m_tankFuel;
                        currTank->m_tankFuel = 0; 
                        return true;
                    } else {
                        targetTank->m_tankFuel = targetTank->m_tankFuel + fuel;
                        currTank->m_tankFuel = currTank->m_tankFuel - fuel; 
                        return true;
                    }
            //If the amount of requested transfer is more than the current empty space in the target tank, the function fills the target tank and returns true.

                } else if (fuel > targetTank->m_tankCapacity - targetTank->m_tankFuel) {
                   
                    if(targetTank->m_tankCapacity - targetTank->m_tankFuel > currTank->m_tankFuel) {
                        targetTank->m_tankFuel = targetTank->m_tankFuel + currTank->m_tankFuel; 
                        currTank->m_tankFuel = 0; 
                        return true;
                    } else {
                        currTank->m_tankFuel = currTank->m_tankFuel - (targetTank->m_tankCapacity - targetTank->m_tankFuel); 
                        targetTank->m_tankFuel = targetTank->m_tankCapacity; 
                        return true;
                    }
            
            //If the amount of requested transfer is greater than the current fuel in the source tank, the function performs the transfer and makes the source tank empty. 

                } else if (fuel > currTank->m_tankFuel) {
                    targetTank->m_tankFuel = targetTank->m_tankFuel + currTank->m_tankFuel; 
                    currTank->m_tankFuel = 0; 
                    
                    return true; 
                }
                

            }
            return false;
	    }

            }
        }
        //the pump id has been found
    } 

    return false; 
    
}

//This function fills up the tankID with the amount of fuel.
// If the empty space of the tank is less than fuel the function still fills up the tank up to its capacity and returns true. 
//If the tank does not exist the function returns false.
bool FuelSys::fill(int tankID, int fuel){

//tank exists
    if(findTank(tankID)){
      if(fuel >=0){
        Tank* currTank = m_current->m_next;

	//adds up the total
        if(currTank->m_tankFuel + fuel >= currTank->m_tankCapacity) {
            currTank->m_tankFuel = currTank->m_tankCapacity; 
            return true;
	    
        } else if (currTank->m_tankFuel + fuel < currTank->m_tankCapacity) {
            currTank->m_tankFuel = currTank->m_tankFuel + fuel; 
            return true;
        }
      }
    }

    return false;

}

//The assignment operator creates a deep copy of rhs. 
//Reminder: a deep copy means the current object has the same information as rhs object, however, 
//it has its own memory allocated. Moreover, an assignment operator needs protection against self-assignment. 
//Note: the new copy is an exact copy of rhs. For example, the pumps of a tank appear in the same order as in rhs.
const FuelSys & FuelSys::operator=(const FuelSys & rhs){

    if(&rhs != this){
      //deletes everthing first
        clear();
        Tank* curr = rhs.m_current;
        addTank(curr->m_tankID, curr->m_tankCapacity, curr->m_tankFuel);
        Tank *start = m_current;
        Pump* prevPump = nullptr;
        Pump* currPump = curr->m_pumps; 


        //adds tanks and pumps
        do{ 
            addTank(curr->m_tankID, curr->m_tankCapacity, curr->m_tankFuel);

            //allocate memory for pumps
            //adds the pumps
            prevPump = nullptr;
            currPump = curr->m_pumps; 
            while(currPump != nullptr){
	      //adds pumps on an empty list
                if(prevPump == nullptr) {
                     Pump *newPump = new Pump(currPump->m_pumpID, currPump->m_target); 
                     m_current->m_pumps = newPump;
                     prevPump = newPump;
               } else {
		  //adds on pumps to the first pump added
                    prevPump->m_next = new Pump(currPump->m_pumpID, currPump->m_target); 
                    prevPump = prevPump->m_next; 

                }
                currPump = currPump->m_next;
              
            }
	    //moves the pointers
            curr = curr->m_next; 
        } while (curr != rhs.m_current);
	//updates m_cuurent
        m_current = start;
        }
    return *this; 


}
void FuelSys::dumpSys() const{
    if (m_current != nullptr){
        Tank* tempTank = m_current->m_next;//we start at front item
        //we continue visting nodes until we reach the cursor
        while(m_current != nullptr && tempTank != m_current){
            cout << "Tank " << tempTank->m_tankID << "(" << tempTank->m_tankFuel << " kg)" << endl;
            // now dump the targets for all pumps in this tank
            // we need to traverse the list of pumps
            dumpPumps(tempTank->m_pumps);
            tempTank = tempTank->m_next;
        }
        //at the end we visit the cursor (current)
        //this also covers the case that there is only one item
        cout << "Tank " << m_current->m_tankID << "(" << m_current->m_tankFuel << " kg)" << endl;
        dumpPumps(tempTank->m_pumps);
        cout << "The current tank is " << m_current->m_tankID << endl;
    }
    else
        cout << "There is no tank in the system!\n\n";
}

void FuelSys::dumpPumps(Pump* pumps) const{
    // this traverses the linked list to the end
    Pump* tempPump = pumps;
    while (tempPump != nullptr){
        cout << " => pump " << tempPump->m_pumpID << "(To tank " << tempPump->m_target << ")" << endl;
        tempPump = tempPump->m_next;
    }
}
