#include "AudioSource/SynthAudioSource.hpp"
#include <cmath>

void SynthAudioSource::audioDeviceIOCallbackWithContext(
  const float *const *inputChannelData,
  int numInputChannels,
  float *const *outputChannelData,
  int numOutputChannels,
  int numSamples,
  const juce::AudioIODeviceCallbackContext &context)
{ 

  for(int i = 0; i < numSamples; i++){
    //Set the current value of output
    float currentSample = 0.15f * (float) std::sin(currentPhase * 2 * M_PI);

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