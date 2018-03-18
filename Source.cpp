#include <iostream>
#include <fstream>
using namespace std;


void SetBit(int &a, int state, int pos)
{
	if (state)
	{
		a = a | (1 << 31 - pos);
	}
	else
	{
		a = a & ~(1 << 31 - pos);
	}
}

int GetBit(int a, int pos)
{
	return 1 & (a >> 31 - pos);
}

int GetBit(long long int a, int pos)
{
	return 1 & (a >> 63 - pos);
}

//Tính phần giá trị của a từ bit start đến bit end
int GetValue(int a, int start, int end)
{
	int sum = 0;
	int t = 0;
	for (int i = start; i <= end; i++)
	{
		sum = sum | GetBit(a, i) << t;
		t++;
	}
	return sum;
}

void BitToString(long long int a)
{
	for (int i = 0; i < 64; i++)
	{
		cout << GetBit(a, i);
	}
	cout << endl;
}

void BitToString(int a)
{
	for (int i = 0; i < 32; i++)
	{
		cout << GetBit(a, i);
	}
	cout << endl;
}

//Key từ 64 bit --> 56 bit bằng hàm này
void KeyPC1(int &l, int &r) {
	//	8 x 7 bỏ bit 8,16,24,32,40,48,56,64
	int map[56] = { 
		57,49,41,33,25,17,9,
		1,58,50,42,34,26,18,
		10,2,59,51,43,35,27,
		19,11,3,60,52,44,36,
		63,55,47,39,31,23,15,
		7,62,54,46,38,30,22,
		14,6,61,53,45,37,29,
		21,13,5,28,20,12,4 };
	int hl = 0;
	int hr = 0;
	for (int i = 0; i < 56; i++) 
	{
		if (map[i] <= 32) //1-->32, 
		{
			if (i <= 27)
				SetBit(hl, GetBit(l, map[i] - 1), i);
			else
				SetBit(hr, GetBit(l, map[i] - 1), i - 28);
		}
		else//33--> 56
		{
			if (i <= 27)
				SetBit(hl, GetBit(r, map[i] - 1 - 32), i);
			else
				SetBit(hr, GetBit(r, map[i] - 1 - 32), i - 28);
		}
	}
	r = hr;
	l = hl;
}
//Key từ 56 bit --> 48 bit bằng hàm này
void KeyPC2(int &l, int &r) {
	int map[48] = {
		14,17,11,24,1,5,
		3,28,15,6,21,10,
		23,19,12,4,26,8,
		16,7,27,20,13,2,
		41,52,31,37,47,55,
		30,40,51,45,33,48,
		44,49,39,56,34,53,
		46,42,50,36,29,32
	};
	int hl = 0;
	int hr = 0;
	for (int i = 0; i < 48; i++)
	{
		if (map[i] <= 28) //1-->28, 
		{
			if (i <= 23)
				SetBit(hl, GetBit(l, map[i] - 1), i);
			else
				SetBit(hr, GetBit(l, map[i] - 1), i - 24);
		}
		else//29-->56
		{
			if (i <= 23)
				SetBit(hl, GetBit(r, map[i] - 1 - 28), i);
			else
				SetBit(hr, GetBit(r, map[i] - 1 - 28), i - 24);
		}
	}
	r = hr;
	l = hl;
}
//Xáo trộn lần đầu
void InitPermutation(int &l, int &r) {
	int map[64] = { 
		58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,
		64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7
	};
	int hl = 0;
	int hr = 0;
	for (int i = 0; i < 64; i++)
	{
		if (map[i] <= 32) //1-->32, 
		{
			if (i <= 31)
				SetBit(hl, GetBit(l, map[i] - 1), i);
			else
				SetBit(hr, GetBit(l, map[i] - 1), i - 32);
		}
		else//33--> 64
		{
			if (i <= 31)
				SetBit(hl, GetBit(r, map[i] - 1 - 32), i);
			else
				SetBit(hr, GetBit(r, map[i] - 1 - 32), i - 32);
		}
	}
	r = hr;
	l = hl;
}

//Xáo trộn lần cuối
void FinalPermutation(int &l, int &r) {
	int map[64] = {
		40,8,48,16,56,24,64,32,
		39,7,47,15,55,23,63,31,
		38,6,46,14,54,22,62,30,
		37,5,45,13,53,21,61,29,
		36,4,44,12,52,20,60,28,
		35,3,43,11,51,19,59,27,
		34,2,42,10,50,18,58,26,
		33,1,41,9,49,17,57,25 
	};
	int hl = 0;
	int hr = 0;
	for (int i = 0; i < 64; i++)
	{
		if (map[i] <= 32) //1-->32, 
		{
			if (i <= 31)
				SetBit(hl, GetBit(l, map[i] - 1), i);
			else
				SetBit(hr, GetBit(l, map[i] - 1), i - 32);
		}
		else//33--> 64
		{
			if (i <= 31)
				SetBit(hl, GetBit(r, map[i] - 1 - 32), i);
			else
				SetBit(hr, GetBit(r, map[i] - 1 - 32), i - 32);
		}
	}
	r = hr;
	l = hl;
}
//Từ r 32 bit mở rộng thành 48 bit, 24 bit chứa trong l, 24 bit chứa trong r
void Expand(int &l, int &r) {
	int map[48] = { 
		32,1,2,3,4,5,
		4,5,6,7,8,9,
		8,9,10,11,12,13,
		12,13,14,15,16,17,
		16,17,18,19,20,21,
		20,21,22,23,24,25,
		24,25,26,27,28,29,
		28,29,30,31,32,1 };
	int hr = 0;
	int hl = 0;
	for (int i = 0; i < 48; i++) {
		if (i <= 23)
			SetBit(hl, GetBit(r, map[i] - 1), i );
		else 
			SetBit(hr, GetBit(r, map[i] - 1), i - 24);
	}
	r = hr;
	l = hl;
}

//Xáo trộn 32 bit
int MidPermutation(int s) {
	int map[32] = { 
		16,7,20,21,29,12,28,17,
		1,15,23,26,5,18,31,10,
		2,8,24,14,32,27,3,9,
		19,13,30,6,22,11,4,25 
	};
	int res = 0;
	for (int i = 0; i < 32; i++) {
		SetBit(res, GetBit(s, map[i]-1),i);
	}
	return res;
}


//Qui đổi giá trị trong bảng S
int LookInSTable(int num, int row, int column) {
		int map[512] = { 
		14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,
		15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
		3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
		0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
		13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,
		10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
		13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
		13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
		1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,
		7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
		13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
		10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
		3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,
		2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
		14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
		4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
		11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,
		12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
		10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
		9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
		4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,
		4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
		13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
		1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
		6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,
		13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
		1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
		7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
		2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 };
	return (map[num * 64 + row * 16 + column]);
	return 0;
}

//Hàm f nhận vào nửa phải 32 bit, kl 24 bit, kr 24 bit
int FunctionF(int r, int kl, int kr) 
{
	int er = r, el = 0;
	Expand(el, er);
	kl = kl ^ el;
	kr = kr ^ er;

	//kl 24 bit chứa 4 block 6 bit
	//kr 24 bit chứa 4 block 6 bit
	int res = 0;

	for (int i = 0; i < 4; i++)
	{
		int row = 0;
		SetBit(row, GetBit(kl, i * 6 + 5), 0);
		SetBit(row, GetBit(kl, i * 6), 1);
		row = GetValue(row, 0, 1);
		int col = 0;
		SetBit(col, GetBit(kl, i * 6 + 4), 0);
		SetBit(col, GetBit(kl, i * 6 + 3), 1);
		SetBit(col, GetBit(kl, i * 6 + 2), 2);
		SetBit(col, GetBit(kl, i * 6 + 1), 3);
		col = GetValue(col,0,3);

		int s = LookInSTable(i, row, col);

		SetBit(res, GetBit(s, 28), i * 4);
		SetBit(res, GetBit(s, 29), i * 4 + 1);
		SetBit(res, GetBit(s, 30), i * 4 + 2);
		SetBit(res, GetBit(s, 31), i * 4 + 3);

	}
	for (int i = 0; i < 4; i++)
	{
		int row = 0;
		SetBit(row, GetBit(kr, i * 6 + 5), 0);
		SetBit(row, GetBit(kr, i * 6), 1);
		row = GetValue(row, 0, 1);
		int col = 0;
		SetBit(col, GetBit(kr, i * 6 + 4), 0);
		SetBit(col, GetBit(kr, i * 6 + 3), 1);
		SetBit(col, GetBit(kr, i * 6 + 2), 2);
		SetBit(col, GetBit(kr, i * 6 + 1), 3);
		col = GetValue(col, 0, 3);

		int s = LookInSTable(i + 4, row, col);
		
		SetBit(res, GetBit(s, 28), (i + 4) * 4);
		SetBit(res, GetBit(s, 29), (i + 4) * 4 + 1);
		SetBit(res, GetBit(s, 30), (i + 4) * 4 + 2);
		SetBit(res, GetBit(s, 31), (i + 4) * 4 + 3);
	}
	return MidPermutation(res);
}

int ShiftLeft(int inp, int size, int rep) {
	for (int i = 0; i < rep; i++) 
	{
		int bit = 0;
		bit = GetBit(inp, 0);
		bit = bit << 32 - size;
		inp = inp << 1;
		inp = inp | bit;
	}
	return inp;
}

long long int Encrypt(long long int msg, long long int key) 
{
	int kr = (int)(key);
	int kl = (int)(key >> 32);
	int c0 = 0, d0 = 0;
	KeyPC1(kl, kr);
	c0 = kl;
	d0 = kr;

	int r0 = (int)(msg);
	int l0 = (int)(msg >> 32);
	InitPermutation(l0, r0);

	int timeShift[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

	int keyl[16];
	int keyr[16];

	for (int i = 0; i < 16; i++) {
		int t = timeShift[i];

		c0 = ShiftLeft(c0, 28, t);
		d0 = ShiftLeft(d0, 28, t);

		kl = c0;
		kr = d0;

		KeyPC2(kl, kr);

		keyl[i] = kl;
		keyr[i] = kr;
		
	}

	for (int i = 0; i < 16; i++) {
		int tmp = l0;
		l0 = r0;
		r0 = tmp ^ FunctionF(r0, keyl[i], keyr[i]);
	}

	int tmp = r0;
	r0 = l0;
	l0 = tmp;

	FinalPermutation(l0, r0);

	long long int final = l0;
	final = final << 32;
	long long int rtmp = r0;
	rtmp = rtmp & 0xffffffff;
	final += rtmp;
	return final;
}

long long int Decrypt(long long int cipher, long long int key)
{
	int kr = (int)(key);
	int kl = (int)(key >> 32);
	int c0 = 0, d0 = 0;
	KeyPC1(kl, kr);

	c0 = kl;
	d0 = kr;

	int r0 = (int)(cipher);
	int l0 = (int)(cipher >> 32);

	InitPermutation(l0, r0);

	int timeShift[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

	int keyl[16];
	int keyr[16];

	for (int i = 0; i < 16; i++) {
		int t = timeShift[i];

		c0 = ShiftLeft(c0, 28, t);
		d0 = ShiftLeft(d0, 28, t);

		kl = c0;
		kr = d0;

		KeyPC2(kl, kr);

		keyl[i] = kl;
		keyr[i] = kr;
	}

	for (int i = 15; i >= 0; i--) {
		int tmp = l0;
		l0 = r0;
		r0 = tmp ^ FunctionF(r0, keyl[i], keyr[i]);
	}

	int tmp = r0;
	r0 = l0;
	l0 = tmp;

	FinalPermutation(l0, r0);

	long long int final = l0;
	final = final << 32;
	long long int rtmp = r0;
	rtmp = rtmp & 0xffffffff;
	final += rtmp;
	return final;
}

int EncryptFile(char filename[256], long long int key)
{
	ifstream f;
	f.open(filename, ios_base::binary);
	if (!f.is_open())
		return 0;
	int size = 0;
	f.seekg(0,f.end);
	size = f.tellg();
	int remander = size % 8;
	int t = size / 8;
	f.seekg(0, f.beg);
	ofstream fo;
	long long int in = 0;
	long long int out = 0;
	
	strcat_s(filename,256,".en");
	fo.open(filename, ios_base::binary);

	fo.write((char*)&remander,4);//Ghi lại số byte dư phải thêm 0

	for (int i = 0; i < t; i++)
	{
		f.read((char*)&in,8);
		out = Encrypt(in, key);
		fo.write((char*)&out,8);
	}
	if (remander != 0)
	{
		in = 0;
		char ch;
		for (int i = 0; i < remander; i++)
		{
			f.read((char*)&ch, 1);
			long long int tmp = ch;
			tmp = tmp & (long long int) 0xff;
			in += tmp;
			in = in << 8;
		}
		in = in << (56 - remander*8);
		out = Encrypt(in, key);
		fo.write((char*)&out, 8);
	}
	f.close();
	fo.close();
	return 1;
}

int DecryptFile(char * filename, long long int key)
{
	ifstream f;
	f.open(filename, ios_base::binary);
	if (!f.is_open())
		return 0;
	int size = 0;
	f.seekg(0, f.end);
	size = f.tellg();
	int t = (size - 4) / 8;
	f.seekg(0, f.beg);
	int remander = 0;
	
	f.read((char*)&remander, 4);
	ofstream fo;
	long long int in = 0;
	long long int out = 0;

	fo.open("decrypt", ios::binary);
	for (int i = 0; i < t-1; i++)
	{
		f.read((char*)&in, 8);
		out = Decrypt(in, key);
		fo.write((char*)&out, 8);

	}
	f.read((char*)&in, 8);
	out = Decrypt(in, key);
	char ch;
	for (int i = 0; i < remander; i++)
	{
		ch = out >> 8 * (7 - i);
		fo.write((char*)&ch, 1);
	}
	f.close();
	fo.close();
	return 1;
}

void main()
{
	long long int key;
	char filename[256];
	char t = 0;
	while (t != '3')
	{
		cout << "Program encrypt-decrypt file\n1. Encrypt\n2. Decrypt\n3. Exit\n-->You choose:";
		cin >> t;
		if (t == '1')
		{
			cout << "What is the file name to encrypt?: ";
			cin >> filename;
			cout << "The password(you must remmember it): ";
			cin >> key;
			if (EncryptFile(filename, key))
				cout << "File is encrypted !!! new file is " << filename << "\n";
			else
				cout << "Cannot find file\n";
			system("pause");

		}
		else if (t == '2')
		{
			cout << "What is the encrypted file ?: ";
			cin >> filename;
			cout << "What is the password: ";
			cin >> key;
			if(DecryptFile(filename, key))
				cout << "File is decrypted !!! new file is \"decrypt\"\n";
			else
				cout << "Cannot find file\n";
			system("pause");
		}
		else if (t == '3')
		{
			break;
		}
		system("cls");
		
	}
}