# Real World Examples & Research

## Task 1: Read A5 and Identify Difficult Parts

Read the A5 handout in detail and begin working on it. Then identify and describe three parts of the assignment you understand the least. Below describe:

1. Replace <title> with the name of the part.
2. What concepts from this part do you understand?
3. How and why is it difficult to understand?

### Part 1: Concept of malloc and free

I do get what each function does. I also get the concept of dynamic memory allocation. But using it in a program is kind of confusing. I am getting address sanitizer issues in `decompress_board` function and I don't know where I am supposed to free the address or if I need to free it.

### Part 2: Pointers in C

The concept of pointers are always confusing. It is used to points to the memory address and does indirect referencing to a value. I find using it difficult mostly during memory management which is needed for this assignment.

### Part 3: Decompression using strtok

I get what the handout is trying to tell us by using `strtok` for compressing the strings. But since the string is big and a lot of error handling is needed. I am struggling with it.

## Task 2: Two Real-World Examples / Analogies

For the concept of "Dynamic Memory Allocation" and one other technical concept from A5, find real-world examples or an analogy to explain it. Think of this as a practice for the final presentation in this class. Include your source from where you found your real-world example or an analogy.

### Concept 1: Dynamic Memory Allocation

Dynamic memory allocation is akin to renting an apartment: just as you might initially lease a small space and later upgrade to a larger one as your needs grow, in programming, dynamic memory allocation allows for the allocation and deallocation of memory during runtime. It enables programs to adjust their memory usage based on changing requirements, allocating more memory as needed and releasing it when no longer required, offering flexibility and efficiency in memory management.

### Concept 2: Linked List

A linked list can be compared to a train consisting of multiple cars where each car is connected to the next one by a coupling. In this analogy, each car represents a node in the linked list, containing both data and a reference (or pointer) to the next node. The first car serves as the head of the train, acting as the starting point of the linked list. To traverse the linked list, you start at the head and follow the couplings (pointers) from one car to the next until you reach the end. This flexibility allows for efficient insertion and removal of cars (nodes) anywhere along the train, without needing to rearrange the entire sequence, making it suitable for dynamic data structures where the size may change frequently.

> [!NOTE]
> Source: Chat GPT.
