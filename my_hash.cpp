#include<iostream>
#include"my_hash.h"
using namespace std;
Node::Node(int k, int v) : key(k), val(v), next(nullptr) {}

int unordered_map::hash(int key)
{
    return key % bucket_num;
}

unordered_map::unordered_map()
{
    bucket_num = 8;
    table = new Node*[bucket_num];
    load_factor = 1.0;
    for(int i=0;i<bucket_num;i++)
        table[i] = nullptr;
}

unordered_map::~unordered_map()
{
    clear();
    delete[] table;
}

void unordered_map::push(int key, int val)
{
    int idx = hash(key);
    Node*& head = table[idx];
    for(Node* p=head;p;p=p->next)
    {
        if(p->key == key)
        {
            p->val = val;
            return;
        }
    }
    Node* newnode = new Node(key, val);
    newnode->next = head;
    head = newnode;

    if((double)size() / bucket_num > load_factor)
        rehash();
}

int unordered_map::get(int key)
{
    int idx = hash(key);
    Node* head = table[idx];
    for(Node* p=head;p;p=p->next)
    {
        if(p->key == key) return p->val;
    }
    return -1;
}

void unordered_map::erase(int key)
{
    int idx = hash(key);
    Node*& head = table[idx];
    Node* pre = nullptr;
    for(Node* p = head;p;pre=p,p=p->next)
    {
        if(p->key == key && p == head)
        {
            head = head->next;
            delete p;
            return;
        }
        else if(p->key == key)
        {
            pre->next = p->next;
            delete p;
            return;
        }
    }
}

void unordered_map::print()
{
    for(int i=0;i<bucket_num;i++)
    {
        cout<<"Ͱ"<<i<<":"<<endl;
        Node* head = table[i];
        for(Node* p=head;p;p=p->next)
        {
            cout<<"key:"<<p->key<<" val:"<<p->val<<endl;
        }
    }
    cout<<"--------------------"<<endl;
}

int unordered_map::size()
{
    int count=0;
    for(int i=0;i<bucket_num;i++)
    {
        Node* head = table[i];
        for(Node* p=head;p;p=p->next)
        {
            count++;
        }
    }
    return count;
}

bool unordered_map::empty()
{
    return size() == 0;
}

void unordered_map::clear()
{
    for(int i=0;i<bucket_num;i++)
    {
        Node* head = table[i];
        while(head)
        {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        table[i] = nullptr;
    }
}

int& unordered_map::operator[](int key)
{
    int idx = hash(key);
    Node*& head = table[idx];
    for (Node* p = head; p; p = p->next) {
        if (p->key == key) {
            return p->val;
        }
    }
    Node* newnode = new Node(key, 0);
    newnode->next = head;
    head = newnode;
    return newnode->val;
}

void unordered_map::rehash()
{
    int old_bucket = bucket_num;
    bucket_num *= 2;
    Node** new_table = new Node*[bucket_num];
    for(int i=0;i<bucket_num;i++)
        new_table[i] = nullptr;

    for(int i=0;i<old_bucket;i++)
    {
        Node* p = table[i];
        while(p)
        {
            Node* next = p->next;
            int idx = hash(p->key);
            p->next = new_table[idx];
            new_table[idx] = p;
            p = next;
        }
    }
    delete[] table;
    table = new_table;
}