/* ----------------------------------------------------------------------------

   Squeezer
   ========
   Flexible general-purpose audio compressor with a touch of lemon.

   Copyright (c) 2013-2015 Martin Zuther (http://www.mzuther.de/)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   Thank you for using free software!

---------------------------------------------------------------------------- */

#include "plugin_editor_squeezer.h"

//==============================================================================
SqueezerAudioProcessorEditor::SqueezerAudioProcessorEditor(SqueezerAudioProcessor *ownerFilter, SqueezerPluginParameters *parameters, int channels)
    : AudioProcessorEditor(ownerFilter)
{
    // the editor window does not have any transparent areas
    // (increases performance on redrawing)
    setOpaque(true);

    // The plug-in editor's size as well as the location of buttons
    // and labels will be set later on in this constructor.

    pProcessor = ownerFilter;
    pProcessor->addActionListener(this);

    nChannels = channels;

    ButtonBypass = new TextButton("Bypass");
    ButtonBypass->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonBypass->setColour(TextButton::buttonOnColourId, Colours::red);

    ButtonBypass->addListener(this);
    addAndMakeVisible(ButtonBypass);


    ButtonDetectorRmsPeak = new TextButton("Peak");
    ButtonDetectorRmsPeak->setRadioGroupId(1);
    ButtonDetectorRmsPeak->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonDetectorRmsPeak->setColour(TextButton::buttonOnColourId, Colours::yellow.withRotatedHue(+0.08f));

    ButtonDetectorRmsPeak->addListener(this);
    addAndMakeVisible(ButtonDetectorRmsPeak);


    ButtonDetectorRmsFast = new TextButton("Fast");
    ButtonDetectorRmsFast->setRadioGroupId(1);
    ButtonDetectorRmsFast->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonDetectorRmsFast->setColour(TextButton::buttonOnColourId, Colours::yellow);

    ButtonDetectorRmsFast->addListener(this);
    addAndMakeVisible(ButtonDetectorRmsFast);


    ButtonDetectorRmsMedium = new TextButton("Medium");
    ButtonDetectorRmsMedium->setRadioGroupId(1);
    ButtonDetectorRmsMedium->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonDetectorRmsMedium->setColour(TextButton::buttonOnColourId, Colours::yellow.withRotatedHue(-0.08f));

    ButtonDetectorRmsMedium->addListener(this);
    addAndMakeVisible(ButtonDetectorRmsMedium);


    ButtonDetectorRmsSlow = new TextButton("Slow");
    ButtonDetectorRmsSlow->setRadioGroupId(1);
    ButtonDetectorRmsSlow->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonDetectorRmsSlow->setColour(TextButton::buttonOnColourId, Colours::yellow.withRotatedHue(-0.16f));

    ButtonDetectorRmsSlow->addListener(this);
    addAndMakeVisible(ButtonDetectorRmsSlow);


    ButtonDesignFeedForward = new TextButton("F.Forw");
    ButtonDesignFeedForward->setRadioGroupId(2);
    ButtonDesignFeedForward->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonDesignFeedForward->setColour(TextButton::buttonOnColourId, Colours::yellow);

    ButtonDesignFeedForward->addListener(this);
    addAndMakeVisible(ButtonDesignFeedForward);


    ButtonDesignFeedBack = new TextButton("F.Back");
    ButtonDesignFeedBack->setRadioGroupId(2);
    ButtonDesignFeedBack->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonDesignFeedBack->setColour(TextButton::buttonOnColourId, Colours::yellow.withRotatedHue(-0.08f));

    ButtonDesignFeedBack->addListener(this);
    addAndMakeVisible(ButtonDesignFeedBack);


    ButtonDetectorLinear = new TextButton("Linear");
    ButtonDetectorLinear->setRadioGroupId(3);
    ButtonDetectorLinear->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonDetectorLinear->setColour(TextButton::buttonOnColourId, Colours::yellow.withRotatedHue(+0.08f));

    ButtonDetectorLinear->addListener(this);
    addAndMakeVisible(ButtonDetectorLinear);


    ButtonDetectorSmoothDecoupled = new TextButton("S-Curve");
    ButtonDetectorSmoothDecoupled->setRadioGroupId(3);
    ButtonDetectorSmoothDecoupled->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonDetectorSmoothDecoupled->setColour(TextButton::buttonOnColourId, Colours::yellow);

    ButtonDetectorSmoothDecoupled->addListener(this);
    addAndMakeVisible(ButtonDetectorSmoothDecoupled);


    ButtonDetectorSmoothBranching = new TextButton("Log");
    ButtonDetectorSmoothBranching->setRadioGroupId(3);
    ButtonDetectorSmoothBranching->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonDetectorSmoothBranching->setColour(TextButton::buttonOnColourId, Colours::yellow.withRotatedHue(-0.08f));

    ButtonDetectorSmoothBranching->addListener(this);
    addAndMakeVisible(ButtonDetectorSmoothBranching);


    ButtonGainStageFET = new TextButton("FET");
    ButtonGainStageFET->setRadioGroupId(4);
    ButtonGainStageFET->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonGainStageFET->setColour(TextButton::buttonOnColourId, Colours::yellow);

    ButtonGainStageFET->addListener(this);
    addAndMakeVisible(ButtonGainStageFET);


    ButtonGainStageOptical = new TextButton("Opto");
    ButtonGainStageOptical->setRadioGroupId(4);
    ButtonGainStageOptical->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonGainStageOptical->setColour(TextButton::buttonOnColourId, Colours::yellow.withRotatedHue(-0.08f));

    ButtonGainStageOptical->addListener(this);
    addAndMakeVisible(ButtonGainStageOptical);


    int nIndex = SqueezerPluginParameters::selThreshold;
    int nIndexSwitch = SqueezerPluginParameters::selThresholdSwitch;
    String strName = parameters->getName(nIndex);
    SliderThresholdCombined = new SliderCombined(strName, parameters, nIndex, nIndexSwitch);
    SliderThresholdCombined->setSliderColour(Colours::purple.brighter(0.2f));

    SliderThresholdCombined->addListener(this);
    SliderThresholdCombined->addButtonListener(this);
    addAndMakeVisible(SliderThresholdCombined);


    nIndex = SqueezerPluginParameters::selRatio;
    nIndexSwitch = SqueezerPluginParameters::selRatioSwitch;
    strName = parameters->getName(nIndex);
    SliderRatioCombined = new SliderCombined(strName, parameters, nIndex, nIndexSwitch);
    SliderRatioCombined->setSliderColour(Colours::purple.brighter(0.2f));

    SliderRatioCombined->addListener(this);
    SliderRatioCombined->addButtonListener(this);
    addAndMakeVisible(SliderRatioCombined);

    nIndex = SqueezerPluginParameters::selKneeWidth;
    nIndexSwitch = SqueezerPluginParameters::selKneeWidthSwitch;
    strName = parameters->getName(nIndex);
    SliderKneeWidthCombined = new SliderCombined(strName, parameters, nIndex, nIndexSwitch);
    SliderKneeWidthCombined->setSliderColour(Colours::purple.brighter(0.2f));

    SliderKneeWidthCombined->addListener(this);
    SliderKneeWidthCombined->addButtonListener(this);
    addAndMakeVisible(SliderKneeWidthCombined);


    nIndex = SqueezerPluginParameters::selAttackRate;
    nIndexSwitch = SqueezerPluginParameters::selAttackRateSwitch;
    strName = parameters->getName(nIndex);
    SliderAttackRateCombined = new SliderCombined(strName, parameters, nIndex, nIndexSwitch);
    SliderAttackRateCombined->setSliderColour(Colours::yellow);

    SliderAttackRateCombined->addListener(this);
    SliderAttackRateCombined->addButtonListener(this);
    addAndMakeVisible(SliderAttackRateCombined);


    nIndex = SqueezerPluginParameters::selReleaseRate;
    nIndexSwitch = SqueezerPluginParameters::selReleaseRateSwitch;
    strName = parameters->getName(nIndex);
    SliderReleaseRateCombined = new SliderCombined(strName, parameters, nIndex, nIndexSwitch);
    SliderReleaseRateCombined->setSliderColour(Colours::yellow);

    SliderReleaseRateCombined->addListener(this);
    SliderReleaseRateCombined->addButtonListener(this);
    addAndMakeVisible(SliderReleaseRateCombined);


#ifdef SQUEEZER_STEREO
    nIndex = SqueezerPluginParameters::selStereoLink;
    nIndexSwitch = SqueezerPluginParameters::selStereoLinkSwitch;
    strName = parameters->getName(nIndex);
    SliderStereoLinkCombined = new SliderCombined(strName, parameters, nIndex, nIndexSwitch);
    SliderStereoLinkCombined->setSliderColour(Colours::purple.brighter(0.2f));

    SliderStereoLinkCombined->addListener(this);
    SliderStereoLinkCombined->addButtonListener(this);
    addAndMakeVisible(SliderStereoLinkCombined);
#endif


    ButtonAutoMakeupGain = new TextButton("Auto MU");
    ButtonAutoMakeupGain->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonAutoMakeupGain->setColour(TextButton::buttonOnColourId, Colours::yellow);

    ButtonAutoMakeupGain->addListener(this);
    addAndMakeVisible(ButtonAutoMakeupGain);


    nIndex = SqueezerPluginParameters::selMakeupGain;
    nIndexSwitch = SqueezerPluginParameters::selMakeupGainSwitch;
    strName = parameters->getName(nIndex);
    SliderMakeupGainCombined = new SliderCombined(strName, parameters, nIndex, nIndexSwitch);
    SliderMakeupGainCombined->setSliderColour(Colours::blue.brighter(0.4f));

    SliderMakeupGainCombined->addListener(this);
    SliderMakeupGainCombined->addButtonListener(this);
    addAndMakeVisible(SliderMakeupGainCombined);


    nIndex = SqueezerPluginParameters::selWetMix;
    nIndexSwitch = SqueezerPluginParameters::selWetMixSwitch;
    strName = parameters->getName(nIndex);
    SliderWetMixCombined = new SliderCombined(strName, parameters, nIndex, nIndexSwitch);
    SliderWetMixCombined->setSliderColour(Colours::blue.brighter(0.4f));

    SliderWetMixCombined->addListener(this);
    SliderWetMixCombined->addButtonListener(this);
    addAndMakeVisible(SliderWetMixCombined);


    ButtonSidechainFilterState = new TextButton("Filter");
    ButtonSidechainFilterState->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonSidechainFilterState->setColour(TextButton::buttonOnColourId, Colours::green);

    ButtonSidechainFilterState->addListener(this);
    addAndMakeVisible(ButtonSidechainFilterState);


    nIndex = SqueezerPluginParameters::selSidechainFilterCutoff;
    nIndexSwitch = SqueezerPluginParameters::selSidechainFilterCutoffSwitch;
    strName = parameters->getName(nIndex);
    SliderSidechainFilterCutoffCombined = new SliderCombined(strName, parameters, nIndex, nIndexSwitch);
    SliderSidechainFilterCutoffCombined->setSliderColour(Colours::green.brighter(0.1f));

    SliderSidechainFilterCutoffCombined->addListener(this);
    SliderSidechainFilterCutoffCombined->addButtonListener(this);
    addAndMakeVisible(SliderSidechainFilterCutoffCombined);


    nIndex = SqueezerPluginParameters::selSidechainFilterGain;
    strName = parameters->getName(nIndex);
    SliderSidechainFilterGain = new SliderSwitchLinearBar(strName, parameters, nIndex);
    SliderSidechainFilterGain->setSliderColour(Colours::green.brighter(0.1f));

    SliderSidechainFilterGain->addListener(this);
    addAndMakeVisible(SliderSidechainFilterGain);


    ButtonSidechainListen = new TextButton("Listen");
    ButtonSidechainListen->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonSidechainListen->setColour(TextButton::buttonOnColourId, Colours::red);

    ButtonSidechainListen->addListener(this);
    addAndMakeVisible(ButtonSidechainListen);


#ifdef DEBUG
    LabelDebug = new Label("Debug Notification", "dbg");
    LabelDebug->setColour(Label::textColourId, Colours::red);
    LabelDebug->setJustificationType(Justification::centred);
    addAndMakeVisible(LabelDebug);
#else
    LabelDebug = nullptr;
#endif


    ButtonResetMeters = new TextButton("Reset");
    ButtonResetMeters->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonResetMeters->setColour(TextButton::buttonOnColourId, Colours::red);

    ButtonResetMeters->addListener(this);
    addAndMakeVisible(ButtonResetMeters);


    ButtonSettings = new TextButton("Settings");
    ButtonSettings->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonSettings->setColour(TextButton::buttonOnColourId, Colours::yellow);

    ButtonSettings->addListener(this);
    addAndMakeVisible(ButtonSettings);


    ButtonAbout = new TextButton("About");
    ButtonAbout->setColour(TextButton::buttonColourId, Colours::grey);
    ButtonAbout->setColour(TextButton::buttonOnColourId, Colours::yellow);

    ButtonAbout->addListener(this);
    addAndMakeVisible(ButtonAbout);


    pInputLevelMeters = new MeterBarLevel*[nChannels];
    pOutputLevelMeters = new MeterBarLevel*[nChannels];
    pGainReductionMeters = new MeterBarGainReduction*[nChannels];

    int y = 20;

#ifdef SQUEEZER_STEREO
    int x = 610;
    int x_spacing = 28;
    int width = 12;
#else
    int x = 570;
    int x_spacing = 20;
    int width = 16;
#endif

    int nNumberOfBars = 24;

    for (int nChannel = 0; nChannel < nChannels; nChannel++)
    {
        pInputLevelMeters[nChannel] = new MeterBarLevel("Input Level Meter #" + String(nChannel), x, y, width, nNumberOfBars - 2, 5, 20.0f);
        addAndMakeVisible(pInputLevelMeters[nChannel]);

        pOutputLevelMeters[nChannel] = new MeterBarLevel("Output Level Meter #" + String(nChannel), x + 2 * x_spacing, y, width, nNumberOfBars - 2, 5, 20.0f);
        addAndMakeVisible(pOutputLevelMeters[nChannel]);

        pGainReductionMeters[nChannel] = new MeterBarGainReduction("Gain Reduction Meter #" + String(nChannel), x + x_spacing, y, width, nNumberOfBars, 5);
        addAndMakeVisible(pGainReductionMeters[nChannel]);

        x += width;
    }


    // This is where our plug-in editor's size is set.
    resizeEditor();

    updateParameter(SqueezerPluginParameters::selBypass);
    updateParameter(SqueezerPluginParameters::selDetectorRmsFilter);
    updateParameter(SqueezerPluginParameters::selDesign);
    updateParameter(SqueezerPluginParameters::selDetector);
    updateParameter(SqueezerPluginParameters::selGainStage);

    updateParameter(SqueezerPluginParameters::selThresholdSwitch);
    updateParameter(SqueezerPluginParameters::selThreshold);
    updateParameter(SqueezerPluginParameters::selRatioSwitch);
    updateParameter(SqueezerPluginParameters::selRatio);
    updateParameter(SqueezerPluginParameters::selKneeWidthSwitch);
    updateParameter(SqueezerPluginParameters::selKneeWidth);

    updateParameter(SqueezerPluginParameters::selAttackRateSwitch);
    updateParameter(SqueezerPluginParameters::selAttackRate);
    updateParameter(SqueezerPluginParameters::selReleaseRateSwitch);
    updateParameter(SqueezerPluginParameters::selReleaseRate);

#ifdef SQUEEZER_STEREO
    updateParameter(SqueezerPluginParameters::selStereoLinkSwitch);
    updateParameter(SqueezerPluginParameters::selStereoLink);
#endif

    updateParameter(SqueezerPluginParameters::selAutoMakeupGain);
    updateParameter(SqueezerPluginParameters::selMakeupGainSwitch);
    updateParameter(SqueezerPluginParameters::selMakeupGain);
    updateParameter(SqueezerPluginParameters::selWetMixSwitch);
    updateParameter(SqueezerPluginParameters::selWetMix);

    updateParameter(SqueezerPluginParameters::selSidechainFilterState);
    updateParameter(SqueezerPluginParameters::selSidechainFilterCutoffSwitch);
    updateParameter(SqueezerPluginParameters::selSidechainFilterCutoff);
    updateParameter(SqueezerPluginParameters::selSidechainFilterGain);
    updateParameter(SqueezerPluginParameters::selSidechainListen);
}


SqueezerAudioProcessorEditor::~SqueezerAudioProcessorEditor()
{
    pProcessor->removeActionListener(this);

    for (int nChannel = 0; nChannel < nChannels; nChannel++)
    {
        delete pInputLevelMeters[nChannel];
        pInputLevelMeters[nChannel] = nullptr;

        delete pOutputLevelMeters[nChannel];
        pOutputLevelMeters[nChannel] = nullptr;

        delete pGainReductionMeters[nChannel];
        pGainReductionMeters[nChannel] = nullptr;
    }

    delete[] pInputLevelMeters;
    pInputLevelMeters = nullptr;

    delete[] pOutputLevelMeters;
    pOutputLevelMeters = nullptr;

    delete[] pGainReductionMeters;
    pGainReductionMeters = nullptr;

    deleteAllChildren();
}


void SqueezerAudioProcessorEditor::resizeEditor()
{
    nHeight = 188;

#ifdef SQUEEZER_STEREO
    nWidth = 710;
#else
    nWidth = 646;
#endif

    int x = 15;
    int y1 = 18;
    int y2 = y1 + 78;

    setSize(nWidth, nHeight);

    ButtonDetectorRmsPeak->setBounds(x + 37, y2, 52, 20);
    ButtonDetectorRmsFast->setBounds(x + 97, y2, 52, 20);
    ButtonDetectorRmsMedium->setBounds(x + 157, y2, 52, 20);
    ButtonDetectorRmsSlow->setBounds(x + 217, y2, 52, 20);

    ButtonDesignFeedForward->setBounds(x + 22, y2 + 25, 52, 20);
    ButtonDesignFeedBack->setBounds(x + 82, y2 + 25, 52, 20);

    ButtonGainStageFET->setBounds(x + 172, y2 + 25, 52, 20);
    ButtonGainStageOptical->setBounds(x + 232, y2 + 25, 52, 20);

    ButtonDetectorLinear->setBounds(x + 67, y2 + 50, 52, 20);
    ButtonDetectorSmoothDecoupled->setBounds(x + 127, y2 + 50, 52, 20);
    ButtonDetectorSmoothBranching->setBounds(x + 187, y2 + 50, 52, 20);

    SliderThresholdCombined->setBounds(x, y1, 52, 60);
    SliderRatioCombined->setBounds(x + 60, y1, 52, 60);
    SliderKneeWidthCombined->setBounds(x + 120, y1, 52, 60);

    SliderAttackRateCombined->setBounds(x + 195, y1, 52, 60);
    SliderReleaseRateCombined->setBounds(x + 255, y1, 52, 60);

    SliderSidechainFilterCutoffCombined->setBounds(x + 330, y1, 52, 60);
    SliderSidechainFilterGain->setBounds(x + 330, y2 + 26, 52, 18);
    ButtonSidechainFilterState->setBounds(x + 330, y2, 52, 20);
    ButtonSidechainListen->setBounds(x + 330, y2 + 50, 52, 20);

#ifdef SQUEEZER_STEREO
    SliderStereoLinkCombined->setBounds(x + 405, y1, 52, 60);

    SliderMakeupGainCombined->setBounds(x + 465, y1, 52, 60);
    SliderWetMixCombined->setBounds(x + 525, y1, 52, 60);

    ButtonAutoMakeupGain->setBounds(x + 465, y2, 52, 20);
    ButtonAbout->setBounds(x + 435, y2 + 25, 52, 20);
    ButtonSettings->setBounds(x + 495, y2 + 25, 52, 20);
    ButtonBypass->setBounds(x + 465, y2 + 50, 52, 20);

    ButtonResetMeters->setBounds(x + 611, y2 + 50, 52, 20);

#else
    SliderMakeupGainCombined->setBounds(x + 415, y1, 52, 60);
    SliderWetMixCombined->setBounds(x + 475, y1, 52, 60);

    ButtonAutoMakeupGain->setBounds(x + 445, y2, 52, 20);
    ButtonAbout->setBounds(x + 415, y2 + 25, 52, 20);
    ButtonSettings->setBounds(x + 475, y2 + 25, 52, 20);
    ButtonBypass->setBounds(x + 445, y2 + 50, 52, 20);

    ButtonResetMeters->setBounds(x + 557, y2 + 50, 52, 20);

#endif

    if (LabelDebug)
    {
        LabelDebug->setBounds(x + 127, y2 + 26, 52, 16);
    }
}


void SqueezerAudioProcessorEditor::actionListenerCallback(const String &strMessage)
{
    // "PC" --> parameter changed, followed by a hash and the
    // parameter's ID
    if (strMessage.startsWith("PC#"))
    {
        String strIndex = strMessage.substring(3);
        int nIndex = strIndex.getIntValue();
        jassert(nIndex >= 0);
        jassert(nIndex < pProcessor->getNumParameters());

        if (pProcessor->hasChanged(nIndex))
        {
            updateParameter(nIndex);
        }
    }
    // "UM" --> update meters
    else if (!strMessage.compare("UM"))
    {
        for (int nChannel = 0; nChannel < nChannels; nChannel++)
        {
            float fPeakInputLevel = pProcessor->getPeakMeterInputLevel(nChannel);
            float fAverageInputLevel = pProcessor->getAverageMeterInputLevel(nChannel);
            float fPeakInputPeakLevel = pProcessor->getPeakMeterPeakInputLevel(nChannel);
            float fMaximumInputLevel = pProcessor->getMaximumInputLevel(nChannel);

            pInputLevelMeters[nChannel]->setLevel(fPeakInputLevel, fAverageInputLevel, fPeakInputPeakLevel, fMaximumInputLevel);

            float fPeakOutputLevel = pProcessor->getPeakMeterOutputLevel(nChannel);
            float fAverageOutputLevel = pProcessor->getAverageMeterOutputLevel(nChannel);
            float fPeakOutputPeakLevel = pProcessor->getPeakMeterPeakOutputLevel(nChannel);
            float fMaximumOutputLevel = pProcessor->getMaximumOutputLevel(nChannel);

            pOutputLevelMeters[nChannel]->setLevel(fPeakOutputLevel, fAverageOutputLevel, fPeakOutputPeakLevel, fMaximumOutputLevel);

            float fGainReduction = pProcessor->getGainReduction(nChannel);
            float fGainReductionPeak = pProcessor->getGainReductionPeak(nChannel);

            // make sure gain reduction meter doesn't show anything
            // while there is no gain reduction
            fGainReduction -= 0.01f;
            fGainReductionPeak -= 0.01f;

            pGainReductionMeters[nChannel]->setGainReduction(fGainReduction, fGainReductionPeak);
        }
    }
    else
    {
        DBG("[Squeezer] Received unknown action message \"" + strMessage + "\".");
    }
}


void SqueezerAudioProcessorEditor::updateParameter(int nIndex)
{
    float fValue = pProcessor->getParameter(nIndex);
    pProcessor->clearChangeFlag(nIndex);

    switch (nIndex)
    {
    case SqueezerPluginParameters::selBypass:
        ButtonBypass->setToggleState(fValue != 0.0f, dontSendNotification);
        break;

    case SqueezerPluginParameters::selDetectorRmsFilter:

        if (fValue == (Compressor::DetectorRmsFilterPeak / float(Compressor::NumberOfDetectorRmsFilters - 1)))
        {
            ButtonDetectorRmsPeak->setToggleState(true, dontSendNotification);
        }
        else if (fValue == (Compressor::DetectorRmsFilterFast / float(Compressor::NumberOfDetectorRmsFilters - 1)))
        {
            ButtonDetectorRmsFast->setToggleState(true, dontSendNotification);
        }
        else if (fValue == (Compressor::DetectorRmsFilterMedium / float(Compressor::NumberOfDetectorRmsFilters - 1)))
        {
            ButtonDetectorRmsMedium->setToggleState(true, dontSendNotification);
        }
        else
        {
            ButtonDetectorRmsSlow->setToggleState(true, dontSendNotification);
        }

        break;

    case SqueezerPluginParameters::selDesign:

        if (fValue == Compressor::DesignFeedForward)
        {
            ButtonDesignFeedForward->setToggleState(true, dontSendNotification);
        }
        else
        {
            ButtonDesignFeedBack->setToggleState(true, dontSendNotification);
        }

        break;

    case SqueezerPluginParameters::selDetector:

        if (fValue == (Compressor::DetectorLinear / float(Compressor::NumberOfDetectors - 1)))
        {
            ButtonDetectorLinear->setToggleState(true, dontSendNotification);
        }
        else if (fValue == (Compressor::DetectorSmoothDecoupled / float(Compressor::NumberOfDetectors - 1)))
        {
            ButtonDetectorSmoothDecoupled->setToggleState(true, dontSendNotification);
        }
        else
        {
            ButtonDetectorSmoothBranching->setToggleState(true, dontSendNotification);
        }

        break;

    case SqueezerPluginParameters::selGainStage:

        if (fValue == (Compressor::GainStageFET / float(Compressor::NumberOfGainStages - 1)))
        {
            ButtonGainStageFET->setToggleState(true, dontSendNotification);
        }
        else
        {
            ButtonGainStageOptical->setToggleState(true, dontSendNotification);
        }

        break;

    case SqueezerPluginParameters::selThresholdSwitch:
        SliderThresholdCombined->updateMode();
        break;

    case SqueezerPluginParameters::selThreshold:
        SliderThresholdCombined->setValue(fValue, dontSendNotification);
        break;

    case SqueezerPluginParameters::selRatioSwitch:
        SliderRatioCombined->updateMode();
        break;

    case SqueezerPluginParameters::selRatio:
        SliderRatioCombined->setValue(fValue, dontSendNotification);

        {
            float fRealValue = SliderRatioCombined->getRealFloat();
            bool bUpwardExpansion = (fRealValue < 1.0f);

            for (int nChannel = 0; nChannel < nChannels; nChannel++)
            {
                pGainReductionMeters[nChannel]->setUpwardExpansion(bUpwardExpansion);
            }
        }

        break;

    case SqueezerPluginParameters::selKneeWidthSwitch:
        SliderKneeWidthCombined->updateMode();
        break;

    case SqueezerPluginParameters::selKneeWidth:
        SliderKneeWidthCombined->setValue(fValue, dontSendNotification);
        break;

    case SqueezerPluginParameters::selAttackRateSwitch:
        SliderAttackRateCombined->updateMode();
        break;

    case SqueezerPluginParameters::selAttackRate:
        SliderAttackRateCombined->setValue(fValue, dontSendNotification);
        break;

    case SqueezerPluginParameters::selReleaseRateSwitch:
        SliderReleaseRateCombined->updateMode();
        break;

    case SqueezerPluginParameters::selReleaseRate:
        SliderReleaseRateCombined->setValue(fValue, dontSendNotification);
        break;

#ifdef SQUEEZER_STEREO

    case SqueezerPluginParameters::selStereoLinkSwitch:
        SliderStereoLinkCombined->updateMode();
        break;

    case SqueezerPluginParameters::selStereoLink:
        SliderStereoLinkCombined->setValue(fValue, dontSendNotification);
        break;
#endif

    case SqueezerPluginParameters::selAutoMakeupGain:
        ButtonAutoMakeupGain->setToggleState(fValue != 0.0f, dontSendNotification);
        break;

    case SqueezerPluginParameters::selMakeupGainSwitch:
        SliderMakeupGainCombined->updateMode();
        break;

    case SqueezerPluginParameters::selMakeupGain:
        SliderMakeupGainCombined->setValue(fValue, dontSendNotification);
        break;

    case SqueezerPluginParameters::selWetMixSwitch:
        SliderWetMixCombined->updateMode();
        break;

    case SqueezerPluginParameters::selWetMix:
        SliderWetMixCombined->setValue(fValue, dontSendNotification);
        break;

    case SqueezerPluginParameters::selSidechainFilterState:
        ButtonSidechainFilterState->setToggleState(fValue != 0.0f, dontSendNotification);
        break;

    case SqueezerPluginParameters::selSidechainFilterCutoffSwitch:
        SliderSidechainFilterCutoffCombined->updateMode();
        break;

    case SqueezerPluginParameters::selSidechainFilterCutoff:
        SliderSidechainFilterCutoffCombined->setValue(fValue, dontSendNotification);
        break;

    case SqueezerPluginParameters::selSidechainFilterGain:
        SliderSidechainFilterGain->setValue(fValue, dontSendNotification);
        break;

    case SqueezerPluginParameters::selSidechainListen:
        ButtonSidechainListen->setToggleState(fValue != 0.0f, dontSendNotification);
        break;

    default:
        DBG("[Squeezer] editor::updateParameter --> invalid index");
        break;
    }
}


//==============================================================================
void SqueezerAudioProcessorEditor::paint(Graphics &g)
{
    g.setColour(Colours::lightgrey.darker(0.1f));
    g.fillAll();

    int x = 10;
    int y1 = 10;
    int y2 = 88;

    g.setColour(Colours::grey.darker(0.0f));
    g.fillRect(x      , y1, 317, 168);
    g.fillRect(x + 320, y1,  82, 168);
#ifdef SQUEEZER_STEREO
    g.fillRect(x + 405, y1, 182, 168);
    g.fillRect(x + 590, y1, 100, 168);
#else
    g.fillRect(x + 405, y1, 142, 168);
    g.fillRect(x + 550, y1,  76, 168);
#endif

    g.setColour(Colours::darkgrey);
    g.drawRect(x      , y1, 317, 168);
    g.drawRect(x + 320, y1,  82, 168);
#ifdef SQUEEZER_STEREO
    g.drawRect(x + 405, y1, 182, 168);
    g.drawRect(x + 590, y1, 100, 168);
#else
    g.drawRect(x + 405, y1, 142, 168);
    g.drawRect(x + 550, y1,  76, 168);
#endif

    g.setColour(Colours::lightgrey.darker(0.2f));
    g.fillRect(x +   5, y2, 307,  85);
    g.fillRect(x + 325, y2,  72,  85);
#ifdef SQUEEZER_STEREO
    g.fillRect(x + 410, y2, 172,  85);
    g.fillRect(x + 595, y1 + 5,  90, 158);
#else
    g.fillRect(x + 410, y2, 132,  85);
    g.fillRect(x + 555, y1 + 5,  66, 158);
#endif

    g.setColour(Colours::grey.darker(0.2f));
    g.drawRect(x +   5, y2, 307,  85);
    g.drawRect(x + 325, y2,  72,  85);
#ifdef SQUEEZER_STEREO
    g.drawRect(x + 410, y2, 172,  85);
    g.drawRect(x + 595, y1 + 5,  90, 158);
#else
    g.drawRect(x + 410, y2, 132,  85);
    g.drawRect(x + 555, y1 + 5,  66, 158);
#endif
}


void SqueezerAudioProcessorEditor::buttonClicked(Button *button)
{
    if (button == ButtonBypass)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selBypass, !button->getToggleState());
    }
    else if (button == ButtonDetectorRmsPeak)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selDetectorRmsFilter, Compressor::DetectorRmsFilterPeak / float(Compressor::NumberOfDetectorRmsFilters - 1));
    }
    else if (button == ButtonDetectorRmsFast)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selDetectorRmsFilter, Compressor::DetectorRmsFilterFast / float(Compressor::NumberOfDetectorRmsFilters - 1));
    }
    else if (button == ButtonDetectorRmsMedium)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selDetectorRmsFilter, Compressor::DetectorRmsFilterMedium / float(Compressor::NumberOfDetectorRmsFilters - 1));
    }
    else if (button == ButtonDetectorRmsSlow)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selDetectorRmsFilter, Compressor::DetectorRmsFilterSlow / float(Compressor::NumberOfDetectorRmsFilters - 1));
    }
    else if (button == ButtonDesignFeedForward)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selDesign, Compressor::DesignFeedForward);
    }
    else if (button == ButtonDesignFeedBack)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selDesign, Compressor::DesignFeedBack);
    }
    else if (button == ButtonDetectorLinear)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selDetector, Compressor::DetectorLinear / float(Compressor::NumberOfDetectors - 1));
    }
    else if (button == ButtonDetectorSmoothDecoupled)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selDetector, Compressor::DetectorSmoothDecoupled / float(Compressor::NumberOfDetectors - 1));
    }
    else if (button == ButtonDetectorSmoothBranching)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selDetector, Compressor::DetectorSmoothBranching / float(Compressor::NumberOfDetectors - 1));
    }
    else if (button == ButtonGainStageFET)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selGainStage, Compressor::GainStageFET / float(Compressor::NumberOfGainStages - 1));
    }
    else if (button == ButtonGainStageOptical)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selGainStage, Compressor::GainStageOptical / float(Compressor::NumberOfGainStages - 1));
    }
    else if (button == ButtonAutoMakeupGain)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selAutoMakeupGain, !button->getToggleState());
    }
    else if (button == ButtonSidechainFilterState)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selSidechainFilterState, !button->getToggleState());
    }
    else if (button == ButtonSidechainListen)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selSidechainListen, !button->getToggleState());
    }
    else if (button == ButtonResetMeters)
    {
        pProcessor->resetMeters();
    }
    else if (button == ButtonSettings)
    {
        String strPluginSettings = pProcessor->getParameters();
        WindowSettings windowSettings(this, strPluginSettings);
        windowSettings.runModalLoop();
    }
    else if (button == ButtonAbout)
    {
        WindowAbout windowAbout(this);
        windowAbout.runModalLoop();
    }
    else
    {
        float fValue = button->getToggleState() ? 1.0f : 0.0f;
        SliderCombined *slider = dynamic_cast<SliderCombined *>(button->getParentComponent());

        if (slider == SliderThresholdCombined)
        {
            pProcessor->changeParameter(SqueezerPluginParameters::selThresholdSwitch, fValue);
        }
        else if (slider == SliderRatioCombined)
        {
            pProcessor->changeParameter(SqueezerPluginParameters::selRatioSwitch, fValue);
        }
        else if (slider == SliderKneeWidthCombined)
        {
            pProcessor->changeParameter(SqueezerPluginParameters::selKneeWidthSwitch, fValue);
        }
        else if (slider == SliderAttackRateCombined)
        {
            pProcessor->changeParameter(SqueezerPluginParameters::selAttackRateSwitch, fValue);
        }
        else if (slider == SliderReleaseRateCombined)
        {
            pProcessor->changeParameter(SqueezerPluginParameters::selReleaseRateSwitch, fValue);
        }

#ifdef SQUEEZER_STEREO
        else if (slider == SliderStereoLinkCombined)
        {
            pProcessor->changeParameter(SqueezerPluginParameters::selStereoLinkSwitch, fValue);
        }

#endif
        else if (slider == SliderMakeupGainCombined)
        {
            pProcessor->changeParameter(SqueezerPluginParameters::selMakeupGainSwitch, fValue);
        }
        else if (slider == SliderWetMixCombined)
        {
            pProcessor->changeParameter(SqueezerPluginParameters::selWetMixSwitch, fValue);
        }
        else if (slider == SliderSidechainFilterCutoffCombined)
        {
            pProcessor->changeParameter(SqueezerPluginParameters::selSidechainFilterCutoffSwitch, fValue);
        }
        else
        {
            DBG("[Squeezer] editor::buttonClicked --> invalid button");
        }
    }
}


void SqueezerAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    float fValue = (float) slider->getValue();

    if (slider == SliderThresholdCombined)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selThreshold, fValue);
    }
    else if (slider == SliderRatioCombined)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selRatio, fValue);
    }
    else if (slider == SliderKneeWidthCombined)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selKneeWidth, fValue);
    }
    else if (slider == SliderAttackRateCombined)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selAttackRate, fValue);
    }
    else if (slider == SliderReleaseRateCombined)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selReleaseRate, fValue);
    }

#ifdef SQUEEZER_STEREO
    else if (slider == SliderStereoLinkCombined)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selStereoLink, fValue);
    }

#endif
    else if (slider == SliderMakeupGainCombined)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selMakeupGain, fValue);
    }
    else if (slider == SliderWetMixCombined)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selWetMix, fValue);
    }
    else if (slider == SliderSidechainFilterCutoffCombined)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selSidechainFilterCutoff, fValue);
    }
    else if (slider == SliderSidechainFilterGain)
    {
        pProcessor->changeParameter(SqueezerPluginParameters::selSidechainFilterGain, fValue);
    }
    else
    {
        DBG("[Squeezer] editor::sliderValueChanged --> invalid slider");
    }
}


void SqueezerAudioProcessorEditor::resized()
{
}


// Local Variables:
// ispell-local-dictionary: "british"
// End:
