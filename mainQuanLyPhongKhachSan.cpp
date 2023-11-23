#include<iostream>
#include<fstream> 
#include <string>
#include<vector>
#include<limits>
using namespace std;
struct PhongKhachSan{
	int id;
	string name;
	double giaThue; 
};

struct Node{
	PhongKhachSan dataKs;
	Node *next,*prev; 
};
struct stack{
	Node *top; 
}; 
void Init(stack &s) {
	s.top = NULL; 
}
int isEmpty(stack s) {
	return (s.top==NULL) ;
}
int len(stack s) {
	int dem = 0;
	while(s.top!=NULL) {
		dem++;
		s.top = s.top->next; 
	}
	return dem; 
}
Node *MakeNode(stack S,PhongKhachSan KS)
{
	Node *p = new Node;
	p->dataKs = KS;
	p->next = S.top;
	p->prev = NULL;
	return p;
}
//Thêm đỉnh
void Push(stack &s,PhongKhachSan KS){
	Node *p = new Node;
	p = MakeNode(s,KS);
//	p->next = s.top;
	if(s.top !=NULL){
		s.top->prev = p; 
	}
	s.top = p;
}
// Thêm vào đáy
// tim node đáy do tra ve nó
Node *nodeLastList(stack s){
	Node *temp = s.top;
	while(temp->next != NULL){
		temp = temp->next;
	}
	return temp;
}
void insertLast(stack &s,PhongKhachSan KS){
	Node *p = new Node;
	if(isEmpty(s)){
		cout<<"Stack rong !";
		return;
	}
	while(s.top!=NULL){
		s.top = s.top->next;
	}
	s.top = p;
}

PhongKhachSan Pop(stack &s){
	if(isEmpty(s)){
		cout<<"Khong co phong !";
	}
	PhongKhachSan KS = s.top->dataKs;
//	neu minh xoa di thi  
	Node *temp = s.top; 
	s.top = s.top->next;
//	delete temp; 
	return KS; 
}
// Lấy phần tử đầu và xóa đi 
PhongKhachSan delPhongFirst(stack &s){
	if(isEmpty(s)){
		cout<<"Khong co phong ";
	}
	while(s.top->next!=NULL){
		s.top = s.top->next;
	}
		return Pop(s);
}
void printStack(stack s) {
	stack temp = s; 
	while(!isEmpty(temp)) {
		PhongKhachSan KS = Pop(temp);
		cout<<KS.id<<"\t"<<KS.name<<"\t"<<KS.giaThue;
		cout<<endl;
//		Push(s,KS);
	}
}
//In man hinh bang con tro prev ,( tức là nó có ý nghĩa in ngược lại , sử dụng trong trường hợp dùng đến Pop sau đó push vào danh sách )
void inManHinhToNode(stack s) {
    if (isEmpty(s)) {
        cout << "rong!!";
        return;
    } else {
        Node* temp = nodeLastList(s); // node này đang ở vị trí node cuối
        while (temp != NULL) {
            cout << temp->dataKs.id << "\t\t" << temp->dataKs.name << "\t\t" << temp->dataKs.giaThue << endl;
            temp = temp->prev;
        }
    }
}
// Thêm hàm insertLast để giải quyết vấn đề in ra
void insertLastThemPrev(stack &s, PhongKhachSan KS) {
    Node *p = MakeNode(s, KS);
    if (isEmpty(s)) {
        cout << "Stack rong !";
        return;
    }
    Node *lastNode = nodeLastList(s);
    lastNode->next = p;
    p->prev = lastNode;
    p->next = NULL;
    s.top = p; // Cập nhật con trỏ đỉnh của stack
}
void NhapPhong(stack& s) {
    for (int i = 0; i < 2; i++) {
        PhongKhachSan phong;
        cout << "Nhap thong tin cho phong " << (i + 1) << endl;
        cout << "Nhap ID: ";
        cin >> phong.id;
        cout << "Nhap ten phong: ";
        cin.ignore();
        getline(cin, phong.name);
        cout << "Nhap gia thue: ";
        cin >> phong.giaThue;
        // Kiểm tra ID trùng lặp trong tầng hiện tại
        bool trungLap = false;
        stack temp = s;
        while (!isEmpty(temp)) {
            PhongKhachSan Ks = Pop(temp);
            if (phong.id == Ks.id) {
                trungLap = true;
                cout << "ID da ton tai trong tang nay. Vui long nhap lai." << endl;
                break;
            }
        }
        if (!trungLap) {
            Push(s, phong);
        } else {
            i--; // Nếu ID trùng lặp, nhập lại cho phòng này
        }
    }
}
// nhập cho mỗi tầng
//gop tat ca cac stack tang vao stack khachSan ý tưởng là gộp tất cả các tầng vào 1 stack 
//gop tat ca cac stack tang vao stack khachSan ý tưởng là gộp tất cả các tầng vào 1 stack 
void gopTatCaStack(stack sTang[], stack &merge, int tang) {
    for (int i = 0; i < tang; i++) {
        stack temp = sTang[i];
        // Kiểm tra stack tạm có rỗng không
        while (!isEmpty(temp)) {
            PhongKhachSan mergePhong = Pop(temp);
            Push(merge, mergePhong);
        }
        // Không làm rỗng tầng hiện tại
        // Nếu bạn muốn làm rỗng tầng, hãy thêm dòng sau:
        // Init(sTang[i]);
    }
}
//in ra màn hình bằng mảng 
// xoa phong sau do tra ve phong day
PhongKhachSan xoaPhong(stack &s, PhongKhachSan phong) {
    stack phongKhongXoa; // Khai báo stack tạm
    Init(phongKhongXoa);
    PhongKhachSan traVe; // Phòng có tên trả về
    if (isEmpty(s)) { // Kiểm tra
        cout << "Khong co phong!" << endl;
        return traVe;
    }

    Node *temp = NULL;

    while (!isEmpty(s)) { // Duyệt
        if (s.top->dataKs.id == phong.id) { // So sánh
            traVe = Pop(s); // Trả về phòng cần xóa
            if (temp != NULL) { // Duyệt node temp
                temp->next = s.top->next;
            }
        } else {
            temp = s.top;
            Push(phongKhongXoa, Pop(s));
        }
    }
    // Nếu như vậy mình đã làm thay đổi stack rồi
    while (!isEmpty(phongKhongXoa)) {
        Push(s, Pop(phongKhongXoa));
    }
    return traVe;
}
// Kiểm tra số tầng đã nhập trước đó 
int kiemTraSoTangDaNhapTruocDo(int tang){
	if(tang == 0){
		cout<<"Ban chua nhap phong nao !\nBay gio hay nhap so tang :";
	}
	else{	
		cout<<"\nHay nhap tiep ke tu so tang[ "<<tang<<" ]";
	}
	return tang;
}
void NhapThongTinTang(stack s[],int &soTang,int &soPhong){ // thêm phong , không reset lại các phong khác 
	int i = 0;
	int demSoPhong = 0;
	int dungLai;
	do{
		cout<<"Nhap thong tin tang thu "<<i+1 <<" :"<<endl;
		cout<<"\nNhap so phong ";
//		int soPhong;
		cin>>soPhong;
		Init(s[i]);
		PhongKhachSan phong;
		NhapPhong(s[i]); // tối đa 2 phòng 1 tầng cho dễ nhập 
		cout<<"\nNhap -1 de dung lai , Nhap tiep hay bam mot so bat ki :";
		cin>>dungLai;
		i++;
		soTang++;
		demSoPhong = demSoPhong + soPhong;
	}while(dungLai != -1);
	soPhong = demSoPhong;
}
void inManHinhBangStackArrray(stack s[],int tang) {
//	stack temp = s; 
	for(int i = 0 ;i<tang ;i++) {
//		Init(s[i]);
		stack temp = s[i] ;
//		cout<<tang;
		cout<<"\nTang thu "<<i+1<<endl;
		while(temp.top != NULL) {
			PhongKhachSan KS = temp.top->dataKs;
			cout<<KS.id<<"\t\t"<<KS.name<<"\t\t"<<KS.giaThue<<endl;
			temp.top = temp.top->next;
//			cout<<endl;
	//		Push(s,KS);
		}
	}
}
// hien thi phong
void printFile(stack &s) {
    stack temp = s;
    while (!isEmpty(temp)) {
        PhongKhachSan KS = Pop(temp);
        cout << KS.id << "\t" << KS.name << "\t" << KS.giaThue << endl;
    }
}

void Push2(stack &s,PhongKhachSan KS){
	Node *p = new Node;
	p = MakeNode(s,KS);
//	p->next = s.top;
	s.top = p;
}
//void docTep(stack s2[], int &tang) {
//    ifstream f1;
//    f1.open("QuanLyPhong.txt");
//    if (!f1) {
//        cout << "Loi doc file!" << endl;
//        return;
//    } else {
//        int soPhong;
//        f1 >> tang;
//        for (int i = 0; i < tang; i++) {
//            f1 >> soPhong;
//            if (soPhong <= 0) {
//                cout << "Loi doc file! - Khong the doc gia tri thu 1 cua tang " << i + 1 << endl;
//                continue;
//            }
//            for (int j = 0; j < soPhong; j++) {
//                PhongKhachSan KS;
//                f1 >> KS.id >> KS.name >> KS.giaThue;
//                Push2(s2[i], KS);
//            }
//            cout << "So tang thu: " << i + 1 << endl;
//            printFile(s2[i]);
//        }
//        cout << "\nDoc thanh cong" << endl;
//        f1.close();
//    }
//}
//doc thong tin tu tep len man hinh terminal 
void docTep(stack s[], int &tang) {
    ifstream f1;
    f1.open("QuanLyPhong.txt");
    if (!f1) {
        cout << "Loi mo tep !" ;
        return;
    }
    int soPhong;
    f1 >> tang;
    f1>>soPhong;
    for (int i = 0; i < tang; i++) {
//        int soPhong;
//        f1 >> soPhong;

        cout << "So tang thu :" << i + 1 << endl;

//        Init(s[i]);
		cout<<"So phong :"<<soPhong<<endl;
        for (int j = 0; j < soPhong; j++) {
            PhongKhachSan KS;
            f1 >> KS.id >> KS.name >> KS.giaThue;
            KS = Pop(s[i]);
            Push(s[i], KS);
        }
        printFile(s[i]);
    }
    cout << "\nDoc thanh cong\n";
    f1.close();
}
//Ghi tệp
//ghi thong tin vao tep 
void ghiTep(stack s[],int tang,int soPhong) {
	ofstream f1;
//	int soPhong = 4;
    f1.open("QuanLyPhong.txt");
    if (!f1) {
        cout << "Loi mo tep !" ;
        return;
    }
    string str = "So tung thu :";
	f1<<tang<<endl;
	f1<<soPhong<<endl;
	for(int i = 0;i<tang;i++){
		f1<<str<<i+1<<endl;
//		Init(s[i]);
		stack temp = s[i];
		f1<<soPhong;
		while(!isEmpty(temp)) {
			PhongKhachSan KS;
			KS = Pop(temp);
			f1 << KS.id << "\t" << KS.name << "\t" << KS.giaThue << endl;
		}
	}
	cout<<"\nGhi thanh cong\n"; 
	f1.close()   ;
}
// xoa PHòng button(đáy)
PhongKhachSan delButton(stack &s){
	if(isEmpty(s)){
		cout<<"Khong co phong ";
	}
	while(s.top->next!=NULL){
		s.top = s.top->next;
	}
	return Pop(s);
}
// Hien phong trong khoảng 
void HienPhongTrongKhoangAdenB(stack s,double giaPhongBatDau,double giaPhongKetThuc){
	stack temp;
	stack hienTai = s;
	while(hienTai.top!=NULL){
		PhongKhachSan giaPhong = hienTai.top->dataKs;
		if(giaPhong.giaThue>giaPhongBatDau&&giaPhong.giaThue<giaPhongKetThuc){
			Push2(temp,giaPhong);
		}
		hienTai.top = hienTai.top->next;
	}
	cout<<"Hien danh sach gia phong trong khoang["<<giaPhongBatDau<<" - "<<giaPhongKetThuc<<" ]";
	inManHinhToNode(temp);
}
int main(){
	int choice,doiTuong;
	// Nếu là quản lý thì
	PhongKhachSan phong1 = {1, "Phong 101", 1100};
    PhongKhachSan phong2 = {2, "Phong 102", 150};
    PhongKhachSan phong3 = {3, "Phong 103", 3900};
    PhongKhachSan phong4 = {4, "Phong 104", 1300};
    PhongKhachSan phong5 = {5, "Phong 105", 40.0};
 	PhongKhachSan phong6 = {6, "Phong 106", 4500};
    PhongKhachSan phong7 = {7, "Phong 107", 28.0};
	stack sTang[10];
	stack merge;
//	Init(merge);
	int tang=0;
	int soTang = 0;
	int soPhong = 0;
	int demSoPhong = 0;
	while(true){
		cout<<"\nLua chon doi tuong su dung\n1. Chuc nang quan ly \n2. Chuc nang khach su dung phong\n";
		cin>>doiTuong;
		if(doiTuong==1) {
			do{
				cout << "=== Quan Ly Dat Phong Khach San ===" << endl;
		        cout << "1. Nhap thong tin phong :" << endl;
		        cout << "2. Kiem tra co bao nhieu phong da dat phong" << endl;
		        cout << "3. Xoa phong khoi danh sach" << endl;
		        cout << "4. Tim kiem phong tra ve thong tin cua phong !"<<endl;
		        cout << "5. Xu ly file " << endl;
		        cout << "6. Hien thi danh sach ra man hinh" << endl;
		        cout << "7. Xoa phong cuoi cung" << endl;
		        cout << "8. Phan phong sang stack giam gia uu dai !"<<endl;
		        cout << "9.  Sap xep gia thue bang selection sort " << endl;
		        cout << "10. Sap xep gia thue insertion sort " << endl;
		        cout << "11. Sap xep gia thue merge sort" << endl;
		        cout << "12. sap xep gia thu quick sort !"<<endl;
		        cout<<"13. Tu dong tao du lieu moi tang co so phong la 4   :"<<endl;
		        cout<<"14. Xoa tat ca cac phong (khoi tao lai danh sach phong! ):"<<endl;
		        cout<<"15. Nhap so tang muon sua doi "<<endl;
		        cout<<"17. Thoat doi tuong quan ly \n";
		        cout<<"21.Nhap so tang va phong de doc file nhanh :\n";
		        cout << "4. Thoat" << endl;
		        cout << "Chon chuc nang: ";
		        int choice;
		        cin>>choice;
		        if(choice == 1){
		//			int kiemTraSoTang = kiemTraSoTangDaNhapTruocDo(tang);
		//			cout<<"\nNhap so luong tang :";
		//			cin>>tang;
		//			stack sTang[100];
					// kiểu tra số tâng đã nhập trước đó 
					NhapThongTinTang(sTang,soTang,soPhong);
					demSoPhong = demSoPhong + soPhong; // luu vao de dem so phong
					system("pause");
				}
				// test lấy thông tin số tầng
				if(choice==20){
					cout<<"So tang = "<<soTang<<endl;
					cout<<"Dem so phong :"<<demSoPhong<<endl;
				}
				if(choice==21){
					cout<<"Nhap so tang :";
					cin>>soTang;
				}
				else if(choice==2){
					cout<<"\nKiem tra co bao nhieu phong da dat !\n";
//					gopTatCaStack(sTang,merge,tang);
					int demSoPhong=len(merge);
					cout<<"\nSo phong co la :"<<demSoPhong<<endl;
					system("pause");
				}
				else if(choice==3){
					PhongKhachSan xoaPhongChild;
		            cout << endl << "Xoa phong \nNhap id phong :";
		            cin >> xoaPhongChild.id;
		            // Gộp tất cả các stack tầng vào stack merge trước khi thực hiện xóa
//		            Init(merge);
		            gopTatCaStack(sTang, merge, tang);
		            // Gọi hàm xoaPhong
		            xoaPhongChild = xoaPhong(merge, xoaPhongChild);
		             // In thông tin phòng đã xóa
		    		cout << "Phong da xoa: " << xoaPhongChild.id << "\t" << xoaPhongChild.name << "\t" << xoaPhongChild.giaThue << endl;
		    		cout<<endl<<"Hien danh sach sau khi xoa :\n";
		    		printStack(merge);
		    		system("pause");  
				}
				else if(choice==5){
					int dong;
					cout<<"\n1. Ghi thong tin vao file .\n2. Doc thong tin tu file ra\n";
					cin>>dong;
					if(dong==1){
						cout<<"\nGhi thong tin vao file :\n";
						cout<<"So phong hien co :"<<soPhong;
						ghiTep(sTang,soTang,soPhong);
					}
					if(dong==2){
						cout<<"\nDoc thong tin tu file :\n";
						docTep(sTang,soTang);
					}
				}
				else if(choice==6){
					int dong;
					cout<<"1.in ra man hinh su dung ket hop stack voi array\n2. In ra man hinh bang merge \n";
					cin>>dong;
					cout<<"\nHien danh sach\n";
					if(dong==1){
						inManHinhBangStackArrray(sTang,soTang);
					}
					if(dong==2){
						Init(merge);
						gopTatCaStack(sTang,merge,soTang);
		//				insertLastThemPrev(merge,phong2);
						inManHinhToNode(merge);
		//				cout<<"\nNode day la:"<<nodeLastList(merge)->dataKs.id;
					}
					system("pause");
				}
				else if(choice==7){
					gopTatCaStack(sTang,merge,tang);
					PhongKhachSan xoaPhongCuoi = Pop(merge);
					cout<<"Phong xoa \t"<<xoaPhongCuoi.id<<"\t"<<xoaPhongCuoi.name;
					system("pause");
				}
				else if(choice == 13){
					cout<<"\nNhap so tang :";
					cin>>tang;
				   	for(int i = 0 ;i<tang;i++){
						Init(sTang[i]); 
						Push(sTang[i],phong1);
						Push(sTang[i],phong2);
						Push(sTang[i],phong3);
						Push(sTang[i],phong4);
					}
					system("pause");
				}
				else if(choice == 14){
					Init(merge);
					system("pause");
				}
				else if(choice == 17){
					cout<<"Thoat !";
					break;
				}
			}while(true);
		}
		else if(doiTuong == 2){
			do{
				cout << "=== Danh cho khach hang ===" << endl;
		        cout << "1. Xem thong tin phong:" << endl;
		        cout << "2. Tim phong voi muc gia tu( A den B ):" << endl;
		        cout << "3. Dat phong " << endl;
		        cout << "4. Tim kiem ten phong gia phu hop !"<<endl;
		        cout<<"5. Xem danh sach phong muc gia tu re den dat(sap xep gia phong ):"<<endl;
		        cout<<"6. Thoat doi tuong khach hang \n";
		        int luaChon;
		        cin>>luaChon;
		        if(luaChon == 1){
		        	inManHinhBangStackArrray(sTang,soTang) ;
		        	system("pause");
				}
				else if(luaChon == 2){
					double giaBatDau,giaKetThuc;
					cout<<"Nhap gia bat dau :";cin>>giaBatDau;
					cout<<"Nhap gia ket thuc :";cin>>giaKetThuc;
					HienPhongTrongKhoangAdenB(merge,giaBatDau,giaKetThuc);
				}
				else if(luaChon == 6){
					break;
				}
				
			}while(true);
		}
	}
}