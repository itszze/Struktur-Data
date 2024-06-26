/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Fungsi untuk menampilkan pesan selamat datang dan instruksi penggunaan program
void pesanSelamatDatang() {
    
    cout << endl;
    
    cout << " Nama        : Meyze HadiShopia" << endl;
    cout << " Nim         : 20230801188" << endl;
    cout << " Mata Kuliah : Struktur Data" << endl;
    cout << " Dosen       : Ryan Putra Laksana, S.Kom., M.M." << endl;
    cout << " Tgl tugas   : Rabu, 12 Juni 2024" << endl << endl;

    cout << " ======================================================\n";
    cout << " * Selamat datang di Program Pengolah Kata Sederhana! *\n";
    cout << " ======================================================\n";
    cout << " Perintah yang tersedia:                              =\n";
    cout << " 1. Ketik       => (Mencetak teks)                    =\n";
    cout << " 2. Undo        => (Batalkan aksi terakhir)           =\n";
    cout << " 3. Redo        => (Ulangi aksi yang dibatalkan)      =\n";
    cout << " 4. IsEmptyUndo => (Periksa apakah undo kosong)       =\n";
    cout << " 5. IsEmptyRedo => (Periksa apakah redo kosong)       =\n";
    cout << " 6. Keluar      => (Menutup program)                  =\n";
    cout << " ==========||========||=======||========||=============\n\n";
}

// Fungsi untuk mencetak teks saat ini
void cetakTeksSaatIni(const string& teks) {
    cout << " Teks Saat Ini: " << teks << "\n";
}

int main() {
    // Stack untuk menyimpan status undo dan redo
    stack<string> tumpukanUndo;
    stack<string> tumpukanRedo;
    string teksSaatIni;

    // Menampilkan pesan selamat datang
    pesanSelamatDatang();

    int perintah;
    while (true) {
        cout << " Masukkan nomor perintah (1-6): ";
        cin >> perintah;

        if (perintah == 1) {
            string teks;
            cin.ignore(); // Mengabaikan karakter newline yang tersisa oleh std::cin
            cout << " Masukkan teks yang ingin diketik: ";
            getline(cin, teks); // Membaca teks yang akan diketik
            tumpukanUndo.push(teksSaatIni); // Menyimpan status teks saat ini ke dalam tumpukan undo
            while (!tumpukanRedo.empty()) {
                tumpukanRedo.pop(); // Mengosongkan tumpukan redo
            }
            teksSaatIni += teks; // Menambahkan teks baru ke teks saat ini
            cetakTeksSaatIni(teksSaatIni); // Mencetak teks saat ini
        } else if (perintah == 2) {
            if (!tumpukanUndo.empty()) {
                tumpukanRedo.push(teksSaatIni); // Menyimpan status teks saat ini ke dalam tumpukan redo
                teksSaatIni = tumpukanUndo.top(); // Mengambil status teks terakhir dari tumpukan undo
                tumpukanUndo.pop(); // Menghapus status teks terakhir dari tumpukan undo
                cetakTeksSaatIni(teksSaatIni); // Mencetak teks saat ini
            } else {
                cout << " Tumpukan undo kosong.\n"; // Pesan jika tumpukan undo kosong
            }
        } else if (perintah == 3) {
            if (!tumpukanRedo.empty()) {
                tumpukanUndo.push(teksSaatIni); // Menyimpan status teks saat ini ke dalam tumpukan undo
                teksSaatIni = tumpukanRedo.top(); // Mengambil status teks terakhir dari tumpukan redo
                tumpukanRedo.pop(); // Menghapus status teks terakhir dari tumpukan redo
                cetakTeksSaatIni(teksSaatIni); // Mencetak teks saat ini
            } else {
                cout << " Tumpukan redo kosong.\n"; // Pesan jika tumpukan redo kosong
            }
        } else if (perintah == 4) {
            cout << (tumpukanUndo.empty() ? " Tumpukan undo kosong.\n" : " Tumpukan undo tidak kosong.\n");
        } else if (perintah == 5) {
            cout << (tumpukanRedo.empty() ? " Tumpukan redo kosong.\n" : " Tumpukan redo tidak kosong.\n");
        } else if (perintah == 6) {
            break; // Keluar dari program
        } else {
            cout << " Perintah tidak valid, Silakan coba lagi.\n"; // Pesan jika perintah tidak valid
        }
    }

    return 0;
}
