/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PfmProject0AudioProcessorEditor::PfmProject0AudioProcessorEditor (PfmProject0AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	cachedBgColor = processor.bgColor->get();
	startTimerHz(20);
    setSize (400, 300);
}

PfmProject0AudioProcessorEditor::~PfmProject0AudioProcessorEditor()
{
	PfmProject0AudioProcessor::updateAutoParam(processor.shouldPlaySound, false);
	
}


void PfmProject0AudioProcessorEditor::timerCallback()
{
	updateBG();
}

void PfmProject0AudioProcessorEditor::updateBG()
{
	cachedBgColor = processor.bgColor->get();
	repaint();
}

//==============================================================================
void PfmProject0AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId).interpolatedWith(Colours::red,cachedBgColor));

    g.setColour (Colours::seagreen);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void PfmProject0AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void PfmProject0AudioProcessorEditor::mouseDown(const MouseEvent& e)
{
	
	//PfmProject0AudioProcessor::updateAutoParam(processor.shouldPlaySound, !processor.shouldPlaySound->get());
	lastClickPos = e.getPosition();
}

void PfmProject0AudioProcessorEditor::mouseUp(const MouseEvent& e)
{
	//processor.shouldPlaySound = false;
}

void PfmProject0AudioProcessorEditor::mouseDrag(const MouseEvent& e)
{
	auto clickPos = e.getPosition();
	auto difY = jmap((double)clickPos.y, 0.0, (double)getHeight(), 1.0, 0.0);
	difY = jlimit(0.0, 1.0, difY);
	//DBG("diffY" << difY);

	PfmProject0AudioProcessor::updateAutoParam(processor.bgColor, difY);
	updateBG();
}
