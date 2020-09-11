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

#include <stdio.h>
#include <unistd.h> /* usleep */
#include <stdlib.h> /* free */
#include <math.h> /* log10 */

#include "PegaDevice.h"

void test_pega(char *ip_address, bool stopOnError, int run, double fromGHz, double toGHz, double stepGHz );

int main( int argc, char *argv[] )
{
	setbuf(stdout, NULL); /* disable stdout buffering */
	printf("TestPega, Version 1.0\n");

	bool stopOnError=false;
	double fromGHz=1.0;
	double toGHz=28.0;
	double stepGHz=0.5;
	char *ip[32];
	int ipCount=0;
	int repeat=1;


	while( *(++argv) )
		if( !strcmp( *argv, "-stop") )
			stopOnError=true;
		else if( !strcmp( *argv, "-step") )
			stepGHz=atof(*(++argv));

		else if( !strcmp( *argv, "-from") )
			fromGHz=atof(*(++argv));

		else if( !strcmp( *argv, "-to") )
			toGHz=atof(*(++argv));

		else if( !strcmp( *argv, "-repeat") )
			repeat=atoi(*(++argv));
		else if( ipCount<32 )
			ip[ipCount++] = *argv;
		else
		{
			printf("Too many IP addresses, maximum is 32\n");
			exit(0);
		}

	if( ipCount==0 || stepGHz<=0.0 || repeat<1 || fromGHz<=0.0 || toGHz>32.0 || fromGHz>=toGHz )
	{
		printf("Usage:  TestPega [options] IP0 IP1 ... IPn\n");
		printf("Options:  -stop ..... stop on first error\n");
		printf("          -from X ... set starting Gbps (dflt 1.0)\n");
		printf("          -to X ..... set ending Gbps (dflt 28.0)\n");
		printf("          -step X ... set step-size Gbps (dflt 0.5)\n" );
		printf("          -repeat N.. number of tests for each IP\n");
		exit(0);
	}

	try
	{
		for( int n=0; n<ipCount; n++ )
			for( int k=0; k<repeat; k++ )
				test_pega(ip[n],stopOnError,k+1,fromGHz,toGHz,stepGHz);
	}
	catch(const char*msg)
	{
		printf("\nError: %s\n", msg );
	}

	return 0;
}

void test_pega(char *ip_address, bool stopOnError, int run, double fromGHz, double toGHz, double stepGHz )
{

	if( ip_address==0 || ip_address[0]==0 || stepGHz<=0.0 )
		throw "[Invalid_Parameter]";

	PegaDevice Pega;

	Pega.Connect( ip_address );

	char serialNumber[1024];
	Pega.Const.getSN( serialNumber, 1024 );

	char buffer[4096];
	printf("PEGA FREQUENCY SWEEP\n");
	printf("IP Address........%s\n", ip_address );
	printf("Serial number.....%s\n", serialNumber ) ;
	printf("Build.............%s\n", Pega.Sys.getBuild( buffer, 4096 )) ;
	printf("StopOnError.......%c\n", stopOnError?'T':'F');
	printf("From GHz..........%.3lf\n", fromGHz );
	printf("To GHz............%.3lf\n", toGHz );
	printf("Step GHz..........%.3lf\n", stepGHz );

	//================================================================================
	//================================================================================
	Pega.Stop();

	Pega.RestoreConfiguration("[factory]");
	Pega.PG.Amp.setAmplMV(0,500.0);
	Pega.PG.Amp.setAmplMV(1,500.0);

	Pega.PG.setPattern(0,BranchPG::Pattern::Prbs7);
	Pega.PG.setPattern(1,BranchPG::Pattern::Prbs31);

	Pega.Syn.setSource(0,BranchSyn::Source::Internal);
	Pega.Syn.setSource(1,BranchSyn::Source::Internal);
	Pega.PG.setAllOn(true);

	Pega.ED.setEnabled(true);
	Pega.ED.Sampler.setMode(BranchEDSampler::Mode::CalInput);
	Pega.ED.setEyeSubrate(BranchED::EyeSubrate::DivBy1) ;
	Pega.ED.setAutoResync(true);
	Pega.ED.setPatt(BranchED::Patt::Auto);

	Pega.Tub.setResolutionPS(0.25);

	printf("=================================================================================\n");
	printf("SN,Run,DegreeC,Gbps,CalDiv,Align,Thresh,Delay,Sync,Errors,Resyncs,BER,LogBER,RJ,EWC,TubStatus\n");

	for( double dataRateGbps = fromGHz; dataRateGbps<=toGHz; dataRateGbps += stepGHz )
	{
		double clockRateGHz=dataRateGbps/2.0;
		Pega.Syn.setClockRateGHz(clockRateGHz);
		BranchSyn::DivCalib divider=Pega.ED.findBestCalibDivider(dataRateGbps);
		Pega.Syn.setDivCalib( divider );
		Pega.PG.WaitForClockToSettle(clockRateGHz);
		double degrees = Pega.getTemperatureC();

		Pega.ED.AlignData(BranchED::AlignBy::All);

		char alignStatus[1024];

		Pega.ED.getAlignDataMsg( alignStatus, 1024 );

		printf("%s", serialNumber);
		printf(",%d", run );
		printf(",%.1lf",degrees);
		printf(",%.2lf", dataRateGbps );
		printf(",%s", BranchSyn::DivCalib_Strings[(int)divider]);
		printf(",\"%s\"", alignStatus );
		printf(",%.1lf",Pega.ED.Sampler.getVoltsMV());
		printf(",%.1lf", Pega.ED.Sampler.getTimePS());

		if( stopOnError && strncasecmp(alignStatus,"Success",7) )
			throw "[Stop_On_No_Alignment]" ;

		//======================================================================
		Pega.App.Stop();
		Pega.App.setTab("BERT");
		Pega.App.Clear();

		bool inSyncFlag = Pega.ED.getInSync();

		Pega.App.Run();
		usleep(5*1000*1000); // run for five seconds
		Pega.App.Stop();

		double ERRS = (int)Pega.Err.getErrors();
		int RC = (int) Pega.Err.getResyncCount();
		double BER = Pega.Err.getABER();

		printf(",%s", inSyncFlag?"Yes":"NoSync");
		printf(",%.0lf", ERRS);
		printf(",%d", RC );
		printf(",%.2le", BER );
		printf(",%.2lf", BER==0.0?0.0:log10(BER));

		if( stopOnError && !inSyncFlag )
			throw "[Stop_On_No_Sync]" ;

		if(  stopOnError && (RC>0 || ERRS>0.0)  )
			throw "[Stop_On_Errors]" ;

		//======================================================================

		Pega.App.Stop();
		Pega.App.setTab("TUB");
		Pega.App.Clear();

		Pega.RunSingle();
		Pega.WaitForRunToComplete(300.0);

		char tubStatusMessage[4096];
		Pega.Tub.getStatusMsg( tubStatusMessage, 4096 );

		char *results = Pega.Tub.FetchResults();
		double RJ=BitwiseDevice::unpackDoubleByKey(results,"RJ");
		double EWC=BitwiseDevice::unpackDoubleByKey(results,"EWC");
		free(results);

		printf(",%.3lf", RJ );
		printf(",%.1lf", EWC );
		printf(",\"%s\"", tubStatusMessage );
		printf("\n");

		if(  stopOnError && (RJ==0.0) && dataRateGbps>=4.0 )
			throw "[Stop_On_Bad_Tub]" ;
	}

	printf("\n");

	Pega.Disconnect();
}

