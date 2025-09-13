#include "VectorStore.h"

// ----------------- ArrayList Implementation -----------------

template <class T>
ArrayList<T>::ArrayList(int initCapacity = 10) {
    // TODO
    this->capacity = initCapacity;
    this->data = new T [initCapacity];
    this->count = 0;
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
    // TODO
    this->capacity = other.capacity;
    this->data = new T [this->capacity];
    memmove(this->data, other.data, (this->capacity)*sizeof(T));
    this->count = 0;
}   

template <class T>
ArrayList<T>::~ArrayList() {
    // TODO
    delete []data;
}

template <class T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &other)
{
    // TODO: insert return statement here
    if(this==&other) return *this;

    delete []this->data;

    this->capacity = other.capacity;
    this->count=other.count;
    this->data = new T [this->capacity];
    for(int i=0; i<this->capacity; i++){
        this->data[i]=other.data[i];
    }
    return *this;
}

// TODO: implement other methods of ArrayList
template <class T>
void ArrayList<T>::ensureCapacity(int cap) {
    if(cap>this->capacity){
        int newCapacity = this->capacity * 3/2;
        T* newData = new T [newCapacity];
        memmove(newData, this->data, this->count*sizeof(T));
        this->capacity=newCapacity;
        delete []data;
        this->data = newData;
    }
}

template <class T>
void ArrayList<T>::add(T e){
    ensureCapacity(this->count+1);
    this->data[this->count]=e;
    this->count++;
}

template <class T>
void ArrayList<T>::add(int index, T e){
    if(index<0 || index>this->count){
        throw std::out_of_range("Index is invalid!");
    }
    ensureCapacity(this->count+1);
    for(int i = this->count; i>index; i++){
        this->data[i]=this->data[i-1];
    }
    this->data[index]=e;
    ++count;
}

template <class T>
T ArrayList<T>::removeAt(int index){
    if(index<0 || index>=count){
        throw std::out_of_range("Index is invalid!");
    }
    T removedElement = this->data[index];
    for(int i=index; i<count-1; i++){
        data[i]=std::move(data[i+1]);
    }
    --count;
    return removedElement;
}

template <class T>
bool ArrayList<T>::empty() const {
    return this->count==0;
}

template <class T>
int ArrayList<T>::size() const {
    return this->count;
}

template <class T>
void ArrayList<T>::clear(){
    delete []this->data;
    this->capacity=10;
    this->data = new T[this->capacity];
    this->count=0;
}

template <class T>
T& ArrayList<T>::get(int index){
    if(index<0 || index>=count){
        throw std::out_of_range("Index is invalid!");
    }
    return data+index;
}

template <class T>
void ArrayList<T>::set(int index, T e){
    if(index<0 || index>=count){
        throw std::out_of_range("Index is invalid!");
    }
    this->data[index]=e;
}

template <class T>
int ArrayList<T>::indexOf(T item) const {
    for(int i=0; i<count; i++){
        if(this->data[i]==item){
            return i;
        }
    }
    return -1;
}

// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* pList, int index) {
    // TODO
}

// TODO: implement other methods of ArrayList::Iterator



// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    // TODO
}   

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    // TODO
}   

// TODO: implement other methods of SinglyLinkedList



// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node* node) {
    // TODO
}   

// TODO: implement other methods of SinglyLinkedList::Iterator



// ----------------- VectorStore Implementation -----------------

VectorStore::VectorStore(int dimension = 512, EmbedFn embeddingFunction = nullptr) {
    // TODO
}

VectorStore::~VectorStore() {
    // TODO
}

// TODO: implement other methods of VectorStore


// Explicit template instantiation for char, string, int, double, float, and Point

template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
