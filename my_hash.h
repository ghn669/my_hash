#ifndef MY_HASH
#define MY_HASH
struct Node
{
    int key;
    int val;
    Node* next;
    Node(int k, int v);
};
class unordered_map
{
private:
    Node **table;
    int bucket_num;
    double load_factor;
    int hash(int key);
public:
    unordered_map();
    void push(int key,int val);
    int get(int key);
    void erase(int key); 
    void print();
    int size();
    bool empty();
    void clear();
    int& operator[](int key);
    void rehash();
    ~unordered_map();
};
#endif