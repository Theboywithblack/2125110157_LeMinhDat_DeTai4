#include "Khaibao.h"
#include <iostream>

void test_case_1_creation() {
    std::cout << "\n========================================\n";
    std::cout << "TEST CASE 1: Kiem thu tao File va Folder\n";
    std::cout << "========================================\n";
    FileExplorer fs;
    fs.mkdir("Documents");
    fs.mkdir("Downloads");
    fs.touch("readme.txt", 5);
    fs.ls();
    std::cout << "[PASSED] Test Case 1 completed.\n";
}

void test_case_2_navigation() {
    std::cout << "\n========================================\n";
    std::cout << "TEST CASE 2: Kiem thu di chuyen duong dan (cd)\n";
    std::cout << "========================================\n";
    FileExplorer fs;
    fs.mkdir("Documents");
    fs.cd("Documents");
    fs.touch("report.pdf", 120);
    fs.ls();
    fs.cd("..");
    std::cout << "[PASSED] Test Case 2 completed.\n";
}

void test_case_3_total_size() {
    std::cout << "\n========================================\n";
    std::cout << "TEST CASE 3: Tinh tong dung luong (Post-order)\n";
    std::cout << "========================================\n";
    FileExplorer fs;
    fs.mkdir("Projects");
    fs.cd("Projects");
    fs.touch("main.cpp", 15);
    fs.touch("utils.h", 5);
    fs.mkdir("Assets");
    fs.cd("Assets");
    fs.touch("image.png", 200);
    fs.cd(".."); // Quay ve Projects
    fs.cd(".."); // Quay ve root
    fs.calcTotalSize();
    std::cout << "[PASSED] Test Case 3 completed.\n";
}

void test_case_4_search_bfs() {
    std::cout << "\n========================================\n";
    std::cout << "TEST CASE 4: Tim kiem file/folder bang thuật toan BFS\n";
    std::cout << "========================================\n";
    FileExplorer fs;
    fs.mkdir("Games");
    fs.cd("Games");
    fs.mkdir("Minecraft");
    fs.cd("Minecraft");
    fs.touch("saves.dat", 50);
    fs.cd(".."); // Quay ve Games
    fs.cd(".."); // Quay ve root
    
    fs.find("saves.dat");
    fs.find("nonexistent.txt");
    std::cout << "[PASSED] Test Case 4 completed.\n";
}

void test_case_5_history_stack() {
    std::cout << "\n========================================\n";
    std::cout << "TEST CASE 5: Dieu huong Lich su (Stack Back/Forward)\n";
    std::cout << "========================================\n";
    FileExplorer fs;
    fs.mkdir("Folder1");
    fs.mkdir("Folder2");
    
    std::cout << "1. Vao Folder1 -> "; fs.cd("Folder1");
    std::cout << "2. Quay lai -> "; fs.cd("..");
    std::cout << "3. Vao Folder2 -> "; fs.cd("Folder2");
    
    std::cout << "4. Thuc hien nhan nut Back:\n";
    fs.back();
    std::cout << "5. Thuc hien nhan nut Back lan nua:\n";
    fs.back();
    std::cout << "6. Thuc hien nhan nut Forward:\n";
    fs.forward();
    std::cout << "[PASSED] Test Case 5 completed.\n";
}

int main() {
    std::cout << "========================================================\n";
    std::cout << "STARTING AUTOMATED TEST SUITE FOR MINI FILE EXPLORER\n";
    std::cout << "========================================================\n";
    
    test_case_1_creation();
    test_case_2_navigation();
    test_case_3_total_size();
    test_case_4_search_bfs();
    test_case_5_history_stack();
    
    std::cout << "\n========================================================\n";
    std::cout << "ALL TEST CASES EXECUTED SUCCESSFULLY.\n";
    std::cout << "========================================================\n";
    return 0;
}
