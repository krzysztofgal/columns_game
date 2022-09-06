#include <windows.h>


class NAPIS{
private:
	char* text;
	unsigned short dl;
	void Alokuj(short);
public:
	NAPIS();
	NAPIS(LPCSTR);
	NAPIS(const NAPIS&);
	NAPIS(int);

	NAPIS& operator=(LPCSTR);
	NAPIS& operator=(const NAPIS&);
	NAPIS& operator=(int);

	LPSTR Text(void);
	LPCSTR CText(void);
	unsigned short Lenght(void);

};
