#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"

using namespace std;

void print_menu() {
    system("cls");
    cout<<"\n            |___*****CHOICE*****___|            \n"
        <<"1. Copying and moving assignment operators\n"
        <<"2. Determine the number of elements in the queue with a specific priority and the total number of elements\n"
        <<"3. Check for an empty queue\n"
        <<"4. Insert element with value and priority\n"
        <<"5. Delete an item from the queue\n"
        <<"6. Get information about the priority and value of the item at the head of the queue\n"
        <<"7. Finish the program\n"
        <<"*to avoid mistakes it is recommended to do the first time from 1 to 6 \n"
        <<"Your choice (1-7):  ";
}

//проверка на input пользователя
int get_variant (int count) {
    int variant;
    cin>>variant;
    while (variant < 1 || variant > count) {
        cout << "Incorrect input. Try again: ";
        cin>>variant;
    }
    return variant;
}

//основная функция
int main() {
    PriorityQueue queue0;    
    PriorityQueue queue1;
    PriorityQueue queue2;
    PriorityQueue queue3;
    for(int i=0; i<20;i++) {  //цикл для рандомного заполнения очереди
        int a, b;
        srand(time(NULL));
        a = rand()%20;
        b = rand()%3+1;
        switch (b)
        {
        case 1:
            queue2.Push(a,PriorityQueue::Priority::high);
            break;
        case 2:
            queue2.Push(a,PriorityQueue::Priority::medium);
            break;
        case 3:
            queue2.Push(a,PriorityQueue::Priority::low);
            break;
        }
    }

    print_menu();
    int n;
    n = get_variant(7);
    while (n!=7) {  // обработка меню
        switch (n)
        {
        case 1:
            queue3=queue2; //копирующий оператор присваивания
            queue1=move(queue2); //перемещающий оператор присваивания
            cout<<"Assigment ends successfully.";
            break;
        case 2: //количество элементов очереди(по приоритетам и в общем)
            int q,w,e,r;
            q = queue1.GetCountOfHighPriority();
            w = queue1.GetCountOfMediumPriority();
            e = queue1.GetCountOfLowPriority();
            r = queue1.Size();
            cout<<"The number of elements in the queue queue1 with high priority is "<< q <<endl;
            cout<<"The number of elements in the queue queue1 with medium priority is "<< w <<endl;
            cout<<"The number of elements in the queue queue1 with low priority is "<< e <<endl;
            cout<<"The total number of elements in the queue is "<< r <<endl;
            break;
        case 3: //проверка на пустоту
                if(queue0.IsEmpty()) {
                    cout<<"Queue0 is empty.\n";
                }
                else {
                    cout<<"Queue0 isn't empty.\n";
                }
                if(queue1.IsEmpty()) {
                    cout<<"Queue1 is empty.\n";
                }
                else {
                    cout<<"Queue1 isn't empty.\n";
                }
                if(queue2.IsEmpty()) {
                    cout<<"Queue2 is empty.\n";
                }
                else {
                    cout<<"Queue2 isn't empty.\n";
                }
            break;
        case 4: //добавление числа 5 в queue2 во всех приоритетах
            queue2.Push(5,PriorityQueue::Priority::high);
            queue2.Push(5,PriorityQueue::Priority::medium);
            queue2.Push(5,PriorityQueue::Priority::low);
            cout<<"In Queue2 was added 5 in all priorities.\n";
            break;
        case 5: // удаление первого элемента в двух очередях
            queue2.Pop();
            queue3.Pop();
            cout<<"In queues queue2 and queue3 the first elements were deleted.";
            break;
        case 6: // значение начала и конца с приоритетом
            int a;
            PriorityQueue::Priority b;
            b = queue1.GetPriorityOfHead();
            a = queue1.GetValueOfHead();
            cout<<"The value of head in queue1 is "<<a<<endl;
            if(b==PriorityQueue::Priority::high) {
                cout<<"The priority of head in queue1 is high.";
            }
            else {
                if(b==PriorityQueue::Priority::high) {
                    cout<<"The priority of head in queue1 is medium.";
                }
                else {
                    cout<<"The priority of head in queue1 is low.";
                }
            }
            break;      
        }
        print_menu();
        n = get_variant(7);
    }
    cout<< "Work completed.\n";

    return 0;
}