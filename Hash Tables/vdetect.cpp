
// CMSC 341 - Spring 2023 - Project 4
// Author: Azqa Asad
// Section : 2
// File: vdetect.cpp
// email: azqaa1@umbc.edu

#include "vdetect.h"

//The constructor takes size to specify the length of the current hash table, and hash is a function pointer to a hash function. 
//The type of hash is defined in vdetect.h.
//The table size must be a prime number between MINPRIME and MAXPRIME. 
//If the user passes a size less than MINPRIME, the capacity must be set to MINPRIME. 
//If the user passes a size larger than MAXPRIME, the capacity must be set to MAXPRIME. 
//If the user passes a non-prime number the capacity must be set to the smallest prime number greater than user's value. 
//The probing parameter specifies the type of collision handling policy for the current hash table.
//Moreover, the constructor creates memory for the current table and initializes all member variables.
VDetect::VDetect(int size, hash_fn hash, prob_t probing = DEFPOLCY){
    if(size >= MINPRIME && size <= MAXPRIME) {
        m_currentCap = size;
    } else if (size < MINPRIME) {
        m_currentCap = MINPRIME;
    } else if (size > MAXPRIME) {
        m_currentCap = MAXPRIME;
    } 
    m_hash = hash; 
    m_currProbing = probing;
              // hash function
    m_newPolicy = NONE; ;     // stores the change of policy request

    m_currentTable = new Virus[m_currentCap]; // hash table
    for (int i = 0; i < m_currentCap; i++) {
        m_currentTable[i] = EMPTY;
    }
     // hash table size (capacity)
    m_currentSize = 0;   // current number of entries
    m_currNumDeleted = 0;// number of deleted entries
    m_oldTable = nullptr;      // hash table
    m_oldCap = 0;        // hash table size (capacity)
    m_oldSize = 0;       // current number of entries
    m_oldNumDeleted = 0; // number of deleted entries
    m_oldProbing = NONE; 
     

}

//deallocates all memory allocated
VDetect::~VDetect(){
    if(m_oldTable != nullptr)
        delete[] m_oldTable;
    
    if(m_currentTable != nullptr)
        delete[] m_currentTable;
    
}

//The user can change the collision handling policy of the hash table at the runtime.
// If a change request has been submitted by a user the new policy will be stored in the variable m_newPolicy.
// Once the next rehash operation is initiated the new policy will be used for the newly created hash table.
void VDetect::changeProbPolicy(prob_t policy){
    m_newPolicy = policy;
}




void VDetect::hashingHelper(Virus virus) {
    unsigned int hashFunc = m_hash(virus.getKey()) % m_currentCap;
    int counter = 0;

    // while we haven't iterated through the whole table
    while(counter < m_currentCap) {
        //cout << "inside insert" << endl;
        // No probing selected
        if(m_currProbing == NONE) {
            
            //hashFunc = (m_hash(virus.getKey())+counter) % m_currentCap;
               
            if(m_currentTable[hashFunc] == EMPTY ) {
                m_currentTable[hashFunc] = virus;
                m_currentSize++;
                
                //break;
            }  
             
            if(m_currentTable[hashFunc] == DELETED) {
                m_currentTable[hashFunc] = virus;
                m_currNumDeleted--;
           
                //break;
            }
            return ;
            //}
        }

        // Quadratic probing
        else if(m_currProbing == QUADRATIC) {
            //update it to become quadratic probing
            
            hashFunc = quadraticHelper(counter, virus.getKey());
            
            if(m_currentTable[hashFunc] == EMPTY ) {
                m_currentTable[hashFunc] = virus;
                m_currentSize++;
               
                break;
            } 
             
            if(m_currentTable[hashFunc] == DELETED) {
                m_currentTable[hashFunc] = virus;
                m_currNumDeleted--;
               
                break;
            }
        }

        // Doublehash probing
        else if(m_currProbing == DOUBLEHASH) {
            //update it to become double hash probing
            
            hashFunc = doubleHashHelper(counter, virus.getKey());
            //cout << "Doublehash probing" << endl;
            //cout << "double: " << hashFunc << endl;  
            if(m_currentTable[hashFunc] == EMPTY ) {
                m_currentTable[hashFunc] = virus;
                m_currentSize++;
              
                break;
            }  
             
            if(m_currentTable[hashFunc] == DELETED) {
                m_currentTable[hashFunc] = virus;
                m_currNumDeleted--;
                
                break;
            }

                
            
        }
        counter++;
    } 
  
    
   
}

//This function inserts an object into the current hash table. 
//The insertion index is determined by applying the hash function m_hash that is set in the VDetect constructor 
//and then reducing the output of the hash function modulo the table size.
// A hash function is provided in the sample driver.cpp file to be used in this project.
//Hash collisions should be resolved using the probing policy specified in the m_currProbing variable. 
//We insert into the table indicated by m_currentTable. After every insertion we need to check for the proper criteria, and if it is required,
// we need to rehash the entire table incrementally into a new table. 
//The incremental transfer proceeds with 25% of the nodes at a time.
// Once we transferred 25% of the nodes for the first time, the second 25% will be transferred at the next operation (insertion or removal). 
//Once all data is transferred to the new table, the old table will be removed, and its memory will be deallocated.
//If the Virus object is inserted, the function returns true, otherwise it returns false. A Virus object can only be inserted once. 
//The hash table does not contain duplicate objects. Moreover, the virus's ID value should be a valid one falling in the range [MINID-MAXID]. 
//Every Virus object is a unique object carrying the Virus's key and the virus's ID. The Virus's key is the key which is used for hashing.
bool VDetect::insert(Virus virus){
    //inserting
    
    if(getVirus(virus.getKey(), virus.getID()) == virus || virus.getID() < MINID || virus.getID() > MAXID){
        
       return false;
    }
    
    (hashingHelper(virus));
       
    //condition to start the rehash where we set everthing to old table
    // lambda() is > .5 and we haven't already created the new table
    if(lambda() > float(0.5)  && m_oldSize == 0) {

        m_oldProbing = m_currProbing;
        m_oldTable = m_currentTable;
        m_oldCap = m_currentCap;
        m_oldNumDeleted = m_currNumDeleted;
        m_oldSize = m_currentSize; 

        //to remove the contents 
        m_currentCap = findNextPrime(4 * (m_currentSize - m_currNumDeleted));
        m_currentSize = 0;   
        m_currNumDeleted = 0;
        

        //if user chose new policy, set new policy
       if(m_newPolicy != NONE){
            m_currProbing = m_newPolicy;
            m_newPolicy = NONE;
        }
        
        //create new table with new cap
        m_currentTable = new Virus[m_currentCap]; 
        for(int i = 0; i < m_currentCap; i++){
            m_currentTable[i] = EMPTY;
        }
    }
        
    //there are viruses left in the old table
    if(m_oldSize != 0) {

        int transfer = m_oldSize *.25;
        int moved = 0;
        int counter = 0;

        //while there still are 25% of viruses to transfer
        while(counter < m_oldCap && moved < transfer){

            //the entry is not deleted or empty, we insert entry into new table
            if(!(m_oldTable[counter] == DELETED || m_oldTable[counter] == EMPTY)){
                    
                //while we haven't found an empty spot to transfer virus to
                hashingHelper(m_oldTable[counter]); 

                m_oldTable[counter] = DELETED;
                m_oldNumDeleted++;
                moved++;

            }
               
            counter++;
        }

        //reached the end of the table, delete old data
        if(counter == m_oldCap){
            delete[] m_oldTable;
            m_oldTable = nullptr;
            m_oldProbing = NONE;
            m_oldCap = 0;
            m_oldNumDeleted = 0;
            m_oldSize = 0;

        }
    }
    
    return true;
}
  

//helper for quadratic probing
int VDetect::quadraticHelper(int i, string key){
    return ((m_hash(key) % m_currentCap) + (i * i)) % m_currentCap; 
}

//helper for double hashinh probing
int VDetect::doubleHashHelper(int i, string key){
    return ((m_hash(key) % m_currentCap) + i * (11 - (m_hash(key) % 11))) % m_currentCap; 
}


//This function removes a data point from either the current hash table or the old hash table where the object is stored. 
//In a hash table we do not empty the bucket, we only tag it as deleted. To tag a removed bucket we assign the DELETED object to the bucket.
// The DELETED object is defined in vdetect.h. To find the bucket of the object we should use the proper probing policy for the table.
//After every deletion we need to check for the proper criteria, and if it is required, we need to rehash the entire table incrementally into the current table. 
//The incremental transfer proceeds with 25% of the nodes at a time. 
//Once we transferred 25% of the nodes for the first time, the second 25% will be transferred at the next operation (insertion or removal). 
//Once all data is transferred to the new table, the old table will be removed, and its memory will be deallocated.
//If the Virus object is found and is deleted, the function returns true, otherwise it returns false.
bool VDetect::remove(Virus virus){

    int counter = 0;
    bool success = false;
    unsigned int hashFunc = m_hash(virus.getKey()) % m_currentCap;

    // while we haven't iterated through the whole table
    while(counter < m_currentCap) {

        // No probing selected
        if(m_currProbing == NONE) {
            //checks if the virus exists at the index and deletes it
            if(m_currentTable[hashFunc] == virus) {
                m_currentTable[hashFunc] = DELETED;
                m_currNumDeleted++;
                success = true;
            }
                break;
            //}
        }

        // Quadratic probing
        else if(m_currProbing == QUADRATIC) {
            //update it to become quadratic probing
            hashFunc = quadraticHelper(counter, virus.getKey());
            //checks if the virus exists at the index and deletes it
            if(m_currentTable[hashFunc] == virus) {
                m_currentTable[hashFunc] = DELETED;
                m_currNumDeleted++;
                success = true;
                break;
            }
        }

        // Doublehash probing
        else if(m_currProbing == DOUBLEHASH) {
            //update it to become double hash probing
            hashFunc = doubleHashHelper(counter, virus.getKey());
            //checks if the virus exists at the index and deletes it
            if(m_currentTable[hashFunc] == virus) {
                m_currentTable[hashFunc] = DELETED;
                m_currNumDeleted++;
                success = true;
                break;
            }
        }
         counter++;
        }

    //condition to start the rehash where we set everthing to old table
    // deletedRatio is > .8 and we haven't already created the new table

        //cout << deletedRatio() << endl;
        if(deletedRatio() > float(0.8) && m_oldSize == 0) {
            m_oldProbing = m_currProbing;
            m_oldTable = m_currentTable;
            m_oldCap = m_currentCap;
            m_oldNumDeleted = m_currNumDeleted;
            m_oldSize = m_currentSize; 

            //to remove the contents 
            m_currentSize = 0;   
            m_currNumDeleted = 0;
            m_currentCap = findNextPrime(4 * (m_currentSize - m_currNumDeleted));

            //if user chose new policy, set new policy
            if(m_newPolicy != NONE){
                m_currProbing = m_newPolicy;
                m_newPolicy = NONE;
            }

            //create new table with new cap
            m_currentTable = new Virus[m_currentCap]; 
            for(int i = 0; i < m_currentCap; i++){
                m_currentTable[i] = EMPTY;
            }  
        }

        //there are viruses left in the old table
        if(m_oldSize != 0) {

            int transfer = m_oldSize *.25;
            int moved = 0;
            int counter = 0;

            //while there still are 25% of viruses to transfer
            while(counter < m_oldCap && moved < transfer){

                //the entry is not deleted or empty, we insert entry into new table
                if(!(m_oldTable[counter] == DELETED || m_oldTable[counter] == EMPTY)){
                    
                    //while we haven't found an empty spot to transfer virus to
                    hashingHelper(m_oldTable[counter]); 

                    //remove(m_oldTable[counter]);
                    m_oldTable[counter] = DELETED;
                    m_oldNumDeleted++;
                    moved++;
                    //m_currentSize++;

                }
               
                counter++;
            }

            //reached the end of the table, delete old data
            if(counter == m_oldSize){

                delete[] m_oldTable;
                m_oldTable = nullptr;
                m_oldProbing = NONE;
                m_oldCap = 0; 
                m_oldNumDeleted = 0;
                m_oldSize = 0;

            }
        }

        return success;
}

//This function looks for the Virus object with key and id in the hash table, 
//if the object is found the function returns it, 
//otherwise the function returns empty object. 
//If there are two hash tables at the time, the function needs to look into both tables.
Virus VDetect::getVirus(string key, int id) const{
    
    int index = 0;
    int oldIndex = 0;

    //loops till the end
    for (int i = 0; i < m_currentCap; i++) {

        //checks the probing
        if(m_currProbing == QUADRATIC) {
            index = ((m_hash(key) % m_currentCap) + (i * i)) % m_currentCap; 
            if(m_oldSize != 0){
                //index for the old table
                oldIndex = ((m_hash(key) % m_oldCap) + (i * i)) % m_oldCap; 
                //if the key and id matches then it return the object
                if(m_oldTable[oldIndex].getKey() == key && m_oldTable[oldIndex].getID() == id){
                    return m_oldTable[oldIndex];
                } 
            }
            //looks for it in the current table
            if(m_currentTable[index].getKey() == key && m_currentTable[index].getID() == id){
                //returns the virus
                return m_currentTable[index];
            }

        }
        else if(m_currProbing == DOUBLEHASH) {
            //gets the index for the current table
            index = ((m_hash(key) % m_currentCap) + i * (11 - (m_hash(key) % 11))) % m_currentCap;
            
            if(m_oldSize != 0){
                oldIndex = ((m_hash(key) % m_oldCap) + i * (11 - (m_hash(key) % 11))) % m_oldCap;
                //if the key and id matches then it return the object
                if(m_oldTable[oldIndex].getKey() == key && m_oldTable[oldIndex].getID() == id){
                    return m_oldTable[oldIndex];
                }
            }

            //looks for the index in the current table
            if(m_currentTable[index].getKey() == key && m_currentTable[index].getID() == id){
                //returns it
                return m_currentTable[index];
            }
        }

        else if(m_currProbing == NONE) {
            index = (m_hash(key)) % m_currentCap;
            
            if(m_oldSize != 0){
                oldIndex = (m_hash(key)) % m_oldCap;
                if( m_oldTable[oldIndex].getKey() == key && m_oldTable[oldIndex].getID() == id){
                    return m_oldTable[oldIndex];
                }
            }

            if(m_currentTable[index].getKey() == key && m_currentTable[index].getID() == id){
                return m_currentTable[index];
            }
        } 
    }
    //otherwise it returns an empty object
    return EMPTY;
}


//This function returns the load factor of the current hash table. 
//The load factor is the ratio of occupied buckets to the table capacity. 
//the number of occupied buckets is the total of available buckets and deleted buckets. 
//An occupied bucket is a bucket which can contain either a live data node (available to be used) or a deleted node.
float VDetect::lambda() const {

    float lambda = float(m_currentSize) / float(m_currentCap); 
    return lambda;  
}

//This function returns the ratio of the deleted buckets to the total number of occupied buckets .
float VDetect::deletedRatio() const {
    return float(m_currNumDeleted) / float(m_currentSize);
}

void VDetect::dump() const {
    cout << "Dump for the current table: " << endl;
    if (m_currentTable != nullptr)
        for (int i = 0; i < m_currentCap; i++) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    cout << "Dump for the old table: " << endl;
    if (m_oldTable != nullptr) {
        for (int i = 0; i < m_oldCap; i++) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
    }
    
}

bool VDetect::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

//This function returns the smallest prime number greater than the argument "current". 
//If "current" is less than or equal to MINPRIME, the function returns MINPRIME. 
//If "current" is greater than or equal to MAXPRIME, the function returns MAXPRIME. 
//In a hash table we'd like to use a table with prime size. 
//Then, every time we need to determine the size for a new table we use this function. 
int VDetect::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}

ostream& operator<<(ostream& sout, const Virus &virus ) {
    if (!virus.m_key.empty())
        sout << virus.m_key << " (ID " << virus.m_id << ")";
    else
        sout << "";
  return sout;
}

bool operator==(const Virus& lhs, const Virus& rhs){
    return ((lhs.m_key == rhs.m_key) && (lhs.m_id == rhs.m_id));
}
