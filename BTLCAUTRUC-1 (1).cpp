#include<conio.h>
#include<stdio.h>
#include <iostream>
#include <string.h>
#include<fstream>
#include<windows.h>
#define MAX 100
using namespace std;
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}
struct SinhVien {
    int id;
    string ten;
    char gioiTinh[5];
    int tuoi;
    float diemGiaitich;
    float diemCautruc;
    float diemLy;
    float diemTB ;
    string hocluc;
};
typedef SinhVien SV;
void printLine(int n);
void nhapThongTinSV(SV &sv, int id);
void nhapSV(SV a[], int id, int n);
void capNhatThongTinSV(SV &sv);
void capNhatSV(SV a[], int id, int n);
int xoaTheoID(SV a[], int id, int n);
void timKiemTheoTen(SV a[], string timTen, int n);
void tinhDTB(SV &sv);
void xeploai(SV &sv);
int idLonNhat(SV a[], int n);
void sapxepTheoDTB(SV a[], int n);
void sapXepTheoTen(SV a[], int n);
void showStudent(SV a[], int n);
void DocFile(SV a[], int &n);
void GhiFile(SV a[], int n);
void pressAnyKey();
int main() {
    int key;
    //char fileName[] = "sinhvien";
    SV arraySV[MAX];
    int soluongSV = 0;
    int idCount = 0;
     //nhap danh sach sinh vien tu file
    DocFile(arraySV, soluongSV);
    idCount = idLonNhat (arraySV, soluongSV);
    while(true) {
        gotoxy(40, 0); cout << "CHUONG TRINH QUAN LY SINH VIEN   \n";
        gotoxy(40, 1);cout << "              MENU TUY CHON    \n";
        gotoxy(40, 2);cout << "  1. Them sinh vien.                               \n";
        gotoxy(40, 3);cout << "  2. Cap nhat thong tin sinh vien boi ID.          \n";
        gotoxy(40, 4);cout << "  3. Xoa sinh vien boi ID.                         \n";
        gotoxy(40, 5);cout << "  4. Tim kiem sinh vien theo ten.                  \n";
        gotoxy(40, 6);cout << "  5. Sap xep sinh vien theo diem trung binh        \n";
        gotoxy(40, 7);cout << "  6. Sap xep sinh vien theo ten.                   \n";
        gotoxy(40, 8);cout << "  7. Hien thi danh sach sinh vien.                 \n";
        gotoxy(40, 9);cout << "  8. Ghi danh sach sinh vien vao file.             \n";
        gotoxy(40, 10);cout << "  0. Thoat                                         \n";
        gotoxy(40, 11);cout << "Nhap lua chon cua ban (0-8): ";
        cin >> key;
        switch(key){
            case 1:
                cout << "\n1. Them sinh vien.";
                idCount++;
                nhapSV(arraySV, idCount, soluongSV);
                printf("\nThem sinh vien thanh cong!");
                soluongSV++;
                pressAnyKey();
                break;
            case 2:
                if(soluongSV > 0) {
                    int id;
                    cout << "\n2. Cap nhat thong tin sinh vien. ";
                    cout << "\n Nhap ID: "; cin >> id;
                    capNhatSV(arraySV, id, soluongSV);
                }else{
                    cout << "\nDanh sach sinh vien trong!";
                }
                pressAnyKey();
                break;
            case 3:
                if(soluongSV > 0) {
                    int id;
                    cout << "\n3. Xoa sinh vien.";
                    cout << "\n Nhap ID: "; cin >> id;
                    if (xoaTheoID(arraySV, id, soluongSV) == 1) {
                        printf("\nSinh vien co id = %d da bi xoa.", &id);
                        soluongSV--;
                    }
                }else{
                    cout << "\nDanh sach sinh vien trong!";
                }
                pressAnyKey();
                break;
            case 4:
                if(soluongSV > 0) {
                    cout << "\n4. Tim kiem sinh vien theo ten.";
                    string timTen;
                    cout << "\nNhap ten de tim kiem: "; fflush(stdin); getline(cin, timTen);
                    timKiemTheoTen(arraySV, timTen, soluongSV);
                }else{
                    cout << "\nDanh sach sinh vien trong!";
                }
                pressAnyKey();
                break;
            case 5:
                if(soluongSV > 0) {
                    cout << "\n5. Sap xep sinh vien theo diem trung binh (GPA).";
                    sapxepTheoDTB(arraySV, soluongSV);
                    showStudent(arraySV, soluongSV);
                }else{
                    cout << "\nDanh sach sinh vien trong!";
                }
                pressAnyKey();
                break;
            case 6:
                if(soluongSV > 0) {
                    cout << "\n6. Sap xep sinh vien theo ten.";
                    sapXepTheoTen(arraySV, soluongSV);
                    showStudent(arraySV, soluongSV);
                } else {
                    cout << "\nDanh sach sinh vien trong!";
                }
                pressAnyKey();
                break;
            case 7:
                if(soluongSV > 0){
                    cout << "\n7. Hien thi danh sach sinh vien.";
                    showStudent(arraySV, soluongSV);
                }else{
                    cout << "\nDanh sach sinh vien trong!";
                }
                pressAnyKey();
                break;
            case 8:
                //if(soluongSV > 0){
                    cout << "\n8. Ghi danh sach sinh vien vao file.";
                    GhiFile(arraySV, soluongSV);
                pressAnyKey();
                break;
            case 0:
                cout << "\nBan da chon thoat chuong trinh!";
                getch();
                return 0;
            default:
                cout << "\nKhong co chuc nang nay!";
                cout << "\nHay chon chuc nang trong hop menu.";
                pressAnyKey();
                break;
        }
    }
}
void tinhDTB(SV &sv) {
    sv.diemTB = (sv.diemGiaitich + sv.diemLy + sv.diemCautruc) / 3;    
}
void xeploai(SV &sv) {
    if(sv.diemTB >= 8) sv.hocluc="Gioi";
    else if(sv.diemTB >= 6.5) sv.hocluc="Kha";
    else if(sv.diemTB >= 5) sv.hocluc="Trung binh";
    else sv.hocluc="Yeu";
}
// nhap sinh vien
void nhapThongTinSV(SV &sv, int id) { //&sv tham chieu sv
    cout << "\n Nhap ho va ten: "; fflush(stdin); getline(cin, sv.ten);//fflush xoa bo nho dem, gets nhap nhan ca space
    cout << " Nhap gioi tinh( Nam hoac Nu ): "; gets(sv.gioiTinh);
    cout << " Nhap tuoi: "; cin >> sv.tuoi;
    cout << " Nhap diem Giai tich: "; cin >> sv.diemGiaitich;
    cout << " Nhap diem Ly: "; cin >> sv.diemLy;
    cout << " Nhap diem Cau truc: "; cin >> sv.diemCautruc;
    sv.id = id;
    tinhDTB(sv);
    xeploai(sv);
}
void nhapSV(SV a[], int id, int n) {
    printLine(40);
    printf("\n Nhap sinh vien thu %d:", n + 1);
    nhapThongTinSV(a[n], id);//&sv gan vo a[n]
    printLine(40);
}
//chinh sua thong tin sinh vien theo id
void capNhatThongTinSV(SV &sv) {
    cout << "\n Nhap ho va ten: "; fflush(stdin); getline(cin, sv.ten);
    cout << " Nhap gioi tinh( Nam hoac Nu ): "; gets(sv.gioiTinh);
    cout << " Nhap tuoi: "; cin >> sv.tuoi;
    cout << " Nhap diem Giaitich: "; cin >> sv.diemGiaitich;
    cout << " Nhap diem Ly: "; cin >> sv.diemLy;
    cout << " Nhap diem Cautruc: "; cin >> sv.diemCautruc;
    tinhDTB(sv);
    xeploai(sv);
}
void capNhatSV(SV a[], int id, int n) {
    int found = 0;
    for(int i = 0; i < n; i++) {
        if (a[i].id == id) {
            found = 1;
            printLine(40);
            cout << "\n Cap nhat thong tin sinh vien co ID = " << id;
            capNhatThongTinSV(a[i]);
            printLine(40);
            break;
        }
    }
    if (found == 0) {
        printf("\n Sinh vien co ID = %d khong ton tai.", id);
    }
}
int xoaTheoID(SV a[], int id, int n) {   
    int found = 0;
    for(int i = 0; i < n; i++) {
        if (a[i].id == id) {
            found = 1;
            printLine(40);
            for (int j = i; j < n; j++) {
                a[j] = a[j+1];
            }
            cout << "\n Da xoa SV co ID = " << id;
            printLine(40);
            break;
        }
    }
    if (found == 0) {
        printf("\n Sinh vien co ID = %d khong ton tai.", id);
        return 0;
    } else {
        return 1;
    }
}
void timKiemTheoTen(SV a[], string timTen, int n) {
    SV arrayFound[MAX];
    int found = 0;
    for(int i = 0; i < n; i++) {
        if(timTen==a[i].ten) {
            arrayFound[found] = a[i];
            found++;
        }
    }
    showStudent(arrayFound, found);
}
void showStudent(SV a[], int n) {
    printLine(120);
    cout <<"STT\tID\tHo va ten\tGioi tinh\tTuoi\tGiaitich\tLy\tCautruc\t\tDiem TB\t\tHoc luc";
    for(int i = 0; i < n; i++) {
        // in sinh vien thu i ra man hinh
        cout<<"\n"<<i + 1;				
        cout<<"\t"<<a[i].id;
        cout<<"\t"<<a[i].ten;
        cout<<"\t\t"<<a[i].gioiTinh;
        cout<<"\t\t"<<a[i].tuoi;
        cout<<"\t"<<a[i].diemGiaitich<<"\t\t"<<a[i].diemLy<<"\t"<< a[i].diemCautruc;
        cout<<"\t\t"<<a[i].diemTB;
        cout<<"\t\t"<<a[i].hocluc;
    }
    printLine(120);
}
void sapxepTheoDTB(SV a[], int n) { //XAP SEP NOI BOT
    //Sap xep theo DTB tang dan
    SV tmp;
    for(int i = 0;i < n;i++) {
        for(int j = i+1; j < n;j++) {
            if(a[i].diemTB > a[j].diemTB) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}
void sapXepTheoTen(SV a[], int n) {
    //Sap xep sinh vien theo ten theo thu tu tang dan
    SV tmp;
    for(int i = 0;i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(a[i].ten>a[j].ten) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}
int idLonNhat (SV a[], int n) {
    int idMax = 0;
    if (n > 0) {
        idMax = a[0].id;
        for(int i = 0;i < n; i++) {
            if (a[i].id > idMax) {
                idMax = a[i].id;
            }
        }
    }
    return idMax;
}
void DocFile(SV a[], int &n){      
	ifstream rfile("cautruc.txt");//ifstream mo de doc rfile thay the cho cin
	rfile>>n;
	if(n==0) return;
	for(int i=0; i<n; i++){
		rfile.ignore(); rfile>>a[i].id;
		rfile.ignore(); getline(rfile, a[i].ten, ',');
		rfile>>a[i].gioiTinh; 
		rfile.ignore(); rfile>>a[i].tuoi;
		rfile.ignore(); rfile>>a[i].diemGiaitich; 
		rfile.ignore(); rfile>>a[i].diemLy;
		rfile.ignore(); rfile>>a[i].diemCautruc;
		rfile.ignore(); rfile>>a[i].diemTB;
		rfile.ignore(); getline(rfile, a[i].hocluc, '.');
	}
			rfile.close();
}
void GhiFile(SV a[], int n){
	ofstream File("cautruc.txt"); //mo de ghi 
	File<<n<<"\n";
	for(int i=0; i<n; i++){
		File<<a[i].id<<" ";
		File<<a[i].ten<<",";
		File<<a[i].gioiTinh<<" ";
		File<<a[i].tuoi<<" ";
		File<<a[i].diemGiaitich<<" ";
		File<<a[i].diemLy<<" ";
		File<<a[i].diemCautruc<<" ";
		File<<a[i].diemTB<<" ";
		if(i==n-1) File<<a[i].hocluc<<".";
		else File<<a[i].hocluc<<".\n";
	}
	File.close();
}
void printLine(int n) {
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "_";
    }
    cout << endl;
}
void pressAnyKey() {
    cout << "\n\nBam phim bat ky de tiep tuc...";
    getch();
    system("cls");
}
