#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>

using namespace std;

const int MAX_MENU = 50;
const int MAX_MEJA = 10;
const int MAX_BAHAN = 20;

struct Menu {
    int id;
    string nama;
    int harga;
};

struct Meja {
    int id;
    string status;
    string nama_pelanggan;
    bool is_member;
    int tagihan_sementara;
};

struct BahanBaku {
    int id;
    string nama;
    int stok;
};

Menu dataMenu[MAX_MENU];
int jumlahMenu = 0;
Meja dataMeja[MAX_MEJA];
BahanBaku dataBahan[MAX_BAHAN];
int jumlahBahan = 0;

void inisialisasiData() {
    dataMenu[0] = {1, "Mie Ayam", 12000};
    dataMenu[1] = {2, "Nasi Goreng Spesial", 20000};
    dataMenu[2] = {3, "Es Teh Manis", 5000};
    jumlahMenu = 3;

    for (int i = 0; i < MAX_MEJA; i++) {
        dataMeja[i] = {i + 1, "Kosong", "-", false, 0};
    }

    dataBahan[0] = {1, "Beras", 50};
    dataBahan[1] = {2, "Mie", 30};
    dataBahan[2] = {3, "Ayam", 20};
    jumlahBahan = 3;
}

int cariMejaKosong() {
    for (int i = 0; i < MAX_MEJA; i++) {
        if (dataMeja[i].status == "Kosong") {
            return dataMeja[i].id;
        }
    }
    return -1;
}

void cariStokBahan(string keyword) {
    bool ditemukan = false;
    cout << "\nHasil Pencarian Bahan Baku '" << keyword << "':\n";
    for (int i = 0; i < jumlahBahan; i++) {
        if (dataBahan[i].nama.find(keyword) != string::npos) {
            cout << "- " << dataBahan[i].nama << " | Stok: " << dataBahan[i].stok << " unit\n";
            ditemukan = true;
        }
    }
    if (!ditemukan) cout << "Bahan baku tidak ditemukan atau stok habis.\n";
}

void urutkanMenuBerdasarkanHarga(Menu* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->harga > (arr + j + 1)->harga) {
                Menu temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

void tampilkanMenu() {
    urutkanMenuBerdasarkanHarga(dataMenu, jumlahMenu);
    cout << "\n=== DAFTAR MENU (Diurutkan dari Termurah) ===\n";
    for (int i = 0; i < jumlahMenu; i++) {
        cout << dataMenu[i].id << ". " << dataMenu[i].nama << " - Rp" << dataMenu[i].harga << "\n";
    }
}

void kelolaMenu() {
    int pilihan;
    do {
        cout << "\n=== KELOLA MENU (MANAGER) ===\n";
        cout << "1. Tambah Menu\n2. Edit Menu\n3. Hapus Menu\n4. Kembali\nPilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            if (jumlahMenu < MAX_MENU) {
                cout << "Nama Menu Baru: "; getline(cin, dataMenu[jumlahMenu].nama);
                cout << "Harga: Rp"; cin >> dataMenu[jumlahMenu].harga;
                dataMenu[jumlahMenu].id = jumlahMenu + 1;
                jumlahMenu++;
                cout << "Menu berhasil ditambahkan!\n";
            } else { cout << "Kapasitas menu penuh!\n"; }
        } 
        else if (pilihan == 2) {
            tampilkanMenu();
            int idEdit; cout << "Masukkan ID Menu yang mau diedit: "; cin >> idEdit;
            bool found = false;
            for (int i = 0; i < jumlahMenu; i++) {
                if (dataMenu[i].id == idEdit) {
                    cin.ignore();
                    cout << "Nama Baru: "; getline(cin, dataMenu[i].nama);
                    cout << "Harga Baru: Rp"; cin >> dataMenu[i].harga;
                    cout << "Menu diupdate!\n"; found = true; break;
                }
            }
            if (!found) cout << "ID tidak ditemukan.\n";
        }
        else if (pilihan == 3) {
            tampilkanMenu();
            int idHapus; cout << "Masukkan ID Menu yang dihapus: "; cin >> idHapus;
            int indexHapus = -1;
            for (int i = 0; i < jumlahMenu; i++) {
                if (dataMenu[i].id == idHapus) { indexHapus = i; break; }
            }
            if (indexHapus != -1) {
                for (int i = indexHapus; i < jumlahMenu - 1; i++) {
                    dataMenu[i] = dataMenu[i + 1];
                }
                jumlahMenu--;
                cout << "Menu dihapus!\n";
            } else { cout << "ID tidak ditemukan.\n"; }
        }
    } while (pilihan != 4);
}

int hitungTotalTagihanMejaRekursif(int index) {
    if (index >= MAX_MEJA) return 0;
    return dataMeja[index].tagihan_sementara + hitungTotalTagihanMejaRekursif(index + 1);
}

void fiturBooking() {
    int mejaTersedia = cariMejaKosong();
    if (mejaTersedia != -1) {
        int idx = mejaTersedia - 1;
        cout << "\nMeja " << mejaTersedia << " tersedia. Masukkan Nama Pemesan: ";
        cin.ignore(); getline(cin, dataMeja[idx].nama_pelanggan);
        dataMeja[idx].status = "Booking";
        cout << "Meja " << mejaTersedia << " berhasil di-booking atas nama " << dataMeja[idx].nama_pelanggan << "!\n";
    } else {
        cout << "Maaf, semua meja penuh!\n";
    }
}

void catatPesanan() {
    int idMeja;
    cout << "\nNomor Meja Pelanggan (1-" << MAX_MEJA << "): "; cin >> idMeja;
    if (idMeja < 1 || idMeja > MAX_MEJA) return;
    int idx = idMeja - 1;

    if (dataMeja[idx].status == "Kosong") {
        dataMeja[idx].status = "Isi";
        cout << "Nama Pelanggan: "; cin.ignore(); getline(cin, dataMeja[idx].nama_pelanggan);
    } else if (dataMeja[idx].status == "Booking") {
        cout << "Meja ini telah di-booking oleh " << dataMeja[idx].nama_pelanggan << ". Lanjut pesanan (y/n)? ";
        char acc; cin >> acc;
        if (acc == 'y' || acc == 'Y') dataMeja[idx].status = "Isi";
        else return;
    }

    tampilkanMenu();
    char tambahLagi;
    do {
        int pilihId, jumlah;
        cout << "Masukkan ID Menu: "; cin >> pilihId;
        cout << "Jumlah porsi: "; cin >> jumlah;
        
        for (int i = 0; i < jumlahMenu; i++) {
            if (dataMenu[i].id == pilihId) {
                dataMeja[idx].tagihan_sementara += (dataMenu[i].harga * jumlah);
                cout << dataMenu[i].nama << " ditambahkan ke pesanan meja " << idMeja << ".\n";
            }
        }
        cout << "Tambah menu lain? (y/n): "; cin >> tambahLagi;
    } while (tambahLagi == 'y' || tambahLagi == 'Y');
}

void pembayaranKasir() {
    int idMeja;
    cout << "\nNomor Meja yang akan membayar (1-" << MAX_MEJA << "): "; cin >> idMeja;
    int idx = idMeja - 1;

    if (dataMeja[idx].tagihan_sementara == 0) {
        cout << "Meja tidak memiliki tagihan aktif.\n"; return;
    }

    cout << "\nTotal Tagihan Meja " << idMeja << " (" << dataMeja[idx].nama_pelanggan << "): Rp" << dataMeja[idx].tagihan_sementara;
    cout << "\nApakah pelanggan ini punya Member? (y/n): ";
    char isMember; cin >> isMember;
    
    double totalBayar = dataMeja[idx].tagihan_sementara;
    if (isMember == 'y' || isMember == 'Y') {
        dataMeja[idx].is_member = true;
        totalBayar = totalBayar * 0.9;
        cout << "\nDiskon Member 10% diaplikasikan!\n";
    }

    cout << "TOTAL YANG HARUS DIBAYAR: Rp" << fixed << setprecision(0) << totalBayar << "\n";
    
    ofstream file("riwayat_transaksi.txt", ios::app);
    if(file.is_open()) {
        file << "Meja " << idMeja << " | Pelanggan: " << dataMeja[idx].nama_pelanggan 
             << " | Member: " << (dataMeja[idx].is_member ? "Ya" : "Tidak") 
             << " | Total Bayar: Rp" << totalBayar << "\n";
        file.close();
    }

    dataMeja[idx] = {idMeja, "Kosong", "-", false, 0};
    cout << "Pembayaran berhasil dicetak ke 'riwayat_transaksi.txt'. Meja dikosongkan.\n";
}

void menuManager() {
    int opsi;
    do {
        cout << "\n=== DASHBOARD MANAGER ===\n";
        cout << "1. Kelola Menu Makanan (CRUD)\n";
        cout << "2. Cek Ketersediaan Stok Bahan Baku\n";
        cout << "3. Laporan Total Tagihan Berjalan (Rekursif)\n";
        cout << "4. Logout\nPilih: ";
        cin >> opsi;
        if (opsi == 1) kelolaMenu();
        else if (opsi == 2) {
            string key; cout << "Masukkan nama bahan (contoh: Ayam): "; cin >> key;
            cariStokBahan(key);
        }
        else if (opsi == 3) {
            cout << "\nTotal Seluruh Tagihan Berjalan (Belum Dibayar): Rp" 
                 << hitungTotalTagihanMejaRekursif(0) << endl;
        }
    } while (opsi != 4);
}

void menuKasir() {
    int opsi;
    do {
        cout << "\n=== DASHBOARD KASIR ===\n";
        cout << "1. Pembayaran & Cetak Struk (Member/Diskon)\n";
        cout << "2. Status Meja\n";
        cout << "3. Logout\nPilih: ";
        cin >> opsi;
        if (opsi == 1) pembayaranKasir();
        else if (opsi == 2) {
            cout << "\n=== STATUS MEJA ===\n";
            for(int i=0; i<MAX_MEJA; i++) {
                cout << "Meja " << dataMeja[i].id << " | Status: " << dataMeja[i].status 
                     << " | Atas Nama: " << dataMeja[i].nama_pelanggan 
                     << " | Tagihan: Rp" << dataMeja[i].tagihan_sementara << "\n";
            }
        }
    } while (opsi != 3);
}

void menuPelayan() {
    int opsi;
    do {
        cout << "\n=== DASHBOARD PELAYAN ===\n";
        cout << "1. Cek Meja Kosong\n";
        cout << "2. Booking Meja\n";
        cout << "3. Input Pesanan Pelanggan\n";
        cout << "4. Logout\nPilih: ";
        cin >> opsi;
        
        if (opsi == 1) {
            int meja = cariMejaKosong();
            if (meja != -1) cout << "\nMeja kosong tersedia di Meja nomor " << meja << ".\n";
            else cout << "\nSemua meja saat ini penuh.\n";
        }
        else if (opsi == 2) fiturBooking();
        else if (opsi == 3) catatPesanan();
    } while (opsi != 4);
}

string inputPasswordBintang() {
    string pwd = "";
    char ch;
    while (true) {
        ch = getch();
        if (ch == 13) {
            break;
        } else if (ch == 8) {
            if (pwd.length() > 0) {
                cout << "\b \b";
                pwd.erase(pwd.length() - 1);
            }
        } else {
            pwd += ch;
            cout << "*";
        }
    }
    cout << endl;
    return pwd;
}

int main() {
    inisialisasiData();
    string username, password;
    bool systemRun = true;

    while (systemRun) {
        cout << "\n====================================\n";
        cout << "   SISTEM MANAJEMEN RESTORAN\n";
        cout << "====================================\n";
        cout << "Username (ketik 'exit' untuk tutup): "; cin >> username;
        
        if (username == "exit") {
            cout << "Sistem dimatikan.\n";
            break;
        }
        
        cout << "Password: "; 
        password = inputPasswordBintang();

        if (username == "manager" && password == "123") {
            cout << "\n[ Login Berhasil sebagai Manager ]\n";
            menuManager();
        } 
        else if (username == "kasir" && password == "123") {
            cout << "\n[ Login Berhasil sebagai Kasir ]\n";
            menuKasir();
        } 
        else if (username == "pelayan" && password == "123") {
            cout << "\n[ Login Berhasil sebagai Pelayan ]\n";
            menuPelayan();
        } 
        else {
            cout << "\n[ ERROR: Username atau Password Salah! ]\n";
        }
    }
    return 0;
}
