//B511209 최아성 
#include<iostream>
#include<utility>
#include<vector>
#include<map>
#include<cstring>
#include<string>
#include<algorithm>
#include"dictionary.h"
using namespace std;



vector< Doclen > doclen; //각 문서가 가진 단어 종류의 수 

// 문서안의 단어종류 개수 구해
// 표준으로 출력한다 
int getDoclen(string docname) {
	ifstream in(docname.c_str());
	if (!in) return 0;
	char temp[MAXLEN + 1];
	map<string, bool> cnt;
	while (in >> temp) {
		cnt.insert(make_pair(temp, true)); 
	}
	in.close();
	cout << docname << " " << cnt.size() << endl;
	return cnt.size();
}

int main() {
	ifstream docin("ir.docnames");
	char docname[MAXDOCNAME];
	while (docin >> docname) {
		int dlength = getDoclen(docname);
		if (dlength) {
			Doclen dc;
			strcpy(dc.docn, docname);
			dc.length = dlength;
			doclen.push_back(dc);
		}
	}
	docin.close();


}
