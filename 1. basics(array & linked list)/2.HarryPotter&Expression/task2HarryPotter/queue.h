#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;

    Node(int v) {
        this->val = v;
    }
};

class Queue {
    Node* head;
    Node* tail;

public:
    Queue() {
        head = NULL;
        tail = NULL;
    }

    void put(int val) {
        if (head == NULL) {
            head = new Node(val);
            tail = head;
            return;
        }
        Node* temp = new Node(val);
        tail->next = temp;
        tail = tail->next;
    }

    int get() {
        if (head == NULL) {
            throw invalid_argument("Invalid arg");
        }
        int val = head->val;
        if (head == tail) {
            delete head;
            head = tail = NULL;
        }
        else {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }

        return val;
    }

    bool empty() {
        return head == NULL;
    }
};