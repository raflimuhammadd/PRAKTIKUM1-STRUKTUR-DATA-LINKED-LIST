#include <iostream>
#include <iomanip>

using namespace std;

int pil;
void pilih();
void newList();
void addBack();
void addFront();
void deleteBack();
void deleteFront();
void printT();

struct patterns
{
  char nomor[20], key;
  string categories;
  int berat;
  struct patterns *next;
} sim, *baru, *awal = NULL, *akhir = NULL, *hapus, *help;

void newList()
{
  int temp_categories;
  baru = (patterns *)malloc(sizeof(struct patterns));
  cout << "Masukkan Nomor ID Kontainer : ";
  cin >> baru->nomor;
  cout << "Masukkan Berat Kontainer (T) : ";
  cin >> baru->berat;
  do
  {
    cout << "Masukkan Categories Barang (Pilih Nomor = 1. Makanan/2. Elektronik/ 3.Chemical) : ";
    cin >> temp_categories;
    if (temp_categories == 1)
      baru->categories = "Makanan";
    else if (temp_categories == 2)
      baru->categories = "Elektronik";
    else if (temp_categories == 3)
      baru->categories = "Chemical";
    else
      cout << "Pilihan Tidak Tersedia, Pilih yang sudah tersedia!!" << endl;
  } while (!(temp_categories >= 1 && temp_categories <= 3));

  baru->next = NULL;
}

void addBack()
{
  if (awal == NULL)
  {
    awal = baru;
  }
  else
  {
    akhir->next = baru;
  }
  akhir = baru;
  akhir->next = NULL;
  cout << endl
       << endl;
  printT();
}

void addMiddle()
{
  bool gerbong_terlarang = false;
  // patterns *current = awal;
  newList();

  if (awal == NULL)
    addFront();
  else if (awal->berat < baru->berat)
  {
    if ((awal->categories == "Makanan" && baru->categories == "Chemical") || (awal->categories == "Chemical" && baru->categories == "Makanan"))
      gerbong_terlarang = true;
    else
      addFront();
  }
  else if (akhir->berat > baru->berat)
  {
    if ((akhir->categories == "Makanan" && baru->categories == "Chemical") || (akhir->categories == "Chemical" && baru->categories == "Makanan"))
      gerbong_terlarang = true;
    else
      addBack();
  }
  else
  {
    patterns *current = awal;
    while (current != NULL)
    {
      if (baru->berat < current->next->berat)
      {
        current = current->next;
      }
      else
      {
        if ((akhir->categories == "Makanan" && baru->categories == "Chemical") || (akhir->categories == "Chemical" && baru->categories == "Makanan"))
          gerbong_terlarang = true;
        else
        {
          baru->next = current->next;
          current->next = baru;
        }
        printT();
        break;
      }
    }
  }
  if (gerbong_terlarang)
    cout << endl
         << "BERBAHAYA!!!" << endl
         << "KERETA GAGAL DIKIRIMKAN, dikarenakan Makanan berdekatan dengan Chemical!!!" << endl;
}

void addFront()
{
  if (awal == NULL)
  {
    awal = baru;
    akhir = baru;
    akhir->next = NULL;
  }
  else
  {
    baru->next = awal;
    awal = baru;
  }
  cout << endl
       << endl;
  printT();
}

void deleteFront()
{
  if (awal == NULL)
    cout << "Kontainer Kosong" << endl;
  else
  {
    hapus = awal;
    awal = awal->next;
    free(hapus);
  }
  cout << endl
       << endl;
  printT();
}

void deleteBack()
{
  if (awal == NULL)
    cout << "Kontainer Kosong" << endl;
  else if (awal == akhir)
  {
    hapus = awal;
    awal = awal->next;
    free(hapus);
  }
  else
  {
    hapus = awal;
    while (hapus->next != akhir)
      hapus = hapus->next;
    akhir = hapus;
    hapus = akhir->next;
    akhir->next = NULL;
    free(hapus);
  }
  cout << endl
       << endl;
  printT();
}

bool search(patterns *awal, int x)
{
  patterns *current = awal;
  while (current != NULL)
  {
    if (current->key == x)
      return true;
    current = current->next;
  }
  return false;
}

void printT()
{
  if (awal == NULL)
    cout << "Kontainer Kosong" << endl;
  else
  {
    help = awal;
    cout << "=========================================" << endl;
    cout << "|  NOMOR ID  |  BERAT  |  categories BARANG  |" << endl;
    cout << "=========================================" << endl;

    while (help != NULL)
    {
      cout << "|" << setiosflags(ios::left) << setw(12) << help->nomor << "|";
      cout << " " << setiosflags(ios::left) << setw(8) << help->berat << "|";
      cout << " " << setiosflags(ios::left) << setw(15) << help->categories << "|" << endl;
      help = help->next;
    }
  }
}

void pilih()
{
  // cout << ">> On Going PILIH" << endl;
  if (pil == 1 || pil == 2)
  {
    // cout << "Tambah Data" << endl;
    addMiddle();
  }
  else if (pil == 3)
  {
    // cout << "Hapus Depan" << endl;
    deleteFront();
  }
  else if (pil == 4)
  {
    // cout << "Hapus Belakang" << endl;
    deleteBack();
  }
  else if (pil == 5)
  {
    // cout << "Menampilkan Data" << endl;
    printT();
  }
  else
    cout << "Exit";
}

int main()
{
  cout << "PROGRAM LINKED TRAIN" << endl;
  do
  {
    cout << endl
         << endl;
    cout << "Menu Pilihan" << endl;
    cout << "1. Tambah Kontainer Di Depan " << endl;
    cout << "2. Tambah Kontainer DI Belakang" << endl;
    cout << "3. Hapus Kontainer Di Depan" << endl;
    cout << "4. Hapus Kontainer Di Belakang" << endl;
    cout << "5. Print Seluruh Kontainer" << endl;
    cout << "6. Exit" << endl
         << endl;
    cout << "Pilih Salah Satu : ";
    cin >> pil;
    pilih();
  } while (pil != 6);
  return 0;
}
