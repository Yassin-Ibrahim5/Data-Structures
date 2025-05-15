#include <iostream>

using namespace std;

template<typename T>
class Stack
{
private:
    T *data;
    int capacity;
    int topIndex;

    void resize(int newCapacity);

public:
    Stack(int initialCapacity = 10);

    ~Stack();

    void push(T item);

    T pop();

    T top();

    bool isEmpty();

    int getSize();

};

template<typename T>
void Stack<T>::resize(int newCapacity)
{
    T *newData = new T[newCapacity];
    for (int i = 0; i <= topIndex; i++)
    {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template<typename T>
Stack<T>::Stack(int initialCapacity)
{
    capacity = initialCapacity;
    data = new T[capacity];
    topIndex = -1;
}

template<typename T>
Stack<T>::~Stack()
{
    delete[] data;
}

template<typename T>
void Stack<T>::push(T item)
{
    if (topIndex == capacity - 1)
    {
        resize(capacity * 2);
    }
    data[++topIndex] = item;
}

template<typename T>
T Stack<T>::pop()
{
    if (isEmpty())
    {
        cerr << "Stack is empty." << endl;
    }
    return data[topIndex--];
}

template<typename T>
T Stack<T>::top()
{
    if (isEmpty())
    {
        cerr << "Stack is empty." << endl;
    }
    return data[topIndex];
}

template<typename T>
bool Stack<T>::isEmpty()
{
    return topIndex == -1;
}

template<typename T>
int Stack<T>::getSize()
{
    return topIndex + 1;
}

//////////////////////////////////

class BrowserHistory
{
private:
    Stack<string> backStack;
    Stack<string> forwardStack;
public:
    BrowserHistory(string homepage);

    void visit(string url);

    string goBack();

    string goForward();

    string getCurrentUrl();
};

BrowserHistory::BrowserHistory(string homepage)
{
    backStack.push(homepage);
}

void BrowserHistory::visit(string url)
{
    while (!forwardStack.isEmpty())
    {
        forwardStack.pop();
    }
    backStack.push(url);
}

string BrowserHistory::goBack()
{
    if (backStack.getSize() > 1)
    {
        string current = backStack.top();
        backStack.pop();
        forwardStack.push(current);
    }
    return backStack.top();
}

string BrowserHistory::goForward()
{
    if (!forwardStack.isEmpty())
    {
        string next = forwardStack.top();
        forwardStack.pop();
        backStack.push(next);
        return next;
    }
    return backStack.top();
}

string BrowserHistory::getCurrentUrl()
{
    return backStack.top();
}

int main()
{
    BrowserHistory history("https://www.google.com");
    cout << "Initial url: " << history.getCurrentUrl() << endl;

    history.visit("https://wikipedia.org");
    cout << "Current url after visiting wikipedia.org: " << history.getCurrentUrl() << endl;

    history.visit("https://youtube.com");
    cout << "Current url after visiting youtube.com: " << history.getCurrentUrl() << endl;

    // first step back
    cout << "First step back: " << history.goBack() << endl;
    cout << "Current url after going back: " << history.getCurrentUrl() << endl;

    // second step back
    cout << "Second step back: " << history.goBack() << endl;
    cout << "Current url after going back: " << history.getCurrentUrl() << endl;

    // step forward
    cout << "Going forward: " << history.goForward() << endl;
    cout << "Current url after going forward: " << history.getCurrentUrl() << endl;

    history.visit("https://facebook.com");
    cout << "Current url after visiting facebook.com: " << history.getCurrentUrl() << endl;
    return 0;
}