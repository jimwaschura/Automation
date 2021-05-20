/* autogenPega.h */
//================================================================================
// BOOST SOFTWARE LICENSE
//
// Copyright 2020 BitWise Laboratories Inc.
// Author.......Jim Waschura
// Contact......info@bitwiselabs.com
//
//Permission is hereby granted, free of charge, to any person or organization
//obtaining a copy of the software and accompanying documentation covered by
//this license (the "Software") to use, reproduce, display, distribute,
//execute, and transmit the Software, and to prepare derivative works of the
//Software, and to permit third-parties to whom the Software is furnished to
//do so, all subject to the following:
//
//The copyright notices in the Software and this entire statement, including
//the above license grant, this restriction and the following disclaimer,
//must be included in all copies of the Software, in whole or in part, and
//all derivative works of the Software, unless such copies or derivative
//works are solely in the form of machine-executable object code generated by
//a source language processor.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
//FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
//ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//DEALINGS IN THE SOFTWARE.
//================================================================================

#ifndef AUTOGEN_PEGA_H
#define AUTOGEN_PEGA_H

#include "autogenCommon.h"
#include "autogenAccessory.h"

/* ================================ */

class BranchClk: /* Clock Access */
    public AutomationExtender
{
    public:
	BranchConst Const;

    BranchClk(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix),
		Const(this,"Const:") {}
    virtual ~BranchClk() {}
};

/* ================================ */

class BranchEDSampler: /* Meta category */
    public AutomationExtender
{
    public:
    BranchEDSampler(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchEDSampler() {}

    enum class DataSource
    {
        Ch0,
        Ch1
    };
    static const char *DataSource_Strings[];

    DataSource getDataSource();
    void setDataSource( DataSource newValue);
    double getDelayRangePS(); /* Sampler delay range */
    double getDelaysPS(int index); /* Sampler delay values by index (0=Cal 1=Deferred) */
    void setDelaysPS(int index, double newValue);

    enum class HControl
    {
        ClockDelay,
        NegDataDelay,
        ClockMinusDataDelay
    };
    static const char *HControl_Strings[];

    HControl getHControl();
    void setHControl( HControl newValue);

    enum class Mode
    {
        CalInput,
        DeferredEye
    };
    static const char *Mode_Strings[];

    Mode getMode();
    void setMode( Mode newValue);
    double getTimePS(); /* Sample time */
    void setTimePS( double newValue);

    enum class VControl
    {
        Ch0Pos,
        Ch0Neg,
        Ch1Pos,
        Ch1Neg
    };
    static const char *VControl_Strings[];

    VControl getVControl();
    void setVControl( VControl newValue);
    double getVoltsMV(); /* Sampler voltage */
    void setVoltsMV( double newValue);
    double getVoltsMaxMV(); /* Sample voltage maximum */
    double getVoltsMinMV(); /* Sample voltage minimum */
};

/* ================================ */

class BranchED: /* Pega Calibration Input Access */
    public AutomationExtender
{
    public:
	BranchEDSampler Sampler;

    BranchED(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix),
		Sampler(this,"Sampler:") {}
    virtual ~BranchED() {}

    char* getAlignDataMsg(char *buffer,int buflen); /* Data alignment results */
    bool getAutoResync(); /* Auto Resync Enable */
    void setAutoResync( bool newValue);
    double getBitRateGHz(); /* Bit Rate */
    double getCalibRateGHz(); /* Calibration input Rate */
    double getCalibLimitGbps(); /* Calibration input rate limit */

    BranchSyn::DivCalib findBestCalibDivider(double dataRateGbps) ;
    double getDelayPS(); /* Delay */
    void setDelayPS( double newValue);

    enum class DetPatt
    {
        AllZeros,
        AllOnes,
        Prbs7,
        InvPrbs7,
        Prbs11,
        InvPrbs11,
        Prbs13,
        InvPrbs13,
        Prbs15,
        InvPrbs15,
        Prbs20,
        InvPrbs20,
        Prbs23,
        InvPrbs23,
        Prbs31,
        InvPrbs31,
        Grab,
        InvGrab,
        None,
        Unknown
    };
    static const char *DetPatt_Strings[];

    DetPatt getDetPatt();
    bool getEnabled(); /* Calibration channel enabled */
    void setEnabled( bool newValue);
    double getEyeRateGHz(); /* Eye Rate */

    enum class EyeSubrate
    {
        DivBy1,
        DivBy2,
        DivBy4,
        DivBy8
    };
    static const char *EyeSubrate_Strings[];

    EyeSubrate getEyeSubrate();
    void setEyeSubrate( EyeSubrate newValue);

    enum class GrabLen
    {
        _32,
        _64,
        _96,
        _128,
        _160,
        _192
    };
    static const char *GrabLen_Strings[];

    GrabLen getGrabLen();
    void setGrabLen( GrabLen newValue);
    char* getGrabPatt(char *buffer,int buflen); /* Grabbed pattern 32-bit word hex values */
    bool getInProgress(); /* Aligning in progress */
    bool getInSync(); /* In Sync Flag */
    bool getMonitor(); /* Pattern change and data rate monitoring enable */
    void setMonitor( bool newValue);

    enum class Patt
    {
        AllZeros,
        AllOnes,
        Prbs7,
        InvPrbs7,
        Prbs11,
        InvPrbs11,
        Prbs13,
        InvPrbs13,
        Prbs15,
        InvPrbs15,
        Prbs20,
        InvPrbs20,
        Prbs23,
        InvPrbs23,
        Prbs31,
        InvPrbs31,
        Grab,
        Auto,
        Unknown
    };
    static const char *Patt_Strings[];

    Patt getPatt();
    void setPatt( Patt newValue);
    int getResyncThresh(); /* Resync Threshold */
    void setResyncThresh( int newValue);
    double getTermDCLevelMV(); /* Termination DC Level */
    void setTermDCLevelMV( double newValue);

    enum class TermType
    {
        DC,
        AC
    };
    static const char *TermType_Strings[];

    TermType getTermType();
    void setTermType( TermType newValue);
    double getThreshMV(); /* Threshold */
    void setThreshMV( double newValue);
    bool getUsingEye(); /* Using Eye Diagramming */

    enum class AlignBy
	{
    	Time,
		Volts,
		All,
		PrbsVolts,
		PrbsAll
	};
    static const char *AlignBy_Strings[];

    void Resync(); /* Manual Resync, Todo:add arguments */
    bool AlignData( AlignBy alignType = AlignBy::All, bool waitToComplete=true ); /* Perform data alignment, parameter: Time, Volts, All (Dflt), PrbsVolts, PrbsAll */
    bool WaitForAlignmentToComplete();
};

/* ================================ */

class BranchErrCfg: /* Configuration Settings */
    public AutomationExtender
{
    public:
    BranchErrCfg(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchErrCfg() {}


    enum class BitsFmt
    {
        Scientific,
        Decimal
    };
    static const char *BitsFmt_Strings[];

    BitsFmt getBitsFmt();
    void setBitsFmt( BitsFmt newValue);
    double getIntervalSeconds(); /* Update interval */
    void setIntervalSeconds( double newValue);
    int getReclen(); /* Record Length */
    void setReclen( int newValue);
    bool getShowSettings(); /* Show Settings */
    void setShowSettings( bool newValue);
    bool getShowStripSettings(); /* Show Strip Chart Settings */
    void setShowStripSettings( bool newValue);
};

/* ================================ */

class BranchErrChart: /* Chart View */
    public AutomationExtender
{
    public:
    BranchErrChart(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchErrChart() {}

    double getBottomLogBER(); /* Chart Bottom */
    void setBottomLogBER( double newValue);
    bool getCursAvail(int index); /* Chart Cursor Available */
    bool getCursEnabled(int index); /* Chart Cursor Enabled */
    void setCursEnabled(int index, bool newValue);
    char* getCursLabel(int index,char *buffer,int buflen); /* Chart Cursor Label */
    double getCursValue(int index); /* Chart Cursor Value */
    void setCursValue(int index, double newValue);
    double getHeightLogBER(); /* Chart Height */
    void setHeightLogBER( double newValue);
    double getLeftSeconds(); /* Chart Left */
    void setLeftSeconds( double newValue);
    double getLimits(int index); /* Chart Limits (LRBT) */
    bool getLocked(); /* Chart Locked */
    void setLocked( bool newValue);
    bool getLogscale(); /* Chart LogScale */
    void setLogscale( bool newValue);

    enum class Scroll
    {
        None,
        X1,
        X2,
        X3,
        X4,
        DX12,
        DX34,
        XPan,
        XScale,
        Y1,
        Y2,
        Y3,
        Y4,
        DY12,
        DY34,
        YPan,
        YScale,
        P1,
        P2,
        P3
    };
    static const char *Scroll_Strings[];

    Scroll getScroll();
    void setScroll( Scroll newValue);
    bool getShowMemory(); /* Show memories */
    void setShowMemory( bool newValue);
    bool getShowOverlays(); /* Show overlays */
    void setShowOverlays( bool newValue);
    char* getTitle(char *buffer,int buflen); /* Chart Title */
    double getWidthSeconds(); /* Chart Width */
    void setWidthSeconds( double newValue);
};


/* ================================ */

class BranchErr: /* Calibration channel error rate application */
    public AutomationExtender
{
    public:
	BranchErrCfg Cfg;
	BranchErrChart Chart;

    BranchErr(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix),
		Cfg(this,"Cfg:"),
		Chart(this,"Chart:") {}
    virtual ~BranchErr() {}

    double getABER(); /* Accumulated BER Result */
    char* getBerReport(char *buffer,int buflen); /* Ber report of 15 things */
    char *getBinary(int *pcount=0); /* Binary Data - Must free() return value */
    long long getBits(); /* Bit Count Result */
    double getElapsedSeconds(); /* Elapsed Time Seconds */
    long long getErrors(); /* Bit Errors Count Result */
    double getIBER(); /* Instantaneous BER Result */
    long long getResyncCount(); /* Resync Count */

    enum class Running
    {
        Stop,
        Run,
        RunOnce
    };
    static const char *Running_Strings[];

    Running getRunning();
    int getSequence(); /* Run Sequence */
    int getSerial(); /* Serial Number of Integration */
    char* Csv(char *buffer,int buflen); /* PegaED Csv, Todo:add arguments */
    char* Csv2(char *buffer,int buflen); /* PegaErr Csv, Todo:add arguments */
    void Fit(); /* PegaED Chart Fit, Todo:add arguments */
    void Reset(); /* Reset position, Todo:add arguments */
};

    /* ================================ */

class BranchEyeCfg: /* Configuration Settings */
    public AutomationExtender
{
    public:
    BranchEyeCfg(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchEyeCfg() {}

    double getBottom(); /* Acquisition Voltage bottom */
    double getBright(); /* Image Brightness */
    void setBright( double newValue);
    int getColumns(); /* Columns in Image */
    void setColumns( int newValue);
    int getDelaySettleUSec(); /* Delay Settle Time */
    void setDelaySettleUSec( int newValue);
    double getDepthBits(); /* E2 Depth */
    void setDepthBits( double newValue);
    int getDivisions(int index); /* Number of divisions H,V */
    void setDivisions(int index, int newValue);
    bool getEyeSync(); /* Eye Sync mode */
    double getFloorNoSync(); /* Floor threshold for No-Sync mode (500K) */
    void setFloorNoSync( double newValue);
    double getFloorSync(); /* Floor threshold for Sync mode (500K) */
    void setFloorSync( double newValue);
    double getHeight(); /* Acquisition Voltage height */
    double getOffset(); /* Acquisition Time offset */
    double getPerDiv(int index); /* Span per division */
    void setPerDiv(int index, double newValue);
    int getPersist(); /* Persistence */
    void setPersist( int newValue);
    int getRows(); /* Rows in Image */
    void setRows( int newValue);
    double getScalePcnt(); /* Scale ratio percentage */
    void setScalePcnt( double newValue);
    bool getShowRaw(); /* Show Raw Data */
    void setShowRaw( bool newValue);
    double getSpan(); /* Acquisition Time span */
    int getThreshSettleUSec(); /* Threshold Settle Time */
    void setThreshSettleUSec( int newValue);
    bool getUseClip(); /* Use Clipping for Floor level */
    void setUseClip( bool newValue);
};

/* ================================ */

class BranchEyeChart: /* Chart View */
    public AutomationExtender
{
    public:
    BranchEyeChart(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchEyeChart() {}

    double getBottomMV(); /* Chart Bottom */
    void setBottomMV( double newValue);
    bool getCursAvail(int index); /* Chart Cursor Available */
    bool getCursEnabled(int index); /* Chart Cursor Enabled */
    void setCursEnabled(int index, bool newValue);
    char* getCursLabel(int index,char *buffer,int buflen); /* Chart Cursor Label */
    double getCursValue(int index); /* Chart Cursor Value */
    void setCursValue(int index, double newValue);
    double getHeightMV(); /* Chart Height */
    void setHeightMV( double newValue);
    double getLeftPS(); /* Chart Left */
    void setLeftPS( double newValue);
    double getLimits(int index); /* Chart Limits (LRBT) */
    bool getLocked(); /* Chart Locked */
    void setLocked( bool newValue);
    bool getLogscale(); /* Chart LogScale */
    void setLogscale( bool newValue);

    enum class Scroll
    {
        None,
        X1,
        X2,
        X3,
        X4,
        DX12,
        DX34,
        XPan,
        XScale,
        Y1,
        Y2,
        Y3,
        Y4,
        DY12,
        DY34,
        YPan,
        YScale,
        P1,
        P2,
        P3
    };
    static const char *Scroll_Strings[];

    Scroll getScroll();
    void setScroll( Scroll newValue);
    bool getShowMemory(); /* Show memories */
    void setShowMemory( bool newValue);
    bool getShowOverlays(); /* Show overlays */
    void setShowOverlays( bool newValue);
    char* getTitle(char *buffer,int buflen); /* Chart Title */
    double getWidthPS(); /* Chart Width */
    void setWidthPS( double newValue);
};


/* ================================ */

class BranchEye: /* Calibration channel eye diagram application */
    public AutomationExtender
{
    public:
	BranchEyeCfg Cfg;
	BranchEyeChart Chart;

    BranchEye(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix),
		Cfg(this,"Cfg:" ),
		Chart(this,"Chart:") {}
    virtual ~BranchEye() {}

    char *getBinary(int *pcount=0); /* Binary Data - Must free() return value */
    double getElapsedSeconds(); /* Elapsed Time Seconds */

    enum class Running
    {
        Stop,
        Run,
        RunOnce
    };
    static const char *Running_Strings[];

    Running getRunning();
    int getSequence(); /* Run Sequence */
    bool getShowSettings(); /* Show gui settings panel */
    void setShowSettings( bool newValue);
    void Fit(); /* Fit chart, Todo:add arguments */
    char* Jpg(char *buffer,int buflen); /* PegaEye Jpg Image, Todo:add arguments */
    void Reset(); /* Reset position, Todo:add arguments */
};


/* ================================ */

class BranchPGAmp: /* Amplifier category */
    public AutomationExtender
{
    public:
    BranchPGAmp(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchPGAmp() {}

    double getAmplMV(int index); /* Amp amplitude setting */
    void setAmplMV(int index, double newValue);

    enum class Coupling
    {
        DC,
        AC
    };
    static const char *Coupling_Strings[];

    Coupling getCoupling(int index);
    void setCoupling(int index, Coupling newValue);
    double getCrossPcnt(int index); /* Amp crossing point setting (10-90) */
    void setCrossPcnt(int index, double newValue);
    bool getEnabled(int index); /* Amp enabled, not automatically restored */
    void setEnabled(int index, bool newValue);
    double getF2PS(int index); /* F2 setting */
    void setF2PS(int index, double newValue);
    double getF2MaxPS(int index); /* F2 maximum limit at this frequency */
    void setF2MaxPS(int index, double newValue);
    double getF2MinPS(int index); /* F2 minimum limit at this frequency */
    void setF2MinPS(int index, double newValue);
    double getOffsMV(int index); /* Amp VOffset */
    void setOffsMV(int index, double newValue);
};


/* ================================ */

class BranchPGChannel: /* Channel taps category */
    public AutomationExtender
{
    public:
    BranchPGChannel(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchPGChannel() {}

    double getFinalTaps(int index); /* Final tap values for Ch-0 (1 Pre, 1 Cursor, 2 Post) */
    double getIntrinsicTaps(int index); /* Intrinsic tap values for Ch-0 (1 Pre, 1 Cursor, 2 Post) */
    void setIntrinsicTaps(int index, double newValue);
    double getTaps(int index); /* Tap values for Ch-0 (1 Pre, 1 Cursor, 2 Post) */
    void setTaps(int index, double newValue);
};

/* ================================ */

class BranchPGDiag: /* Diagnostics access */
    public AutomationExtender
{
    public:
    BranchPGDiag(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchPGDiag() {}

    double getActualAmplMV(int index); /* Actual amplitude */
    int getBangStatus(int index); /* Bang-bang status [0]=Adsantec, [1]=Euvis */
    double getMarkDensity(int index); /* Mark Density */
    double getOpRateGHz(int index); /* Operating clock rate, -1 means not set */
    void setOpRateGHz(int index, double newValue);
};

/* ================================ */

class BranchPGErr: /* Error injector */
    public AutomationExtender
{
    public:
    BranchPGErr(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchPGErr() {}

    int getInterval128(int index); /* Error inject interval */
    void setInterval128(int index, int newValue);

    enum class Mode
    {
        Single,
        Repeat
    };
    static const char *Mode_Strings[];

    Mode getMode(int index);
    void setMode(int index, Mode newValue);
    double getRepeatBER(int index); /* Error inject repeat BER */

    enum class Type
    {
        None,
        Err1Bit,
        Err2Bit,
        Err3Bit,
        Err4Bit,
        Err5Bit,
        Err10Bit,
        Err32Bit,
        Err64Bit,
        Err128Bit,
        SepBy1,
        SepBy2
    };
    static const char *Type_Strings[];

    Type getType(int index);
    void setType(int index, Type newValue);
    void Single(); /* Do single error inject, Todo:add arguments */
};

/* ================================ */

class BranchPGPam: /* PAM4 category */
    public AutomationExtender
{
    public:
    BranchPGPam(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchPGPam() {}

    double getAmplMV(); /* Pam4 Combiner amplitude */
    void setAmplMV( double newValue);
    double getDelayPS(); /* Pam4 common delay */
    void setDelayPS( double newValue);
    double getDelayAlignPS(); /* Pam4 Combiner delay alignment */
    void setDelayAlignPS( double newValue);
    double getOffsMV(int index); /* Pam4 Combiner offset */
    void setOffsMV(int index, double newValue);
};

/* ================================ */

class BranchPGTerm: /* Termination category */
    public AutomationExtender
{
    public:
    BranchPGTerm(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchPGTerm() {}

    double getDCLevelMV(int index); /* Termination DC Level */
    void setDCLevelMV(int index, double newValue);
    double getImpedanceOhms(int index); /* Termination Impedance */
    void setImpedanceOhms(int index, double newValue);
    bool getLinkPosNeg(int index); /* Link positive and negative legs for offset and term */
    void setLinkPosNeg(int index, bool newValue);

    enum class Type
    {
        DC,
        AC
    };
    static const char *Type_Strings[];

    Type getType(int index);
    void setType(int index, Type newValue);
};
/* ================================ */

class BranchPGTrig: /* Trigger outputs */
    public AutomationExtender
{
    public:
    BranchPGTrig(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchPGTrig() {}

    int getIndexBits(int index); /* Trigger index */
    void setIndexBits(int index, int newValue);

    enum class Type
    {
        Pattern,
        Clock64
    };
    static const char *Type_Strings[];

    Type getType(int index);
    void setType(int index, Type newValue);
};

/* ================================ */

class BranchPG: /* Pattern generator control */
    public AutomationExtender
{
    public:
	BranchPGAmp Amp;
	BranchPGChannel Ch0;
	BranchPGChannel Ch1;
    BranchPGErr Err;
	BranchPGDiag Diag;
	BranchPGPam Pam;
    BranchPGTerm Term;
	BranchPGTrig Trig;

    BranchPG(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix),
		Amp(this,"Amp:"),
		Ch0(this,"Ch0:"),
		Ch1(this,"Ch1:"),
		Err(this,"Err:"),
		Diag(this,"Diag:"),
		Pam(this,"Pam:"),
		Term(this,"Term:"),
		Trig(this,"Trig:") {}
    virtual ~BranchPG() {}

    bool getAllOn(); /* Enable clock and both channels of data */
    void setAllOn( bool newValue);

    enum class Connectors
    {
        Ch0Pos,
        Ch1Pos,
        Ch0Neg,
        Ch1Neg
    };
    static const char *Connectors_Strings[];

    Connectors getConnectors(int index);
    void setConnectors(int index, Connectors newValue);
    double getDelayPS(int index); /* Delay */
    void setDelayPS(int index, double newValue);
    int getHwVersion(); /* Hardware version */

    enum class LinkMode
    {
        Ch0,
        Ch1,
        Unlinked,
        Linked,
        Interleaved
    };
    static const char *LinkMode_Strings[];

    LinkMode getLinkMode();
    void setLinkMode( LinkMode newValue);
    bool getLinkTapChanges(); /* Link Tap changes across channels */
    void setLinkTapChanges( bool newValue);
    bool getMonitor(); /* Frequency and Amp Current monitoring enable */
    void setMonitor( bool newValue);
    double getOperatingRateGHz(); /* Operating clock rate, -1 means not set */
    void setOperatingRateGHz( double newValue);

    enum class Pattern
    {
        Zeros,
        Prbs7,
        Prbs11,
        Prbs13,
        Prbs15,
        Prbs20,
        Prbs23,
        Prbs31,
        User,
        Ones,
        InvPrbs7,
        InvPrbs11,
        InvPrbs13,
        InvPrbs15,
        InvPrbs20,
        InvPrbs23,
        InvPrbs31,
        InvUser
    };
    static const char *Pattern_Strings[];

    Pattern getPattern(int index);
    void setPattern(int index, Pattern newValue);
    int getPrbsBitOffset(int index); /* Pattern bit offset */
    void setPrbsBitOffset(int index, int newValue);


	/* notice clock rate is 1/2 data rate */
	void WaitForClockToSettle( double targetClockGHz, double timeoutSec=30.0, double toleranceGHz=0.002);


    double getReadRateGHz(); /* Readback rate */
    bool getUseCombiner(); /* Use PAM4 Combiner level settings */
    void setUseCombiner( bool newValue);
    int getUserAvailableBitmask(int index); /* User Pattern pages available bit mask */

    enum class UserPage
    {
        PageA,
        PageB
    };
    static const char *UserPage_Strings[];

    UserPage getUserPage(int index);
    void setUserPage(int index, UserPage newValue);
    void SetDefaults(); /* Set defaults, Todo:add arguments */
    void UserPageFlip(); /* User Page temporary flip, Todo:add arguments */
};


class BranchTubChart: /* Chart View */
    public AutomationExtender
{
    public:
    BranchTubChart(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchTubChart() {}


    enum class AxisY
    {
        BER,
        Q
    };
    static const char *AxisY_Strings[];

    AxisY getAxisY();
    void setAxisY( AxisY newValue);
    double getBottom(); /* Chart Bottom */
    void setBottom( double newValue);
    bool getCursAvail(int index); /* Chart Cursor Available */
    bool getCursEnabled(int index); /* Chart Cursor Enabled */
    void setCursEnabled(int index, bool newValue);
    char* getCursLabel(int index,char *buffer,int buflen); /* Chart Cursor Label */
    double getCursValue(int index); /* Chart Cursor Value */
    void setCursValue(int index, double newValue);
    double getHeight(); /* Chart Height */
    void setHeight( double newValue);
    double getLeftPS(); /* Chart Left */
    void setLeftPS( double newValue);
    double getLimits(int index); /* Chart Limits (LRBT) */
    bool getLocked(); /* Chart Locked */
    void setLocked( bool newValue);
    bool getLogscale(); /* Chart LogScale */
    void setLogscale( bool newValue);

    enum class Scroll
    {
        None,
        X1,
        X2,
        X3,
        X4,
        DX12,
        DX34,
        XPan,
        XScale,
        Y1,
        Y2,
        Y3,
        Y4,
        DY12,
        DY34,
        YPan,
        YScale,
        P1,
        P2,
        P3
    };
    static const char *Scroll_Strings[];

    Scroll getScroll();
    void setScroll( Scroll newValue);
    bool getShowMemory(); /* Show memories */
    void setShowMemory( bool newValue);
    bool getShowOverlays(); /* Show overlays */
    void setShowOverlays( bool newValue);
    char* getTitle(char *buffer,int buflen); /* Chart Title */
    double getWidthPS(); /* Chart Width */
    void setWidthPS( double newValue);
};

/* ================================ */

class BranchTub: /* BER Tub application */
    public AutomationExtender
{
    public:
	BranchTubChart Chart;

    BranchTub(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix),
		Chart(this,"Chart:"){}
    virtual ~BranchTub() {}

    double getConfBER(); /* Confidence BER */
    void setConfBER( double newValue);
    int getConfErrors(); /* Number of sufficient errors in BER measurement */
    double getConfLevel(); /* Confidence Level */
    void setConfLevel( double newValue);
    double getElapsedSeconds(); /* Elapsed Time Seconds */
    double getExtrapBER(); /* Extrapolation depth BER level */
    void setExtrapBER( double newValue);
    double getFitHighBER(); /* High BER level for extrapolation basis */
    void setFitHighBER( double newValue);
    double getMeasureBER(); /* Measurement BER level */
    void setMeasureBER( double newValue);
    char *getMeta(int *pcount=0); /* Packed chart meta information binary data - Must free() return value */
    void setMeta(char *buffer,int count);
    int getMetaSEQ(); /* Chart Meta sequence number */
    int getPointCount(); /* Number of points in result */
    int getProgress100Pcnt(); /* Progress 0 to 100 */
    double getResolutionPS(); /* Resolution of time increments */
    void setResolutionPS( double newValue);

    enum class Running
    {
        Stop,
        Run,
        RunOnce
    };
    static const char *Running_Strings[];

    Running getRunning();
    int getSequence(); /* Run Sequence */
    bool getShowResults(); /* Show gui results panel */
    void setShowResults( bool newValue);
    bool getShowSettings(); /* Show gui settings panel */
    void setShowSettings( bool newValue);
    char* getStatusMsg(char *buffer,int buflen); /* Tub status message */
    double getSuffBits(); /* Confidence Bits based on confidence settings */

    enum class TubType
    {
        Tub,
        Peak
    };
    static const char *TubType_Strings[];

    TubType getTubType();
    void setTubType( TubType newValue);
    int getWkgSEQ(); /* Working Serial number */
    char* Csv(char *buffer,int buflen); /* PegaTub Csv, Todo:add arguments */
    char *FetchPoints(); /* Fetch points - Must free() return value, Todo:add arguments */
    char *FetchResults(); /* Fetch results - Must free() return value */
    char *FetchWkg(); /* Fetch working values - Must free() return value, Todo:add arguments */
    void Fit(); /* PegaTub Chart Fit, Todo:add arguments */
    void Reset(); /* Reset position, Todo:add arguments */
};

#endif // AUTOGEN_PEGA_H



