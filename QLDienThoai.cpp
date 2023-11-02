#include <iostream>
#include <fstream>
using namespace std;
struct DienThoai
{
	int Ma;
	string Ten;
	double DonGia;
};
typedef DienThoai Item;
struct Node
{
	Item Data;//Du lieu
	Node *Next;//link
	
};
struct Stack
{
	Node *Top;
};
//Khoi tao Stack
void Init(Stack &S)
{
	S.Top=NULL;
}
//Kiem tra rong tra ve true neu top dang NULL nguoc lai tra ve false
int IsEmpty(Stack S)
{
	return (S.Top==NULL);
}
int len(Stack S)
{
	int Dem=0;
	Node *p;
	
	p = S.Top;
	while(p!=NULL)
	{
		Dem++;
		p=p->Next;	
	}
	return Dem;
}
//Tao 1 nut moi
Node *MakeNode(Item x)
{
	Node *p = new Node;
	p->Data = x;
	p->Next = NULL;
	return p;
}
//Them phan tu vao Stack
void Push(Stack &S, Item x)
{
	Node *p = MakeNode(x);
	p->Next = S.Top;
	S.Top = p;
}
//Lay phan tu o dau Stack nhung khong xoa
Item Peak(Stack S)
{
	return S.Top->Data;
}
//Loai bo phan tu dau tien khoi danh sach va tra ve gia tri do
Item Pop(Stack &S)
{
	if(IsEmpty(S))
	{
		cout<<"Stack trong!";
	}
	else
	{
		Item x = S.Top->Data;
		S.Top = S.Top->Next;
		return x;
	}
}
//Nhap danh sach ket thuc bang gia tri 0
void Input(Stack &S)
{
	Item x;
	do
	{
		cout<<"Nhap ma:";
		cin>>x.Ma;
		cout<<"Nhap vao ten:";
		cin>>x.Ten;
		cout<<"Nhap vao gia:";
		cin>>x.DonGia;
		if (x.Ma!=0)
			Push(S,x);
	}while(x.Ma!=0);
}
//In ra danh sach gia tri cac phan tu trong ngan xep
void Output(Stack S)
{
	Item x;
	
	while(S.Top!=NULL)
	{
		x = Pop(S);
		cout<<x.Ma<<"\t"<<x.Ten<<"\t"<<x.DonGia<<"\n";
	}	
}
//Tinh tong cac phan tu trong danh sach
int TongStack(Stack S)
{
	int Tong=0;
	Item x; 
	
	while(S.Top!=NULL)
	{
		x = Pop(S);
		Tong = Tong + x.DonGia;
	}	
	return Tong;
}
//Hàm đọc từ tệp dienthoai.txt ra Stack
void TepVaoStack(Stack &S)
{
	ifstream f1;
	int SoLuong;
	Item x;
	
	f1.open("Dienthoai.txt");//Tệp và code cùng 1 thư mục
	if(!f1)//Kiểm tra nếu mở bị lỗi
	{
		cout<<"Loi mo tep!";
		return;
	}
	f1>>SoLuong; //Đọc phần tử đầu tiên để biết số lượng điện thoại
	for(int i=0;i<SoLuong;i++)
	{
		f1>>x.Ma;
		f1>>x.Ten;
		f1>>x.DonGia;
		
		Push(S,x);
	}
	
	f1.close();
}
int main()
{
	Stack S;
	
	TepVaoStack(S); //Gọi hàm để đọc từ tệp ra Stack S
	Output(S);
	return 0;
}
