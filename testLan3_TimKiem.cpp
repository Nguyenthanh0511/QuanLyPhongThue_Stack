#include<iostream>
#include<fstream> 
#include<string>
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

int len(stack s) {
    int dem = 0;
    Node* temp = s.top;
    while (temp != NULL) {
        dem++;
        temp = temp->next;
    }
    return dem;
}

Node* MakeNode(stack S, PhongKhachSan KS) {
    Node* p = new Node;
    p->dataKs = KS;
    p->next = S.top;
    p->prev = NULL;
    return p;
}

void Push(stack& s, PhongKhachSan KS) {
    Node* p = MakeNode(s, KS);
    if (s.top != NULL) {
        s.top->prev = p;
    }
    s.top = p;
}
//Pop
PhongKhachSan Pop(stack& s) {
    if (isEmpty(s)) {
        cout << "Khong co phong !";
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
void inManHinhToNode(stack s) {
    if (isEmpty(s)) {
        cout << "rong!!";
        return;
    } else {
        Node* temp = s.top;
        while (temp != NULL) {
            cout << temp->dataKs.id << "\t\t" << temp->dataKs.name << "\t\t" << temp->dataKs.giaThue << endl;
            temp = temp->prev;
        }
    }
}

PhongKhachSan TimKiemTraVePhong(stack s, PhongKhachSan phong) {
    stack temp = s;
    PhongKhachSan ketQua = {0, "", 0};
    if (isEmpty(temp)) {
        cout << "Khong co phong!";
        PhongKhachSan phongRong = ketQua;
        return phongRong;
    } else {
        PhongKhachSan kiemTraPhong;
        while (!isEmpty(temp)) {
            kiemTraPhong = Pop(temp);
            if (kiemTraPhong.id == phong.id) {
                ketQua = kiemTraPhong;
            }
        }
    }
    return ketQua;
}


int main() {
    stack sTang[10];
    stack merge;
    int tang = 0;
    int soTang = 0;
    int soPhong = 0;
    PhongKhachSan phong1 = {1, "Phong 101", 1100};
    PhongKhachSan phong2 = {2, "Phong 102", 150};
    PhongKhachSan phong3 = {3, "Phong 103", 3900};
    PhongKhachSan phong4 = {4, "Phong 104", 1300};
    PhongKhachSan phong5 = {5, "Phong 105", 40.0};
    PhongKhachSan phong6 = {6, "Phong 106", 4500};
    PhongKhachSan phong7 = {7, "Phong 107", 28.0};
//    Push(s, phong1);
//    Push(s, phong2);
//    Push(s, phong3);
//    Push(s, phong4);
//    Push(s, phong5);
//    Push(s, phong6);
//    Push(s, phong7);
    while (true) {
        cout << "\n1. Nhap thong tin phong" << endl;
        cout << "2. Kiem tra so phong da dat phong" << endl;
        cout << "3. Xoa phong khoi danh sach" << endl;
        cout << "4. Tim kiem phong tra ve thong tin phong" << endl;
        cout << "5. In danh sach" << endl;
        cout << "6. Thoat" << endl;
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Nhap thong tin tang thu " << tang + 1 << ":" << endl;
            cout << "Nhap so phong: ";
            cin >> soPhong;

            Init(sTang[tang]);

            for (int i = 0; i < soPhong; i++) {
                PhongKhachSan phong;
                cout << "Nhap thong tin cho phong " << i + 1 << endl;
                cout << "Nhap ID: ";
                cin >> phong.id;
                cout << "Nhap ten phong: ";
                cin.ignore();
                getline(cin, phong.name);
                cout << "Nhap gia thue: ";
                cin >> phong.giaThue;

                bool trungLap = false;
                stack temp = sTang[tang];
                while (!isEmpty(temp)) {
                    PhongKhachSan Ks = Pop(temp);
                    if (phong.id == Ks.id) {
                        trungLap = true;
                        cout << "ID da ton tai trong tang nay. Vui long nhap lai." << endl;
                        break;
                    }
                }

                if (!trungLap) {
                    Push(sTang[tang], phong);
                } else {
                    i--; // Nếu ID trùng lặp, nhập lại cho phòng này
                }
            }

            tang++;
        } else if (choice == 2) {
            int demSoPhong = 0;
            stack mergeLen;
            Init(mergeLen);
            for (int i = 0; i < tang; i++) {
                stack temp = sTang[i];
                while (!isEmpty(temp)) {
                    PhongKhachSan KS = Pop(temp);
                    demSoPhong++;
                    Push(mergeLen, KS);
                }
            }

            cout << "So phong da dat la: " << demSoPhong << endl;
            cout << "Danh sach cac phong da dat la:" << endl;
            inManHinhToNode(mergeLen);
        } else if (choice == 3) {
            int idXoa;
            cout << "Nhap ID phong can xoa: ";
            cin >> idXoa;
            int flag = 0;

            for (int i = 0; i < tang; i++) {
                stack temp = sTang[i];
                stack temp2;
                Init(temp2);

                while (!isEmpty(temp)) {
                    PhongKhachSan KS = Pop(temp);
                    if (KS.id == idXoa) {
                        flag = 1;
                        cout << "Da xoa phong " << idXoa << " thanh cong." << endl;
                    } else {
                        Push(temp2, KS);
                    }
                }

                while (!isEmpty(temp2)) {
                    PhongKhachSan KS = Pop(temp2);
                    Push(temp, KS);
                }
            }

            if (flag == 0) {
                cout << "Khong tim thay phong co ID " << idXoa << " trong danh sach." << endl;
            }
        } else if (choice == 4) {
            cout << "\nTim kiem phong tra ve thong tin phong:\nNhap id phong tim kiem: ";
            PhongKhachSan phongTimKiem;
            cin >> phongTimKiem.id;

            // Sử dụng hàm TimKiemTraVePhong để tìm kiếm phòng
            PhongKhachSan ketQua = TimKiemTraVePhong(merge, phongTimKiem);

            // Kiểm tra kết quả và hiển thị thông tin
            if (phongTimKiem.id == ketQua.id) {
                cout << "Thong tin phong: " << ketQua.id << "\t" << ketQua.name << "\t" << ketQua.giaThue << endl;
            } else {
                cout << "KHONG TIM THAY PHONG" << endl;
            }
            system("pause");
        } else if (choice == 5) {
            cout << "Danh sach cac phong da dat la:" << endl;
            for (int i = 0; i < tang; i++) {
                stack temp = sTang[i];
                while (!isEmpty(temp)) {
                    PhongKhachSan KS = Pop(temp);
                    Push(merge, KS);
                }
            }

            inManHinhToNode(merge);
        } else if (choice == 6) {
            break;
        } else {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Giải phóng bộ nhớ khi kết thúc chương trình
    for (int i = 0; i < tang; i++) {
        stack temp = sTang[i];
        while (!isEmpty(temp)) {
            Pop(temp);
        }
    }

    while (!isEmpty(merge)) {
        Pop(merge);
    }

    return 0;
}
