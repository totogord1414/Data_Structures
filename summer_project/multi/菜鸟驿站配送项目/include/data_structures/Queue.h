#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <stdexcept>

namespace data_structures {

    template <typename T>
    class CircularQueue {
    private:
        std::vector<T> data;
        int head;
        int tail;
        int count;
        int capacity;

    public:
        // Constructor with initial capacity
        CircularQueue(int size = 100) : capacity(size), head(0), tail(0), count(0) {
            data.resize(capacity);
        }

        void enqueue(const T& element) {
            if (count == capacity) {
                std::vector<T> newData(capacity * 2);
                for (int i = 0; i < count; ++i) {
                    newData[i] = data[(head + i) % capacity];
                }
                data = std::move(newData);
                head = 0;
                tail = count;
                capacity *= 2;
            }
            data[tail] = element;
            tail = (tail + 1) % capacity;
            count++;
        }

        void dequeue() {
            if (isEmpty()) {
                throw std::out_of_range("Queue is empty, cannot dequeue.");
            }
            head = (head + 1) % capacity;
            count--;

            if (count > 0 && count <= capacity / 4 && capacity > 100) {
                int newCapacity = capacity / 2;
                std::vector<T> newData(newCapacity);
                for (int i = 0; i < count; ++i) {
                    newData[i] = data[(head + i) % capacity];
                }
                data = std::move(newData);
                head = 0;
                tail = count;
                capacity = newCapacity;
            }
        }

        T& front() {
            if (isEmpty()) {
                throw std::out_of_range("Queue is empty, cannot get front.");
            }
            return data[head];
        }

        const T& front() const {
            if (isEmpty()) {
                throw std::out_of_range("Queue is empty, cannot get front.");
            }
            return data[head];
        }

        bool isEmpty() const {
            return count == 0;
        }

        int size() const {
            return count;
        }
    };

}

#endif 