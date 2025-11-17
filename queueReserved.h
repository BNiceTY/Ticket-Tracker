#ifndef H_QUEUERESERVED 
#define H_QUEUERESERVED

#include <cassert>

template <class Type>
class queueReserved
{
public:
    // Assignment operator: copies one queueReserved into another.
    const queueReserved<Type>& operator=(const queueReserved<Type>& otherQueue);

    // Returns true if the queue has no elements.
    bool isEmptyQueue() const;

    // Returns true if the queue is full (using the reserved-slot method)
    bool isFullQueue() const;

    // Initializes Queue to default state (empty)
    void initializeQueue();

    // Returns the element at the front of the queue 
    Type front() const;

    // Returns the element at the back of the queue 
    Type back() const;

    // Adds a new element to the back of the queue.
    void addQueue(const Type& queueElement);

    // Removes the element at the front of the queue.
    void deleteQueue();

    // Constructor
    queueReserved(int queueSize = 100);

    // Copy constructor
    queueReserved(const queueReserved<Type>& otherQueue);

    // Destructor
    ~queueReserved();

private:
    int maxQueueSize;  
    int queueFront;     // Index of the front (oldest) element
    int queueRear;     
    Type* list;         
};


// Constructor
template <class Type>
queueReserved<Type>::queueReserved(int queueSize)
{
    if (queueSize <= 1)               
        queueSize = 100;              

    maxQueueSize = queueSize;          
    queueFront = 0;                    // Start the front index at 0
    queueRear = 0;                     // Start the rear index at 0 also  (queue empty)
    list = new Type[maxQueueSize];     // Allocate the array of 'Type' with maxQueueSize slots
}

// Copy 
template <class Type>
queueReserved<Type>::queueReserved(const queueReserved<Type>& otherQueue)
{
    maxQueueSize = otherQueue.maxQueueSize;    
    queueFront   = otherQueue.queueFront;      
    queueRear    = otherQueue.queueRear;       

    list = new Type[maxQueueSize];             

    for (int i = 0; i < maxQueueSize; ++i)
        list[i] = otherQueue.list[i];
}

// Destructor
template <class Type>
queueReserved<Type>::~queueReserved()
{
    delete[] list;
    list = nullptr; 
}

// Assignment operator
template <class Type>
const queueReserved<Type>&
queueReserved<Type>::operator=(const queueReserved<Type>& otherQueue)
{
    if (this != &otherQueue)
    {
        if (maxQueueSize != otherQueue.maxQueueSize)
        {
            delete[] list;                         
            maxQueueSize = otherQueue.maxQueueSize;
            list = new Type[maxQueueSize];         
        }

        queueFront = otherQueue.queueFront;        
        queueRear  = otherQueue.queueRear;         

        for (int i = 0; i < maxQueueSize; ++i)
            list[i] = otherQueue.list[i];
    }

    return *this;                      
}

// Check if the queue is empty
template <class Type>
bool queueReserved<Type>::isEmptyQueue() const
{
    return (queueFront == queueRear);
}

// Check if the queue is full (reserved-slot method)
template <class Type>
bool queueReserved<Type>::isFullQueue() const
{
    return ( (queueRear + 1) % maxQueueSize == queueFront );
}

// Reset the queue to empty
template <class Type>
void queueReserved<Type>::initializeQueue()
{
    queueFront = 0;
    queueRear  = 0;
}

// Access the front element
template <class Type>
Type queueReserved<Type>::front() const
{
    assert(!isEmptyQueue());
    return list[queueFront];           // Return the element at the front 
}

// Access the back element
template <class Type>
Type queueReserved<Type>::back() const
{
    assert(!isEmptyQueue());           
    int lastIndex = (queueRear - 1 + maxQueueSize) % maxQueueSize;
    return list[lastIndex];            // Return the most recently inserted element
}

// Add an element to the back of the queue
template <class Type>
void queueReserved<Type>::addQueue(const Type& queueElement)
{
    assert(!isFullQueue());            // Make sure we are not overflowing the queue

    list[queueRear] = queueElement;    // Store the new element at queueRear
    queueRear = (queueRear + 1) % maxQueueSize;
}

// Remove the front element
template <class Type>
void queueReserved<Type>::deleteQueue()
{
    assert(!isEmptyQueue());           // Make sure queue is not empty
    queueFront = (queueFront + 1) % maxQueueSize; // Move front forward (circularly)
}

#endif // H_QUEUERESERVED