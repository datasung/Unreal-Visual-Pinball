// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Windows/AllowWindowsPlatformTypes.h" // Add vanilla C++ header :Start

extern "C"  // this end-runs a compiler error - but I think it's still functional
{
	long __cdecl _InterlockedIncrement(long volatile* pn);
	long __cdecl _InterlockedDecrement(long volatile* pn);
}
inline long InterlockedIncrement(long volatile* pn) { return _InterlockedIncrement(pn); }
inline long InterlockedDecrement(long volatile* pn) { return _InterlockedDecrement(pn); }

#include "com.h"
#include "Windows/HideWindowsPlatformTypes.h" // Add vanilla C++ header :End
//#include "UE4_VPinMAME.h"
#include "VPmame.generated.h"

/**
 * 
 */
UCLASS()
class UVPmame : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	public:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;
	static IController* pController;

	UVPmame();

	/**
	 * Get romname from blueprint and start PinMAME emulator
	 */
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME")
		static void VPStart(const FString& RomName);
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME")
		static void VPStop();
	/************************************************************************
	 * IController.DmdWidth property (read-only): getthe width of DMD bitmap
	 ************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME")
		static void VPGetDMD(TArray<uint8>& Dots);
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME")
		static void VPGetLamps(TArray<uint8>& Lamps);

/*****************************************
 * IController.Run method: start emulation
 *****************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void Run (int nMinVersion=0 );
/*********************************************
 * IController.Stop() method: stop emulation 
 *********************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void Stop ( );
/*****************************************************************
 * IController.ShowOptsDialog: shows the options dialog
 *
 * Deprecated:
 * use Controller.Games("name").Settings.ShowSettingsDlg instead
 *****************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void ShowOptsDialog ();
/******************************************************
 * IController.ShowAboutDialog: shows the About dialog
 ******************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void ShowAboutDialog ();
/****************************************************************
 * IController.Lamp property (read only): get the state of a lamp
 ****************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Lamp (int nLamp, bool &pVal ); 
/************************************************************************
 * IController.Solenoid property (read only): get the state of a solenoid
 ************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Solenoid (int nSolenoid, bool &pVal );
/************************************************************************
 * IController.Switch property: get the state of a switch
 ************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Switch (int nSwitchNo, bool &pVal );
/************************************************************************
 * IController.Switch property: set the state of a switch
 ************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_Switch (int nSwitchNo,bool pVal );
#if 0
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_RomDirs ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_RomDirs (BSTR pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_NVRamDir ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_NVRamDir (BSTR pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_SamplesDir ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_SamplesDir (BSTR pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_CfgDir ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_CfgDir (BSTR pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_WPCNumbering ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Lamps ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedLamps ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Switches ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_Switches (VARIANT pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedSolenoids ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_GameName ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_GameName (BSTR pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_InstallDir ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_HandleKeyboard ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_HandleKeyboard (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_UseSamples ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_UseSamples (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ShowTitle ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_ShowTitle (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Pause ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_Pause (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Machines (BSTR sMachine, /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Running ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void CheckROMS (int nShowOptions,LONG_PTR hParentWnd, /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_HandleMechanics ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_HandleMechanics (int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_GIString ( int nString, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedGIStrings ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ShowDMDOnly ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_ShowDMDOnly (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_SplashInfoLine ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_SplashInfoLine (BSTR pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Solenoids ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Dip (int nNo, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_Dip (int nNo,int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_GIStrings ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_GetMech (int mechNo, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ShowFrame ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_ShowFrame (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_BorderSizeX ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_BorderSizeX (int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_BorderSizeY ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_BorderSizeY (int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_WindowPosX ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_WindowPosX (int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_WindowPosY ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_WindowPosY (int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_SampleRate ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_SampleRate (int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_DoubleSize ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_DoubleSize (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void SetDisplayPosition (int x,int y,LONG_PTR hParentWindow );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_LockDisplay ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_LockDisplay (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Antialias ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_Antialias (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_SolMask (int nLow, /*[out,retval]*/ long * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_SolMask (int nLow,long pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void ShowPathesDialog (LONG_PTR hParentWnd );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ImgDir ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_ImgDir (BSTR pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Version ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_Mech (int param,int _arg2 );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_NewSoundCommands ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Games ( /*[out,retval]*/ struct IGames * * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Settings ( /*[out,retval]*/ struct IControllerSettings * * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedLEDs (int nHigh,int nLow,int nnHigh,int nnLow, /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Hidden ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_Hidden (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Game ( /*[out,retval]*/ struct IGame * * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_MechSamples ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_MechSamples (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void GetWindowRect (LONG_PTR hWnd, /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void GetClientRect (LONG_PTR hWnd, /*[out,retval]*/ VARIANT * pVal );
#endif
/************************************************************************
 * IController.RawDmdWidth property (read-only): get the width of the DMD
 ************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_RawDmdWidth(int& Width);
#if 0
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_RawDmdHeight ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_RawDmdPixels ( /*[out,retval]*/ VARIANT * pVal );
#endif
/************************************************************************
 * IController.DmdWidth property (read-only): get the width of DMD bitmap
 ************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_DmdWidth(int& Width);
#if 0
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_DndHeight(int& Height);
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_DmdPixel (int x,int y, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_updateDmdPixels (int * * buf,int width,int height, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedLampsState (int * * buf, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_LampsState (int * * buf, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedSolenoidsState (int * * buf, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_SolenoidsState (int * * buf, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedGIsState (int * * buf, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_MasterVolume ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_MasterVolume (int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_EnumAudioDevices ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_AudioDevicesCount ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_AudioDeviceDescription (int num, /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_AudioDeviceModule (int num, /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_CurrentAudioDevice ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_CurrentAudioDevice (int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_FastFrames ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_FastFrames (int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_IgnoreRomCrc ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_IgnoreRomCrc (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_CabinetMode ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_CabinetMode (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ShowPinDMD ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_ShowPinDMD (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ShowWinDMD ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_ShowWinDMD (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedLEDsState (int nHigh,int nLow,int nnHigh,int nnLow,int * * buf, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_RawDmdColoredPixels ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_NVRAM ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedNVRAM ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_SoundMode ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_SoundMode (int pVal );
#endif

};

IController* UVPmame::pController = NULL;