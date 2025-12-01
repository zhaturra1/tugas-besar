#include "mahasiswa.h"
#include <cstring>

using namespace std;

// Implementasi fungsi dasar List Child (Mahasiswa)

void createListChild(ListChild &L) {
    L.first = nullptr;
}

address_child alokasiChild(const char* NIM, const char* Nama, int Angkatan) {
    address_child C = new NodeChild;
    if (C != nullptr) {
        strcpy(C->info.nim, NIM);
        strcpy(C->info.nama, Nama);
        C->info.angkatan = Angkatan;
        C->next = nullptr;
    }
    return C;
}

// Fungsi (b) Insert element child
void insertChild(ListChild &L, address_child C_Baru) {
    if (L.first == nullptr) L.first = C_Baru;
    else {
        address_child Last = L.first;
        while (Last->next != nullptr) Last = Last->next;
        Last->next = C_Baru;
    }
}

address_child findChildByNIM(ListChild L, const char* NIM_Target) {
    address_child P = L.first;
    while (P != nullptr) {
        if (strcmp(P->info.nim, NIM_Target) == 0) return P;
        P = P->next;
    }
    return nullptr;
}

// Tambahkan di mahasiswa.cpp, di bawah handleInputMahasiswa:

void showMahasiswa(ListChild L_Child) {
    address_child C = L_Child.first;
    cout << "\n--- DAFTAR MAHASISWA (CHILD LIST) ---" << endl;
    if (C == nullptr) { cout << "List Mahasiswa kosong." << endl; return; }
    while (C != nullptr) {
        cout << " - NIM: " << C->info.nim << " | Nama: " << C->info.nama << " | Angkatan: " << C->info.angkatan << endl;
        C = C->next;
    }
}

// Fungsi utama untuk input dinamis
void handleInputMahasiswa(ListChild &L_Child, const char* NIM, const char* Nama) {
    address_child C_Target = findChildByNIM(L_Child, NIM);

    if (C_Target == nullptr) {
        // Angkatan diset 0 (default)
        address_child C_Baru = alokasiChild(NIM, Nama, 0);
        insertChild(L_Child, C_Baru);
        cout << "   [INFO] Data Mahasiswa '" << Nama << "' ditambahkan ke List Child." << endl;
    }
}
