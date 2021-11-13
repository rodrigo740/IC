#include<iostream>
#include<fstream>
#include<vector>
#include <limits>
#include <map>
#include <math.h>
#include "../AudioFile/AudioFile.h"

using namespace std;

int main(int argc, char **argv){
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

    //Variaveis das equacoes
    int delta = stoi(argv[2]);
    float value;
    for(int i=0; i<numChannels; i++){
        for(int j=0; j<numSamples; j++){
            float k = floor( (audioFile.samples[i][j] / delta) + 0.5);
            value = k * delta;
            //cout << audioFile.samples[i][j] << endl;
            output.samples[i][j] = value;
        }
    }
    output.save ("audio/ex8.wav", AudioFileFormat::Wave);    
    return 0;
}