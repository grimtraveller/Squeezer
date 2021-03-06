/* ----------------------------------------------------------------------------

   Squeezer
   ========
   Flexible general-purpose audio compressor with a touch of lemon.

   Copyright (c) 2013-2016 Martin Zuther (http://www.mzuther.de/)

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

#ifndef __PLUGINEDITOR_SQUEEZER_H__
#define __PLUGINEDITOR_SQUEEZER_H__

#include "FrutHeader.h"
#include "compressor.h"
#include "meter_bar_gain_reduction.h"
#include "meter_bar_level.h"
#include "plugin_processor.h"
#include "skin.h"


class SqueezerAudioProcessorEditor :
    public AudioProcessorEditor,
    public ButtonListener,
    public SliderListener,
    public ActionListener
{
public:
    SqueezerAudioProcessorEditor(
        SqueezerAudioProcessor *OwnerFilter,
        SqueezerPluginParameters *PluginParameters,
        int NumberOfChannels);

    ~SqueezerAudioProcessorEditor();

    void buttonClicked(Button *Button);
    void sliderValueChanged(Slider *Slider);

    void actionListenerCallback(const String &Message);
    void updateParameter(int Index);

    void windowAboutCallback(int ModalResult);
    void windowSettingsCallback(int ModalResult);
    void windowSkinCallback(int ModalResult);

    void resized();

private:
    JUCE_LEAK_DETECTOR(SqueezerAudioProcessorEditor);

    void applySkin_();
    void loadSkin_();

    bool IsInitialising_;
    int NumberOfChannels_;

    SqueezerAudioProcessor *PluginProcessor_;

    File SkinDirectory_;
    Skin CurrentSkin_;
    String CurrentSkinName_;

    OwnedArray<MeterBarLevel> InputLevelMeters_;
    OwnedArray<MeterBarLevel> OutputLevelMeters_;
    OwnedArray<MeterBarGainReduction> GainReductionMeters_;

    TextButton ButtonDetectorRms_;
    TextButton ButtonDesignFeedback_;
    TextButton ButtonGainStageOptical_;

    TextButton ButtonKneeHard_;
    TextButton ButtonKneeMedium_;
    TextButton ButtonKneeSoft_;

    TextButton ButtonDetectorLinear_;
    TextButton ButtonDetectorSmoothDecoupled_;
    TextButton ButtonDetectorSmoothBranching_;

    ScopedPointer<frut::widget::SliderCombined> SliderThreshold_;
    ScopedPointer<frut::widget::SliderCombined> SliderRatio_;

    ScopedPointer<frut::widget::SliderCombined> SliderAttackRate_;
    ScopedPointer<frut::widget::SliderCombined> SliderReleaseRate_;

    TextButton ButtonAutoMakeupGain_;
    ScopedPointer<frut::widget::SliderCombined> SliderMakeupGain_;
    ScopedPointer<frut::widget::SliderCombined> SliderWetMix_;

    TextButton ButtonSidechainFilterState_;
    ScopedPointer<frut::widget::SliderCombined> SliderSidechainLpfCutoff_;
    ScopedPointer<frut::widget::SliderSwitchLinearBar> SliderSidechainFilterGain_;
    TextButton ButtonSidechainListen_;

    TextButton ButtonBypass_;
    TextButton ButtonReset_;

    TextButton ButtonSkin_;
    TextButton ButtonSettings_;
    TextButton ButtonAbout_;

    Label LabelDebug_;

    ImageComponent BackgroundImage_;
};


#endif  // __PLUGINEDITOR_SQUEEZER_H__


// Local Variables:
// ispell-local-dictionary: "british"
// End:
