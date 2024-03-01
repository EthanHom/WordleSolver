#include <iostream>
#include <string>
#include "WordleHelper.h"

using namespace std;

int main(){

    WordleHelper wh;
    wh.addGreen("_____");
    wh.addGray("ija");
    wh.addYellow("ou___");
    // wh.addYellow("_____");
    // wh.addYellow("_____");

    std::vector<std::string> pp;
    pp = wh.possibleSolutions();
    for(int i = 0; i < pp.size(); i++){
        cout << pp[i] << endl;
    }



    return 0;

}