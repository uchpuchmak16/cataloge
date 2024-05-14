#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Book {
    std::string id;
    std::string author;
    std::string title;
    int pages;
};

void addBook(std::ofstream& file, const Book& book) {
    file << book.id << " " << book.author << " " << book.title << " " << book.pages << "\n";
}

void viewAllBooks(std::ifstream& file) {
    Book book;
    while (file >> book.id >> book.author >> book.title >> book.pages) {
        std::cout << "ID: " << book.id << ", Author: " << book.author << ", Title: " << book.title << ", Pages: " << book.pages << "\n";
    }
}

void deleteBook(const std::string& id, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file.\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.find(id) == 0) {
            continue;
        }
        lines.push_back(line);
    }

    inFile.close();

    std::ofstream outFile(filename);
    for (const auto& l : lines) {
        outFile << l << "\n";
    }

    outFile.close();
}

void searchBook(const std::string& id, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file.\n";
        return;
    }

    Book book;
    bool found = false;
    while (inFile >> book.id >> book.author >> book.title >> book.pages) {
        if (book.id == id) {
            found = true;
            break;
        }
    }

    inFile.close();

    if (found) {
        std::cout << "Book found - ID: " << book.id << ", Author: " << book.author << ", Title: " << book.title << ", Pages: " << book.pages << "\n";
    }
    else {
        std::cout << "Book with ID " << id << " not found.\n";
    }
}

int main() {
    std::ofstream catalogFile("books.txt", std::ios::app);

    // Пример добавления новой записи
    Book newBook = { "0003", "J.R.R. Tolkien", "The Lord of the Rings", 1178 };
    addBook(catalogFile, newBook);

    catalogFile.close();

    std::ifstream readFile("books.txt");

    // Просмотр всех записей
    viewAllBooks(readFile);

    readFile.close();

    // Удаление записи
    deleteBook("0002", "books.txt");

    // Поиск записи
    searchBook("0001", "books.txt");

    return 0;
}
