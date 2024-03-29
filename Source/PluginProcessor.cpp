/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PfmProject0AudioProcessor::PfmProject0AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
aptvs(*this, nullptr )
{
	//shouldPlaySound = new AudioParameterBool("ShouldPlaySoundParam", "shouldPlaySound", false);
	//addParameter(shouldPlaySound);

	auto shouldPlaySoundParam = std::make_unique<AudioParameterBool>("ShouldPlaySoundParam", "shouldPlaySound", false);
	auto* param = aptvs.createAndAddParameter(std::move(shouldPlaySoundParam));
	shouldPlaySound = dynamic_cast<AudioParameterBool*>(param);

	auto bgColorParam = std::make_unique<AudioParameterFloat>("bg color", "bgcolor", 0.f, 1.f, 0.5f);
	param = aptvs.createAndAddParameter(std::move(bgColorParam));
	bgColor = dynamic_cast<AudioParameterFloat*>(param);
	aptvs.state = ValueTree("PfmSynthValueTree");
	
}

PfmProject0AudioProcessor::~PfmProject0AudioProcessor()
{
}

//==============================================================================
const String PfmProject0AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PfmProject0AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PfmProject0AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PfmProject0AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PfmProject0AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PfmProject0AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PfmProject0AudioProcessor::getCurrentProgram()
{
    return 0;
}

void PfmProject0AudioProcessor::setCurrentProgram (int index)
{
}

const String PfmProject0AudioProcessor::getProgramName (int index)
{
    return {};
}

void PfmProject0AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PfmProject0AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PfmProject0AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PfmProject0AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PfmProject0AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.


    /*for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }*/
	
	for (int i = 0; i < buffer.getNumSamples(); ++i)
	{
		for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
		{
			if (shouldPlaySound->get())
			{
				buffer.setSample(channel, i, (r.nextFloat()*0.0025));
			}
			else
			{
				buffer.setSample(channel, i, 0);
			}
		}
	}

}

//==============================================================================
bool PfmProject0AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PfmProject0AudioProcessor::createEditor()
{
    return new PfmProject0AudioProcessorEditor (*this);
}

//==============================================================================
void PfmProject0AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	DBG(aptvs.state.toXmlString());
	MemoryOutputStream mos(destData, false);
	aptvs.state.writeToStream(mos);

}

void PfmProject0AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
	if (tree.isValid())
	{
		aptvs.state = tree;
	}
	DBG(aptvs.state.toXmlString());
}

void PfmProject0AudioProcessor::updateAutoParam(RangedAudioParameter* param, float value)
{
	param->beginChangeGesture();
	param->setValueNotifyingHost(value);
	param->endChangeGesture();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PfmProject0AudioProcessor();
}
