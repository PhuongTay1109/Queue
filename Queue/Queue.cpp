#include "graphics.h"
#include "Queue.h"
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void drawWelcomeInterface();
void queueSimulation();
void drawInsert(string data);
void drawDelete(string preFrontNode);
void drawObjectsInQueue(RECT pos);

QUEUE* q = new QUEUE();

int main()
{
    q->init(); // khởi tạo queue
    initgraph(); // khởi tạo graphic
    drawWelcomeInterface(); // vẽ giao diện bắt đầu
    _getch();
    system("cls");

   drawQueueFrame(); // vẽ khung queue
   queueSimulation(); // bắt đầu mô phỏng

    return 0;
}

// Vẽ giao diện bắt đầu
void drawWelcomeInterface()
{
    drawText(430, 80, "QUEUE SIMULATION", 255, 0, 0);
    drawQueueFrame();

    // vẽ 2 node bên trong queue
    for (int i = 100; i <= 200; i+=100)
    {

        rectangle(firstNodePos.left + i, firstNodePos.top, firstNodePos.right + i, firstNodePos.bottom);
    }

    // vẽ node delete
    drawText(270, 220, "DELETE", 255, 255, 0);
    setcolor(12);
    line(230, 250, 350, 250);
    setcolor(12);
    line(230, 250, 240, 240);
    setcolor(12);
    line(230, 250, 240, 260);
    setcolor(12);
    rectangle(endPos);

    // vẽ node insert
    drawText(720, 220, "INSERT", 255, 255, 0);
    setcolor(12);
    line(700, 250, 820, 250);
    setcolor(12);
    line(700, 250, 710, 240);
    setcolor(12);
    line(700, 250, 710, 260);
    setcolor(12);
    rectangle(beginPos);

    drawText(320, 400, "This program simulates the queue having capacity of 4 objects.", 255, 255, 255);
    drawText(420, 430, "Press any key to start.", 255, 255, 255);
}
 
// Vẽ các node trong queue
// Hàm này nhận vào 1 tham số kiểu RECT để bắt đầu vẽ từ vị trí đó
void drawObjectsInQueue(RECT pos)
{
    system("cls");
    drawQueueFrame(); // vẽ khung queue
    // nếu queue rỗng thì kết thúc sau khi vẽ khung, không cần vẽ node bên trong
    if (q->isEmpty()) {
        return;
    }

    // duyệt các node trong queue và vẽ ra màn hình bắt đầu từ vị trí được truyền vào
    // mỗi node rộng 50 đơn vị và cách nhau 50 đơn vị
    NODE* tmp = q->front;
    for (int i = 0; i < q->size() * 100; i += 100)
    {
        block(pos.left + i, pos.top, pos.right + i, pos.bottom, tmp->data.c_str()); // vẽ ra 1 hình chữ nhật có dữ liệu bên trong
        tmp = tmp->next;
    }
}

// Vẽ queue đang xóa
void drawDelete(string preFrontNode)
{
    // node được xóa bắt đầu di chuyển từ vị trí của node đầu tiên
    int x1 = firstNodePos.left, y1 = firstNodePos.top, x2 = firstNodePos.right, y2 = firstNodePos.bottom;
    int max = firstNodePos.left - endPos.left;
    for (int i = 0; i < max; i += 10)
    {
        system("cls");
        // Nếu node đã di chuyển ra khỏi queue thì vẽ các node còn lại trong queue bắt đầu từ vị trí đầu tiên
        if (i > 100) {
            block(x1 - i, y1, x2 - i, y2, preFrontNode.c_str());
            drawObjectsInQueue(firstNodePos);
        }
        // Nếu node đang di chuyển trong queue thì vẽ các node còn lại bắt đầu từ vị trí thứ hai
        else
        {
            block(x1 - i, y1, x2 - i, y2, preFrontNode.c_str());
            drawObjectsInQueue(secondPos);
        }
        Sleep(sleepTime);
    }
    // Vẽ lại queue 1 lần nữa sau khi vòng lặp kết thúc
    drawObjectsInQueue(firstNodePos);
}

// Vẽ queue đang được thêm node mới
void drawInsert(string data)
{
    // Node được thêm vào bắt đầu di chuyển từ vị trí của beginPos
    int x1 = beginPos.left, y1 = beginPos.top, x2 = beginPos.right, y2 = beginPos.bottom;
    for (int i = 0; i < getmaxx(); i += 10)
    {
        system("cls");
        x1 -= i;
        x2 -= i;
        // Điều kiện dừng
        // 820 - 20 cho chẵn số
        // maxCap - q.size là bước di chuyển
        // - 50 là độ rộng của node đó
        if(x1 < (820 - 100*(maxCap - q->size()) - 20 - 50))
            break;
        block(x1, y1, x2, y2, data.c_str());
        drawObjectsInQueue(firstNodePos);
        Sleep(sleepTime);
    }
    // Insert node mới vào và vẽ lại queue 1 lần nữa
    q->insert(data);
    drawObjectsInQueue(firstNodePos);
}

void queueSimulation()
{
    cout << "Press '1' to Insert." << endl;
    cout << "Press '2' to Delete." << endl;
    cout << "Press any other key to esc." << endl;
    int opt;
    string data;
    cin >> opt;
    if (opt == 1)
    {
        if (q->size() >= 4)
        {
            cout << "Queue is full. You can only choose Delete." << endl;;
            queueSimulation();
        }
        else
        {
            cout << "Enter data: ";
            cin >> data;
            drawInsert(data);
            queueSimulation();
        }
    }
    else if (opt == 2)
    {
        if (!q->isEmpty())
        {
            string preFrontNode = q->front->data; // dữ liệu của node front cũ
            q->deleteElement(); // xóa queue
            drawDelete(preFrontNode);
            queueSimulation();
        }
        else
        {
            cout << "Queue is empty. You must insert data first." << endl;
            queueSimulation();
        }
    }
    else
    {
        system("cls");
    }
}

