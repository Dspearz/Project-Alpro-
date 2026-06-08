#include <iostream>
#include <string>
#include <ctime>
using namespace std;

const int MAX_MEJA = 5;
const int MAX_STAFF = 100;
const int MAX_PELANGGAN = 200;
const int MAX_PESANAN = 500;
const int MAX_DETAIL = 2000;
const int JUMLAH_MENU = 12;
const int MAX_BAHAN_BAKU = 100;
const int MAX_PESANAN_BAHAN = 100;

// Struktur untuk Tanggal
struct Tanggal {
    int hari;
    int bulan;
    int tahun;
};

// Struktur untuk Waktu
struct Waktu {
    int jam;
    int menit;
    int detik;
};

// Fungsi untuk mendapatkan tanggal sekarang
Tanggal getTanggalSekarang() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Tanggal t;
    t.hari = ltm->tm_mday;
    t.bulan = ltm->tm_mon + 1;
    t.tahun = ltm->tm_year + 1900;
    return t;
}

// Fungsi untuk mendapatkan waktu sekarang
Waktu getWaktuSekarang() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Waktu w;
    w.jam = ltm->tm_hour;
    w.menit = ltm->tm_min;
    w.detik = ltm->tm_sec;
    return w;
}

// Fungsi untuk menampilkan tanggal
void tampilkanTanggal(Tanggal t) {
    cout << t.hari << "/" << t.bulan << "/" << t.tahun;
}

// Fungsi untuk menampilkan waktu
void tampilkanWaktu(Waktu w) {
    cout << w.jam << ":" << w.menit << ":" << w.detik;
}

// Struktur untuk Bahan Baku
struct BahanBaku {
    int id;
    int id_staff;
    string nama;
    string jenis;
    int stok;
    string satuan;
    int harga_per_kg;
    Tanggal tanggal_dipesan; // Tanggal terakhir kali dipesan
};

BahanBaku dataBahanBaku[MAX_BAHAN_BAKU] = {
    {1, 2, "Ayam", "Protein", 50000, "g", 45000, {0,0,0}},
    {2, 2, "Mie", "Karbohidrat", 60000, "g", 20000, {0,0,0}},
    {3, 2, "Daun Bawang", "Sayuran", 4000, "g", 15000, {0,0,0}},
    {4, 2, "Kecap", "Pelengkap", 3000, "ml", 22000, {0,0,0}},
    {5, 2, "Garam", "Bumbu", 2000, "g", 8000, {0,0,0}},
    {6, 6, "Minyak Goreng", "Pelengkap", 25000, "ml", 17000, {0,0,0}},
    {7, 6, "Telur", "Protein", 80, "butir", 28000, {0,0,0}},
    {8, 6, "Nasi", "Karbohidrat", 100000, "g", 14000, {0,0,0}},
    {9, 6, "Ati Ampela", "Protein", 25000, "g", 38000, {0,0,0}},
    {10, 6, "Cabai", "Bumbu", 4500, "g", 60000, {0,0,0}},
    {11, 9, "Gula", "Bumbu", 30000, "g", 13000, {0,0,0}},
    {12, 9, "Teh", "Minuman", 10000, "g", 60000, {0,0,0}},
    {13, 9, "Jeruk", "Buah", 50, "buah", 24000, {0,0,0}},
    {14, 9, "Susu Bubuk", "Minuman", 4000, "g", 95000, {0,0,0}},
    {15, 9, "Coklat Bubuk", "Minuman", 3500, "g", 80000, {0,0,0}},
    {16, 10, "Kopi Bubuk", "Minuman", 5000, "g", 120000, {0,0,0}},
    {17, 10, "Es Batu", "Pelengkap", 100000, "g", 2000, {0,0,0}},
    {18, 10, "Persa Vanila", "Pelengkap", 2000, "ml", 75000, {0,0,0}},
    {19, 10, "Sirup Gula", "Pelengkap", 3000, "ml", 30000, {0,0,0}},
    {20, 9, "Kelapa Kopyor", "Pelengkap", 30000, "g", 40000, {0,0,0}},
    {21, 9, "Kelapa Serut", "Pelengkap", 30000, "g", 35000, {0,0,0}},
    {22, 9, "Nangka", "Buah", 25, "buah", 20000, {0,0,0}}
};

int jumlahBahanBaku = 22;

// Struktur untuk Resep Menu (bahan yang dibutuhkan per menu)
struct ResepMenu {
    int id_menu;
    int id_bahan_baku;
    int jumlah_dibutuhkan;
    string satuan;
};

ResepMenu dataResep[] = {
    // Mie Ayam
    {1, 2, 100, "g"},  // Mie
    {1, 1, 50, "g"},   // Ayam
    {1, 3, 10, "g"},   // Daun Bawang
    {1, 4, 10, "ml"},  // Kecap
    {1, 5, 5, "g"},    // Garam
    
    // Magelangan
    {2, 2, 80, "g"},   // Mie
    {2, 8, 80, "g"},   // Nasi
    {2, 1, 40, "g"},   // Ayam
    {2, 4, 10, "ml"},  // Kecap
    {2, 5, 5, "g"},    // Garam
    
    // Nasi Goreng Biasa
    {3, 8, 150, "g"},  // Nasi
    {3, 6, 15, "ml"},  // Minyak Goreng
    {3, 5, 5, "g"},    // Garam
    
    // Nasi Goreng Telur
    {4, 8, 150, "g"},  // Nasi
    {4, 7, 1, "butir"}, // Telur
    {4, 6, 15, "ml"},  // Minyak Goreng
    {4, 5, 5, "g"},    // Garam
    
    // Nasi Goreng Ati
    {5, 8, 150, "g"},  // Nasi
    {5, 9, 30, "g"},   // Ati Ampela
    {5, 6, 15, "ml"},  // Minyak Goreng
    {5, 5, 5, "g"},    // Garam
    
    // Mie Goreng Telur
    {6, 2, 100, "g"},  // Mie
    {6, 7, 1, "butir"}, // Telur
    {6, 6, 15, "ml"},  // Minyak Goreng
    {6, 5, 5, "g"},    // Garam
    
    // Es Teh
    {7, 12, 5, "g"},   // Teh
    {7, 11, 10, "g"},  // Gula
    {7, 17, 50, "g"},  // Es Batu
    
    // Es Jeruk
    {8, 13, 1, "buah"}, // Jeruk
    {8, 11, 10, "g"},  // Gula
    {8, 17, 50, "g"},  // Es Batu
    
    // Teh Panas
    {9, 12, 5, "g"},   // Teh
    {9, 11, 10, "g"},  // Gula
    
    // Soda Gembira
    {10, 19, 20, "ml"}, // Sirup Gula
    {10, 17, 50, "g"}, // Es Batu
    
    // Es Kopyor
    {11, 20, 30, "g"}, // Kelapa Kopyor
    {11, 21, 20, "g"}, // Kelapa Serut
    {11, 17, 50, "g"}, // Es Batu
    
    // Es Teler
    {12, 22, 1, "buah"}, // Nangka
    {12, 21, 20, "g"}, // Kelapa Serut
    {12, 17, 50, "g"}  // Es Batu
};

int jumlahResep = 36;

string meja_status[MAX_MEJA] = {"Kosong", "Kosong", "Kosong", "Kosong", "Kosong"};
string meja_nama[MAX_MEJA] = {"-", "-", "-", "-", "-"};
int meja_id_pelanggan[MAX_MEJA] = {0,0,0,0,0};
int totalPendapatanMeja[MAX_MEJA] = {0, 0, 0, 0, 0};
int jumlahPesananMeja[MAX_MEJA] = {0, 0, 0, 0, 0};

string nama_menu[JUMLAH_MENU] = {
    "Mie Ayam", 
    "Magelangan",
    "Nasi Goreng Biasa",
    "Nasi Goreng Telur",
    "Nasi Goreng Ati",
    "Mie Goreng Telur",
    "Es Teh",
    "Es Jeruk",
    "Teh Panas",
    "Soda Gembira",
    "Es Kopyor",
    "Es Teler"
};

int harga_menu[JUMLAH_MENU] = {
    12000,
    13000,
    10000,
    12000,
    14000,
    10000,
    5000,
    7000,
    5000,
    15000,
    12000,
    13000
};

int stok_menu[JUMLAH_MENU] = {
    50,50,50,50,50,50,50,50,50,50,50,50
};

static string namaStaff[MAX_STAFF];
static string jabatan[MAX_STAFF];
static int gaji[MAX_STAFF];
static int jumlahStaff = 0;

struct Pelanggan {
    int id;
    string nama;
    string telepon;
    Tanggal tanggal_daftar; // Tanggal pertama kali mendaftar
};

Pelanggan dataPelanggan[MAX_PELANGGAN];
int jumlahPelanggan = 0;

struct Pesanan {
    int id;
    int id_meja;
    int id_pelanggan;
    int id_staff;
    int total_harga;
    Tanggal tanggal_pesan;
    Waktu waktu_pesan;
};

Pesanan dataPesanan[MAX_PESANAN];
int jumlahPesanan = 0;

struct DetailPesanan {
    int id;
    int id_pesanan;
    int id_menu;
    int jumlah;
    int subtotal;
};

DetailPesanan detailPesanan[MAX_DETAIL];
int jumlahDetail = 0;

// Struktur untuk Pesanan Bahan Baku
struct PesananBahan {
    int id;
    int id_pemasok;
    int id_bahan_baku;
    int jumlah;
    Tanggal tanggal_pesan;
    string status;
};

PesananBahan dataPesananBahan[MAX_PESANAN_BAHAN];
int jumlahPesananBahan = 0;

const int MAX_PEMASOK = 10;

struct Pemasok {
    int id;
    string nama;
    string domisili;
    string telepon;
    string email;
    int id_manager;
};

Pemasok dataPemasok[MAX_PEMASOK] = {
    {1, "Agro Fresh", "Bandung", "081234567801", "agro@fresh.id", 1},
    {2, "Sumber Protein", "Jakarta", "081234567802", "sprotein@food.id", 2},
    {3, "Bumi Pangan", "Bogor", "081234567803", "bumi@pangan.id", 3},
    {4, "Nusantara Rasa", "Surabaya", "081234567804", "nusarasa@food.id", 1},
    {5, "Minuman Jaya", "Depok", "081234567805", "minum@jaya.id", 2},
    {6, "Tropical Supply", "Semarang", "081234567806", "tropi@supply.id", 3}
};

int jumlahPemasok = 6;

// Fungsi untuk mengecek ketersediaan bahan baku
bool cekKetersediaanBahan(int id_menu, int jumlah_pesanan) {
    for (int i = 0; i < jumlahResep; i++) {
        if (dataResep[i].id_menu == id_menu) {
            int id_bahan = dataResep[i].id_bahan_baku;
            int kebutuhan = dataResep[i].jumlah_dibutuhkan * jumlah_pesanan;
            
            // Cari stok bahan baku
            for (int j = 0; j < jumlahBahanBaku; j++) {
                if (dataBahanBaku[j].id == id_bahan) {
                    if (dataBahanBaku[j].stok < kebutuhan) {
                        cout << "Bahan baku '" << dataBahanBaku[j].nama 
                             << "' tidak cukup. Stok tersedia : " << dataBahanBaku[j].stok 
                             << " " << dataBahanBaku[j].satuan 
                             << ", dibutuhkan : " << kebutuhan << " " << dataBahanBaku[j].satuan << endl;
                        return false;
                    }
                    break;
                }
            }
        }
    }
    return true;
}

// Fungsi untuk mengurangi stok bahan baku setelah pemesanan
void kurangiStokBahan(int id_menu, int jumlah_pesanan) {
    for (int i = 0; i < jumlahResep; i++) {
        if (dataResep[i].id_menu == id_menu) {
            int id_bahan = dataResep[i].id_bahan_baku;
            int kebutuhan = dataResep[i].jumlah_dibutuhkan * jumlah_pesanan;
            
            for (int j = 0; j < jumlahBahanBaku; j++) {
                if (dataBahanBaku[j].id == id_bahan) {
                    dataBahanBaku[j].stok -= kebutuhan;
                    break;
                }
            }
        }
    }
}

void menuMeja() {
    cout << "\n=== STATUS MEJA ===\n";
    for (int i = 0; i < MAX_MEJA; i++) {
        cout << "Meja " << i+1
             << " | Status : " << meja_status[i]
             << " | Nama : " << meja_nama[i]
             << " | Total Pendapatan : Rp " << totalPendapatanMeja[i]
             << " | Jumlah Item : " << jumlahPesananMeja[i]
             << endl;
    }
    char pilih;
    cout << "\nKosongkan meja? (y/n): ";
    cin >> pilih;
    if (pilih == 'y' || pilih == 'Y') {
        int nomorMeja;
        cout << "Pilih nomor meja (1-" << MAX_MEJA << ") : ";
        cin >> nomorMeja;
        if (nomorMeja < 1 || nomorMeja > MAX_MEJA) return;
        int idx = nomorMeja - 1;
        meja_status[idx] = "Kosong";
        meja_nama[idx] = "-";
        meja_id_pelanggan[idx] = 0;
        cout << "Meja dikosongkan.\n";
    }
}

void buatPelangganUntukMeja(int idx) {
    jumlahPelanggan++;
    dataPelanggan[jumlahPelanggan-1].id = jumlahPelanggan;
    dataPelanggan[jumlahPelanggan-1].nama = meja_nama[idx];
    cout << "No Telepon Pelanggan : ";
    string tel;
    cin >> tel;
    dataPelanggan[jumlahPelanggan-1].telepon = tel;
    dataPelanggan[jumlahPelanggan-1].tanggal_daftar = getTanggalSekarang();
    meja_id_pelanggan[idx] = jumlahPelanggan;
}

void tambahDetailPesanan(int idPesanan, int idMenu, int jumlah, int subtotal) {
    if (jumlahDetail >= MAX_DETAIL) return;
    detailPesanan[jumlahDetail].id = jumlahDetail + 1;
    detailPesanan[jumlahDetail].id_pesanan = idPesanan;
    detailPesanan[jumlahDetail].id_menu = idMenu;
    detailPesanan[jumlahDetail].jumlah = jumlah;
    detailPesanan[jumlahDetail].subtotal = subtotal;
    jumlahDetail++;
}

void buatPesananBaru(int idx, int total, int totalItem) {
    if (jumlahPesanan >= MAX_PESANAN) return;
    jumlahPesanan++;
    dataPesanan[jumlahPesanan-1].id = jumlahPesanan;
    dataPesanan[jumlahPesanan-1].id_meja = idx + 1;
    dataPesanan[jumlahPesanan-1].id_pelanggan = meja_id_pelanggan[idx];
    dataPesanan[jumlahPesanan-1].id_staff = 0;
    dataPesanan[jumlahPesanan-1].total_harga = total;
    dataPesanan[jumlahPesanan-1].tanggal_pesan = getTanggalSekarang();
    dataPesanan[jumlahPesanan-1].waktu_pesan = getWaktuSekarang();
}

void pemesanan() {
    int meja;
    cout << "\nPilih meja (1-" << MAX_MEJA << ") : ";
    cin >> meja;
    while (meja < 1 || meja > MAX_MEJA) cin >> meja;
    int idx = meja - 1;

    cin.ignore();
    if (meja_status[idx] != "Isi") {
        cout << "Masukkan nama pelanggan : ";
        getline(cin, meja_nama[idx]);
        meja_status[idx] = "Isi";
        buatPelangganUntukMeja(idx);
    } else {
        if (meja_id_pelanggan[idx] == 0) {
            cout << "Masukkan nama pelanggan : ";
            getline(cin, meja_nama[idx]);
            buatPelangganUntukMeja(idx);
        } else {
            cout << "Lanjutkan pesanan untuk pelanggan : " << meja_nama[idx] << "\n";
        }
    }

    int total = 0;
    int totalItemPesananIni = 0;
    char confirm;
    do {
        cout << "\n_________________________________________-\n";
        cout << "|No|Nama Menu              |Harga    |Stok  |\n";
        cout << "|__|_______________________|_________|_____ |\n";
        for (int i = 0; i < JUMLAH_MENU; i++) {
            cout << "|" << i+1 << ".|" << nama_menu[i];
            for (int sp = nama_menu[i].length(); sp < 23; sp++) cout << " ";
            cout << " |Rp" << harga_menu[i] << "  |" << stok_menu[i] << "   |\n";
        }
        cout << "|__|_______________________|_________|_____|\n\n";

        int menu;
        do {
            cout << "Pilih Menu (1-" << JUMLAH_MENU << ") : ";
            cin >> menu;
        } while (menu < 1 || menu > JUMLAH_MENU);

        int jumlah;
        do {
            cout << "Jumlah : ";
            cin >> jumlah;
        } while (jumlah < 1);

        int index = menu - 1;
        
        // Cek ketersediaan bahan baku sebelum memproses pesanan
        if (!cekKetersediaanBahan(menu, jumlah)) {
            cout << "Pesanan tidak dapat diproses karena bahan baku tidak cukup.\n";
            cout << "Silakan pilih menu lain atau kurangi jumlah pesanan.\n";
            continue;
        }

        if (jumlah > stok_menu[index]) {
            cout << "Stok menu tidak cukup. Stok tersedia : " << stok_menu[index] << "\n";
            cout << "Pesanan dibatalkan untuk item ini.\n";
        } else {
            int subtotal = harga_menu[index] * jumlah;
            total += subtotal;
            totalItemPesananIni += jumlah;
            stok_menu[index] -= jumlah;
            
            // Kurangi stok bahan baku
            kurangiStokBahan(menu, jumlah);
            
            tambahDetailPesanan(jumlahPesanan + 1, index + 1, jumlah, subtotal);
        }

        cout << "Subtotal item ditambahkan.\n";
        cout << "Total sementara pesanan ini: Rp " << total << "\n";
        cout << "Tambah Pesanan Lagi? (y/n): ";
        cin >> confirm;
    } while (confirm == 'y' || confirm == 'Y');

    if (total > 0) {
        buatPesananBaru(idx, total, totalItemPesananIni);
        totalPendapatanMeja[idx] += total;
        jumlahPesananMeja[idx] += totalItemPesananIni;
        cout << "\n=== TOTAL AKHIR ===\n";
        cout << "Total Harga Akhir : Rp " << total << endl;
        cout << "Jumlah Item : " << totalItemPesananIni << endl;
        cout << "Waktu Pemesanan : ";
        tampilkanTanggal(dataPesanan[jumlahPesanan-1].tanggal_pesan);
        cout << " ";
        tampilkanWaktu(dataPesanan[jumlahPesanan-1].waktu_pesan);
        cout << endl;
    } else {
        cout << "Tidak ada item yang berhasil dipesan.\n";
    }
}

void menuPemasok() {
    int pilihan;

    do {
        cout << "\n=========== MENU PEMASOK ===========\n";
        cout << "1. Lihat Daftar Pemasok\n";
        cout << "2. Pesan Bahan Baku\n";
        cout << "3. Lihat Stok Bahan Baku\n";
        cout << "4. Lihat Riwayat Pesanan Bahan Baku\n";
        cout << "5. Kembali\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "\n======= DAFTAR PEMASOK =======\n";
            for (int i = 0; i < jumlahPemasok; i++) {
                cout << dataPemasok[i].id << ". "
                     << dataPemasok[i].nama
                     << " | " << dataPemasok[i].domisili
                     << " | " << dataPemasok[i].telepon
                     << " | " << dataPemasok[i].email
                     << " | Manager ID : " << dataPemasok[i].id_manager
                     << endl;
            }
        }
        else if (pilihan == 2) {
            int idp;
            cout << "\nMasukkan ID pemasok yang ingin dipesan : ";
            cin >> idp;

            bool ditemukan = false;
            for (int i = 0; i < jumlahPemasok; i++) {
                if (dataPemasok[i].id == idp) {
                    ditemukan = true;

                    cout << "\n=== FORM PEMESANAN BAHAN BAKU ===\n";
                    cout << "Pemasok : " << dataPemasok[i].nama << endl;
                    
                    // Tampilkan daftar bahan baku yang tersedia
                    cout << "\nDaftar Bahan Baku :\n";
                    for (int j = 0; j < jumlahBahanBaku; j++) {
                        cout << dataBahanBaku[j].id << ". " << dataBahanBaku[j].nama 
                             << " | Stok: " << dataBahanBaku[j].stok << " " << dataBahanBaku[j].satuan << endl;
                    }
                    
                    cout << "Masukkan ID bahan baku : ";
                    int id_bahan;
                    cin >> id_bahan;
                    
                    string nama_bahan = "";
                    for (int j = 0; j < jumlahBahanBaku; j++) {
                        if (dataBahanBaku[j].id == id_bahan) {
                            nama_bahan = dataBahanBaku[j].nama;
                            break;
                        }
                    }
                    
                    if (nama_bahan == "") {
                        cout << "ID bahan baku tidak ditemukan.\n";
                        break;
                    }

                    cout << "Masukkan jumlah (" << dataBahanBaku[id_bahan-1].satuan << ") : ";
                    int jml;
                    cin >> jml;

                    // Tambah stok bahan baku dan update tanggal dipesan
                    for (int j = 0; j < jumlahBahanBaku; j++) {
                        if (dataBahanBaku[j].id == id_bahan) {
                            dataBahanBaku[j].stok += jml;
                            dataBahanBaku[j].tanggal_dipesan = getTanggalSekarang();
                            break;
                        }
                    }

                    // Simpan riwayat pesanan bahan baku
                    if (jumlahPesananBahan < MAX_PESANAN_BAHAN) {
                        jumlahPesananBahan++;
                        dataPesananBahan[jumlahPesananBahan-1].id = jumlahPesananBahan;
                        dataPesananBahan[jumlahPesananBahan-1].id_pemasok = idp;
                        dataPesananBahan[jumlahPesananBahan-1].id_bahan_baku = id_bahan;
                        dataPesananBahan[jumlahPesananBahan-1].jumlah = jml;
                        dataPesananBahan[jumlahPesananBahan-1].tanggal_pesan = getTanggalSekarang();
                        dataPesananBahan[jumlahPesananBahan-1].status = "Selesai";
                    }

                    cout << "\n=== PESANAN BERHASIL ===\n";
                    cout << "Anda memesan " << jml << " " << dataBahanBaku[id_bahan-1].satuan 
                         << " \"" << nama_bahan
                         << "\" dari pemasok " << dataPemasok[i].nama << endl;
                    cout << "Stok " << nama_bahan << " sekarang : " 
                         << dataBahanBaku[id_bahan-1].stok << " " << dataBahanBaku[id_bahan-1].satuan << endl;
                    cout << "Tanggal dipesan : ";
                    tampilkanTanggal(dataBahanBaku[id_bahan-1].tanggal_dipesan);
                    cout << endl;
                }
            }

            if (!ditemukan) {
                cout << "ID pemasok tidak ditemukan.\n";
            }
        }
        else if (pilihan == 3) {
            cout << "\n======= STOK BAHAN BAKU =======\n";
            cout << "ID | Nama Bahan Baku      | Jenis       | Stok | Satuan | Harga/Kg | Terakhir Dipesan\n";
            cout << "___|______________________|_____________|______|________|__________|_________________\n";
            for (int i = 0; i < jumlahBahanBaku; i++) {
                cout << dataBahanBaku[i].id << "  | " << dataBahanBaku[i].nama;
                for (int sp = dataBahanBaku[i].nama.length(); sp < 21; sp++) cout << " ";
                cout << " | " << dataBahanBaku[i].jenis;
                for (int sp = dataBahanBaku[i].jenis.length(); sp < 12; sp++) cout << " ";
                cout << " | " << dataBahanBaku[i].stok;
                for (int sp = to_string(dataBahanBaku[i].stok).length(); sp < 5; sp++) cout << " ";
                cout << " | " << dataBahanBaku[i].satuan;
                for (int sp = dataBahanBaku[i].satuan.length(); sp < 7; sp++) cout << " ";
                cout << " | Rp " << dataBahanBaku[i].harga_per_kg;
                for (int sp = to_string(dataBahanBaku[i].harga_per_kg).length(); sp < 7; sp++) cout << " ";
                cout << " | ";
                if (dataBahanBaku[i].tanggal_dipesan.hari == 0) {
                    cout << "Belum pernah";
                } else {
                    tampilkanTanggal(dataBahanBaku[i].tanggal_dipesan);
                }
                cout << endl;
            }
        }
        else if (pilihan == 4) {
            cout << "\n======= RIWAYAT PESANAN BAHAN BAKU =======\n";
            if (jumlahPesananBahan == 0) {
                cout << "Belum ada riwayat pesanan bahan baku.\n";
            } else {
                cout << "ID | Pemasok ID | Bahan ID | Jumlah | Tanggal Pesan | Status\n";
                cout << "___|____________|__________|________|_______________|_______\n";
                for (int i = 0; i < jumlahPesananBahan; i++) {
                    cout << dataPesananBahan[i].id << "  | " << dataPesananBahan[i].id_pemasok;
                    for (int sp = to_string(dataPesananBahan[i].id_pemasok).length(); sp < 11; sp++) cout << " ";
                    cout << " | " << dataPesananBahan[i].id_bahan_baku;
                    for (int sp = to_string(dataPesananBahan[i].id_bahan_baku).length(); sp < 9; sp++) cout << " ";
                    cout << " | " << dataPesananBahan[i].jumlah;
                    for (int sp = to_string(dataPesananBahan[i].jumlah).length(); sp < 7; sp++) cout << " ";
                    cout << " | ";
                    tampilkanTanggal(dataPesananBahan[i].tanggal_pesan);
                    cout << " | " << dataPesananBahan[i].status << endl;
                }
            }
        }
        else if (pilihan != 5) {
            cout << "Pilihan invalid.\n";
        }

    } while (pilihan != 5);
}

void fungsiStaffJabatan() {
    int pilihan;
    char lanjut;

    do {
        cout << "\n=== SISTEM MANAJEMEN STAFF ===\n";
        cout << "1. Tambah Staff\n";
        cout << "2. Ubah Jabatan / Hapus Staff\n";
        cout << "3. Tampilkan Semua Staff\n";
        cout << "4. Kembali\n";
        cout << "Pilih Opsi : ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            do {
                if (jumlahStaff >= MAX_STAFF) break;
                cout << "Nama staff: ";
                getline(cin, namaStaff[jumlahStaff]);
                int pilihJab;
                cout << "1.Supervisor\n2.Kasir\n3.Chef\n4.Pelayan\n";
                cout << "Pilih opsi: ";
                cin >> pilihJab;
                cin.ignore();
                if (pilihJab == 1) jabatan[jumlahStaff] = "Supervisor", gaji[jumlahStaff] = 5000000;
                else if (pilihJab == 2) jabatan[jumlahStaff] = "Kasir", gaji[jumlahStaff] = 1500000;
                else if (pilihJab == 3) jabatan[jumlahStaff] = "Chef", gaji[jumlahStaff] = 3000000;
                else jabatan[jumlahStaff] = "Pelayan", gaji[jumlahStaff] = 1550000;
                jumlahStaff++;
                cout << "Tambah lagi? (y/n) : ";
                cin >> lanjut;
                cin.ignore();
            } while (lanjut == 'y' || lanjut == 'Y');
        }
        else if (pilihan == 2) {
            int subMenu;
            cout << "1. Ubah Jabatan\n2. Hapus Staff\n";
            cout << "Pilih Opsi : ";
            cin >> subMenu;
            cin.ignore();

            if (subMenu == 1) {
                string cari;
                cout << "Nama staff: ";
                getline(cin, cari);
                for (int i = 0; i < jumlahStaff; i++) {
                    if (namaStaff[i] == cari) {
                        int pilihBaru;
                        cout << "1.Supervisor\n2.Kasir\n3.Chef\n4.Pelayan\n";
                        cout << "Pilih Opsi : ";
                        cin >> pilihBaru;
                        cin.ignore();
                        if (pilihBaru == 1) jabatan[i] = "Supervisor", gaji[i] = 5000000;
                        else if (pilihBaru == 2) jabatan[i] = "Kasir", gaji[i] = 3000000;
                        else if (pilihBaru == 3) jabatan[i] = "Chef", gaji[i] = 4500000;
                        else jabatan[i] = "Pelayan", gaji[i] = 2500000;
                        break;
                    }
                }
            }
            else if (subMenu == 2) {
                string hapus;
                cout << "Nama staff : ";
                getline(cin, hapus);
                for (int i = 0; i < jumlahStaff; i++) {
                    if (namaStaff[i] == hapus) {
                        for (int j = i; j < jumlahStaff - 1; j++) {
                            namaStaff[j] = namaStaff[j+1];
                            jabatan[j] = jabatan[j+1];
                            gaji[j] = gaji[j+1];
                        }
                        jumlahStaff--;
                        break;
                    }
                }
            }
        }
        else if (pilihan == 3) {
            if (jumlahStaff == 0) cout << "Tidak ada staff.\n";
            else {
                for (int i = 0; i < jumlahStaff; i++) {
                    cout << i+1 << ". " << namaStaff[i]
                         << " - " << jabatan[i]
                         << " - Rp " << gaji[i] << endl;
                }
            }
        }
        else if(pilihan == 4){
				cout << "\nBerhasil kembali ke main menu\n";
				break;
			} else {
            cout << "\nInvalid input, hanya 1-3\n";
            continue;
        }
    } while (pilihan != 4);
}

void laporanManager() {
    cout << "\n=== LAPORAN RESTORAN ===\n";
    int terisi = 0, kosong = 0;

    for (int i = 0; i < MAX_MEJA; i++) {
        if (meja_status[i] == "Isi") terisi++;
        else kosong++;
    }

    cout << "Meja Terisi : " << terisi << endl;
    cout << "Meja Kosong : " << kosong << endl;

    cout << "\nDAFTAR PELANGGAN :\n";
    if (jumlahPelanggan == 0) cout << "Belum ada pelanggan.\n";
    else {
        for (int i = 0; i < jumlahPelanggan; i++) {
            cout << dataPelanggan[i].id << ". " << dataPelanggan[i].nama
                 << " - " << dataPelanggan[i].telepon 
                 << " | Bergabung : ";
            tampilkanTanggal(dataPelanggan[i].tanggal_daftar);
            cout << endl;
        }
    }

    cout << "\nDAFTAR PELANGGAN PER MEJA :\n";
    for (int i = 0; i < MAX_MEJA; i++) {
        cout << "Meja " << i+1 << " | " << meja_status[i] << " | ";
        if (meja_id_pelanggan[i] > 0) {
            int pid = meja_id_pelanggan[i] - 1;
            cout << dataPelanggan[pid].nama << " (" << dataPelanggan[pid].telepon << ")";
        } else {
            cout << "-";
        }
        cout << " | Item : " << jumlahPesananMeja[i] << " | Pendapatan : Rp " << totalPendapatanMeja[i] << "\n";
    }

    cout << "\nDAFTAR PESANAN :\n";
    if (jumlahPesanan == 0) cout << "Belum ada pesanan.\n";
    else {
        for (int i = 0; i < jumlahPesanan; i++) {
            cout << "Pesanan " << dataPesanan[i].id
                 << " | Meja " << dataPesanan[i].id_meja
                 << " | Pelanggan ID " << dataPesanan[i].id_pelanggan
                 << " | Total Rp " << dataPesanan[i].total_harga
                 << " | ";
            tampilkanTanggal(dataPesanan[i].tanggal_pesan);
            cout << " ";
            tampilkanWaktu(dataPesanan[i].waktu_pesan);
            cout << endl;
        }
    }

    cout << "\nDETAIL PESANAN :\n";
    if (jumlahDetail == 0) cout << "Tidak ada detail pesanan.\n";
    else {
        for (int i = 0; i < jumlahDetail; i++) {
            cout << "PesananID " << detailPesanan[i].id_pesanan
                 << " | MenuID " << detailPesanan[i].id_menu
                 << " | " << nama_menu[detailPesanan[i].id_menu - 1]
                 << " x" << detailPesanan[i].jumlah
                 << " = Rp " << detailPesanan[i].subtotal << endl;
        }
    }

    cout << "\nDAFTAR STAFF :\n";
    if (jumlahStaff == 0) cout << "Belum ada staff.\n";
    else {
        for (int i = 0; i < jumlahStaff; i++) {
            cout << i+1 << ". " << namaStaff[i]
                 << " - " << jabatan[i]
                 << " - Rp " << gaji[i] << endl;
        }
    }

    cout << "\nSTOK BAHAN BAKU :\n";
    for (int i = 0; i < jumlahBahanBaku; i++) {
        cout << dataBahanBaku[i].id << ". " << dataBahanBaku[i].nama
             << " | Stok: " << dataBahanBaku[i].stok << " " << dataBahanBaku[i].satuan
             << " | Terakhir dipesan: ";
        if (dataBahanBaku[i].tanggal_dipesan.hari == 0) {
            cout << "Belum pernah";
        } else {
            tampilkanTanggal(dataBahanBaku[i].tanggal_dipesan);
        }
        cout << endl;
    }

    cout << "\nRIWAYAT PESANAN BAHAN BAKU:\n";
    if (jumlahPesananBahan == 0) {
        cout << "Belum ada riwayat pesanan bahan baku.\n";
    } else {
        for (int i = 0; i < jumlahPesananBahan; i++) {
            cout << "Pesanan " << dataPesananBahan[i].id
                 << " | Pemasok: " << dataPesananBahan[i].id_pemasok
                 << " | Bahan: " << dataPesananBahan[i].id_bahan_baku
                 << " | Jumlah: " << dataPesananBahan[i].jumlah
                 << " | Tanggal: ";
            tampilkanTanggal(dataPesananBahan[i].tanggal_pesan);
            cout << " | Status: " << dataPesananBahan[i].status << endl;
        }
    }

    int totalPendapatan = 0;
    int totalItem = 0;
    for (int i = 0; i < MAX_MEJA; i++) {
        totalPendapatan += totalPendapatanMeja[i];
        totalItem += jumlahPesananMeja[i];
    }

    cout << "\nTOTAL PENDAPATAN RESTORAN : Rp " << totalPendapatan << endl;
    cout << "TOTAL JUMLAH PESANAN     : " << totalItem << " item" << endl;
}

void mainMenuManager() {
    int menu;
    do {
        cout << "\n=========== MENU MANAGER ==========\n";
        cout << "1. Pemesanan\n";
        cout << "2. Staff Management\n";
        cout << "3. Meja (Status & Kosongkan)\n";
        cout << "4. Laporan\n";
        cout << "5. Pemasok dan bahan baku\n";
        cout << "6. Logout\n";
        cout << "Masukkan Pilihan : ";
        cin >> menu;
        cin.ignore();
        if (menu == 1) pemesanan();
        else if (menu == 2) fungsiStaffJabatan();
        else if (menu == 3) menuMeja();
        else if (menu == 4) laporanManager();
        else if (menu == 5) menuPemasok();
        else if (menu == 6){
			cout << "\nLogout Berhasil";
			} else {
             cout << "\nInvalid input, hanya 1-6!\n"; 
             continue; }
    } while (menu != 6);
}

void mainMenuKasir() {
    int menu;
    do {
        cout << "\n=========== MENU KASIR ==========\n";
        cout << "1. Pemesanan\n";
        cout << "2. Meja\n";
        cout << "3. Logout\n";
        cout << "Masukkan Pilihan : ";
        cin >> menu;
        cin.ignore();
        if (menu == 1) pemesanan();
        else if (menu == 2) menuMeja();
        else if (menu == 3){
			cout << "\nLogout Berhasil";
			} else {
            cout << "\nInvalid input, hanya 1-3\n";
            continue;
        }
    } while (menu != 3);
}

void mainMenuPelayan() {
    int menu;
    do {
        cout << "\n=========== MENU PELAYAN ==========\n";
        cout << "1. Pemesanan\n";
        cout << "2. Logout\n";
        cout << "Masukkan Pilihan : ";
        cin >> menu;
        cin.ignore();
        if (menu == 1) pemesanan();
        else if (menu == 2){
			cout << "\nLogout Berhasil";
			} else{
            cout << "\nInvalid input, hanya 1-2\n";
            continue;
        }
    } while (menu != 2);
}

void fungsiLogin(bool &loginBerhasil, string &role) {
    const int jumlahUser = 3;
    string usernames[jumlahUser] = {"manager", "kasir", "pelayan"};
    string passwords[jumlahUser] = {"123", "123", "123"};
    string roles[jumlahUser] = {"Manager", "Kasir", "Pelayan"};
    string inputUser, inputPass;
    cout << "===== LOGIN =====\n";
    cout << "Masukkan username: ";
    cin >> inputUser;
    cout << "Masukkan password: ";
    cin >> inputPass;
    for (int i = 0; i < jumlahUser; i++) {
        if (inputUser == usernames[i] && inputPass == passwords[i]) {
            loginBerhasil = true;
            role = roles[i];
            cout << "\nLogin Berhasil!\n";
        }
    }
}

void fungsiDashboard(string role) {
    if (role == "Manager") mainMenuManager();
    else if (role == "Kasir") mainMenuKasir();
    else if (role == "Pelayan") mainMenuPelayan();
}

int main() {
    string role;
    bool loginBerhasil = false;
    fungsiLogin(loginBerhasil, role);
    if (loginBerhasil) fungsiDashboard(role);
    else cout << "Login gagal.\n";
    return 0;
}
