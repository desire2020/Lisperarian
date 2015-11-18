/*
	���������Md5�㷨
*/
#include "stdincs.hpp"

namespace Nusers
{
	int CircleTheXLeftSBits(int x, int s)
	{
		int temp1 = x << s;
		int temp2 = x >> (32 - s);
		int temp3 = 0;
		for(int i = 0; i<s; i++)
		{
			temp3 += temp2 & (1<<i);
		}
		return temp1 | temp3;
	}
	
	int F(int x, int y, int z){return (x & y) | ((~x) & z);}
	int G(int x, int y, int z){return (x & z) | (y & (~z));}
	int H(int x, int y, int z){return x ^ y ^ z;}
	int I(int x, int y, int z){return y ^ (x | (~z));}
	
	int FF(int &a, int b, int c, int d, int m, char s, int ti)
	{
		a = a + F(b, c, d) + m + ti;
		a = CircleTheXLeftSBits(a, s);
		a += b;
		return 0;
	}
	
	int GG(int &a, int b, int c, int d, int m, char s, int ti)
	{
		a = a + G(b, c, d) + m + ti;
		a = CircleTheXLeftSBits(a, s);
		a += b;
		return 0;
	}

	int HH(int &a, int b, int c, int d, int m, char s,int ti)
	{
		a = a + H(b, c, d) + m + ti;
		a = CircleTheXLeftSBits(a, s);
		a += b;
		return 0;
	}

	int II(int &a, int b, int c, int d, int m, char s, int ti)
	{
		a = a + I(b, c, d) + m + ti;
		a = CircleTheXLeftSBits(a, s);
		a += b;
		return 0;
	}
	
	TPassword printWithLE(int target) 
	{
		TPassword ss = "0123456789abcdef";
		TPassword ans = "";
		while (target) {
			int temp = target & 0xf;
			ans += ss[temp];
			target >> 4;
		}
		return ans;
	}

	TPassword encryptingWithMd5(TPassword userPassword)
	int main()
	{
		int lengthPassword = userPassword.length();
		int lengthOfBits = lengthPassword * 8;
		int M[16] = {0};
		
		int i = 0 , j = 0 , p = 1;
		for ( ; j < 16; ++j) 
		{
			int num;
			if (4 * p - 1 < lengthPassword) num = 4 * p - 1;
			else num = lengthPassword - 1;
			for (int k = num; k >= i; --k) 
			{
				M[j] = (M[j] << 8) + userPassword[k];
			}
			i = num + 1;
			if (i == lengthPassword ) {
				if (i % 4) M[j] += 0x80 << ((i % 4) * 8);
				else M[++j] = 0x80;
				break;
			}
			++p;
		}
		M[14] = lengthOfBits & 0x00000000ffffffff;
		M[15] = lengthOfBits & 0xffffffff00000000;
		
		int A , B , C , D;
		A = 0x67452301;
		B = 0xefcdab89;
		C = 0x98badcfe;
		D = 0x10325476;
		int a = A , b = B , c = C , d = D;
		
		FF(a,b,c,d,M[0],7,0xd76aa478);
		FF(d,a,b,c,M[1],12,0xe8c7b756);
		FF(c,d,a,b,M[2],17,0x242070db); 
		FF(b,c,d,a,M[3],22,0xc1bdceee);
		FF(a,b,c,d,M[4],7,0xf57c0faf);
		FF(d,a,b,c,M[5],12,0x4787c62a); 
		FF(c,d,a,b,M[6],17,0xa8304613);
		FF(b,c,d,a,M[7],22,0xfd469501) ;
		FF(a,b,c,d,M[8],7,0x698098d8) ;
		FF(d,a,b,c,M[9],12,0x8b44f7af) ;
		FF(c,d,a,b,M[10],17,0xffff5bb1) ;
		FF(b,c,d,a,M[11],22,0x895cd7be) ;
		FF(a,b,c,d,M[12],7,0x6b901122) ;
		FF(d,a,b,c,M[13],12,0xfd987193) ;
		FF(c,d,a,b,M[14],17,0xa679438e) ;
		FF(b,c,d,a,M[15],22,0x49b40821);
		
		GG(a,b,c,d,M[1],5,0xf61e2562); 
		GG(d,a,b,c,M[6],9,0xc040b340); 
		GG(c,d,a,b,M[11],14,0x265e5a51); 
		GG(b,c,d,a,M[0],20,0xe9b6c7aa) ;
		GG(a,b,c,d,M[5],5,0xd62f105d) ;
		GG(d,a,b,c,M[10],9,0x02441453) ;
		GG(c,d,a,b,M[15],14,0xd8a1e681); 
		GG(b,c,d,a,M[4],20,0xe7d3fbc8) ;
		GG(a,b,c,d,M[9],5,0x21e1cde6) ;
		GG(d,a,b,c,M[14],9,0xc33707d6) ;
		GG(c,d,a,b,M[3],14,0xf4d50d87) ;
		GG(b,c,d,a,M[8],20,0x455a14ed); 
		GG(a,b,c,d,M[13],5,0xa9e3e905); 
		GG(d,a,b,c,M[2],9,0xfcefa3f8) ;
		GG(c,d,a,b,M[7],14,0x676f02d9) ;
		GG(b,c,d,a,M[12],20,0x8d2a4c8a);
		
		HH(a,b,c,d,M[5],4,0xfffa3942); 
		HH(d,a,b,c,M[8],11,0x8771f681); 
		HH(c,d,a,b,M[11],16,0x6d9d6122); 
		HH(b,c,d,a,M[14],23,0xfde5380c) ;
		HH(a,b,c,d,M[1],4,0xa4beea44) ;
		HH(d,a,b,c,M[4],11,0x4bdecfa9) ;
		HH(c,d,a,b,M[7],16,0xf6bb4b60) ;
		HH(b,c,d,a,M[10],23,0xbebfbc70); 
		HH(a,b,c,d,M[13],4,0x289b7ec6); 
		HH(d,a,b,c,M[0],11,0xeaa127fa); 
		HH(c,d,a,b,M[3],16,0xd4ef3085); 
		HH(b,c,d,a,M[6],23,0x04881d05); 
		HH(a,b,c,d,M[9],4,0xd9d4d039); 
		HH(d,a,b,c,M[12],11,0xe6db99e5); 
		HH(c,d,a,b,M[15],16,0x1fa27cf8) ;
		HH(b,c,d,a,M[2],23,0xc4ac5665);
		
		II(a,b,c,d,M[0],6,0xf4292244) ;
		II(d,a,b,c,M[7],10,0x432aff97) ;
		II(c,d,a,b,M[14],15,0xab9423a7); 
		II(b,c,d,a,M[5],21,0xfc93a039) ;
		II(a,b,c,d,M[12],6,0x655b59c3) ;
		II(d,a,b,c,M[3],10,0x8f0ccc92) ;
		II(c,d,a,b,M[10],15,0xffeff47d); 
		II(b,c,d,a,M[1],21,0x85845dd1) ;
		II(a,b,c,d,M[8],6,0x6fa87e4f) ;
		II(d,a,b,c,M[15],10,0xfe2ce6e0); 
		II(c,d,a,b,M[6],15,0xa3014314) ;
		II(b,c,d,a,M[13],21,0x4e0811a1); 
		II(a,b,c,d,M[4],6,0xf7537e82) ;
		II(d,a,b,c,M[11],10,0xbd3af235); 
		II(c,d,a,b,M[2],15,0x2ad7d2bb); 
		II(b,c,d,a,M[9],21,0xeb86d391);
		A += a;
		B += b;
		C += c;
		D += d;
		
		TPassword encryptedPassword = "";
		encryptedPassword = printWithLE(A) + printWithLE(B) + printWithLE(C) + printWithLE(D);
		return encryptedPassword;
	}
}
