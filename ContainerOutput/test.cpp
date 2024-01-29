#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <string>
#include "container_output.h"  // 假设你的代码在这个头文件中

using namespace std;

int main() {
    // 测试基本类型
    vector<int> vec = {1, 2, 3, 4};
    cout << "Testing vector<int>: " << vec << endl;

    list<double> lst = {1.1, 2.2, 3.3};
    cout << "Testing list<double>: " << lst << endl;

    set<string> st = {"hello", "world"};
    cout << "Testing set<string>: " << st << endl;

    // 测试字符和字符串
    vector<char> charVec = {'a', 'b', 'c'};
    cout << "Testing vector<char>: " << charVec << endl;

    vector<const char*> cstrVec = {"first", "second", "third"};
    cout << "Testing vector<const char*>: " << cstrVec << endl;

    // 测试布尔值
    vector<bool> boolVec = {true, false, true};
    cout << "Testing vector<bool>: " << boolVec << endl;

    // 测试嵌套容器
    vector<vector<int>> nestedVec = {{1, 2}, {3, 4}, {5, 6}};
    cout << "Testing vector<vector<int>>: " << nestedVec << endl;

    map<int, vector<int>> mapVec = {{1, {2, 3}}, {4, {5, 6}}};
    cout << "Testing map<int, vector<int>>: " << mapVec << endl;

    // 测试包含pair的容器
    map<int, pair<string, int>> mapPair = {{1, {"one", 1}}, {2, {"two", 2}}};
    cout << "Testing map<int, pair<string, int>>: " << mapPair << endl;


     // 测试 map 嵌套 map
    map<int, map<int, int>> mapOfMap = {
        {1, {{2, 3}, {4, 5}}},
        {6, {{7, 8}, {9, 10}}}
    };
    cout << "Testing map<int, map<int, int>>: " << mapOfMap << endl;

    // 测试 map 嵌套 vector
    map<int, vector<pair<string, int>>> mapVectorPair = {
        {1, {{"apple", 2}, {"banana", 3}}},
        {2, {{"cherry", 5}, {"date", 7}}}
    };
    cout << "Testing map<int, vector<pair<string, int>>>: " << mapVectorPair << endl;

    // 测试 vector 嵌套 map
    vector<map<string, set<int>>> vecMapSet = {
        {{"a", {1, 2, 3}}, {"b", {4, 5}}},
        {{"c", {6, 7, 8}}, {"d", {9}}}
    };
    cout << "Testing vector<map<string, set<int>>>: " << vecMapSet << endl;

    // 测试 map 嵌套 list
    map<int, list<pair<string, double>>> mapListPair = {
        {1, {{"apple", 2.5}, {"banana", 3.5}}},
        {2, {{"cherry", 5.5}, {"date", 7.5}}}
    };
    cout << "Testing map<int, list<pair<string, double>>>: " << mapListPair << endl;

    // 测试嵌套的多层级结构
    map<int, map<int, vector<pair<string, list<int>>>>> complexNested = {
        {1, {
            {2, {
                {"a", {1, 2, 3}},
                {"b", {4, 5, 6}}
            }},
            {3, {
                {"c", {7, 8, 9}},
                {"d", {10, 11, 12}}
            }}
        }},
        {4, {
            {5, {
                {"e", {13, 14, 15}},
                {"f", {16, 17, 18}}
            }}
        }}
    };
    cout << "Testing complex nested structure: " << complexNested << endl;
    return 0;
}
