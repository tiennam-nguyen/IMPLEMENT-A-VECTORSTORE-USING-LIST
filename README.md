VectorStore Implementation Using List
Overview

This project implements a VectorStore using two fundamental data structures:

Singly Linked List (SinglyLinkedList): Each vector is represented as a singly linked list.

Dynamic Array List (ArrayList): The entire collection of vectors is managed by a dynamic array list.

This design simulates the storage and retrieval mechanisms of vectors, similar to the way modern database systems manage vector data.

Features

Singly Linked List: Each vector is represented as a singly linked list of elements.

Dynamic Array List: The collection of vectors is managed by a dynamic array list, providing efficient resizing with a growth factor of 3/2.

Key Functionalities

All methods are implemented correctly.

Memory Management: Proper constructors, destructors, and assignment operators are in place to ensure efficient memory handling.

Exception Handling: The system includes proper exception handling with clear and informative messages for edge cases.

Iterator Implementation: A fully functional iterator is implemented for traversing vectors in the store.

Growth Strategy: The dynamic array list uses a 3/2 growth factor to handle resizing efficiently.

Bounds Checking: Proper bounds checking is implemented to prevent accessing out-of-bounds elements.

Data Structures
1. Singly Linked List (SinglyLinkedList)

This is the fundamental building block for representing vectors.

Each vector is a list of elements, stored sequentially with pointers to the next element.

Operations on the list include insertion, deletion, and traversal of elements.

2. Dynamic Array List (ArrayList)

The ArrayList stores a collection of vectors (each represented by a singly linked list).

It dynamically resizes using a growth factor of 3/2, allowing efficient memory usage and access.

Operations supported include adding vectors, resizing the internal array, and accessing vectors via indexing.

Installation
Prerequisites

C++ Compiler (GCC, Clang, etc.)