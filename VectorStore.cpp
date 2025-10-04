#include "VectorStore.h"

// ----------------- ArrayList Implementation -----------------

template <class T>
ArrayList<T>::ArrayList(int initCapacity) {
    // TODO
    this->capacity = initCapacity;
    this->data = new T [initCapacity];
    this->count = 0;
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
    // TODO
    this->capacity = other.capacity;
    this->data = new T [other.capacity];
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
    for(int i=0; i<other.count; i++){
        this->data[i]=other.data[i];
    }
    return *this;
}

// TODO: implement other methods of ArrayList
template <class T>
void ArrayList<T>::ensureCapacity(int cap) {
    if(cap>this->capacity){
        int newCapacity = (this->capacity * 3)/2;
        if (newCapacity < cap) newCapacity = cap;
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
    for(int i = this->count; i>index; i--){
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
T& ArrayList<T>::get(int index) const {
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
string ArrayList<T>::toString(string (*item2str)(T&)) const{
    ostringstream result;
    result << "[";
    for(int i=0; i<count; ++i){
        if(item2str)
            result << item2str(data[i]);
        else
            result << data[i]; // works for int, double, float, string
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
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator=(const Iterator& other){
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
    this->tail->next=nullptr;
}   

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    // TODO
    Node* current = head;
    while (current!=nullptr)
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
    for(int i=-1; i<index-1; ++i){
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
    curr->next=nullptr;
    delete curr;
    curr=nullptr;
    --count;
    return value;
}

template <class T>
bool SinglyLinkedList<T>::removeItem(T item){
    Node* temp = head->next;
    for(int i=0; i<count; ++i){
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
    this->head->next=this->tail;
}

template <class T>
T& SinglyLinkedList<T>::get(int index) const {
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
string SinglyLinkedList<T>::toString(string (*item2str)(T&)) const{
    ostringstream result;
    Node* temp = head->next;
    while(temp!=tail){
        if(item2str)
        result << "[" << item2str(temp->data) << "]";
        else
        result << "[" << temp->data << "]";
        if(temp->next!=tail){
            result << "->";
        }
        temp=temp->next;
    }
    return result.str();
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin() const {
    return Iterator(this->head->next);
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() const {
    return Iterator(this->tail);
}

// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node* node): current(node) {
    // TODO
}   

// TODO: implement other methods of SinglyLinkedList::Iterator
template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator=(const Iterator& other){
    this->current=other.current;
    return *this;
}

template <class T>
T& SinglyLinkedList<T>::Iterator::operator*(){
    if(current==nullptr || current->next==nullptr){
        throw out_of_range("Iterator is out of range!");
    }
    return this->current->data;
}

template <class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator& other) const{
    return this->current!=other.current;
}

template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++(){
    if(this->current==nullptr || this->current->next==nullptr){
        throw out_of_range("Iterator cannot advance past end!");
    }
    this->current=this->current->next;
    
    return *this;
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::operator++(int){
    if(this->current==nullptr || this->current->next==nullptr){
        throw out_of_range("Iterator cannot advance past end!");
    }
    Iterator temp = *this;
    this->current=this->current->next;
    return temp;
}

template <class T>
void SinglyLinkedList<T>::trimToSize(int newSize) {
    if(newSize<0||newSize>count) return;
    Node* curr = head;
    for(int i=-1; i<newSize-1; ++i){
        curr = curr->next;
    }
    Node* toDel = curr->next;
    curr->next=tail;
    while(toDel!=tail){
        Node* temp = toDel;
        toDel=toDel->next;
        delete temp;
    }
    count=newSize;
}


// ----------------- VectorStore Implementation -----------------

VectorStore::VectorStore(int dimension, EmbedFn embeddingFunction) {
    // TODO
    this->dimension=dimension;
    this->embeddingFunction=embeddingFunction;
    this->count=0;
}

VectorStore::~VectorStore() {
    // TODO
    this->clear();
}

// TODO: implement other methods of VectorStore

int  VectorStore::size() const{
    return this->count;
}

bool VectorStore::empty() const{
    return this->count==0;
}

void VectorStore::clear(){
    for(int i=0; i<count; ++i){
        VectorRecord* vec = records.get(i);
        delete vec->vector;
        delete vec;
    }
    records.clear();
    count=0;
}

SinglyLinkedList<float>* VectorStore::preprocessing(string rawText){
    if (!embeddingFunction) throw std::runtime_error("Embedding function is not set");
    SinglyLinkedList<float>* result = embeddingFunction(rawText);
    if (!result) throw std::runtime_error("Embedding function returned nullptr");
    if(result->size()>dimension){
        result->trimToSize(dimension);
    }
    else if(result->size()<dimension){
        int oldSize = result->size();
        for(int i=0; i<dimension-oldSize; ++i){
            result->add(0.0);
        }
    }
    return result;
}

VectorStore::VectorRecord::VectorRecord(int id, const string& rawText, SinglyLinkedList<float>* vector)
: id(id), rawText(rawText), rawLength(rawText.length()), vector(vector){}

void VectorStore::addText(string rawText){
    int newId = 1;
    if(count>0){
        newId = records.get(count-1)->id+1;
    }
    SinglyLinkedList<float>* vec = preprocessing(rawText);
    VectorRecord* record = new VectorRecord(newId, rawText, vec);
    records.add(record);
    count++;
}

SinglyLinkedList<float>& VectorStore::getVector(int index){
    if(index<0||index>=count) throw out_of_range("Index is invalid!");
    return *(this->records.get(index)->vector);
}

string VectorStore::getRawText(int index) const{
    if(index<0||index>=count) throw out_of_range("Index is invalid!");
    return this->records.get(index)->rawText;
}


int VectorStore::getId(int index) const{
    if(index<0||index>=count) throw out_of_range("Index is invalid!");
    return this->records.get(index)->id;
}

bool VectorStore::removeAt(int index){
    if(index<0||index>=count) throw out_of_range("Index is invalid!");
    VectorRecord* rec = this->records.get(index);
    this->records.removeAt(index);
    delete rec->vector;
    delete rec;
    --count;
    return true;
}

bool VectorStore::updateText(int index, string newRawText){
    if(index<0||index>=count) throw out_of_range("Index is invalid!");
    SinglyLinkedList<float>* newVector = preprocessing(newRawText);

    delete this->records.get(index)->vector;
    this->records.get(index)->vector=newVector;
    this->records.get(index)->rawText=newRawText;
    this->records.get(index)->rawLength=newRawText.length();
    
    return true;
}

void VectorStore::setEmbeddingFunction(EmbedFn newEmbeddingFunction){
    this->embeddingFunction=newEmbeddingFunction;
}

void VectorStore::forEach(void (*action)(SinglyLinkedList<float>&, int, string&)){
    for(int i=0; i<count; ++i){
        action(*(this->records.get(i)->vector), this->records.get(i)->id, this->records.get(i)->rawText);
    }
}

double VectorStore::cosineSimilarity(const SinglyLinkedList<float>& v1,
                            const SinglyLinkedList<float>& v2) const{
                                double dotProduct = 0;
                                double sumSquareA = 0;
                                double sumSquareB = 0;

                                auto it1 = v1.begin();
                                auto it2 = v2.begin();
                                

                                for(int i=0; i<dimension; ++i){
                                    float A = *it1;
                                    float B = *it2;
                                    dotProduct += (A * B);
                                    sumSquareA += (A * A);
                                    sumSquareB += (B * B);
                                    ++it1;
                                    ++it2;
                                }
                                double normA = sqrt(sumSquareA);
                                double normB = sqrt(sumSquareB);
                                if(normA==0||normB==0) return 0;
                                return dotProduct/(normA*normB);
                            }

double VectorStore::l1Distance(const SinglyLinkedList<float>& v1,
                      const SinglyLinkedList<float>& v2) const{
                        double dist = 0;
                        auto it1 = v1.begin();
                        auto it2 = v2.begin();
                        for(int i=0; i<dimension; ++i){
                            dist += std::abs(*it1 - *it2);
                            ++it1;
                            ++it2;
                        }
                        return dist;
                      }

double VectorStore::l2Distance(const SinglyLinkedList<float>& v1,
                      const SinglyLinkedList<float>& v2) const{
                        double dist = 0;
                        auto it1 = v1.begin();
                        auto it2 = v2.begin();
                        for(int i=0; i<dimension; ++i){
                            float diff = *it1-*it2;
                            dist += diff*diff;
                            ++it1;
                            ++it2;
                        }
                        return sqrt(dist);
                      }

int VectorStore::findNearest(const SinglyLinkedList<float>& query, const string& metric) const{
    double smallestDistance=1e9;
    double largestSimilarity=-1e9;
    int idx=-1;
    if(metric=="cosine"){
        for(int i=0; i<count; ++i){
        double value = cosineSimilarity(query, *(this->records.get(i)->vector));
        if(value>largestSimilarity){
            largestSimilarity=value;
            idx=i;
        }
        }
    }
    else if(metric=="euclidean"){
        for(int i=0; i<count; ++i){
        double value = l2Distance(query, *(this->records.get(i)->vector));
        if(value<smallestDistance){
            smallestDistance=value;
            idx=i;
        }
        }
    }
    else if(metric=="manhattan"){
        for(int i=0; i<count; ++i){
        double value = l1Distance(query, *(this->records.get(i)->vector));
        if(value<smallestDistance){
            smallestDistance=value;
            idx=i;
        }
        }
    }
    else throw invalid_metric();
    return idx;
}


void VectorStore::recursiveMergeSort(ArrayList<Pair>& list, int low, int hi, bool descending) const {
    if (low < hi) {
        int mid = low + (hi - low) / 2;
        recursiveMergeSort(list, low, mid, descending);
        recursiveMergeSort(list, mid + 1, hi, descending);
        merge(list, low, mid, hi, descending);
    }
}

void VectorStore::merge(ArrayList<Pair>& list, int low, int mid, int hi, bool descending) const {
    int n = hi - low + 1;
    Pair* temp = new Pair[n];
    for (int i = 0; i < n; ++i) {
        temp[i] = list.get(low + i);
    }
    int i = 0, j = mid - low + 1, k = low;
    while (i <= mid - low && j < n) {
        bool cmp = descending ? (temp[i].value > temp[j].value) : (temp[i].value < temp[j].value);
        // For stable sort: when values are equal, pick the one with smaller original index
        bool equalValues = (temp[i].value == temp[j].value);
        bool pickLeft = cmp || (equalValues && temp[i].idx <= temp[j].idx);
        if (pickLeft) {
            list.set(k++, temp[i++]);
        } else {
            list.set(k++, temp[j++]);
        }
    }
    while (i <= mid - low) list.set(k++, temp[i++]);
    while (j < n) list.set(k++, temp[j++]);
    delete[] temp;
}

int* VectorStore::topKNearest(const SinglyLinkedList<float>& query, int k, const string& metric) const{
    if(k<=0||k>count) throw invalid_k_value();
    ArrayList<Pair> temp(count);
    for(int i=0; i<count; ++i){
        double val;
        if(metric=="cosine")
            val = cosineSimilarity(query, *this->records.get(i)->vector);
        else if(metric=="euclidean")
            val = l2Distance(query, *this->records.get(i)->vector);
        else if(metric=="manhattan")
            val = l1Distance(query, *this->records.get(i)->vector);
        else throw invalid_metric();
        Pair p = {i, val};
        temp.add(p);
}
    //sort
    bool descending = (metric=="cosine");
    recursiveMergeSort(temp,0,temp.size()-1,descending);
    
    int* result = new int [k];
    for(int i=0; i<k;++i){
        result[i]=temp.get(i).idx;
    }
    return result;
}

// Explicit template instantiation for char, string, int, double, float, and Point

template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;
template class ArrayList<VectorStore::VectorRecord*>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
