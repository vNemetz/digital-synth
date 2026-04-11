#pragma once

#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_processors/juce_audio_processors.h>


enum class WaveformType {
    Sine,
    Square,
    Sawtooth,
    Triangle,
		WhiteNoise,
};

class SynthAudioSource : public juce::AudioIODeviceCallback{
private:
	double currentPhase = 0.0f;
  double phaseIncrement = 0.0f;
	WaveformType waveform = WaveformType::Sine;

	juce::Random randomGenerator;
	
public: 

	SynthAudioSource(WaveformType waveform);
	void audioDeviceIOCallbackWithContext (
    const float* const* inputChannelData,
		int numInputChannels,
	  float* const* outputChannelData,
		int numOutputChannels,
		int numSamples,
		const juce::AudioIODeviceCallbackContext& context) override;

	void audioDeviceAboutToStart (juce::AudioIODevice* device) override;
	void audioDeviceStopped() override;

};