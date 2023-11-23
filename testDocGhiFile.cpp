#include<iostream>
#include<fstream> 
#include <string>
#include<vector>
#include<limits>
using namespace std;

struct PhongKhachSan {
    int id;
    string name;
    double giaThue; 
};

struct Node {
    PhongKhachSan dataKs;
    Node* next, *prev; 
};

struct stack {
    Node* top; 
}; 

void Init(stack& s) {
    s.top = NULL; 
}

int isEmpty(stack s) {
    return (s.top == NULL);
}

Node* MakeNode(stack S, PhongKhachSan KS) {
    Node* p = new Node;
    p->dataKs = KS;
    p->next = S.top;
    p->prev = NULL;
    return p;
}

void Push(stack& s, PhongKhachSan KS) {
    Node* p = new Node;
    p = MakeNode(s, KS);
    if (s.top != NULL) {
        s.top->prev = p;
    }
    s.top = p;
}

PhongKhachSan Pop(stack& s) {
    if (isEmpty(s)) {
        cout << "Khong co phong !";
    }
    PhongKhachSan KS = s.top->dataKs;
    Node* temp = s.top; 
    s.top = s.top->next;
    delete temp; 
    return KS; 
}

void printStack(stack s) {
    stack temp = s; 
    while (!isEmpty(temp)) {
        PhongKhachSan KS = Pop(temp);
        cout << KS.id << "\t" << KS.name << "\t" << KS.giaThue;
        cout << endl;
    }
}

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

void ghiTep(stack s[], int tang) {
    ofstream f1;
    f1.open("duLieuMau.txt");
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
void inThongTin(stack s[], int tang) {
    for (int i = 0; i < tang; i++) {
        cout << "Tang thu " << i + 1 << endl;
        if(isEmpty(s[i])){
        	cout<<"stack rong!";
		}
        printStack(s[i]);
        cout << endl;
    }
}
int main() {
    PhongKhachSan phong1 = {1, "Phong 101", 1100};
    PhongKhachSan phong2 = {2, "Phong 102", 150};
    stack sTang[10];
    int tang = 3;
	for(int i = 0 ;i <tang;i++){
		Init(sTang[i]);
//		for(int j =0;j<2;j++){
			Push(sTang[i],phong1);
			Push(sTang[i],phong2);
//		}
	}

    // Thực hiện đọc và ghi file
	
	ghiTep(sTang, tang);
    docTep(sTang, tang);
    inThongTin(sTang,tang) ;
	
    return 0;
}
