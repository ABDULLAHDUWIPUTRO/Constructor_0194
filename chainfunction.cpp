#include <iostream>
2 using namespace std;

class buku
4
5 string judul;
6
7 public:
8 buku setJudul(string judul)
9 {
10 this->judul = judul;
11 return *this; // chain function
12 }
13 string getJudul((
14 {
15 return this->judul;
16 }
17
18 } bukunya;
