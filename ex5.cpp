#include <iostream>
#include <fstream>
#include <map>
#include <experimental/filesystem>
#include <math.h>
    
using namespace std;

int main(){
    ifstream ifs("lusiadas.txt");
    ofstream ofs("histogram.txt");
    map<char,int> m;
    for(char x; ifs >> x;){
        m[x]++;
    }
    int sizeFileIn = std::experimental::filesystem::file_size("lusiadas.txt");
    cout << "size: " << sizeFileIn << endl;
     double h =0;
    for(pair<char,int> i : m){
        double p = (static_cast<double>(i.second)/static_cast<double>(sizeFileIn));
        h = h-p*log(p);
        ofs << "" << i.first << " -> " << i.second << endl;
    }
    cout << "Entropy: " << h << endl;
    ifs.close();
    ofs.close();
    return 0;
}