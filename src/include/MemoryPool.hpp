#include <cstddef>
#include <new>
#include <stdexcept>
#include <utility>

template <typename T>
class MemoryPool
{
public:
    // poolSize: maximum number of objects in the pool
    MemoryPool(size_t poolSize)
        : poolSize(poolSize), objectSize(sizeof(T)), pool(nullptr), freeList(nullptr)
    {
        // Allocate a contiguous block of memory
        pool = new char[poolSize * objectSize];
        // Build the free list: each block points to the next one
        freeList = nullptr;
        for (size_t i = 0; i < poolSize; ++i)
        {
            Node *node = reinterpret_cast<Node *>(pool + i * objectSize);
            node->next = freeList;
            freeList = node;
        }
    }

    ~MemoryPool()
    {
        // Free the allocated block
        delete[] pool;
    }

    // Allocate memory and construct an object with placement new
    template <typename... Args>
    T *allocate(Args &&...args)
    {
        if (!freeList)
        {
            throw std::bad_alloc(); // or expand the pool if desired
        }
        Node *node = freeList;
        freeList = freeList->next;
        // Use placement new to construct the object in-place
        return new (node) T(std::forward<Args>(args)...);
    }

    // Call the destructor and add the node back to the free list
    void deallocate(T *ptr)
    {
        if (ptr)
        {
            ptr->~T();
            Node *node = reinterpret_cast<Node *>(ptr);
            node->next = freeList;
            freeList = node;
        }
    }

private:
    // Node used for the free list; it shares memory with T
    struct Node
    {
        Node *next;
    };

    size_t poolSize;   // total number of objects the pool can hold
    size_t objectSize; // size of each object (should equal sizeof(T))
    char *pool;        // pointer to the memory block
    Node *freeList;    // pointer to the head of the free list

    // Disallow copying
    MemoryPool(const MemoryPool &) = delete;
    MemoryPool &operator=(const MemoryPool &) = delete;
};
