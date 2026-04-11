#include "AudioSource/SynthAudioSource.hpp"
#include <cmath>
#include <cstdint>

SynthAudioSource::SynthAudioSource(WaveformType waveform){
  this->waveform = waveform;
}

void SynthAudioSource::audioDeviceIOCallbackWithContext(
  const float *const *inputChannelData,
  int numInputChannels,
  float *const *outputChannelData,
  int numOutputChannels,
  int numSamples,
  const juce::AudioIODeviceCallbackContext &context)
{ 

  for(int i = 0; i < numSamples; i++){
    float currentSample = 0.0f;
    if(this->waveform == WaveformType::Sine){
      //Set the current value of output
      currentSample = 0.15f * (float) std::sin(currentPhase * 2 * M_PI);
    }
    else if(this->waveform == WaveformType::Square){
      if(currentPhase > 0.5f) currentSample = 0.15f;
      else{currentSample = -0.15f;}
    }
    else if(this->waveform == WaveformType::Sawtooth){
      currentSample = 0.15f * (float)((currentPhase * 2.0f) - 1.0f);
    }
    else if(this->waveform == WaveformType::Triangle){
      if(currentPhase < 0.5f){currentSample = 0.15f * (float)((currentPhase * 4.0f) - 1.0f);}
      else{currentSample = 0.15f* (float)(3.0f - (currentPhase * 4.0f) );}
    }
    else if(this->waveform == WaveformType::WhiteNoise){
      float randomNoise = (randomGenerator.nextFloat() * 2.0f) - 1.0f;
      currentSample = 0.15f * randomNoise;
    }
    for(int j = 0; j < numOutputChannels; j++){
      outputChannelData[j][i] = currentSample;
    }

    currentPhase += phaseIncrement;

    //Control the output maximum value
    if (currentPhase >= 1.0) {
      currentPhase -= 1.0;
    }
  }
}

void SynthAudioSource::audioDeviceAboutToStart (juce::AudioIODevice* device){
  double sampleRate = device->getCurrentSampleRate();
  //Sets pitch to A = 432.0Hz
  phaseIncrement = 432.0f / sampleRate;
}

void SynthAudioSource::audioDeviceStopped(){

}