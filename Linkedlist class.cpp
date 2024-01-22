#include <iostream>
using namespace std;

struct Node {
  
    int value;
    Node * next;
    
    Node (int val, Node * ptr)
      : value(val), next(ptr)
    {};
    
};

class LinkedListSet {
    
    private:
        Node* head;
    
    public:
        LinkedListSet()
          : head(nullptr)
        {};
        // The provided display function is intended to print the contents of the LinkedListSet in a readable format. It iterates through the linked list and prints each element followed by a comma. Finally, it prints a closing brace to denote the end of the set.
        void display(){
            Node * ptr = head;
            cout << "LinkedListSet{";
            while (ptr){
                cout << ptr->value << ", ";
                ptr = ptr->next;
            }
            cout << "}" << endl;
        }
        // The provided code is the destructor for the LinkedListSet class. It is responsible for freeing the memory allocated for the nodes of the linked list when an object of the class is destroyed.
        ~LinkedListSet(){
            
            while (head) {
                Node * ptr = head;
                head = head->next;
                delete ptr;
            }
        }
        // The provided code is an attempt to overload the = operator for the LinkedListSet class, implementing the copy assignment operator. This operator is designed to copy the contents of another LinkedListSet object (copy) to the current object (*this).
        LinkedListSet & operator =(const LinkedListSet & copy) {
            
            while (head) {
                Node * deleted = head;
                head = head->next;
                delete deleted;
            }
            if (copy.head == nullptr)
                head = nullptr;
            else{
                head = new Node(copy.head->value, nullptr); // creating new head
                Node * ptr = copy.head->next, * temp= head;
                
                while(ptr){
                    *this + ptr->value;
                    ptr = ptr->next;
                    
                }
            }
            return *this;
        }
        // The provided code is an attempt to overload the + operator for the LinkedListSet class, specifically for adding a new value to the set. The operator takes an integer value val as an argument and adds that value to the set while maintaining the sorted order.
        LinkedListSet & operator +(int val) {
            
            Node * ptr = head, * prev = nullptr;
            if (head == nullptr || ptr->value > val){
                
                if (head != nullptr)
                    head = new Node(val, ptr); // adding new value to the set by forming new node
                else
                    head = new Node(val, nullptr); // adding new value to the set by forming new node
            }
            else {
                bool flag = true;
                while (ptr != nullptr && ptr->value <= val){
                    
                    if (ptr->value == val)
                        flag = false; // aim of flag is to identify if same value are in the set, if it is, flag is false
                    prev = ptr;
                    ptr = ptr->next;
                }
                if (flag){
                    Node * new_value = new Node(val,ptr); // adding new value to the set by forming new node
                    prev->next = new_value;
                }
            }
            return *this;
        }
        // The provided code is an attempt to overload the - operator for the LinkedListSet class, specifically for removing a specific value from the set. The operator takes an integer value val as an argument and removes the first occurrence of that value from the set.
        LinkedListSet & operator -(int val) {
            
            Node * ptr = head, * prev = head;
            while (ptr != nullptr && ptr->value != val){
                prev = ptr;
                ptr = ptr->next;
            }
            
             // değişcek yer
            if (ptr != nullptr && prev == ptr){
                head = ptr->next;
                delete ptr;}
             //
             
            else if (ptr){
                prev->next = ptr->next;
                delete ptr;
                ptr = nullptr;
            }
            return *this;
        }
        // The provided code appears to be an attempt to overload the += operator for the LinkedListSet class, implementing the set union operation. The += operator is used to find the union of two sets and update the current set (*this) with the result.
        LinkedListSet & operator +=(const LinkedListSet & rhs) {
            
            Node * rhs_ptr = rhs.head, * ptr = head, * prev = nullptr;
            while (rhs_ptr){
                bool flag = true;
                if (ptr && rhs_ptr->value < ptr->value){
                    *this + rhs_ptr->value;
                    ptr = head;
                }
                else{
                    while (ptr != nullptr && rhs_ptr->value >= ptr->value){
                        if (rhs_ptr->value == ptr->value){
                            flag = false; // aim of flag is to identify if same value are in both of the sets
                            break;
                        }
                        prev = ptr;
                        ptr = ptr->next;
                    }
                    if (flag){
                        *this + rhs_ptr->value; // If the value of right set is not in left set, adding it to left set by using + operator
                        ptr = head;
                        if(ptr == nullptr)
                            ptr = prev->next;}
                }
                rhs_ptr = rhs_ptr->next;
            }
            return *this;
        }
        // The aim of the provided code is to overload the -= operator for the LinkedListSet class, implementing the set difference operation. The -= operator is used to find the difference between two sets and update the current set (*this) with the result.
        LinkedListSet & operator -=(const LinkedListSet & rhs) {
            
            Node * rhs_ptr = rhs.head, * ptr = head, * prev = nullptr;
            while (rhs_ptr){
        
                while (ptr && rhs_ptr->value > ptr->value){
                    prev = ptr;
                    ptr = ptr->next;
                }
                if (ptr && rhs_ptr->value == ptr->value){
                    // eklenen kısım
                    if (prev == nullptr){
                        head = ptr->next;
                        delete ptr;
                        ptr = head;
                    } // 3 satır
                    else {
                        *this - rhs_ptr->value; // If the value right set by matching with the value of left set, removing from left set by using - operator
                        ptr = prev->next;}
                }
                rhs_ptr = rhs_ptr->next;
            }
            return *this;
        }
        // The aim of the provided code is to overload the &= operator for the LinkedListSet class, implementing the set intersection operation. The &= operator is used to find the intersection of two sets and update the current set (*this) with the result.
        LinkedListSet & operator &=(const LinkedListSet & rhs) {
            Node *  ptr = head, * rhs_ptr = rhs.head;
            LinkedListSet result;
            while (ptr){
                while (rhs_ptr && ptr->value > rhs_ptr->value){
                    rhs_ptr = rhs_ptr->next;
                }
                if (rhs_ptr && ptr->value == rhs_ptr->value){
                    result + ptr->value;   // If the values of the sets are same, adding the result object by using + operator
                    rhs_ptr = rhs_ptr->next;
                }
                ptr = ptr->next;
            }
            *this = result; // Copying the result object to this by using = operator
            return *this;
        }
};

int main() {

  // Example usage
  LinkedListSet set1;
  set1 + 1 + 2 + 3 + 17; // Insertion
  set1.display();
  
  set1 - 2; // Deletion
  set1.display();
  
  LinkedListSet set2;
  set2 + 3 + 4 + 5;
  set2.display();
  
  set2 += set1 + 7 + 3 + 19; //Insertion with multiple right-hand values
  set2.display();
  
  LinkedListSet set3;
  set3 + 3 + 4 + 7 + 17 + 41;
  set3.display();
  
  LinkedListSet set4;
  set4 + 41 + 37+ 7 + 19 + 41;
  set4.display();
  
  // Set Union
  set1 += set2;
  set1.display();
  
  // Set Difference
  set1 -= set3;
  set1.display();
  
  // Set Intersection
  set1 &= set4;
  set1.display();
  
  return 0;
}
// SULEYMAN BERBER
