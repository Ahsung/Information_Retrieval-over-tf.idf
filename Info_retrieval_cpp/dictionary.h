//B511209 최아성 
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#define MAXLEN 256
#define MAXDOCNAME 100
#define totalDocument 9
using namespace std;

template<class T>
void ChangeSize1D(T *&a, const int oldSize, const int newSize) {
	if (newSize < 0) throw "what is this" ;
	T* temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete[]a;
	a = temp;
}
struct Posting
{
	Posting(int dp = -1, int fr = 0):docpos(dp),freq(fr){}
	int docpos;
	int freq;
};

struct Dict_Term
{
	char word[MAXDOCNAME];
	int wordpos;
	int poststart;
	int numposts;
	double idf;
};

//문서의 unique하게 단어 개수 저장하는 구조체
struct Doclen
{
	char docn[MAXDOCNAME];
	int length;
};

bool IsAlpha(int c);
bool IsDigit(int c);
bool IsBlank(int c);
bool IsOtherCode(int c);
bool IsLetter(int c);

void SkipBlanks(istream& in);
void Capital2Lower(char *word);
void Filepos2Str(istream& in, int pos, char*str);

bool NextWord(istream& in, char *word);
bool IsStopWord(char *word);
bool NextNonStopWord(istream& in, char *word);

bool BinarySearchDictionary(ifstream & din, const char *word, Dict_Term& tm);
int NumDocs();
int NumWords();
double MaxIDF();
#endif

