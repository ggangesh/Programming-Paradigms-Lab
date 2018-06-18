#include <iostream>
using namespace std;

struct Element {int id;Element *next;};
struct Queue {Element *front, *end; int numElements;};

void reverse(Queue &q,Element *&t1);


int main()
{
Queue q;
q.front = NULL; q.end = NULL; q.numElements = 0;

bool b=true;

while (b)
{
cout << "Command: ‘j’ to join queue, ’x’ to exit." << endl;
char command; cin >> command;
switch(command)
{
case 'j':
        Element *newElement; newElement= new Element;
        if (newElement == NULL) {cout << "Memory allocation failure"<< endl; return -1;}
        newElement->next = NULL;
        cout << "Give id of element: "; cin >> newElement->id;

        if (q.end == NULL)
        { // Element queue empty
            q.front = newElement; q.end = newElement; q.numElements = 1;
        }
        else {(q.end)->next = newElement; q.end = newElement; q.numElements++; }

break;

case 'x': cout << "Thank you" << endl;b=false;
break;
default: cout << "Invalid command." << endl;
}
}

Element *t;

//code to display the linked list

cout<<"The list is "<<endl;
t=q.front;
while(t!=NULL)
{
    cout<< "ID "<< t->id<<endl;
    t=t->next;
}


//code to reverse the linked list using 2 temporary variables t and t1
if(q.front==NULL)
{}

else
{
    Element *t1;
    t1=q.front->next;

    q.front->next=NULL;

    reverse(q,t1);
}


cout<<endl<<"The list has been reversed"<<endl<<endl;

//code to display the linked list
cout<<"The list is "<<endl;
t=q.front;
while(t!=NULL)
{
    cout<< "ID "<< t->id<<endl;
    t=t->next;
}

return 0;



}

void reverse(Queue &q,Element *&t1)
{
    if(t1==NULL)
    {
        return;
    }

    Element *t;
    t=q.front;
    q.front=t1;
    t1=t1->next;
    q.front->next=t;

    reverse(q,t1);

}
