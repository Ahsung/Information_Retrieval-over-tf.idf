//B511209 최아성 
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
#include"dictionary.h"
using namespace std;
//Binary file에서 포스팅의 정보를 획득해서 반환 
pair< vector<string>, vector<int> > getPostingLine(ifstream& pin,ifstream& docin, int start, int pstnum) {
	vector<string> docnames(pstnum);
	vector<int> freg(pstnum);
	pin.seekg(start);
	Posting *pst = new Posting[pstnum];
	pin.read((char *)pst, sizeof(Posting)*pstnum);
	for (int i = 0; i < pstnum; i++) {
		docin.seekg(pst[i].docpos);
		docin >> docnames[i];
		freg[i] = pst[i].freq;
	}
	return make_pair(docnames, freg);
}

// 포스팅 정보를 출력
void printdict(string word, vector<int> freg, int docnums,double idf, vector<string> docnames) {
	int sum = 0;
	for (int i = 0; i < freg.size(); i++) sum += freg[i];
	cout << word << " appeared " << sum << " time(s) in " << docnums << " document(s) [ idf=" << idf << " ]" << endl;

	for (int i = 0; i < docnames.size(); i++) {
		cout << docnames[i] << " " << freg[i] << "  ";
	}
	cout <<"\n"<< endl;
}


int main() {
	ifstream din("ir.dictionary", ios::in | ios::binary);
	ifstream pin("ir.posting", ios::in | ios::binary);
	ifstream win("ir.words");
	ifstream docin("ir.docnames");
	string temp;

	string word;
	pair< vector<string>, vector<int> > PstLine;
	Dict_Term tm;
	while (din.read((char *)&tm,sizeof(Dict_Term))){
		word = tm.word; //tm.word는 현재 위치 사전이 가르키는 단어
		PstLine = getPostingLine(pin, docin, tm.poststart*sizeof(Posting), tm.numposts);
		printdict(word, PstLine.second, tm.numposts, tm.idf, PstLine.first);
	}
	cout << endl << "<Collection Summary>" << endl;
	cout << "#Docs = " << NumDocs() << "  #Words = " << NumWords() << "  Max. IDF = " << MaxIDF() << endl;

	din.close();
	pin.close();
	win.close();
	docin.close();
}
