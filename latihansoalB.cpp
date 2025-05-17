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
#include <vector>
using namespace std;

class Peminjam;  // Forward declaration
class Petugas;
class Admin;

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

    friend class Petugas;  // Petugas berhak mengubah status peminjaman
    friend void aksesData(Admin&, const Buku&);
};

class Peminjam {
private:
    string nama;
    int ID;
    int totalPinjaman;

public:
    Peminjam(string n, int id) : nama(n), ID(id), totalPinjaman(0) {}

    friend class Petugas;  // Petugas berhak mengelola jumlah pinjaman
    friend void aksesData(Admin&, const Peminjam&);
};

class Petugas {
private:
    string nama;
    int ID_petugas;
    string levelAkses;

public:
    Petugas(string n, int id, string level) : nama(n), ID_petugas(id), levelAkses(level) {}

    void prosesPinjam(Buku* b, Peminjam* p) {
        if (!b->dipinjam) {
            b->dipinjam = true;
            p->totalPinjaman++;
            cout << "Peminjaman berhasil oleh " << p->nama << endl;
        } else {
            cout << "Buku sudah dipinjam!" << endl;
        }
    }

    void prosesKembali(Buku* b, Peminjam* p) {
        if (b->dipinjam) {
            b->dipinjam = false;
            p->totalPinjaman--;
            cout << "Pengembalian berhasil oleh " << p->nama << endl;
        } else {
            cout << "Buku tidak dalam status dipinjam!" << endl;
        }
    }

    friend class Admin;  // Admin berhak mengubah level akses
};

class Admin {
public:
    void ubahAksesPetugas(Petugas& petugas, string levelBaru) {
        petugas.levelAkses = levelBaru;
        cout << "Level akses Petugas diperbarui ke: " << levelBaru << endl;
    }

    friend void aksesData(Admin&, const Buku&);
    friend void aksesData(Admin&, const Peminjam&);
};

void aksesData(Admin& admin, const Buku& buku) {
    cout << "Admin mengakses buku yang sedang diproses: " << buku.judul << endl;
}

void aksesData(Admin& admin, const Peminjam& peminjam) {
    cout << "Admin melihat total pinjaman milik " << peminjam.nama 
         << ": " << peminjam.totalPinjaman << " buku." << endl;
}

int main() {
    Buku buku1("C++ Dasar", "Bjarne Stroustrup");
    Peminjam peminjam1("Abdullah", 101);
    Petugas petugas1("Rizal", 201, "Standar");
    Admin admin1;

    petugas1.prosesPinjam(&buku1, &peminjam1);
    admin1.ubahAksesPetugas(petugas1, "Senior");
    aksesData(admin1, buku1);
    aksesData(admin1, peminjam1);
    petugas1.prosesKembali(&buku1, &peminjam1);

    return 0;
}