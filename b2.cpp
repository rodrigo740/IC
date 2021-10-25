#include<iostream>
#include<fstream>
#include<vector>
#include <limits>
#include "../AudioFile/AudioFile.h"

using namespace std;

int main(int argc, char **argv){
    AudioFile<float> audioFile;
    audioFile.load ("../IC/noise.wav");
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
    output.save ("../IC/output.wav", AudioFileFormat::Wave);    
    return 0;
} 
