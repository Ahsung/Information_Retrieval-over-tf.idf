//B511209 최아성
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstring>
#include "dictionary.h"
#define maxlen 128;
using namespace std;

int totalwordsNum = 0;
double maxidf = 0;
vector< vector<Posting> > post_line;
int lin5 = 0; // enter each 5 words

//ir.words 작성  
int WordsWrite(string wordsname,ofstream& wout) {
	int wstart = wout.tellp();
	wout << wordsname;
	if ((++lin5) % 5 == 0) wout << "\n";
	else wout << " ";
	return wstart;
}

//Binary file ir.posing 작성 
int PostingWrite(int docnums,int line_index, ofstream& pout) {
	int pstart = pout.tellp();
	int docpos;
	int docinfreq;
	Posting pst;
	for (int i = 0; i < docnums; i++) {
		cin >> docpos >> docinfreq;
		//check document
		
		pst = Posting(docpos, docinfreq);
		post_line[line_index].push_back(pst);
		pout.write(reinterpret_cast<const char *>(&pst), sizeof(Posting));
	}
	return pstart/sizeof(Posting);
}

//Binary file ir.dictionary writed
void DictWrite(Dict_Term tm, ofstream & dout) {
	dout.write(reinterpret_cast<const char *>(&tm), sizeof(Dict_Term));
}

int main() {
		
	ofstream iout("ir.info");
	ofstream wout("ir.words");
	ofstream pout("ir.posting", ios::out | ios::binary);
	ofstream dout("ir.dictionary", ios::out | ios::binary);
	string wordsname;
	int docnums;
	int totalnums;
	
	
	int line_index = -1; // line counting

	Dict_Term tm;
	//각 단어별 등장 문서를 보고
	//indexing term을 위한 파일 생성
	while (cin >> wordsname >> docnums >> totalnums) {
		totalwordsNum++;
		post_line.push_back(vector<Posting>());
		
		// make posting, docnums
		line_index++;
		strcpy(tm.word, wordsname.c_str());
		tm.wordpos = WordsWrite(wordsname, wout);
		tm.poststart = PostingWrite(docnums, line_index, pout);
		tm.numposts = docnums;
		//문서가 희귀할 수록 좋음
		//등장한 문서수에 반비례 총 문서개수에는 비례
		//즉 등장한 문서수가 적을 수록 좋다.
		tm.idf = log2(double(totalDocument)/double(docnums)); 
		DictWrite(tm, dout);
		maxidf = max(maxidf, tm.idf);
	}
	iout << totalDocument << " " << totalwordsNum << " " << maxidf;

	iout.close();
	wout.close();
	pout.close();
	dout.close();
	//만들어진 posting들의 내용 출력
	cout << " Dictionary:\n" << endl;
	for (int i = 0; i < post_line.size(); i++) {
		cout <<" "<< i + 1 <<" Posting_list :"<< endl;
		for (int j = 0; j < post_line[i].size(); j++) {
			printf("[docpos: %2d, freq: %2d]	", post_line[i][j].docpos, post_line[i][j].freq);
		}
		cout << "\n"<<endl ;
	}
}
