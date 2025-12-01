#include "mll.h"
#include <cstring>
#include <iomanip>
#include <limits>

using namespace std;

// --- FUNGSI DASAR & ALOKASI ---
void createListParent(ListParent &L) { L.first = nullptr; }
void createListChild(ListChild &L) { L.first = nullptr; }

address_parent alokasiParent(int ID, const char* Posisi, const char* Perusahaan, float Kuota) {
    address_parent P = new NodeParent;
    if (P != nullptr) {
        P->info.id_lowongan = ID;
        strcpy(P->info.posisi, Posisi);
        strcpy(P->info.nama_perusahaan, Perusahaan);
        P->info.kuota = Kuota;
        P->next = nullptr;
        P->first_relasi = nullptr;
    }
    return P;
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

// --- INSERT DASAR & FIND ---
void insertParent(ListParent &L, address_parent P_Baru) {
    if (L.first == nullptr) L.first = P_Baru;
    else { address_parent Last = L.first; while (Last->next != nullptr) Last = Last->next; Last->next = P_Baru; }
}
void insertChild(ListChild &L, address_child C_Baru) {
    if (L.first == nullptr) L.first = C_Baru;
    else { address_child Last = L.first; while (Last->next != nullptr) Last = Last->next; Last->next = C_Baru; }
}

address_parent findParent(ListParent L, int ID_Target) {
    address_parent P = L.first;
    while (P != nullptr) {
        if (P->info.id_lowongan == ID_Target) return P;
        P = P->next;
    }
    return nullptr;
}
address_child findChildByNIM(ListChild L, const char* NIM_Target) {
    address_child P = L.first;
    while (P != nullptr) {
        if (strcmp(P->info.nim, NIM_Target) == 0) return P;
        P = P->next;
    }
    return nullptr;
}

// --- FUNGSI KHUSUS INPUT CHILD DINAMIS ---
void handleInputMahasiswa(ListChild &L_Child, const char* NIM, const char* Nama) {
    address_child C_Target = findChildByNIM(L_Child, NIM);

    if (C_Target == nullptr) {
        // Angkatan diset 0 (default) karena tidak diinput oleh user
        address_child C_Baru = alokasiChild(NIM, Nama, 0);
        insertChild(L_Child, C_Baru);
        cout << "   [INFO] Data Mahasiswa '" << Nama << "' ditambahkan ke List Child." << endl;
    }
}


// --- FUNGSI UTAMA MLL (RELASI) ---

// 1. Insert element relation (Mahasiswa Ajukan Lamaran)
void insertRelasi(ListParent &L_Parent, ListChild &L_Child, int ID_Lowongan, const char* NIM_Mhs, const char* Nama_Mhs, int ID_Lamaran_Baru) {
    address_parent P_Parent = findParent(L_Parent, ID_Lowongan);

    // Pastikan data Mahasiswa ada/dibuat di List Child
    handleInputMahasiswa(L_Child, NIM_Mhs, Nama_Mhs);

    address_child P_Child = findChildByNIM(L_Child, NIM_Mhs);

    if (P_Parent != nullptr && P_Child != nullptr) {
        address_relasi R_Baru = new NodeRelasi;
        R_Baru->info.id_lamaran = ID_Lamaran_Baru;
        R_Baru->info.status_dosen = 0;
        R_Baru->info.status_perusahaan = 0;

        R_Baru->ptr_parent = P_Parent;
        R_Baru->ptr_child = P_Child;
        R_Baru->next = nullptr;

        // Insert Last Relasi ke Sub-List Lowongan
        if (P_Parent->first_relasi == nullptr) {
            P_Parent->first_relasi = R_Baru;
        } else {
            address_relasi R_Last = P_Parent->first_relasi;
            while (R_Last->next != nullptr) R_Last = R_Last->next;
            R_Last->next = R_Baru;
        }
        cout << "✅ Lamaran ID " << ID_Lamaran_Baru << " diajukan ke Lowongan " << ID_Lowongan << "." << endl;
    } else {
        cout << "❌ Error: Lowongan tidak ditemukan. Lamaran dibatalkan." << endl;
    }
}

// 2. Edit relasi (Aksi Dosen)
void editStatusDosen(ListParent &L_Parent, int ID_Lamaran_Target, int Status_Baru) {
    address_parent P_Parent = L_Parent.first;
    address_relasi R_Target = nullptr;

    while (P_Parent != nullptr && R_Target == nullptr) {
        address_relasi R = P_Parent->first_relasi;
        while (R != nullptr) {
            if (R->info.id_lamaran == ID_Lamaran_Target) {
                R_Target = R;
                break;
            }
            R = R->next;
        }
        if (R_Target != nullptr) break;
        P_Parent = P_Parent->next;
    }

    if (R_Target != nullptr) {
        if (Status_Baru == 1 || Status_Baru == 2) {
            R_Target->info.status_dosen = Status_Baru;
            cout << "✅ Status Verifikasi Dosen untuk Lamaran ID " << ID_Lamaran_Target << " diperbarui menjadi: **" << (Status_Baru == 1 ? "DISETUJUI" : "DITOLAK") << "**" << endl;
        } else {
            cout << "Input status verifikasi tidak valid (1=Setuju, 2=Tolak)." << endl;
        }
    } else {
        cout << "❌ Lamaran dengan ID " << ID_Lamaran_Target << " tidak ditemukan." << endl;
    }
}

// 3. Edit relasi (Aksi Perusahaan)
void editStatusPerusahaan(ListParent &L_Parent, int ID_Lamaran_Target, int Status_Baru) {
    address_parent P_Parent = L_Parent.first;
    address_relasi R_Target = nullptr;

    while (P_Parent != nullptr && R_Target == nullptr) {
        address_relasi R = P_Parent->first_relasi;
        while (R != nullptr) {
            if (R->info.id_lamaran == ID_Lamaran_Target) {
                R_Target = R;
                break;
            }
            R = R->next;
        }
        if (R_Target != nullptr) break;
        P_Parent = P_Parent->next;
    }

    if (R_Target != nullptr) {
        if (R_Target->info.status_dosen != 1) {
            cout << "❌ GAGAL. Lamaran ID " << ID_Lamaran_Target << " belum diverifikasi/ditolak Dosen (Status harus DISETUJUI)." << endl;
            return;
        }

        if (Status_Baru == 1 || Status_Baru == 2) {
            R_Target->info.status_perusahaan = Status_Baru;
            cout << "✅ Keputusan Perusahaan untuk Lamaran ID " << ID_Lamaran_Target << " diperbarui menjadi: **" << (Status_Baru == 1 ? "DITERIMA" : "DITOLAK") << "**" << endl;
        } else {
            cout << "⚠️ Status input tidak valid." << endl;
        }
    } else {
        cout << "❌ Lamaran dengan ID " << ID_Lamaran_Target << " tidak ditemukan." << endl;
    }
}

// 4. Show setiap data parent beserta data child yang berelasi dengannya (Show M:N)
void showLowonganDanPelamar(ListParent L_Parent) {
    address_parent P = L_Parent.first;

    std::cout << "\n========================================================" << endl;
    std::cout << "LAPORAN REKAP LAMARAN PER LOWONGAN (SHOW M:N)" << endl;
    std::cout << "========================================================" << endl;

    while (P != nullptr) {
        std::cout << "\n[LOWONGAN ID " << P->info.id_lowongan << "]: " << P->info.posisi
                  << " (Perusahaan: " << P->info.nama_perusahaan << ", Kuota: " << fixed << setprecision(0) << P->info.kuota << ")" << endl;

        address_relasi R = P->first_relasi;
        if (R == nullptr) {
            std::cout << "   - Belum ada pelamar." << endl;
        } else {
            std::cout << "   --- DAFTAR PELAMAR (RELASI) ---" << endl;
            while (R != nullptr) {
                address_child C = R->ptr_child;

                std::cout << "   [Lamaran ID: " << R->info.id_lamaran << "] - "
                          << C->info.nama << " (NIM: " << C->info.nim << ")" << endl;
                std::cout << "     Status Dosen: " << (R->info.status_dosen == 1 ? "Disetujui" : (R->info.status_dosen == 2 ? "Ditolak" : "Menunggu")) << endl;
                std::cout << "     Status Perusahaan: " << (R->info.status_perusahaan == 1 ? "DITERIMA" : (R->info.status_perusahaan == 2 ? "DITOLAK" : "Menunggu")) << endl;

                R = R->next;
            }
        }
        P = P->next;
    }
}
