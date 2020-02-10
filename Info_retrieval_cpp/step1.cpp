
#include <iostream>
#include <fstream>
#include "dictionary.h"
using namespace std;

void PrintAllWordsWithDocpos(istream &in, int docpos) {
    char word[MAXLEN + 1];
    int count = 0;

    while (NextNonStopWord(in, word)) {
		Capital2Lower(word);
        cout << word << " ";
        cout.width(12);
        cout << docpos << endl;
    }
}

bool GetDocnamenDocpos(ifstream &fin, char *docname, int &docpos) {
    SkipBlanks(fin);
    if (fin.peek() == EOF) return false;
    docpos = fin.tellg();
    if (!(fin >> docname)) throw "No";
    return true;
}

int main() {
	ifstream fin("ir.docnames");
	if (!fin) {
		cerr << "what is this..\n";
		return 1;
	}
	int docpos;
	char docname[MAXLEN + 1];
	try {
		while (GetDocnamenDocpos(fin, docname, docpos)) {
			ifstream in(docname);
			if (!in) {
				cerr << docname <<
					" in ir.docnames does not exist.\n";
				continue;
			}
			PrintAllWordsWithDocpos(in, docpos);
			in.close();
		}
	}
	catch (char const *msg) {
		cout << msg << endl;
	}
    fin.close();
}
