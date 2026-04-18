#include <iostream>
#include <string>
#include <iomanip>
#include <stack>
#include <queue>

struct Node {
    std::string feeInfo;
    float amount;
    int urgency;
    Node* next;
};

struct feeRecord {
    std::string feeInfo;
    float amount;
    int urgency;
};

std::stack<feeRecord> history;
Node* head = nullptr;

void displayMenu(Node* head);
void addFee(Node*& head);
void displayFees(Node* head);
void displayByUrgency();
void searchFee(Node* head);
void markAsPaid(Node*& head);
void displayHistory();

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
        std::cout << "==========\n";
        std::cout << std::setw(5) << "Main Menu" << std::setw(5) << "\n";
        std::cout << "==========\n";
        std::cout << "1. Add Fee Record\n";
        std::cout << "2. Show Fee Records\n";
        std::cout << "3. Mark Fee As Paid\n";
        std::cout << "4. Search Fee\n";
        std::cout << "5. Display Payment History\n";

        std::cout << "\n Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1: addFee(head); break;
            case 2: displayFees(head); break;
            case 3: markAsPaid(head); break;
            case 4: searchFee(head); break;
            case 5: displayHistory(); break;
            default: {
                std::cout << "Invalid input. Please try again.\n";
                return;
            }
        }
    }
}

void addFee(Node*& head) {
    std::string feeDesc;
    int urgency;
    float amount;

    std::cout << "Enter fee type: ";
    std::cin.ignore();
    std::getline(std::cin, feeDesc);
    std::cout << "Enter amount: ₱";
    std::cin >> amount;
    std::cout << "Enter the fee urgency (1 - 4)";
    std::cin >> urgency;

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

void displayFees(Node* head) {
    Node* temp = head;
    int counter = 1;
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

void markAsPaid(Node*& head) {
    if (head == nullptr) {
        std::cout << "No fees to pay! Good work.\n";
        return;
    }

    feeRecord record;
    int searcher;
    std::cout << "Enter the fee number of the paid fee: ";
    std::cin >> searcher;

    searcher--; // in order to make the positions 0-indexed

    if(searcher < 1) {
        std::cout << "Invalid input.\n";
        return;
    }

    if(searcher == 0) {
        Node* temp = head;
        record.feeInfo = temp->feeInfo;
        record.amount = temp->amount;
        record.urgency = temp->urgency;

        history.push(record);

        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;
    for(int i = 0; i < searcher - 1; i++){
        if(temp->next == nullptr) {
            std::cout << "Invalid input. Fee does not exist.\n";
            return;
        }
        temp = temp->next;
    }

    Node* toDelete = temp->next;

    if (toDelete == nullptr) {
        std::cout << "Invalid input. The fee does not exist.";
        return;
    }

    record.feeInfo = toDelete->feeInfo;
    record.amount = toDelete->amount;
    record.urgency = toDelete->urgency;

    history.push(record);

    temp->next = toDelete->next;
    delete toDelete;

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
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        if(choice < 1 || choice > 2 || std::cin.fail()) {
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
                std::cout << temp->feeInfo << '\n';
                std::cout << temp->amount << '\n';
                std::cout << temp->urgency << '\n';
                std::cout << "----------------------------------------";
                
                isFound = true;
            }
            temp = temp->next;
        }
        if(!isFound) {
            std::cout << "Fee not found. Try again.";
        }
    } else {
        std::cout << "Enter the urgency level of the fee you wanted to search: ";
        std::cin >> searchUrgency;
        
        while(temp != nullptr) {
            if(temp->urgency == searchUrgency) {
                std::cout << "Fee found!\n";
                std::cout << temp->feeInfo << '\n';
                std::cout << temp->amount << '\n';
                std::cout << temp->urgency << '\n';
                std::cout << "----------------------------------------";
                
                isFound = true;
            }
            temp = temp->next;
        }
        if(!isFound) {
            std::cout << "Fee not found. Try again.";
        }
    }
}