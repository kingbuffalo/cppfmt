#include <iostream>
#include <cassert>
#include <chrono>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <cmath>
#include <climits>
#include <functional>
#include <list>
#include <cstdlib>
#include <set>
#include <stack>
#include <map>
#include <algorithm>
#include "ssfmt.h"

using namespace std;
using namespace buffalo;

#define TEST_MAX 999999
#define CHAR_LEN 50

int main(){
	//fmt("试试中文dssxxfqwe{0},{1},{2},{3}来吧",'a',1123,5.2,"哈哈");
	fmt("试试dssxxfqwe{0},{1},{2},{3}",'a',1123,5.2,"哈哈");

	cout << "----------------------" << endl;

	auto start = std::chrono::steady_clock::now();
	for ( int i=0;i<TEST_MAX; i++ ){
		stringstream ss;
		ssfmt(ss,"dalfdskjf{0},{1}","abc",2);
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "ssfmt time: " << elapsed_seconds.count() << "s\n";


	start = end;
	for ( int i=0;i<TEST_MAX ; i++ ){
		sfmt("dalfdskjf{0},{1}","abc",2);
	}
	end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds3 = end-start;
	std::cout << "sfmt time: " << elapsed_seconds3.count() << "s\n";


	start = end;
	char *tmp = new char[CHAR_LEN];
	for ( int i=0;i<TEST_MAX ; i++ ){
		snprintf(tmp,CHAR_LEN,"试试dalfdskjf%s,%d,%lf,%s,哈哈","abc",2,5.2,"哈仲裁");
	}
	delete[] tmp;
	end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds2 = end-start;
	std::cout << "sprintf time: " << elapsed_seconds2.count() << "s\n";

	return 0;
}
