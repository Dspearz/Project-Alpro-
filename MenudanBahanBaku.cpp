#include <iostream>
using namespace std;

int main() {
    int pilihan
    char menu[50]
    char bahan[50]
    char data[50]

    do {
cout << "====MENU & BAHAN BAKU====" << endl;
cout << "1. Tambah Menu" << endl;
cout << "2. Ubah Menu" << endl;
cout << "3. Hapus Menu" << endl;
cout << "4. Kembali" << endl;
cin >> pilihan

switch(pilihan){
case 1:
cout << "Masukkan nama menu baru:";
cin >> menu;
cout << "Masukkan bahan baku utama:";
cin >> bahan;
cout << "Menu baru :" << menu;
cout << "Bahan Baku:" << bahan;
cout << "Berhasil Ditambahkan." << endl;
break;

case 2:
cout << "Masukkan nama menu yang ingin diubah:";
cin >> menu;
cout << "Masukkan nama baru:";
cin >> data;
cout << "Menu telah diperbarui";
break;

case 3:
cout << "Masukkan nama menu yang ingin dihapus:";
cin >> menu;
cout << "Menu dihapus.";
break;

case 4:
cout <<"Keluar dari program."

default:
cout << "pilihan tidak valid."
}
    }
    while (pilihan != 4)
    return 0;
    }

