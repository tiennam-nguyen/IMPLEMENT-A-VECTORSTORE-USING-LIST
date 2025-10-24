# Data Structures & Algorithms - Assignment 1: VectorStore Implementation

This repository contains the C++ implementation for Assignment 1 of the Data Structures and Algorithms course (CO2003) at Ho Chi Minh City University of Technology (HCMUT).

The primary goal of this assignment is to build a `VectorStore` from the ground up, utilizing custom-built, list-based data structures. This project demonstrates proficiency in Object-Oriented Programming (OOP), memory management, and the practical application of data structures.

The core components implemented are:
1.  **`ArrayList<T>`**: A dynamic array list.
2.  **`SinglyLinkedList<T>`**: A singly linked list.
3.  **`VectorStore`**: A vector database that uses the `ArrayList` and `SinglyLinkedList` to store and query high-dimensional vectors.

## Implemented Features

### 1. `ArrayList<T>`

A template-based dynamic array list class.
* [cite_start]**Dynamic Capacity:** Automatically expands capacity by a factor of 1.5 when full. [cite: 48]
* **Core Operations:** Implements a full range of list operations, including:
    * [cite_start]`add(T e)`: Appends to the end (Amortized $O(1)$). [cite: 72, 74]
    * [cite_start]`add(int index, T e)`: Inserts at a specific index ($O(n)$). [cite: 76, 77]
    * [cite_start]`removeAt(int index)`: Removes at a specific index ($O(n)$). [cite: 79, 84]
    * [cite_start]`get(int index)` / `set(int index, T e)`: Random access ($O(1)$). [cite: 99, 102, 100, 103]
    * [cite_start]`indexOf(T item)` / `contains(T item)`: Linear search ($O(n)$). [cite: 105, 107, 109, 111]
    * [cite_start]`clear()`: Resets the list ($O(1)$). [cite: 94, 97]
* [cite_start]**Iterator Support:** Includes a full-featured inner `Iterator` class supporting: [cite: 133]
    * [cite_start]Dereferencing (`operator*`). [cite: 158]
    * [cite_start]Inequality comparison (`operator!=`). [cite: 162]
    * [cite_start]Prefix/postfix increment (`operator++`). [cite: 167, 172]
    * [cite_start]Prefix/postfix decrement (`operator--`). [cite: 180, 185]

### 2. `SinglyLinkedList<T>`

A template-based singly linked list class.
* [cite_start]**Node-Based:** Implemented using `Node` structs, with `head` and `tail` pointers for efficient management. [cite: 198, 203, 204, 206, 207]
* **Core Operations:**
    * [cite_start]`add(T e)` / `add(int index, T e)`: ($O(n)$). [cite: 219, 221, 223, 224]
    * [cite_start]`removeAt(int index)` / `removeItem(T item)`: ($O(n)$). [cite: 226, 227, 229, 235]
    * [cite_start]`get(int index)`: Access by index ($O(n)$). [cite: 249, 250]
    * [cite_start]`indexOf(T item)` / `contains(T item)`: Linear search ($O(n)$). [cite: 252, 254, 256, 258]
    * [cite_start]`clear()`: Deletes all nodes ($O(n)$). [cite: 245, 247]
* [cite_start]**Iterator Support:** Includes an inner `Iterator` class for forward traversal. [cite: 282]
    * [cite_start]Dereferencing (`operator*`). [cite: 301]
    * [cite_start]Inequality comparison (`operator!=`). [cite: 305]
    * [cite_start]Prefix/postfix increment (`operator++`). [cite: 309, 313]

### 3. `VectorStore`

[cite_start]A class that simulates a modern vector database, used for semantic search and recommendation systems. [cite: 341, 339]

* **Architecture:**
    * [cite_start]Uses an `ArrayList<VectorRecord*>` to manage the collection of all vector records. [cite: 355]
    * [cite_start]Each `VectorRecord` stores metadata (ID, raw text) and a pointer to a `SinglyLinkedList<float>`, which holds the actual high-dimensional vector. [cite: 349, 350, 351, 353]
* **Text Processing:**
    * [cite_start]**`addText(string rawText)`**: Adds a new vector by first processing the text. [cite: 391]
    * [cite_start]**`preprocessing(string rawText)`**: Uses a provided `embeddingFunction` to convert text to a vector. [cite: 382, 384] [cite_start]It then truncates or pads the vector with zeros to match the store's fixed `dimension`. [cite: 386, 387]
* [cite_start]**CRUD Operations:** Provides methods to manage records, such as `getVector(int index)`, `getRawText(int index)`, `removeAt(int index)`, and `updateText(int index, string newRawText)`. [cite: 396, 399, 409, 413]
* **Similarity Metrics:** Implements three standard vector similarity/distance functions:
    * [cite_start]**`cosineSimilarity(v1, v2)`**: $cos(\theta)=\frac{A\cdot B}{||A||||B||}$ [cite: 425, 427]
    * [cite_start]**`l1Distance(v1, v2)`** (Manhattan): $d(\vec{A},\vec{B})=\sum_{i=1}^{d}|A_{i}-B_{i}|$ [cite: 431, 437]
    * [cite_start]**`l2Distance(v1, v2)`** (Euclidean): $l(\vec{A},\vec{B})=\sqrt{\sum_{i=1}^{d}(A_{i}-B_{i})^{2}}$ [cite: 443, 445]
* **Search Functionality:**
    * [cite_start]**`findNearest(query, metric)`**: Finds and returns the index of the single nearest vector to the query vector using the specified metric. [cite: 450]
    * [cite_start]**`topKNearest(query, k, metric)`**: Returns a dynamically allocated array of indices for the top $k$ nearest vectors to the query. [cite: 454, 458]

## File Structure

* [cite_start]`VectorStore.h`: Header file containing all class definitions (`ArrayList`, `SinglyLinkedList`, `VectorStore`, and their inner classes/structs). [cite: 470, 483]
* [cite_start]`VectorStore.cpp`: Implementation file containing the method definitions for all classes. [cite: 470, 483]
* `main.cpp`, `main.h`, `utils.h`: Provided files from the university for testing the implementation. [cite_start]These files were not modified. [cite: 469, 471]

## How to Compile

The project is written in C++17. [cite_start]It can be compiled using the following g++ command: [cite: 473]

```bash
g++ -o main main.cpp VectorStore.cpp -I -std=c++17
