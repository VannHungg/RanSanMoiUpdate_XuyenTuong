#include <iostream>
#include "myLib.h"
#define MAX 100
#define TIME 20

using namespace std;

int iSoLuong = 3;

void veTuongTren(){
	int iX = 10; 
	int iY = 1;
	
	while (iX <= 100){
		gotoXY(iX, iY);
		cout << "-";
		iX++;
	}
}

void veTuongDuoi(){
	int iX = 10;
	int iY = 26;

	while (iX <= 100){
		gotoXY(iX, iY);
		cout << "-";
		iX++;
	}
}

void veTuongPhai(){
	int iX = 100; 
	int iY = 1;

	while (iY <= 26){
		gotoXY(iX, iY);
		//SetColor(4);
		cout << "|";
		iY++;
	}
}

void veTuongTrai(){
	int iX = 10;
	int iY = 1;

	while (iY <= 26){
		gotoXY(iX, iY);
		//SetColor(10);
		cout << "|";
		iY++;
	}
}

void veTuong(){
	veTuongTren();
	veTuongDuoi();
	veTuongPhai();
	veTuongTrai();
}

void khoiTaoToaDoChoRan(int iToaDoX[], int iToaDoY[]){
	int iX = 50; 
	int iY = 13;

	for (int i = 0; i < iSoLuong; i++){
		iToaDoX[i] = iX;
		iToaDoY[i] = iY;
		iX--;
	}
}

void veRan(int iToaDoX[], int iToaDoY[]){
	for (int i = 0; i < iSoLuong; i++){
		gotoXY(iToaDoX[i], iToaDoY[i]);
		SetColor(9);
		if (i == 0){
			cout << "O";
		}
		else{
			cout << "o";
		}
	}
}

void xoaDuLieuCu(int iToaDoX[], int iToaDoY[]){
	for (int i = 0; i < iSoLuong; i++){
		gotoXY(iToaDoX[i], iToaDoY[i]);
		cout << " ";
	}
}

void themPhanTu(int iArr[], int iX){
	for (int i = (iSoLuong - 1); i >= 0; i--){
		iArr[i + 1] = iArr[i];
	}
	iArr[0] = iX;
	iSoLuong++;
}

void xoaPhanTu(int iArr[], int iViTriXoa){
	for (int i = iViTriXoa; i < iSoLuong; i++){
		iArr[i] = iArr[i + 1];
	}
	iSoLuong--;
}

bool kiemTraRanAnQua(int iXQua, int iYQua, int iX0, int iY0){
	if ((iXQua == iX0) && (iYQua == iY0)){
		return true;
	}
	return false;
}

bool kiemTraRanDeQua(int iToaDoX[], int iToaDoY[], int iXQua, int iYQua){
	for (int i = 0; i < iSoLuong; i++){
		if ((iXQua == iToaDoX[i]) && (iYQua == iToaDoY[i])){
			return true;
		}
	}
	return false;
}

void taoQua(int &iXQua, int &iYQua, int iToaDoX[], int iToaDoY[]){
	do{
		iXQua = rand() % (99 - 11 + 1) + 11;
		iYQua = rand() % (25 - 2 + 1) + 2;
	} while (kiemTraRanDeQua(iToaDoX, iToaDoY, iXQua, iYQua));
	if ((!(abs(iXQua - iYQua) % 20)) || (!(abs(iXQua - iYQua) % 10)) || (!(abs(iXQua - iYQua) % 50))){
		gotoXY(iXQua, iYQua);
		SetColor(4);
		cout << "$";
	}
	else{
		gotoXY(iXQua, iYQua);
		SetColor(7);
		cout << "o";
	}
}

bool kiemTraCoQuaDo(int iXQua, int iYQua){
	return ((!(abs(iXQua - iYQua) % 20)) || (!(abs(iXQua - iYQua) % 10)) || (!(abs(iXQua - iYQua) % 50))) ? true : false;
}

bool kiemTraRanAnQuaDo(int iX0, int iY0, int iXQua, int iYQua){
	bool bCheck;
	if (kiemTraCoQuaDo(iXQua, iYQua)){
		bCheck = kiemTraRanAnQua(iXQua, iYQua, iX0, iY0);
	}
	return bCheck;
}

void xuLyRan(int iToaDoX[], int iToaDoY[], int iX, int iY, int &iXQua, int &iYQua){
	themPhanTu(iToaDoX, iX);
	themPhanTu(iToaDoY, iY);

	if (!kiemTraRanAnQua(iXQua, iYQua, iToaDoX[0], iToaDoY[0])){
		xoaPhanTu(iToaDoX, iSoLuong - 1);
		xoaPhanTu(iToaDoY, iSoLuong - 1);
	}
	else{
		iSoLuong--;
		taoQua(iXQua, iYQua, iToaDoX, iToaDoY);
	}

	veRan(iToaDoX, iToaDoY);
}

bool kiemTraRanChamTuong(int iX0, int iY0, int iCheck){
	if ((iY0 == 2) && (iX0 > 10) && (iX0 < 100) && (iCheck == 1)){
		return true;//gameover
	}
	//ran cham tuong duoi
	else if ((iY0 == 25) && (iX0 > 10) && (iX0 < 100) && (iCheck == 0)){
		return true;//gameover
	}
	//ran cham tuong ben phai
	else if ((iX0 == 99) && (iY0 > 1) && (iY0 < 26) && (iCheck == 2)){
		return true;
	}
	//ran cham tuong ben trai
	else if ((iX0 == 11) && (iY0 > 1) && (iY0 < 26) && (iCheck == 3)){
		return true;//gameover
	}
	return false;
}

bool kiemTraRanChamDuoi(int iToaDoX[], int iToaDoY[]){
	for (int i = 1; i < iSoLuong; i++){
		if ((iToaDoX[0] == iToaDoX[i]) && (iToaDoY[0] == iToaDoY[i])){
			return true; //gameover
		}
	}
	return false;
}

bool kiemTraRan(int iToaDoX[], int iToaDoY[], int iCheck){
	bool bKiemTraChamDuoi = kiemTraRanChamDuoi(iToaDoX, iToaDoY);
	//bool bKiemTraChamTuong = kiemTraRanChamTuong(iToaDoX[0], iToaDoY[0], iCheck);

	if (bKiemTraChamDuoi){
		return true;
	}
	return false;
}

bool kiemTraRanDuocXuyenTuong(int iX0, int iY0, int iXQua, int iYQua, int iTime){
	bool bKiemTraRanAnQuaDo = kiemTraRanAnQuaDo(iX0, iY0, iXQua, iYQua);

	if (bKiemTraRanAnQuaDo){
		Sleep(1000);
		if (iTime < TIME){
			return true;
		}
		else{
			return false;
		}
	}
	return false;
}

int main(){
	srand(time(NULL));
	int iXQua; 
	int iYQua;

	bool bGameOver = false;
	int iToaDoX[MAX];
	int iToaDoY[MAX];
	veTuong();
	khoiTaoToaDoChoRan(iToaDoX, iToaDoY);
	veRan(iToaDoX, iToaDoY);
	taoQua(iXQua, iYQua, iToaDoX, iToaDoY);
	
	int iX = 50;
	int iY = 13;
	int iCheck = 2;
	int iTime = 0;

	while (!bGameOver){
		xoaDuLieuCu(iToaDoX, iToaDoY);
		
		bool bKiemTraCoQuaDo = kiemTraCoQuaDo(iXQua, iYQua);
		bool bKiemTraRanDuocXuyenTuong = false;//kiemTraRanDuocXuyenTuong(iToaDoX[0], iToaDoY[0], iXQua, iYQua, iTime);

		//dieu khien
		if (_kbhit()){
			char cKyTu = _getch();
			if (cKyTu == -32){
				cKyTu = _getch();
				if (cKyTu == 72 && iCheck != 0){//di len
					iCheck = 1;
				}
				else if (cKyTu == 80 && iCheck != 1){
					//di xuong
					iCheck = 0;
				}
				else if (cKyTu == 77 && iCheck != 3){
					//di qua phai
					iCheck = 2;
				}
				else if (cKyTu == 75 && iCheck != 2){
					//di qua trai
					iCheck = 3;
				}
			}
		}

		//thuc hien di chuyen.
		if ((kiemTraRanChamTuong(iToaDoX[0], iToaDoY[0], iCheck))){
			if (iCheck == 0){
				iY = 2;
			}
			else if (iCheck == 1){
				iY = 25;
			}
			else if (iCheck == 2){
				iX = 11;
			}
			else if (iCheck == 3){
				iX = 99;
			}
		}
		else{
			if (iCheck == 0){
				iY++;
			}
			else if (iCheck == 1){
				iY--;
			}
			else if (iCheck == 2){
				iX++;
			}
			else if (iCheck == 3){
				iX--;
			}
		}

		xuLyRan(iToaDoX, iToaDoY, iX, iY, iXQua, iYQua);
		bGameOver = (kiemTraRan(iToaDoX, iToaDoY, iCheck));
		//iTime++;
		Sleep(150);
	}

	_getch();
	return 0;
}