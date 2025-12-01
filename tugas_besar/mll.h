#ifndef MLL_H
#define MLL_H

#include <iostream>

// Definisikan tipe data untuk pointer
typedef struct NodeRelasi* address_relasi;
typedef struct NodeParent* address_parent;
typedef struct NodeChild* address_child;

// --- 1. STRUKTUR LIST PARENT (LOWONGAN) ---
struct InfoLowongan {
    int id_lowongan;
    char posisi[50];
    char nama_perusahaan[100];
    float kuota;
};

struct NodeParent {
    InfoLowongan info;
    address_parent next;
    address_relasi first_relasi;
};

struct ListParent {
    address_parent first;
};

// --- 2. STRUKTUR LIST CHILD (MAHASISWA) ---
struct InfoMahasiswa {
    char nim[10];
    char nama[100];
    int angkatan;
};

struct NodeChild {
    InfoMahasiswa info;
    address_child next;
};

struct ListChild {
    address_child first;
};

// --- 3. STRUKTUR LIST RELASI (LAMARAN) ---
struct InfoLamaran {
    int id_lamaran;
    int status_dosen; // 0=Menunggu, 1=Disetujui, 2=Ditolak
    int status_perusahaan; // 0=Menunggu, 1=Diterima, 2=Ditolak
};

struct NodeRelasi {
    InfoLamaran info;
    address_relasi next;
    address_parent ptr_parent;
    address_child ptr_child;
};

// --- DEKLARASI FUNGSI ---
void createListParent(ListParent &L);
void createListChild(ListChild &L);
address_parent alokasiParent(int ID, const char* Posisi, const char* Perusahaan, float Kuota);
address_child alokasiChild(const char* NIM, const char* Nama, int Angkatan);

void insertParent(ListParent &L, address_parent P_Baru);
void insertChild(ListChild &L, address_child C_Baru);

address_parent findParent(ListParent L, int ID_Target);
address_child findChildByNIM(ListChild L, const char* NIM_Target);

void handleInputMahasiswa(ListChild &L_Child, const char* NIM, const char* Nama);
void insertRelasi(ListParent &L_Parent, ListChild &L_Child, int ID_Lowongan, const char* NIM_Mhs, const char* Nama_Mhs, int ID_Lamaran_Baru);
void editStatusDosen(ListParent &L_Parent, int ID_Lamaran_Target, int Status_Baru);
void editStatusPerusahaan(ListParent &L_Parent, int ID_Lamaran_Target, int Status_Baru);
void showLowonganDanPelamar(ListParent L_Parent);

#endif // MLL_H
