#include <iostream>
#include <string>
#include "Agent.h"
#include "RationaleAgent.h"
using namespace std;

int main(int argc, char* argv[]) {
//    freopen("../tests/public/T03_input.txt","r",stdin);

	string input_line;
	getline(cin, input_line);
	RationaleAgent agent(input_line);
    agent.start();
	return 0;
}

