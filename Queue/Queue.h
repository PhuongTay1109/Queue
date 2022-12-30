#pragma once

struct NODE {
    string data;
    NODE* next;
};

struct QUEUE {
    NODE* front;
    NODE* rear;

    void init() {
        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty() {
        if (front == nullptr)
            return true;
        return false;
    }

    NODE* makeNode(string x) {
        NODE* newNode = new NODE();
        newNode->data = x;
        newNode->next = nullptr;
        return newNode;
    }

    void insert(string x) {
        NODE* newNode = makeNode(x);
        if (this->isEmpty()) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void deleteElement() {
        if (this->isEmpty())
            return;
        else {
            NODE* newFront = front->next;
            delete(front);
            front = newFront;
            if (front == nullptr)
                rear = nullptr;
        }
    }

    int size()
    {
        NODE* tmp = front;
        int cnt = 0;
        while (tmp != nullptr) {
            cnt++;
            tmp = tmp->next;
        }
        return cnt;
    }
};

