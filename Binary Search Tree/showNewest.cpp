// UMBC - CMSC 341 - Spring 2023 - Proj2
#include "show.h"
Show::Show(){
    m_root = nullptr; 
}

//The destructor performs the required cleanup including memory deallocations and re-initializing.
Show::~Show(){
    clear();
    
}

//This function inserts a Drone object into the tree in the proper position. 
//The Drone::m_id should be used as the key to traverse the Show tree and abide by BST traversal rules. 
//The comparison operators (>, <, ==, !=) work with the int type in C++. 
//A Drone id is a unique number in the range MINID - MAXID. 
//We do not allow a duplicate id or an object with invalid id in the tree.
//Note:
//In the Show tree data structure every node is a Drone object which is represented as a pointer to the Drone object. 
//Therefore, for every insertion we need to allocate memory and use the information of aDrone to initialize the new node. 
//Memory allocation takes place in the Show class.
//After an insertion, we should also update the height of each node on the path traversed down the tree as well as check for an imbalance at each node in this path.
void Show::insert(const Drone& aDrone){

    //checks if the id is in range and then inserts
    if(aDrone.m_id >= MINID && aDrone.m_id <= MAXID) {
        m_root = insert1(aDrone, m_root);
    
    }
    
}

//inserts the nodes
Drone * Show::insert1(const Drone& element, Drone *aDrone) {
    if(aDrone == nullptr){
        //allocates memory if the drone doesnt exsit
        aDrone = new Drone(element);
        //if id is less than the right side then its addded to the left
    } else if(element.m_id < aDrone->m_id) {
        aDrone->m_left = insert1(element, aDrone->m_left); 
        //otherwise to the right
    } else if(element.m_id > aDrone->m_id) {
        aDrone->m_right = insert1(element, aDrone->m_right);
    } 
    //hight is updated
    updateHeight(aDrone);
    //balance function is stored
    aDrone = balanceFunction(aDrone);

    return aDrone;

}

Drone* Show::rotateLeft(Drone* aDrone) {
    //Drone* myDrone = aDrone;
    //function totates to the left is the tree is right heavy
    Drone* dronePtr = aDrone->m_right;
    aDrone->m_right = dronePtr->m_left;
    dronePtr->m_left = aDrone;
    updateHeight(aDrone);
    updateHeight(dronePtr);
    return dronePtr;
}

Drone* Show::rotateRight(Drone* aDrone){
    //Drone* myDrone = aDrone;
    //function totates to the right is the tree is left heavy
    Drone* dronePtr = aDrone->m_left;
    aDrone->m_left = dronePtr->m_right;
    dronePtr->m_right = aDrone;
    updateHeight(aDrone);
    updateHeight(dronePtr);
    return dronePtr;
}

//right heavy you wanna do L or RL
//leavy heavy you wanna do R or LR
Drone* Show::balanceFunction(Drone* aDrone){
    //check the height of aDrone
    int balanceAmount = balanceFactor(aDrone);

    if(aDrone != nullptr){

        //if the function is right heavy
        if(balanceAmount < -1) {
            if( balanceFactor(aDrone->m_right) > 0 ){
                aDrone->m_right = rotateRight(aDrone->m_right);
            } 
            return rotateLeft(aDrone); 
         
        //if the function is left heavy
        } else if (balanceAmount > 1) {
            if(balanceFactor(aDrone->m_left) < 0) {
                aDrone->m_left = rotateLeft(aDrone->m_left); 
            }
            return rotateRight(aDrone);

        }
    }
    
    return aDrone; 

}

//gets the balance factor of the the tree
int Show::balanceFactor(Drone *aDrone){
    if(aDrone == nullptr)
        return -1;
        //none of the children exist
    else if(aDrone->m_left == nullptr && aDrone->m_right == nullptr){
        return 0;
        //left children exist
    } else if(aDrone->m_left != nullptr && aDrone->m_right == nullptr) {
        return aDrone->m_left->m_height + 1; 
        //right children exist
    } else if(aDrone->m_right != nullptr && aDrone->m_left == nullptr) {
        return -1 - aDrone->m_right->m_height;
    }
    //both children exist
    return aDrone->m_left->m_height - aDrone->m_right->m_height;  

}

//this function checks if the tree is an AVL tree
bool Show::balanceBool(Drone *myDrone) {
    if(myDrone == nullptr) return true;
    int balance = balanceFactor(myDrone);
    bool result = true;
    //checks for the balance factor
    if(balance < -1 || balance > 1) {
        result = false;
    }
    //recursive calls
    bool leftChild = balanceBool(myDrone->m_left);
    bool rightChild = balanceBool(myDrone->m_right);
    
    return result && leftChild && rightChild;
    
}


//this function updates the heght of the tree
void Show::updateHeight(Drone *aDrone){
    
    //checks if the drone exists
   if(aDrone != nullptr){
        int left = -1;
        int right = -1;

        if(aDrone->m_left != nullptr)  {
            //stores the height of the left child
            left = aDrone->m_left->m_height;
        }
        if(aDrone->m_right != nullptr) {
            //stores the height of the right child
            right = aDrone->m_right->m_height;
        }

        if(left > right) {
            //if left is bigger then 1 is added
            aDrone->m_height = left + 1; 
        }
        else {
            aDrone->m_height = right + 1; 
        }
    }
  
}




void Show::clearHelper(Drone* &aDrone){
    if(aDrone != nullptr) {
        clearHelper(aDrone->m_left);
        clearHelper(aDrone->m_right);
        delete aDrone;
      //aDrone = nullptr;
    }
    aDrone = nullptr;
}
//The clear function deallocates all memory in the tree and makes it an empty tree.
void Show::clear(){
    clearHelper(m_root);
    
}

//finds the max child on the left side 
Drone* Show::findMax(Drone *aDrone){
    if (aDrone == nullptr || aDrone->m_right == nullptr)
        return aDrone;
    else
        return findMax(aDrone->m_right);

}

Drone* Show::removeHelper(Drone *aDrone, int id){

    if(aDrone != nullptr) {

        if(id < aDrone->m_id) {
            aDrone->setLeft(removeHelper(aDrone->m_left, id));
        }
        //
        else if(id > aDrone->m_id) {
            aDrone->setRight(removeHelper(aDrone->m_right, id));
        }
        //two children
        else if(aDrone->m_left != nullptr && aDrone->m_right != nullptr && id == aDrone->m_id) { 
            Drone* temp = findMax(aDrone->m_left);
            //copies all the other vars
            aDrone->m_id = temp->m_id;
            aDrone->m_state = temp->m_state;
            aDrone->m_type = temp->m_type;
            aDrone->m_left = removeHelper(aDrone->m_left, temp->m_id);
        }
        //one or no children 
        else if (aDrone->m_id == id) {
            if(m_root->m_id == aDrone->m_id) {
                m_root = nullptr; 
            }
            Drone* temp = aDrone;
            if (aDrone->m_left == nullptr)
                aDrone = aDrone->m_right;
            else
                aDrone = aDrone->m_left;
            delete temp;
            }
    updateHeight(aDrone);
    aDrone = balanceFunction(aDrone); 
    }
    return aDrone;

    
}


//The remove function traverses the tree to find a node with the id and removes it from the tree.
void Show::remove(int id){

    if(findDrone(id)) {
       m_root = removeHelper(m_root, id);
    }    else {
        return; 
    }

    
}

//This function prints a list of all drones in the tree to the standard output in the ascending order of IDs. 
//The information for every Drone object will be printed in a new line. 
//For the format of output please refer to the sample output file, i.e. driver.txt.
void Show::listDrones() const {
    //19224:LIGHTON:RED
    listDroneHelper(m_root);
} 

//helper function prints the list in ascending order of IDs
void Show::listDroneHelper(Drone* myDrone) const{

    if(myDrone != nullptr) {
        listDroneHelper(myDrone->m_left);
        cout << myDrone->m_id << ":" << myDrone->getStateStr() << ":" << myDrone->getTypeStr() << endl;
        listDroneHelper(myDrone->m_right);

    }

}



//This function finds the node with id in the tree and sets its Drone::m_state member variable to state. 
//If the operation is successful, the function returns true otherwise it returns false. 
//For example, when the drone with id does not exist in the tree the function returns false.
bool Show::setState(int id, STATE state){
    Drone *newDrone = findHelper(m_root, id);
    if(newDrone != nullptr) {
        newDrone->setState(state); 
        return true; 
    }
    return false; 
}

//helper function to remove the drones with the state light off
Drone* Show::removeLightsHelper(Drone *aDrone) {

    if(aDrone == nullptr) return aDrone; 
    if(aDrone != nullptr) {
        //recursive calls
        aDrone->m_left = removeLightsHelper(aDrone->m_left);
        aDrone->m_right = removeLightsHelper(aDrone->m_right);
        if(aDrone->m_state == LIGHTOFF) { 
            //calls the remove helper
            aDrone = removeHelper(aDrone, aDrone->m_id); 
                   
        } 

    }
    return aDrone;
}
       

//This function traverses the tree, finds all drones with LIGHTOFF state and removes them from the tree. 
//The final tree must be a balanced AVL tree.
void Show::removeLightOff(){
    m_root = removeLightsHelper(m_root); 
    
}

//This function returns true if it finds the node with id in the tree, otherwise it returns false.
bool Show::findDrone(int id) const {
    if(findHelper(m_root, id) != nullptr){
        return true;
    }
    return false; 
  
  
}

Drone* Show::findHelper(Drone *aDrone, int id) const{
    if(aDrone == nullptr) {
        return aDrone;
    }

    if(aDrone != nullptr) {
        if(aDrone->m_id == id) {
            return aDrone; 
        }
        //key is smaller therefore you go left
        else if(aDrone->m_id > id) {
            return findHelper(aDrone->m_left, id);   
        }
        //key is greater 
        else if(aDrone->m_id < id) {
            return findHelper(aDrone->m_right, id);      
    }
    }
   //when id doesnt exist
   return aDrone;
     
    
}


//This function overloads the assignment operator for the class Show. It creates an exact deep copy of the rhs.
const Show & Show::operator=(const Show & rhs){
   
   //checks for self assignment
    if(this != &rhs) {
         clear();
         //calls the helper function
         m_root = assignmentHelper(m_root, rhs.m_root);

    }
    return *this;

    
}
Drone* Show::assignmentHelper(Drone *aDrone, const Drone* myDrone){
    if(myDrone == nullptr) {
        return nullptr;
    }
    //allocates memory
    aDrone = new Drone(myDrone->getID(), myDrone->getType(), myDrone->getState()); 
    //recursive calls for the rest of the tree
    aDrone->setLeft(assignmentHelper(aDrone->getLeft(), myDrone->getLeft()));
    aDrone->setRight(assignmentHelper(aDrone->getRight(), myDrone->getRight()));
    return aDrone;
   
}


//this functipm passes a pointer, color, and refernce to the counter from the actual function
int Show::countDronesHelper(Drone *aDrone, LIGHTCOLOR aColor, int &counter) const {
    if(aDrone == nullptr){
        return 0;
    }
    if(aDrone->getType() == aColor) {
        counter++; 
    }
    //recuses through the rest of the tree
    countDronesHelper(aDrone->m_left, aColor, counter);
    countDronesHelper(aDrone->m_right, aColor, counter);
    return counter; 

}

//This function traverses the tree, finds all drones with the color specified by aColor variable 
//and returns the total number of drones of that color in the show.
int Show::countDrones(LIGHTCOLOR aColor) const{
    //passes counter by refernce
    int counter = 0;
    return countDronesHelper(m_root, aColor, counter);
}



void Show::dumpTree() const {dump(m_root);}
void Show::dump(Drone* aDrone) const{
    if (aDrone != nullptr){
        cout << "(";
        dump(aDrone->m_left);//first visit the left child
        cout << aDrone->m_id << ":" << aDrone->m_height;//second visit the node itself
        dump(aDrone->m_right);//third visit the right child
        cout << ")";
    }
}