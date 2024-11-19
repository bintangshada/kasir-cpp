#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

const int MAX_BARANG = 100;
const int MAX_PELANGGAN = 10;
const int MAX_TRANSAKSI = 10;

string namaBarang[MAX_BARANG];
double hargaBarang[MAX_BARANG];
int jumlahBarang[MAX_BARANG];

string transaksiNama[MAX_PELANGGAN][MAX_TRANSAKSI][MAX_BARANG];
double transaksiHarga[MAX_PELANGGAN][MAX_TRANSAKSI][MAX_BARANG];
int transaksiJumlah[MAX_PELANGGAN][MAX_TRANSAKSI][MAX_BARANG];

int jumlahBarangTotal = 0;
int jumlahTransaksi[MAX_PELANGGAN] = {0};

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void tampilkanBarang() {
    cout << left << setw(5) << "ID" << setw(20) << "Nama Barang" << setw(10) << "Harga" << setw(10) << "Jumlah" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < jumlahBarangTotal; i++) {
        cout << left << setw(5) << i + 1 << setw(20) << namaBarang[i] << setw(10) << hargaBarang[i] << setw(10) << jumlahBarang[i] << endl;
    }
}

void tampilkanIDPelanggan() {
    cout << "\n--- ID Pelanggan yang telah melakukan pembelian ---\n";
    for (int idPelanggan = 0; idPelanggan < MAX_PELANGGAN; idPelanggan++) {
        if (jumlahTransaksi[idPelanggan] > 0) {
            cout << "Pelanggan ID: " << idPelanggan + 1 << "\n";
        }
    }
}

void tambahBarang() {
    clearScreen();
    tampilkanBarang();
    cout << "\n--- Tambah Barang ---\n";
    cout << "Masukkan nama barang: ";
    cin >> namaBarang[jumlahBarangTotal];
    cout << "Masukkan harga barang: ";
    while (!(cin >> hargaBarang[jumlahBarangTotal])) {
        cout << "Input tidak valid. Masukkan harga barang: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Masukkan jumlah barang: ";
    while (!(cin >> jumlahBarang[jumlahBarangTotal])) {
        cout << "Input tidak valid. Masukkan jumlah barang: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    jumlahBarangTotal++;
    cout << "\nBarang berhasil ditambahkan!\n";
}

void tambahTransaksi(int idPelanggan) {
    clearScreen();
    tampilkanBarang();
    cout << "\n--- Tambah Transaksi ---\n";
    int indeksBarang, jumlah;
    cout << "Masukkan indeks barang: ";
    while (!(cin >> indeksBarang) || indeksBarang < 1 || indeksBarang > jumlahBarangTotal) {
        cout << "Input tidak valid. Masukkan indeks barang: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Masukkan jumlah: ";
    while (!(cin >> jumlah) || jumlah < 1 || jumlah > jumlahBarang[indeksBarang - 1]) {
        cout << "Input tidak valid atau stok tidak mencukupi. Masukkan jumlah: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    transaksiNama[idPelanggan][jumlahTransaksi[idPelanggan]][indeksBarang - 1] = namaBarang[indeksBarang - 1];
    transaksiHarga[idPelanggan][jumlahTransaksi[idPelanggan]][indeksBarang - 1] = hargaBarang[indeksBarang - 1];
    transaksiJumlah[idPelanggan][jumlahTransaksi[idPelanggan]][indeksBarang - 1] = jumlah;
    jumlahBarang[indeksBarang - 1] -= jumlah;
    jumlahTransaksi[idPelanggan]++;
    cout << "\nTransaksi berhasil ditambahkan!\n";
}

void tampilkanSemuaTransaksi() {
    clearScreen();
    cout << "\n--- Semua Transaksi ---\n";
    for (int idPelanggan = 0; idPelanggan < MAX_PELANGGAN; idPelanggan++) {
        if (jumlahTransaksi[idPelanggan] > 0) {
            cout << "Transaksi untuk pelanggan " << idPelanggan + 1 << ":\n";
            cout << left << setw(5) << "ID" << setw(20) << "Nama Barang" << setw(10) << "Harga" << setw(10) << "Jumlah" << setw(10) << "Subtotal" << endl;
            cout << "--------------------------------------------------------------------------" << endl;
            double totalBelanja = 0;
            for (int i = 0; i < jumlahTransaksi[idPelanggan]; i++) {
                for (int j = 0; j < jumlahBarangTotal; j++) {
                    if (transaksiJumlah[idPelanggan][i][j] > 0) {
                        double subtotal = transaksiHarga[idPelanggan][i][j] * transaksiJumlah[idPelanggan][i][j];
                        totalBelanja += subtotal;
                        cout << left << setw(5) << j + 1 << setw(20) << transaksiNama[idPelanggan][i][j] << setw(10) << transaksiHarga[idPelanggan][i][j] << setw(10) << transaksiJumlah[idPelanggan][i][j] << setw(10) << subtotal << endl;
                    }
                }
            }
            cout << "Total Belanja: Rp" << totalBelanja << "\n\n";
        }
    }
}

void cetakStruk(int idPelanggan) {
    clearScreen();
    double total = 0;
    cout << "\n--- Struk untuk pelanggan " << idPelanggan + 1 << " ---\n";
    cout << left << setw(5) << "ID" << setw(20) << "Nama Barang" << setw(10) << "Harga" << setw(10) << "Jumlah" << setw(10) << "Subtotal" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    for (int i = 0; i < jumlahTransaksi[idPelanggan]; i++) {
        for (int j = 0; j < jumlahBarangTotal; j++) {
            if (transaksiJumlah[idPelanggan][i][j] > 0) {
                double subtotal = transaksiHarga[idPelanggan][i][j] * transaksiJumlah[idPelanggan][i][j];
                total += subtotal;
                cout << left << setw(5) << j + 1 << setw(20) << transaksiNama[idPelanggan][i][j] << setw(10) << transaksiHarga[idPelanggan][i][j] << setw(10) << transaksiJumlah[idPelanggan][i][j] << setw(10) << subtotal << endl;
            }
        }
    }
    cout << "Total: Rp" << total << "\n";
}

void ubahStok() {
    clearScreen();
    tampilkanBarang();
    cout << "\n--- Ubah Stok Barang ---\n";
    int indeksBarang, jumlahBaru;
    cout << "Masukkan indeks barang: ";
    while (!(cin >> indeksBarang) || indeksBarang < 1 || indeksBarang > jumlahBarangTotal) {
        cout << "Input tidak valid. Masukkan indeks barang: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Masukkan jumlah stok baru: ";
    while (!(cin >> jumlahBaru) || jumlahBaru < 0) {
        cout << "Input tidak valid. Masukkan jumlah stok baru: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    jumlahBarang[indeksBarang - 1] = jumlahBaru;
    cout << "\nStok barang berhasil diubah!\n";
}

void tampilkanMenu() {
    cout << "=========================================\n";
    cout << "          Program Kasir Sederhana        \n";
    cout << "=========================================\n";
    cout << "1. Tambah Barang\n";
    cout << "2. Tampilkan Barang\n";
    cout << "3. Tambah Transaksi\n";
    cout << "4. Tampilkan Semua Transaksi\n";
    cout << "5. Cetak Struk\n";
    cout << "6. Ubah Stok\n";
    cout << "7. Keluar\n";
    cout << "=========================================\n";
    cout << "Masukkan pilihan Anda: ";
}

int main() {
    int pilihan, idPelanggan;

    while (true) {
        clearScreen();
        tampilkanMenu();
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 7) {
            cout << "Input tidak valid. Masukkan pilihan Anda: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        clearScreen();
        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilkanBarang();
                break;
            case 3:
                tampilkanIDPelanggan();
                cout << "Masukkan ID pelanggan (ID pelanggan adalah nomor unik yang diberikan kepada setiap pelanggan): ";
                while (!(cin >> idPelanggan) || idPelanggan < 1 || idPelanggan > MAX_PELANGGAN) {
                    cout << "Input tidak valid. Masukkan ID pelanggan: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                tambahTransaksi(idPelanggan - 1);
                break;
            case 4:
                tampilkanSemuaTransaksi();
                break;
            case 5:
                tampilkanIDPelanggan();
                cout << "Masukkan ID pelanggan: ";
                while (!(cin >> idPelanggan) || idPelanggan < 1 || idPelanggan > MAX_PELANGGAN) {
                    cout << "Input tidak valid. Masukkan ID pelanggan: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cetakStruk(idPelanggan - 1);
                break;
            case 6:
                ubahStok();
                break;
            case 7:
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
    }

    return 0;
}