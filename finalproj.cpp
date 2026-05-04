#include <iostream>
#include <string>
#include <iomanip>
#include <stack>
#include <queue>


struct Node { // Node declaration
    std::string feeInfo;
    float amount;
    int urgency;
    Node* next;
};

struct feeRecord { // struct used for the stacks
    std::string feeInfo;
    float amount;
    int urgency;
};

struct Compare { // comparator (helper for priority queue)
    bool operator()(Node* a, Node* b) {
        return a->urgency < b->urgency;
    }
};

std::stack<feeRecord> history; // stakcs used for payment history
Node* head = nullptr;

void urgentInMenu (Node* head); // used in printing one of the most urgent fee in the menu
void displayMenu(); // main menu
void addFee(Node*& head); // function used to add fee record
void displayFees(); // used as a connector to print impending fees using 2 methods
void displayByInitialOrder (Node* head); // display fees depending on the order when the fee/s is/are added
void displayByUrgency(Node* head); //display fees based on their urgency using priority queues
void searchFee(Node* head); // function used to search fees by either the fees' description or urgency level
void markAsPaid(Node*& head); // function used to delete fees and marking them as paid, also pushed them to the stacks in order to display or put them in payment history.
void displayHistory(); // function used to access the stack and printing it as the payment history of the user


int main(void) {
    int startChoice;

    std::cout << "===== Welcome to Priority-Based Fees Management System! =====\n";
    std::cout << "1. Start\n";
    std::cout << "2. Exit.\n\n";
    std::cout << "Enter your choice: ";
    std::cin >> startChoice;
    if(startChoice == 1) {
        displayMenu();
    } else {
        std::cout << "Exiting program . . .";
        return 0;
    }

    return 0;
}

void displayMenu() {
    int choice;
    while(true) {
        urgentInMenu(head);
        std::cout << "==========\n";
        std::cout << std::setw(5) << "Main Menu" << std::setw(5) << "\n";
        std::cout << "==========\n";
        std::cout << "1. Add Fee Record\n";
        std::cout << "2. Show Fee Records\n";
        std::cout << "3. Mark Fee As Paid\n";
        std::cout << "4. Search Fee\n";
        std::cout << "5. Display Payment History\n";
        std::cout << "6. Exit";

        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1: addFee(head); break;
            case 2: displayFees(); break;
            case 3: markAsPaid(head); break;
            case 4: searchFee(head); break;
            case 5: displayHistory(); break;
            case 6: std::cout << "Exiting Program . . ."; return;
            default: {
                std::cout << "Invalid input. Please try again.\n";
            }
        }
    }
}

void addFee(Node*& head) {
    std::string feeDesc;
    int urgency;
    float amount;

    while(true){
        std::cout << "Enter fee type: ";
        std::cin.ignore();
        std::getline(std::cin, feeDesc);

        if(feeDesc.empty()) {
            std::cout << "Fee description cannot be empty.\n";
        } else {
            break;
        }
    }

    while(true) {
        std::cout << "Enter amount: ₱";
        std::cin >> amount;

        if(std::cin.fail() || amount <= 0) {
            std::cout << "Invalid amount. Please enter a positive number.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else {
            break;
        }
    }

    while(true){
        std::cout << "Enter the fee urgency (1 - 4): ";
        std::cin >> urgency;

        if(std::cin.fail() || urgency < 1 || urgency > 4) {
            std::cout << "Invalid input. Please enter numbers between 1 - 4 only.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else {
            break;
        }
    }
    Node* newNode = new Node();
    newNode->feeInfo = feeDesc;
    newNode->amount = amount;
    newNode->urgency = urgency;
    newNode->next = nullptr;

    if(head == nullptr) {
        head = newNode;
        return;
    }
    
    Node* temp = head;
    while(temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = newNode;

}

void displayByUrgency (Node* head){
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq; //vector is used by priority queues, it is just shown in the code since we're dealing with nodes instead of data types
    
    Node* temp = head;
    while(temp != nullptr) {
        pq.push(temp);
        temp = temp->next;
    }

    int counter = 1;

    while(!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        std::cout << "Fee #" << counter << ":\n";
        counter++;
        std::cout << "Description: " << current->feeInfo << "\n";
        std::cout << "Amount: " << current->amount << "\n";
        std::cout << "Urgency: " << current->urgency << "\n";
        std::cout << "----------------------------------------\n";    
    }
    
}

void displayByInitialOrder (Node* head){
    Node* temp = head;
    int counter = 1;
    
    if(head == nullptr) {
        std::cout << "No fees available! Good work.\n";
    }
    while(temp != nullptr) {
        std::cout << "Fee #" << counter << '\n';
        counter++;
        std::cout << "Fee Description: " << temp->feeInfo << '\n';
        std::cout << "Amount: ₱" << temp->amount << '\n';
        std::cout << "Urgency Level: " << temp->urgency << '\n';
        std::cout << "----------------------------------------\n";
        temp = temp->next;
    }
}

void displayFees() {
    int choice;

    std::cout << "Choose history display method:\n";
    std::cout << "1. By add order\n";
    std::cout << "2. By urgency level\n\n";

    std::cout << "Enter choice: ";
    std::cin >> choice;

    if(choice == 1) {
        displayByInitialOrder(head);
    } else if (choice == 2) {
        displayByUrgency(head);
    } else {
        std::cout << "Invalid input. Going back to main menu . . .\n";
    }
}

void markAsPaid(Node*& head) {
    if (head == nullptr) {
        std::cout << "No fees to pay! Good work.\n";
        return;
    }

    feeRecord record;
    std::string searcher;
    std::cout << "Enter the fee description of the paid fee: ";
    std::cin.ignore();
    std::getline(std::cin, searcher);


    Node* temp = head;
    Node* prev = nullptr;
    while(temp != nullptr && temp->feeInfo != searcher){
        prev = temp;
        temp = temp->next;
    }

    if(temp == nullptr) {
            std::cout << "Invalid input. Fee does not exist.\n";
            return;
        }

    std::cout << "Fee is now marked as paid.\n";
    record.feeInfo = temp->feeInfo;
    record.amount = temp->amount;
    record.urgency = temp->urgency;

    history.push(record);

    if(prev == nullptr) {
        head = head->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;

}

void displayHistory () {
    if(history.empty()) {
        std::cout << "No payment history available.\n";
        return;
    }

    std::stack<feeRecord> temp = history;

    int counter = 1;
     
    while(!temp.empty()) {
        feeRecord record = temp.top();

        std::cout << "Payment #" << counter << "\n";
        std::cout << "Fee: " << record.feeInfo << "\n";
        std::cout << "Amount: ₱" << record.amount << "\n";
        std::cout << "Urgency: " << record.urgency << "\n";
        std::cout << "---------------------------------------\n";

        temp.pop();
        counter++;
    }
}

void searchFee(Node* head) {
    int choice;
    int searchUrgency;
    std::string searchDesc;
    while(true) {
        std::cout << "Enter the search method you would want to use:\n";
        std::cout << "1. By fee description\n";
        std::cout << "2. By urgency level\n";
        std::cout << "3. Back to main menu\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        if(choice < 1 || choice > 3 || std::cin.fail()) {
            std::cout << "Invalid input. Please try again.";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else {
            break;
        }
    }

    Node* temp = head;
    bool isFound = false;

    if (choice == 1) {
        std::cout << "Enter the fee description of the fee you wanted to search: ";
        std::cin.ignore();
        std::getline(std::cin, searchDesc);
        if(temp == nullptr) {
            std::cout << "Fee not found. The records are empty.";
            return;
        }

        while(temp != nullptr) {
            if(temp->feeInfo == searchDesc) {
                std::cout << "Fee found!\n";
                std::cout << "Description:" << temp->feeInfo << '\n';
                std::cout << "Amount: " << temp->amount << '\n';
                std::cout << "Urgency Level: " << temp->urgency << '\n';
                std::cout << "----------------------------------------\n";
                
                isFound = true;
            }
            temp = temp->next;
        }
        if(!isFound) {
            std::cout << "Fee not found. Try again.";
        }
    } else if (choice == 2) {
        std::cout << "Enter the urgency level of the fee you wanted to search: ";
        std::cin >> searchUrgency;
        
        while(temp != nullptr) {
            if(temp->urgency == searchUrgency) {
                std::cout << "Fee found!\n";
                std::cout << temp->feeInfo << '\n';
                std::cout << temp->amount << '\n';
                std::cout << temp->urgency << '\n';
                std::cout << "----------------------------------------\n";
                
                isFound = true;
            }
            temp = temp->next;
        }
        if(!isFound) {
            std::cout << "Fee not found. Try again.\n";
        }
    } else {
        std::cout << "Going back to main menu . . .\n";
        return;
    }
}

void urgentInMenu (Node* head) {
    if(head == nullptr) {
        std::cout << "\nThere's still no urgent fees found.\n";
        std::cout << "----------------------------------------\n";
        return;
    }

    Node* temp = head;
    Node* mostUrgent = head;
    while(temp != nullptr) {
        if(temp->urgency > mostUrgent->urgency) {
            mostUrgent = temp;
            
        }
        temp = temp->next;
    }

    
    std::cout << "\nUrgent fee:\n";
    std::cout << "Description: " << mostUrgent->feeInfo << "\n";
    std::cout << "Amount:" << mostUrgent->amount << "\n";
    std::cout << "Please pay it immediately.\n"; 
    std::cout << "----------------------------------------\n";
}