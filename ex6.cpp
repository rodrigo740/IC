#include<iostream>
#include<fstream>
#include<vector>
#include <limits>
#include <map>
#include <math.h>
#include "AudioFile/AudioFile.h"

using namespace std;

int main(int argc, char **argv){
    if(argc != 3){
        cerr << "Usage: ./ex6 <input_audio> <histogram_txt>\nExample: ./ex6 audio/example.wav txts/hist.txt" << endl;
        return -1;
    }
    ofstream ofs(argv[2]);
    AudioFile<float> audioFile;
    audioFile.load(argv[1]);
    int numSamples = audioFile.getNumSamplesPerChannel();
    int numChannels = audioFile.getNumChannels();
    cout << "Channels: " <<  numChannels << endl;
    cout << "Samples: " << numSamples << endl;
    map<float,int> ml,mr,mm;

    for (int i = 0; i < numSamples; i++){
        ml[(audioFile.samples[0][i])]++;
        mr[(audioFile.samples[1][i])]++;
    }
    for (int i = 0; i < numSamples; i++){
        for (int j = 0; j < numChannels; j++){
            mm[(audioFile.samples[j][i])]++;
        }
    }
    double hl = 0;
    for(pair<float,int> i : ml){
        double p = (static_cast<double>(i.second)/static_cast<double>(numSamples));
        hl = hl-p*log(p);
        ofs << "R. " << i.first << " -> " << i.second << endl;
    }
    cout << "Entropy Left Channel: " << hl << endl;
    double hr = 0;
    for(pair<float,int> i : mr){
        double p = (static_cast<double>(i.second)/static_cast<double>(numSamples));
        hr = hr-p*log(p);
        ofs << "L. " << i.first << " -> " << i.second << endl;
    }
    cout << "Entropy Right Channel: " << hr << endl;
    double hm = 0;
    for(pair<float,int> i : mm){
        double p = (static_cast<double>(i.second)/static_cast<double>(numSamples));
        hm = hm-p*log(p);
        ofs << "M. " << i.first << " -> " << i.second << endl;
    }
    cout << "Entropy Mono Version: " << hm << endl;
    ofs.close();
    return 0;
}
