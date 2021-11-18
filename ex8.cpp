#include<iostream>
#include<fstream>
#include<vector>
#include <limits>
#include <map>
#include <math.h>
#include "AudioFile/AudioFile.h"
#include <chrono>

using namespace std::chrono;
using namespace std;

int main(int argc, char **argv){
    auto start = high_resolution_clock::now();
    if(argc != 3){
        cerr << "Usage: ./ex8 <input_sound> <quantization>\nExample: ./ex8 audio/noise.wav 8" << endl;
        return -1;
    }
    AudioFile<float> audioFile;
    AudioFile<float> output;
    audioFile.load(argv[1]);
    int numSamples = audioFile.getNumSamplesPerChannel();
    int numChannels = audioFile.getNumChannels();
    output.setNumChannels(numChannels);
    output.setNumSamplesPerChannel(numSamples);
    output.setBitDepth (audioFile.getBitDepth());
    output.setSampleRate (audioFile.getSampleRate());
    cout << "Channels: " <<  numChannels << endl;
    cout << "Samples: " << numSamples << endl;

    //passar int e floor
    int niveis = stoi(argv[2]);
    int div = (32/niveis)/2;   //nºde bits a dividir por quantos niveis quero
                            //a dividir por 2 porque dar shift num bit divide por dois, 2 bits por 4, etc...
    for(int i=0; i<numChannels; i++){
        for(int j=0; j<numSamples; j++){
            int n =(int)(audioFile.samples[i][j]*pow(2,15));
            n = n >> div;
            n = n << div;
            output.samples[i][j]=(float)(n/pow(2,15));
        }
    }
    output.save ("audio/ex8.wav", AudioFileFormat::Wave);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Processing Time: " << duration.count() << endl;
    return 0;
}

