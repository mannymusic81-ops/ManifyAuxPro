#pragma once
#include <JuceHeader.h>

class ModeSampler {
public:
    ModeSampler() { formatManager.registerBasicFormats(); }

    void prepare (double sampleRate, int samplesPerBlock, int channels)
    {
        juce::dsp::ProcessSpec spec { sampleRate, (juce::uint32) samplesPerBlock, (juce::uint32) channels };
        synth.clearVoices();
        for (int i = 0; i < 16; ++i)
            synth.addVoice (new juce::SamplerVoice());
        sr = sampleRate;
    }

    bool loadSampleFromFile (const juce::File& file)
    {
        if (! file.existsAsFile()) return false;
        std::unique_ptr<juce::AudioFormatReader> reader (formatManager.createReaderFor (file));
        if (! reader) return false;
        return setReaderAsSound (std::move(reader));
    }

    bool loadSampleFromBinary (const void* data, size_t dataSize)
    {
        std::unique_ptr<juce::InputStream> stream (new juce::MemoryInputStream (data, dataSize, false));
        std::unique_ptr<juce::AudioFormatReader> reader (formatManager.createReaderFor (std::move(stream)));
        if (! reader) return false;
        return setReaderAsSound (std::move(reader));
    }

    void process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
    {
        synth.renderNextBlock (buffer, midi, 0, buffer.getNumSamples());
    }

private:
    bool setReaderAsSound (std::unique_ptr<juce::AudioFormatReader> reader)
    {
        juce::BigInteger allNotes; allNotes.setRange (0, 128, true);
        auto* sound = new juce::SamplerSound ("modeSound", *reader, allNotes, 60, 0.0, 0.0, 10.0);
        synth.clearSounds();
        synth.addSound (sound);
        return true;
    }

    double sr {44100.0};
    juce::Synthesiser synth;
    juce::AudioFormatManager formatManager;
};
