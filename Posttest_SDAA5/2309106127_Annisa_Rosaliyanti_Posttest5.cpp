#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Perabotan {
    string nama;
    string harga;
    Perabotan* berikutnya;
};

vector<pair<string, string>> data_login = {{"Ocha", "127"}, {"Lozy", "128"}, {"Zayn", "129"}};

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
    cout << "1. Tambah Perabotan (Linked List)" << endl;
    cout << "2. Tampilkan Daftar Perabotan" << endl;
    cout << "3. Ubah Perabotan" << endl;
    cout << "4. Hapus Perabotan" << endl;
    cout << "5. Tambah Perabotan ke Stack" << endl;
    cout << "6. Keluarkan Perabotan dari Stack" << endl;
    cout << "7. Tambah Perabotan ke Queue" << endl;
    cout << "8. Keluarkan Perabotan dari Queue" << endl;
    cout << "9. Urutkan Perabotan (Merge Sort - Ascending)" << endl;
    cout << "10. Urutkan Perabotan (Quick Sort - Descending)" << endl;
    cout << "11. Keluar" << endl;
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

Perabotan* sortedMerge(Perabotan* a, Perabotan* b) {
    if (!a) return b;
    if (!b) return a;

    Perabotan* result = nullptr;

    if (a->harga <= b->harga) {
        result = a;
        result->berikutnya = sortedMerge(a->berikutnya, b);
    } else {
        result = b;
        result->berikutnya = sortedMerge(a, b->berikutnya);
    }

    return result;
}

void split(Perabotan* source, Perabotan** frontRef, Perabotan** backRef) {
    Perabotan* fast;
    Perabotan* slow;
    slow = source;
    fast = source->berikutnya;

    while (fast != nullptr) {
        fast = fast->berikutnya;
        if (fast != nullptr) {
            slow = slow->berikutnya;
            fast = fast->berikutnya;
        }
    }

    *frontRef = source;
    *backRef = slow->berikutnya;
    slow->berikutnya = nullptr;
}

void mergeSort(Perabotan** kepala) {
    if (*kepala == nullptr || (*kepala)->berikutnya == nullptr) {
        return;
    }

    Perabotan* a;
    Perabotan* b;

    split(*kepala, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *kepala = sortedMerge(a, b);
}

Perabotan* partition(Perabotan* low, Perabotan* high, Perabotan** newHead, Perabotan** newEnd) {
    Perabotan* pivot = high;
    Perabotan* prev = nullptr, *cur = low, *tail = pivot;

    while (cur != pivot) {
        if (cur->harga > pivot->harga) {
            if (*newHead == nullptr) *newHead = cur;
            prev = cur;
            cur = cur->berikutnya;
        } else {
            if (prev) prev->berikutnya = cur->berikutnya;
            Perabotan* temp = cur->berikutnya;
            cur->berikutnya = nullptr;
            tail->berikutnya = cur;
            tail = cur;
            cur = temp;
        }
    }

    if (*newHead == nullptr) *newHead = pivot;

    *newEnd = tail;

    return pivot;
}

Perabotan* quickSortRec(Perabotan* kepala, Perabotan* end) {
    if (!kepala || kepala == end) return kepala;

    Perabotan* newHead = nullptr, *newEnd = nullptr;

    Perabotan* pivot = partition(kepala, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Perabotan* temp = newHead;
        while (temp->berikutnya != pivot) temp = temp->berikutnya;
        temp->berikutnya = nullptr;

        newHead = quickSortRec(newHead, temp);

        temp = newHead;
        while (temp->berikutnya != nullptr) temp = temp->berikutnya;
        temp->berikutnya = pivot;
    }

    pivot->berikutnya = quickSortRec(pivot->berikutnya, newEnd);

    return newHead;
}

void quickSort(Perabotan** kepala) {
    *kepala = quickSortRec(*kepala, nullptr);
    return;
}

void bersihkanMemori(Perabotan* kepala) {
    while (kepala != nullptr) {
        Perabotan* temp = kepala;
        kepala = kepala->berikutnya;
        delete temp;
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

void push(Perabotan*& stack, const string& nama, const string& harga) {
    Perabotan* perabotan_baru = new Perabotan{nama, harga, stack};
    stack = perabotan_baru;
    cout << "Perabotan " << nama << " berhasil ditambahkan ke stack." << endl;
}

void pop(Perabotan*& stack) {
    if (stack == nullptr) {
        cout << "Stack kosong." << endl;
    } else {
        Perabotan* temp = stack;
        stack = stack->berikutnya;
        cout << temp->nama << " telah dikeluarkan dari stack." << endl;
        delete temp;
    }
}

void enqueue(Perabotan*& queue, const string& nama, const string& harga) {
    Perabotan* perabotan_baru = new Perabotan{nama, harga, nullptr};
    if (queue == nullptr) {
        queue = perabotan_baru;
    } else {
        Perabotan* temp = queue;
        while (temp->berikutnya != nullptr) {
            temp = temp->berikutnya;
        }
        temp->berikutnya = perabotan_baru;
    }
    cout << "Perabotan " << nama << " berhasil ditambahkan ke queue." << endl;
}

void dequeue(Perabotan*& queue) {
    if (queue == nullptr) {
        cout << "Queue kosong." << endl;
    } else {
        Perabotan* temp = queue;
        queue = queue->berikutnya;
        cout << temp->nama << " telah dikeluarkan dari queue." << endl;
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
    Perabotan* stack = nullptr;
    Perabotan* queue = nullptr;

    while (true) {
        tampilkanMenuUtama();

        int pilihan;
        cout << "Masukkan pilihan (1-11): ";
        cin >> pilihan;

        string nama, harga;

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
                cout << "Masukkan nama perabotan untuk stack: ";
                cin >> nama;
                cout << "Masukkan harga perabotan untuk stack: ";
                cin >> harga;
                push(stack, nama, harga);
                break;
            case 6:
                pop(stack);
                break;
            case 7:
                cout << "Masukkan nama perabotan untuk queue: ";
                cin >> nama;
                cout << "Masukkan harga perabotan untuk queue: ";
                cin >> harga;
                enqueue(queue, nama, harga);
                break;
            case 8:
                dequeue(queue);
                break;
            case 9:
                mergeSort(&kepala);
                cout << "Daftar perabotan telah diurutkan secara ascending menggunakan Merge Sort." << endl;
                break;
            case 10:
                quickSort(&kepala);
                cout << "Daftar perabotan telah diurutkan secara descending menggunakan Quick Sort." << endl;
                break;
            case 11:
                cout << "Terima kasih telah menggunakan program ini." << endl;
                bersihkanMemori(kepala);
                bersihkanMemori(stack);
                bersihkanMemori(queue);
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan pilih kembali." << endl;
        }
    }

    return 0;
}

