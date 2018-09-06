#include <bits/stdc++.h>
using namespace std;



int getoption(){int input;
	system("cls");
	cout << "program crud data pekerja" << endl;
  cout << "========================================================" << endl;

 cout << "1.tambah data" << endl; 
 cout << "2.tampilkan data" << endl; 
 cout << "3.rubah data" << endl; 
 cout << "4.hapus data" << endl; 
 cout << "5.selesai" << endl;
 cout << "=========================================================" << endl;
 cout << "by M Raehan Akbar" << endl;
 cout << "\n";
cout << "masukkan pilihan 1-5: ";
cin >> input;
cin.ignore(numeric_limits<streamsize>::max(),'\n');
return input;}
//================================================================================================================
struct pekerja{int pk;
string nama_pekerja;
string alamat_pekerja;
string posisi_pekerja;
string nohp_pekerja;
string pendidikan_terakhir_pekerja;};
//================================================================================================================
void cekdatabase(fstream &database){
	if (database.is_open())
	{
		cout << "data ditemukan" << endl;
	}else{cout << "data tidak ditemukan,buat data baru" << endl;
database.close();
database.open("database.bin",ios::trunc|ios::out|ios::in|ios::binary);}}

//=================================================================================================================

void writedatapekerja(fstream &database,int posisi,pekerja &inputpekerja){
database.seekp((posisi - 1)*sizeof(inputpekerja),ios::beg);
database.write(reinterpret_cast<char*>(&inputpekerja),sizeof(pekerja));
}

//=================================================================================================================

int getdatasize(fstream &database){int start,end;
database.seekg(0,ios::beg);
start = database.tellg();
database.seekg(0,ios::end);
end = database.tellg();
return (end-start)/sizeof(pekerja);}

//==================================================================================================================

pekerja readdata(fstream &database,int posisi){
pekerja readpekerja;
database.seekg((posisi-1)*sizeof(pekerja),ios::beg);
database.read(reinterpret_cast<char*>(&readpekerja),sizeof(pekerja));
return readpekerja;}

//====================================================================================================================


//===========================================================================================================================


void addatapekerja(fstream &database){
       

       pekerja inputpekerja,lastpekerja;

       inputpekerja.pk = 1;
       int size = getdatasize(database);

       cout << "ukuran data: " << size << endl;
       if (size == 0)
       {
       	inputpekerja.pk = 1;
       }else{lastpekerja = readdata(database,size);
       	cout << "pk = " << lastpekerja.pk << endl;
        inputpekerja.pk = lastpekerja.pk+1;}

       // readdata(database,size);

cout <<"Nama Pekerja: ";
getline(cin, inputpekerja.nama_pekerja);
cout <<"Alamat Pekerja: ";
getline(cin, inputpekerja.alamat_pekerja);
cout <<"Posisi Pekerja: ";
getline(cin, inputpekerja.posisi_pekerja);
cout <<"No hp pekerja: ";
getline(cin, inputpekerja.nohp_pekerja);
cout <<"Pendidikan terakhir pekerja: ";
getline(cin, inputpekerja.pendidikan_terakhir_pekerja);

writedatapekerja(database,size+1,inputpekerja);
}


void membacadatapekerja(fstream &database){int size = getdatasize(database);
pekerja showpekerja;

cout << "no.\tpk.\tnama.\talamat.\tposisi.\tkontak.\tpendidikan" << endl;

for (int i = 1; i <= size; ++i)
{   
	showpekerja  = readdata(database,i);
	cout << i << "\t";
	cout << showpekerja.pk << "\t";
	cout << showpekerja.nama_pekerja << "\t";
	cout << showpekerja.alamat_pekerja << "\t";
	cout << showpekerja.posisi_pekerja << "\t";
	cout << showpekerja.nohp_pekerja << "\t";
	cout << showpekerja.pendidikan_terakhir_pekerja<< endl;
}
}


void ubahdata(fstream &database){int nomor;
pekerja ubahpekerja;
cout << "pilih no ";
cin >> nomor;
cin.ignore(numeric_limits<streamsize>::max(),'\n');

ubahpekerja = readdata(database,nomor);
cout << "\n\n pilihan data: " << endl;
cout <<"Nama Pekerja: " << ubahpekerja.nama_pekerja << endl;
cout <<"Alamat Pekerja" << ubahpekerja.alamat_pekerja << endl;
cout <<"Posisi Pekerja" << ubahpekerja.posisi_pekerja << endl;
cout <<"Kontak Pekerja" << ubahpekerja.nohp_pekerja << endl;
cout <<"Pendidikan Terakhir Pekerja" << ubahpekerja.pendidikan_terakhir_pekerja << endl;

cout << "\n merubah data" << endl;
cout << "Nama Pekerja: ";
getline(cin,ubahpekerja.nama_pekerja);
cout << "Almat Pekerja: ";
getline(cin,ubahpekerja.alamat_pekerja);
cout << "Posisi Pekerja: ";
getline(cin,ubahpekerja.posisi_pekerja);
cout << "Kontak Pekerja: ";
getline(cin,ubahpekerja.nohp_pekerja);
cout << "Pendidikan Pekerja: ";
getline(cin,ubahpekerja.pendidikan_terakhir_pekerja);

writedatapekerja(database,nomor,ubahpekerja);
}

void hapusdata(fstream &database){
  int no,size,offset;
  pekerja blankpekerja,temppekerja;
  fstream datasementara;
  size = getdatasize(database);
  cout << "hapus no: ";
  cin >> no;

  writedatapekerja(database,no,blankpekerja);

  datasementara.open("temp.dat", ios::trunc|ios::out|ios::in|ios::binary);

offset = 0;

for (int i=1; i<= size; i++)
{
	temppekerja = readdata(database,i);
	if (!temppekerja.nama_pekerja.empty() )
	{
		writedatapekerja(datasementara,i - offset,temppekerja);
	}else{
		offset++;
		cout << "deleted item" << endl;
	}

}

size = getdatasize(datasementara);
database.close();
database.open("data.bin",ios::trunc|ios::out|ios::binary);
database.close();
database.open("data.bin",ios::out|ios::in|ios::binary);

for (int i = 1; i <= size; i++)
{   temppekerja = readdata(datasementara,i);
	writedatapekerja(database,i,temppekerja);
	
}

}
//==================================================================================================================================================================



int main(int argc, char const *argv[])
{   fstream database;
	database.open("database.bin",ios::out|ios::in|ios::binary);
      
	cekdatabase(database);




	int pilihan = getoption();
    char is_continue;
	while(pilihan != 5){

	switch(pilihan){case 1 : cout << "menambah data pekerja" <<endl;
	                addatapekerja(database);
	                break;
                    case 2 : cout << "menampilkan data pekerja" <<endl;
                    membacadatapekerja(database);
                    break;
                    case 3 : cout << "merubah data pekerja" <<endl;
                    membacadatapekerja(database);
                    ubahdata(database);
                    membacadatapekerja(database);
                    break;
                    case 4 : cout << "menghapus data pekerja" <<endl;
                    membacadatapekerja(database);
                    hapusdata(database);
                    membacadatapekerja(database);
                    break;
                    default: cout << "404 not found" << endl;}
cout << "kembali ke menu(y)/menyudahi program(n)";
cin >> is_continue;
if((is_continue == 'y') | (is_continue == 'Y')){                   
pilihan = getoption();	} else if((is_continue == 'n') | (is_continue == 'N')) { 
	break;}

    
}

	cin.get();
	return 0;
}

