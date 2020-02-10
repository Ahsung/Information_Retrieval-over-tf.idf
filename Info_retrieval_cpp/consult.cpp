//B511209 최아성 
#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include<utility>
#include<map>
#include<algorithm>
#include"dictionary.h"
using namespace std;
vector<string> queryWords;	    // 질의어
map< string, double > accumulators; //각 단어별 tf.idf 가중치

//문서명이 사전순으로 sorting된 이진파일에서
// binary search를 통해 문서의 단어수를 알아온다.
// 문서의 단어수는 중복없는 개수이다.
bool BinarySearchDoc(const char * docname,int &length) {
	ifstream in("ir.docpos.numuniquewords", ios::in | ios::binary);

	Doclen doclen;
	int mid;
	int left = 0;
	int right = NumDocs()-1;
	while (left <= right) {
		mid = (left + right) / 2;
		in.seekg(mid * sizeof(Doclen));
		in.read((char *)&doclen, sizeof(Doclen));
		if (strcmp(doclen.docn, docname) == 0) {
			length = doclen.length;
			return true;
		};
		if (strcmp(doclen.docn, docname) > 0) {
			right = mid - 1;
		}
		if (strcmp(doclen.docn, docname) < 0) {
			left = mid + 1;
		}
	}
	return false;
}

//사전에 해당하는 Posing들을 반환
Posting * getPosts(ifstream &pin, Dict_Term tm) {
	pin.clear();
	pin.seekg(tm.poststart * sizeof(Posting));
	Posting * pst = new Posting[tm.numposts];
	pin.read((char *)pst, sizeof(Posting)*tm.numposts);
	return pst;
}

// tf.idf를 구해서 acumulator에 저장한다.
// 한단어의 포스팅을 넣어준다.
// 한단어씩 accum함수 실행
// term at a time
void accum(ifstream &docnin, Posting *pst, int numposts, double idf) {
	docnin.clear();
	string docName;
	int len;
	for (int i = 0; i < numposts; i++) {
		//단어의 Posting을 하나씩 계산한다.
		docnin.seekg(pst[i].docpos); docnin >> docName;
		//tf를 구해서 tf.idf를 계산 후 가중치 추가
		if (BinarySearchDoc(docName.c_str(), len)) {
			double tf = log2(double(pst[i].freq + 1)) / log2(double(len));
			if(!accumulators.count(docName) && idf > MaxIDF()/3)accumulators.insert(make_pair(docName, tf*idf));
			else accumulators[docName] += tf * idf;
		}
		else {
			cerr << "not exist" << docName << " document " << endl;
			continue;
		}
	}
}

int main(int argc, char * argv[]) {
	ifstream query(argv[1]);
	ifstream din("ir.dictionary", ios::in | ios::binary);
	ifstream pin("ir.posting", ios::in | ios::binary);
	ifstream docnin("ir.docnames");
	Dict_Term tm;
	char qw[MAXLEN + 1];
	while (NextNonStopWord(query,qw)) {
		Capital2Lower(qw);
		queryWords.push_back(qw);
	}
	int len;
	
	//각 질의어 idf를 binary file에서 search해 온다.
	//각 질의어를 한단어씩 tf.idf 구해서 더한다 term at a time
	cout << "[Query]" << endl;
	for (int i= 0 ; i <queryWords.size(); i++) cout << queryWords[i] << " ";
	cout <<"\n-------------------" << endl;
	for (int i = 0; i < queryWords.size(); i++) {
		if (BinarySearchDictionary(din, queryWords[i].c_str(), tm)) {
			cout << queryWords[i]<< "(idf=" << tm.idf << "): " << tm.numposts << " Posting(s)" << endl;
			// 단어의 dictionary를 찾아서 존재한다면 그 dictionary에 적혀있는 posting 한 line을 반환한다.
			Posting *pst = getPosts(pin, tm);
			//그리고 단어의 idf와 posting의 각 문서별 길이를 구해, tf를 구한다.
			// tf는 단어 빈도이므로 freq에 비례하고 doc의 length에 반비례한다.
			accum(docnin, pst, tm.numposts, tm.idf);
		}
	}
	cout << endl;
	if (accumulators.empty()) {
		cout << "No Releveant Documents Found!" << endl;
	}
	else {
		//accumulator에서 내림차순으로
		//가중치가 높은 것 순으로 꺼내서 보여준다.
		map<string, double>::reverse_iterator it;
		vector< pair<double, string> > result;
		for (it = accumulators.rbegin(); it != accumulators.rend(); it++) {
			result.push_back(make_pair((*it).second, (*it).first));
		}
		sort(result.begin(), result.end());
		for (int i = result.size()-1; i >=0; i--) {
			cout << "["<<result.size()-i<<"] "<< result[i].second << " (tf.idf=" << result[i].first <<")"<< endl;
			ifstream dcontext(result[i].second.c_str());
			string context;
			string temp;
			int j=0;
			while (getline(dcontext,temp) && j<3) {
				context.append(temp + "\n");
				j++;
			};
			cout << context << endl;
			dcontext.close();
		}
	}

	query.close();
	din.close();
	pin.close();
	docnin.close();

}
