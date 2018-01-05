//	 									MultiSpec
//
//					Laboratory for Applications of Remote Sensing
//									Purdue University
//								West Lafayette, IN 47907
//							 Copyright (1988-2017)
//						(c) Purdue Research Foundation
//								All rights reserved.
//
//	File:						CPalette.h
//	Implementation:		CPalette.cpp
//
//	Authors:					Larry L. Biehl
//
//	Revision number:		2.7
//
//	Revision date:			11/29/2017
//
//	Language:				C++
//
//	System:					Linux and Windows Operating Systems
//
//	Brief description:	This file is the definition for the CMPalette class
//
//------------------------------------------------------------------------------------
               
#if !defined __MPALETTE_H__
	#define	__MPALETTE_H__ 

#if defined multispec_lin
	#include "SMultiSpec.h" 
#endif	// defined multispec_lin

#if defined multispec_lin
	class CMPalette : public wxPalette 
#endif	// defined multispec_lin
#if defined multispec_win
	class	CMPalette : public CPalette
#endif	// defined multispec_win
		{
		public:
										CMPalette();	// constructor
			#if defined multispec_lin
											CMPalette (	// constructor
												SInt16								numberEntries);
			#endif	// defined multispec_lin
			
			virtual 					~CMPalette();		// destructor stub

			#if defined multispec_lin
				bool						Create (
												SInt16								numberEntries,
												UInt8*								redpalette,
												UInt8*								greenpalette,
												UInt8*								bluepalette);
			#endif	// defined multispec_lin
			
			#if defined multispec_win
				Boolean					LoadRGBQUADStructure (
												RGBQUAD								*RGBQuadPtr,
												SInt16								wUsage);
			#endif	// defined multispec_win
												
			SInt16					GetNumberPaletteEntries (void);
			
			void						SetNumberPaletteEntries (
											SInt16								numberEntries);
													
			void 						SetPalette (
											SInt16								paletteId);  
											
			PaletteHandle			mPaletteObject; 
	
		protected:
			void						MSetPalette (void);
											
			SInt16					mNumberEntries;
			
			static UInt16			s_palette1001[117];
			
			static UInt16			s_palette1002[396];
			
			static UInt16			s_palette1003[759];
			
			static UInt16			s_palette1004[315];
			
			static UInt16			s_palette1005[372];
			
			static UInt16			s_palette1006[768];
			
			static UInt16			s_palette1007[768];
			
			static UInt16			s_palette1008[768];
			
		};  
#endif	// !defined __MPALETTE_H__