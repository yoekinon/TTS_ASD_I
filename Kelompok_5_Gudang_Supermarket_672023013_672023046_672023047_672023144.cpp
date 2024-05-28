#include <iostream>
#include <string>
#include <numeric>
#include <conio.h>

using namespace std;

const int MAX_STOCK = 100;

struct Item {
    string nama;
    int jumlah;
};

class StokGudang {
private: 
    Item stok[MAX_STOCK];
    int jumlahItem;

public:
    StokGudang() : jumlahItem(0) {}

    void input_barang(const string& nama, int jumlah) {
        if (jumlahItem < MAX_STOCK) {
            stok[jumlahItem] = {nama, jumlah};
            jumlahItem++;
            cout << "Data '" << nama << "' dengan jumlah " << jumlah << " berhasil diinput." << endl;
        } else {
            cout << "Stok gudang penuh." << endl;
        }
    }

    void update_barang(int indeks, const string& nama_baru, int jumlah_baru) {
        if (indeks >= 0 && indeks < jumlahItem) {
            string nama_lama = stok[indeks].nama;
            int jumlah_lama = stok[indeks].jumlah;
            stok[indeks] = {nama_baru, jumlah_baru};
            cout << "Data di indeks " << indeks << " telah diubah dari '"
                 << nama_lama << "' (" << jumlah_lama  << ") menjadi '"
                 << nama_baru << "' (" << jumlah_baru << ")." << endl;
        } else {
            cout << "Indeks tidak valid." << endl;
        }
    }

    void tampilkan_barang() const {
        if (jumlahItem == 0) {
            cout << "Belum ada data yang diinput." << endl;
        } else {
            cout << "Data yang telah diinput:" << endl;
            for (int i = 0; i < jumlahItem; ++i) {
                cout << "Indeks " << i << ": " << stok[i].nama << " - " << stok[i].jumlah << endl;
            }
        }
    }

    void tampilkan_ratarata() const {
        if (jumlahItem == 0) {
            cout << "Tidak ada data yang bisa dihitung rata-ratanya." << endl;
        } else {
            int total = 0;
            for (int i = 0; i < jumlahItem; ++i) {
                total += stok[i].jumlah;
            }
            double average = static_cast<double>(total) / jumlahItem;
            cout << "Rata-rata jumlah stok: " << average << endl;
        }
    }

    void exit_program() const {
        cout << "Keluar dari program." << endl;
    }
};

int main() {
    StokGudang gudang;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Input barang\n";
        cout << "2. Ubah barang\n";
        cout << "3. Tampilkan barang\n";
        cout << "4. Tampilkan rata-rata jumlah stok\n";
        cout << "5. Keluar\n";

        cout << "Pilih opsi: ";
        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            system("cls");
            string nama;
            int jumlah;
            cout << "inputkan data yang ditentukan dari setiap tema: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan jumlah barang: ";
            cin >> jumlah;
            gudang.input_barang(nama, jumlah);
            cin.ignore();
            cin.get();
            system("cls");
        } else if (pilihan == 2) {
            system("cls");
            int indeks;
            string nama_baru;
            int jumlah_baru;
            cout << "Masukkan indeks data yang ingin diubah: ";
            cin >> indeks;
            cout << "Masukkan nama baru: ";
            cin.ignore();
            getline(cin, nama_baru);
            cout << "Masukkan jumlah baru: ";
            cin >> jumlah_baru;
            gudang.update_barang(indeks, nama_baru, jumlah_baru);
            cin.ignore();
            cin.get();
            system("cls");
        } else if (pilihan == 3) {
            system("cls");
            gudang.tampilkan_barang();
            cin.ignore();
            cin.get();
            system("cls");
        } else if (pilihan == 4) {
            system("cls");
            gudang.tampilkan_ratarata();
            cin.ignore();
            cin.get();
            system("cls");
        } else if (pilihan == 5) {
            gudang.exit_program();
            break;
        } else {
            cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    }

    return 0;
}
