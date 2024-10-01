#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Perabotan {
    string nama;
    string harga;
    Perabotan* berikutnya;
};

vector<pair<string, string>> data_login = {{"Ocha","127"}, {"Lozy", "128"}, {"Zayn", "129"}};

bool login(int percobaan_login = 3) {
    if (percobaan_login == 0) {
        cout << "Anda telah melebihi batas percobaan login. Program berhenti." << endl;
        return false;
    }

    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    for (const auto& login : data_login) {
        if (login.first == username && login.second == password) {
            cout << "Login berhasil! Selamat datang, " << username << "!" << endl;
            return true;
        }
    }

    cout << "Login gagal. Silakan coba lagi." << endl;
    return login(percobaan_login - 1);
}


void tampilkanMenuUtama() {
    cout << "\n=== PROGRAM CRUD PERABOTAN RUMAH TANGGA ===" << endl;
    cout << "1. Tambah Perabotan" << endl;
    cout << "2. Tampilkan Daftar Perabotan" << endl;
    cout << "3. Ubah Perabotan" << endl;
    cout << "4. Hapus Perabotan" << endl;
    cout << "5. Keluar" << endl;
}


void tambahPerabotan(Perabotan*& kepala) {
    Perabotan* perabotan_baru = new Perabotan;
    cout << "Masukkan nama perabotan: ";
    cin >> perabotan_baru->nama;
    cout << "Masukkan harga perabotan: ";
    cin >> perabotan_baru->harga;
    perabotan_baru->berikutnya = nullptr;

    if (kepala == nullptr) {
        kepala = perabotan_baru;
    } else {
        Perabotan* temp = kepala;
        while (temp->berikutnya != nullptr) {
            temp = temp->berikutnya;
        }
        temp->berikutnya = perabotan_baru;
    }
    cout << "Perabotan berhasil ditambahkan." << endl;
}


void tampilkanPerabotan(Perabotan* kepala) {
    if (kepala == nullptr) {
        cout << "Belum ada perabotan yang ditambahkan." << endl;
        return;
    }

    cout << "\n=== DAFTAR PERABOTAN RUMAH TANGGA ===" << endl;
    int indeks = 1;
    Perabotan* temp = kepala;
    while (temp != nullptr) {
        cout << indeks << ". Nama: " << temp->nama << ", Harga: " << temp->harga << endl;
        temp = temp->berikutnya;
        indeks++;
    }
}

void ubahPerabotan(Perabotan* kepala) {
    if (kepala == nullptr) {
        cout << "Belum ada perabotan yang ditambahkan." << endl;
        return;
    }

    int indeks;
    cout << "Masukkan nomor perabotan yang akan diubah: ";
    cin >> indeks;

    Perabotan* temp = kepala;
    for (int i = 1; i < indeks && temp != nullptr; i++) {
        temp = temp->berikutnya;
    }

    if (temp != nullptr) {
        cout << "Masukkan nama perabotan baru: ";
        cin >> temp->nama;
        cout << "Masukkan harga perabotan baru: ";
        cin >> temp->harga;
        cout << "Perabotan berhasil diubah." << endl;
    } else {
        cout << "Nomor perabotan tidak valid." << endl;
    }
}


void hapusPerabotan(Perabotan*& kepala) {
    if (kepala == nullptr) {
        cout << "Belum ada perabotan yang ditambahkan." << endl;
        return;
    }

    int indeks;
    cout << "Masukkan nomor perabotan yang akan dihapus: ";
    cin >> indeks;

    if (indeks == 1) {
        Perabotan* temp = kepala;
        kepala = kepala->berikutnya;
        cout << temp->nama << " telah dihapus dari daftar." << endl;
        delete temp;
    } else {
        Perabotan* temp = kepala;
        Perabotan* sebelumnya = nullptr;
        for (int i = 1; i < indeks && temp != nullptr; i++) {
            sebelumnya = temp;
            temp = temp->berikutnya;
        }

        if (temp != nullptr) {
            sebelumnya->berikutnya = temp->berikutnya;
            cout << temp->nama << " telah dihapus dari daftar." << endl;
            delete temp;
        } else {
            cout << "Nomor perabotan tidak valid." << endl;
        }
    }
}

void bersihkanMemori(Perabotan* kepala) {
    while (kepala != nullptr) {
        Perabotan* temp = kepala;
        kepala = kepala->berikutnya;
        delete temp;
    }
}

int main() {
    cout << "SELAMAT DATANG" << endl;
    cout << "===================" << endl;

    bool berhasil_login = login();

    if (!berhasil_login) {
        return 0;
    }

    Perabotan* kepala = nullptr;

    while (true) {
        tampilkanMenuUtama();

        int pilihan;
        cout << "Masukkan pilihan (1/2/3/4/5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPerabotan(kepala);
                break;
            case 2:
                tampilkanPerabotan(kepala);
                break;
            case 3:
                ubahPerabotan(kepala);
                break;
            case 4:
                hapusPerabotan(kepala);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini." << endl;
                bersihkanMemori(kepala);
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan pilih kembali." << endl;
        }
    }

    return 0;
}