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
Node *nodeLastList(stack s) {
    if (isEmpty(s)) {
        return NULL;  
    }
    Node *temp = s.top;
    while (temp->next != NULL) {
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
        cout << "Nhap thong tin cho phong " << (i) << endl;
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
//            if (temp != NULL) { // Duyệt node temp
//                temp->next = s.top->next;
//            
        } else {
//            temp = s.top;
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
	int i = soTang;
	int demSoPhong = 0;
	int dungLai;
	do{
		cout<<"Nhap thong tin tang thu "<<i <<" :"<<endl;
//		Init(s[i]);
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
	for(int i = 0 ;i<tang ;i++) {
		stack temp = s[i] ;
		cout<<"\nTang thu "<<i+1<<endl;
		while(temp.top != NULL) {
			PhongKhachSan KS = temp.top->dataKs;
			cout<<KS.id<<"\t\t"<<KS.name<<"\t\t"<<KS.giaThue<<endl;
			temp.top = temp.top->next;
//			cout<<endl; 
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
void docTep(stack s[], int& tang) {
    ifstream f1;
    f1.open("DuLieuMau.txt");
    if (!f1) {
        cout << "Loi mo tep !" ;
        return;
    }
    int soPhong = 2; // Mặc định số phòng cho mỗi tầng là 2

    f1 >> tang; // Đọc số tầng
    
    // Duyệt qua từng tầng
    for (int i = 0; i < tang; i++) {
        Init(s[i]); // Khởi tạo stack cho tầng
		f1>>soPhong;
        // Duyệt qua từng phòng trong tầng
        for (int j = 0; j < soPhong; j++) {
            PhongKhachSan KS;
            char comma; // Dùng để đọc dấu ',' phân cách giữa các trường
            f1 >> KS.id >> comma >> ws;
            getline(f1, KS.name, ',');
            f1 >> KS.giaThue;

            // Thêm phòng vào stack của tầng
            Push(s[i], KS);
        }
    }

    cout << "\nDoc thanh cong\n";
    f1.close();
}
//Ghi tệp
//ghi thong tin vao tep 
void ghiTep(stack s[], int tang) {
    ofstream f1;
    f1.open("GhiFile.txt");
    if (!f1) {
        cout << "Loi mo tep !" ;
        return;
    }

    f1 << tang << endl; // Ghi số tầng vào tệp

    // Duyệt qua từng tầng
    for (int i = 0; i < tang; i++) {
        stack temp = s[i];

        // Ghi số phòng của mỗi tầng vào tệp
        f1 << "2" << endl;

        // Ghi thông tin từng phòng trong tầng vào tệp
        while (!isEmpty(temp)) {
            PhongKhachSan KS = Pop(temp);
            f1 << KS.id << "," << KS.name << "," << KS.giaThue << endl;
        }
    }

    cout << "\nGhi thanh cong\n"; 
    f1.close();
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
//Tổng tiền 
double tongGiaThue(stack s){
	double tong = 0.0;
	if(isEmpty(s)){
		cout<<"stack rong!";
	}
	else{
		while(!isEmpty(s)){
			PhongKhachSan phong = Pop(s);
			tong = tong + phong.giaThue;
		}
	}
	return tong;
}
/////////////////////////////////Sắp xếp ////////////////////////////////


// insertion sort
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
// Doi cho phong 
void swapNodes(stack& s, Node* node1, Node* node2) {
    // Nếu node1->next == node2
    if (node1->next == node2) {
        Node* temp = node2->next;
        node2->next = node1;
        node1->next = temp;
        s.top = node2;
        node2 = node1;
    } 
    //Nếu node2->next == node1 ( tức là 2 node kề nhau ) 
	else if (node2->next == node1) {
        // Swap the nodes
        Node* temp = node1->next;
        node1->next = node2;
        node2->next = temp;
        s.top = node1;
        node1 = node2;
    } 
	else {
		// không kề nhau 
		// Ý tưởng là tạo 2 con trỏ trước node1 và node 2 để lấy địa chỉ của chúng , 
		//làm như vậy sẽ không bị mất liên kết địa chỉ giữa các node với nhau ví dụ node1 : 0x87 node2:0x76 , 
		//prev1->next = 0x87 và prev2->next = 0x87 , sau đó đổi node là đổi node quản lý 
        Node* truoc1 = NULL;
        Node* truoc2 = NULL;
        Node* current = s.top; // current duyệt đến node đấy (node1 or node2)
        // tìm node trước node1
        while (current != NULL && current != node1) {
            truoc1 = current; //  gan node truoc do cua node1
            current = current->next;
        }
// 		Test duyệt node1 ở đỉnh thi current == node1 , vạy preve1 = NULL
//        truoc1 -> NULL
        current = s.top; // reset lại để duyệt node2 
        while (current != NULL && current != node2) { 
            truoc2 = current;
            current = current->next;
        }
        //truoc1 trỏ lấy node 2
        if (truoc1 != NULL) { 
            truoc1->next = node2;
        } 
		else {
            s.top = node2;
        }
		//truoc2 tro lấy node1
        if (truoc2 != NULL) {
            truoc2->next = node1;
        } else {
            s.top = node1;
        }
        Node* temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
    }
}
// Hàm chính selection sort
void selectionSortPhongGiaThue(stack &s) {
    stack sorted; // Stack để lưu trữ các phần tử đã được sắp xếp
    Init(sorted);```````````````````````````
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
//    // Đưa các phần tử từ stack đã sắp xếp về stack gốc
//    while (!isEmpty(sorted)) {
//        Node *temp = sorted.top;
//        Pop(sorted);
//        Push(s, temp->dataKs);
//        sorted.top = sorted.top->next;
//    }
	s = sorted;
}
//Thử pop cho quick sort :
PhongKhachSan PopQ(stack& s) {
    if (isEmpty(s)) {
        cout << "Khong co phong !";
        // Trả về một giá trị phong rỗng để xử lý tình huống lỗi
        return {0, "", 0.0};
    }
    PhongKhachSan KS = s.top->dataKs;
    Node* temp = s.top;
    s.top = s.top->next;
    if (s.top != NULL) {
        s.top->prev = NULL;
    }
    delete temp;
    return KS;
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

    PhongKhachSan pivot = PopQ(s);
    Push(equal, pivot);
    while (!isEmpty(s)) {
        PhongKhachSan KS = PopQ(s);
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
        Push(s, PopQ(less));
    }
    while (!isEmpty(equal)) {
        Push(s, PopQ(equal));
    }
    while (!isEmpty(greater)) {
        Push(s, PopQ(greater));
    }
}
//Tìm kiếm trả về phòng
PhongKhachSan TimKiemPhongTheoID(stack s, int id) {
    stack temp;
    Init(temp);
    PhongKhachSan ketQua = {0, "", 0.0};

    while (!isEmpty(s)) {
        PhongKhachSan KS = Pop(s);
        if (KS.id == id) {
            ketQua = KS;
            break;
        } else {
            Push(temp, KS);
        }
    }

    // Khôi phục lại stack gốc
    while (!isEmpty(temp)) {
        Push(s, Pop(temp));
    }

    return ketQua;
}
//Gia max nhat
Node *phongGiaThuMax(stack s){
	Node *Max = s.top;
	if(isEmpty(s)){
		cout<<"stack rong!";
	}
	while(!isEmpty(s)){
		Node *soSanh;
		PhongKhachSan phong = Pop(s);
		if(Max->dataKs.giaThue < phong.giaThue)
			Max->dataKs = phong;
	}
	return Max;
}
//Thuật toán buble 
//b1 biến bool swapped 
//b2 Vòng lặp để duyệt hết các node 

//void bubble_sort(stack &s){
//	stack temp = s;
//	bool swapped;
//	while(temp.top!=NULL){
//		Node *nodeCuoi = nodeLastList(temp);
//		swapped = false;
//		Node *duyet;
//		duyet = nodeCuoi->prev;
//		while(duyet->next!=NULL){
//			Node *hienTai = duyet;
//			Node *sau = duyet->next;
//			if(hienTai->dataKs.giaThue>sau->dataKs.giaThue){
//				swapNodes(temp,hienTai,sau);
//				swapped=true;
//			}
//			duyet = duyet->next;
//		}
//		if(swapped ==false){
//			break;
//		}
//		temp.top = temp.top->next;
//	}
//	s = temp;
//}

void bubble_sort(stack &s) {
    bool swapped;
    while (s.top != NULL) {
        Node *nodeCuoi = nodeLastList(s);
        swapped = false;
        Node *duyet;
        duyet = nodeCuoi->prev;
        while (duyet->next != NULL) {
            Node *hienTai = duyet;
            Node *sau = duyet->next;
            if (hienTai->dataKs.giaThue > sau->dataKs.giaThue) {
                swapNodes(s, hienTai, sau);
                swapped = true;
            }
            duyet = duyet->next;
        }
        if (!swapped) {
            break;
        }
        s.top = s.top->next;
    }
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
//    stack datPhong[10];
	stack sTang[10];
	stack datPhong;
	Init(datPhong);
	int idatPhong;
	idatPhong = 0;
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
		        cout << "9. Sap xep gia thue bang selection sort " << endl;
		        cout << "10. Sap xep gia thue insertion sort " << endl;
		        cout << "11. Sap xep gia thue merge sort" << endl;
		        cout << "12. sap xep gia thu quick sort !"<<endl;
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
//					demSoPhong = demSoPhong + soPhong; // luu vao de dem so phong
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
//					stack mergeLen;
//					Init(mergeLen);
//					gopTatCaStack(sTang,mergeLen,tang);
					int demSoPhong=len(merge);
					if(demSoPhong == 0){
						cout<<"khong co phong ";
					}
					else{
						cout<<"\nSo phong co la :"<<demSoPhong<<endl;
					}
					system("pause");					
				}
				else if(choice==3){
					PhongKhachSan xoaPhongChild;
		            cout << endl << "Xoa phong \nNhap id phong :";
		            cin >> xoaPhongChild.id;
		            // Gộp tất cả các stack tầng vào stack merge trước khi thực hiện xóa
//		            Init(merge);
//		            gopTatCaStack(sTang, merge, tang);
		            // Gọi hàm xoaPhong
		            stack temp = merge;
		        	PhongKhachSan timKiemPhongXoa = TimKiemPhongTheoID(temp,xoaPhongChild.id);
//		            PhongKhachSan phongTimKiem = TimKiemPhongTheoID(temp, idCanTim);
				    if(timKiemPhongXoa.id != 0) {
				        cout << "Thong tin phong: " << timKiemPhongXoa.id << "\t" << timKiemPhongXoa.name << "\t" <<timKiemPhongXoa.giaThue << endl;
				        xoaPhongChild = xoaPhong(merge, xoaPhongChild);
			             // In thông tin phòng đã xóa
			    		cout << "Phong da xoa: " << xoaPhongChild.id << "\t" << xoaPhongChild.name << "\t" << xoaPhongChild.giaThue << endl;
			    		cout<<endl<<"Hien danh sach sau khi xoa :\n";
			    		printStack(merge);
			    		system("pause"); 
				        
				    } else {
				        cout << "Khong tim thay phong!" << endl;
				    }
		            
		             
				}
//			 Trong hàm main, tại choice == 4
				else if (choice == 4) {
								     // Gọi hàm tìm kiếm phòng theo ID
					stack temp = merge;
				    int idCanTim;
				    cout << "Nhap ID phong can tim: ";
				    cin >> idCanTim;
				
				    PhongKhachSan phongTimKiem = TimKiemPhongTheoID(temp, idCanTim);
				    if (phongTimKiem.id != 0) {
				        cout << "Thong tin phong: " << phongTimKiem.id << "\t" << phongTimKiem.name << "\t" << phongTimKiem.giaThue << endl;
				    } else {
				        cout << "Khong tim thay phong!" << endl;
				    }
				    system("pause");
				}
				else if(choice==5){
					int dong;
					cout<<"\n1. Ghi thong tin vao file .\n2. Doc thong tin tu file ra\n";
					cin>>dong;
					if(dong==1){
						cout<<"\nGhi thong tin vao file :\n";
						cout<<"So phong hien co :"<<soPhong;
						ghiTep(sTang,soTang);
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
				else if(choice == 8){
			        cout << "\nPhan phong sang stack giam gia uu dai \nNhap muc gia :";
			        double giaGiam =16.0;
			        stack giamGia ;
					stack temp = merge;
			        Init(giamGia);
			        if(isEmpty(temp)){
			        	cout<<"Rong!!!";
					}
					else{
						while(!isEmpty(temp)){
							PhongKhachSan phongGiamGia = Pop(temp);
							if(phongGiamGia.giaThue < giaGiam){
								Push(giamGia,phongGiamGia);
							}
						}
					}
					cout<<"\nNhung phong giam gia :\n";
		        	QuickSort(giamGia);
		        	printStack(giamGia);
				}
				else if(choice ==9){
					selectionSortPhongGiaThue(merge);
					printStack(merge);
				}
				else if(choice == 10){
					insertionSort(merge);
					printStack(merge);
				}
				else if(choice == 12){
					cout<<"Sap xep quick sort :\n";
					QuickSort(merge);
					if(isEmpty(merge)){
						cout<<"rong!";
					}
					cout<<"\n Node top :"<<merge.top->dataKs.id;
					printStack(merge);
					cout<<"\n Node top :"<<merge.top->dataKs.id;
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
		        cout << "4. Huy phong khong muon dat !"<<endl;
		        cout << "5. Thong tin gia phong !"<<endl;
		        cout<<"6. Xem danh sach phong muc gia tu re den dat(sap xep gia phong ):"<<endl;
		        cout<<"7.Dat phong cuoi cung !\n";
		        cout<<"7. Thoat doi tuong khach hang \n";
		        cout<<":Moi ban nhap :";
		        int luaChon;
		        cin>>luaChon;
		        if(luaChon == 1){
		        	int dong;
		        	cout<<"1.Xem thong tin co cac tang va phong \n2.Xem thong tin tong hop cua stack \nNhap lua chon :";
		        	cin>>dong;
		        	if(dong==1)
		        		inManHinhBangStackArrray(sTang,soTang);
		        	else{
		        		printStack(merge);
					}
		        	system("pause");
				}
				else if(luaChon == 2){
					double giaBatDau = 10.0,giaKetThuc=16.0;
					stack temp = merge;
					stack hienGiaTrongKhoang;
					Init(hienGiaTrongKhoang);
//					cout<<"\n Node top :"<<temp.top->dataKs.id;
//					cout<<"Nhap gia bat dau :";cin>>giaBatDau;
//					cout<<"Nhap gia ket thuc :";cin>>giaKetThuc;
					if(isEmpty(temp)){
						cout<<" rong!";
					}
					
//					HienPhongTrongKhoangAdenB(merge,giaBatDau,giaKetThuc);
					else{
						while(!isEmpty(temp)){
							PhongKhachSan phongHienGiaAb = Pop(temp);
							if(giaBatDau<phongHienGiaAb.giaThue&&phongHienGiaAb.giaThue<giaKetThuc){
								Push(hienGiaTrongKhoang,phongHienGiaAb);
							}
//							printStack(hienGiaTrongKhoang);
						}
					
					}
					while(!isEmpty(hienGiaTrongKhoang)) {
						PhongKhachSan KS = Pop(hienGiaTrongKhoang);
						cout<<KS.id<<"\t"<<KS.name<<"\t"<<KS.giaThue;
						cout<<endl;
//		Push(s,KS);
					}
					
					system("pause");
				}
				else if(luaChon == 3){
					cout<<"Moi quy khach chon phong dat ";
					cout<<"Hay nhap id phong :";
					int id;
					cin>>id;
					stack temp = merge;
					PhongKhachSan phongTimKiem = TimKiemPhongTheoID(temp, id);
				    if (phongTimKiem.id != 0) {
				        cout << "Thong tin phong: " << phongTimKiem.id << "\t" << phongTimKiem.name << "\t" << phongTimKiem.giaThue << endl;
						cout<<"Danh sach dat phong\n";
				        Push(datPhong,phongTimKiem);
						inManHinhToNode(datPhong);
				        
				    } else {
				        cout << "Khong tim thay phong!" << endl;
				    }
				}
				else if(luaChon==4){
					cout<<"Nhap id phong ban muon huy dat phong:";
					int idHuyPhong;
					cin>>idHuyPhong;
					PhongKhachSan huyDatPhong = TimKiemPhongTheoID(datPhong,idHuyPhong);
					if(huyDatPhong.id != 0) {
				        cout << "Thong tin phong: " << huyDatPhong.id << "\t" << huyDatPhong.name << "\t" <<huyDatPhong.giaThue << endl;
				        PhongKhachSan xoaPhongChild = xoaPhong(datPhong, huyDatPhong);
			             // In thông tin phòng đã xóa
			    		cout << "Phong da xoa: " << xoaPhongChild.id << "\t" << xoaPhongChild.name << "\t" << xoaPhongChild.giaThue << endl;
			    		cout<<endl<<"Hien danh sach sau khi xoa :\n";
			    		printStack(datPhong);
			    		system("pause"); 
				        
				    } else {
				        cout << "Khong tim thay phong!" << endl;
				    }		
				}
				else if(luaChon == 5){
					int dong;
					cout<<"1.Gia phong re nhat\n2. Gia phong max nhat \nMoi ban nhap :";
					cin>>dong;
					if(dong==1){
						cout<<"Phong re nhat :"<<findMinNode(merge)->dataKs.id<<"\t"<<findMinNode(merge)->dataKs.name<<"\t"<<findMinNode(merge)->dataKs.giaThue<<endl;
					}
					else{
						cout<<"Phong max nhat :"<<phongGiaThuMax(merge)->dataKs.id<<"\t"<<phongGiaThuMax(merge)->dataKs.name<<phongGiaThuMax(merge)->dataKs.giaThue<<endl;
					}
					system("pause");
				}
				else if(luaChon == 6){
					bubble_sort(merge);
					cout<<endl<<"Hien danh sach sau khi sap xep :"<<endl;
					printStack(merge) ;
					break;
				}
				else if(luaChon == 7){
					insertLastThemPrev(merge,phong5);
				}
				
			}while(true);
		}
	}
}



//Đang gặp ở lỗi nhập , nếu nhập thêm thì lại bắt đầu từ vị trí 0 . 
//Bây giờPhải đưa mỗi lần nhập thì i tăng từ vị trí tiếp theo 