#include <iostream>
#include <cstring>

class string
{
public:
	// конструктор 
	string(const char* str) 
	{
		if(str)
		{
			int length = std::strlen(str);
			copyString(str, length);
		}
	}

	// конструктор копирования
	string(const string& str) 
	{
		if(str.buf)
			copyString(str.buf, str.size);
	}

	// конструктор move
	string(string&& str) noexcept
	{
		buf = str.buf;
		size = str.size;
		str.buf = nullptr;
		str.size = 0;
	}

	// деструктор
	~string()
	{
		delete[] buf;
		buf = nullptr;
		size = 0;
	}

	// оператор присваивания
	string& operator=(const string& str)
	{
		if(str.buf)
			copyString(str.buf, str.size);
		return *this;
	}

	// оператор присваивания move
	string& operator=(string&& str) noexcept
	{
		if(str.buf)
		{
			buf = str.buf;
			size = str.size;
			str.buf = nullptr;
			str.size = 0;
		}
		return *this;
	}

	// оператор += строка 
	string& operator+=(const string& str)
	{
		if(str.buf)
		{
			int newSize = size + str.size;
			char* newBuf = new char[newSize + 1];
			std::memcpy(newBuf, buf, size);
			std::memcpy(newBuf + size, str.buf, str.size);
			newBuf[newSize] = '\0';
			delete[] buf;
			buf = newBuf;
			size = newSize;
		}
		return *this;
	}

	// оператор += чар 
	string& operator+=(const char* str)
	{
		if (str)
		{
			int strSize = std::strlen(str);
			int newSize = size + strSize;
			char* newBuf = new char[newSize + 1];
			std::memcpy(newBuf, buf, size);
			std::memcpy(newBuf + size, str, strSize);
			newBuf[newSize] = '\0';
			delete[] buf;
			buf = newBuf;
			size = newSize;
		}
		return *this;
	}

	// оператор индексации
	char& operator[](int index)
	{
		if (index >= size)
			throw std::out_of_range("index out of range");
		return buf[index];
	}

	// константный оператор индексации
	const char& operator[](int index) const
	{
		if (index >= size)
			throw std::out_of_range("index out of range");
		return buf[index];
	}

	// оператор вывода
	friend std::ostream& operator<<(std::ostream& os, const string& str) {
		if (str.buf) {
			os << str.buf;
		}
		return os;
	}

	// поулчение размера 
	int getSize() const
	{
		return size; 
	}

	//  получение строки 
	const char* getBuf() const
	{
		return buf ? buf : "";
	}

private:
	// метод который занимается копированием
	void copyString(const char* str, int length)
	{
		buf = new char[length + 1];
		std::memcpy(buf, str, length);
		buf[length] = '\0';
		size = length;
	}

private:
	char* buf = nullptr; // указатель на масив строк 
	int size = 0; // размер масива 
};

// внешний оператор сложения string + string
string operator+(const string& str1, const string& str2)
{
	string str = str1;
	str += str2;
	return str;
}


// внешний оператор сложения string + char 
string operator+(const string& str1, const char* str2)
{
	string str = str1;
	str += str2;
	return str;
}

// внешний оператор сложения  char + string
string operator+(const char* str1, const string& str2)
{
	string str = str1;
	str += str2;
	return str;
}


int main()
{
	// пример использовыания 
	// Сложение 
	const char* strNinja = "Ninja ";
	string strBrayan = "Brayan";
	string strNSP = strNinja + strBrayan;
	std::cout << strNSP << std::endl;

	// оператор +=
	strNSP += " and Dan";
	std::cout << strNSP << std::endl;

	// move сементика
	string strGood = "NSP";
	std::cout << strGood << std::endl;
	string strLetsTry = std::move(strGood);
	std::cout << strLetsTry << std::endl;
	std::cout << strGood << std::endl;

	return 0;
}