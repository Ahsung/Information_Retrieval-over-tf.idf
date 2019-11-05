//B511209 최아성
#include <iostream>
#include <fstream>
#include<string>
#include "dictionary.h"

using namespace std;

struct Line {
    Line() : capacity(8), numposts(0) { pArray = new Posting[capacity]; }

    void Print();

    void NewWord(string wd) {
        word = wd;
        numposts = 0;
    }

    void NewPosting(Posting);

    string word;
    int totralfreq;
    int numposts; // how many terms stored
    int capacity; // max no. terms storable
    Posting *pArray;
};

// Line implementation follows.
void Line::NewPosting(Posting pst) {
	if (numposts == capacity) {//double mem
		ChangeSize1D(pArray, capacity, 2 * capacity);
		capacity *= 2;
	}
	pArray[numposts++] = pst;

}

void Line::Print() {
    totralfreq = 0;
    for (int i = 0; i < numposts; i++)
		totralfreq += pArray[i].freq;
    cout << word << " " << numposts
         << " " << totralfreq << " ";
    for (int i = 0; i < numposts; i++)
        cout << " " << pArray[i].docpos
             << " " << pArray[i].freq;
    cout << endl;
}

int main() {
    Line line;
    Posting pst;
    string word;
    int docpos;

    if (!(cin >> word >> pst.docpos)) {
        cerr << "Empty input\n";
        return 1;
    }
    line.NewWord(word);
    pst.freq = 1;

    while (cin >> word >> docpos) {
        if (word != line.word) {
            line.NewPosting(pst);
            line.Print();
            // Start new line with new word
            line.NewWord(word);
            // Insert new posting
            pst.docpos = docpos;
            pst.freq = 1;
        } else if (docpos != pst.docpos) {
            line.NewPosting(pst);
            // Start new posting
            pst.docpos = docpos;
            pst.freq = 1;
        } else pst.freq++;
    }// end of while

    line.NewPosting(pst);
    line.Print();
}
