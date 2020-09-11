/* autogenStepscope.h */
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

#ifndef AUTOGEN_STEPSCOPE_H
#define AUTOGEN_STEPSCOPE_H

#include "autogenCommon.h"
#include "autogenAccessory.h"

/* ================================ */

class BranchCalib: /* Calibration features */
    public AutomationExtender
{
    public:
    BranchCalib(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchCalib() {}

    char* getDelayFile(char *buffer,int buflen); /* Delay table file */
    char* getNoiseFile(char *buffer,int buflen); /* Noise table file */

    enum class Status
    {
        Ready,
        Error,
        Success,
        Running,
        Canceled
    };
    static const char *Status_Strings[];

    Status getStatus();
    void Cancel(); /* Cancel calibration, Todo:add arguments */
    void RunDelay(); /* Run Delay calibration, Todo:add arguments */
    void RunNoise(); /* Run Noise calibration, Todo:add arguments */
};

/* ================================ */

class BranchPulse: /* Pulser Access */
    public AutomationExtender
{
    public:
    BranchPulse(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchPulse() {}

    double getAccAmplMV(); /* Accessory pulser amplitude */
    void setAccAmplMV( double newValue);

    enum class AccWidth
    {
        _1,
        _2,
        _4,
        _8,
        _16
    };
    static const char *AccWidth_Strings[];

    AccWidth getAccWidth();
    void setAccWidth( AccWidth newValue);
    double getAmplMV(); /* Local Pulser amplitude */
    void setAmplMV( double newValue);
    double getFreqMHz(); /* Pulser frequency */
    int getLength(); /* Pulser length, sets period to 2X */
    void setLength( int newValue);

    enum class Mode
    {
        Off,
        Local,
        Remote,
        Triggered,
        Accessory
    };
    static const char *Mode_Strings[];

    Mode getMode();
    void setMode( Mode newValue);
    int getResetDac(); /* Delay Dac value during pulser reset */
    void setResetDac( int newValue);
    double getSlaveAmplMV(); /* Slave pulser amplitude */
    void setSlaveAmplMV( double newValue);
    char* getSlaveIP(char *buffer,int buflen); /* Pulser Slave IP address */
    void setSlaveIP( const char* newValue);
    void Reset(); /* Pulser reset, Todo:add arguments */
};

/* ================================ */

class BranchS11Cfg: /* Configuration */
    public AutomationExtender
{
    public:
    BranchS11Cfg(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchS11Cfg() {}

    bool getApplySmooth(); /* Apply FFT Smoothing */
    void setApplySmooth( bool newValue);
    int getAvg(); /* Averages */
    void setAvg( int newValue);

    enum class FileFormat
    {
        CSV,
        S1P_RI,
        S1P_DB
    };
    static const char *FileFormat_Strings[];

    FileFormat getFileFormat();
    void setFileFormat( FileFormat newValue);
    double getOffsetGHz(); /* Record Offset */
    int getPersist(); /* Persistence */
    void setPersist( int newValue);
    int getReclen(); /* Record Length */
    void setReclen( int newValue);
    bool getShowIncident(); /* Show Incident trace */
    void setShowIncident( bool newValue);
    bool getShowReflected(); /* Show Reflected trace */
    void setShowReflected( bool newValue);
    bool getShowS11(); /* Show S11 trace */
    void setShowS11( bool newValue);
    int getSmoothWidth(); /* FFT Smoothing width */
    void setSmoothWidth( int newValue);
    double getSpanGHz(); /* Record Span */
};

/* ================================ */

class BranchS11Chart: /* Chart View */
    public AutomationExtender
{
    public:
    BranchS11Chart(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix) {}
    virtual ~BranchS11Chart() {}


    enum class AxisX
    {
        Linear,
        Log
    };
    static const char *AxisX_Strings[];

    AxisX getAxisX();
    void setAxisX( AxisX newValue);
    double getBottomDB(); /* Chart Bottom */
    void setBottomDB( double newValue);
    bool getCursAvail(int index); /* Chart Cursor Available */
    bool getCursEnabled(int index); /* Chart Cursor Enabled */
    void setCursEnabled(int index, bool newValue);
    char* getCursLabel(int index,char *buffer,int buflen); /* Chart Cursor Label */

    enum class Cursor1
    {
        Manual,
        AutoYS11,
        AutoYIncident,
        AutoYReflected,
        AutoXS11,
        AutoXIncident,
        AutoXReflected
    };
    static const char *Cursor1_Strings[];

    Cursor1 getCursor1();
    void setCursor1( Cursor1 newValue);

    enum class Cursor2
    {
        Manual,
        AutoYS11,
        AutoYIncident,
        AutoYReflected,
        AutoXS11,
        AutoXIncident,
        AutoXReflected
    };
    static const char *Cursor2_Strings[];

    Cursor2 getCursor2();
    void setCursor2( Cursor2 newValue);
    double getCursValue(int index); /* Chart Cursor Value */
    void setCursValue(int index, double newValue);
    double getHeightDB(); /* Chart Height */
    void setHeightDB( double newValue);
    double getLeftGHz(); /* Chart Left */
    void setLeftGHz( double newValue);
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
    double getWidthGHz(); /* Chart Width */
    void setWidthGHz( double newValue);
};

/* ================================ */

class BranchS11: /* S11 Application */
    public AutomationExtender
{
    public:
    BranchS11(AutomationInterface *baseDevice,const char *prefix) :
        AutomationExtender(baseDevice,prefix),
	    Chart(this,"Chart:"),
	    Cfg(this,"Cfg:")
		{}
    virtual ~BranchS11() {}

    char *getBinaryIncident(int *pcount=0); /* Binary Incident Results - Must free() return value */
    char *getBinaryMagn(int *pcount=0); /* Binary Magnitude Results - Must free() return value */
    char *getBinaryReflected(int *pcount=0); /* Binary Reflected Results - Must free() return value */
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
    bool getShowSettings(); /* Show Settings */
    void setShowSettings( bool newValue);
    char* getStatusMsg(char *buffer,int buflen); /* Status Message */
    char* FileSave(char *buffer,int buflen); /* S21 file save, Todo:add arguments */
    void Fit(); /* S11 Chart Fit */
    void Reset(); /* Reset position */

    public:
    BranchS11Chart Chart;
    BranchS11Cfg Cfg;
};

/* ================================ */

class BranchS21Cfg: /* Configuration */
	public AutomationExtender
{
	public:
	BranchS21Cfg(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix) {}
	virtual ~BranchS21Cfg() {}

	bool getApplySmooth(); /* Apply FFT Smoothing */
	void setApplySmooth( bool newValue);
	int getAvg(); /* Averages */
	void setAvg( int newValue);

	enum class FileFormat
	{
		CSV,
		S1P_RI,
		S1P_DB
	};
	static const char *FileFormat_Strings[];

	FileFormat getFileFormat();
	void setFileFormat( FileFormat newValue);
	double getOffsetGHz(); /* Record Offset */
	int getPersist(); /* Persistence */
	void setPersist( int newValue);
	int getReclen(); /* Record Length */
	void setReclen( int newValue);
	bool getShowDut(); /* Show DUT trace */
	void setShowDut( bool newValue);
	bool getShowS21(); /* Show S21 Trace */
	void setShowS21( bool newValue);
	bool getShowThrough(); /* Show Through trace */
	void setShowThrough( bool newValue);
	int getSmoothWidth(); /* FFT Smoothing width */
	void setSmoothWidth( int newValue);
	double getSpanGHz(); /* Record Span */
};

/* ================================ */

class BranchS21Chart: /* Chart View */
	public AutomationExtender
{
	public:
	BranchS21Chart(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix) {}
	virtual ~BranchS21Chart() {}


	enum class AxisX
	{
		Linear,
		Log
	};
	static const char *AxisX_Strings[];

	AxisX getAxisX();
	void setAxisX( AxisX newValue);
	double getBottomDB(); /* Chart Bottom */
	void setBottomDB( double newValue);
	bool getCursAvail(int index); /* Chart Cursor Available */
	bool getCursEnabled(int index); /* Chart Cursor Enabled */
	void setCursEnabled(int index, bool newValue);
	char* getCursLabel(int index,char *buffer,int buflen); /* Chart Cursor Label */

	enum class Cursor1
	{
		Manual,
		AutoYS21,
		AutoYDut,
		AutoYThrough,
		AutoXS21,
		AutoXDut,
		AutoXThrough
	};
	static const char *Cursor1_Strings[];

	Cursor1 getCursor1();
	void setCursor1( Cursor1 newValue);

	enum class Cursor2
	{
		Manual,
		AutoYS21,
		AutoYDut,
		AutoYThrough,
		AutoXS21,
		AutoXDut,
		AutoXThrough
	};
	static const char *Cursor2_Strings[];

	Cursor2 getCursor2();
	void setCursor2( Cursor2 newValue);
	double getCursValue(int index); /* Chart Cursor Value */
	void setCursValue(int index, double newValue);
	double getHeightDB(); /* Chart Height */
	void setHeightDB( double newValue);
	double getLeftGHz(); /* Chart Left */
	void setLeftGHz( double newValue);
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
	double getWidthGHz(); /* Chart Width */
	void setWidthGHz( double newValue);
};

/* ================================ */

class BranchS21: /* S21 Application */
	public AutomationExtender
{
	public:
	BranchS21(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix),
		Chart(this,"Chart:"),
		Cfg(this,"Cfg:")
		{}
	virtual ~BranchS21() {}

	char *getBinaryDut(int *pcount=0); /* Binary Dut Results - Must free() return value */
	char *getBinaryMagn(int *pcount=0); /* Binary Magnitude Results - Must free() return value */
	char *getBinaryThrough(int *pcount=0); /* Binary Through Results - Must free() return value */
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
	bool getShowSettings(); /* Show Settings */
	void setShowSettings( bool newValue);
	char* getStatusMsg(char *buffer,int buflen); /* Status Message */
	char* FileSave(char *buffer,int buflen); /* S21 file save, Todo:add arguments */
	void Fit(); /* S21 Chart Fit */
	void Reset(); /* Reset position */

	public:
	BranchS21Chart Chart;
	BranchS21Cfg Cfg;
};

/* ================================ */

class BranchStepCfg: /* Configuration */
	public AutomationExtender
{
	public:
	BranchStepCfg(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix) {}
	virtual ~BranchStepCfg() {}

	bool getAutoRefresh(); /* Automatic refresh */
	void setAutoRefresh( bool newValue);
	int getAvg(); /* Averages */
	void setAvg( int newValue);
	double getBWGHz(); /* BW Limit GHz */
	void setBWGHz( double newValue);
	int getDepth(); /* Sample Depth */
	void setDepth( int newValue);

	enum class DSPMode
	{
		Off,
		Differential,
		SEPositive,
		SENegative
	};
	static const char *DSPMode_Strings[];

	DSPMode getDSPMode();
	void setDSPMode( DSPMode newValue);

	enum class NoiseMode
	{
		Off,
		Normal,
		Double
	};
	static const char *NoiseMode_Strings[];

	NoiseMode getNoiseMode();
	void setNoiseMode( NoiseMode newValue);
	double getOffsetPS(); /* Record Offset */
	void setOffsetPS( double newValue);
	int getReclen(); /* Record Length */
	void setReclen( int newValue);
	double getSpanPS(); /* Record Span */
	void setSpanPS( double newValue);
};

/* ================================ */

class BranchStepChart: /* Chart View */
	public AutomationExtender
{
	public:
	BranchStepChart(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix) {}
	virtual ~BranchStepChart() {}

	double getBottom(); /* Chart Bottom */
	void setBottom( double newValue);
	bool getCursAvail(int index); /* Chart Cursor Available */
	bool getCursEnabled(int index); /* Chart Cursor Enabled */
	void setCursEnabled(int index, bool newValue);
	char* getCursLabel(int index,char *buffer,int buflen); /* Chart Cursor Label */

	enum class Cursor1
	{
		Manual,
		AutoY,
		AutoX
	};
	static const char *Cursor1_Strings[];

	Cursor1 getCursor1();
	void setCursor1( Cursor1 newValue);

	enum class Cursor2
	{
		Manual,
		AutoY,
		AutoX
	};
	static const char *Cursor2_Strings[];

	Cursor2 getCursor2();
	void setCursor2( Cursor2 newValue);
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

class BranchStep: /* Step Response Application */
	public AutomationExtender
{
	public:
	BranchStep(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix),
		Chart(this,"Chart:"),
		Cfg(this,"Cfg:")
		{}
	virtual ~BranchStep() {}

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
	bool getShowSettings(); /* Show settings on gui */
	void setShowSettings( bool newValue);
	char* getStatusMsg(char *buffer,int buflen); /* Status Message */
	double getTimeFallPS(); /* Time of falling edge */
	double getTimeRisePS(); /* Time of rising edge */

	enum class AlignMode
	{
		None,
		align0101,
		align0111,
		align0110,
		align0011,
		align0000,
		align1010,
		align1000,
		align1001,
		align1100,
		align1111,
		CalNoiseLow,
		CalNoiseHigh,
		CalRefLow,
		CalRefHigh,
		FallingEdge,
		RisingEdge
	};
	static const char *AlignMode_Strings[];

	void Align( AlignMode mode, bool waitToComplete=true, double waitUntilAligningTimeout=10 ); /* Step Align */
	void WaitForAlignmentToComplete( double timeoutSec=15 );
	char* Csv(char *buffer,int buflen); /* Step Csv, Todo:add arguments */
	void Fit(); /* Step Chart Fit */
	char* PulseStats(char *buffer,int buflen); /* Pulse statistics, Todo:add arguments */

	public:
	BranchStepChart Chart;
	BranchStepCfg Cfg;
};

/* ================================ */

class BranchTdrCfg: /* Configuration */
	public AutomationExtender
{
	public:
	BranchTdrCfg(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix) {}
	virtual ~BranchTdrCfg() {}

	bool getAutoRefresh(); /* Automatic refresh */
	void setAutoRefresh( bool newValue);
	int getAvg(); /* Avergages */
	void setAvg( int newValue);
	double getBWGHz(); /* BW Limit GHz */
	void setBWGHz( double newValue);
	int getCalAvg(); /* Calibration averages */
	void setCalAvg( int newValue);
	int getCalDepth(); /* Calibration sample depth */
	void setCalDepth( int newValue);
	int getCalReclen(); /* Calibration record length */
	void setCalReclen( int newValue);

	enum class Edge
	{
		Rising,
		Falling
	};
	static const char *Edge_Strings[];

	Edge getEdge();
	void setEdge( Edge newValue);
	double getOffsetPS(); /* Record Offset */
	void setOffsetPS( double newValue);
	int getReclen(); /* Record Length */
	void setReclen( int newValue);
	double getSpanPS(); /* Record Span */
	void setSpanPS( double newValue);
	double getTermOhms(); /* Termination Impedance */
	void setTermOhms( double newValue);
	bool getUseBeforeStep(); /* Use estimated level before step */
	void setUseBeforeStep( bool newValue);
	bool getUseDiff(); /* Use Differential */
	void setUseDiff( bool newValue);
};

/* ================================ */

class BranchTdrChart: /* Chart View */
	public AutomationExtender
{
	public:
	BranchTdrChart(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix) {}
	virtual ~BranchTdrChart() {}

	double getBottomOhms(); /* Chart Bottom */
	void setBottomOhms( double newValue);
	bool getCursAvail(int index); /* Chart Cursor Available */
	bool getCursEnabled(int index); /* Chart Cursor Enabled */
	void setCursEnabled(int index, bool newValue);
	char* getCursLabel(int index,char *buffer,int buflen); /* Chart Cursor Label */

	enum class Cursor1
	{
		Manual,
		AutoY,
		AutoX
	};
	static const char *Cursor1_Strings[];

	Cursor1 getCursor1();
	void setCursor1( Cursor1 newValue);

	enum class Cursor2
	{
		Manual,
		AutoY,
		AutoX
	};
	static const char *Cursor2_Strings[];

	Cursor2 getCursor2();
	void setCursor2( Cursor2 newValue);
	double getCursValue(int index); /* Chart Cursor Value */
	void setCursValue(int index, double newValue);
	double getHeightOhms(); /* Chart Height */
	void setHeightOhms( double newValue);
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

class BranchTdr: /* TDR Application */
	public AutomationExtender
{
	public:
	BranchTdr(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix),
		Chart(this,"Chart:"),
		Cfg(this,"Cfg:")
		{}
	virtual ~BranchTdr() {}

	char *getBinary(int *pcount=0); /* Binary Data - Must free() return value */


	enum class CalState
	{
		None,
		Short,
		Term,
		Success,
		Fail
	};
	static const char *CalState_Strings[];

	CalState getCalState();
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
	char* getShortCalFile(char *buffer,int buflen); /* Short cal table file */
	bool getShowSettings(); /* Show Settings */
	void setShowSettings( bool newValue);
	char* getStatusMsg(char *buffer,int buflen); /* Status Message */
	char* getTermCalFile(char *buffer,int buflen); /* Term cal table file */
	void CancelCal(); /* Cancel calibration, Todo:add arguments */
	void ClearCal(); /* Clear calibration, Todo:add arguments */
	char* Csv(char *buffer,int buflen); /* Tdr Csv, Todo:add arguments */
	void Fit(); /* Tdr Chart Fit, */
	void LoadShortCal(); /* Load short calibration, Todo:add arguments */
	void LoadTermCal(); /* Load termination calibration, Todo:add arguments */
	void Reset(); /* Reset position,  */
	void RunShortCal(); /* Run Short calibration, Todo:add arguments */
	void RunTermCal(); /* Run 50 Ohm calibration, Todo:add arguments */
	void SaveShortCal(); /* Save short calibration, Todo:add arguments */
	void SaveTermCal(); /* Save termination calibration, Todo:add arguments */

	public:
	BranchTdrChart Chart;
	BranchTdrCfg Cfg;
};

/* ================================ */

class BranchTdtCfg: /* Configuration */
	public AutomationExtender
{
	public:
	BranchTdtCfg(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix) {}
	virtual ~BranchTdtCfg() {}

	bool getAlignRef(); /* Align Reference Step */
	void setAlignRef( bool newValue);
	bool getAutoRefresh(); /* Automatic refresh */
	void setAutoRefresh( bool newValue);
	int getAvg(); /* Avergages */
	void setAvg( int newValue);
	double getBWGHz(); /* BW Limit GHz */
	void setBWGHz( double newValue);
	int getCalAvg(); /* Calibration averages */
	void setCalAvg( int newValue);
	int getCalDepth(); /* Calibration sample depth */
	void setCalDepth( int newValue);
	int getCalReclen(); /* Calibration record length */
	void setCalReclen( int newValue);

	enum class DSPMode
	{
		Off,
		Differential,
		SEPositive,
		SENegative
	};
	static const char *DSPMode_Strings[];

	DSPMode getDSPMode();
	void setDSPMode( DSPMode newValue);

	enum class Edge
	{
		Rising,
		Falling
	};
	static const char *Edge_Strings[];

	Edge getEdge();
	void setEdge( Edge newValue);
	double getOffsetPS(); /* Record Offset */
	void setOffsetPS( double newValue);
	int getReclen(); /* Record Length */
	void setReclen( int newValue);
	double getSpanPS(); /* Record Span */
	void setSpanPS( double newValue);
};

/* ================================ */

class BranchTdtChart: /* Chart View */
	public AutomationExtender
{
	public:
	BranchTdtChart(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix) {}
	virtual ~BranchTdtChart() {}

	double getBottom(); /* Chart Bottom */
	void setBottom( double newValue);
	bool getCursAvail(int index); /* Chart Cursor Available */
	bool getCursEnabled(int index); /* Chart Cursor Enabled */
	void setCursEnabled(int index, bool newValue);
	char* getCursLabel(int index,char *buffer,int buflen); /* Chart Cursor Label */

	enum class Cursor1
	{
		Manual,
		AutoYDut,
		AutoYThrough,
		AutoXDut,
		AutoXThrough
	};
	static const char *Cursor1_Strings[];

	Cursor1 getCursor1();
	void setCursor1( Cursor1 newValue);

	enum class Cursor2
	{
		Manual,
		AutoYDut,
		AutoYThrough,
		AutoXDut,
		AutoXThrough
	};
	static const char *Cursor2_Strings[];

	Cursor2 getCursor2();
	void setCursor2( Cursor2 newValue);
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

class BranchTdt: /* TDR Application */
	public AutomationExtender
{
	public:
	BranchTdt(AutomationInterface *baseDevice,const char *prefix) :
		AutomationExtender(baseDevice,prefix),
		Chart(this,"Chart:"),
		Cfg(this,"Cfg:")
		{}
	virtual ~BranchTdt() {}

	double getAlignPS(); /* Alignment between DUT and REF */
	char *getBinary(int *pcount=0); /* Binary Data - Must free() return value */

	enum class CalState
	{
		None,
		Through,
		Success,
		Fail
	};
	static const char *CalState_Strings[];

	CalState getCalState();
	double getElapsedSeconds(); /* Elapsed Time Seconds */
	char *getRef(int *pcount=0); /* Binary Ref Data - Must free() return value */
	void setRef(char *buffer,int count);

	enum class Running
	{
		Stop,
		Run,
		RunOnce
	};
	static const char *Running_Strings[];

	Running getRunning();
	int getSequence(); /* Run Sequence */
	bool getShowDut(); /* Show TDR trace */
	void setShowDut( bool newValue);
	bool getShowSettings(); /* Show Settings */
	void setShowSettings( bool newValue);
	bool getShowThrough(); /* Show Reference trace */
	void setShowThrough( bool newValue);
	char* getStatusMsg(char *buffer,int buflen); /* Status Message */
	char* getThroughCalFile(char *buffer,int buflen); /* Through cal table file */
	void CancelCal(); /* Cancel calibration, Todo:add arguments */
	void ClearCal(); /* Clear calibration, Todo:add arguments */
	char* Csv(char *buffer,int buflen); /* Tdt Csv, Todo:add arguments */
	void Fit(); /* Tdt Chart Fit */
	void LoadThroughCal(); /* Load through calibration, Todo:add arguments */
	void Reset(); /* Reset position */
	void RunThroughCal(); /* Run Through calibration, Todo:add arguments */
	void SaveThroughCal(); /* Save through calibration, Todo:add arguments */

	public:
	BranchTdtChart Chart;
	BranchTdtCfg Cfg;
};

#endif // AUTOGEN_STEPSCOPE_H
