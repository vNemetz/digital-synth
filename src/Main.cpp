#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_processors/juce_audio_processors.h>

class SimpleSynth : public juce::AudioSource {
public:
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override {
        currentSampleRate = sampleRate;
        phase = 0.0;
        sampleCount = 0;
        noteIndex = 0;
        
        // Define uma melodia (Frequências em Hz)
        melody = { 261.63, 329.63, 392.00, 493.88, 523.26, 493.88, 392.00, 329.63}; // C4, E4, G4, B4, C5
        updateDelta();
    }

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override {
        // Quantas amostras cada nota deve durar (ex: 0.5 segundos)
        int samplesPerNote = (int)(currentSampleRate * 0.2);

        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample) {
            // Lógica do Sequenciador
            sampleCount++;
            if (sampleCount >= samplesPerNote) {
                sampleCount = 0;
                noteIndex = (noteIndex + 1) % melody.size(); // Vai para a próxima nota
                updateDelta();
            }

            // Geração de Áudio (Onda Senoidal)
            auto level = (float) std::sin (phase);
            
            for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
                bufferToFill.buffer->setSample (channel, bufferToFill.startSample + sample, level * 0.1f);
            }
            
            phase += wtDelta;
            if (phase > juce::MathConstants<double>::twoPi)
                phase -= juce::MathConstants<double>::twoPi;
        }
    }

    void releaseResources() override {}

private:
    void updateDelta() {
        double frequency = melody[noteIndex];
        wtDelta = (frequency * 2.0 * juce::MathConstants<double>::pi) / currentSampleRate;
    }

    double currentSampleRate = 0.0;
    double phase = 0.0;
    double wtDelta = 0.0;
    
    int sampleCount = 0;
    int noteIndex = 0;
    std::vector<double> melody;
};

int main (int argc, char* argv[])
{
    juce::ScopedJuceInitialiser_GUI initialiser;
    juce::AudioDeviceManager deviceManager;

    // Tenta inicializar com as configurações padrão do sistema (PulseAudio/PipeWire)
    // Passamos nullptr para que o JUCE escolha o melhor XML de configuração padrão
    auto error = deviceManager.initialiseWithDefaultDevices (0, 2);

    if (error.isNotEmpty())
    {
        std::cerr << "Erro ao abrir dispositivo: " << error << std::endl;
        return 1;
    }

    SimpleSynth mySynth;
    juce::AudioSourcePlayer player;
    player.setSource (&mySynth);
    
    // Adiciona o callback ao deviceManager
    deviceManager.addAudioCallback (&player);

    std::cout << "Synth tocando via System Audio... Pressione Enter para parar." << std::endl;
    std::cin.get();

    deviceManager.removeAudioCallback (&player);
    return 0;
}