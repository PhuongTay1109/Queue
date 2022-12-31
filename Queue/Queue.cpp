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

void drawQueueFrame();
void drawWelcomeInterface();
void queueSimulation();
void drawInsert(string data);
void drawDelete(string preFrontNode);
void drawObjectsInQueue(RECT pos);

QUEUE* q = new QUEUE();
RECT firstNodePos = { 350, 225, 400, 275 };
RECT secondPos = { 450, 225, 500, 275 }; 
RECT beginPos = { 820, 225, 870, 275 };
RECT endPos = { 180, 225, 230, 275 }; 
int sleepTime = 30;
int maxCap = 4;

int main()
{
    q->init(); 
    initgraph(); 
    drawWelcomeInterface();
    _getch();
    system("cls");

   drawQueueFrame(); 
   queueSimulation(); 

    return 0;
}

void drawQueueFrame()
{
    setcolor(15);
    line(300, 200, 750, 200);
    line(300, 300, 750, 300);
}

void drawWelcomeInterface()
{
    drawText(430, 80, "QUEUE SIMULATION", 255, 0, 0);
    drawQueueFrame();

    for (int i = 100; i <= 200; i+=100)
    {

        rectangle(firstNodePos.left + i, firstNodePos.top, firstNodePos.right + i, firstNodePos.bottom);
    }

    drawText(270, 220, "DELETE", 255, 255, 0);
    setcolor(12);
    line(230, 250, 350, 250);
    setcolor(12);
    line(230, 250, 240, 240);
    setcolor(12);
    line(230, 250, 240, 260);
    setcolor(12);
    rectangle(endPos);

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
 
void drawObjectsInQueue(RECT pos)
{
    system("cls");
    drawQueueFrame(); 

    if (q->isEmpty()) {
        return;
    }

    NODE* tmp = q->front;
    for (int i = 0; i < q->size() * 100; i += 100)
    {
        block(pos.left + i, pos.top, pos.right + i, pos.bottom, tmp->data.c_str());
        tmp = tmp->next;
    }
}

void drawDelete(string preFrontNode)
{
    int x1 = firstNodePos.left, y1 = firstNodePos.top, x2 = firstNodePos.right, y2 = firstNodePos.bottom;
    int max = firstNodePos.left - endPos.left;
    for (int i = 0; i < max; i += 10)
    {
        system("cls");
        if (i > 100) {
            block(x1 - i, y1, x2 - i, y2, preFrontNode.c_str());
            drawObjectsInQueue(firstNodePos);
        }
        else
        {
            block(x1 - i, y1, x2 - i, y2, preFrontNode.c_str());
            drawObjectsInQueue(secondPos);
        }
        Sleep(sleepTime);
    }
    drawObjectsInQueue(firstNodePos);
}

void drawInsert(string data)
{
    int x1 = beginPos.left, y1 = beginPos.top, x2 = beginPos.right, y2 = beginPos.bottom;
    for (int i = 0; i < getmaxx(); i += 10)
    {
        system("cls");
        x1 -= i;
        x2 -= i;
        if(x1 < (820 - 100*(maxCap - q->size()) - 20 - 50))
            break;
        block(x1, y1, x2, y2, data.c_str());
        drawObjectsInQueue(firstNodePos);
        Sleep(sleepTime);
    }
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
            cout << "Queue is full. You can only choose Delete." << endl;
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
            string preFrontNode = q->front->data;
            q->deleteElement();
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

