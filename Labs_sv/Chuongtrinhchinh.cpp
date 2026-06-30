#include "Khaibao.h"
#include <iostream>

void displayMenu() {
    std::cout << "\n===== MINI FILE EXPLORER =====\n";
    std::cout << "1. pwd - Hien thi duong dan hien tai\n";
    std::cout << "2. ls - Liet ke file/thu muc\n";
    std::cout << "3. mkdir - Tao thu muc\n";
    std::cout << "4. touch - Tao file moi\n";
    std::cout << "5. rm - Xoa file/thu muc\n";
    std::cout << "6. rename - Doi ten\n";
    std::cout << "7. cd - Di chuyen thu muc (go .. de quay lai)\n";
    std::cout << "8. back - Quay lai lich su (Stack)\n";
    std::cout << "9. forward - Tien toi lich su (Stack)\n";
    std::cout << "10. tree - Hien thi cau truc cay ASCII\n";
    std::cout << "11. find - Tim kiem file (BFS)\n";
    std::cout << "12. size - Tinh tong dung luong (Post-order)\n";
    std::cout << "13. save - Luu cau truc ra file txt\n";
    std::cout << "14. load - Doc cau truc tu file txt\n";
    std::cout << "0. Thoat\n";
    std::cout << "==============================\n";
    std::cout << "Chon chuc nang: ";
}

int main() {
    FileExplorer fs;
    int choice;
    std::string name, newName;
    int size;

    while (true) {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1: fs.pwd(); break;
        case 2: fs.ls(); break;
        case 3:
            std::cout << "Nhap ten thu muc: "; std::cin >> name;
            fs.mkdir(name); break;
        case 4:
            std::cout << "Nhap ten file: "; std::cin >> name;
            std::cout << "Nhap dung luong (KB): "; std::cin >> size;
            fs.touch(name, size); break;
        case 5:
            std::cout << "Nhap ten can xoa: "; std::cin >> name;
            fs.rm(name); break;
        case 6:
            std::cout << "Nhap ten cu: "; std::cin >> name;
            std::cout << "Nhap ten moi: "; std::cin >> newName;
            fs.rename(name, newName); break;
        case 7:
            std::cout << "Nhap ten thu muc (hoac ..): "; std::cin >> name;
            fs.cd(name); break;
        case 8: fs.back(); break;
        case 9: fs.forward(); break;
        case 10: fs.tree(); break;
        case 11:
            std::cout << "Nhap ten can tim: "; std::cin >> name;
            fs.find(name); break;
        case 12: fs.calcTotalSize(); break;
        case 13: fs.saveToFile("filesystem.txt"); break;
        case 14: fs.loadFromFile("filesystem.txt"); break;
        case 0: return 0;
        default: std::cout << "Lua chon khong hop le.\n";
        }
    }
    return 0;
}