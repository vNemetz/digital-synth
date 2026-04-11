#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include <AudioSource/SynthAudioSource.hpp>

int main(int argc, char *argv[])
{
	int waveform = 0;
	std::cout << "Select waveform (0=Sine, 1=Square, 2=Sawtooth, 3=Triangle, 4=White Noise): ";
	std::cin >> waveform;
	std::cin.ignore();

	WaveformType wave;
	if      (waveform == 0) wave = WaveformType::Sine;
	else if (waveform == 1) wave = WaveformType::Square;
	else if (waveform == 2) wave = WaveformType::Sawtooth;
	else if (waveform == 3) wave = WaveformType::Triangle;
	else 										wave = WaveformType::WhiteNoise;
	juce::AudioDeviceManager audioDeviceManager;
	SynthAudioSource synthEngine(wave);

	audioDeviceManager.initialiseWithDefaultDevices(0, 2);
	audioDeviceManager.addAudioCallback(&synthEngine);

	std::cout << "Playing... press Enter to stop." << std::endl;
	std::cin.get();

	audioDeviceManager.removeAudioCallback(&synthEngine);

	return 0;
}