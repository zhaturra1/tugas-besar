#ifndef LAMARAN_H
#define LAMARAN_H

#include "MLL_STRUCTS.h"

// DEKLARASI FUNGSI LAMARAN (RELASI)
// --- FUNGSI TAMPILAN SPESIFIK BARU ---
void showStatusLamaranMahasiswa(ListParent L_Parent, const char* NIM_Target);
void showRekapLamaranPerusahaan(ListParent L_Parent);
void insertRelasi(ListParent &L_Parent, ListChild &L_Child, int ID_Lowongan, const char* NIM_Mhs, const char* Nama_Mhs, int ID_Lamaran_Baru);
void editStatusDosen(ListParent &L_Parent, int ID_Lamaran_Target, int Status_Baru);
void editStatusPerusahaan(ListParent &L_Parent, int ID_Lamaran_Target, int Status_Baru);
void showLowonganDanPelamar(ListParent L_Parent);

#endif // LAMARAN_H
