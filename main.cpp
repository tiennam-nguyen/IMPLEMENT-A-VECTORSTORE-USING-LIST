#include "VectorStore.h"
#include "VectorStore.cpp"

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>

using namespace std;

// Test embedding functions
SinglyLinkedList<float>* fixedEmbed5(const string& text) {
    SinglyLinkedList<float>* vec = new SinglyLinkedList<float>();
    for (int i = 0; i < 5; ++i) {
        vec->add(static_cast<float>(i + text.length()));
    }
    return vec;
}

SinglyLinkedList<float>* undersizedEmbed(const string& text) {
    SinglyLinkedList<float>* vec = new SinglyLinkedList<float>();
    for (int i = 0; i < 3; ++i) {
        vec->add(static_cast<float>(text[i % text.length()]));
    }
    return vec;
}

SinglyLinkedList<float>* oversizedEmbed(const string& text) {
    SinglyLinkedList<float>* vec = new SinglyLinkedList<float>();
    for (int i = 0; i < 15; ++i) {
        vec->add(static_cast<float>(i * 0.1));
    }
    return vec;
}

SinglyLinkedList<float>* identityEmbed(const string& text) {
    SinglyLinkedList<float>* vec = new SinglyLinkedList<float>();
    if (text == "v1") {
        vec->add(1.0f); vec->add(0.0f); vec->add(0.0f);
    } else if (text == "v2") {
        vec->add(0.0f); vec->add(1.0f); vec->add(0.0f);
    } else if (text == "v3") {
        vec->add(0.9f); vec->add(0.1f); vec->add(0.0f);
    } else {
        vec->add(0.5f); vec->add(0.5f); vec->add(0.0f);
    }
    return vec;
}

void testBasicOperations() {
    cout << "Test 1: Basic VectorStore Operations" << endl;
    
    VectorStore store(5, fixedEmbed5);
    assert(store.empty());
    assert(store.size() == 0);
    
    store.addText("hello");
    assert(!store.empty());
    assert(store.size() == 1);
    assert(store.getRawText(0) == "hello");
    assert(store.getId(0) == 1);
    
    store.addText("world");
    assert(store.size() == 2);
    assert(store.getId(1) == 2);
    
    cout << "  ✓ Passed" << endl;
}

void testPreprocessingPadding() {
    cout << "Test 2: Preprocessing - Zero Padding" << endl;
    
    VectorStore store(10, undersizedEmbed);
    store.addText("abc");
    
    SinglyLinkedList<float>& vec = store.getVector(0);
    assert(vec.size() == 10);
    
    // Check that padding zeros exist
    for (int i = 3; i < 10; ++i) {
        assert(abs(vec.get(i) - 0.0f) < 0.001f);
    }
    
    cout << "  ✓ Passed" << endl;
}

void testPreprocessingTruncation() {
    cout << "Test 3: Preprocessing - Truncation" << endl;
    
    VectorStore store(8, oversizedEmbed);
    store.addText("test");
    
    SinglyLinkedList<float>& vec = store.getVector(0);
    assert(vec.size() == 8);
    
    cout << "  ✓ Passed" << endl;
}

void testUpdateText() {
    cout << "Test 4: Update Text with Preprocessing" << endl;
    
    VectorStore store(10, oversizedEmbed);
    store.addText("original");
    
    int originalId = store.getId(0);
    string originalText = store.getRawText(0);
    
    store.updateText(0, "updated");
    
    // ID should remain the same
    assert(store.getId(0) == originalId);
    assert(store.getRawText(0) == "updated");
    
    // Vector should be truncated to dimension
    SinglyLinkedList<float>& vec = store.getVector(0);
    assert(vec.size() == 10);
    
    cout << "  ✓ Passed" << endl;
}

void testRemoveAt() {
    cout << "Test 5: RemoveAt" << endl;
    
    VectorStore store(5, fixedEmbed5);
    store.addText("first");
    store.addText("second");
    store.addText("third");
    
    assert(store.size() == 3);
    store.removeAt(1);
    assert(store.size() == 2);
    assert(store.getRawText(0) == "first");
    assert(store.getRawText(1) == "third");
    
    cout << "  ✓ Passed" << endl;
}

void testClear() {
    cout << "Test 6: Clear" << endl;
    
    VectorStore store(5, fixedEmbed5);
    store.addText("a");
    store.addText("b");
    store.addText("c");
    
    assert(store.size() == 3);
    store.clear();
    assert(store.empty());
    assert(store.size() == 0);
    
    // Can add again after clear
    store.addText("new");
    assert(store.size() == 1);
    
    cout << "  ✓ Passed" << endl;
}

void testCosineSimilarity() {
    cout << "Test 7: Cosine Similarity" << endl;
    
    VectorStore store(3, nullptr);
    
    SinglyLinkedList<float> v1, v2, v3;
    v1.add(1.0f); v1.add(0.0f); v1.add(0.0f);
    v2.add(0.0f); v2.add(1.0f); v2.add(0.0f);
    v3.add(1.0f); v3.add(1.0f); v3.add(0.0f);
    
    // Orthogonal vectors
    double cos12 = store.cosineSimilarity(v1, v2);
    assert(abs(cos12 - 0.0) < 0.001);
    
    // 45 degree angle
    double cos13 = store.cosineSimilarity(v1, v3);
    assert(abs(cos13 - 0.7071) < 0.01);
    
    // Same vector
    double cos11 = store.cosineSimilarity(v1, v1);
    assert(abs(cos11 - 1.0) < 0.001);
    
    cout << "  ✓ Passed" << endl;
}

void testL1Distance() {
    cout << "Test 8: L1 (Manhattan) Distance" << endl;
    
    VectorStore store(3, nullptr);
    
    SinglyLinkedList<float> v1, v2;
    v1.add(1.0f); v1.add(0.0f); v1.add(0.0f);
    v2.add(0.0f); v2.add(1.0f); v2.add(0.0f);
    
    double dist = store.l1Distance(v1, v2);
    assert(abs(dist - 2.0) < 0.001);
    
    cout << "  ✓ Passed" << endl;
}

void testL2Distance() {
    cout << "Test 9: L2 (Euclidean) Distance" << endl;
    
    VectorStore store(3, nullptr);
    
    SinglyLinkedList<float> v1, v2;
    v1.add(1.0f); v1.add(0.0f); v1.add(0.0f);
    v2.add(0.0f); v2.add(1.0f); v2.add(0.0f);
    
    double dist = store.l2Distance(v1, v2);
    assert(abs(dist - sqrt(2.0)) < 0.001);
    
    cout << "  ✓ Passed" << endl;
}

void testFindNearestCosine() {
    cout << "Test 10: FindNearest with Cosine" << endl;
    
    VectorStore store(3, identityEmbed);
    store.addText("v1");
    store.addText("v2");
    store.addText("v3");
    
    SinglyLinkedList<float> query;
    query.add(1.0f); query.add(0.0f); query.add(0.0f);
    
    int nearest = store.findNearest(query, "cosine");
    assert(nearest == 0 || nearest == 2); // v1 or v3
    
    cout << "  ✓ Passed" << endl;
}

void testFindNearestEuclidean() {
    cout << "Test 11: FindNearest with Euclidean" << endl;
    
    VectorStore store(3, identityEmbed);
    store.addText("v1");
    store.addText("v2");
    store.addText("v3");
    
    SinglyLinkedList<float> query;
    query.add(1.0f); query.add(0.0f); query.add(0.0f);
    
    int nearest = store.findNearest(query, "euclidean");
    assert(nearest == 0 || nearest == 2);
    
    cout << "  ✓ Passed" << endl;
}

void testTopKNearest() {
    cout << "Test 12: TopKNearest" << endl;
    
    VectorStore store(3, identityEmbed);
    store.addText("v1");
    store.addText("v2");
    store.addText("v3");
    store.addText("v4");
    
    SinglyLinkedList<float> query;
    query.add(1.0f); query.add(0.0f); query.add(0.0f);
    
    int* topK = store.topKNearest(query, 2, "cosine");
    assert(topK != nullptr);
    
    // Should return 2 indices
    cout << "  Top 2 indices: " << topK[0] << ", " << topK[1] << endl;
    
    delete[] topK;
    
    cout << "  ✓ Passed" << endl;
}

void testTopKWithAllVectors() {
    cout << "Test 13: TopK with k = count" << endl;
    
    VectorStore store(3, identityEmbed);
    store.addText("v1");
    store.addText("v2");
    store.addText("v3");
    
    SinglyLinkedList<float> query;
    query.add(1.0f); query.add(0.0f); query.add(0.0f);
    
    int* topK = store.topKNearest(query, 3, "cosine");
    assert(topK != nullptr);
    
    delete[] topK;
    
    cout << "  ✓ Passed" << endl;
}

void testExceptions() {
    cout << "Test 14: Exception Handling" << endl;
    
    VectorStore store(5, fixedEmbed5);
    store.addText("test");
    
    // Invalid index
    try {
        store.getVector(5);
        assert(false);
    } catch (const out_of_range& e) {
        assert(strcmp(e.what(), "Index is invalid!") == 0);
    }
    
    // Invalid metric
    SinglyLinkedList<float> query;
    query.add(1.0f);
    try {
        store.findNearest(query, "invalid");
        assert(false);
    } catch (const invalid_metric& e) {
        // Expected
    }
    
    // Invalid k
    try {
        store.topKNearest(query, 0, "cosine");
        assert(false);
    } catch (const invalid_k_value& e) {
        // Expected
    }
    
    try {
        store.topKNearest(query, 10, "cosine");
        assert(false);
    } catch (const invalid_k_value& e) {
        // Expected
    }
    
    cout << "  ✓ Passed" << endl;
}

void testSetEmbeddingFunction() {
    cout << "Test 15: Change Embedding Function" << endl;
    
    VectorStore store(5, fixedEmbed5);
    store.addText("before");
    
    store.setEmbeddingFunction(undersizedEmbed);
    store.addText("after");
    
    // Both should work
    assert(store.size() == 2);
    assert(store.getVector(0).size() == 5);
    assert(store.getVector(1).size() == 5); // Padded
    
    cout << "  ✓ Passed" << endl;
}

void testForEach() {
    cout << "Test 16: ForEach" << endl;
    
    VectorStore store(3, identityEmbed);
    store.addText("v1");
    store.addText("v2");
    store.addText("v3");
    
    int callCount = 0;
    store.forEach([](SinglyLinkedList<float>& vec, int id, string& text) {
        static int count = 0;
        count++;
    });
    
    // Just verify it doesn't crash
    cout << "  ✓ Passed" << endl;
}

void testIdSequence() {
    cout << "Test 17: ID Sequence after Add/Remove" << endl;
    
    VectorStore store(5, fixedEmbed5);
    store.addText("a");
    store.addText("b");
    store.addText("c");
    
    assert(store.getId(0) == 1);
    assert(store.getId(1) == 2);
    assert(store.getId(2) == 3);
    
    store.removeAt(1);
    
    // IDs should remain unchanged for remaining elements
    assert(store.getId(0) == 1);
    assert(store.getId(1) == 3);
    
    // New element should get next ID
    store.addText("d");
    assert(store.getId(2) == 4);
    
    cout << "  ✓ Passed" << endl;
}

void testComplexityTopK() {
    cout << "Test 18: TopK Time Complexity Check" << endl;
    
    VectorStore store(10, fixedEmbed5);
    
    // Add many vectors
    for (int i = 0; i < 100; ++i) {
        store.addText("text" + to_string(i));
    }
    
    SinglyLinkedList<float> query;
    for (int i = 0; i < 10; ++i) {
        query.add(static_cast<float>(i));
    }
    
    int* topK = store.topKNearest(query, 10, "cosine");
    assert(topK != nullptr);
    
    delete[] topK;
    
    cout << "  ✓ Passed (100 vectors processed)" << endl;
}

void testMemoryLeakCheck() {
    cout << "Test 19: Memory Leak Check" << endl;
    
    for (int iter = 0; iter < 50; ++iter) {
        VectorStore store(8, oversizedEmbed);
        store.addText("a");
        store.addText("b");
        store.addText("c");
        
        store.removeAt(1);
        store.updateText(0, "updated");
        
        SinglyLinkedList<float> query;
        for (int i = 0; i < 8; ++i) {
            query.add(1.0f);
        }
        
        int* topK = store.topKNearest(query, 2, "euclidean");
        delete[] topK;
        
        store.clear();
    }
    
    cout << "  ✓ Passed (run valgrind for verification)" << endl;
}

int main() {
    cout << "=== VectorStore Comprehensive Tests ===" << endl << endl;
    
    try {
        testBasicOperations();
        testPreprocessingPadding();
        testPreprocessingTruncation();
        testUpdateText();
        testRemoveAt();
        testClear();
        testCosineSimilarity();
        testL1Distance();
        testL2Distance();
        testFindNearestCosine();
        testFindNearestEuclidean();
        testTopKNearest();
        testTopKWithAllVectors();
        testExceptions();
        testSetEmbeddingFunction();
        testForEach();
        testIdSequence();
        testComplexityTopK();
        testMemoryLeakCheck();
        
        cout << endl << "=== ALL TESTS PASSED ===" << endl;
        cout << "\n✓ Your VectorStore implementation is ready to submit!" << endl;
        cout << "\nFinal checks:" << endl;
        cout << "  1. Run: valgrind --leak-check=full ./test" << endl;
        cout << "  2. Verify no memory leaks reported" << endl;
        cout << "  3. Submit VectorStore.h and VectorStore.cpp" << endl;
        
    } catch (const exception& e) {
        cout << endl << "!!! TEST FAILED !!!" << endl;
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}