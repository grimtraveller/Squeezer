/* ----------------------------------------------------------------------------

   Squeezer
   ========
   Flexible general-purpose audio compressor with a touch of lemon.

   Copyright (c) 2013 Martin Zuther (http://www.mzuther.de/)

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

#include "side_chain.h"


SideChain::SideChain(int nSampleRate)
/*  Constructor.

    nSampleRate (integer): internal sample rate

    return value: none
*/
{
    fSampleRate = (float) nSampleRate;

    pGainStageCurrent = nullptr;
    pGainStageFET = new GainStageFET(fSampleRate);
    pGainStageOptical = new GainStageOptical(fSampleRate);

    setThreshold(-12.0f);
    setRatio(2.0f);
    setKneeWidth(0.0f);

    setDetectorRmsFilter(10.0f);
    nDetectorType = Compressor::DetectorSmoothBranching;
    nGainStageType = Compressor::GainStageFET;

    setAttackRate(10);
    setReleaseRate(100);
    setDetector(nDetectorType);
    setGainStage(nGainStageType);

    // reset (i.e. initialise) all relevant variables
    reset();

#if DEBUG_RELEASE_RATE
    fTimePassed = 1.0f / float(nSampleRate);

    fDebugFinalValue90 = -1.0f;
    fDebugTimeInReleasePhase = 0.0f;
#endif
}


SideChain::~SideChain()
/*  Destructor.

    return value: none
*/
{
    pGainStageCurrent = nullptr;

    delete pGainStageFET;
    pGainStageFET = nullptr;

    delete pGainStageOptical;
    pGainStageOptical = nullptr;
}


void SideChain::reset()
/*  Reset all relevant variables.

    return value: none
*/
{
    fGainReduction = 0.0f;
    fGainCompensation = 0.0f;
    fDetectorOutputLevelSquared = 0.0f;

    fCrestFactorAutoGain = 20.0f;
}


float SideChain::getDetectorRmsFilter()
/*  Get current detector RMS filter rate.

    return value (float): returns current current detector RMS filter
    rate
*/
{
    return fDetectorRateMilliSeconds;
}


void SideChain::setDetectorRmsFilter(float fDetectorRateMilliSecondsNew)
/*  Set new detector RMS filter rate.

    fDetectorRateMilliSecondsNew (float): new detector RMS filter rate

    return value: none
*/
{
    fDetectorRateMilliSeconds = fDetectorRateMilliSecondsNew;
    float fDetectorRateSeconds = fDetectorRateMilliSeconds / 1000.0f;

    // logarithmic envelope reaches 90% of the final reading
    // in the given attack time
    fDetectorCoefficient = expf(logf(0.10f) / (fDetectorRateSeconds * fSampleRate));
}


int SideChain::getDetector()
/*  Get current compressor detector type.

    return value (integer): returns compressor detector type
 */
{
    return nDetectorType;
}


void SideChain::setDetector(int nDetectorTypeNew)
/*  Set new compressor detector type.

    nDetectorTypeNew (integer): new compressor detector type

    return value: none
 */
{
    nDetectorType = nDetectorTypeNew;
    fGainReductionIntermediate = 0.0f;

    setAttackRate(nAttackRate);
    setReleaseRate(nReleaseRate);
}


int SideChain::getGainStage()
/*  Get current compressor detector type.

    return value (integer): returns compressor detector type
 */
{
    return nGainStageType;
}


void SideChain::setGainStage(int nGainStageTypeNew)
/*  Set new compressor gain stage type.

    nGainStageTypeNew (integer): new compressor gain stage type

    return value: none
 */
{
    nGainStageType = nGainStageTypeNew;

    if (nGainStageType == Compressor::GainStageFET)
    {
        pGainStageCurrent = pGainStageFET;
    }
    else if (nGainStageType == Compressor::GainStageOptical)
    {
        pGainStageCurrent = pGainStageOptical;
    }

    // update gain compensation
    setThreshold(fThreshold);

    pGainStageCurrent->reset(fGainReduction);
}


float SideChain::getThreshold()
/*  Get current threshold.

    return value (float): returns the current threshold in decibels
 */
{
    return fThreshold;
}


void SideChain::setThreshold(float fThresholdNew)
/*  Set new threshold.

    fThresholdNew (float): new threshold in decibels

    return value: none
 */
{
    fThreshold = fThresholdNew;
    fGainCompensation = queryGainComputer(fCrestFactorAutoGain) / 2.0f;
}


float SideChain::getRatio()
/*  Get current compression ratio.

    return value (float): returns the current compression ratio
 */
{
    return 1.0f / (1.0f - fRatioInternal);
}


void SideChain::setRatio(float fRatioNew)
/*  Set new compression ratio.

    nRatioNew (float): new compression ratio

    return value: none
 */
{
    fRatioInternal = 1.0f - (1.0f / fRatioNew);
    fGainCompensation = queryGainComputer(fCrestFactorAutoGain);
}


float SideChain::getKneeWidth()
/*  Get current knee width.

    return value (float): returns the current knee width in decibels
 */
{
    return fKneeWidth;
}


void SideChain::setKneeWidth(float fKneeWidthNew)
/*  Set new knee width.

    nKneeWidthNew (float): new knee width in decibels

    return value: none
 */
{
    fKneeWidth = fKneeWidthNew;
    fKneeWidthHalf = fKneeWidth / 2.0f;
    fKneeWidthDouble = fKneeWidth * 2.0f;
}


int SideChain::getAttackRate()
/*  Get current attack rate.

    return value (integer): returns the current attack rate in
    milliseconds
 */
{
    return nAttackRate;
}


void SideChain::setAttackRate(int nAttackRateNew)
/*  Set new attack rate.

    nAttackRateNew (integer): new attack rate in milliseconds

    return value: none
 */
{
    nAttackRate = nAttackRateNew;

    if (nAttackRate == 0)
    {
        fAttackCoefficient = 0.0f;
    }
    else
    {
        float fAttackRateSeconds = nAttackRate / 1000.0f;

        // logarithmic envelope reaches 90% of the final reading in
        // the given attack time
        fAttackCoefficient = expf(logf(0.10f) / (fAttackRateSeconds * fSampleRate));
    }
}


int SideChain::getReleaseRate()
/*  Get current release rate.

    return value (integer): returns the current release rate in
    milliseconds
 */
{
    return nReleaseRate;
}


void SideChain::setReleaseRate(int nReleaseRateNew)
/*  Set new release rate.

    nReleaseRateNew (integer): new release rate in milliseconds

    return value: none
 */
{
    nReleaseRate = nReleaseRateNew;

    if (nReleaseRate == 0)
    {
        fReleaseCoefficient = 0.0f;
    }
    else
    {
        float fReleaseRateSeconds = nReleaseRate / 1000.0f;

        if (nDetectorType == Compressor::DetectorLinear)
        {
            // fall time: falls 10 dB per interval defined in release
            // rate (linear)
            fReleaseCoefficient = 10.0f / (fReleaseRateSeconds * fSampleRate);
        }
        else
        {
            // logarithmic envelope reaches 90% of the final reading
            // in the given release time
            fReleaseCoefficient = expf(logf(0.10f) / (fReleaseRateSeconds * fSampleRate));
        }
    }
}


float SideChain::getGainReduction(bool bAutoMakeupGain)
/*  Get current gain reduction.

    bAutoMakeupGain (boolean): determines whether the gain reduction
    should be level compensated or not

    return value (float): returns the current gain reduction in
    decibel
 */
{
    float fGainReductionTemp = pGainStageCurrent->processGainReduction(fGainReduction, fGainReductionIdeal);

    if (bAutoMakeupGain)
    {

        return fGainReductionTemp - fGainCompensation;
    }
    else
    {
        return fGainReductionTemp;
    }
}


float SideChain::queryGainComputer(float fInputLevel)
/*  Calculate gain reduction and envelopes from input level.

    fInputLevel (float): current input level in decibels

    return value: calculated gain reduction in decibels
 */
{
    float fAboveThreshold = fInputLevel - fThreshold;

    if (fKneeWidth == 0.0f)
    {
        if (fInputLevel <= fThreshold)
        {
            return 0.0f;
        }
        else
        {
            return fAboveThreshold * fRatioInternal;
        }
    }
    else
    {
        // algorithm adapted from Giannoulis et al., "Digital Dynamic
        // Range Compressor Design - A Tutorial and Analysis", JAES,
        // 60(6):399-408, 2012
        if (fAboveThreshold < -fKneeWidthHalf)
        {
            return 0.0f;
        }
        else if (fAboveThreshold > fKneeWidthHalf)
        {
            return fAboveThreshold * fRatioInternal;
        }
        else
        {
            float fFactor = fAboveThreshold + fKneeWidthHalf;
            float fFactorSquared = fFactor * fFactor;

            return fFactorSquared / fKneeWidthDouble * fRatioInternal;
        }
    }
}


void SideChain::processSample(float fInputLevel)
/*  Process a single audio sample value.

    fInputLevel (float): current audio sample value in decibels

    return value: current gain reduction in decibels
*/
{
    // feed input level to gain computer
    fGainReductionIdeal = queryGainComputer(fInputLevel);

    // filter calculated gain reduction through level detection filter
    float fGainReductionNew = applyLevelDetectionFilter(fGainReductionIdeal);

    // feed output from gain computer to level detector
    switch (nDetectorType)
    {
    case Compressor::DetectorLinear:
        applyDetectorLinear(fGainReductionNew);
        break;

    case Compressor::DetectorSmoothDecoupled:
        applyDetectorSmoothDecoupled(fGainReductionNew);
        break;

    case Compressor::DetectorSmoothBranching:
        applyDetectorSmoothBranching(fGainReductionNew);
        break;

    default:
        DBG("[Squeezer] sidechain::processSample --> invalid detector");
        break;
    }

#if DEBUG_RELEASE_RATE

    // reset things during attack phase
    if (fGainReductionNew > fGainReduction)
    {
        fDebugFinalValue90 = -1.0f;
        fDebugTimeInReleasePhase = 0.0f;
    }
    // we're in release phase
    else
    {
        // release phase has just started
        if (fDebugFinalValue90 < 0.0f)
        {
            // only measure "real" data
            if (fGainReduction >= 1.0f)
            {
                // determine time when the envelope reaches 90% of the
                // final reading
                fDebugFinalValue90 = fGainReduction * 0.1f;

                // reset time measurement
                fDebugTimeInReleasePhase = 0.0f;
            }
        }
        // test for 90% of the final reading
        else if (fGainReduction <= fDebugFinalValue90)
        {
            // display measured time
            DBG(String(fDebugTimeInReleasePhase * 1000.0f, 1) + " ms");

            // reset things
            fDebugFinalValue90 = -1.0f;
            fDebugTimeInReleasePhase = 0.0f;
        }
        // update time since start of release phase
        else
        {
            fDebugTimeInReleasePhase += fTimePassed;
        }
    }

#endif
}


float SideChain::applyLevelDetectionFilter(float fDetectorInputLevel)
{
    float fDetectorInputLevelSquared = fDetectorInputLevel * fDetectorInputLevel;
    float fDetectorOutputLevelSquaredOld = fDetectorOutputLevelSquared;

    fDetectorOutputLevelSquared = (fDetectorCoefficient * fDetectorOutputLevelSquaredOld) + (1.0f - fDetectorCoefficient) * fDetectorInputLevelSquared;

    float fDetectorOutputLevel = sqrtf(fDetectorOutputLevelSquared);
    return fDetectorOutputLevel;
}


void SideChain::applyDetectorLinear(float fGainReductionNew)
/*  Calculate detector with logarithmic attack and linear release
    ("Linear").

    fGainReductionNew (float): calculated new gain reduction in
    decibels

    return value: none
*/
{
    // apply attack rate if proposed gain reduction is above old gain
    // reduction
    if (fGainReductionNew >= fGainReduction)
    {
        if (fAttackCoefficient == 0.0f)
        {
            fGainReduction = fGainReductionNew;
        }
        else
        {
            // algorithm adapted from Giannoulis et al., "Digital
            // Dynamic Range Compressor Design - A Tutorial and
            // Analysis", JAES, 60(6):399-408, 2012

            float fGainReductionOld = fGainReduction;
            fGainReduction = (fAttackCoefficient * fGainReductionOld) + (1.0f - fAttackCoefficient) * fGainReductionNew;
        }
    }
    // otherwise, apply release rate if proposed gain reduction is
    // below old gain reduction
    else
    {
        if (fReleaseCoefficient == 0.0f)
        {
            fGainReduction = fGainReductionNew;
        }
        else
        {
            fGainReduction -= fReleaseCoefficient;

            if (fGainReduction < fGainReductionNew)
            {
                fGainReduction = fGainReductionNew;
            }
        }
    }
}


void SideChain::applyDetectorSmoothDecoupled(float fGainReductionNew)
/*  Calculate smooth decoupled detector ("S-Curve").

    fGainReductionNew (float): calculated gain reduction in decibels

    return value: none
*/
{
    // algorithm adapted from Giannoulis et al., "Digital Dynamic
    // Range Compressor Design - A Tutorial and Analysis", JAES,
    // 60(6):399-408, 2012
    //
    // apply release envelope
    if (fReleaseCoefficient == 0.0f)
    {
        fGainReductionIntermediate = fGainReductionNew;
    }
    else
    {
        float fGainReductionIntermediateOld = fGainReductionIntermediate;
        fGainReductionIntermediate = (fReleaseCoefficient * fGainReductionIntermediateOld) + (1.0f - fReleaseCoefficient) * fGainReductionNew;

        // maximally fast peak detection
        if (fGainReductionNew > fGainReductionIntermediate)
        {
            fGainReductionIntermediate = fGainReductionNew;
        }
    }

    // apply attack envelope
    if (fAttackCoefficient == 0.0f)
    {
        fGainReduction = fGainReductionIntermediate;
    }
    else
    {
        float fGainReductionOld = fGainReduction;
        fGainReduction = (fAttackCoefficient * fGainReductionOld) + (1.0f - fAttackCoefficient) * fGainReductionIntermediate;
    }
}


void SideChain::applyDetectorSmoothBranching(float fGainReductionNew)
/*  Calculate smooth branching detector ("Logarithmic").

    fGainReductionNew (float): calculated gain reduction in decibels

    return value: none
*/
{
    // apply attack rate if proposed gain reduction is above old gain
    // reduction
    if (fGainReductionNew > fGainReduction)
    {
        if (fAttackCoefficient == 0.0f)
        {
            fGainReduction = fGainReductionNew;
        }
        else
        {
            // algorithm adapted from Giannoulis et al., "Digital
            // Dynamic Range Compressor Design - A Tutorial and
            // Analysis", JAES, 60(6):399-408, 2012

            float fGainReductionOld = fGainReduction;
            fGainReduction = (fAttackCoefficient * fGainReductionOld) + (1.0f - fAttackCoefficient) * fGainReductionNew;
        }
    }
    // otherwise, apply release rate if proposed gain reduction is
    // below old gain reduction
    else
    {
        if (fReleaseCoefficient == 0.0f)
        {
            fGainReduction = fGainReductionNew;
        }
        else
        {
            // algorithm adapted from Giannoulis et al., "Digital
            // Dynamic Range Compressor Design - A Tutorial and
            // Analysis", JAES, 60(6):399-408, 2012

            float fGainReductionOld = fGainReduction;
            fGainReduction = (fReleaseCoefficient * fGainReductionOld) + (1.0f - fReleaseCoefficient) * fGainReductionNew;
        }
    }
}


float SideChain::level2decibel(float fLevel)
/*  Convert level from linear scale to decibels (dB).

    fLevel (float): audio level

    return value (float): returns given level in decibels (dB) when
    above "fMeterMinimumDecibel", otherwise "fMeterMinimumDecibel"
*/
{
    float fMeterMinimumDecibel = -70.01f;

    // log(0) is not defined, so return "fMeterMinimumDecibel"
    if (fLevel == 0.0f)
    {
        return fMeterMinimumDecibel;
    }
    else
    {
        // calculate decibels from audio level (a factor of 20.0 is
        // needed to calculate *level* ratios, whereas 10.0 is needed
        // for *power* ratios!)
        float fDecibels = 20.0f * log10f(fLevel);

        // to make meter ballistics look nice for low levels, do not
        // return levels below "fMeterMinimumDecibel"
        if (fDecibels < fMeterMinimumDecibel)
        {
            return fMeterMinimumDecibel;
        }
        else
        {
            return fDecibels;
        }
    }
}


float SideChain::decibel2level(float fDecibels)
/*  Convert level from decibels (dB) to linear scale.

    fLevel (float): audio level in decibels (dB)

    return value (float): given level in linear scale
*/
{
    // calculate audio level from decibels (a divisor of 20.0 is
    // needed to calculate *level* ratios, whereas 10.0 is needed for
    // *power* ratios!)
    float fLevel = powf(10.0f, fDecibels / 20.0f);
    return fLevel;
}


// Local Variables:
// ispell-local-dictionary: "british"
// End:
