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

    // wich sample is stored in b bits
    int b = 32;
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

    //maximum per sample absolute error
    float error = 0;
    cout << "Maximum per sample absolute error: EM FALTA" << error << endl;
    
    return 0;
}