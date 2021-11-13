#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(int argc, char **argv){

    if(argc != 3){
        cerr << "Usage: ./ex2 <input_txt> <output_txt>\nExample: ./ex2 txts/lusiadas.txt txts/lusiadasCopy.txt" << endl;
        return -1;
    }

    string fileIn, fileOut, textout, textin;
    vector<char> chars;
    char ch;

    fileIn = argv[1];
    fileOut = argv[2];

    ifstream ifs(fileIn);
    ofstream ofs(fileOut);

    if (!ifs.is_open())
    {
        cerr << "Could not open input file: '" << fileIn << "'" << endl;
        return 1;
    }
    
    
    while (ifs.get(ch))
    {
        chars.push_back(ch);
    }

    for (auto c : chars)
    {
        ofs << c;
    }
    
    ofs << textout;
    ifs.close();
    ofs.close();
    return 0;
}