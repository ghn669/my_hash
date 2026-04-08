#include"my_hash.h"
#include<iostream>
using namespace std;
int main()
{
    unordered_map mp;

    // 1. 插入一批数据，触发 rehash 扩容
    cout << "=== 插入数据 ===" << endl;
    mp.push(1, 10);
    mp.push(2, 20);
    mp.push(3, 30);
    mp.push(4, 40);
    mp.push(5, 50);
    mp.push(6, 60);
    mp.push(7, 70);
    mp.push(8, 80);  // 插入第8个，size=8，桶=8 → 负载因子1
    mp.push(9, 90);  // 插入第9个 → 触发 rehash，桶变成16
    mp.print();

    // 2. 测试 [] 重载
    cout << "=== 测试 [] 运算符 ===" << endl;
    mp[10] = 100;       // 不存在 → 插入
    mp[2] = 200;        // 已存在 → 修改
    cout << "mp[2] = " << mp[2] << endl;
    cout << "mp[10] = " << mp[10] << endl;
    mp.print();

    // 3. 测试 get
    cout << "=== 测试 get ===" << endl;
    cout << "get(3) = " << mp.get(3) << endl;
    cout << "get(99) = " << mp.get(99) << "（不存在）" << endl;

    // 4. 测试删除
    cout << "=== 删除 key=3 ===" << endl;
    mp.erase(3);
    mp.print();

    // 5. 测试 size / empty
    cout << "size = " << mp.size() << endl;
    cout << "empty? " << (mp.empty() ? "是" : "否") << endl;

    // 6. 测试 clear
    cout << "=== 清空整个 map ===" << endl;
    mp.clear();
    mp.print();
    cout << "clear 后 size = " << mp.size() << endl;
    cout << "empty? " << (mp.empty() ? "是" : "否") << endl;

    return 0;
}