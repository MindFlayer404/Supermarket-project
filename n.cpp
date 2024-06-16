#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Declarations of functions
int search(int);
int display();
int back();
int check(int);       // For checking quantity

int value = 0;

// Node structure
struct Node {
    int ID;
    string proName;
    double prePrice;  // Product price
    int quantity;
    Node* next;
};

Node* head = nullptr;

// For entering (saving) the 1st record in the list
void beg() {
    system("cls");
    int id, quant;  // Quant for quantity
    string name;
    double pre;  // Pre for price
    Node* t = new Node;

    cout << "\t\t\tEnter product ID: ";
    cin >> id;
    t->ID = id;

    cout << "\t\t\tEnter product Name: ";
    cin >> name;
    t->proName = name;

    cout << "\t\t\tEnter product price: ";
    cin >> pre;
    t->prePrice = pre;

    cout << "\t\t\tEnter product quantity: ";
    cin >> quant;
    t->quantity = quant;

    t->next = head;
    head = t;

    system("cls");
    cout << "\n\n\t\t\t\tThis product is Inserted!\n\n\n";
}

// For entering (saving) the 2nd and onward records in the list
void end() {
    system("cls");
    int id, quant;  // Quant for quantity
    string name;
    double pre;  // Pre for price
    Node* t = new Node;
    Node* p = head;

    cout << "\t\t\tEnter product ID: ";
    cin >> id;
    t->ID = id;

    cout << "\t\t\tEnter product Name: ";
    cin >> name;
    t->proName = name;

    cout << "\t\t\tEnter product price: ";
    cin >> pre;
    t->prePrice = pre;

    cout << "\t\t\tEnter product quantity: ";
    cin >> quant;
    t->quantity = quant;

    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = t;
    t->next = nullptr;

    system("cls");
    cout << "\n\n\t\t\t\tThis product is Inserted!\n\n\n";
}

void delPro() {
    system("cls");
    display();
    int id;
    Node* cur = head;
    Node* pre = head;

    cout << "\n\nEnter ID to delete that product:\n\n";
    cin >> id;

    if (head == nullptr) {
        system("cls");
        cout << "List is empty\n";
        return;
    }

    int pos = 0;
    int count = display();  // For load no of nodes
    pos = search(id);  // For check whether desired node exists or not

    if (pos <= count) {
        while (cur->ID != id) {  // For deleting middle area products
            pre = cur;
            cur = cur->next;
        }
        pre->next = cur->next;
        system("cls");
        cout << "\n<<item is deleted>>\n";
    } else {
        cout << "\n<<<Not found>>>\n\n";
    }
}

void modify() {
    int id;
    double pre;  // Pre for price
    string pName;  // pName for new name

    if (head == nullptr) {
        system("cls");
        cout << "List is empty\n";
    } else {
        cout << "\n\nEnter ID to modify product Name and its price:\n";
        cin >> id;

        Node* cur = head;
        int pos = 0;
        int count = display();  // For load no of nodes
        pos = search(id);  // For check whether desired node exists or not

        if (pos <= count) {
            while (cur->ID != id) {
                cur = cur->next;
            }

            cout << "\nOld Name : " << cur->proName;
            cout << "\nOld Price : " << cur->prePrice;
            cout << "\nEnter new Name: ";
            cin >> pName;
            cur->proName = pName;

            cout << "Enter new Price: ";
            cin >> pre;
            cur->prePrice = pre;
        } else {
            cout << id << " is <<Not found>>\n\n";
        }
    }
}

int display() {
    system("cls");
    int c = 0;  // C for count products
    Node* p = head;

    cout << "Existing products are:\n";
    cout << "ID\t\tProduct Name\t\tPrice\t\tQuantity\n";

    while (p != nullptr) {
        cout << p->ID << "\t\t" << p->proName << "\t\t\t" << p->prePrice << "\t";
        if (check(p->quantity) <= 0)
            cout << "OUT OF STOCK!\n";
        else
            cout << check(p->quantity) << "\n";

        p = p->next;
        c++;
    }

    cout << "\nTotal products in our store is : " << c << "\n\n\n";
    return c;
}

int check(int quant) {  // Check function
    return quant <= 0 ? 0 : quant;
}

void buy() {
    system("cls");
    int pay = 0, no, price, id, i = 1;

    if (head == nullptr) {
        cout << "\n<<<<There is no items to buy>>>>\n\n";
    } else {
        cout << "How many items you want to buy!\n";
        cin >> no;

        int count = display();  // For store no of nodes in c

        while (i <= no) {
            Node* cur = head;
            int quant;

            cout << "Enter id of item that you want to buy: ";
            int id, pos = 0;
            cin >> id;
            pos = search(id);

            if (pos <= count) {  // Item is available in store
                while (cur->ID != id) {
                    cur = cur->next;
                }

                cout << "How many quantities you want:";
                cin >> quant;
                pay += (cur->prePrice * quant);  // Calculate Bill
                cur->quantity -= quant;  // Change quantity
                i++;

                cout << "\n\n\t\t\tYou have bought : " << cur->proName << "\n\n";
            } else {
                cout << "\n<<<<<This item is not available in our store at this time>>>>\n\n";
            }
        }

        price = pay * 0.90;  // With 10% discount
        cout << "\n\n\t\t\t\t\tOriginal price : " << pay << "\n";
        cout << "\t\t\t\t\twith 10 percent discount: " << price << "\n\t\t\t\t\tThank you! for the shopping\n\n";
    }
}

int search(int id) {  // For searching item in list
    int count = 1;
    Node* p = head;

    while (p != nullptr) {
        if (p->ID == id)
            break;
        else {
            count++;
            p = p->next;
        }
    }

    return count;
}

int back() {
    int no, i = 1, give = 0;

    cout << "How many items you want to return!\n";
    cin >> no;
    int count = display();

    while (i <= no) {
        Node* cur = head;
        int quant;

        cout << "Enter the id of product you want to return";
        int id, pos = 0;
        cin >> id;
        pos = search(id);

        if (pos <= count) {  // Item is available in store
            while (cur->ID != id) {
                cur = cur->next;
            }

            cout << "\n\nHow many quantities you want to return\n\n";
            cin >> quant;
            give += (cur->prePrice * quant);  // Calculate Bill
            cur->quantity += quant;
            i++;
        }
    }

    cout << "\n\n\t\t\t\tYou will get " << give << " rs back";
}

// Main function
int main() {
    int flag, flag1;
    cout << "-----|   Bali Arcade   |-----\n";
    cout << "-------| MONDAY off! |------\n\n\n";

    int temp = 1;

    while (true) {
        int cm;
        flag = 1;
        flag1 = 1;

        cout << "\t\tEnter 1 for Shopkeeper portal \n\n\t\tEnter 2 for Customer portal\n\n\t\tEnter 0 for exit\n\n";
        cout << "Enter:";
        cin >> cm;

        switch (cm) {
            case 1:
                while (flag) {
                    int ch;  // Choice for below message
                    cout << "\t\tEnter 1 for ADD a new product \n\n\t\tEnter 2 to display all products \n\n\t\tEnter 3 for MODIFY Existing product\n\n";
                    cout << "\t\tEnter 4 for Delete a particular product item\n\n\t\tEnter 0 for exit\n\n";
                    cout << "Enter:";
                    cin >> ch;

                    switch (ch) {
                        case 1:
                            if (temp == 0) {  // Second time and onward this is only executed
                                end();
                            }
                            if (temp == 1) {
                                value++;  // This will be executed only one time
                                beg();
                                temp = 0;
                            }
                            break;
                        case 2:
                            system("cls");
                            display();
                            break;
                        case 3:
                            modify();
                            break;
                        case 4:
                            delPro();
                            break;
                        case 0:
                            cout << "Exiting...\n";
                            flag = 0;  // Exit from while loop
                            break;
                        default:
                            system("cls");
                            cout << "\t\t<<<Wrong choice>>>\n\n";
                            break;
                    }
                }
                break;
            case 2:
                while (flag1) {
                    int cd;
                    cout << "\n\n\t\tEnter 1 To buy something\n\n\t\tEnter 2 to return something\n\n\t\tEnter 0 for exit\n\n";
                    cout << "Enter:";
                    cin >> cd;

                    switch (cd) {
                        case 1:
                            buy();
                            break;
                        case 2:
                            back();
                            break;
                        case 0:
                            cout << "Exiting...\n";
                            flag1 = 0;  // Exit from while loop
                            break;
                        default:
                            system("cls");
                            cout << "\t\t<<<Wrong choice>>>\n\n";
                            break;
                    }
                }
                break;
            case 0:
                cout << "Exiting...\n";
                exit(1);  // Exit from while loop
                break;
            default:
                system("cls");
                cout << "\t\t<<<Wrong choice>>>\n\n";
                break;
        }
    }
}

