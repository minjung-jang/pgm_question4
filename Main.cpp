#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <windows.h>

using namespace std;

void main(int argc, char *argv[]) {

	if (argc < 2) {
		cout << "execute : Program.exe file.txt" << endl;
		exit(-1);
	}

	/*-------------------------------------
		파일 내용 읽어들이기
	-------------------------------------*/
	ifstream in;
	in.open(argv[1]);

	string fileRecord;

	getline(in, fileRecord);
	in.close();

	/*-------------------------------------
		파일 레코드 vector에 저장
	-------------------------------------*/
	string data;

	string::size_type pos = 0;
	string::size_type befo_pos = 0;

	vector<int> sequence;

	while (true) {
		pos = fileRecord.find(", ", pos);
		
		if (pos == string::npos) 
			break;

		data = fileRecord.substr(befo_pos, pos-befo_pos);
		sequence.push_back(atoi(data.c_str()));
		befo_pos = pos+2;
		pos += 2;
	}

	vector<int>::iterator iter;
	
	vector<int>::iterator it_begin;
	vector<int>::iterator it_end;

	it_begin = sequence.begin();
	it_end = it_begin+1;
	
	vector<int>::size_type s_index = 1;
	while(true) {
		iter = search(sequence.begin()+s_index, sequence.end(), it_begin, it_end);
		cout << "iter_seq : " << *iter << " it_begin : " << *it_begin << " it_end : " << *it_end << endl;
		
		if (*iter < 0) {
			it_begin++;
			s_index++;
		}
		it_end++;		

		if (*iter > 0) {
			cout << "※ iter_seq : " << *iter << " it_begin : " << *it_begin << " it_end : " << *it_end << endl;
			
			if (*it_begin == *it_end) 
				break;			
		}
	}

	cout << "수열의 첫 시작부분은 : " << *it_begin << endl;
}
