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

void displayMenu();
void addFee();
void displayFees();
void displayByUrgency();
void searchFee();
void updateFee();
void markAsPaid();
void displayHistory();

Node* head = nullptr;

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
            case 1: addFee(); break;
            case 2: displayFees(); break;
            case 3: markAsPaid(); break;
            case 4: searchFee(); break;
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
    temp->next == newNode;

}