#pragma once
#include "stdafx.h"


class EF_Gain :  public CXAPOBase {

public:
	//EF_Gain(const XAPO_REGISTRATION_PROPERTIES* pRegistrationProperties);
	//virtual ~EF_Gain();

	STDMETHOD(LockForProcess) (
		UINT32 InputLockedParameterCount,
		_In_reads_opt_(InputLockedParameterCount) const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS *pInputLockedParameters,
		UINT32 OutputLockedParameterCount,
		_In_reads_opt_(OutputLockedParameterCount) const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS *pOutputLockedParameters) override;


	STDMETHOD_(void, Process) (
		UINT32 InputProcessParameterCount,
		_In_reads_opt_(InputProcessParameterCount) const XAPO_PROCESS_BUFFER_PARAMETERS *pInputProcessParameters,
		UINT32 OutputProcessParameterCount,
		_Inout_updates_opt_(OutputProcessParameterCount) XAPO_PROCESS_BUFFER_PARAMETERS *pOutputProcessParameters,
		BOOL IsEnabled) override;


private:
	int uChannels;
	int uBytesPerSample;
	int nSamplesPerSec;
};

//reset disable enable
//UnlockForProcess
//OnSetParameters
//SetParameters

