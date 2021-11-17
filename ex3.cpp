#include<iostream>
#include<fstream>
#include<vector>
#include <limits>
#include "AudioFile/AudioFile.h"
#include <chrono>
using namespace std::chrono;
using namespace std;

int main(int argc, char **argv){
    auto start = high_resolution_clock::now();
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
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Processing Time: " << duration.count() << endl;  
    return 0;
} 
