#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

struct Book {
    std::string title;
    std::string description;
    std::string publisher;
    int year;
    std::string ISBN;
};

std::vector<std::string> tokenize(const std::string &str) {
    std::vector<std::string> tokens;
    std::string token;
    for (char ch : str) {
        if (ch == ' ') {
            tokens.push_back(token);
            token = "";
        } else {
            token += ch;
        }
    }
    tokens.push_back(token);
    return tokens;
}

bool compareBooks(const Book &book1, const Book &book2) {
    return book1.title < book2.title;
}

int main () {
    std::vector<Book> library;
    char choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Tambah Buku\n";
        std::cout << "2. Cari Buku\n";
        std::cout << "3. Tampilkan Semua Buku (urut berdasarkan judul)\n";
        std::cout << "4. Keluar\n";
        std::cout << "Pilihan Anda: ";
        std::cin >> choice;

        switch(choice) {
            case '1': {
                Book newBook;
                std::cin.ignore();

                std::cout << "Nama Buku: ";
                std::getline(std::cin, newBook.title);

                std::cout << "Deskripsi Buku: ";
                std::getline(std::cin, newBook.description);

                std::cout << "Penerbit: ";
                std::getline(std::cin, newBook.publisher);

                std::cout << "Tahun Terbit: ";
                std::cin >> newBook.year;

                std::cout << "ISBN: ";
                std::cin >> newBook.ISBN;

                library.push_back(newBook);
                break;
            }
            case '2': {
                std::string keyword;
                std::cin.ignore();

                std::cout << "Masukan kata kunci: ";
                std::getline(std::cin, keyword);

                std::vector<std::string> searchKeywords = tokenize(keyword);

                std::vector<Book> searchResults;
                for (const auto &book : library) {
                    bool found = true;
                    for (const auto &kw : searchKeywords) {
                        if (book.title.find(kw) == std::string::npos &&
                        book.description.find(kw) == std::string::npos &&
                        book.publisher.find(kw) == std::string::npos &&
                        std::to_string(book.year).find(kw) == std::string::npos &&
                        book.ISBN.find(kw) == std::string::npos) {
                            found = false;
                            break;
                        }
                    }
                    if (found) {
                        searchResults.push_back(book);
                    }
                }

                if (searchResults.empty()) {
                    std::cout << "Buku tidak ditemukan.\n";
                } else {
                    for (const auto &book : searchResults) {
                        std::cout << "Nama Buku: " << book.title << '\n';
                        std::cout << "Deskripsi Buku: " << book.description << '\n';
                        std::cout << "Penerbit: " << book.publisher << '\n';
                        std::cout << "Tahun Terbit: " << book.year << '\n';
                        std::cout << "ISBN: " << book.ISBN << "\n\n";
                    }
                }
                break;
            }
            case '3': {
                std::vector<Book> sortedLibrary = library;
                std::sort(sortedLibrary.begin(), sortedLibrary.end(), compareBooks);
                std::cout << "Daftar Buku (Urut Berdasarkan Judul):\n";
                for (const auto &book : sortedLibrary) {
                    std::cout << "Nama Buku: " << book.title << '\n';
                    std::cout << "Deskripsi Buku: " << book.description << '\n';
                    std::cout << "Penerbit: " << book.publisher << '\n';
                    std::cout << "Tahun Terbit: " << book.year << '\n';
                    std::cout << "ISBN: " << book.ISBN << "\n\n";
                }
                break;
            }
            case '4':
                std::cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != '4');

    return 0;
}