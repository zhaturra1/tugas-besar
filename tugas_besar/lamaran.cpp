#include "lamaran.h"
#include "lowongan.h"   // Diperlukan untuk mengakses fungsi findParent
#include "mahasiswa.h"  // Diperlukan untuk mengakses fungsi handleInputMahasiswa dan findChildByNIM
#include <iomanip>
#include <cstring>

using namespace std;

// Catatan: Fungsi yang dipanggil di sini harus sudah diimplementasikan
// di file lowongan.cpp dan mahasiswa.cpp masing-masing.

// 1. Insert element relation (Mahasiswa Ajukan Lamaran)
void insertRelasi(ListParent &L_Parent, ListChild &L_Child, int ID_Lowongan, const char* NIM_Mhs, const char* Nama_Mhs, int ID_Lamaran_Baru) {
    // 1. Pastikan data Mahasiswa ada/dibuat di List Child
    handleInputMahasiswa(L_Child, NIM_Mhs, Nama_Mhs);

    // 2. Cari Node Parent dan Child
    address_parent P_Parent = findParent(L_Parent, ID_Lowongan);
    address_child P_Child = findChildByNIM(L_Child, NIM_Mhs);

    if (P_Parent != nullptr && P_Child != nullptr) {
        address_relasi R_Baru = new NodeRelasi;
        R_Baru->info.id_lamaran = ID_Lamaran_Baru;
        R_Baru->info.status_dosen = 0; // Menunggu
        R_Baru->info.status_perusahaan = 0; // Menunggu

        // 3. Hubungkan Pointer Kunci MLL
        R_Baru->ptr_parent = P_Parent;
        R_Baru->ptr_child = P_Child;
        R_Baru->next = nullptr;

        // 4. Insert Last Relasi ke Sub-List Lowongan
        if (P_Parent->first_relasi == nullptr) {
            P_Parent->first_relasi = R_Baru;
        } else {
            address_relasi R_Last = P_Parent->first_relasi;
            while (R_Last->next != nullptr) R_Last = R_Last->next;
            R_Last->next = R_Baru;
        }
        cout << "Lamaran ID " << ID_Lamaran_Baru << " diajukan ke Lowongan " << ID_Lowongan << "." << endl;
    } else {
        cout << "Error: Lowongan ID " << ID_Lowongan << " tidak ditemukan. Lamaran dibatalkan." << endl;
    }
}

// Tambahkan di lamaran.cpp

// Catatan: Asumsikan Anda dapat mengakses ListChild L_Child jika diperlukan
// Namun, karena Node Relasi (R) sudah menyimpan ptr_child, kita bisa traversing Parent saja.

void showStatusLamaranMahasiswa(ListParent L_Parent, const char* NIM_Target) {
    address_parent P = L_Parent.first;
    bool found_lamaran = false;

    cout << "\n========================================================" << endl;
    cout << "STATUS LAMARAN ANDA (NIM: " << NIM_Target << ")" << endl;
    cout << "========================================================" << endl;

    while (P != nullptr) {
        address_relasi R = P->first_relasi;
        while (R != nullptr) {
            // Cek apakah NIM pada ptr_child Node Relasi cocok dengan NIM_Target
            if (strcmp(R->ptr_child->info.nim, NIM_Target) == 0) {
                found_lamaran = true;

                cout << "  [Lowongan ID " << P->info.id_lowongan << "]: " << P->info.posisi
                     << " (" << P->info.nama_perusahaan << ")" << endl;
                cout << "    Status Dosen: " << (R->info.status_dosen == 1 ? "Disetujui" : (R->info.status_dosen == 2 ? "Ditolak" : "Menunggu")) << endl;
                cout << "    Status Perusahaan: " << (R->info.status_perusahaan == 1 ? "**DITERIMA**" : (R->info.status_perusahaan == 2 ? "DITOLAK" : "Menunggu")) << endl;
                cout << "---------------------------------------" << endl;
            }
            R = R->next;
        }
        P = P->next;
    }

    if (!found_lamaran) {
        cout << "Tidak ada lamaran ditemukan untuk NIM " << NIM_Target << "." << endl;
    }
}
// Tambahkan atau pastikan implementasi ini ada di lamaran.cpp

void showRekapLamaranPerusahaan(ListParent L_Parent) {
    address_parent P = L_Parent.first;

    cout << "\n========================================================" << endl;
    cout << "REKAP DETAIL LAMARAN (Untuk Admin/Perusahaan)" << endl;
    cout << "========================================================" << endl;

    while (P != nullptr) {
        int count_pelamar = 0;
        int count_diterima = 0;

        cout << "\n[LOWONGAN ID " << P->info.id_lowongan << "]: " << P->info.posisi
             << " (Perusahaan: " << P->info.nama_perusahaan << ")" << endl;

        address_relasi R = P->first_relasi;

        if (R == nullptr) {
            cout << "   > Total Pelamar: 0" << endl;
        } else {
            cout << "   DETAIL PELAMAR:" << endl;
            while (R != nullptr) {
                count_pelamar++;
                if (R->info.status_perusahaan == 1) {
                    count_diterima++;
                }

                address_child C = R->ptr_child;
                cout << "   - NIM: " << C->info.nim << " | Nama: " << C->info.nama
                     << " | Status Akhir: " << (R->info.status_perusahaan == 1 ? "DITERIMA" : "DITOLAK/MENUNGGU") << endl;

                R = R->next;
            }
            cout << "   ---------------------------------------" << endl;
            cout << "   > Total Pelamar: " << count_pelamar << endl;
            cout << "   > Total Diterima: " << count_diterima << endl;
        }
        P = P->next;
    }
}

// Catatan: Pastikan juga Anda menghapus atau mengganti semua stubs (placeholder)
// yang tersisa di lamaran.cpp dengan implementasi aslinya.


// Stubs (placeholder) untuk fungsi edit dan show lainnya
void editStatusDosen(ListParent &L_Parent, int ID_Lamaran_Target, int Status_Baru) { cout << "Fungsi Edit Dosen belum diimplementasikan." << endl; }
void editStatusPerusahaan(ListParent &L_Parent, int ID_Lamaran_Target, int Status_Baru) { cout << "Fungsi Edit Perusahaan belum diimplementasikan." << endl; }
void showLowonganDanPelamar(ListParent L_Parent) { cout << "Fungsi Show M:N belum diimplementasikan." << endl; }
