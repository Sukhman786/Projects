#include<iostream>
#include<windows.h>
#include<mmsystem.h>
#include<sstream>
#include<array>
#include<fstream>
#include<cstdlib>
#include<string>
using namespace std;

// Using structure for making Linked List and Stack
struct Node{
    int data;
    Node* next;
    Node* prev;
};

// Stacks Operations.......
// Search Function of stacks
void Search(Node* top){
    if(top == NULL){
        cout << "Stack is empty!\n";
        cin.ignore();
        cin.get();
        return;
    }

    while(1){
        int find,i=1;
        bool flag = false;

        cout<<endl<<"\033[0m";

        Node* temp = top;

        cout<<"\033[1;37mTop";

            while(temp!=NULL){
                cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
                temp = temp->next;
            }
        cout<<endl<<endl;

        cout<<"\033[1;35m";

        cout<<endl<<"Enter an element to search whether the element is present or not in the given list :- ";
        cin>>find;

        cout<<endl;

        cout<<endl<<"\033[0m";

        temp = top;

        while(temp!=NULL){
            if(temp->data==find){
                cout<<"Element "<<find<<" found at position "<<i<<endl;
                flag = true;
            }
            temp = temp->next;
            i++;
        }

        if(flag==false) cout<<"Element "<<find<<" not present in the given list"<<endl;        

        cout<<"\033[1;35m";

        char x;
        cout<<endl<<"If you want to search for another element, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
      
    }
}

// Remove Function (from ending) of stacks
void Removeend(Node* &top){
    while(1){

        if(top == NULL){
            cout << "Stack is empty!\n";
            cin.ignore();
            cin.get();
            return;
        }

        cout<<endl<<"\033[0m";

        Node* temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl;
        
        temp =top;;

        if(top->next == NULL) {
            delete top;
            top = NULL;
            return;
        }

        else{
            temp = top;

            while(temp->next->next != NULL){
                temp = temp->next;
            }
            
            delete temp->next;
            temp->next = NULL;

        }

        cout<<endl<<"\033[1;32mElement has been Removed from Ending"<<endl<<endl<<"\033[0m";

        temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl<<"\033[1;34m";

        char x;
        cout<<endl<<"If you want to delete another element from ending, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Remove Function (from beginning) of stacks
void Removebeg(Node* &top){
    while(1){

        if(top == NULL){
            cout << "Stack is empty!\n";
            cin.ignore();
            cin.get();
            return;
        }

        cout<<endl<<"\033[0m";

        Node* temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl;

        temp = top;

        Node* z = top;
        top = temp->next;
        delete z;

        cout<<endl<<"\033[1;32mElement has been Removed from beginning"<<endl<<endl<<"\033[0m";

        temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<"\033[1;34m";

        char x;
        cout<<endl<<"If you want to delete another element from ending, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Main remove Function of stacks
void Remove(Node* &top){
    while(1){

        if(top == NULL){
            cout << "Stack is empty!\n";
            cin.ignore();
            cin.get();
            return;
        }

        cout<<endl<<"\033[0m";

        Node* temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl;
        location3:

        int loc,i=0;
        cout<<endl<<"\033[1;34mEnter location of the value you want to delete from the list :- ";
        cin>>loc;

        temp = top;

        while(temp!=NULL){
            temp = temp->next;
            i++;
        }

        if(loc<1 || loc>i){
            cout<<"\n\033[0mInvalid Location\n\n\033[1;34mAgain, ";
            goto location3;
        }

        temp = top;
        i=1;

        if(loc==1){
            Node* x = top;
            top = temp->next;
            delete x;
        }

        else{
            while(i<loc-1 && temp!=NULL){
                temp = temp->next;
                i++;
            }
            
            if(temp!=NULL && temp->next!=NULL){
                Node* x = temp->next;
                temp->next = temp->next->next;
                delete x;
            }
            
        }

        cout<<endl<<"\033[0m";

        temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
                cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
                temp = temp->next;
        }

        cout<<endl<<"\033[1;34m";

        
        char x;
        cout<<endl<<"If you want to delete another element, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Insert Function (from ending) of stacks
void Insertend(Node* &top){
    while(1){
    
        cout<<endl<<"\033[0m";

        Node* temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl<<"\033[1;31m";

        int value;
        cout<<endl<<"Enter value to insert at ending :- ";
        cin>>value;

        cout<<endl;

        Node* newnode = new Node{value,NULL};

        if(top == NULL){
            top = newnode;
        }
        
        else{
            temp = top;

            while(temp->next != NULL){
                temp = temp->next;
            }

            temp->next = newnode;
        }

        cout<<endl<<"\033[0m";

        temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl<<"\033[1;31m";
    
        char x;
        cout<<endl<<"If you want to insert another element at ending, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Insert Function (from beginning) of stacks
void Insertbeg(Node* &top){
    while(1){
    
        cout<<endl<<"\033[0m";

        Node* temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl<<"\033[1;31m";

        int value;
        cout<<endl<<"Enter value to insert at beginning :- ";
        cin>>value;

        cout<<endl;

        Node* newnode = new Node{value,NULL};
        newnode->next = top;
        top = newnode;

        cout<<endl<<"\033[0m";

        temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl<<"\033[1;31m";
    
        char x;
        cout<<endl<<"If you want to insert another element at beginning, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Main insert Function of stacks
void Insert(Node* &top){
    while(1){
    
        cout<<endl<<"\033[0m";

        Node* temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl<<"\033[1;31m";

        int value;
        cout<<endl<<"Enter value to insert at your favourite location :- ";
        cin>>value;

        cout<<endl;

        location4:

        int loc,i=1;
        cout<<endl<<"Enter loaction at which do you want to insert "<<value<<" :- ";
        cin>>loc;

        Node* newnode = new Node{value,NULL};

        temp = top;

        while(temp!=NULL){
            temp = temp->next;
            i++;
        }

        if(loc<1 || loc>i){
            cout<<"\n\033[0mInvalid Location\n\n\033[1;31mAgain, ";
            goto location4;
        }

        temp = top;
        i=1;

        if(loc==1){
            newnode->next = top;
            top = newnode;
        }

        else{
        
            while(i<loc-1 && temp!=NULL){
                temp = temp->next;
                i++;
            }

        newnode->next = temp->next;
        temp->next = newnode;
        }

        cout<<endl<<"\033[0m";

        temp = top;

        cout<<"\033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl<<"\033[1;31m"; 
    
        char x;
        cout<<endl<<"If you want to insert another element, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Display Function (all nodes) of stacks
void Display(Node* top){
    if(top == NULL){
        cout << "Stack is empty!\n";
        cin.ignore();
        cin.get();
        return;
    }

    cout<<endl<<"\033[1;32mFull Stack is displayed below :\n\n";

    cout<<endl<<"\033[0m";

    Node* temp = top;

    cout<<"\033[1;37mTop";

    while(temp!=NULL){
        cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
        temp = temp->next;
    }

    cout<<endl<<endl<<"\033[1;32mPress Enter to Continue.......\n";
    cin.ignore();
    cin.get();
}

// --- DOUBLY LINKED LIST DECLARATIONS ---
void insertbegDLL(Node* &head){

}

void insertendDLL(Node* &head){

}

void insertDLL(Node* &head){

}

void removebegDLL(Node* &head){

}

void removeendDLL(Node* &head){

}

void removeDLL(Node* &head){

}

void searchDLL(Node* head){

}

void displayDLL(Node* head){

}

// --- CIRCULAR SINGLY LINKED LIST DECLARATIONS ---
void insertbegCSLL(Node* &head){

}

void insertendCSLL(Node* &head){

}

void insertCSLL(Node* &head){

}

void removebegCSLL(Node* &head){

}

void removeendCSLL(Node* &head){

}

void removeCSLL(Node* &head){

}
void searchCSLL(Node* head);
void displayCSLL(Node* head);

// Linked List Operations.......
// Search Function of Linked List
void search(Node* head){
    if(head == NULL){
        cout << "List is empty!\n";
        cin.ignore();
        cin.get();
        return;
    }
    
    while(1){
        int find,i=1;
        bool flag = false;

        cout<<endl<<"\033[0m";

        Node* temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }
        cout<<"null"<<endl<<endl;

        cout<<"\033[1;35m";

        cout<<endl<<"Enter an element to search whether the element is present or not in the given list :- ";
        cin>>find;

        cout<<endl;

        cout<<endl<<"\033[0m";

        temp = head;

        while(temp!=NULL){
            if(temp->data==find){
                cout<<"Element "<<find<<" found at position "<<i<<endl;
                flag = true;
            }
            temp = temp->next;
            i++;
        }

        if(flag==false) cout<<"Element "<<find<<" not present in the given list"<<endl;

        cout<<"\033[1;35m";

        char x;
        cout<<endl<<"If you want to search for another element, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
      
    }
}

// Remove Function (from ending) of Linked List
void removeend(Node* &head){
    while(1){

        if(head == NULL){
            cout << "List is empty!\n";
            cin.ignore();
            cin.get();
            return;
        }

        cout<<endl<<"\033[0m";

        Node* temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<endl;
        
        temp = head;

        if (head->next == NULL) {
            delete head;
            head = NULL;
            return;
        }

        else{
            temp = head;

            while(temp->next->next != NULL){
                temp = temp->next;
            }
            
            delete temp->next;
            temp->next = NULL;

        }

        cout<<endl<<"\033[1;32mElement has been Removed from Ending"<<endl<<endl<<"\033[0m";

        temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<"\033[1;34m";

        char x;
        cout<<endl<<"If you want to delete another element from ending, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Remove Function (from beginning) of Linked List
void removebeg(Node* &head){
    while(1){

        if(head == NULL){
            cout << "List is empty!\n";
            cin.ignore();
            cin.get();
            return;
        }

        cout<<endl<<"\033[0m";

        Node* temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<endl;

        temp = head;

        Node* z = head;
        head = temp->next;
        delete z;

        cout<<endl<<"\033[1;32mElement has been Removed from beginning"<<endl<<endl<<"\033[0m";

        temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<"\033[1;34m";

        char x;
        cout<<endl<<"If you want to delete another element from ending, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Main remove Function of Linked List
void remove(Node* &head){
    while(1){

        if(head == NULL){
            cout << "List is empty!\n";
            cin.ignore();
            cin.get();
            return;
        }

        cout<<endl<<"\033[0m";

        Node* temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<endl;

        location:
        
        int loc,i=0;
        cout<<"\033[1;34mEnter location of the value you want to delete from the list :- ";
        cin>>loc;

        temp = head;

        while(temp!=NULL){
            temp = temp->next;
            i++;
        }

        if(loc<1 || loc>i){
            cout<<"\n\033[0mInvalid Location\n\n\033[1;34mAgain, ";
            goto location;
        }

        temp = head;
        i=1;

        if(loc==1){
            Node* x = head;
            head = temp->next;
            delete x;
        }

        else{
            while(i<loc-1 && temp!=NULL){
                temp = temp->next;
                i++;
            }

            if(temp!=NULL && temp->next!=NULL){
                Node* x = temp->next;
                temp->next = temp->next->next;
                delete x;
            }
        }

        cout<<endl<<"\033[0m";

        temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<"\033[1;34m";

        char x;
        cout<<endl<<"If you want to delete another element, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }   
 
}

// Insert Function (from ending) of Linked List
void insertend(Node* &head){
    while(1){
    
        cout<<endl<<"\033[0m";

        Node* temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<"\033[1;31m";

        int value;
        cout<<endl<<"Enter value to insert at ending :- ";
        cin>>value;

        cout<<endl;

        Node* newnode = new Node{value,NULL};

        if(head == NULL){
            head = newnode;
        }
        else{
            temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newnode;
        }

        cout<<endl<<"\033[0m";

        temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<endl<<"\033[1;31m";
    
        char x;
        cout<<endl<<"If you want to insert another element at ending, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Insert Function (from beginning) of Linked List
void insertbeg(Node* &head){
    while(1){

        cout<<endl<<"\033[0m";

        Node* temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<"\033[1;31m";

        int value;
        cout<<endl<<"Enter value to insert at beginning :- ";
        cin>>value;

        cout<<endl;

        Node* newnode = new Node{value,NULL};
        newnode->next = head;
        head = newnode;

        cout<<endl<<"\033[0m";

        temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<endl<<"\033[1;31m";
    
        char x;
        cout<<endl<<"If you want to insert another element at beginning, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Main insert Function of Linked List
void insert(Node* &head){
    while(1){
    
        cout<<endl<<"\033[0m";

        Node* temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<"\033[1;31m";

        int value;
        cout<<endl<<"Enter value to insert at your favourite location :- ";
        cin>>value;

        cout<<endl;

        location2:

        int loc,i=1;
        cout<<"Enter loaction at which do you want to insert "<<value<<" :- ";
        cin>>loc;

        Node* newnode = new Node{value,NULL};

        temp = head;

        while(temp!=NULL){
            temp = temp->next;
            i++;
        }

        if(loc<1 || loc>i){
            cout<<"\n\033[0mInvalid Location\n\n\033[1;31mAgain, ";
            goto location2;
        }

        temp = head;
        i=1;

        if(loc==1){
            newnode->next = head;
            head = newnode;
        }

        else{
        
            while(i<loc-1 && temp!=NULL){
                temp = temp->next;
                i++;
            }

        newnode->next = temp->next;
        temp->next = newnode;
        }

        cout<<endl<<"\033[0m";

        temp = head;

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<endl<<"\033[1;31m";
    
        char x;
        cout<<endl<<"If you want to insert another element, then type '1' otherwise press any key :- ";
        cin>>x;

        cout<<endl;

        if(x!='1'){
            
            return;
        }
    }
}

// Display Function (all nodes) of Linked List
void display(Node* head){
    if(head == NULL){
        cout << "List is empty!\n";
        cin.ignore();
        cin.get();
        return;
    }

    cout<<endl<<"\033[1;32mFull Linked List is displayed below :\n\n";

    cout<<endl<<"\033[0m";

    Node* temp = head;

    while(temp!=NULL){
        cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
        temp = temp->next;
    }

    cout<<"null"<<endl;

    cout<<endl<<"\033[1;32mPress Enter to Continue.......\n";
    cin.ignore();
    cin.get();
}

void Circular_LinkedList(){
    Node* node1 = new Node{10, NULL, NULL};
    Node* head = node1;

    Node* node2 = new Node{20, NULL, NULL};
    node1->next = node2;

    Node* node3 = new Node{30, NULL, NULL};
    node2->next = node3;
    node3->next = head; // Make it circular
    
    while(1){
        system("CLS");

        Node* temp = head;

        cout<<endl<<"\033[1;91mCircular Linked List : \033[1;36mHEAD -> ";

        if (head != NULL) {
            do {
                cout<<"\033[1;37m"<<temp->data<<"\033[1;36m -> \033[1;37m";
                temp = temp->next;
            } while (temp != head);
        }
        
        cout<<"(Loop to HEAD)\033[0m"<<endl<<endl;

        cout<<"\033[1;33m";

        char x;
        cout<<"Type : \n1 -> Inserting an element to the list\n";
        cout<<"2 -> Deleting an element from the list\n";
        cout<<"3 -> Searching an element from the list\n";
        cout<<"4 -> Displaying all Elements of the List\nAny Key -> exit\n\nHERE :- ";
        cin>>x;

        cout<<endl;

        if(x == '1'){
            cout<<"\033[1;32m";
            cout<<"\n1 -> Inserting an element at the Beginning of the list\n";
            cout<<"2 -> Inserting an element at the ending of the list\n";
            cout<<"3 -> Inserting an element at your favourite location of the list\nAny Key -> exit\n\nHERE :- ";
            cin>>x;

            cout<<endl;

            if(x == '1') insertbegCSLL(head); 
            else if(x == '2') insertendCSLL(head);
            else if(x == '3') insertCSLL(head);
            else continue;
        }

        else if(x == '2'){
            cout<<"\033[1;32m";
            cout<<"\n1 -> Deleting an element at the Beginning of the list\n";
            cout<<"2 -> Deleting an element at the ending of the list\n";
            cout<<"3 -> Deleting an element at your favourite location of the list\nAny Key -> exit\n\nHERE :- ";
            cin>>x;

            cout<<endl;

            if(x == '1') removebegCSLL(head);
            else if(x == '2') removeendCSLL(head);
            else if(x == '3') removeCSLL(head);
            else continue;
        }

        else if(x == '3') searchCSLL(head);
        else if(x == '4') displayCSLL(head);
        else break;

    }
}

void Doubly_LinkedList(){
    Node* node1 = new Node{10, NULL, NULL};
    Node* head = node1;

    Node* node2 = new Node{20, NULL, node1};
    node1->next = node2;

    Node* node3 = new Node{30, NULL, node2};
    node2->next = node3;
    
    while(1){
        system("CLS");

        Node* temp = head;

        cout<<endl<<"\033[1;91mDoubly Linked List : \033[1;36mNULL <-> ";

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;36m <-> \033[1;37m";
            temp = temp->next;
        }

        cout<<"NULL\033[0m"<<endl<<endl;

        cout<<"\033[1;33m";

        char x;
        cout<<"Type : \n1 -> Inserting an element to the list\n";
        cout<<"2 -> Deleting an element from the list\n";
        cout<<"3 -> Searching an element from the list\n";
        cout<<"4 -> Displaying all Elements of the List\nAny Key -> exit\n\nHERE :- ";
        cin>>x;

        cout<<endl;

        if(x == '1'){
            cout<<"\033[1;32m";
            cout<<"\n1 -> Inserting an element at the Beginning of the list\n";
            cout<<"2 -> Inserting an element at the ending of the list\n";
            cout<<"3 -> Inserting an element at your favourite location of the list\nAny Key -> exit\n\nHERE :- ";
            cin>>x;

            cout<<endl;

            if(x == '1') insertbegDLL(head); 
            else if(x == '2') insertendDLL(head);
            else if(x == '3') insertDLL(head);
            else continue;
        }

        else if(x == '2'){
            cout<<"\033[1;32m";
            cout<<"\n1 -> Deleting an element at the Beginning of the list\n";
            cout<<"2 -> Deleting an element at the ending of the list\n";
            cout<<"3 -> Deleting an element at your favourite location of the list\nAny Key -> exit\n\nHERE :- ";
            cin>>x;

            cout<<endl;

            if(x == '1') removebegDLL(head);
            else if(x == '2') removeendDLL(head);
            else if(x == '3') removeDLL(head);
            else continue;
        }

        else if(x == '3') searchDLL(head);
        else if(x == '4') displayDLL(head);
        else break;

    }
}

void Singly_LinkedList(){
    Node* node1 = new Node{10,NULL};
    Node* head = node1;

    Node* node2 = new Node{20,NULL};
    node1->next = node2;

    Node* node3 = new Node{30,NULL};
    node2->next = node3;
    
    while(1){
        system("CLS");

        Node* temp = head;

        cout<<endl<<"\033[1;91mLinked List : ";

        while(temp!=NULL){
            cout<<"\033[1;37m"<<temp->data<<"\033[1;32m -> \033[1;37m";
            temp = temp->next;
        }

        cout<<"null"<<endl<<endl;

        cout<<"\033[1;33m";

        char x;
        cout<<"Type : \n1 -> Inserting an element to the list\n";
        cout<<"2 -> Deleting an element from the list\n";
        cout<<"3 -> Searching an element from the list\n";
        cout<<"4 -> Displaying all Elements of the Stack\nAny Key -> exit\n\nHERE :- ";
        cin>>x;

        cout<<endl;

        if(x == '1'){
            cout<<"\033[1;32m";
            cout<<"\n1 -> Inserting an element at the Beginning of the list\n";
            cout<<"2 -> Inserting an element at the ending of the list\n";
            cout<<"3 -> Inserting an element at your favourite location of the list\nAny Key -> exit\n\nHERE :- ";
            cin>>x;

            cout<<endl;

            if(x == '1') insertbeg(head);
            else if(x == '2') insertend(head);
            else if(x == '3') insert(head);
            else continue;
        }

        else if(x == '2'){
            cout<<"\033[1;32m";
            cout<<"\n1 -> Deleting an element at the Beginning of the list\n";
            cout<<"2 -> Deleting an element at the ending of the list\n";
            cout<<"3 -> Deleting an element at your favourite location of the list\nAny Key -> exit\n\nHERE :- ";
            cin>>x;

            cout<<endl;

            if(x == '1') removebeg(head);
            else if(x == '2') removeend(head);
            else if(x == '3') remove(head);
            else continue;
        }

        else if(x == '3') search(head);
        else if(x == '4') display(head);
        else break;

    }
}

void LinkedList_Menu(){
    while(1){
        system("CLS");

        cout<<"\t\t\t\t\t\033[0m";

        for(int i=1; i<=80; i++){
            cout<<"*";
        }

        cout<<"\033[1;36m\n";

        char x;

        cout<<"\t\t\t\t\t\t\t\tTYPES OF LINKED LIST : \n\n";

        cout<<"\t\t\t\t\t\033[0m";

        for(int i=1; i<=80; i++){
            cout<<"*";
        }

        // Choose One data structure from menu
        cout<<"\n\n\033[1;36m1 -> Singly Linked List Operations\n";
        cout<<"2 -> Doubly Linked List Operations\n";
        cout<<"2 -> Circular Linked list Operations\n";
        cout<<"\nAny Key -> exit\n\nHERE :- ";
        cin>>x;

        cout<<endl;

        if(x == '1') Singly_LinkedList();
        else if(x == '2') Doubly_LinkedList();
        else if(x == '3') Circular_LinkedList();
        else break;
    }
}

void Stack_Menu(){
    Node* n1 = new Node{10,NULL};
    Node* n2 = new Node{20,n1};
    Node* n3 = new Node{30,n2};

    Node* top = n3;

    cout<<endl<<"\033[0m";

    while(1){

        system("CLS");

        Node* temp = top;

        cout<<"\033[1;91mStack : \033[1;37mTop";

        while(temp!=NULL){
            cout<<"\033[1;32m <- \033[1;37m"<<temp->data;
            temp = temp->next;
        }

        cout<<endl<<endl;

        cout<<"\033[1;33m";

        char x;

        cout<<"Type : \n1 -> Inserting an element to the Stack\n";
        cout<<"2 -> Deleting an element from the Stack\n";
        cout<<"3 -> Searching an element from the Stack\n";
        cout<<"4 -> Displaying all Elements of the Stack\nAny Key -> exit\n\nHERE :- ";
        cin>>x;

        cout<<endl;

        if(x == '1'){
            cout<<"\033[1;32m";
            cout<<"\n1 -> Inserting an element at the Beginning of the Stack\n";
            cout<<"2 -> Inserting an element at the ending of the Stack\n";
            cout<<"3 -> Inserting an element at your favourite location of the Stack\nAny Key -> exit\n\nHERE :- ";
            cin>>x;

            cout<<endl;

            if(x == '1') Insertbeg(top);
            else if(x == '2') Insertend(top);
            else if(x == '3') Insert(top);
            else continue;
        }

        else if(x == '2'){
            cout<<"\033[1;32m";
            cout<<"1 -> Deleting an element at the Beginning of the Stack\n";
            cout<<"2 -> Deleting an element at the ending of the Stack\n";
            cout<<"3 -> Deleting an element at your favourite location of the Stack\nAny Key -> exit\n\nHERE :- ";
            cin>>x;

            cout<<endl;

            if(x == '1') Removebeg(top);
            else if(x == '2') Removeend(top);
            else if(x == '3') Remove(top);
            else continue;
        }

        else if(x == '3') Search(top);
        else if(x == '4') Display(top);
        else break;

    }
            
}

// Menu Function
void menu(){
    while(1){
        system("CLS");

        cout<<"\t\t\t\t\t\033[0m";

        for(int i=1; i<=80; i++){
            cout<<"*";
        }

        cout<<"\033[1;36m\n";

        char x;

        cout<<"\t\t\t\t\t\t\t\tTYPE, WHAT DO YOU WANT TO DO : \n\n";

        cout<<"\t\t\t\t\t\033[0m";

        for(int i=1; i<=80; i++){
            cout<<"*";
        }

        // Choose One data structure from menu
        cout<<"\n\n\033[1;36m1 -> Linked List Operations\n";
        cout<<"2 -> Stack Operations\n";
        cout<<"\nAny Key -> exit\n\nHERE :- ";
        cin>>x;

        cout<<endl;

        // Calling Linked List operations
        if(x=='1') LinkedList_Menu();
        
        // Calling Stacks Operations
        else if(x == '2') Stack_Menu();
        // Exiting menu function and Ending the program
        else return;
    }
}

// Error handling function for playing music
void printMciError(DWORD error) {
    char errorText[256];
    mciGetErrorStringA(error, errorText, sizeof(errorText));
    cout << "MCI Error: " << errorText << endl;
}

// Music Playing function
void playmusic(){
    string filename = "Akaza_music.mp3";
    string openCommand = "open \"" + filename + "\" type mpegvideo alias myMusic";
    DWORD openError = mciSendStringA(openCommand.c_str(), NULL, 0, NULL);

    if (openError != 0) {
        cout << "Failed to open music file. Make sure '" << filename << "' is in the same folder." << endl;
    } else {
        DWORD playError = mciSendStringA("play myMusic repeat", NULL, 0, NULL);
        if (playError != 0) {
            cout << "Failed to play music." << endl;
            cin.get();
            printMciError(playError);
            mciSendStringA("close myMusic", NULL, 0, NULL);
        }
    }
}

// Making text bigger using figlet
string runFiglet(const string &text) {
    string command = "figlet \"" + text + "\"";
    array<char, 256> buffer{};
    string result;
    FILE *pipe = _popen(command.c_str(), "r");
    if (!pipe) return "Error running figlet!";
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
        result += buffer.data();
    _pclose(pipe);
    return result;
}

// Welcome screen Interface
void welcome(){
    system("CLS");

    int width = 160; // Width of terminal screen
    string border(width, '*'); // String of width's size contains '*'
    string emptyLine = "*" + string(width - 2, ' ') + "*"; // Empty line with side borders

    string subtitle = "Fast - Reliable - Efficient";
    string info1 = "Play with Linked List and Stacks";
    string info2 = "Traverse, Insert, Delete, Search and Display";

    // Run Figlet for the big title
    string titleFiglet = runFiglet("DS Project");

    // Print top border
    cout << "\033[1;33m" << border << "\033[0m" << endl; // Yellow border

    // Empty spacing lines
    for (int i = 0; i < 11; i++) cout << "\033[1;33m" << emptyLine << endl;

    // Print the Figlet title
    stringstream ss(titleFiglet);
    string line;
    while (getline(ss, line)) {
        int pad = (width - 2 - line.length()) / 2;
        if (pad < 0) pad = 0;
        cout << "\033[1;33m*" << string(pad, ' ') << "\033[1;33m" << line << string(width - 2 - pad - line.length(), ' ') << "\033[1;33m*\033[0m" << endl;
    }

    // One Empty Spacing line
    cout << "\033[1;33m" << emptyLine << endl;

    // center normal text
    auto printCentered = [width](string text, string colorCode = "\033[1;37m") {
        int padding = (width - 2 - text.length()) / 2;
        if (padding < 0) padding = 0;
        cout << "\033[1;33m*" << string(padding, ' ') << colorCode << text << string(width - 2 - padding - text.length(), ' ') << "\033[1;33m*\033[0m" << endl;
    };

    printCentered(subtitle, "\033[1;91m");
    printCentered(info1, "\033[1;92m");
    printCentered(info2, "\033[1;36m");

    string textVisible = "Developed by Sukhman";
    int padding = (width - 2 - textVisible.length()) / 2;
    if (padding < 0) padding = 0;
    cout << "\033[1;33m*" << string(padding, ' ') << "\033[1;33mDeveloped by \033[1;97mSukhman\033[0m" << string(width - 2 - padding - textVisible.length(), ' ') << "\033[1;33m*" << endl;

    // Empty spacing lines
    for (int i = 0; i < 11; i++) cout << "\033[1;33m" << emptyLine << endl;
    // Print bottom border
    cout << "\033[1;33m" << border << "\033[0m" << endl;

    cout<<"\nPress Enter to Continue.......";
    cin.get();
}

// Main Funcion
int main(){
    system("CLS");

    // Calling background music playing function
    playmusic();

    // Calling welcome screen interface function
    welcome();

    // Calling menu function
    menu();
    return 0;
}