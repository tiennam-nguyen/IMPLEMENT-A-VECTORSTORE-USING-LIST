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
* **Dynamic Capacity:** Automatically expands capacity by a factor of 1.5 when full.
* **Core Operations:** Implements a full range of list operations, including:
    * `add(T e)`: Appends to the end (Amortized $O(1)$).
    * `add(int index, T e)`: Inserts at a specific index ($O(n)$).
    * `removeAt(int index)`: Removes at a specific index ($O(n)$).
    * `get(int index)` / `set(int index, T e)`: Random access ($O(1)$).
    * `indexOf(T item)` / `contains(T item)`: Linear search ($O(n)$).
    * `clear()`: Resets the list ($O(1)$).
* **Iterator Support:** Includes a full-featured inner `Iterator` class supporting:
    * Dereferencing (`operator*`).
    * Inequality comparison (`operator!=`).
    * Prefix/postfix increment (`operator++`).
    * Prefix/postfix decrement (`operator--`).

### 2. `SinglyLinkedList<T>`

A template-based singly linked list class.
* **Node-Based:** Implemented using `Node` structs, with `head` and `tail` pointers for efficient management.
* **Core Operations:**
    * `add(T e)` / `add(int index, T e)`: ($O(n)$).
    * `removeAt(int index)` / `removeItem(T item)`: ($O(n)$).
    * `get(int index)`: Access by index ($O(n)$).
    * `indexOf(T item)` / `contains(T item)`: Linear search ($O(n)$).
    * `clear()`: Deletes all nodes ($O(n)$).
* **Iterator Support:** Includes an inner `Iterator` class for forward traversal.
    * Dereferencing (`operator*`).
    * Inequality comparison (`operator!=`).
    * Prefix/postfix increment (`operator++`).

### 3. `VectorStore`

A class that simulates a modern vector database, used for semantic search and recommendation systems.

* **Architecture:**
    * Uses an `ArrayList<VectorRecord*>` to manage the collection of all vector records.
    * Each `VectorRecord` stores metadata (ID, raw text) and a pointer to a `SinglyLinkedList<float>`, which holds the actual high-dimensional vector.
* **Text Processing:**
    * **`addText(string rawText)`**: Adds a new vector by first processing the text.
    * [cite_start]**`preprocessing(string rawText)`**: Uses a provided `embeddingFunction` to convert text to a vector. It then truncates or pads the vector with zeros to match the store's fixed `dimension`.
* **CRUD Operations:** Provides methods to manage records, such as `getVector(int index)`, `getRawText(int index)`, `removeAt(int index)`, and `updateText(int index, string newRawText)`.
* **Similarity Metrics:** Implements three standard vector similarity/distance functions:
    * **`cosineSimilarity(v1, v2)`**: $cos(\theta)=\frac{A\cdot B}{||A||||B||}$
    * **`l1Distance(v1, v2)`** (Manhattan): $d(\vec{A},\vec{B})=\sum_{i=1}^{d}|A_{i}-B_{i}|$
    * **`l2Distance(v1, v2)`** (Euclidean): $l(\vec{A},\vec{B})=\sqrt{\sum_{i=1}^{d}(A_{i}-B_{i})^{2}}$
* **Search Functionality:**
    * **`findNearest(query, metric)`**: Finds and returns the index of the single nearest vector to the query vector using the specified metric.
    * **`topKNearest(query, k, metric)`**: Returns a dynamically allocated array of indices for the top $k$ nearest vectors to the query.
## File Structure

* `VectorStore.h`: Header file containing all class definitions (`ArrayList`, `SinglyLinkedList`, `VectorStore`, and their inner classes/structs).
* `VectorStore.cpp`: Implementation file containing the method definitions for all classes.
* `main.cpp`, `main.h`, `utils.h`: Provided files for testing the implementation. These files were having basic test cases to make sure the code can run.

## How to Compile

The project is written in C++17. It can be compiled using the following g++ command: 

```bash
g++ -o main main.cpp VectorStore.cpp -I -std=c++17
