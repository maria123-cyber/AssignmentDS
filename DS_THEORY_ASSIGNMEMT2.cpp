#include <iostream>
#include <string>

using namespace std;

struct Node {
    string page; 
    Node* next;  // pointer that points to the next node
};

struct Stack {
    Node* top; // pointer that points to the top node of the stack
};
// stack for back  and  forward history 
Stack backStack;    
Stack forwardStack; 
string currentPage = "Home"; 

// Function to push a page onto the stack
void push(Stack stack, string page) {
    Node* newNode = new Node; // create new node
    newNode->page = page;     
    newNode->next = stack.top; // new node linked with the current top
    stack.top = newNode;      // update the top pointer to the new node
}

// Function to pop a page from the stack
string pop(Stack stack) {
    if (stack.top == NULL) { 
        cout << "Stack is empty." << endl;
        return ""; 
    }
    Node* temp = stack.top;       // store the current top node
    string poppedPage = temp->page; // page from the top node will be received 
    stack.top = stack.top->next;  
    delete temp;                  // to free the memory
    return poppedPage;            
}

// Function to check if the stack is empty
bool isEmpty(Stack stack) {
    return stack.top == NULL;
}

// Function to visit a new page
void visitPage(string page) {
    if (currentPage != "") {
        push(backStack, currentPage); // push the current page to the back stack
    }
    currentPage = page;

    // clear or delete or pop the forward stack when visiting a new page
    while (forwardStack.top != NULL) {
        pop(forwardStack);
    }

    cout << "Visited: " << currentPage << endl;
}

// Function to go back to the previous page
void goBack() {
    if (backStack.top == NULL) {
        cout << "No pages in the back history." << endl;
    } else {
        push(forwardStack, currentPage); // move current page to forward stack
        currentPage = pop(backStack);     // move the previous page from the back stack
        cout << "Back to: " << currentPage << endl;
    }
}

// Function to go forward to the next page
void goForward() {
    if (forwardStack.top == NULL) {
        cout << "No pages in the forward history." << endl;
    } else {
        push(backStack, currentPage);      // current page to back stack
        currentPage = pop(forwardStack);    // receive the next page from the forward stack
        cout << "Forward to: " << currentPage << endl;
    }
}

// function to show the current page
void showCurrentPage() {
    cout << "Current page: " << currentPage << endl;
}

int main() {
    int choice;
    string page;
    
    backStack.top = NULL;
    forwardStack.top = NULL;

   //loop
    do {
        cout << "\n1. Visit Page\n2. Go Back\n3. Go Forward\n4. Show Current Page\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter page name: ";
                cin >> page;
                
                visitPage(page); 
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                showCurrentPage();
                break;
            case 5:
                cout << "Exiting browser history..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}

