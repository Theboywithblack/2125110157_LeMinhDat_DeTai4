#include "Khaibao.h"

FileExplorer::FileExplorer() {
    root = new FileNode("root", true);
    current = root;
}

FileExplorer::~FileExplorer() {
    deleteTree(root);
}

void FileExplorer::deleteTree(FileNode* node) {
    if (!node) return;
    for (auto child : node->children) {
        deleteTree(child);
    }
    delete node;
}

void FileExplorer::pwd() {
    std::string path = "";
    FileNode* temp = current;
    while (temp != nullptr) {
        path = "/" + temp->name + path;
        temp = temp->parent;
    }
    std::cout << "Current Path: " << path << "\n";
}

void FileExplorer::ls() {
    std::cout << "Contents of " << current->name << ":\n";
    for (auto child : current->children) {
        std::cout << (child->isFolder ? "[DIR] " : "[FILE] ") << child->name
            << (child->isFolder ? "" : " (" + std::to_string(child->size) + " KB)") << "\n";
    }
}

void FileExplorer::mkdir(std::string name) {
    for (auto child : current->children) {
        if (child->name == name && child->isFolder) {
            std::cout << "Folder already exists!\n";
            return;
        }
    }
    current->children.push_back(new FileNode(name, true, 0, current));
    std::cout << "Folder created: " << name << "\n";
}

void FileExplorer::touch(std::string name, int size) {
    for (auto child : current->children) {
        if (child->name == name && !child->isFolder) {
            std::cout << "File already exists!\n";
            return;
        }
    }
    current->children.push_back(new FileNode(name, false, size, current));
    std::cout << "File created: " << name << " (" << size << " KB)\n";
}

void FileExplorer::rm(std::string name) {
    for (auto it = current->children.begin(); it != current->children.end(); ++it) {
        if ((*it)->name == name) {
            deleteTree(*it);
            current->children.erase(it);
            std::cout << "Deleted " << name << "\n";
            return;
        }
    }
    std::cout << "Not found: " << name << "\n";
}

void FileExplorer::rename(std::string oldName, std::string newName) {
    for (auto child : current->children) {
        if (child->name == oldName) {
            child->name = newName;
            std::cout << "Renamed to " << newName << "\n";
            return;
        }
    }
    std::cout << "Not found: " << oldName << "\n";
}

void FileExplorer::cd(std::string name) {
    if (name == "..") {
        if (current->parent != nullptr) {
            backHistory.push(current);
            while (!forwardHistory.empty()) forwardHistory.pop();
            current = current->parent;
            pwd();
        }
        else {
            std::cout << "Already at root.\n";
        }
        return;
    }

    for (auto child : current->children) {
        if (child->name == name && child->isFolder) {
            backHistory.push(current);
            while (!forwardHistory.empty()) forwardHistory.pop();
            current = child;
            pwd();
            return;
        }
    }
    std::cout << "Folder not found.\n";
}

void FileExplorer::back() {
    if (!backHistory.empty()) {
        forwardHistory.push(current);
        current = backHistory.top();
        backHistory.pop();
        pwd();
    }
    else {
        std::cout << "No backward history.\n";
    }
}

void FileExplorer::forward() {
    if (!forwardHistory.empty()) {
        backHistory.push(current);
        current = forwardHistory.top();
        forwardHistory.pop();
        pwd();
    }
    else {
        std::cout << "No forward history.\n";
    }
}

void FileExplorer::tree() {
    std::cout << ".\n";
    printTree(current, "", true);
}

void FileExplorer::printTree(FileNode* node, std::string prefix, bool isLast) {
    if (!node) return;
    int count = 0;
    int total = node->children.size();
    for (auto child : node->children) {
        count++;
        bool lastChild = (count == total);
        std::cout << prefix << (lastChild ? "└── " : "├── ") << child->name << "\n";
        if (child->isFolder) {
            printTree(child, prefix + (lastChild ? "    " : "│   "), lastChild);
        }
    }
}

void FileExplorer::find(std::string name) {
    // Sử dụng Queue cho thuật toán BFS tìm kiếm
    std::queue<FileNode*> q;
    q.push(current);
    bool found = false;

    std::cout << "Search results for '" << name << "':\n";
    while (!q.empty()) {
        FileNode* node = q.front();
        q.pop();

        if (node->name == name) {
            std::cout << "- Found at folder level.\n";
            found = true;
        }

        for (auto child : node->children) {
            q.push(child);
        }
    }
    if (!found) std::cout << "No files or folders found with that name.\n";
}

int FileExplorer::calcSizeRecursive(FileNode* node) {
    if (!node) return 0;
    if (!node->isFolder) return node->size; // Post-order: tính leaf

    int total = 0;
    for (auto child : node->children) {
        total += calcSizeRecursive(child); // Duyệt Post-order
    }
    return total;
}

void FileExplorer::calcTotalSize() {
    int total = calcSizeRecursive(current);
    std::cout << "Total size of current directory: " << total << " KB\n";
}

void FileExplorer::saveRecursive(FileNode* node, std::ofstream& out, int depth) {
    if (!node) return;
    out << depth << "|" << node->name << "|" << node->isFolder << "|" << node->size << "\n";
    for (auto child : node->children) {
        saveRecursive(child, out, depth + 1);
    }
}

void FileExplorer::saveToFile(std::string filename) {
    std::ofstream out(filename);
    if (out.is_open()) {
        saveRecursive(root, out, 0);
        out.close();
        std::cout << "Tree saved to " << filename << "\n";
    }
    else {
        std::cout << "Error opening file for writing.\n";
    }
}

void FileExplorer::loadFromFile(std::string filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "File not found.\n";
        return;
    }

    deleteTree(root);
    while (!backHistory.empty()) backHistory.pop();
    while (!forwardHistory.empty()) forwardHistory.pop();

    std::string line;
    FileNode* lastNodeAtDepth[100] = { nullptr };

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string depthStr, name, isFolderStr, sizeStr;
        std::getline(ss, depthStr, '|');
        std::getline(ss, name, '|');
        std::getline(ss, isFolderStr, '|');
        std::getline(ss, sizeStr, '|');

        int depth = std::stoi(depthStr);
        bool isFolder = (isFolderStr == "1");
        int size = std::stoi(sizeStr);

        FileNode* newNode = new FileNode(name, isFolder, size);

        if (depth == 0) {
            root = newNode;
        }
        else {
            FileNode* parentNode = lastNodeAtDepth[depth - 1];
            newNode->parent = parentNode;
            parentNode->children.push_back(newNode);
        }
        lastNodeAtDepth[depth] = newNode;
    }
    current = root;
    in.close();
    std::cout << "Tree loaded successfully.\n";
}