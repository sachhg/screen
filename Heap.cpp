#include "Heap.h"
#include <stdexcept>


namespace {

    void filterUp(Heap::Entry* data, size_t index){

        while (index > 0) {

            size_t parent = (index - 1) / 2;

            if (data[index].score < data[parent].score){

                Heap::Entry temp = data[index];
                data[index] = data[parent];
                data[parent] = temp;
                index = parent;

            } else {

                break;
            }


        }
    }


    void filterDown(Heap::Entry* data, size_t count, size_t index){

        while (true) {

            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t smallest = index;


            if (left < count && data[left].score < data[smallest].score) {

                smallest = left;
            }

            if (right < count && data[right].score < data[smallest].score){

                smallest = right;
            }

            if (smallest != index){

                Heap::Entry temp = data[index];
                data[index] = data[smallest];
                data[smallest] = temp;
                index = smallest;

            } else {

                break;
            }
        }
    }

}




//constructor
Heap::Heap(size_t capacity) : mData(new Entry[capacity]), mCapacity(capacity), mCount(0) {}

//copy constructor
Heap::Heap(const Heap& other) : mData(new Entry[other.mCapacity]), mCapacity(other.mCapacity), mCount(other.mCount) {

    for (size_t i = 0; i < mCount; ++i){

        mData[i] = other.mData[i];

    }

}


//move constructor
Heap::Heap(Heap&& other) : mData(other.mData), mCapacity(other.mCapacity), mCount(other.mCount) {

            other.mData = NULL;
            other.mCapacity = 0;
            other.mCount = 0;

}


//destructor
Heap::~Heap() {

    delete[] mData;

}


//getter function for capacity
size_t Heap::capacity() const {

    return mCapacity;

}


//getter for count
size_t Heap::count() const {

    return mCount;

}


const Heap::Entry& Heap::lookup(size_t index) const {

    if (index >= mCount) {

        throw std::out_of_range("Index out of range");

    }
    return mData[index];

}



Heap::Entry Heap::pop() {

    if (mCount == 0){

        throw std::underflow_error("Cannot pop from empty heap");
    }

    Entry top = mData[0];
    mCount--;

    
    if (mCount > 0) {

        mData[0] = mData[mCount];
        filterDown(mData, mCount, 0);
    }

    return top;

}


void Heap::push(const std::string& value, float score) {

    if (mCount >= mCapacity){

        throw std::overflow_error("Heap capacity reached");
    }

    mData[mCount] = {value, score};
    mCount++;
    filterUp(mData, mCount - 1);

}


Heap::Entry Heap::pushpop(const std::string& value, float score) {

    if (mCount == 0){

        throw std::underflow_error("Cannot pushpop empty heap");
    }

    Entry removed = mData[0];
    mData[0] = {value, score};
    filterDown(mData, mCount, 0);
    return removed;

}


const Heap::Entry& Heap::top() const {

    if (mCount == 0) {

        throw std::underflow_error("Heap is empty");
        
    }
    return mData[0];
    
}
