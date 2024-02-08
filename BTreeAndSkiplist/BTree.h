#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include <vector>
#include <memory>

template<typename T>
class BTreeNode : public std::enable_shared_from_this<BTreeNode<T>>{
private:
    std::vector<T>keys;
    int minDegree;
    std::vector<std::shared_ptr<BTreeNode<T>>>children;
    int keyCount;
    bool isLeaf;
public:
    BTreeNode(int minDegree,bool isLeaf):minDegree(minDegree),isLeaf(isLeaf),keyCount(0){
        keys.resize(2*minDegree-1);
        children.resize(2*minDegree);
    }

    void insertNonFull(T key);

    void splitChild(int index,std::shared_ptr<BTreeNode<T>>child);

    void traverse();

    std::shared_ptr<BTreeNode<T>> search(T key);

    template<typename U>
    friend class BTree;
};

template<typename T>
class BTree{
private:
    std::shared_ptr<BTreeNode<T>> root;
    int minDegree;

public:
    BTree(int minDegree):root(nullptr),minDegree(minDegree){}

    void traverse(){
        if (root!=nullptr) root->traverse();
    }

    std::shared_ptr<BTreeNode<T>> search(int key){
        if(root==nullptr)
            return nullptr;
        return root->search(key);
    }

    void insert(T key);
};

template<typename T>
void BTreeNode<T>::traverse(){
    int index;
    for(index=0;index<keyCount;index++){
        if(!isLeaf) children[index]->traverse();
        std::cout<<" "<<keys[index];
    }
    if(!isLeaf) children[index]->traverse();
}
template<typename T>
std::shared_ptr<BTreeNode<T>> BTreeNode<T>::search(T key){
    int index=0;
    while(index<keyCount&&key>keys[index]) index++;
    if(index<keys.size()&&keys[index]==key) return std::enable_shared_from_this<BTreeNode<T>>::shared_from_this();
    if(isLeaf) return nullptr;
    return children[index]->search(key);
}
template<typename T>
void BTreeNode<T>::splitChild(int index,std::shared_ptr<BTreeNode<T>>child){
    std::shared_ptr<BTreeNode<T>> newChild = std::make_shared<BTreeNode<T>>(child->minDegree,child->isLeaf);
    newChild->keyCount = minDegree-1;

    for(int j=0;j<minDegree-1;j++){
        newChild->keys[j] = child->keys[j+minDegree];
    }

    if(!child->isLeaf){
        for(int j=0;j<minDegree;j++){
            newChild->children[j] = child->children[j+minDegree];
        }
    }
    child->keyCount = minDegree-1;

    for (int j=keyCount;j>=index+1;j--){
        children[j+1] = children[j];
    }
    children[index+1] = newChild;

    for(int j=keyCount-1;j>=index;j--){
        keys[j+1]=keys[j];
    }
    keys[index] = child->keys[minDegree-1];
    keyCount++;
}
template<typename T>
void BTreeNode<T>::insertNonFull(T key){
    int index = keyCount-1;
    if(isLeaf){
        while(index>=0&&keys[index]>key){
            keys[index+1] = keys[index];
            index--;
        }
        keys[index+1] = key;
        keyCount++; 
    }else{
        while(index>=0&&keys[index]>key) index--;
        if (children[index+1]->keyCount == 2*minDegree-1){
            splitChild(index+1,children[index+1]);
            if(keys[index+1]<key) index++;
        }
        children[index+1]->insertNonFull(key);
    }

}
template<typename T>
void BTree<T>::insert(T key){
    if(root==nullptr){
        root = std::make_shared<BTreeNode<T>>(minDegree,true);
        root->keys[0] = key;
        root->keyCount = 1;
    }else{
        if(root->keyCount == 2*minDegree-1){
            
            std::shared_ptr<BTreeNode<T>> newNode = std::make_shared<BTreeNode<T>>(minDegree,false);
            newNode->children[0] = root;
            newNode->splitChild(0,root);
            int index = 0;
            if(newNode->keys[0]<key){
                index++;
            }
            newNode->children[index]->insertNonFull(key);

            root = newNode;
            
        }else{
            root->insertNonFull(key);
        }
    }
}
#endif 