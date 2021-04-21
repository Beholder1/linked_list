//Kamil W³odarczyk
#include <iostream>

using namespace std;

enum class EXCEPTION_CODE
{
    listEmpty,
    nonExisting
};

void seeExceptions(EXCEPTION_CODE error)
{
    switch (error) {
    case EXCEPTION_CODE::listEmpty:
        std::cerr << "Lista jest pusta!" << std::endl;
        break;
    case EXCEPTION_CODE::nonExisting:
        std::cerr << "Element o takim indexie nie istnieje!" << std::endl;
        break;
    default:
        std::cerr << "Nieznany blad!";
        break;
    }
}
class Element {
private:
    int v;
    Element* next;

public:
    Element()                                        //tworzy pusty element
    {
        v = NULL;
        next = NULL;
    }
    Element(int x, Element* next, Element* prev)    //tworzy element przechowuj¹cy x
    {
        prev->next = this;
        this->next = next;
        v = x;
    }
    int getValue()                                    //zwraca wartoœæ
    {
        return v;
    }
    void setValue(int v)                            //ustawia waroœæ v
    {
        this->v = v;
    }
    Element* getNext()                                //zwraca pozycjê nastêpnego elementu
    {
        return next;
    }
    void setNext(Element* p)                        //ustawia p jako nastêpny element
    {
        next = p;
    }
};


class LinkedList {
private:
    Element* head;                    //pozycja pierwszego elementu
    Element* tail;                    //pozycja ostatniego elementu
    int size;

public:
    LinkedList()                                //tworzy pust¹ listê
    {
        head = NULL;
        tail = NULL;
        size = 0;

    }
    bool empty()                                //zwraca prawdê jeœli lista pusta, fa³sz w przeciwnym przypadku
    {
        if (size == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int getSize()                                //zwraca wielkoœæ listy (liczbê elementów w liœcie)
    {
        return size;
    }
    Element* getFirst()                         //zwraca pozycjê (wskaŸnik do) pierwszego elementu listy
    {
        if (empty())
        {
            throw EXCEPTION_CODE::listEmpty;
        }
        else
        {
            return head;
        }
    }
    Element* getLast()                               //zwraca pozycjê (wskaŸnik do) ostatniego elementu listy
    {
        if (empty())
        {
            throw EXCEPTION_CODE::listEmpty;
        }
        else
        {
            return tail;
        }
    }
    Element* getNext(Element* p)               //zwraca pozycjê (wskaŸnik do) nastêpniego elementu listy
    {
        if (p)
        {
            return p->getNext();
        }
        else
        {
            throw EXCEPTION_CODE::nonExisting;
        }
    }
    Element* getPrev(Element* p)              //zwraca pozycjê (wskaŸnik do) poprzedniego elementu listy
    {
        if (p)
        {
            Element* tmp = getFirst();
            for (int i = 0; i < getSize() - 1; i++)
            {
                if (getNext(tmp) == p)
                {
                    return tmp;
                }
                else
                {
                    tmp = getNext(tmp);
                }
            }
        }
        else
        {
            throw EXCEPTION_CODE::nonExisting;
        }
    }
    int retrive(Element* p)                   //zwraca element (wartoœæ) z pozycji (wskazywanej przez) p
    {
        if (p)
        {
            return p->getValue();
        }
        else
        {
            throw EXCEPTION_CODE::nonExisting;
        }
    }
    Element* locate(int x)                         //zwrac pozycjê pierwszego wyst¹pienia elementu x, NULL jeœli x nie wystêpuje
    {
        Element* tmp = getFirst();
        while (tmp != NULL)
        {
            if (retrive(tmp) == x)
            {
                return tmp;
            }
            else
            {
                tmp = getNext(tmp);
            }
        }
        return NULL;
    }
    void append(int x)                            //wstawia element z x na koñcu listy
    {
        Element* tmp = new Element();
        tmp->setValue(x);

        if (empty())
        {
            head = tmp;
        }
        else
        {
            tail->setNext(tmp);
        }
        tail = tmp;
        size++;
    }
    void insert(Element* p, int x)              //wstawia element z wartoœci¹ x na pozycjê (wskazywan¹ przez) p
    {
        if (!p)
        {
            throw EXCEPTION_CODE::nonExisting;
        }
        if (!empty())
        {
            Element* tmp = new Element();
            tmp->setValue(x);
            if (p == getFirst())
            {
                tmp->setNext(p);
                head = tmp;
            }
            else if (getNext(p) || p == getLast())
            {
                tmp->setNext(p);
                getPrev(p)->setNext(tmp);
            }
            else
            {
                getLast()->setNext(tmp);
                tail = tmp;
            }
            size++;
        }
        else
        {
            append(x);
        }
    }
    void del(Element* p)                            //usuwa element z pozycji (wskazywaniej przez) p
    {
        if (!empty()&&p)
        {
            if (p == getFirst())
            {
                head = getFirst()->getNext();
                if (!head)
                {
                    tail = NULL;
                }
            }
            else
            {
                Element* prev = getPrev(p);
                prev->setNext(getNext(p));
                if (!getNext(prev))
                {
                    tail = prev;
                }
            }

            delete p;
            size--;
        }
        else if (empty())
        {
            throw EXCEPTION_CODE::listEmpty;
        }
        else
        {
            throw EXCEPTION_CODE::nonExisting;
        }
    }
    void clear()                    //usuwa ca³¹ listê
    {
        while (!empty())
        {
            del(getFirst());
        }
    }
    friend ostream& operator<<(ostream& out, LinkedList* l); //wypisuje elementu listy           
    void insert(int p, int x)            //wstawia element z x na pozycjê (integer) p (licz¹c od 0)
    {

        if (p > size - 1 || p < 0)
        {
            throw EXCEPTION_CODE::nonExisting;
        }
        if (size <= p)
        {
            append(x);
        }
        else
        {
            Element* tmp = getFirst();
            if (p > 0)
            {
                for (int i = 0; i < p; i++)
                {
                    tmp = getNext(tmp);
                }
            }
            insert(tmp, x);
        }
    }
    void del(int p)                    //usuwa element z pozycji (integer) p (licz¹c od 0)
    {
        if (empty())
        {
            throw EXCEPTION_CODE::listEmpty;
        }

        if (p > size - 1 || p < 0)
        {
            throw EXCEPTION_CODE::nonExisting;
        }
        Element* tmp = getFirst();

        if (p > 0)
        {
            for (int i = 0; i < p; i++)
            {
                tmp = getNext(tmp);
            }
        }
        del(tmp);
    }
    ~LinkedList()
    {
        clear();
        delete head;
        delete tail;
    }
};
std::ostream& operator<<(std::ostream& out, LinkedList& l)
{
    Element* tmp = l.getFirst();
    while (tmp != NULL)
    {
        out << l.retrive(tmp) << " ";
        tmp = l.getNext(tmp);
    }
    return out;
};
//Zadanie 5.2
class SortedLinkedList : public LinkedList
{
public:
    using LinkedList::LinkedList;

    void insertSorted(int x)
    {
        int position = -1, i = 0;

        if (empty())
        {
            append(x);
        }
        else
        {
            Element* tmp = getFirst();

            while (tmp != NULL)
            {
                if (x <= retrive(tmp))
                {
                    position = i;
                    break;
                }

                i++;
                tmp = getNext(tmp);
            }

            if (position != -1)
            {
                insert(position, x);
            }
            else
            {
                append(x);
            }
        }
    }
};
int main()
{
    try
    {
        //Zadanie 5.1 - test
        cout << endl << "Zadanie 5.1 - test" << endl;

        LinkedList* a = new LinkedList();
        cout << endl << "empty(): 1 - " << a->empty();                                                                      //testowanie metody empty()
        cout << endl << "getSize():  0 - " << a->getSize();                                                                 //testowanie metody getSize()
        cout << endl << "append(4): 4 - "; a->append(4); cout << " " << *a;                                                 //testowanie metody append()
        cout << endl << "append(3): 4 3 - "; a->append(3); cout << " " << *a;                                               //testowanie metody append()
        cout << endl << "append(6): 4 3 6 - "; a->append(6); cout << " " << *a;                                             //testowanie metody append()
        cout << endl << "append(2): 4 3 6 2 - "; a->append(2); cout << " " << *a;                                           //testowanie metody append()
        cout << endl << "append(7): 4 3 6 2 7 - "; a->append(7); cout << " " << *a;                                         //testowanie metody append()
        cout << endl << "retrive(a->getFirst()): 4 - " << a->retrive(a->getFirst());                                        //testowanie metody retrive() oraz getFirst()
        cout << endl << "retrive(a->getLast()): 7 - " << a->retrive(a->getLast());                                          //testowanie metody retrive() oraz getLast()
        cout << endl << "locate(3), retrive(el): 3 - "; Element* el = a->locate(7); cout << a->retrive(el);                 //testowanie metody locate() oraz retrive()
        //cout << endl << "retrive(a->getNext(el)): 6 - " << a->retrive(a->getNext(el));                                      //testowanie metody retrive() oraz getNext()
        cout << endl << "retrive(a->getPrev(el)): 4 - " << a->retrive(a->getPrev(el));                                      //testowanie metody retrive() oraz getPrev()
        cout << endl << "insert(el, 1): 4 1 3 6 2 7 - ";  a->insert(el, 1); cout << " " << *a;                              //testowanie metody insert()
        cout << endl << "del(el): 4 1 6 2 7 - ";  a->del(el); cout << " " << *a;                                            //testowanie metody del()
        cout << endl << "insert(3, 3): 4 1 6 3 2 7 - ";  a->insert(3, 3); cout << " " << *a;                                //testowanie metody insert()
        cout << endl << "del(2): 4 1 3 2 7 - ";  a->del(2); cout << " " << *a;                                              //testowanie metody del()
        cout << endl << "clear(), append(4): - ";  a->clear(); a->append(4); cout << " " << *a;                             //testowanie metody clear() oraz append()

        //Zadanie 5.2 - test
        cout << endl << "Zadanie 5.2 – test" << endl;
        SortedLinkedList* b = new SortedLinkedList();
        cout << endl << "insertSorted(4): 4 - "; b->insertSorted(4); cout << " " << *b;                                     //testowanie metody insertSorted()
        cout << endl << "insertSorted(3): 3 4 - "; b->insertSorted(3); cout << " " << *b;                                   //testowanie metody insertSorted()
        cout << endl << "insertSorted(6): 3 4 6 - "; b->insertSorted(6); cout << " " << *b;                                 //testowanie metody insertSorted()
        cout << endl << "insertSorted(2): 2 3 4 6 - "; b->insertSorted(2); cout << " " << *b;                               //testowanie metody insertSorted()
        cout << endl << "insertSorted(7): 2 3 4 6 7 - "; b->insertSorted(7); cout << " " << *b;                             //testowanie metody insertSorted()
        cout << endl << "insertSorted(1): 1 2 3 4 6 7 - "; b->insertSorted(1); cout << " " << *b;                           //testowanie metody insertSorted()


    }
    catch (EXCEPTION_CODE error)
    {
        seeExceptions(error);
    }
    return 0;
}

