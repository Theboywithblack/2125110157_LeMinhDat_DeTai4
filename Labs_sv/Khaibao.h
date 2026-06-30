#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>

struct FileNode {
    std::string name;
    bool isFolder;
    int size;
    FileNode* parent;
    std::list<FileNode*> children;

    FileNode(std::string n, bool folder, int s = 0, FileNode* p = nullptr)
        : name(n), isFolder(folder), size(s), parent(p) {
    }
};

class FileExplorer {
private:
    FileNode* root;
    FileNode* current;
    std::stack<FileNode*> backHistory;
    std::stack<FileNode*> forwardHistory;

    void deleteTree(FileNode* node);
    void printTree(FileNode* node, std::string prefix, bool isLast);
    int calcSizeRecursive(FileNode* node);
    void saveRecursive(FileNode* node, std::ofstream& out, int depth);

public:
    FileExplorer();
    ~FileExplorer();

    void pwd();
    void ls();
    void mkdir(std::string name);
    void touch(std::string name, int size);
    void rm(std::string name);
    void rename(std::string oldName, std::string newName);

    void cd(std::string name);
    void back();
    void forward();

    void tree();
    void find(std::string name);
    void calcTotalSize();

    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);
};

#endif