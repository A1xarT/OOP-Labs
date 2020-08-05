#include "Classes.h"

cString::cString() {
	this->Str = (char*)malloc(1);
	strcpy(this->Str, "");
}
cString::cString(const char* psz) {
	if (NULL == psz) {
		this->Str = (char*)malloc(1);
		strcpy(this->Str, "");
		return;
	}
	this->Str = (char*)malloc(strlen(psz) + 1);
	strcpy(this->Str, psz);
}
cString::cString(const cString& stringsrc){
	if (!strlen(stringsrc.Str)) return;
	Str = (char*)malloc(stringsrc.Getlength() + 1);
	strcpy(Str, stringsrc.Str);
}
cString::~cString() {
	free(this->Str);
}

int cString::Getlength(void) const {
	return strlen(Str);
}
bool cString::Isempty(void)const {
	if (!strlen(Str)) return true;
	return false;
}
void cString::Empty(void) {
	free(this->Str);
	this->Str = (char*)malloc(1);
	strcpy(this->Str, "");
	return;
}
void cString::SetAt(int nindex, char ch) {
	if ((nindex >= 0) && (nindex < strlen(this->Str)) && (ch != '\0')) {
		Str[nindex] = ch;
	}
}
int cString::Compare(const cString& s) const {
	return strcmp(Str, s.Str);
}
int cString::Find(char ch) const {
	int i, len = strlen(this->Str);
	for (i = 0; i < len; i++)
		if (Str[i] == ch) return i;
	return -1;
}
int cString::Find(const char* pszsub) const { 
	char* C = strstr(this->Str, pszsub);
	if (C != NULL) return strlen(this->Str) - strlen(C);
	return -1;
}
cString cString::Mid(int nfirst, int ncount) const {
	int i, new_len;
	if ((ncount <= 0) || (ncount + nfirst > strlen(this->Str))) {
		cString A;
		return A;
	}
	else {
		new_len = ncount + 1;
		char* str_new = (char*)malloc(new_len);
		for (i = 0; i < new_len - 1; i++) str_new[i] = this->Str[nfirst + i];
		str_new[new_len - 1] = '\0';
		cString A(str_new);
		free(str_new);
		return A;
	}
}
cString cString::Left(int ncount) const {
	int i;
	if (ncount <= 0) {
		cString A;
		return A;

	}
	else {
		if (ncount >= strlen(this->Str)) {
			cString A(this->Str);
			return A;
		}
		else {
			char* str_new = (char*)malloc(ncount + 1);
			for (i = 0; i < ncount; i++)
				str_new[i] = this->Str[i];
			str_new[ncount] = '\0';
			cString A(str_new);
			free(str_new);
			return A;
		}
	}
}
cString cString::Right(int ncount) const {
	int i;
	if (ncount <= 0) { 
		cString A;
		return A;
	}
	else
	{
		if (ncount >= strlen(this->Str)) {
			cString A(this->Str);
			return A;
		}
		char* str_new = (char*)malloc(ncount + 1);
		for (i = 0; i < ncount; i++) {
			str_new[i] = this->Str[strlen(this->Str) - ncount + i];
		}
		str_new[ncount] = '\0';
		cString A(str_new);
		free(str_new);
		return A;
	}
}
int cString::operator ==(const cString& string) {
	if (!strcmp(string.Str, this->Str)) return 1;
	return 0;
}
char cString::operator [](int indx) {
	if((indx >= 0)&&(indx <= strlen(this->Str)))
		return this->Str[indx];
}
const cString& cString::operator =(const unsigned char* psz) {
	if (!strlen((char*)psz)) {
		cString A;
		return A;
	}
	else {
		free(this->Str);
		this->Str = (char*)malloc(strlen((char*)psz) + 1);
		strcpy(this->Str, (char*)psz);
		return *this;
	}
}
cString& cString::operator =(const cString& stringsrc) {
	if (stringsrc.Isempty()) {
		cString A;
		return A;
	}
	else {
		free(this->Str);
		this->Str = (char*)malloc(strlen(stringsrc.Str) + 1);
		strcpy(this->Str, stringsrc.Str);
		return *this;
	}
}
cString cString::operator +(const cString& string) {
	if (string.Isempty()) {
		cString A = *this;
		return A;
	}
	else {
		char* new_str = (char*)malloc(strlen(this->Str) + strlen(string.Str) + 1);
		new_str[0] = '\0';
		strcat(new_str, this->Str);
		strcat(new_str, string.Str);
		cString A(new_str);
		return A;
	}
}
cString& cString::operator +=(const cString& string) {
	if (string.Isempty()) return *this;
	else {
		char* new_str = (char*)malloc(strlen(this->Str) + strlen(string.Str) + 1);
		new_str[0] = '\0';
		strcat(new_str, this->Str);
		strcat(new_str, string.Str);
		free(this->Str);
		this->Str = (char*)malloc(strlen(new_str) + 1);
		strcpy(this->Str, new_str);
		return *this;
	}

}
void cString::Print() {
	printf("\n %s", Str);
}
