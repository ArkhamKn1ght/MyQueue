#include <iostream>

template<typename T>
class MyQueue{
public:
    MyQueue(){
        size = 0;
        capacity = 5;
        data = new T[capacity];
        front = 0;
        rear = -1;
        std::cout << "Default constructor" << std::endl;
    }
    MyQueue(const MyQueue& obj) {
        this->size = obj.size;
        this->capacity = obj.capacity;
        this->front = obj.front;
        this->rear = obj.rear;
        this->data = new T[this->capacity];
        for(size_t i = 0; i < obj.size; i++) {
            this->data[i] = obj.data[i];
        }
        std::cout << "Copy constructor" << std::endl;

    }
    MyQueue(MyQueue&&obj) {
        
        this->data = obj.data;
        this->size = obj.size;
        this->capacity = obj.capacity;
        this->front = obj.front;
        this->rear = obj.rear;

        obj.data = nullptr;
        obj.size = 0;
        obj.capacity = 0;
        obj.front = 0;
        obj.rear = -1;

        std::cout << "Move constructor" << std::endl;
        
        
    }
    MyQueue& operator=(const MyQueue& rhs)  {
        if(this != &rhs && rhs.size) {
            if(rhs.size > this->capacity) {
                delete[] this->data;
                
                this->capacity = rhs.capacity;
                this->data = new T[this->capacity];
            }
            this->size= rhs.size;
            this->front = rhs.front;
            this->rear = rhs.rear;
            for(int i = front; i !=  this->rear; i++) {
                    this->data[i % this->capacity] = rhs.data[i % this->capacity]; 
                }
        }
        std::cout << "Copy assignment operator" << std::endl;
        return *this;
    }
    MyQueue& operator=( MyQueue&& rhs) noexcept {
        if(this != &rhs) {
            delete[] this->data;
            
            this->data = rhs.data;
            this->size = rhs.size;
            this->capacity = rhs.capacity;
            this->front = rhs.front;
            this->rear = rhs.rear;

            rhs.data = nullptr;
            rhs.capacity = 0;
            rhs.size = 0;
            rhs.front = 0;
            rhs.rear = -1;
        }
        std::cout << "Move assignment operator" << std::endl;
        return *this;
    }
    ~MyQueue() {
        delete[] data;
    }

    void enqeue(const T& tempData) {

        if(!(capacity > size)) {
            std::cout << "===RESIZE===" <<  std::endl;
            T* tempArr = new T[capacity];
            int i = front;
            int j = 0;
            while(i != rear) {
                tempArr[j] = data[i % capacity];
                j++;
                i= (i+1) % capacity;
            }
            tempArr[j] = data[rear]; // following up last idx, the data[rear]

            delete[] data; 

            capacity +=5 ;
            data = new T[capacity];
            for(int i = 0; i < static_cast<int>(size); i++) {
                data[i] = tempArr[i];
            }
            front = 0;
            rear = size -1;
            delete[] tempArr;
        }
        std::cout << "Write " << tempData << " to " << (rear + 1) % capacity << std::endl;
        rear = (rear + 1) % capacity;
        data[rear] = tempData;
        size++; 
        
    }

    T dequeue() {
        if(size > 0) {
            T tempData = data[front];
            front = (front + 1) % capacity;
            size--;
            return tempData;
        } else {
            std::cerr << "Queue is empty" << std::endl;
            return T();
        }
    }

    size_t getSize() {
        return size;
    }
private:
    T* data;
    size_t size;
    size_t capacity;
    int front;
    int rear;
};



int main() {
    MyQueue<int> testQueue;
    testQueue.enqeue(1);
    testQueue.enqeue(2);
    testQueue.enqeue(3);
    testQueue.enqeue(4);
    testQueue.enqeue(5);
    testQueue.enqeue(6);
    testQueue.enqeue(7);
    testQueue.dequeue();
    testQueue.dequeue();
    testQueue.dequeue();
    testQueue.enqeue(8);
    testQueue.enqeue(9);
    testQueue.enqeue(10);
    testQueue.enqeue(11);
    testQueue.enqeue(12);
    testQueue.enqeue(13);
    testQueue.enqeue(14);

    MyQueue<int> sadoMazoQueue;
    sadoMazoQueue = std::move(testQueue);

    while(sadoMazoQueue.getSize()) {
        std::cout << sadoMazoQueue.dequeue();
    }
    std::cout << std::endl;
    return 0;
}