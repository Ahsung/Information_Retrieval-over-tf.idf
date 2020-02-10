//B511209 최아성
#include "dictionary.h"

bool IsAlpha(int c) {return c>='a' && c<='z' || c>='A'&&c<='Z';}
bool IsDigit(int c) {return c>='0' && c<='9';}
bool IsBlank(int c) {return c==' ' || c == '\t' || c=='\n';}

bool IsOtherCode(int c){
	return  c < -1 || c > 127;
}

bool IsLetter(int c) {
	return IsAlpha(c) || IsOtherCode(c);
}

void SkipBlanks(istream& in){
	char c;
	while ((c=in.peek())!=EOF && IsBlank(c))
		in.get();
}

void Capital2Lower(char* word){
	int index = 0;
	while (word[index] != '\0') {
		if (word[index] <= 'Z' && word[index] >= 'A') {
			word[index] += 'a' - 'A';
		}
		index++;
	}
}

void Filepos2Str(istream& in, int pos, char* str) {

	if( !(in.seekg(pos, ios::beg)) )
		throw "Seekg Failed";
	in >> str;
}

//[a-zA-Z]찾아
bool NextWord(istream& in, char* word) {
	char c;
	while( !IsLetter(c = in.peek()) ){
		if(c == EOF) return false;
		in.get();
	}
	int wordlen =0;
	while (IsLetter(in.peek()) ){
		word[wordlen++] = in.get();
		if (wordlen == MAXLEN) break;
	}
	word[wordlen] = '\0';
	return true;
}

bool IsStopWord(char *word) {
	if (strcmp(word, "is") == 0 || strcmp(word, "the") == 0 || strcmp(word, "very") ==0 ) return true;
	return false;
}

bool NextNonStopWord(istream& in, char *word) {
	while(1){
		if(!NextWord(in, word) ) return false;
		if(!IsStopWord(word) ) return true;
	}
}

//

int NumDocs() {
	ifstream iin("ir.info");
	int numdocs, numwords; float maxidf;
	if(!(iin >> numdocs>>numwords>>maxidf))
		throw "ir.info does not exist";
	iin.close();
	return numdocs;
}
int NumWords() { 
	ifstream iin("ir.info");
	int numdocs, numwords; float maxidf;
	if (!(iin >> numdocs >> numwords >> maxidf))
		throw "ir.info does not exist";
	iin.close();
	return numwords;
}
double MaxIDF() { 
	ifstream iin("ir.info");
	int numdocs, numwords; float maxidf;
	if (!(iin >> numdocs >> numwords >> maxidf))
		throw "ir.info does not exist";
	iin.close();
	return maxidf;
}

// dictionary를 이진탐색으로 찾는다.
// 사전순으로 word가 정렬되어 있다.
bool BinarySearchDictionary(ifstream& din, const char *word, Dict_Term& tm)
{	
	din.clear();

	Dict_Term temp;
	int mid;
	int left = 0;
	int right = NumWords()-1;
	//Binary Search 
	//현재 seek의 Dic_Term에 저장되어 있는 word와 찾고있는 word를 비교
	while (left <= right ) {
		mid = (left + right) / 2;
		din.seekg(mid * sizeof(Dict_Term));
		din.read((char *)&temp, sizeof(Dict_Term));
		if (strcmp(temp.word, word) == 0) {
			tm = temp;
			return true;
		};
		if (strcmp(temp.word, word) > 0) {
			right = mid - 1;
		}
		if (strcmp(temp.word, word) < 0) {
			left = mid + 1;
		}
	}
	return false;
}
