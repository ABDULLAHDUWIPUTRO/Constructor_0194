#include <iostream>
using namespace std;

class mahasiswa{
    private:
       static int jmlmhs;
       public :

    string status;
    string nama;
    int nim;
    mahasiswa(string pnama, int pnim){
        status = "mahasiswa baru";
        nama = pnama;
        nim = pnim;
        cout << "mahasiswa dibuat" << nama << endl;
        cout << "status = " << status << endl;
        ++ jmlmhs;
    };
    mahasiswa(){
    cout << "mahasiswa dengan nama" << nama << "dihancurkan" << endl;
    ++jmlmhs;
    };
    static int gettotalmhs(){
        cout << "jumlah mahasiswa = " << jmlmhs << endl;
    };
};

int mahasiswa::jmlmhs = 0;

int main(){
    cout << "jumlah mahasiswa = " << mahasiswa::gettotalmhs() << endl;
    mahasiswa mhs1("rudy", 28);
    mahasiswa mhs2("joko", 73);
    mhs2.status = "mahasiswa uzur";
    cout << mhs2.status << endl;
    mahasiswa mhs3("wobo", 69);
    cout << "jumlah mahasiswa = " << mahasiswa::gettotalmhs() << endl;
    {
        mahasiswa mhs4("pra", 98);
        cout << "jumlah mahasiswa dalam bracket = " << mahasiswa::gettotalmhs() << endl;
    }
    cout << "jumlah mahasiswa = " << mahasiswa::gettotalmhs() << endl;
    return 0;
}