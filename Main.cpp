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
	---------------------------------------*/
	ifstream in;
	in.open(argv[1]);

	string fileRecord;

	getline(in, fileRecord);
	in.close();

	/*-------------------------------------
		파일 레코드 vector에 저장
	---------------------------------------*/
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

	/*----------------------------------------
	    구간이 일치하는 첫 숫자의 위치 저장
	------------------------------------------*/
	vector<int>::iterator iter;
	
	/*----------------------------------------
	    검색 대상 구간의 시작과 끝 위치 저장
	------------------------------------------*/
	vector<int>::iterator it_begin;
	vector<int>::iterator it_end;

	it_begin = sequence.begin();
	it_end = it_begin+1;
	
	/*----------------------------------------
	    구간 탐색 시작 위치 설정 변수
	------------------------------------------*/
	vector<int>::size_type s_index = 1;
	while(true) {
		/*-----------------------------------------------------------------------
			수열 전체 구간(수열 시작위치는 계속 변경)에서 검색 대상 구간 찾기
        -------------------------------------------------------------------------*/
		iter = search(sequence.begin()+s_index, sequence.end(), it_begin, it_end);
		cout << "iter_seq : " << *iter << " it_begin : " << *it_begin << " it_end : " << *it_end << endl;
		
		/*-----------------------------------------------------------------------
			찾는 구간이 없으면 -1 반환
			- 수열 검색 시작위치 +1

			일치하는 구간이 존재하면 검색 종료위치 +1 (검색 구간 증가) 
        -------------------------------------------------------------------------*/
		if (*iter < 0) {
			it_begin++;
			s_index++;
		}
		it_end++;		

		if (*iter > 0) {
			cout << "※ iter_seq : " << *iter << " it_begin : " << *it_begin << " it_end : " << *it_end << endl;
			
			/*--------------------------------------------------------------------------------
				검색 구간의 첫 위치의 수와 마지막 위치의 수가 일치하면 반복구간을 찾은 것
			----------------------------------------------------------------------------------*/
			if (*it_begin == *it_end) 
				break;			
		}
	}

	cout << "수열의 첫 시작부분은 : " << *it_begin << endl;
}
