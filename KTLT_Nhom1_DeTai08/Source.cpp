/*
Nhóm 1 - Đề tài 8: Cài đặt giải bài toán chọn giải pháp sắp xếp Container xuất khẩu.
Thành viên:
	Võ Văn Tú - 2001190315
	Đặng Quốc Vũ - 2001191214
	Nguyễn Ngọc Bảo Trang - 2001190302
	Lê Thị Diễm Trinh - 2201173014
	Hồ Tường Vy - 2001190340

	Bài tập lớn kết thúc môn Kỹ Thuật Lập Trình
*/

/*
Khai báo thư viện
*/
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <string>
#include <time.h> 
/*
Định nghĩa
*/
#define MAX 50

/*
Khaii báo cấu trúc
*/
//Cấu trúc loại thùng hàng
struct ThungHang
{
	char tenLoaiThungHang[35];
	float dai, rong, cao, theTich, trongTai, giaTri;
	int soLuong, soLuongChon = 0;
};
//Cấu trúc loại container
struct Container
{
	char loaiContainer[35];
	float dai, rong, cao, theTich, trongTai, giaTri;
	int soLuong, soLuongChon = 0;
	ThungHang dsTH[MAX];
	int soLuongLoaiTH = 0;
	int id;//áp dụng cho container
};
/*
Khai báo hàm con
*/
int menu();
void docFile(Container dsCon[], ThungHang dsTH[], int& nCon, int& nTH);
void sapXepContainer(Container dsCon[], int nCon);
void hoanViContaier(Container& a, Container& b);
void sapXepThungHang(ThungHang dsTH[], int nTH);
void hoanViThungHang(ThungHang& a, ThungHang& b);
void xuatDanhSach(Container dsCon[], ThungHang dsTH[], int nCon, int nTH);
void xuatDanhSachChon(Container dsCon[], int nCon);
int tinhTongContainer(Container dsCon[], int nCon);
int tinhTongThungHang(ThungHang dsTH[], int nTH);
void sapXepContainerXuatKhau(Container dsCon[], ThungHang dsTH[], Container dsConKQ[], int nCon, int& nTH, int& nKQ);
float timTheTichMin(ThungHang dsTH[], int nTH);
float timTrongTaiMin(ThungHang dsTH[], int nTH);
void xuatKQ(Container dsConKQ[], int nKQ);
void xoaTH(ThungHang dsTH[], int& nTH, int vt);
void XuatDSCont(Container dsCont[], int nCont);
void XuatDSTH(ThungHang dsTH[], int nTH);
void themTH(ThungHang dsTH[], int& nTH);
void themCont(Container dsCont[], int& nCont);
void themCont(Container dsCont[], int nCont, char loaiCont[], int soLuong);
void ghiFile(Container dsCon[], Container dsConKQ[], int nCon, int nKQ);
/*
Hàm main
*/
void main()
{
	Container dsCon[MAX];
	ThungHang dsTH[MAX];
	int nCon, nTH, kq;
	int thoat = 0, chon;
	char loaiTH[35];

	docFile(dsCon, dsTH, nCon, nTH);
	do
	{
		chon = menu();
		switch (chon)
		{
		case 0:
			thoat = 1;
			break;
		case 1:
			XuatDSCont(dsCon, nCon);
			break;
		case 2:
			XuatDSTH(dsTH, nTH);
			break;
		case 3:
			themCont(dsCon, nCon);
			break;
		case 4:
			themTH(dsTH, nTH);
			break;
		case 5:
			printf("\t\tNhap Loai Container: ");
			int c;
			scanf_s("%d", &c);
			fflush(stdin);
			gets_s(loaiTH);
			printf("\t\tNhap So Luong : ");
			scanf_s("%d", &kq);
			themCont(dsCon, nCon, loaiTH, kq);
			break;
		case 6:
			Container dsKQ[MAX];
			int nKQ;

			sapXepContainer(dsCon, nCon);
			sapXepThungHang(dsTH, nTH);
			sapXepContainerXuatKhau(dsCon, dsTH, dsKQ, nCon, nTH, nKQ);
			//xuatDanhSach(dsCon, dsTH, nCon, nTH);
			xuatDanhSachChon(dsCon, nCon);
			xuatKQ(dsKQ, nKQ);
			ghiFile(dsCon, dsKQ, nCon, nKQ);
			break;
		}
	} while (thoat == 0);

}
/*
Thân hàm con
*/

//đọc dữ liệu file input đầu vào
void docFile(Container dsCon[], ThungHang dsTH[], int& nCon, int& nTH)
{
	FILE* f;
	//input.txt : file du lieu dau vao
	fopen_s(&f, "../data/input/input.txt", "rt");
	if (f == NULL)
	{
		printf("File ko load dc");
		exit(0);
	}
	//đọc danh sách Container
	fscanf_s(f, "%d", &nCon);
	//printf("%d\n", nCon);
	for (int i = 0; i < nCon; i++)
	{
		int c;
		fscanf_s(f, "%d", &c);
		fflush(stdin);
		//fscanf_s(f, "%s", &dsCon[i].loaiContainer);
		fgets(dsCon[i].loaiContainer, 35, f);
		dsCon[i].loaiContainer[strlen(dsCon[i].loaiContainer) - 1] = '\0';
		fscanf_s(f, "%f", &dsCon[i].rong);
		fscanf_s(f, "%f", &dsCon[i].cao);
		fscanf_s(f, "%f", &dsCon[i].dai);
		fscanf_s(f, "%f", &dsCon[i].trongTai);
		fscanf_s(f, "%d", &dsCon[i].soLuong);
		dsCon[i].theTich = dsCon[i].dai * dsCon[i].rong * dsCon[i].cao;
		dsCon[i].giaTri = dsCon[i].trongTai / dsCon[i].theTich;

		//printf("%s\t %.3f\t %.3f\t %.3f\t %.3f\t %.3f\t %d %.3f\n", dsCon[i].loaiContainer, dsCon[i].rong,
			//dsCon[i].cao, dsCon[i].dai, dsCon[i].theTich, dsCon[i].trongTai, dsCon[i].soLuong, dsCon[i].giaTri);
	}

	//đọc danh sách thùng hàng
	fscanf_s(f, "%d", &nTH);
	//printf("%d\n", nTH);
	for (int i = 0; i < nTH; i++)
	{
		int c;
		fscanf_s(f, "%d", &c);
		fflush(stdin);
		//fscanf_s(f, "%s", &dsCon[i].loaiContainer);
		fgets(dsTH[i].tenLoaiThungHang, 35, f);
		dsTH[i].tenLoaiThungHang[strlen(dsTH[i].tenLoaiThungHang) - 1] = '\0';
		fscanf_s(f, "%f", &dsTH[i].rong);
		fscanf_s(f, "%f", &dsTH[i].cao);
		fscanf_s(f, "%f", &dsTH[i].dai);
		fscanf_s(f, "%f", &dsTH[i].trongTai);
		fscanf_s(f, "%d", &dsTH[i].soLuong);
		dsTH[i].theTich = dsTH[i].dai * dsTH[i].rong * dsTH[i].cao;
		dsTH[i].giaTri = dsTH[i].trongTai / dsTH[i].theTich;

		//printf("%s\t %.3f\t %.3f\t %.3f\t %.3f\t %.3f\t %d\t %.3f\n", dsTH[i].tenLoaiThungHang, dsTH[i].rong,
			//dsTH[i].cao, dsTH[i].dai, dsTH[i].theTich, dsTH[i].trongTai, dsTH[i].soLuong, dsTH[i].giaTri);
	}
	fclose(f);
}
//săp xếp container theo giá trị giảm dần
void sapXepContainer(Container dsCon[], int nCon)
{
	for (int i = 0; i < nCon - 1; i++)
	{
		for (int j = i + 1; j < nCon; j++)
		{
			if (dsCon[i].giaTri < dsCon[j].giaTri)
			{
				hoanViContaier(dsCon[i], dsCon[j]);
			}
		}
	}
}
//hoán vị dữ liệu hai container
void hoanViContaier(Container& a, Container& b)
{
	Container tam = a;
	a = b;
	b = tam;
}
//sắp xếp thùng hàng theo giá trị giảm dần
void sapXepThungHang(ThungHang dsTH[], int nTH)
{
	for (int i = 0; i < nTH - 1; i++)
	{
		for (int j = i + 1; j < nTH; j++)
		{
			if (dsTH[i].giaTri < dsTH[j].giaTri)
			{
				hoanViThungHang(dsTH[i], dsTH[j]);
			}
		}
	}
}
//hoán vị dữ liệu hai thùng hàng
void hoanViThungHang(ThungHang& a, ThungHang& b)
{
	ThungHang tam = a;
	a = b;
	b = tam;
}
//tìm thể tích nhỏ nhất trong tất cả các thùng hàng
float timTheTichMin(ThungHang dsTH[], int nTH)
{
	float kq = dsTH[0].theTich;
	for (int i = 1; i < nTH; i++)
		if (dsTH[i].theTich < kq)
			kq = dsTH[i].theTich;
	return kq;
}
//tìm trọng tải nhỏ nhất trong tất cả các thùng hàng
float timTrongTaiMin(ThungHang dsTH[], int nTH)
{
	float kq = dsTH[0].trongTai;
	for (int i = 1; i < nTH; i++)
		if (dsTH[i].trongTai < kq)
			kq = dsTH[i].trongTai;
	return kq;
}
//xuất danh sách dữ liệu đầu vào
void xuatDanhSach(Container dsCon[], ThungHang dsTH[], int nCon, int nTH)
{
	//Danh sách container
	printf("Danh sach loai Contaier: %d\n", nCon);
	printf("Ten container\troong\tcao\tdai\tthe tich\ttrong tai\tso luong\t gia tri\tso luong chon\n");
	for (int i = 0; i < nCon; i++)
	{
		printf("%s\t\t%.3f\t%.3f\t%.3f\t%.3f\t\t%.3f\t%d\t\t %.3f\t%d\n", dsCon[i].loaiContainer, dsCon[i].rong,
			dsCon[i].cao, dsCon[i].dai, dsCon[i].theTich, dsCon[i].trongTai, dsCon[i].soLuong, dsCon[i].giaTri, dsCon[i].soLuongChon);
	}
	//danh sách thùng hàng
	printf("\nDanh sach loai Thung Hang: %d\n", nTH);
	printf("Ten thung hang\troong\tcao\tdai\tthe tich\ttrong tai\tso luong\t gia tri\n");
	for (int i = 0; i < nTH; i++)
	{
		printf("%s\t%.3f\t%.3f\t%.3f\t%.3f\t\t%.3f\t\t%d\t\t %.3f\n", dsTH[i].tenLoaiThungHang, dsTH[i].rong,
			dsTH[i].cao, dsTH[i].dai, dsTH[i].theTich, dsTH[i].trongTai, dsTH[i].soLuong, dsTH[i].giaTri);
	}
}
//xuất danh sách thống kê số lượng từng loại container đã chọn
void xuatDanhSachChon(Container dsCon[], int nCon)
{
	printf("\n\t\t\t\033[3;42;30m       Danh Sach Cac Container Da Chon      \033[0m");
	printf(".\n");
	printf("\x1B[31m\tLoai\tThe Tich\tTrong Tai\tSo Luong Da Chon\tSo Luong Con Lai\033[0m");
	printf(".\n");
	for (int i = 0; i < nCon; i++)
	{
		if (dsCon[i].soLuongChon != 0)
			printf("\t%s\t%.3f\t\t%.3f\t%d\t\t\t%d\n", dsCon[i].loaiContainer, dsCon[i].theTich, dsCon[i].trongTai, dsCon[i].soLuongChon, dsCon[i].soLuong);
	}
}
//tính tổng số lượng container các loại
int tinhTongContainer(Container dsCon[], int nCon)
{
	int sum = 0;
	for (int i = 0; i < nCon; i++)
	{
		sum += dsCon[i].soLuong;
	}
	return sum;
}
//tính tổng số lượng thùng hàng các loại
int tinhTongThungHang(ThungHang dsTH[], int nTH)
{
	int sum = 0;
	for (int i = 0; i < nTH; i++)
	{
		sum += dsTH[i].soLuong;
	}
	return sum;
}
//sắp xếp container xuất khẩu(hàm chính)
void sapXepContainerXuatKhau(Container dsCon[], ThungHang dsTH[], Container dsConKQ[], int nCon, int& nTH, int& nKQ)
{
	//khởi tạo số lượng cont đã chọn từng loại bằng 0
	for (int i = 0; i < nCon; i++)
		dsCon[i].soLuongChon = 0;

	nKQ = 0;
	int tongContainer = tinhTongContainer(dsCon, nCon);//
	int tongTH = tinhTongThungHang(dsTH, nTH);//

	float trongTaiMin = timTrongTaiMin(dsTH, nTH);
	float theTichMin = timTheTichMin(dsTH, nTH);
	//kiểm tra nếu hết cont hoặc hết hàng thì dừng
	if (tongContainer == 0 || tongTH == 0)
	{
		return;
	}

	for (int i = 0; i < nCon; i++)//duyệt danh sách loại container
	{
		if (dsCon[i].soLuong == 0)//nếu số lượng loại container X ==0 bỏ qua
		{
			continue;
		}
		for (int v = 0; v < dsCon[i].soLuong; v++)//duyệt từng container mỗi loại
		{
			Container now = dsCon[i];//Khởi tạo một container mới cùng loại hiện tại

			for (int j = 0; j < nTH; j++)//duyệt danh sách loại thùng hàng
			{

				//nếu container hiện tại ko còn đủ trọng tải hoặc thể tích cho thùng hàng có thể tích 
				//hoặc trọng tải bé nhất thì ko sắp xếp container này nữa
				if (now.trongTai < trongTaiMin || now.theTich < theTichMin)
					break;
				//tinh tỷ lệ
				int tiLeTTai = now.trongTai / dsTH[j].trongTai;
				int tiLeTTich = now.theTich / dsTH[j].theTich;
				//min này là số lượng thùng hàng tối đa loại X container chứa được
				int min = (tiLeTTich < tiLeTTai ? tiLeTTich : tiLeTTai);
				//min là số lượng thùng hàng loại X lấy được
				min = (min < dsTH[j].soLuong ? min : dsTH[j].soLuong);
				if (min == 0)
					continue;
				//sau khi lấy thay đổi các chỉ số của thùng hàng loại X
				dsTH[j].soLuongChon = min;
				dsTH[j].soLuong -= min;

				//sau khi lấy thay đổi các chỉ số của Container loại X
				now.trongTai -= dsTH[j].trongTai * min;
				now.theTich -= dsTH[j].theTich * min;
				now.dsTH[now.soLuongLoaiTH] = dsTH[j];//thêm thùng hàng vào container
				now.soLuongLoaiTH++;
				tongTH -= min;//giảm số lượng thùng hàng trong tổng TH

				//không có thùng hàng loại này
				if (dsTH[j].soLuong <= 0)
				{
					//thêm cái xóa thùng hàng
					xoaTH(dsTH, nTH, j);
					j--;
					continue;
				}
			}
			now.id = v;//lấy cái id theo thứ tự container
			dsConKQ[nKQ] = now;//thêm container vào danh sách kết quả
			nKQ++;//tăng số lượng container
			dsCon[i].soLuongChon++;//tăng số lượng container đã chọn
			tongContainer--;//giảm tổng số lượng container
		}
		//kiểm tra nếu hết cont hoặc hết hàng thì dừng
		if (tongContainer == 0 || tongTH == 0)
			break;
	}
	//giảm số lượng container sau khi sắp xếp
	for (int i = 0; i < nCon; i++)
	{
		dsCon[i].soLuong -= dsCon[i].soLuongChon;
	}
}
//xuất danh sách các container và dữ liệu các thùng hàng sau khi sắp xếp
void xuatKQ(Container dsConKQ[], int nKQ)
{
	printf("\n\t    \033[3;42;30m       Danh Sach Ket Qua Sap Xep Container Xuat Khau      \033[0m");
	printf(".\n");
	//printf("Danh sach Contaier: %d\n", nKQ);
	for (int i = 0; i < nKQ; i++)
	{
		printf("\x1B[31m\tLoai Container\tid\tThe Tich Con Lai\ttrong Tai Con Lai\033[0m");
		printf(".\n");
		printf("\t%s\t\t%d\t%.3f\t\t\t%.3f\n", dsConKQ[i].loaiContainer, dsConKQ[i].id, dsConKQ[i].theTich, dsConKQ[i].trongTai);
		//printf("\n\t-----------------------------------------------------------\n");
		printf("\x1B[33m\tTen Thung Hang\tThe Tich TH\tTrong Tai TH\tSo Luong\033[0m");
		printf(".\n");
		for (int j = 0; j < dsConKQ[i].soLuongLoaiTH; j++)
		{
			printf("\t%s\t%.3f\t\t%.3f\t\t%d\n", dsConKQ[i].dsTH[j].tenLoaiThungHang, dsConKQ[i].dsTH[j].theTich,
				dsConKQ[i].dsTH[j].trongTai, dsConKQ[i].dsTH[j].soLuongChon);
		}
		printf("\n\t-------------------------------------------------------------------\n");
	}
}
//Xóa một loại thùng hàng tại vị trí X
void xoaTH(ThungHang dsTH[], int& nTH, int vt)
{
	if (nTH <= 0)
	{
		return;
	}
	//Dịch chuyển mảng
	for (int i = vt; i < nTH - 1; i++)
	{
		dsTH[i] = dsTH[i + 1];
	}
	//Giảm số lượng phần tử sau khi xóa
	nTH--;
}
//hàm menu
int menu()
{
	fflush(stdin);
	int chon;
	printf("\n\033[3;47;35m\t\t-----------------Danh Sach Chuc Nang---------------\033[0m");
	printf(".\n");
	printf("\x1B[34m\t\t 1. Xuat Danh Sach Container\n\033[0m");
	printf("\x1B[34m\t\t 2. Xuat Danh Sach Thung Hang\n\033[0m");
	printf("\x1B[34m\t\t 3. Them Moi 1 Contariner\n\033[0m");
	printf("\x1B[34m\t\t 4. Them Moi 1 Thung Hang\n\033[0m");
	printf("\x1B[34m\t\t 5. Them 1 Container Da Co Truoc\n\033[0m");
	printf("\x1B[34m\t\t 6. Sap Xet Tat Ca Thung Hang Vao Container\n\033[0m");
	printf("\x1B[31m\t\t 0. Thoat Chuong Trinh\n\033[0m");

	printf("\n\t\t---------------------------------------------------\n");
	printf("\033[3;43;30m\t\tMoi chon chuc nang\033[0m ");
	printf(": ");
	scanf_s("%d", &chon);
	return chon;
}
//Xuất danh sách Container hiện có
void XuatDSCont(Container dsCont[], int nCont)
{
	printf("\n\t\t\t\033[3;42;30m       Danh Sach Container      \033[0m");
	printf(".\n");
	printf("\x1B[31m\tLoai Container\tThe Tich\tTrong Tai\tSo Luong\033[0m");
	//printf("\033[3;104;30m\tLoai Container\tThe Tich\tTrong Tai\tSo Luong\033[0m");
	printf(".\n");

	//printf("\tLoai Container\tThe Tich\tTrong Tai\tSo Luong\n");
	for (int i = 0; i < nCont; i++)
	{
		if (dsCont[i].soLuong != 0)
			printf("\t%s\t\t%.3f\t\t%.3f\t%d\n", dsCont[i].loaiContainer, dsCont[i].theTich, dsCont[i].trongTai, dsCont[i].soLuong);;
	}
}
//Xuất danh sách thùng hàng hiện có
void XuatDSTH(ThungHang dsTH[], int nTH)
{

	printf("\n\t\t\t\033[3;42;30m       Danh Sach Thung Hang      \033[0m");
	printf(".\n");
	printf("\x1B[31m\tLoai Container\t\tThe Tich\tTrong Tai\tSo Luong\033[0m");
	printf(".\n");

	for (int i = 0; i < nTH; i++)
	{
		printf("\t%s\t\t%.3f\t\t%.3f\t\t%d\n", dsTH[i].tenLoaiThungHang, dsTH[i].theTich, dsTH[i].trongTai, dsTH[i].soLuong);;
	}
}
//Thêm 1 loại thùng hàng
void themTH(ThungHang dsTH[], int& nTH)
{
	printf("\t\t\x1B[35m Nhap 1 Thung Hang Moi\n\033[0m\t\t");
	ThungHang a;
	printf("Nhap Ten Thung Hang: ");
	int c;
	scanf_s("%d", &c);
	fflush(stdin);
	gets_s(a.tenLoaiThungHang);
	printf("\t\t\t+ Nhap Dai : ");
	scanf_s("%f", &a.dai);
	printf("\t\t\t+ Nhap Cao : ");
	scanf_s("%f", &a.rong);
	printf("\t\t\t+ Nhap Rong : ");
	scanf_s("%f", &a.cao);
	printf("\t\t\t+ Nhap Trong Tai : ");
	scanf_s("%f", &a.trongTai);
	printf("\t\t\t+ Nhap So Luong TH : ");
	scanf_s("%d", &a.soLuong);
	a.theTich = a.dai * a.rong * a.cao;
	a.giaTri = a.trongTai / a.theTich;
	a.soLuongChon = 0;
	dsTH[nTH] = a;
	nTH++;
	system("cls");
	printf("\x1B[32mThem Thung Hang Moi Thanh Cong \n\033[0m\t\t");
}
//Thêm loại Container mới
void themCont(Container dsCont[], int& nCont)
{
	printf("\t\t\x1B[35m Them Moi 1 Container\n\033[0m\t\t");
	Container a;
	printf("Nhap Ten Cont : ");
	int c;
	scanf_s("%d", &c);
	fflush(stdin);
	gets_s(a.loaiContainer);
	printf("\t\t\t+ Nhap Dai : ");
	scanf_s("%f", &a.dai);
	printf("\t\t\t+ Nhap Cao : ");
	scanf_s("%f", &a.rong);
	printf("\t\t\t+ Nhap Rong : ");
	scanf_s("%f", &a.cao);
	printf("\t\t\t+ Nhap Trong Tai : ");
	scanf_s("%f", &a.trongTai);
	printf("\t\t\t+ Nhap So Luong Container : ");
	scanf_s("%d", &a.soLuong);
	a.theTich = a.dai * a.rong * a.cao;
	a.giaTri = a.trongTai / a.theTich;
	a.soLuongChon = 0;
	dsCont[nCont] = a;
	nCont++;
	system("cls");
	printf("\x1B[32mThem Container Moi Thanh Cong \n\033[0m\t\t");

}
//Thêm k container loại X đã có
void themCont(Container dsCont[], int nCont, char loaiCont[], int soLuong)
{

	for (int i = 0; i < nCont; i++)
	{
		if (strcmp(dsCont[i].loaiContainer, loaiCont) == 0)
		{
			dsCont[i].soLuong += soLuong;
			system("cls");
			printf("\n\x1B[32mThem Thanh Cong. \n\033[0m\t\t");
			return;
		}
	}
	system("cls");
	printf("\n\x1B[31mThem Khong Thanh Cong !!\n\033[0m\t\t");

}
//ghi dữ liệu output ra file txt
void ghiFile(Container dsCon[], Container dsConKQ[], int nCon, int nKQ)
{
	//lấy thời gian
	time_t result = time(NULL);
	char timeNow[50];
	ctime_s(timeNow, sizeof timeNow, &result);
	timeNow[strlen(timeNow) - 1] = '\0';
	//tạo tên file kèm thời gian 
	char tenFile[100] = "../data/output/output-";
	strcat_s(tenFile, timeNow);
	strcat_s(tenFile, ".txt");
	FILE* fOUT;
	//thay thế dấu ':' thành '-' để đặt tên file ko lỗi
	for (int i = 0; i < strlen(tenFile); i++)
		if (tenFile[i] == ':')
			tenFile[i] = '-';
	//mở file
	fopen_s(&fOUT, tenFile, "w");
	if (fOUT == NULL)
	{
		printf("File ko load dc");
		exit(0);
	}
	//ghi file 
	//xuất danh sách Container còn lại
	fprintf(fOUT, "\n\t\t\t      Danh Sach Cac Container Da Chon\n\n");
	fprintf(fOUT, "\tLoai\tThe Tich\tTrong Tai\tSo Luong Da Chon\tSo Luong Con Lai\n");
	for (int i = 0; i < nCon; i++)
	{
		if (dsCon[i].soLuongChon != 0)
			fprintf(fOUT, "\t%s\t%.3f\t\t%.3f\t%d\t\t\t%d\n", dsCon[i].loaiContainer, dsCon[i].theTich, dsCon[i].trongTai, dsCon[i].soLuongChon, dsCon[i].soLuong);
	}
	fprintf(fOUT, "\n\t              ****************************************             \n");

	//Xuất danh sách kết quả bao gồm Container và các thùng hàng trong container đó
	fprintf(fOUT, "\n\n\n\t           Danh Sach Ket Qua Sap Xep Container Xuat Khau\n\n");
	for (int i = 0; i < nKQ; i++)
	{
		fprintf(fOUT, "\tLoai Container\tid\tThe Tich Con Lai\ttrong Tai Con Lai\n");
		fprintf(fOUT, "\t%s\t\t%d\t%.3f\t\t\t%.3f\n", dsConKQ[i].loaiContainer, dsConKQ[i].id, dsConKQ[i].theTich, dsConKQ[i].trongTai);
		fprintf(fOUT, "\n\t              ----------------------------------------             \n");
		fprintf(fOUT, "\tTen Thung Hang\tThe Tich TH\tTrong Tai TH\tSo Luong\n");
		for (int j = 0; j < dsConKQ[i].soLuongLoaiTH; j++)
		{
			fprintf(fOUT, "\t%s\t%.3f\t\t%.3f\t\t%d\n", dsConKQ[i].dsTH[j].tenLoaiThungHang, dsConKQ[i].dsTH[j].theTich,
				dsConKQ[i].dsTH[j].trongTai, dsConKQ[i].dsTH[j].soLuongChon);
		}
		fprintf(fOUT, "\n\t-------------------------------------------------------------------\n");
	}
	//xuất thời gian lập báo cáo
	fprintf(fOUT, "\n\t\tThoi gian xuat bao cao: %s", timeNow);
}