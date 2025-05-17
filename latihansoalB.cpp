// Class Buku berisi informasi seperti judul, penulis, dan status peminjaman (bool dipinjam). Status ini bersifat privat dan tidak
// dapat diubah langsung oleh sembarang class. Hanya class Petugas yang dapat memproses status peminjaman atau pengembalian buku.
// Oleh karena itu, class Petugas harus dijadikan sebagai friend class dari Buku, sehingga dapat memodifikasi status peminjaman
// dengan method seperti prosesPinjam(Buku* b, Peminjam* p) dan prosesKembali(Buku* b).

// Class Peminjam menyimpan data pengguna seperti nama dan ID, serta jumlah buku yang sedang dipinjam (int totalPinjaman).
// Atribut totalPinjaman bersifat privat dan hanya dapat diubah oleh class Petugas yang memproses peminjaman atau pengembalian.
// Oleh karena itu, Petugas juga dijadikan friend class oleh Peminjam.

// Class Petugas bertanggung jawab terhadap operasional peminjaman dan pengembalian. Selain itu, ia memiliki atribut pribadi seperti
// nama, ID petugas, dan level akses (string levelAkses). Namun, hanya class Admin yang boleh mengubah level akses petugas
// berdasarkan performa. Karena itu, class Admin harus dijadikan friend class oleh Petugas.

// Terakhir, class Admin hanya berhak melihat statistik data, termasuk jumlah buku yang sedang dipinjam oleh seorang peminjam, dan
// melihat nama buku yang sedang diproses oleh petugas, tetapi tidak memiliki akses penuh terhadap atribut private class lain.
// Untuk itu, informasi-informasi tersebut diberikan melalui friend function yang didefinisikan di dalam class Peminjam dan Buku,
// tetapi diimplementasikan di dalam class Admin. Dengan kata lain, Admin hanya diizinkan mengakses data privat
// melalui fungsi friend yang disediakan secara terbatas.

#include <iostream>
using namespace std;

class Buku {
private:
    string judul;
    string penulis;
    bool dipinjam;

public:
    Buku(string j, string p) : judul(j), penulis(p), dipinjam(false) {}

    void tampilkanInfo() const {
        cout << "Judul: " << judul << ", Penulis: " << penulis 
             << ", Status: " << (dipinjam ? "Dipinjam" : "Tersedia") << endl;
    }

    void setDipinjam(bool status) {
        dipinjam = status;
    }

    bool getDipinjam() const {
        return dipinjam;
    }
};

class Peminjam {
private:
    string nama;
    int ID;
    int totalPinjaman;

public:
    Peminjam(string n, int id) : nama(n), ID(id), totalPinjaman(0) {}

    void tambahPinjaman() {
        totalPinjaman++;
    }

    void kurangiPinjaman() {
        if (totalPinjaman > 0) {
            totalPinjaman--;
        } else {
            cout << "Error: Tidak ada buku yang dipinjam untuk dikembalikan!" << endl;
        }
    }

    void tampilkanInfo() const {
        cout << "Nama Peminjam: " << nama << ", ID: " << ID 
             << ", Total Pinjaman: " << totalPinjaman << endl;
    }
    
    string getNama() const {
        return nama;
    }
};

class Petugas {
private:
    string nama;
    int ID_petugas;

public:
    Petugas(string n, int id) : nama(n), ID_petugas(id) {}

    void prosesPinjam(Buku &b, Peminjam &p) {
        if (!b.getDipinjam()) {
            b.setDipinjam(true);
            p.tambahPinjaman();
            cout << "Peminjaman berhasil oleh " << p.getNama() << endl;
        } else {
            cout << "Buku sudah dipinjam!" << endl;
        }
    }

    void prosesKembali(Buku &b, Peminjam &p) {
        if (b.getDipinjam()) {
            b.setDipinjam(false);
            p.kurangiPinjaman();
            cout << "Pengembalian berhasil oleh " << p.getNama() << endl;
        } else {
            cout << "Buku tidak dalam status dipinjam!" << endl;
        }
    }
};

int main() {
    Buku buku1("C++ Dasar", "Bjarne Stroustrup");
    Peminjam peminjam1("Abdullah", 101);
    Petugas petugas1("Rizal", 201);

    cout << "\n--- Informasi Awal ---" << endl;
    buku1.tampilkanInfo();
    peminjam1.tampilkanInfo();

    cout << "\n--- Proses Peminjaman ---" << endl;
    petugas1.prosesPinjam(buku1, peminjam1);
    buku1.tampilkanInfo();
    peminjam1.tampilkanInfo();

    cout << "\n--- Proses Pengembalian ---" << endl;
    petugas1.prosesKembali(buku1, peminjam1);
    buku1.tampilkanInfo();
    peminjam1.tampilkanInfo();

    return 0;
}