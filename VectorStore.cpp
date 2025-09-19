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
    for(int i=0; i<other.count; ++i){
        this->data[i]=other.data[i];
    }
    this->count = other.count;
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
        for(int i=0; i<this->count; ++i){
            newData[i]=this->data[i];
        }
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
    return data[index];
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
    for(int i=0; i<count; ++i){
        if(this->data[i]==item){
            return i;
        }
    }
    return -1;
}

template <class T>
bool ArrayList<T>::contains(T item) const{
    for(int i=0; i<this->count; ++i){
        if(this->data[i]==item) return true;
    }
    return false;
}

template <class T>
string ArrayList<T>::toString(string (*item2str)(T&) = 0) const{
    ostringstream result;
    result << "[";

    for(int i=0; i<count; ++i){
        result << item2str(data[i]);
        if(i<count-1){
            result << ", ";
        }
    }
    result << "]";
    return result.str();
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::begin(){
    return Iterator(this, 0);
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::end(){
    return Iterator(this, count);
}

// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* pList, int index) {
    // TODO
    if(index<0||index>pList->count){
        throw out_of_range("Index is invalid!");
    }
    this->pList=pList;
    cursor = index;
}

// TODO: implement other methods of ArrayList::Iterator
template <class T>
ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator=(const Iterator& other){
    this->cursor=other.cursor;
    this->pList=other.pList;
    return *this;
}

template <class T>
T& ArrayList<T>::Iterator::operator*(){
    if(cursor<0||cursor>=pList->count){
        throw out_of_range("Iterator is out of range!");
    }
    return pList->data[cursor];
}

template <class T>
 bool ArrayList<T>::Iterator::operator!=(const Iterator& other) const{
    return this->pList!=other.pList || this->cursor!=other.cursor;
 }

template <class T>
 typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator++(){
    if(cursor==pList->count){
        throw out_of_range("Iterator cannot advance past end!");
    }
    ++cursor;
    return *this;
 }

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++(int) {
    if(cursor==pList->count){
        throw out_of_range("Iterator cannot advance past end!");
    }
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator--(){
    if(cursor==0){
        throw out_of_range("Iterator cannot move before begin!");
    }
    --cursor;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--(int){
    if(cursor==0){
        throw out_of_range("Iterator cannot move before begin!");
    }
    Iterator temp = *this;
    --(*this);
    return temp;
}


// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() : count(0) {
    // TODO
    this->head = new Node();
    this->tail = new Node();
    this->head->next=this->tail;
    this->tail->next=this->head;
}   

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    // TODO
    Node* current = head;
    while (current!=NULL)
    {
        Node* temp = current;
        current=current->next;
        delete temp;
    }
}   

template <class T>
void SinglyLinkedList<T>::add(T e){
    add(count, e);
}

template <class T>
void SinglyLinkedList<T>::add(int index, T e){
    if(index<0||index>count){
        throw out_of_range("Index is invalid!");
    }
    Node* temp = new Node(e);
    Node* prev = head;
    for(int i=-1; i<count-1; ++i){
        prev=prev->next;
    }
    temp->next=prev->next;
    prev->next=temp;
    ++count;
}

// TODO: implement other methods of SinglyLinkedList

template <class T>
T SinglyLinkedList<T>::removeAt(int index){
    if(index<0||index>=count){
        throw out_of_range("Index is invalid!");
    }
    T value;
    Node* prev = head;
    for(int i=-1; i<index-1; ++i){
        prev=prev->next;
    }
    Node* curr = prev->next;
    value=curr->data;
    prev->next=curr->next;
    curr->next=NULL;
    delete curr;
    curr=NULL;
    --count;
    return value;
}

template <class T>
bool SinglyLinkedList<T>::removeItem(T item){
    Node* temp = head->next;
    for(int i=0; i<count-1; ++i){
        if(temp->data==item){
            removeAt(i);
            return true;
        }
        temp=temp->next;
    }
    return false;
}

template <class T>
bool SinglyLinkedList<T>::empty() const{
    return count==0;
}

template <class T>
int SinglyLinkedList<T>::size() const{
    return count;
}

template <class T>
void SinglyLinkedList<T>::clear(){
    Node* curr = head->next;
    Node* temp;
    while(curr!=tail){
        temp=curr;
        curr=curr->next;
        delete temp;
    }
    count=0;
}

template <class T>
T& SinglyLinkedList<T>::get(int index){
    if(index<0||index>=count){
        throw out_of_range("Index is invalid!");
    }
    Node* temp = head->next;
    for(int i=0; i<index; ++i){
            temp=temp->next;
    }
    return temp->data;
}

template <class T>
int SinglyLinkedList<T>::indexOf(T item) const{
    Node* temp = head->next;
    for(int i=0; i<count; ++i){
        if(temp->data==item) return i;
        temp=temp->next;
    }
    return -1;
}

template <class T>
bool SinglyLinkedList<T>::contains(T item) const{
    Node* temp = head->next;
    for(int i=0; i<count; ++i){
        if(temp->data==item) return true;
        temp=temp->next;
    }
    return false;
}

template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T&) = 0) const{
    ostringstream result;
    Node* temp = head->next;
    while(temp!=tail){
        result << "[" << item2str(temp->data) << "]";
        if(temp->next!=tail){
            result << "->";
        }
        temp=temp->next;
    }
    return result.str();
}

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
