#include<iostream> 
#include<fstream> 
#include <string>
using namespace std;

struct PhongKhachSan{
	int id;
	string name;
	float giaThue; 
}; 
struct Node{
	PhongKhachSan dataKs;
	Node *next; 
};
struct stack{
	Node *top; 
}; 
//typedef Node *KS; 
void input(stack &s,int n);
void Push(stack &s,PhongKhachSan KS);
Node *MakeNode(stack S,PhongKhachSan KS);
int len(stack s);
int isEmpty(stack s);
void Init(stack &s);
void print(stack &s) ;
PhongKhachSan Pop(stack &s);
//

void Init(stack &s) {
	s.top = NULL; 
}
int isEmpty(stack s) {
	return (s.top==NULL) ;
}
int len(stack s) {
	int dem = 0;
	Node *p = s.top;
	while(p!=NULL) {
		dem++;
		p = p->next; 
	}
	return dem; 
}
Node *MakeNode(stack S,PhongKhachSan KS)
{
	Node *p = new Node;
	p->dataKs = KS;
	p->next = S.top;
	return p;
}
// hien thi phong
void print(stack &s) {
	stack temp = s; 
	while(!isEmpty(temp)) {
		PhongKhachSan KS = Pop(temp);
		cout<<KS.id<<"\t"<<KS.name<<"\t"<<KS.giaThue;
		cout<<endl;
//		Push(s,KS);
	}
}
void Push(stack &s,PhongKhachSan KS){
	Node *p = new Node;
	p = MakeNode(s,KS);
	p->next = s.top;
	s.top = p;
}
void input(stack &s,int n) {
	PhongKhachSan KS;
	int i = 0;
	do{
		if(i<n){
			cout<<"Nhap vao id khach san :";
			cin>>KS.id;
			cout<<"Nhap ten khach san :";
			cin>>KS.name;
			cout<<"Gia phong thue :";
			cin>>KS.giaThue;	
			Push(s,KS);
		}
		if(i==n){
			break;
		}
		i++;
	}while(true);
}
//
//doc thong tin tu tep len man hinh terminal 
void docTep(stack &s) {
	ifstream f1; 
	int soLuong;
	PhongKhachSan KS;
	f1.open("QuanLyPhong.text");
	if(!f1)  {
		cout<<"Loi mo tep !" ;
		return; 
	}
	f1>>soLuong;
	for(int i = 0 ;i<soLuong;i++) {
		f1>>KS.id;
		f1>>KS.name;
		f1>>KS.giaThue;
		Push(s,KS) ;
	}
	f1.close() ;
}
//ghi thong tin vao tep 
void ghiTep(stack &s,int soLuong) {
	ofstream f1;
    PhongKhachSan KS;
    f1.open("QuanLyPhong.txt");
    if (!f1) {
        cout << "Loi mo tep !" ;
        return;
    }
    stack temp = s;
	f1<<"So Luong phong :"<<soLuong<<endl;
	f1<<"\nThong tin\n" ;
	f1<<"id\t\tTen\t\tGia Thue"<<endl;
	while(!isEmpty(temp)) {
		KS = Pop(temp) ;
		f1 << KS.id << "\t\t" << KS.name << "\t\t" << KS.giaThue << endl;
	}
	cout<<"\nGhi thanh cong\n"; 
	f1.close()   ;
}
//Ham so sanh cac id giong nhau 

//Pop
PhongKhachSan Pop(stack &s){
	if(isEmpty(s)){
		cout<<"Khong co phong !";
	}
	else{
		PhongKhachSan KS = s.top->dataKs;
//		neu minh xoa di thi  
		Node *temp = s.top; 
		s.top = s.top->next;
//		delete temp; 
		return KS; 
	}
}
//Xoa phong co gia tien trong khoang tu 3tr den 5tr den so phong le 
void HienPhongTuAdenB(stack &s,float giaPhongBatDau ,float giaPhongKetThuc){
	stack temp;
	stack hienTai = s; 
	while(!isEmpty(hienTai)){
		PhongKhachSan KS = Pop(hienTai);
		if(KS.giaThue > giaPhongBatDau&&KS.giaThue<giaPhongKetThuc){
			Push(temp,KS);
		}
	}
	while(!isEmpty(temp)){
		PhongKhachSan KS = Pop(temp);
		//tra ve s 
	
		cout<<KS.id<<"\t"<<KS.name<<"\t"<<KS.giaThue;
		cout<<endl;	
//		Push(s,KS); 
	}
}
//kiem tra phong tra ve so thu tu phong 
int TimKiem(stack s , PhongKhachSan phong) {
	int ketQua = 0;
	stack temp = s; 
	if(isEmpty(temp)) {
		ketQua = -1; 
	}
	else{
		PhongKhachSan kiemTra; 
		while(!isEmpty(s)) {
			kiemTra = Pop(s) ;
			if(kiemTra.id==phong.id) {
				ketQua = 1;
				break; 
			}
		}
	}
	return ketQua; 
}
//tim kiem tra ve ten phong 
PhongKhachSan TimKiemTraVePhong(stack s, PhongKhachSan phong) {
	stack temp = s;
	if(isEmpty(temp)) {
		cout<<"Khong co phong!" ;
		PhongKhachSan phongRong = {0, "", 0};
		return phongRong; 
	}
	else{
		PhongKhachSan kiemTraPhong;
		while(!isEmpty(temp) ) {
			kiemTraPhong = Pop(s);
			if(kiemTraPhong.id==phong.id) {
				return kiemTraPhong; 
			}
		}
	} 
}

//y tuong xay dung tang khach san , moi tang co 4 phong 
//vi du tim kiem tang 1 co phong ma id la 134 hay khong 
// y tuong xay dung code la , moi tang se tuong ung voi 1 stack , vi du stack tang1 , stack tang2 ...
// cach duyet cac stack la cu goi tang do len  
PhongKhachSan PopTang(stack s[],int tang) {
	if(isEmpty(s[tang])) {
		cout<<"Khong co phong!!" ;
		PhongKhachSan phongRong = {0, "", 0};
		return phongRong; 
	}
	else{
		PhongKhachSan KS = s[tang].top->dataKs;
		Node *temp =s[tang].top;
		s[tang].top = s[tang].top->next;
		delete temp;
		return KS; 
	} 
}
//Dien thong tin phong cho moi tang 
void DienThongTinPhong(stack s[],int tang) 
{
//	stack sTang[10] ;
	PhongKhachSan KS;
	for(int i = 0;i<tang;i++) {
		Init(s[i]) ;
		cout<<"\nTang thu ["<<i+1<<" ]"<<endl; 	
		int j = 0;
		do{
		if(j<2){
			
			cout<<"Nhap vao id khach san ["<<j+1<<" ]";
			cin>>KS.id;
			cout<<"Nhap ten khach san ["<<j+1<<" ]";
			cin>>KS.name;
			cout<<"Gia phong thue ["<<j+1<<" ]";
			cin>>KS.giaThue;	
			Push(s[i],KS);
		}
		else{
			break;
		}
		j++;
	}while(true) ;
	}
	
}
//in thong tin tang va phong 
void print(stack s[],int tang) {
//	stack temp = s; 
	for(int i = 0 ;i<tang;i++) {
		stack temp = s[i] ;
		while(!isEmpty(temp)) {
			PhongKhachSan KS = Pop(temp);
			cout<<KS.id<<"\t"<<KS.name<<"\t"<<KS.giaThue;
			cout<<endl;
	//		Push(s,KS);
		}	
	}
	
}
int main() {
 	stack s;
    Init(s);
  	PhongKhachSan phong1 = {1, "Phong 101", 1100};
    PhongKhachSan phong2 = {2, "Phong 102", 150};
    PhongKhachSan phong3 = {3, "Phong 103", 3900};
    PhongKhachSan phong4 = {4, "Phong 104", 1300};
    PhongKhachSan phong5 = {5, "Phong 105", 40.0};
 	PhongKhachSan phong6 = {6, "Phong 106", 4500};
    PhongKhachSan phong7 = {7, "Phong 107", 28.0};	
    // T? �?ng th�m m?u 5 ph?ng v�o danh s�ch �?t
    Push(s, phong1);
    Push(s, phong2);
    Push(s, phong3);
    Push(s, phong4);
    Push(s, phong5);
    Push(s, phong6);
    Push(s, phong7);
    print(s);
    PhongKhachSan phong;
////	input(s,2);
//	cout<<"\nKhoang tu A den B\n" ;
//	HienPhongTuAdenB(s,1000,3000);
//	cout<<"\n\tHien phong \n" ;
//	
//	
//	print(s) ; // bay gio no se hien ca 2 phong  
//	int n;
//	cin>>n; 
//	input(s,n);
//	ghiTep(s,n);
//	

//	timKiem tra ve so nguyenn  
	PhongKhachSan timKiemPhong; 
	cout<<"\nNhap id phong muon tim kiem :";
	cin>>timKiemPhong.id; 
	int ketQua = TimKiem(s,timKiemPhong)  ;
	if(ketQua==-1||ketQua == 0){
		cout<<"\nKhong tim thay phong\n" ;
	}
	else{
		cout<<"Tim thay phong co id :"<<timKiemPhong.id;
	}
	// tim kiem tra ve kieu struct 
	PhongKhachSan kiemTraPhongStruct = TimKiemTraVePhong(s,timKiemPhong);
	if(kiemTraPhongStruct.id != 0){
		cout<<"\nTim thay phong co id :"<<kiemTraPhongStruct.id<<"\t"<<kiemTraPhongStruct.name<<"\t"<<kiemTraPhongStruct.giaThue; 
	}
	else{
		cout<<"\nKhong tim thay phong\n" ;	
	}
//	cout<<"\nGhi Tep !\n" ;
//	ghiTep(s);

	//xay dung so tang cho khach san 
	stack sTang[10] ;
	
	int tang;
	cout<<"\nNhap so tang khach san va moi tang toi da la 4 phong :"; 
	cin>>tang;  
	DienThongTinPhong(sTang,tang);
	cout<<"\nIn thong tin \nID \t\t Ten phong \t\t Gia thue\n";
	print(sTang,tang);
	
	
	
	
//    while (true) {
//        cout << "=== Quan Ly Dat Phong Khach San ===" << endl;
//        cout << "1. Dat phong" << endl;
//        cout << "2. Huy phong" << endl;
//        cout << "3. Xem danh sach phong dang thue" << endl;
//        cout << "4. Thoat" << endl;
//        cout << "Chon chuc nang: ";
//        cin >> choice;
//
//        switch (choice) {
//            case 1:
//                cout << "Nhap ID phong: ";
//                cin >> phong.id;
//                cout << "Nhap ten phong: ";
//                cin.ignore();
//                getline(cin, phong.name);
//                cout << "Nhap gia thue: ";
//                cin >> phong.giaThue;
//                Push(s, phong);
//                cout << "Dat phong thanh cong!" << endl;
//                break;
//            case 2:
//                if (!isEmpty(s)) {
//                    Pop(s);
//                    cout << "Huy phong thanh cong!" << endl;
//                } else {
//                    cout << "Khong co phong nao duoc thue hien tai." << endl;
//                }
//                break;
//            case 3:
//                ShowPhongDangThue(s);
//                break;
//            case 4:
//                cout << "Ket thuc chuong trinh." << endl;
//                return 0;
//            default:
//                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
//                break;
//        }
//    }
//; 
	return 0; 
}


