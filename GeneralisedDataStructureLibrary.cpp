#include<iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Structure of Singly Linked List and Stack and Queue
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
struct node
{
   T Data;
   struct node * next;
};




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Structure of Doubly Linked List
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
struct node
{
   T Data;
   struct node *prev;
   struct node *next;
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class of Singly Circular Linked List
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class SinglyCR
{
   private:
	struct node<T> *Head;
	struct node<T> *Tail;
	
   public:
   	SinglyCR();
   	void InsertFirst(T);
   	void InsertLast(T);
   	void InsertAtPos(T,int);
   	void DeleteFirst();
   	void DeleteLast();
   	void DeleteAtPos(int);
   	int Count();
   	void Display();   	
};

template <class T>
SinglyCR<T>::SinglyCR()
{
   Head = NULL;
   Tail = NULL;
}

template <class T>
void SinglyCR<T>::InsertFirst(T value)
{
    struct node<T> *newn = NULL;

    newn = new node<T>;

    newn->Data = value;
    newn->next = NULL;

    if((Head == NULL) && (Tail == NULL))    // If LL is empty
    {
        Head = newn;
        Tail = newn;
    }
    else        // If LL constains atleast one node
    {
        newn -> next = Head;
        Head = newn;
    }
    Tail -> next = Head;
   
}

template <class T>
void SinglyCR<T>::InsertLast(T value)
{
   struct node<T> *newn = NULL;
   newn = new node<T>;
   
   newn->Data = value;
   newn->next = NULL;
   
   if((Head==NULL) && (Tail==NULL))
   {
      Head = newn;
      Tail = newn;
   }
   else
   {
      Tail->next = newn;
      Tail = newn;
   }
   Tail->next = Head;
}

template <class T>
void SinglyCR<T>::InsertAtPos(T value,int iPos)
{
   int iRet = 0;
   iRet = Count();
   
   if((iPos<1)||(iPos>(iRet+1)))
   {
      cout<<"Invalid Position"<<endl;
      return;
   }
   if(iPos == 1)
   {
      InsertFirst(value);
   }
   else if(iPos == (iRet+1))
   {
      InsertLast(value);
   }
   else
   {
     struct node<T> *newn = NULL;
     struct node<T> *Temp = NULL;
     Temp = Head;
     int iCnt = 0;
   
     newn = new node<T>;
     newn->Data = value;
     newn->next = NULL;
   
     for(iCnt=1;iCnt<(iPos-1);iCnt++)
     {
         Temp = Temp->next; 
     }
     newn->next = Temp->next;
     Temp->next = newn;
   }
}


template <class T>
void SinglyCR<T>::Display()
{
   struct node<T> *Temp = NULL;
   Temp = Head;
   
   do
   {
      cout<<"|"<<Temp->Data<<"|"<<"=>";
      Temp = Temp->next;
   }while(Temp != Head);
   
   cout<<endl;
}


template <class T>
int SinglyCR<T>::Count()
{
   struct node<T> *Temp = NULL;
   Temp = Head;
   int iCnt = 0;
   do
   {
      iCnt++;
      Temp = Temp->next;
   }while(Temp != Head);
   
   return iCnt;
}


template <class T>
void SinglyCR<T>::DeleteFirst()
{
    if((Head==NULL) && (Tail==NULL))
    {
       return;
    }
    else if(Head==Tail)
    {
       delete Head;
       Head = NULL;
       Tail = NULL;
    }
    else
    {
       Head = Head->next;
       delete Tail->next;
       
       Tail->next = Head;
    }
}


template <class T>
void SinglyCR<T>::DeleteLast()
{
    if((Head==NULL) && (Tail==NULL))
    {
       return;
    }
    else if(Head==Tail)
    {
       delete Head;
       Head = NULL;
       Tail = NULL;
    }
    else
    {
       struct node<T> *Temp = NULL;
       Temp = Head;
       while(Temp->next != Tail)
       {
          Temp = Temp->next;
       }
       delete Tail;
       Tail = Temp;
       Tail->next = Head;
    }
}

template <class T>
void SinglyCR<T>::DeleteAtPos(int iPos)
{
   int iRet = 0;
   iRet = Count();
   
   if((iPos<1) && (iPos>iRet))
   {
      cout<<"Invalid Position"<<endl;
      return;
   }
   
   if(iPos==1)
   {
      DeleteFirst();
   }
   else if(iPos==iRet)
   {
      DeleteLast();
   }
   else
   {
      struct node<T> *Temp = NULL;
      Temp = Head;
      
      struct node<T> *Temp2 = NULL;
      
      int iCnt = 0;
      
      for(iCnt=1;iCnt<(iPos-1);iCnt++)
      {
         Temp = Temp->next;
      }
      Temp2 = Temp->next;
      Temp->next = Temp2->next;
      delete Temp2;
      
   }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class of Singly Linear Linked List
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class SinglyLL
{
    public:
    	struct node<T> *Head;
    	int Count;
    	
    	SinglyLL();
    	void InsertFirst(T);
    	void InsertLast(T);
    	void InsertAtPos(T,int);
    	void DeleteFirst();
    	void DeleteLast();
    	void DeleteAtPos(int);
    	void Display();
    	int CountNodes();
    	
};

template <class T>
SinglyLL<T>::SinglyLL()
{
    Head = NULL;
    Count = 0;
}

template <class T>
void SinglyLL<T>::InsertFirst(T no)
{
    struct node<T> *newn = NULL;
    newn = new node<T>;
    
    newn->Data = no;
    newn->next = NULL;
    
    if(Head == NULL)
    {
        Head = newn;
    }
    else
    {
         newn->next = Head;
         Head = newn;
    }
    Count++;
}

template <class T>
void SinglyLL<T>::InsertLast(T no)
{
    struct node<T> *newn = NULL;
    newn = new node<T>;
    
    newn->Data = no;
    newn->next = NULL;
    
    if(Head == NULL)
    {
        Head = newn;
    }
    else
    {
        struct node<T> *Temp = Head;
        while(Temp->next != NULL)
        {
            Temp = Temp->next;
        }
        Temp->next = newn;
    }
    Count++;
}

template <class T>
void SinglyLL<T>::Display()
{
    cout<<"Elements from linked list are:"<<endl;
    struct node<T> *Temp = Head;
    
    while(Temp != NULL)
    {
       cout<<Temp->Data<<"=>";
       Temp = Temp->next;
    }
    cout<<endl;
}

template <class T>
int SinglyLL<T>::CountNodes()
{
    return Count;
}

template <class T>
void SinglyLL<T>::InsertAtPos(T No,int Pos)
{
   int Ret = 0;
   Ret = CountNodes();
   
   if((Pos<1) || (Pos>(Ret+1)))
   {
      cout<<"Invalide Position"<<endl;
      return;
   }
   
   if(Pos == 1)
   {
      InsertFirst(No);
   }
   else if(Pos == (Ret+1))
   {
      InsertLast(No);
   }
   
   else
   {
       int iCnt = 0;
       struct node<T> *newn = NULL;
       struct node<T> *Temp = Head;
       
       newn = new node<T>;
       newn->Data = No;
       newn->next = NULL;
       
       for(iCnt=1;iCnt<(Pos-1);iCnt++)
       {
          Temp = Temp->next;
       }
       newn->next = Temp->next;
       Temp->next = newn;
   }
   Count++;
}

template <class T>
void SinglyLL<T>::DeleteFirst()
{
   struct node<T> *Temp = NULL;
   
   
   if(Head == NULL)
   {
      return;
   }
   else
   {
      Temp = Head;
      Head = Head->next; 
      delete Temp;
   }
   Count--;
}

template <class T>
void SinglyLL<T>::DeleteLast()
{
   struct node<T> *Temp = Head;
   struct node<T> *DTemp = NULL;
   
   
   if(Head == NULL)
   {
      return;
   }
   else if(Head->next ==NULL)
   {
      delete Head;
      Head = NULL;
   }
   else
   {
       while(Temp->next->next != NULL)
       {
          Temp = Temp->next;
       }
       DTemp = Temp->next;
       Temp->next = NULL;
       delete DTemp;
   }
   Count--;
}

template <class T>
void SinglyLL<T>::DeleteAtPos(int Pos)
{
   int Ret = 0;
   Ret = CountNodes();
   
   if((Pos<1) || (Pos>Ret))
   {
       cout<<"Invalide Position"<<endl;
       return;     
   }
   
   if(Pos == 1)
   {
       DeleteFirst();
   }
   else if(Pos == Ret)
   {
       DeleteLast();
   }
   else
   {
       int iCnt = 0;
       struct node<T> *Temp = Head;
       struct node<T> *DTemp = NULL;
       
      
       for(iCnt=1;iCnt<(Pos-1);iCnt++)
       {
           Temp = Temp->next;
       }
       DTemp = Temp->next;
       Temp->next = DTemp->next;
       delete DTemp;
   }
   Count--;

}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class of Doubly Circular Linked List
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class DoublyCR
{
    private:
        struct node<T> *Head;
        struct node<T> *Tail;
        
    public:
          DoublyCR();
          void InsertFirst(T);
   	  void InsertLast(T);
   	  void InsertAtPos(T,int);
   	  void DeleteFirst();
   	  void DeleteLast();
   	  void DeleteAtPos(int);
   	  int Count();
   	  void Display();      

};

template <class T>
DoublyCR<T>::DoublyCR()
{
    Head = NULL;
    Tail = NULL;
}

template <class T>
void DoublyCR<T>::Display()
{
    struct node<T> *Temp = NULL;
    Temp = Head;
    
    if((Head == NULL) && (Tail == NULL))
    {
       return;
    }
    do
    {
       cout<<"|"<<Temp->Data<<"|";
       Temp = Temp->next;
    }while(Temp != Head);
    cout<<endl;
}

template <class T>
int DoublyCR<T>::Count()
{
    struct node<T> *Temp = NULL;
    Temp = Head;
    int iCnt = 0;
    
    if((Head == NULL) && (Tail == NULL))
    {
        return 0;
    }
    do
    {
       iCnt++;
       Temp = Temp->next;
    }while(Temp != Head);
    
    return iCnt;
}


template <class T>
void DoublyCR<T>::InsertFirst(T value)
{
    struct node<T> *newn = NULL;
    
    newn = new node<T>;
    newn->Data = value;
    newn->prev = NULL;
    newn->next = NULL;
    
    if((Head==NULL) && (Tail==NULL))
    {
       Head = newn;
       Tail = newn;
    }
    else
    {
       newn->prev = Tail;
       newn->next = Head;
       Head->prev = newn;
       Tail->next = newn;
       
       Head = newn;
    }
    
}

template <class T>
void DoublyCR<T>::InsertLast(T value)
{
   struct node<T> *newn = NULL;
   
   newn = new node<T>;
   newn->Data = value;
   newn->prev = NULL;
   newn->next = NULL;
   
   if((Head == NULL)  && (Tail == NULL))
   {
      Head = newn;
      Tail = newn;
   }
   else
   {
      newn->prev = Tail;
      Tail->next = newn;
      Tail = newn;
      Head->prev = Tail;
      Tail->next = Head;
   }
}

template <class T>
void DoublyCR<T>::InsertAtPos(T value,int iPos)
{
   int iRet = 0;
   iRet = Count();
   
   if((iPos<1) || (iPos>(iRet+1)))
   {
      cout<<"Invalid Position"<<endl;
      return;
   }
   
   if(iPos == 1)
   {
      InsertFirst(value);
   }
   else if(iPos == (iRet + 1))
   {
      InsertLast(value);
   }
   
   else
   {
      int iCnt = 0;
      struct node<T> *newn = NULL;
      
      newn = new node<T>;
      newn->Data = value;
      newn->prev = NULL;
      newn->next = NULL;
      
      struct node<T> *Temp = NULL;
      Temp = Head;
      
      for(iCnt=1;iCnt<(iPos-1);iCnt++)
      {
         Temp = Temp->next;
      }
      newn->prev = Temp;
      newn->next = Temp->next;
      Temp->next->prev = newn;
      Temp->next = newn;
   }
}

template <class T>
void DoublyCR<T>::DeleteFirst()
{
   if((Head == NULL) && (Tail == NULL))
   {
      return;
   }
   else if(Head == Tail)
   {
      delete Head;
      Head = NULL;
      Tail = NULL;
   }
   else
   {
      Head = Head->next;
      delete Head->prev;
      Head->prev = Tail;
      Tail->next = Head;
   }
}


template <class T>
void DoublyCR<T>::DeleteLast()
{
   struct node<T> *Temp = NULL;
   Temp = Head;
   
   if((Head == NULL) &&(Tail == NULL))
   {
      return;
   }
   else if(Head == Tail)
   {
      delete Head;
      Head = NULL;
      Tail = NULL;
   }
   else
   {
      while(Temp->next != Tail)
      {
         Temp = Temp->next;
      }
      delete Temp->next;
      Tail = Temp;
      Tail->next = Head;
      Head->prev = Tail;
   }
   
}


template <class T>
void DoublyCR<T>::DeleteAtPos(int iPos)
{
   int iRet = 0;
   iRet = Count();
   
   if((iPos<1) || (iPos>(iRet)))
   {
      cout<<"Invalid position"<<endl;
      return;
   }
   
   if(iPos == 1)
   {
      DeleteFirst();
   }
   else if(iPos == iRet)
   {
      DeleteLast();
   }
   else
   {
      struct node<T> *Temp = NULL;
      struct node<T> *Temp2 = NULL;
      
      Temp = Head;
      int iCnt = 0;
      
      for(iCnt=1;iCnt<(iPos-1);iCnt++)
      {
         Temp = Temp->next;
      }
      Temp2 = Temp->next;
      Temp->next = Temp2->next;
      Temp->next->prev = Temp;
      delete Temp2;
      
   }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class of Doubly Linear Linked List
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class DoublyLR
{
    private:
	struct node<T> *Head;
	
    public:
    	DoublyLR();
    	void InsertFirst(T);
    	void InsertLast(T);
    	void InsertAtPos(T,int);
    	void DeleteFirst();
    	void DeleteLast();
    	void DeleteAtPos(int);
    	void Display();
    	int Count();    	
};

template <class T>
DoublyLR<T>::DoublyLR()
{
    Head = NULL;
}

template <class T>
void DoublyLR<T>::Display()
{
    struct node<T> *Temp = NULL;
    Temp = Head;
    
    if(Head == NULL)
    {
       cout<<"Linked List is Empty"<<endl;
       return;
    }
    
    else
    {
       while(Temp != NULL)
       {
          cout<<Temp->Data<<"=>";
          Temp = Temp->next;
       }
       cout<<"NULL"<<endl;
    }
}

template <class T>
int DoublyLR<T>::Count()
{
    int iCnt = 0;
    struct node<T> *Temp = NULL;
    Temp = Head;
    
    while(Temp != NULL)
    {
       iCnt++;
       Temp = Temp->next;
    }
    return iCnt;

}

template <class T>
void DoublyLR<T>::InsertFirst(T value)
{
    struct node<T> *newn = NULL;
    newn = new node<T>;
    newn->Data = value;
    newn->prev = NULL;
    newn->next = NULL;
    
    if(Head == NULL)
    {
       Head = newn;
    }
    else
    {
       newn->next = Head;
       Head->prev = newn;
       Head = newn;
    }
}

template <class T>
void DoublyLR<T>::InsertLast(T value)
{
    struct node<T> *newn = NULL;
    struct node<T> *Temp = NULL;
    Temp = Head;
    
    newn = new node<T>;
    newn->Data = value;
    newn->prev = NULL;
    newn->next = NULL;
    
    if(Head == NULL)
    {
        Head = newn;
    }
    
    else
    {
        while(Temp->next != NULL)
        {
           Temp = Temp->next;
        }
        Temp->next = newn;
        newn->prev = Temp;
    }
}


template <class T>
void DoublyLR<T>::InsertAtPos(T value,int iPos)
{
    int iRet = 0;
    iRet = Count();
    
    if((iPos<1) || (iPos>(iRet+1)))
    {
        cout<<"Invalide Position"<<endl;
        return;
    }
    
    if(iPos == 1)
    {
        InsertFirst(value);
    }
    else if((iPos == (iRet+1)))
    {
        InsertLast(value);
    }
    else
    {
        int iCnt = 0;
        struct node<T> *newn = NULL;
        struct node<T> *Temp = NULL;
        
        Temp = Head;
        
        newn = new node<T>;
        newn->Data = value;
        newn->prev = NULL;
        newn->next = NULL;
        
        for(iCnt=1;iCnt<(iPos-1);iCnt++)
        {
            Temp = Temp->next;
        }
        newn->next = Temp->next;
        Temp->next = newn;
        newn->next->prev = newn;
        newn->prev = Temp;
      
    }
}


template <class T>
void DoublyLR<T>::DeleteFirst()
{
    struct node<T> *Temp = NULL;
    
    if(Head == NULL)
    {
        return;
    }
    else if(Head->next == NULL)
    {
        delete Head;
        Head = NULL;
    }
    else
    {
        Temp = Head;
        Head = Temp->next;
        Head->prev = NULL;
        delete Temp;
    }
    
}


template <class T>
void DoublyLR<T>::DeleteLast()
{
    struct node<T> *Temp = NULL;
    struct node<T> *DTemp = NULL;
    
    Temp = Head;
    
    if(Head == NULL)
    {
        return;
    }
    else if(Head->next == NULL)
    {
        delete Head;
        Head = NULL;
    }
    else
    {
        while(Temp->next->next != NULL)
        {
            Temp = Temp->next;
        }
        DTemp = Temp->next;
        Temp->next = NULL;
        delete DTemp;
    }
}


template <class T>
void DoublyLR<T>::DeleteAtPos(int iPos)
{
   int iRet = 0;
   iRet = Count();
   
   if((iPos<1) || (iPos>iRet))
   {
       cout<<"Invalide Position"<<endl;
       return;
   }
   
   if(iPos == 1)
   {
       DeleteFirst();
   }
   else if(iPos == iRet)
   {
       DeleteLast();
   }
   else
   {
       int iCnt = 0;
       struct node<T> *Temp = NULL;
       struct node<T> *DTemp = NULL;
       Temp = Head;
       
       for(iCnt=1;iCnt<(iPos-1);iCnt++)
       {
           Temp = Temp->next;
       }
       DTemp = Temp->next;
       Temp->next = DTemp->next;
       Temp->next->prev = Temp;
       delete DTemp;
   }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class of Stack
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<class T>
class Stack
{
    public:
        struct node<T> *Head;
        int Count;

        Stack();
        void Push(T);        // InsertLast
        void Pop();            // DeleteFirst
        void Display();
        int CountNode();
};

template<class T>
Stack<T>::Stack()
{
    Head = NULL;
    Count = 0;
}

template<class T>
void Stack<T>::Push(T no)
{
    struct node<T> *newn = NULL;
    newn = new node<T>;

    newn->data = no;
    newn->next = NULL;

    newn->next = Head;
    Head = newn;
    Count++;
}

template <class T>
void Stack<T>::Pop()       // Deletefirst
{
    T no;

    if(Count == 0)
    {
        cout<<"Stack is empty"<<endl;
        return;
    }

    no = Head -> data;
    struct node<T> *temp = Head;
    Head = Head->next;
    delete temp;       
    
    Count--;
    cout<<"Removed element is : "<<no<<endl;
}

template<class T>
void Stack<T>::Display()
{
    cout<<"Elements from Stack are : "<<endl;
    struct node<T> *temp = Head;
    while(temp != NULL)
    {
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

template<class T>
int Stack<T>::CountNode()
{
    return Count;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Class of Queue
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<class T>
class Queue
{
    public:
        struct node<T> *Head;
        int Count;

        Queue();
        void Enqueue(T);        // InsertLast
        void Dequeue();            // DeleteFirst
        void Display();
        int CountNode();
};

template<class T>
Queue<T>::Queue()
{
    Head = NULL;
    Count = 0;
}

template<class T>
void Queue<T>::Enqueue(T no)
{
    struct node<T> *newn = NULL;
    newn = new node<T>;

    newn->data = no;
    newn->next = NULL;

    if(Head == NULL)
    {
        Head = newn;
    }
    else
    {
            struct node<T> *temp = Head;
            while(temp->next != NULL)
            {
                temp = temp -> next;
            }

            temp->next = newn;
    }
    Count++;
}

template <class T>
void Queue<T>::Dequeue()       // Deletefirst
{
    T no;

    if(Count == 0)
    {
        cout<<"Queue is empty"<<endl;
        return;
    }

    no = Head -> data;
    struct node<T> *temp = Head;
    Head = Head->next;
    delete temp;       
    
    Count--;
    cout<<"Removed element is : "<<no<<endl;
}

template<class T>
void Queue<T>::Display()
{
    cout<<"Elements from Queue are : "<<endl;
    struct node<T> *temp = Head;
    while(temp != NULL)
    {
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

template<class T>
int Queue<T>::CountNode()
{
    return Count;
}

