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
	static IController* GPController;

	UVPmame();

	/**
	 * Get romname from blueprint and start PinMAME emulator
	 */
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="VP Start"), Category = "VPinball|VPinMAME")
		static void VpStart(const FString& RomName);
		
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="VP Stop"), Category = "VPinball|VPinMAME")
		static void VpStop();
		
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="VP Get DMD"), Category = "VPinball|VPinMAME")
		static void VpGetDMD(TArray<uint8>& Dots);
		
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="VP Get Lamps"), Category = "VPinball|VPinMAME")
		static void VpGetLamps(TArray<uint8>& Lamps);
		

	/*****************************************
	 * IController.Run method: start emulation
	 *****************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void Run (int MinVersion=0 );
	
	/*********************************************
	 * IController.Stop() method: stop emulation 
	 *********************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void Stop ( );
	
	/*****************************************************************
	 * IController.ShowOptsDialog: shows the options dialog
	 *
	 * Deprecated:
	 * use Controller.Games("name").Settings.ShowSettingsDlg instead
	 *****************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="ShowOptsDialog"), Category = "VPinball|VPinMAME|Core")
		static void ShowOptsDialog ();
	
	/******************************************************
	 * IController.ShowAboutDialog: shows the About dialog
	 ******************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="ShowAboutDialog"), Category = "VPinball|VPinMAME|Core")
		static void ShowAboutDialog ();
	
	/****************************************************************
	 * IController.Lamp property (read only): get the state of a lamp
	 ****************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="get_Lamp"), Category = "VPinball|VPinMAME|Core") 
		static void get_Lamp (int LampNumber, bool &State ); 
	
	/************************************************************************
	 * IController.Solenoid property (read only): get the state of a solenoid
	 ************************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="get_Solenoid"), Category = "VPinball|VPinMAME|Core")
		static void get_Solenoid (int SolenoidNumber, bool &State );
	
	/************************************************************************
	 * IController.Switch property: get the state of a switch
	 ************************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="get_Switch"), Category = "VPinball|VPinMAME|Core")
		static void get_Switch (int SwitchNumber, bool &State );
	
	/************************************************************************
	 * IController.Switch property: set the state of a switch
	 ************************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="put_Switch"), Category = "VPinball|VPinMAME|Core")
		static void put_Switch (int SwitchNumber,bool State );
	
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
#endif
	/*********************************************************************
	 * IController.Lamps property (read-only): gets the state of all lamps
	 *
	 * There are 90 lamp slots
	 *********************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_Lamps (TArray<uint8>& Lamps);
	/***************************************************************
	 * IController.ChangedLamps property: returns a list of the 
	 * numbers of lamp, which state has changed since the last call
	 * number is in the first, state in the second part.
	 *
	 * There are 90 lamp slots
	 ***************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_ChangedLamps ( TArray<uint8>& lampNumber, TArray<uint8>& lampState );
	/****************************************************************************
	 * IController.Switches property: sets/gets the state of all switches at once
	 *
	 * There are 129 switch slots
	 ****************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_Switches ( TArray<uint8>&Switches);
	/****************************************************************************
	 * IController.Switches property: sets/gets the state of all switches at once
	 *
	 * There are 90 lamp slots
	 ****************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void put_Switches (TArray<uint8>Switches);
	/****************************************************************************
	 * IController.ChangedSolenoids property (read-only): gets the state of all 
	 * solenoids
	 * (also gets the information, if at leats one solenoid has changed after 
	 * last call; element 0 state if TRUE if at least one solenoid has changed 
	 * state sice last call)
	 ****************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_ChangedSolenoids ( TArray<uint8>& solenoidNumber, TArray<uint8>& solenoidState );
	/******************************************************
	 * IController.GameName property: get/set the game name
	 *
	 * If it's been set, returns the current rom name
	 ******************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="get_GameName"), Category = "VPinball|VPinMAME|Core")
		static FString get_GameName ();
	/******************************************************
	 * IController.GameName property: get/set the game (rom) name
	 ******************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="put_GameName"), Category = "VPinball|VPinMAME|Core")
		static void put_GameName (const FString& RomName );
#if 0
	UFUNCTION(BlueprintCallable, kCategory = "VPinball|VPinMAME|Core") static void get_InstallDir ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_HandleKeyboard ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_HandleKeyboard (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_UseSamples ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_UseSamples (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ShowTitle ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_ShowTitle (VARIANT_BOOL pVal );
#endif
	/*************************************************
	 * IController.Pause property: Pause the emulation
	 *************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static bool get_Pause ( );
	/*************************************************
	 * IController.Pause property: Pause the emulation
	 *************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void put_Pause (bool pVal );
#if 0
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Machines (BSTR sMachine, /*[out,retval]*/ VARIANT * pVal );
#endif
/*************************************************************************
 * IController.Running property: is the emulation initialized and running?
 *************************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="get_Running"), Category = "VPinball|VPinMAME|Core") static bool get_Running ();
#if 0
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void CheckROMS (int nShowOptions,LONG_PTR hParentWnd, /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_HandleMechanics ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_HandleMechanics (int pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_GIString ( int nString, /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedGIStrings ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ShowDMDOnly ( /*[out,retval]*/ VARIANT_BOOL * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_ShowDMDOnly (VARIANT_BOOL pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_SplashInfoLine ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_SplashInfoLine (BSTR pVal );
#endif //0
/****************************************************************************
 * IController.Solenoids property (read-only): returns the state of all 
 * solenoids at once
 * 
 * There are 66 Solenoid slots
 ****************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_Solenoids ( TArray<uint8>& Solenoids);
#if 0
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
#endif
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="ShowPathsDialog"), Category = "VPinball|VPinMAME|Core")
		static void ShowPathsDialog ();
#if 0
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ImgDir ( /*[out,retval]*/ BSTR * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_ImgDir (BSTR pVal );
#endif
	UFUNCTION(BlueprintCallable, Meta=(DisplayNam="get_Version"), Category = "VPinball|VPinMAME|Core")
		static FString get_Version ( );
#if 0
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_Mech (int param,int _arg2 );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_NewSoundCommands ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Games ( /*[out,retval]*/ struct IGames * * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_Settings ( /*[out,retval]*/ struct IControllerSettings * * pVal );
#endif //0
	/****************************************************************************
	 * IController.ChangedLEDs property (read-only): gets the state of all 
	 * LEDs
	 * (also gets the information, if at least one LED has changed after 
	 * last call; element 0 state if TRUE if at least one LED has changed 
	 * state since last call)
	 *
	 * devnote:  I'm guessing on this one - it's not documented, so test and see if
	 * you can figure out how this works or what it should do.  This is, I believe,
	 * for use with segmented LED score displays.  The Flicker or Gorgar roms, for
	 * example.  I think Flicker should be safe for public use because I think that's
	 * not a rom copy - it was developed to restore an existing game - it's super
	 * simple so might be a good use case example, and we can use it on an educational
	 * and historic basis.
	 ****************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_ChangedLEDs (int nHigh,int nLow,int nnHigh,int nnLow, TArray<uint8>& ledNumber , TArray<uint8>& ledSegments , TArray<uint8>& ledState );
#if 0
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
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="getRawDndWidth"), Category = "VPinball|VPinMAME|Core")
		static void get_RawDmdWidth(int& Width);
	
	/************************************************************************
	 * IController.RawDmdHeight property (read-only): get the height of the DMD
	 ************************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="get_RawDmdHeight"), Category = "VPinball|VPinMAME|Core")
		static void get_RawDmdHeight ( int& Height );
	
	/************************************************************************************************
	* IController.RawDmdPixels (read-only): Copy whole DMD to a self allocated array (values 0..100)
	************************************************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="get_RawDmdPixels"), Category = "VPinball|VPinMAME|Core")
		static void get_RawDmdPixels ( TArray<uint8>& Pixels );
	
	/************************************************************************
	 * IController.DmdWidth property (read-only): get the width of DMD bitmap
	 ************************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="get_DmdWidth"), Category = "VPinball|VPinMAME|Core")
		static void get_DmdWidth(int& Width);
	
	/************************************************************************
	 * IController.DmdHeight property (read-only): get the height of DMD bitmap
	 ************************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="get_DmdHeight"), Category = "VPinball|VPinMAME|Core")
		static void get_DmdHeight(int& Height);
	
	/*************************************************************************
	* IController.DmdPixel (read-only): read a given pixel of the DMD (slow!) (values 0..100?)
	*************************************************************************/
	UFUNCTION(BlueprintCallable, Meta=(DisplayName="get_DmdPixels"), Category = "VPinball|VPinMAME|Core")
		static void get_DmdPixel (int x,int y,  uint8 & PixelValue );
#if 0
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_updateDmdPixels (int * * buf,int width,int height, /*[out,retval]*/ int * pVal );
#endif // 0
	/*****************************************************************************************
	 * ChangedLampsState (read-only): Copy whole Changed Lamps array to a user allocated array
	 *
	 * There are 90 lamp slots
	 *****************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_ChangedLampsState ( TArray<uint8>& lampNumber, TArray<uint8>& lampState, int &lampCount );
	/**************************************************************************
	 * LampsState (read-only): Copy whole Lamps array to a user allocated array
	 *
	 * There are 90 lamp slots
	 **************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_LampsState (TArray<uint8>& lampState, int &lampCount);
	/*************************************************************************************************
	 * ChangedSolenoidsState (read-only): Copy whole Changed Solenoids array to a user allocated array
	 *************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_ChangedSolenoidsState ( TArray<uint8>& solenoidNumber, TArray<uint8>& solenoidState, int &solenoidCount );
	/**************************************************************************
	 * SolenoidsState (read-only): Copy whole Solenoid array to a user allocated array
	 *
	 * There are 66 lamp slots
	 **************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_SolenoidsState ( TArray<uint8>& solenoidState, int &solenoidCount);
#if 0
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
#endif // 0
	/*****************************************************************************************
	 * get_ChangedLEDsState (read-only): Copy whole Changed LEDS digits/Segments array to a user allocated array
	 *****************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core")
		static void get_ChangedLEDsState (int nHigh,int nLow,int nnHigh,int nnLow, TArray<uint8>& ledNumber , TArray<uint8>& ledSegments , TArray<uint8>& ledState, int &ledCount );
#if 0
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_RawDmdColoredPixels ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_NVRAM ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_ChangedNVRAM ( /*[out,retval]*/ VARIANT * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void get_SoundMode ( /*[out,retval]*/ int * pVal );
	UFUNCTION(BlueprintCallable, Category = "VPinball|VPinMAME|Core") static void put_SoundMode (int pVal );
#endif
};

IController* UVPmame::GPController = nullptr;