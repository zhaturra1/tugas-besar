#ifndef MAHASISWA_H
#define MAHASISWA_H

#include "mll_structs.h"

// DEKLARASI FUNGSI MAHASISWA (CHILD)
void createListChild(ListChild &L);
address_child alokasiChild(const char* NIM, const char* Nama, int Angkatan);
void insertChild(ListChild &L, address_child C_Baru);
address_child findChildByNIM(ListChild L, const char* NIM_Target);
void handleInputMahasiswa(ListChild &L_Child, const char* NIM, const char* Nama); // Untuk input dinamis

#endif // MAHASISWA_H
