#include <iostream>
#include <mysql/mysql.h>
#include <sstream>

using namespace std;

const char* hostname = "127.0.0.1";
const char* user = "root";
const char* pass = "123";
const char* dbname = "gramedia";
unsigned int port = 31235;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connect_db() {
    MYSQL* conn = mysql_init(0);
    if (conn) {
        conn = mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag);
        if (conn) {
            cout << "Terhubung ke basis data dengan sukses." << endl;
        } else {
            cerr << "Koneksi gagal: " << mysql_error(conn) << endl;
        }
    } else {
        cerr << "mysql_init gagal" << endl;
    }
    return conn;
}

void add_book(const string& title, const string& author, const string& publisher, const string& genre, int year, int price) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "INSERT INTO buku (judul, penulis, penerbit, genre, tahun, harga) VALUES ('" << title << "', '" << author << "', '" << publisher << "', '" << genre << "', " << year << ", " << price << ")";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "INSERT gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil ditambahkan." << endl;
        }
        mysql_close(conn);
    }
}

void show_books() {
    MYSQL* conn = connect_db();
    if (conn) {
        if (mysql_query(conn, "SELECT * FROM buku")) {
            cerr << "SELECT gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << ", Judul: " << row[1] << ", Penulis: " << row[2] << ", Penerbit: " << row[3] << ", Genre: " << row[4] << ", Tahun: " << row[5] << ", Harga: Rp." << row[6] << endl;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
}

void update_book(int book_id, const string& title, const string& author, const string& publisher, const string& genre, int year, int price) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE buku SET judul = '" << title << "', penulis = '" << author << "', penerbit = '" << publisher << "', genre = '" << genre << "', tahun = " << year << ", harga = " << price << " WHERE id = " << book_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "UPDATE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil diperbarui." << endl;
        }
        mysql_close(conn);
    }
}

void delete_book(int book_id) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "DELETE FROM buku WHERE id = " << book_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "DELETE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil dihapus." << endl;
        }
        mysql_close(conn);
    }
}

void admin_menu() {
    int choice;
    while (true) {
        cout << "\nMenu Admin:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Semua Buku\n";
        cout << "3. Perbarui Buku\n";
        cout << "4. Hapus Buku\n";
        cout << "5. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            string title, author, publisher, genre;
            int year, price;
            cout << "Masukkan judul buku: ";
            cin.ignore();
            getline(cin, title);
            cout << "Masukkan penulis: ";
            getline(cin, author);
            cout << "Masukkan penerbit: ";
            getline(cin, publisher);
            cout << "Masukkan genre: ";
            getline(cin, genre);
            cout << "Masukkan tahun terbit: ";
            cin >> year;
            cout << "Masukkan harga (tanpa titik atau koma): Rp.";
            cin >> price;
            add_book(title, author, publisher, genre, year, price);
        } else if (choice == 2) {
            show_books();
        } else if (choice == 3) {
            int book_id, year, price;
            string title, author, publisher, genre;
            cout << "Masukkan ID buku yang akan diperbarui: ";
            cin >> book_id;
            cin.ignore();
            cout << "Masukkan judul baru: ";
            getline(cin, title);
            cout << "Masukkan penulis baru: ";
            getline(cin, author);
            cout << "Masukkan penerbit baru: ";
            getline(cin, publisher);
            cout << "Masukkan genre baru: ";
            getline(cin, genre);
            cout << "Masukkan tahun terbit baru: ";
            cin >> year;
            cout << "Masukkan harga baru (tanpa titik atau koma): Rp.";
            cin >> price;
            update_book(book_id, title, author, publisher, genre, year, price);
        } else if (choice == 4) {
            int book_id;
            cout << "Masukkan ID buku yang akan dihapus: ";
            cin >> book_id;
            delete_book(book_id);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

void user_menu() {
    int choice;
    while (true) {
        cout << "\nMenu User:\n";
        cout << "1. Tampilkan Semua Buku\n";
        cout << "2. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            show_books();
        } else if (choice == 2) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

int main() {
    int role_choice;
    cout << "Pilih peran:\n";
    cout << "1. Admin\n";
    cout << "2. User\n";
    cout << "Masukkan pilihan: ";
    cin >> role_choice;

    if (role_choice == 1) {
        admin_menu();
    } else if (role_choice == 2) {
        user_menu();
    } else {
        cout << "Pilihan tidak valid." << endl;
    }

    return 0;
}
