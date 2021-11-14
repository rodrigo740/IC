#include<iostream>
#include<fstream>
#include<vector>
#include <limits>
#include "AudioFile/AudioFile.h"

using namespace std;

int main(int argc, char **argv){

    if(argc != 3){
        cerr << "Usage: ./ex3 <input_file> <output_file>\nExample: ./ex3 audio/noise.wav audio/copyNoise.wav" << endl;
        return -1;
    }
    AudioFile<float> audioFile;
    audioFile.load (argv[1]);
    AudioFile<float> output;
    
    int numSamples = audioFile.getNumSamplesPerChannel();
    int numChannels = audioFile.getNumChannels();
    output.setNumChannels(numChannels);
    output.setNumSamplesPerChannel(numSamples);
    int channel = 0;

    for (int i = 0; i < numSamples; i++)
        {
            for (int channel = 0; channel < numChannels; channel++)
            {
                output.samples[channel][i] = audioFile.samples[channel][i];
            }
        }
    output.setBitDepth (audioFile.getBitDepth());
    output.setSampleRate (audioFile.getSampleRate());
    output.save (argv[2], AudioFileFormat::Wave);    
    return 0;
} 
