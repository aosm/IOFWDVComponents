/*
     File:       DeviceControl.i.c
 
     Contains:   Component API for doing AVC transactions.
 
     Version:    xxx put version here xxx
 
     DRI:        Jed (George) Wilson
 
     Copyright:  � 1999-2001 by Apple Computer, Inc., all rights reserved.
 
     Warning:    *** APPLE INTERNAL USE ONLY ***
                 This file may contain unreleased API's
 
     BuildInfo:  Built by:            wgulland
                 On:                  Tue Mar 12 16:49:01 2002
                 With Interfacer:     3.0d35   (Mac OS X for PowerPC)
                 From:                DeviceControl.i
                     Revision:        3
                     Dated:           6/16/99
                     Last change by:  GDW
                     Last comment:    Changed AVC struct name to DVC for people that include
 
     Bugs:       Report bugs to Radar component "System Interfaces", "Latest"
                 List the version information (from above) in the Problem Description.
 
*/

#include <CoreServices/CoreServices.h>
//#include <CarbonCore/MixedMode.h>
//#include <CarbonCore/Components.h>
#include <DVComponentGlue/DeviceControl.h>
#if MP_SUPPORT
	#include "MPMixedModeSupport.h"
#endif

#define TOOLBOX_TRAPADDRESS(trapNum) (*(((UniversalProcPtr*)(((trapNum & 0x03FF) << 2) + 0xE00))))
#define OS_TRAPADDRESS(trapNum)      (*(((UniversalProcPtr*)(((trapNum & 0x00FF) << 2) + 0x400))))

#ifndef TRAPGLUE_NO_COMPONENT_CALL
DEFINE_API( ComponentResult ) DeviceControlDoAVCTransaction(ComponentInstance instance, DVCTransactionParams* params)
{
	#if PRAGMA_STRUCT_ALIGN
	  #pragma options align=mac68k
	#elif PRAGMA_STRUCT_PACKPUSH
	  #pragma pack(push, 2)
	#elif PRAGMA_STRUCT_PACK
	  #pragma pack(2)
	#endif
	struct DeviceControlDoAVCTransactionGluePB {
		unsigned char                  componentFlags;
		unsigned char                  componentParamSize;
		short                          componentWhat;
		DVCTransactionParams*          params;
		ComponentInstance              instance;
	};
	#if PRAGMA_STRUCT_ALIGN
	  #pragma options align=reset
	#elif PRAGMA_STRUCT_PACKPUSH
	  #pragma pack(pop)
	#elif PRAGMA_STRUCT_PACK
	  #pragma pack()
	#endif

	#if OLD_COMPONENT_GLUE
	struct DeviceControlDoAVCTransactionGluePB myDeviceControlDoAVCTransactionGluePB = {
		0,
		4,
		1
	};

	#else
	struct DeviceControlDoAVCTransactionGluePB myDeviceControlDoAVCTransactionGluePB;
	*((unsigned long*)&myDeviceControlDoAVCTransactionGluePB) = 0x00040001;
	#endif

	myDeviceControlDoAVCTransactionGluePB.params = params;
	myDeviceControlDoAVCTransactionGluePB.instance = instance;

	#if TARGET_API_MAC_OS8
		return (ComponentResult)CallUniversalProc(CallComponentUPP, 0x000000F0, &myDeviceControlDoAVCTransactionGluePB);
	#else
		return (ComponentResult)CallComponentDispatch( (ComponentParameters*)&myDeviceControlDoAVCTransactionGluePB );
	#endif
}
#endif


