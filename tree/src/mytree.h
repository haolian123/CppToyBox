#ifndef MYTREE
#define MYTREE
#include <dirent.h>
// #include "dirent.h"
#include <iostream>
#include <string>
#include <vector>
#include<memory>




// 文件节点基类
class FileNode {
protected:
    std::string fileName;

public:
    FileNode(const std::string& name) : fileName(name) {}

    // 纯虚函数，派生类必须实现
    virtual void add(const std::shared_ptr<FileNode>& fileNode) = 0;
    virtual void add(std::shared_ptr<FileNode>&& fileNode) = 0;
    virtual void display(int depth, bool last) = 0;
};

// 文件类，继承自文件节点基类
class File : public FileNode {
public:
    File(const std::string& name) : FileNode(name) {}

    // 不允许在文件中添加文件或文件夹
    void add(const std::shared_ptr<FileNode>& fileNode) override {
        std::cout << "无法添加到文件中" << std::endl;
    }

    void add(std::shared_ptr<FileNode>&& fileNode) override {
        std::cout << "无法添加到文件中" << std::endl;
    }

    // 显示文件信息
    void display(int depth, bool last) override {
        std::string indentation = "";
        for (int i = 0; i < depth; ++i) {
            if (i == depth - 1) {
                if (last) {
                    indentation += "└─── ";
                } else {
                    indentation += "├─── ";
                }
            } else {
                indentation += "│   ";
            }
        }
        std::cout << indentation << fileName << std::endl;
    }
};

// 文件夹类，继承自文件节点基类
class Folder : public FileNode {
private:
    std::vector<std::shared_ptr<FileNode>> children;

public:
    // 构造函数
    Folder(const std::string& name) : FileNode(name) {}

    Folder(std::string&& name) : FileNode(std::move(name)) {}

    // 允许在文件夹中添加文件或文件夹
    void add(const std::shared_ptr<FileNode>& fileNode) override {
        children.emplace_back(fileNode);
    }

    void add(std::shared_ptr<FileNode>&& fileNode) override {
        children.emplace_back(std::move(fileNode));
    }

    // 显示文件夹及其子项信息
    void display(int depth, bool last) override {
        std::string indentation = "";
        for (int i = 0; i < depth; ++i) {
            if (i == depth - 1) {
                if (last) {
                    indentation += "└─── ";
                } else {
                    indentation += "├─── ";
                }
            } else {
                indentation += "│   ";
            }
        }
        std::cout << indentation << fileName << "/" << std::endl;

        for (size_t i = 0; i < children.size(); ++i) {
            children[i]->display(depth + 1, i == children.size() - 1);
        }
    }
};



// 文件树类
class FileTree {
private:
    // 递归获取目录列表
    void getDirList(const std::string& directoryPath, std::shared_ptr<FileNode>& curFolder);

public:
    // 构建并显示文件树
    void tree(std::string folderPath = ".") {
        std::shared_ptr<FileNode> root(new Folder(folderPath));
        getDirList(folderPath, root);
        root->display(0, true);
    }
};

// 递归得到文件列表
void FileTree::getDirList(const std::string& directoryPath, std::shared_ptr<FileNode>& curFolder) {
    DIR* dir = opendir(directoryPath.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) {
                // 文件
                curFolder->add(std::make_shared<File>(std::string(entry->d_name)));
            } else {
                // 文件夹
                auto folder_name = std::string(entry->d_name);
                if (folder_name == ".." || folder_name == ".") {
                    continue;
                }
                std::shared_ptr<FileNode> thisFolder(new Folder(folder_name));
                curFolder->add(thisFolder);
                getDirList(directoryPath + '/' + folder_name, thisFolder);
            }
        }
        closedir(dir);
    } else {
        std::cerr << "无法打开目录" << std::endl;
    }
}

#endif