#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

struct Petugas {
    string nama;
    string id;
};

struct Kendaraan {
    string platNomor;
    string jenis;
    string warna;
    time_t waktuMasuk;
};

class Parkiran {
private:
    Kendaraan* daftarParkir[20];
    int jumlahParkir;

    bool platSudahAda(const string& plat) {
        for (int i = 0; i < jumlahParkir; i++) {
            if (daftarParkir[i] && daftarParkir[i]->platNomor == plat) {
                return true;
            }
        }
        return false;
    }

public:
    Parkiran() {
        jumlahParkir = 0;
        for (int i = 0; i < 20; i++)
            daftarParkir[i] = nullptr;
    }

    void kendaraanMasuk() {
        int jumlah;
        cout << "\nMasukkan jumlah mobil yang akan diparkirkan: ";
        cin >> jumlah;
        cin.ignore();

        if (jumlah > 20 || jumlahParkir + jumlah > 20) {
            cout << "\nMaaf, parkiran hanya dapat memuat 20 mobil!\n";
            return;
        }

        // Input data kendaraan (plat, merk, warna)
        for (int i = 0; i < jumlah; i++) {
            cout << "\nMobil ke-" << i + 1 << ":\n";
            Kendaraan* k = new Kendaraan();

            bool duplikat;
            do {
                cout << "Masukkan plat mobil  : ";
                getline(cin, k->platNomor);
                duplikat = platSudahAda(k->platNomor);
                if (duplikat) {
                    cout << "Plat nomor sudah terdaftar! Masukkan plat yang berbeda.\n";
                }
            } while (duplikat);

            cout << "Masukkan merk mobil  : "; getline(cin, k->jenis);
            cout << "Masukkan warna mobil : "; getline(cin, k->warna);
            k->waktuMasuk = time(0);

            daftarParkir[jumlahParkir++] = k;
        }

        cout << "\nMobil berhasil diparkir!\n";
    }

    void tampilkanParkiran() {
        if (jumlahParkir == 0) {
            cout << "\nTidak ada kendaraan yang sedang parkir.\n";
            return;
        }

        cout << "\nDAFTAR MOBIL YANG SUDAH TERPARKIR:\n";
        cout << "=====================================\n";
        for (int i = 0; i < jumlahParkir; i++) {
            Kendaraan* k = daftarParkir[i];
            time_t sekarang = time(0);
            double durasi = difftime(sekarang, k->waktuMasuk); // detik
            int jam = static_cast<int>(durasi) / 3600;
            int menit = (static_cast<int>(durasi) % 3600) / 60;
            int detik = static_cast<int>(durasi) % 60;

            cout << "Mobil ke-" << i + 1 << endl;
            cout << "Plat mobil  : " << k->platNomor << endl;
            cout << "Merk mobil  : " << k->jenis << endl;
            cout << "Warna mobil : " << k->warna << endl;
            cout << "Waktu parkir: " << jam << " jam " << menit << " menit " << detik << " detik\n";
            cout << "=====================================\n";
        }
    }

    void pembayaran() {
        if (jumlahParkir == 0) {
            cout << "\nTidak ada kendaraan yang sedang parkir.\n";
            return;
        }

        string plat;
        cout << "\nMasukkan plat mobil untuk pembayaran: ";
        getline(cin >> ws, plat);

        for (int i = 0; i < jumlahParkir; i++) {
            if (daftarParkir[i] && daftarParkir[i]->platNomor == plat) {
                time_t keluar = time(0);
                double durasi = difftime(keluar, daftarParkir[i]->waktuMasuk);
                int biaya = static_cast<int>(durasi) * 2; // Rp2 per detik

                cout << "\nB I A Y A   P A R K I R : Rp." << biaya << "\n";

                // Menghapus kendaraan dari daftar parkir karena sudah bayar atau keluar
                delete daftarParkir[i];
                for (int j = i; j < jumlahParkir - 1; j++)
                    daftarParkir[j] = daftarParkir[j + 1];

                daftarParkir[--jumlahParkir] = nullptr;
                return;
            }
        }

        cout << "\nPLAT TIDAK DITEMUKAN!\n";
    }
    // Destructor class Parkiran untuk menghapus semua pointer kendaraan yang sudah keluar dan bayar
    ~Parkiran() {
        for (int i = 0; i < jumlahParkir; i++) {
            if (daftarParkir[i]) {
                delete daftarParkir[i];
                daftarParkir[i] = nullptr;
            }
        }
    }
};


int main() {
    system ("cls");
    Petugas petugas;
    Parkiran parkir;

    cout << "===================================================\n";
    cout << "         S E L A M A T   D A T A N G               \n";
    cout << "   DI PORTAL PARKIR KHUSUS MOBIL MALL PRIENAL      \n";
    cout << "===================================================\n\n";
    cout << "Sebelum melanjutkan, silakan masukkan informasi Anda.\n";

    cout << "Masukkan nama : "; getline(cin, petugas.nama);
    cout << "Masukkan ID   : "; getline(cin, petugas.id);

    cout << "\nNama Petugas : " << petugas.nama << endl;
    cout << "ID Petugas   : " << petugas.id << endl;
    cout << "\nTERIMA KASIH ATAS KERJASAMANYA!\n";
    cout << "============= S E L A M A T   B E R T U G A S =============\n";

    int opsi;
    do {
        cout << "=====================================\n";
        cout << "Silakan pilih opsi berikut:\n";
        cout << "1. Tambahkan Daftar Kendaraan\n";
        cout << "2. Tampilkan Daftar Kendaraan\n";
        cout << "3. Pembayaran\n";
        cout << "4. Keluar Program\n";
        cout << "Masukkan opsi: ";
        cin >> opsi;
        cin.ignore();

        switch (opsi) {
            case 1:
                parkir.kendaraanMasuk();
                break;
            case 2:
                parkir.tampilkanParkiran();
                break;
            case 3:
                parkir.pembayaran();
                break;
            case 4:
                cout << "\nTerima kasih telah menggunakan layanan kami!\n";
                break;
            default:
                cout << "\nOpsi tidak valid! Silakan coba lagi.\n";
        }
    } while (opsi != 4);

    return 0;
}