#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include <AudioSource/SynthAudioSource.hpp>

int main(int argc, char *argv[])
{
	juce::AudioDeviceManager audioDeviceManager;
	SynthAudioSource synthEngine;

	audioDeviceManager.initialiseWithDefaultDevices(0, 2);

	audioDeviceManager.addAudioCallback(&synthEngine);

	std::cin.get();

	audioDeviceManager.removeAudioCallback(&synthEngine);

	return 0;
}