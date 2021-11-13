#include <iostream>
#include <fstream>
#include <map>
#include <experimental/filesystem>
#include <math.h>
    
using namespace std;

int main(int argc, char **argv){
    if(argc != 3){
        cerr << "Usage: ./ex5 <input_txt> <histogram_txt>\nExample: ./ex5 txts/lusiadas.txt txts/hist.txt" << endl;
        return -1;
    }
    ifstream ifs(argv[1]);
    ofstream ofs(argv[2]);
    
    map<char,int> m;
    for(char x; ifs >> x;){
        m[x]++;
    }
    int sizeFileIn = std::experimental::filesystem::file_size(argv[1]);
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