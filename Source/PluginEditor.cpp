#include "PluginEditor.h"
#include "PluginProcessor.h"

MaNiFyAuxProAudioProcessorEditor::MaNiFyAuxProAudioProcessorEditor (MaNiFyAuxProAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    setSize (600, 340);

    title.setText ("MaNiFy Aux Pro", juce::dontSendNotification);
    title.setJustificationType (juce::Justification::centredLeft);
    title.setFont (juce::Font (20.0f, juce::Font::bold));
    addAndMakeVisible (title);

    for (auto* b : { &padBtn, &bellBtn, &ambBtn, &hitBtn, &pluckBtn })
    {
        addAndMakeVisible (*b);
        b->addListener (this);
    }
}

MaNiFyAuxProAudioProcessorEditor::~MaNiFyAuxProAudioProcessorEditor() {}

void MaNiFyAuxProAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xFF0f1216));

    // header
    g.setColour (juce::Colour (0xFFd6b46b));
    g.fillRect (0, 0, getWidth(), 48);

    g.setColour (juce::Colours::black);
    g.setFont (juce::Font (18.0f, juce::Font::bold));
    g.drawText ("MaNiFy", 12, 10, 100, 28, juce::Justification::centredLeft);

    // mode card
    auto area = getLocalBounds().reduced (16).withTrimmedTop (64).removeFromTop (140);
    g.setColour (juce::Colour (0xFF1c2127));
    g.fillRoundedRectangle (area.toFloat(), 14.0f);
    g.setColour (juce::Colours::white.withAlpha (flashAlpha));
    g.setFont (juce::Font (44.0f, juce::Font::bold));
    g.drawText (processor.getCurrentModeName(), area, juce::Justification::centred);
}

void MaNiFyAuxProAudioProcessorEditor::resized()
{
    auto r = getLocalBounds();
    title.setBounds (r.removeFromTop (48).reduced (12));

    auto row = r.removeFromBottom (84).reduced (12);
    auto w = row.getWidth() / 5;
    padBtn.setBounds   (row.removeFromLeft (w).reduced (6));
    bellBtn.setBounds  (row.removeFromLeft (w).reduced (6));
    ambBtn.setBounds   (row.removeFromLeft (w).reduced (6));
    hitBtn.setBounds   (row.removeFromLeft (w).reduced (6));
    pluckBtn.setBounds (row.removeFromLeft (w).reduced (6));
}

void MaNiFyAuxProAudioProcessorEditor::startFlash()
{
    flashAlpha = 1.0f;
    struct FlashTimer : juce::Timer {
        MaNiFyAuxProAudioProcessorEditor* ed { nullptr };
        void timerCallback() override {
            ed->flashAlpha = juce::jmax (0.4f, ed->flashAlpha - 0.06f);
            ed->repaint();
            if (ed->flashAlpha <= 0.41f) stopTimer();
        }
    };
    static FlashTimer t; t.ed = this; t.startTimerHz (30);
}

void MaNiFyAuxProAudioProcessorEditor::buttonClicked(juce::Button* b)
{
    using Mode = MaNiFyAuxProAudioProcessor::Mode;
    if      (b == &padBtn)   processor.forceMode (Mode::Pads);
    else if (b == &bellBtn)  processor.forceMode (Mode::Bells);
    else if (b == &ambBtn)   processor.forceMode (Mode::Ambient);
    else if (b == &hitBtn)   processor.forceMode (Mode::Hits);
    else if (b == &pluckBtn) processor.forceMode (Mode::Pluck);
    startFlash();
}
