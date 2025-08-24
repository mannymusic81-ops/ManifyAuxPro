#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class MaNiFyAuxProAudioProcessorEditor : public juce::AudioProcessorEditor,
                                         private juce::Button::Listener
{
public:
    MaNiFyAuxProAudioProcessorEditor (MaNiFyAuxProAudioProcessor&);
    ~MaNiFyAuxProAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void buttonClicked(juce::Button* b) override;
    void startFlash();

    MaNiFyAuxProAudioProcessor& processor;

    juce::Label title;
    juce::TextButton padBtn {"Pads"}, bellBtn {"Bells"},
                     ambBtn {"Ambient"}, hitBtn {"Hits"}, pluckBtn {"Pluck"};
    float flashAlpha = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MaNiFyAuxProAudioProcessorEditor)
};
