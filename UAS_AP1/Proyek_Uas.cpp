#include <iostream>
#include <vector>
#include <string>
#include <ctime> //header untuk menghitung waktu (real)
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
    Kendaraan* daftarParkir[20]; // kapasitas tetap
    int jumlahParkir;

public:
    Parkiran() {
        jumlahParkir = 0;
        for (int i = 0; i < 20; i++)
            daftarParkir[i] = nullptr;
    }

void kendaraanMasuk() {
    int jumlah;
    cout <<"Masukkan jumlah mobil yang akan diparkirkan: ";
    cin >> jumlah;
    cin.ignore();

    if (jumlah >20 ){
        cout<< "\nMaaf, parkiran hanya dapat memuat 20 mobil !\n\n";
        return;
    }
    if (jumlahParkir > 20) {
        cout << "\nMaaf, parkiran hanya dapat memuat 20 mobil !\n\n";
        return;
    }
    //untuk menginput data kendaraan(plat,merk,warna)
    for(int i=0;i<jumlah;i++){
    cout << "mobil ke-"<<i+1<<": ";
    Kendaraan* k = new Kendaraan();
    cout << "\nMasukkan plat mobil  : ";
    getline(cin, k->platNomor);
    cout << "Masukkan merk mobil  : ";
    getline(cin, k->jenis);
    cout << "Masukkan warna mobil : ";
    getline(cin, k->warna);
    k->waktuMasuk = time(0);

    daftarParkir[jumlahParkir++] = k;}

    cout << "\nKendaraan berhasil masuk ke parkiran.\n\n";
}

void tampilkanParkiran() {
    cout << "\nDAFTAR MOBIL YANG SUDAH TERPARKIR :\n";

    if (jumlahParkir == 0) {
        cout << "Belum ada kendaraan yang parkir.\n\n";
        return;
    }

    time_t sekarang = time(0);

    //menampilkan kendaraan yang sudah terparkir
    for (int i = 0; i < jumlahParkir; i++) {
        double durasi = difftime(sekarang, daftarParkir[i]->waktuMasuk); // detik
        int jam = static_cast<int>(durasi) / 3600;
        int menit = (static_cast<int>(durasi) % 3600) / 60;
        int detik = static_cast<int>(durasi) % 60;

        cout << "=======================================================================\n";
        cout << "Mobil ke-" << i + 1 << endl;
        cout << "Plat mobil  : " << daftarParkir[i]->platNomor << endl;
        cout << "Merk mobil  : " << daftarParkir[i]->jenis << endl;
        cout << "Warna mobil : " << daftarParkir[i]->warna << endl;
        cout << "Waktu parkir: " << jam << " jam " << menit << " menit " << detik << " detik\n\n";
    }
}


void pembayaran() {
    if (jumlahParkir == 0) {
        cout << "\nTidak ada kendaraan yang sedang parkir.\n\n";
        return;
    }

    string plat;
    cout << "Masukkan plat mobil yang ingin dibayar : ";
    getline(cin, plat);

    //mencari plat mobil inputan dalam parkiran dan menghitung biaya parkir
    for (int i = 0; i < jumlahParkir; i++) {
        if (daftarParkir[i]->platNomor == plat) {
            time_t keluar = time(0);
            double durasi = difftime(keluar, daftarParkir[i]->waktuMasuk); // dalam detik

            int biaya = static_cast<int>(durasi) * 2; //biaya parkir = Rp.2 per detik
            cout << "B I A Y A   P A R K I R  : Rp" << biaya << "\n\n";

            //menghapus data kendaraan dari parkiran ketika sudah keluar dan bayar
            delete daftarParkir[i];
            for (int j = i; j < jumlahParkir - 1; j++)
                daftarParkir[j] = daftarParkir[j + 1];

            daftarParkir[--jumlahParkir] = nullptr;
            return;
        }
    }

    cout << "\nPLAT TIDAK DITEMUKAN !\n\n";
}

    //Destructor class parkiran untuk menghapus semua pointer kendaraan yang sudah keluar dan bayar
    ~Parkiran() {
        for (int i = 0; i < jumlahParkir; i++) {
            delete daftarParkir[i];
        }
    }
};

void tampilkanMenu() {
    cout << "Silahkan input opsi berikut dalam bentuk angka.\n";
    cout << "1. Tambahkan Daftar Kendaraan\n";
    cout << "2. Tampilkan Daftar Kendaraan\n";
    cout << "3. Pembayaran\n";
    cout << "4. Keluar Program\n";
    cout << "Masukkan opsi : ";
}

int main() {
    system("cls");
    Petugas petugas;
    cout << "================================================================================\n";
    cout << "---------------------------S E L M A T  D A T A N G-----------------------------\n";
    cout << "                         DI PORTAL PARKIR KHUSUS MOBIL                          \n";
    cout << "                                 MALL PRIENAL                                   \n";
    cout << "================================================================================\n";
    cout << "Kami senang Anda telah hadir.\n";
    cout << "Sebelum melanjutkan, Silahkan masukkan informasi Anda yang akan bertugas hari ini.\n";
    cout << "\nMasukkan nama : ";
    getline(cin, petugas.nama);
    cout << "Masukkan ID   : ";
    getline(cin, petugas.id);

    Parkiran parkiran;
    int pilihan;

    cout << "\n\n========================================================================\n";
    cout << "Nama Petugas : " << petugas.nama << endl;
    cout << "ID Petugas   : " << petugas.id << endl;
    cout << "\n=====================TERIMA KASIH ATAS KERJASAMANYA!====================\n";
    cout << "-------------------- S E L A M A T  B E R T U G A S --------------------\n";
    cout << "========================================================================\n\n";

    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                parkiran.kendaraanMasuk();
                break;
            case 2:
                parkiran.tampilkanParkiran();
                break;
            case 3:
                parkiran.pembayaran();
                break;
            case 4:
                cout << "\nTerima kasih, " << petugas.nama << ". Sampai jumpa!\n";
                break;
            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 4);

    return 0;
}