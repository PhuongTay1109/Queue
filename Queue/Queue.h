#pragma once

// Mỗi node trong queue rộng 50 đơn vị và cách nhau 50 đơn vị
RECT firstNodePos = { 350, 225, 400, 275 }; // vị trí của node đầu tiên trong queue
RECT secondPos = { 450, 225, 500, 275 }; // vị trí của node thứ hai trong queue
RECT beginPos = { 820, 225, 870, 275 }; // vị trí bắt đầu khi di chuyển vào queue
RECT endPos = { 180, 225, 230, 275 }; // vị trí node kết thúc sau khi di chuyển khỏi queue
int sleepTime = 100;
int maxCap = 4; // số node tối đa trong queue

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

void drawQueueFrame()
{
    setcolor(15);
    line(300, 200, 750, 200);
    line(300, 300, 750, 300);
}
