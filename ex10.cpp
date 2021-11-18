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
        cerr << "Usage: ./ex10 <input_audio_original> <input_audio_noise> \nExample: ./ex10 audio/example.wav audio/example_noise.wav" << endl;
        return -1;
    }
    AudioFile<float> audioFile_original;
    audioFile_original.load(argv[1]);
    AudioFile<float> audioFile_noise;
    audioFile_noise.load(argv[2]);

    int numSamples_orig = audioFile_original.getNumSamplesPerChannel();
    int numChannels_orig = audioFile_original.getNumChannels();
    int numSamples_noi = audioFile_noise.getNumSamplesPerChannel();
    int numChannels_noi = audioFile_noise.getNumChannels();

    float somX = 0;
    float somR = 0;
    for (int i = 0; i < numChannels_orig; i++){
        for (int j = 0; j < numSamples_orig; j++){
            somX  += pow(abs(audioFile_original.samples[i][j]),2);
        }
    }    

    for (int i = 0; i < numChannels_noi; i++){
        for (int j = 0; j < numSamples_noi; j++){
            somR += pow(abs(audioFile_noise.samples[i][j]),2);
        }
    }

    float snr = 10*log(somX/somR);
    cout << "SNR: " << snr << endl;

    float diff = 0;
    for (int i = 0; i < numChannels_orig; i++){
        for (int j = 0; j < numSamples_orig; j++){
            diff += abs(audioFile_original.samples[i][j]-audioFile_noise.samples[i][j]);
        }
    } 

    //maximum per sample absolute error
    float error = diff/(numSamples_orig*numChannels_orig);
    cout << "Maximum per sample absolute error: " << error << endl;
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Processing Time: " << duration.count() << endl;
    return 0;
}