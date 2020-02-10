//B511209 최아성 
#include<iostream>
#include<utility>
#include<vector>
#include<map>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstring>
#include"dictionary.h"
using namespace std;



int main() {
	
	Doclen doclen;
	ofstream pairLen("ir.docpos.numuniquewords", ios::out | ios::binary);
	char docname[MAXDOCNAME];
	int length;

	//sorting해서 받은 각 문서들의 단어개수 정보를 담은 구조체를
	//이진파일에 저장한다.
	while(cin >> docname >> length) {
		strcpy(doclen.docn, docname);
		doclen.length = length;
		pairLen.write((char *)&doclen, sizeof(Doclen));
	}

	cout << "Complete" << endl;
	pairLen.close();

}
