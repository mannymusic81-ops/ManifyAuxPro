#pragma once
#include <JuceHeader.h>
#include "SamplerEngine.h"

class MaNiFyAuxProAudioProcessor  : public juce::AudioProcessor
{
public:
    enum class Mode { Pads, Bells, Ambient, Hits, Pluck };

    MaNiFyAuxProAudioProcessor();
    ~MaNiFyAuxProAudioProcessor() override = default;

    //==============================================================================
    const juce::String getName() const override { return "MaNiFy Aux Pro"; }
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override { return true; }
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    //==============================================================================
    double getTailLengthSeconds() const override { return 0.0; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}
    void getStateInformation (juce::MemoryBlock&) override {}
    void setStateInformation (const void*, int) override {}

    //==============================================================================
    const juce::String getCurrentModeName() const;
    void forceMode (Mode m) { currentMode = m; }

private:
    void analyseMidi (const juce::MidiBuffer& midi);

    Mode currentMode { Mode::Pads };

    ModeSampler pads, bells, ambient, hits, pluck;
    double sr {44100.0};
};
