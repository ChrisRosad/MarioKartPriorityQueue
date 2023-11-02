/*
* Name: Christopher Rosado, 2001956343, Assignment six
* Description: The priority Queue class uses a set of functions
* to push items into the queue and popping the front item 
* of the priority queue. Throughout the process of inputing 
* items into the priority queue, the functions will work 
* together to ensure that the items are within their proper
* priority at all times. 
* Input: an item that matches the dynamic array allocation
* Output: The front node in the array.
*/
#include "priorityQ.h"
#include <cstdlib>
using namespace std;
//Change all of the pointer values ex: line 88 & 65
//left child index * 2 + 1 Right Child: index * 2 + 2
/* Description */
/*
* function_identifier: priorityQ()
* parameters: none
* description: constructor will set the values
* to their base and the heap array will allocate 
* a new array of size capacity.
* return value: none
*/
template <class t1, class t2>
priorityQ<t1, t2>::priorityQ() 
{
    size = 0;
    capacity = 5;
    heapArray = new priorityType[capacity];
}

/* Description */
/*
* function_identifier: priorityQ(const priorityQ<t1, t2>& copy)
* parameters: const priorityQ<t1, t2>& copy
* description: The copy constructor will set the values of *this
* to be equal to copy's values. Once that is complete the function
* will deep copy all of the values from copy.heaparray to 
* this->heaparray.
* return value: none
*/
template <class t1, class t2>
priorityQ<t1, t2>::priorityQ(const priorityQ<t1, t2>& copy) 
{
    this->size = copy.size;
    this->capacity = copy.capacity;
    this->itemToPQ = copy.itemToPQ;
    this->heapArray = new priorityType [this->capacity];
    for(int i = 0; i < copy.capacity; i++)
        this->heapArray[i] = copy.heapArray[i];
    
}

/* Description */
/*
* function_identifier: operator=(const priorityQ<t1, t2>& rhs)
* parameters: const priorityQ<t1, t2>& rhs
* description: The assignment overload is used so that 
* the user can have a simpler time with copying array allocated 
* priority queues to other priority queues within main. 
* this function will clean all of the values in *this and will 
* replace those values with the values within rhs. 
* return value: *this
*/
template <class t1, class t2>
const priorityQ<t1, t2>& priorityQ<t1, t2>::operator=(const priorityQ<t1, t2>& rhs)
{
    if (this != &rhs)
    {
        delete [] this->heapArray;
        this->size = rhs.size;
        this->capacity = rhs.capacity;
        this->itemToPQ = rhs.itemToPQ;
        this->heapArray = new priorityType [this->capacity];
        for(int i = 0; i < this->capacity; i++)
            this->heapArray[i] = rhs.heapArray[i];
    }

    return *this;
}

/* Description */
/*
* function_identifier: ~priorityQ()
* parameters: none
* description: will reset all the sizes to zero and will deallocate the heaparray
* return value: none
*/
template <class t1, class t2>
priorityQ<t1, t2>::~priorityQ()
{
    capacity = 0;
    size = 0;
    delete [] heapArray;
}

/* Description */
/*
* function_identifier: push_back(const t1& key, const t2& priority)
* parameters: const t1& key, const t2& priority
* description: The push_back function is meant to push the value
* into the priority queue and then use bubbleUp function to 
* place the value within the correct location within the priority
* queue. Though first the function will consistently check the size 
* of the heaparray to ensure that it is at a size that it can take 
* in the key and priority into a new node. Then it will create 
* a priorityType value to save key and priority and inserts it into 
* the heaparray. Once complete it will call bubbleUp to place it in
* the correct location
* return value: none
*/
template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& priority)
{
       if(size == capacity){
        size_t NewCapacity = 0;
        NewCapacity = capacity * 2;
        priorityType *Temp = new priorityType[NewCapacity];
        for(int i = 0; i < capacity; i++)
            Temp[i] = heapArray[i];
        delete [] heapArray;
        heapArray = Temp;
        Temp = nullptr;
        capacity = NewCapacity;
    }
    priorityType Traversal;
    Traversal.key = key;
    Traversal.priority = priority; 
    heapArray[size++] = Traversal;
    bubbleUp(size - 1);
}

/* Description */
/*
* function_identifier: pop_front()
* parameters: none
* description: The function will first grab the previous
* top of the queue and set the its location within the hashmap to a 
* garbage value, ensenuating that it is no longer apart of the array.
* The it will set the last value within heapArray to be the first value
* and then will call the bubbledown function if the heapArray size is not already at 0.
* return value: none
*/
template <class t1, class t2>
void priorityQ<t1, t2>::pop_front()
{
priorityType Pop, PrevTop;
PrevTop = heapArray[0];
itemToPQ[PrevTop.key] = -1; //sets previous top key to be -1 as garbage val

Pop = heapArray[--size]; //sets Pop to bottom most element
heapArray[0] = Pop; //sets first index equal to last element
itemToPQ[Pop.key] = 0; //updates hashmap 
if(size != 0)
    bubbleDown(0);
}

/* Description */
/*
* function_identifier: decrease_priority(const t1& key, const t2& priority)
* parameters: const t1& key, const t2& priority
* description: The decrease_priority function first finds the index of the 
* key value using the hashmap. Once the Index is found the function creates
* a new priorityType value to take in the elements within the heapArray[Index]
* and then will swap the priority value and reinsert it into the heapArray
* and will call bubbleUp, ensuring that the change in priority leads the 
* element to the correct location.
* return value: none
*/
template <class t1, class t2>
void priorityQ<t1, t2>::decrease_priority(const t1& key, const t2& priority)
{

size_t Index = itemToPQ[key];
priorityType SwapPriorities;
SwapPriorities = heapArray[Index];
SwapPriorities.priority = priority;
heapArray[Index] = SwapPriorities;
bubbleUp(Index);
}

/* Description */
/*
* function_identifier: get_front_priority()
* parameters: none
* description:  returns the top priority value 
* from the heapArray
* return value: t2
*/
template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
    priorityType node = heapArray[0];
    return node.priority;
}

/* Description */
/*
* function_identifier: get_front_key() 
* parameters: none
* description:  returns the top key value 
* from the heapArray
* return value: t1
*/
template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
    priorityType node = heapArray[0];
     return node.key;
}

/* Description */
/*
* function_identifier: isEmpty()
* parameters: none
* description: returns if size is equal to zero
* return value: boolean
*/
template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{
    return size == 0;
}

/* Description */
/*
* function_identifier: bubbleUp(std::size_t index)
* parameters: std::size_t index
* description: The bubbleUp function is a recursive 
* function that will find the parent index of the index
* given and will compare it to see if the parent's priority 
* value is less than the child's priority value. If it 
* is then a swap will ensue, updating the location of the 
* oldparents index value within the hashmap and the program 
* will recursively call itself. The function will stop calling 
* itself whenever index is equal to zero or if the parent priority
* is bigger than the child's priority. Setting the childNodes
* index value within the hashmap.  
* return value: none
*/
template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
    priorityType ChildNode = heapArray[index];

    if(index == 0){
        itemToPQ[ChildNode.key] = index;
        return;
    }
    
    size_t ParentIndex = (index - 1) / 2;
    priorityType ParentNode = heapArray[ParentIndex];
    
    if(ParentNode.priority > ChildNode.priority){
        priorityType Swap = ParentNode; //setting up swap 

        ParentNode = ChildNode;
        
        heapArray[ParentIndex] = ParentNode;

        ChildNode = Swap;

        heapArray[index] = ChildNode;

        itemToPQ[ChildNode.key] = index;
        return bubbleUp(ParentIndex);
    }else{
        itemToPQ[ChildNode.key] = index;
    }        

    return;
}

/* Description */
/*
* function_identifier: bubbleDown(std::size_t index)
* parameters: std::size_t index
* description: The function will first get the right and left
* childs indices. Then it will check the validity of those indices
* with the size of the array. If leftIndex is bigger then 
* the current index has no children and will return immediately.
* Then the function checks if both childrens priorities are greater than
* the parent, if it is then the function will set the parents hashmap
* index value to the current index and will return. 
* If only the right child is bigger than the size of the array 
* then the current index only has one child and will do the swap
* if necessary and will return with the proper hashmap index values.
* After these base checks the general cases are comparing which child 
* node is bigger and will do a swap with the smaller child and the parent,
* setting the previous child nodes index to the current index. Once the swap
* properly down, the function will recursively call itself but with 
* the smaller childs index value as the parameter. 
* return value: none
*/
template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
    priorityType LeftChild, RightChild, Parent, Swap;
    size_t LeftIndex = index * 2 + 1, RightIndex = index * 2 + 2;
    
    Parent = heapArray[index];

    if(LeftIndex > (size - 1)){
        itemToPQ[Parent.key] = index;
        return;
    }

    LeftChild = heapArray[LeftIndex];
    RightChild = heapArray[RightIndex];

    if(LeftChild.priority > Parent.priority && RightChild.priority > Parent.priority){
        itemToPQ[Parent.key] = index;
        return;
    }
    
    if(RightIndex > (size - 1)){
        if(LeftChild.priority < Parent.priority){
            Swap = LeftChild;
            LeftChild = Parent;
            Parent = Swap;

            heapArray[index] = Parent;
            heapArray[LeftIndex] = LeftChild;
        }
        itemToPQ[Parent.key] = index;
        return;
    }


    if(LeftChild.priority < RightChild.priority){
        Swap = LeftChild;
        LeftChild = Parent;
        Parent = Swap;
        heapArray[index] = Parent;
        heapArray[LeftIndex] = LeftChild;
        itemToPQ[Parent.key] = index;
        return bubbleDown(LeftIndex);
    }

    if(RightChild.priority < LeftChild.priority){
        Swap = RightChild;
        RightChild = Parent;
        Parent = Swap;
        heapArray[index] = Parent;
        heapArray[RightIndex] = RightChild;
        itemToPQ[Parent.key] = index;
       return bubbleDown(RightIndex);
    }

    itemToPQ[Parent.key] = index;
    return;
}