//sourctree 
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
//Tao node 
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
//	p->next = s.top;
	s.top = p;
}
// Thêm vào cuối
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
void NhapPhong(stack& s) {
    int soPhong = 2; // Số lượng phòng tối đa 2 phòng cho mỗi tầng
    for (int i = 0; i < soPhong; i++) {
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
/*Ý tưởng của hàm này như sau :
Nó sẽ thực hiện việc nhập cho từng stack nếu stack có số tầng thứ i có id nhập vào trùng nhau thì nó sẽ bảo người dùng nhập lại với ô stack đó  */
void NhapThongTinTang(stack s[] , int tang){
	for(int i = 0;i<tang;i++){
		cout<<"Nhap thong tin tang thu "<<i+1 <<" :"<<endl;
		Init(s[i]);
		PhongKhachSan phong;
		NhapPhong(s[i]); // tối đa 2 phòng 1 tầng cho dễ nhập 
	}
}
//Pop
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
PhongKhachSan delFirst(stack &s){
	if(isEmpty(s)){
		cout<<"Khong co phong ";
	}
	while(s.top->next!=NULL){
		s.top = s.top->next;
	}
		return Pop(s);
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
int TimKiem(stack &s , PhongKhachSan phong) {
	int ketQua = 0;
	stack temp = s; 
	if(isEmpty(temp)) {
		ketQua = 0; 
	}
	else{
		PhongKhachSan kiemTra; 
		while(!isEmpty(temp)) {
			kiemTra = Pop(temp) ;
			if(kiemTra.id==phong.id) {
				ketQua = 1;
			}
		}
	}
	return ketQua; 
}
//tim kiem tra ve ten phong 
PhongKhachSan TimKiemTraVePhong(stack &s, PhongKhachSan phong) {
	stack temp = s;
	PhongKhachSan ketQua = {0, "", 0};
	if(isEmpty(temp)) {
		cout<<"Khong co phong!" ;
		PhongKhachSan phongRong = ketQua;
		return phongRong;
	}
	else{
		PhongKhachSan kiemTraPhong;
		while(!isEmpty(temp) ) {
			kiemTraPhong = Pop(temp);
			if(kiemTraPhong.id==phong.id) {
				ketQua = kiemTraPhong; 
			}
		}
	}
	return ketQua;
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
// 											Sử dụng vector , in ra mà merge code 
//gop tat ca cac stack tang vao stack khachSan   
void gopTatCaStack(stack sTang[],stack &merge,int tang) {
	for(int i = 0 ;i < tang ;i++){
		while(!isEmpty(sTang[i])){
			PhongKhachSan mergePhong = Pop(sTang[i]);
			Push(merge,mergePhong);
		}
	}
}
// xoa phong sau do tra ve phong day
//PhongKhachSan xoaPhong(stack &s,PhongKhachSan phong){
//	stack bienTam = s;
//	PhongKhachSan traVe;
//	// nêu cần xóa ở vị trí đỉnh
//	if(phong.id==s.top->dataKs.id){
//		traVe = Pop(s);
//	}
//	else{
//		if(isEmpty(s)){
//			cout<<"Khong co phong !";
//		}
//		PhongKhachSan KS = s.top->dataKs;
//		Node *temp;
//		while(s.top->next!=NULL){
//			if(phong.giaThue!=s.top->dataKs.giaThue){
//				temp = s.top;
//				traVe = s.top->dataKs;
//				break;	
//			}
//			s.top = s.top->next;
//		}
//		 
//		temp->next = s.top->next;
//			
//	}
//	return traVe;
//}

PhongKhachSan xoaPhong(stack &s, PhongKhachSan phong) {
    stack bienTam;
    Init(bienTam);
    PhongKhachSan traVe;

    if (isEmpty(s)) {
        cout << "Khong co phong!" << endl;
        return traVe;
    }

    Node *temp = NULL;

    while (!isEmpty(s)) {
        if (s.top->dataKs.giaThue == phong.giaThue) {
            traVe = Pop(s);
            if (temp != NULL) {
                temp->next = s.top->next;
            }
            break;
        } else {
            temp = s.top;
            Push(bienTam, Pop(s));
        }
    }

    while (!isEmpty(bienTam)) {
        Push(s, Pop(bienTam));
    }

    return traVe;
}

// Sắp xếp selection sort 
// Tim node co phong nho nhat  , tim theo gia phong 
PhongKhachSan findMinPhong(stack &s){
	PhongKhachSan phongMin = s.top->dataKs;
	stack temp;
	Init(temp);
	while(!isEmpty(s)){
		PhongKhachSan KS = Pop(s);
		if(KS.giaThue<phongMin.giaThue){
			phongMin = KS;
			// mục đích push là để trả lại stack cũ 
			Push(temp,phongMin);
		}
		else{
			Push(temp,phongMin) ;
		}
	}
	while(!isEmpty(temp)){
		PhongKhachSan phong = Pop(temp);
		Push(s,phong);
	}
	return phongMin;
}
// tim min phong su dung node de duyet 
PhongKhachSan findMin(stack &s) {
    if (isEmpty(s)) {
        cout << "Rong !";
    }
    Node *current = s.top;
    PhongKhachSan min = current->dataKs;
    while (current != NULL) {
        PhongKhachSan phong = current->dataKs;
        if (phong.giaThue < min.giaThue) {
            min = phong;
        }
        current = current->next;
    }
    return min;
}

void swapGiaThue(Node *node1, Node *node2) {
    PhongKhachSan temp = node1->dataKs;
    node1->dataKs = node2->dataKs;
    node2->dataKs = temp;
}
// xay dung tim min tra ve node
Node *findMinNode(stack &s){
	if(isEmpty(s)){
		cout<<"rong!";
	}
	Node *current = s.top;
	Node *min = current;
	while(current!=NULL){
		Node *phong = current;
		if(phong->dataKs.giaThue < min->dataKs.giaThue){
			min = phong;	
		}
		current = current->next;
	}
	return min;
}
void swapNodes(stack& s, Node* node1, Node* node2) {
    // Check if the nodes are already adjacent (i.e., node1->next is node2)
    if (node1->next == node2) {
        // Swap the nodes
        Node* temp = node2->next;
        node2->next = node1;
        node1->next = temp;

        // Update the top of the stack if needed
        if (s.top == node1) {
            s.top = node2;
        } else if (s.top == node2) {
            s.top = node1;
        }
    } else if (node2->next == node1) {
        // Swap the nodes
        Node* temp = node1->next;
        node1->next = node2;
        node2->next = temp;

        // Update the top of the stack if needed
        if (s.top == node1) {
            s.top = node2;
        } else if (s.top == node2) {
            s.top = node1;
        }
    } else {
        // Nodes are not adjacent, so we need to traverse the list and update the links
        Node* prev1 = nullptr;
        Node* prev2 = nullptr;
        Node* current = s.top;

        // Find the previous nodes of node1 and node2
        while (current != nullptr && current != node1) {
            prev1 = current;
            current = current->next;
        }

        current = s.top; // Reset the current pointer

        while (current != nullptr && current != node2) {
            prev2 = current;
            current = current->next;
        }

        if (prev1 != nullptr) {
            prev1->next = node2;
        } else {
            s.top = node2;
        }

        if (prev2 != nullptr) {
            prev2->next = node1;
        } else {
            s.top = node1;
        }

        Node* temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
    }
}

void selectionSortPhongGiaThue(stack &s) {
    stack sorted; // Stack để lưu trữ các phần tử đã được sắp xếp
    Init(sorted);

    while (s.top != NULL) {
        Node *phongMin = new Node;
        stack Dinh = s;
        phongMin = findMinNode(Dinh);
        if (s.top->dataKs.giaThue != phongMin->dataKs.giaThue) {
            Node *temp = Dinh.top;
            swapNodes(s,temp, phongMin);
//            Push(sorted,temp->dataKs);
        }
//        lÚC NÀY Nó đã đổi chỗ vị node thứ 
        // Đẩy phần tử nhỏ nhất vào stack đã sắp xếp
        Push(sorted,phongMin->dataKs);
//        // Xóa phần tử nhỏ nhất khỏi stack gốc
//        Pop(s);
        s.top = s.top->next;
    }
//
//    // Đưa các phần tử từ stack đã sắp xếp về stack gốc
//    while (!isEmpty(sorted)) {
//        Node *temp = sorted.top;
//        Pop(sorted);
//        Push(s, temp->dataKs);
//        sorted.top = sorted.top->next;
//    }
	s = sorted;
}
// Thuật toán quick sort 
void QuickSort(stack &s) {
    if (isEmpty(s)) {
        return;
    }
    stack less, equal, greater;
    Init(less);
    Init(equal);
    Init(greater);

    PhongKhachSan pivot = Pop(s);
    Push(equal, pivot);

    while (!isEmpty(s)) {
        PhongKhachSan KS = Pop(s);
        if (KS.giaThue < pivot.giaThue) {
            Push(less, KS);
        } else if (KS.giaThue == pivot.giaThue) {
            Push(equal, KS);
        } else {
            Push(greater, KS);
        }
    }

    QuickSort(less);
    QuickSort(greater);

    while (!isEmpty(less)) {
        Push(s, Pop(less));
    }
    while (!isEmpty(equal)) {
        Push(s, Pop(equal));
    }
    while (!isEmpty(greater)) {
        Push(s, Pop(greater));
    }
}

void insertionSort(stack& s) {
    stack sortedStack;
    Init(sortedStack);
    while (!isEmpty(s)) {
        PhongKhachSan minPhong = Pop(s);
        stack tempStack;
        Init(tempStack);
        while (!isEmpty(s)) {
            PhongKhachSan KS = Pop(s);
            if (KS.giaThue < minPhong.giaThue) {
                Push(tempStack, minPhong);
                minPhong = KS;
            } else {
                Push(tempStack, KS);
            }
        }

        Push(sortedStack, minPhong);

        while (!isEmpty(tempStack)) {
            Push(s, Pop(tempStack));
        }
    }

    while (!isEmpty(sortedStack)) {
        Push(s, Pop(sortedStack));
    }
}

void Merge(stack &s, stack &left, stack &right) {
    while (!isEmpty(left) && !isEmpty(right)) {
        if (left.top->dataKs.giaThue <= right.top->dataKs.giaThue) {
            Push(s, Pop(left));
        } else {
            Push(s, Pop(right));
        }
    }

    while (!isEmpty(left)) {
        Push(s, Pop(left));
    }

    while (!isEmpty(right)) {
        Push(s, Pop(right));
    }
}

void MergeSort(stack &s) {
    if (len(s) <= 1) {
        return;
    }

    stack left, right;
    Init(left);
    Init(right);

    int middle = len(s) / 2;
    int i = 0;

    while (i < middle) {
        Push(left, Pop(s));
        i++;
    }

    while (!isEmpty(s)) {
        Push(right, Pop(s));
    }

    MergeSort(left);
    MergeSort(right);

    Merge(s, left, right);
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
    // T? ð?ng thêm m?u 5 ph?ng vào danh sách ð?t
//    Push(s, phong1);
//    Push(s, phong2);
//    Push(s, phong3);
//    Push(s, phong4);
//    Push(s, phong5);
//    Push(s, phong6);
//    Push(s, phong7);
//    print(s);
//    PhongKhachSan phong;
    stack sTang[5];
    int tang;
    cout<<endl<<"Nhap so tang :";
    cin>>tang;
//     Xây dưng số tầng 
   	for(int i = 0 ;i<tang;i++){
		Init(sTang[i]); 
		Push(sTang[i],phong1);
		Push(sTang[i],phong2);
		Push(sTang[i],phong3);
		Push(sTang[i],phong4);
	} 
    
//Nhập thông tin số tầng
//NhapThongTinTang(sTang,tang);
    
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

//	 Gộp stack 
	stack merge;
	Init(merge);
	gopTatCaStack(sTang,merge,tang);
	print(merge);
	
	// xoa phong sau do tra ve phong
//	PhongKhachSan xoaPhongKS = xoaPhong(merge,phong1);
//	cout<<"\n Phong vua xoa :"<<xoaPhongKS.name<<endl;
	print(merge);
	//Tìm giá phòng nhỏ nhất
	PhongKhachSan giaThueRe = findMin(merge);
	cout<<"Gia phong nho nhat id :"<<giaThueRe.id<<"\t"<<giaThueRe.giaThue;
// Sắp xếp theo giá thuê phongf
	cout<<"\nSap xep \n";
	Node *node1 = new Node;
	Node *node2 = new Node;
	node1->dataKs = phong1;
	node2->dataKs = phong3;
//	swapGiaThue(node1,node2);
//	insertionSort(merge);
	selectionSortPhongGiaThue(merge);
//	QuickSort(merge);
//	Merge
	print(merge);
//	timKiem tra ve so nguyenn  
	PhongKhachSan timKiemPhong; 
	cout<<"\nNhap id phong muon tim kiem :";
	cin>>timKiemPhong.id;
	int ketQua = TimKiem(merge,timKiemPhong)  ;
	if(ketQua==-1||ketQua == 0){
		cout<<"\nKhong tim thay phong\n" ;
	}
	else{
		cout<<"Tim thay phong co id :"<<timKiemPhong.id;
	}
	// tim kiem tra ve kieu struct 
	PhongKhachSan kiemTraPhongStruct = TimKiemTraVePhong(merge,timKiemPhong);
	if(kiemTraPhongStruct.id != 0){
		cout<<"\nTim thay phong co id :"<<kiemTraPhongStruct.id<<"\t"<<kiemTraPhongStruct.name<<"\t"<<kiemTraPhongStruct.giaThue; 
	}
	else{
		cout<<"\nKhong tim thay phong\n" ;	
	}
//	cout<<"\nGhi Tep !\n" ;
//	ghiTep(s);

	//xay dung so tang cho khach san , nhap thu cong 
//	stack sTang[10] ;
//	
//	int tang;
//	cout<<"\nNhap so tang khach san va moi tang toi da la 4 phong :"; 
//	cin>>tang;  
//	DienThongTinPhong(sTang,tang);
//	cout<<"\nIn thong tin \nID \t\t Ten phong \t\t Gia thue\n";
//	print(sTang,tang);
//	
//	
	
	
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


