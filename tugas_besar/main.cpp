#include "lowongan.h"
#include "mahasiswa.h"
#include "lamaran.h"
#include <limits>
#include <iomanip>

using namespace std;



// Deklarasi fungsi Show (yang implementasinya ada di lowongan.cpp dan mahasiswa.cpp)
// --- FUNGSI UTAMA ---
int main() {
    ListParent L_Parent;
    ListChild L_Child;
    createListParent(L_Parent);
    createListChild(L_Child);

    int counter_lowongan = 103;
    int counter_lamaran = 1;
    int pilihan_menu_utama;

    cout << "========================================" << endl;
    cout << " SISTEM LAYANAN MAGANG (MLL TIPE B) " << endl;
    cout << "========================================" << endl;

    // Tambahkan beberapa data awal Lowongan (Parent) untuk pengujian Relasi
    insertParent(L_Parent, alokasiParent(101, "Data Scientist", "TechCorp", 5.0));
    insertParent(L_Parent, alokasiParent(102, "Mobile Developer", "GameDev", 3.0));


    do {
        cout << "\n\n--- MENU UTAMA ---" << endl;
        cout << "1. Input Lowongan Baru (Parent)" << endl;
        cout << "2. Input Data Mahasiswa Baru (Child)" << endl;
        cout << "3. Ajukan Lamaran (Insert Relasi)" << endl;
        cout << "4. Verifikasi Dosen (Edit Relasi)" << endl;
        cout << "5. Keputusan Perusahaan (Edit Relasi)" << endl;
       cout << "6. Tampilkan Semua Lowongan & Pelamar (Show All M:N)" << endl;
        cout << "7. Tampilkan Data Lowongan (Parent & Child)" << endl;
         cout << "8. Tampilkan Data Pelamar (Parent & Child)" << endl;
        cout << "9. **STATUS LAMARAN (MAHASISWA)**" << endl; // <-- OPSI BARU (Mahasiswa)
        cout << "10. **REKAP LAMARAN (ADMIN/PERUSAHAAN)**" << endl; // <-- OPSI BARU (Perusahaan/Admin)
        cout << "11. Keluar" << endl; // Exit option adjusted
        cout << "Pilihan Anda: ";


        if (!(cin >> pilihan_menu_utama)) {
            cout << "Input tidak valid. Silakan masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (pilihan_menu_utama) {
            case 1: { // Input Lowongan Baru (Parent)
                int pilihan_sub;
                do {
                    menuInsertParent(L_Parent, counter_lowongan);
                    cout << "\n--- SUB-MENU ---" << endl;
                    cout << "1. Input Lowongan Lagi" << endl;
                    cout << "2. Kembali ke Menu Utama" << endl;
                    cout << "Pilihan: ";
                    if (!(cin >> pilihan_sub)) {
                        cout << "Input tidak valid." << endl;
                        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        pilihan_sub = 0;
                    } else if (pilihan_sub == 2) {
                        // FIX LOOPING: Bersihkan buffer setelah membaca angka sub-menu
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (pilihan_sub == 1);
                break;
            }
            case 2: { // Input Data Mahasiswa Baru (Child)
                int pilihan_sub;
                do {
                    char nim_input[10];
                    char nama_input[100];
                    int angkatan_input;

                    cout << "\n--- INPUT MAHASISWA BARU ---" << endl;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Masukkan NIM: "; cin.getline(nim_input, 10);
                    cout << "Masukkan Nama Lengkap: "; cin.getline(nama_input, 100);

                    cout << "Masukkan Angkatan (Tahun): ";
                    if (!(cin >> angkatan_input)) {
                        cout << "Input Angkatan tidak valid. Mahasiswa dibatalkan." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        pilihan_sub = 1;
                        continue;
                    }

                    if (findChildByNIM(L_Child, nim_input) != nullptr) {
                        cout << "Gagal. Mahasiswa dengan NIM " << nim_input << " sudah ada." << endl;
                    } else {
                        address_child C_Baru = alokasiChild(nim_input, nama_input, angkatan_input);
                        insertChild(L_Child, C_Baru);
                        cout << "Mahasiswa " << nama_input << " berhasil ditambahkan." << endl;
                    }

                    cout << "\n--- SUB-MENU ---" << endl;
                    cout << "1. Input Mahasiswa Lagi" << endl;
                    cout << "2. Kembali ke Menu Utama" << endl;
                    cout << "Pilihan: ";
                    if (!(cin >> pilihan_sub)) {
                        cout << "Input tidak valid." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        pilihan_sub = 0;
                    } else if (pilihan_sub == 2) {
                        // FIX LOOPING: Bersihkan buffer setelah membaca angka sub-menu
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (pilihan_sub == 1);
                break;
            }
            case 3: { // Ajukan Lamaran (INSERT ELEMENT RELATION)
                int id_lowongan_input;
                char nim_input[10];
                char nama_input[100];

                cout << "--- PENGINPUTAN DATA PELAMAR ---" << endl;
                cout << "Masukkan ID Lowongan yang dilamar: ";
                if (!(cin >> id_lowongan_input)) {
                    cout << "Input ID Lowongan tidak valid. Lamaran dibatalkan." << endl;
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Masukkan NIM Anda: "; cin.getline(nim_input, 10);
                cout << "Masukkan Nama Lengkap Anda: "; cin.getline(nama_input, 100);

                insertRelasi(L_Parent, L_Child, id_lowongan_input, nim_input, nama_input, counter_lamaran++);
                break;
            }
            case 4: { // Verifikasi Dosen (EDIT RELASI)
                int id_lamaran_target, status_baru;
                cout << "Masukkan ID Lamaran untuk diverifikasi: "; cin >> id_lamaran_target;
                cout << "Status Verifikasi (1=DISETUJUI, 2=DITOLAK): "; cin >> status_baru;
                editStatusDosen(L_Parent, id_lamaran_target, status_baru);
                break;
            }
            case 5: { // Keputusan Perusahaan (EDIT RELASI)
                int id_lamaran_target, status_baru;
                cout << "Masukkan ID Lamaran untuk keputusan Perusahaan: "; cin >> id_lamaran_target;
                cout << "Status Keputusan (1=DITERIMA, 2=DITOLAK): "; cin >> status_baru;
                editStatusPerusahaan(L_Parent, id_lamaran_target, status_baru);
                break;
            }
            case 6: { // Tampilkan Semua Data (SHOW ALL M:N)
                showLowonganDanPelamar(L_Parent);
                break;
            }
            case 7: { // Tampilkan Data Dasar
                showLowongan(L_Parent);
                break;
            }
            case 8: { // Tampilkan Data Dasar
                showMahasiswa(L_Child);
                break;
            }
           case 9: { // STATUS LAMARAN (MAHASISWA)
                char nim_input[10];
                cout << "\n--- STATUS LAMARAN ---" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan NIM Anda: ";
                cin.getline(nim_input, 10);
                showStatusLamaranMahasiswa(L_Parent, nim_input);
                break;
            }
            case 10: { // REKAP LAMARAN (ADMIN/PERUSAHAAN)
                showRekapLamaranPerusahaan(L_Parent);
                break;
            }
            case 11:
                cout << "Program selesai. Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak ditemukan." << endl;
        }

    } while (pilihan_menu_utama != 10); // Kondisi keluar disesuaikan

    return 0;
}
