//	 									MultiSpec
//
//					Laboratory for Applications of Remote Sensing
// 								Purdue University
//								West Lafayette, IN 47907
//								 Copyright (2009-2020)
//							(c) Purdue Research Foundation
//									All rights reserved.
//
//	File:						xTextView.cpp : class implementation file
//	Class Definition:		xTextView.h
//
//	Authors:					Abdur Rahman Maud, Larry L. Biehl
//
//	Revision date:			07/25/2016 by Wei-Kang Hsu
//								09/01/2019 by Larry L. Biehl
//
//	Language:				C++
//
//	System:					Linux and MacOS Operating Systems
//
//	Brief description:	This file contains functions that relate to the
//								CMTextDoc class.
//
//------------------------------------------------------------------------------------

#include "xMultiSpec.h"
#include "xTextFrame.h"
#include "xTextView.h"

#include "wx/fontenum.h"

IMPLEMENT_DYNAMIC_CLASS (CMTextView, wxView)

int 									s_clientHeight,
										s_clientWidth,
										s_textWindowXPosition,
										s_textWindowYPosition;



CMTextView::CMTextView ()
		: wxView ()

{
	m_frame = (wxDocChildFrame*)NULL;
	m_textsw = (TextWindow2*)NULL;
	
}	// end "CMTextView"


	
CMTextView::~CMTextView ()

{
	m_textsw = NULL;
	m_frame = NULL;
	gOutputViewCPtr = NULL;
	gActiveWindowType = 0;
	gTheActiveWindow = NULL;
	
}	// end "~CMTextView"

//------------------------------------------------------------------------------------
//								 Copyright (2009-2020)
//							(c) Purdue Research Foundation
//									All rights reserved.
//
//	Function name:		SInt16 GetWindowType
//
//	Software purpose:	The purpose of this routine is to return the window type
//							variable for this window object.
//
//	Parameters in:		None			
//
//	Parameters out:	None			
//
//	Value Returned:	0 if now window structure exists
//							window type for output text window
// 
// Called By:						
//
//	Coded By:			Larry L. Biehl			Date: 06/06/2015
//	Revised By:			Larry L. Biehl			Date: 06/06/2015	

SInt16 CMTextView::GetWindowType (void)

{  
	SInt16								windowType = 0;
	
	         
			// Get the window type which will be output window
	                              
	windowType = kOutputWindowType;
	
	return (windowType);
	
}	// end "GetWindowType"



void CMTextView::InitialUpdate (void)

{   
   m_textsw->SetTabWidth (1);
   m_textsw->SetMarginLeft (-12);
   m_textsw->SetScrollWidthTracking (true);
   m_textsw->SetFoldMarginColour (true, wxColor (0, 0, 0));
   m_textsw->SetFoldMarginHiColour (true, wxColor (0, 0, 0));
	//m_textsw->MarginSetStyleOffset (0);
	//m_textsw->SetWrapMode (1);
	//m_textsw->SetUseHorizontalScrollBar (false);

}	// end "InitialUpdate"



bool CMTextView::OnCreate (
				wxDocument*							doc,
				long 									WXUNUSED (flags))

{
	int									clientWidth,
											clientHeight,
											width = 650,
											height = 350,
											textWindowXPosition,
											textWindowYPosition;
			
	
	GetMainFrame()->GetClientSize (&clientWidth, &clientHeight);
	width = MIN (width, clientWidth);
	height = MIN (height, clientHeight);

   textWindowXPosition = clientWidth - width - 12;
	
	#ifdef NetBeansProject
		textWindowYPosition = 110;
	#else	// mygeohub
		textWindowYPosition = 80;
	#endif
	
	s_textWindowXPosition = textWindowXPosition;
	s_textWindowYPosition = textWindowYPosition;
	s_clientWidth = clientWidth;
	s_clientHeight = clientHeight;

	m_frame = new CMTextFrame (doc,
										this,
										GetMainFrame (),
										wxID_ANY,
										wxT("Text Output"),
										wxPoint (textWindowXPosition, textWindowYPosition),
										wxSize (width, height),
										#if defined multispec_wxmac
											wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT);
										#else
											wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP);
										#endif

	doc->SetFilename (wxT("MultiSpec_Text_Output"), false);
	wxFont font (
				gFontSize, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
   m_frame->SetFont (font);
	m_frame->GetClientSize (&width, &height);
   m_frame->SetTitle (_T("Text Output"));
   
	m_textsw = new TextWindow2 (this,
											m_frame,
											wxPoint (0, 0),
											wxSize (width, height),
											wxTE_MULTILINE); //wxHSCROLL|wxTE_READONLY|
	wxFont textwf (
				gFontSize, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	m_textsw->StyleSetFont (wxSTC_STYLE_DEFAULT, textwf);
   m_textsw->StyleClearAll ();
	
	gOutputViewCPtr = this;
	gTheActiveWindow = (WindowPtr)this;
	#ifdef __X__
				// X seems to require a forced resize
		int 		x,
					y;
		m_frame->GetSize (&x, &y);
		m_frame->SetSize (wxDefaultCoord, wxDefaultCoord, x, y);
	#endif

	m_frame->Show (true);
	Activate (true);
	
	InitialUpdate ();

	return true;
	
}	// end "OnCreate"


/*
void CMTextView::UpdateCaretPosition (
				wxStyledTextEvent& 				event)
 
{
	//m_textsw->MoveCaretInsideView ();
	//m_textsw->VerticalCentreCaret ();
	//OnTextChange ();
 
   if (m_textsw->m_eventSkip != true)
		m_textsw->LineScrollDown ();
 
   	 	// make sure m_textsw->m_eventSkip is changed only at the second time in
 
   if (enableFlag == true)
      m_textsw->m_eventSkip = false;
   
   enableFlag = true;
   
	//event.Skip ();
	//event.StopPropagation ();
   
}	// end "UpdateCaretPosition"



void CMTextView::SetVariableSkip (
				wxKeyEvent& 						event)
 
{
   m_textsw->m_eventSkip = true;
   enableFlag = false;
	//OnTextChange ();
   event.Skip ();
 
}	// end "SetVariableSkip"



void CMTextView::MoveBackCaretPosition (
				wxStyledTextEvent& 				event)

{
   m_textsw->LineScrollUp ();

}	// end "MoveBackCaretPosition"
*/


class MyFontEnumerator : public wxFontEnumerator

{
	public:
		bool GotAny() const
			{ return !m_facenames.IsEmpty(); }
	
		const wxArrayString& GetFacenames() const
			{ return m_facenames; }
	
	protected:
		virtual bool OnFacename (const wxString& facename)
			{
			m_facenames.Add (facename);
			return true;
			}
	
	private:
		wxArrayString m_facenames;

}	fontEnumerator;
	
	
bool CMTextView::DoEnumerateFamilies (
				wxFont 								textwf,
				bool 									fixedWidthOnly,
				wxFontEncoding 					encoding)

{
	MyFontEnumerator					fontEnumerator;
	
	
	fontEnumerator.EnumerateFacenames (encoding, fixedWidthOnly);
   
	if (fontEnumerator.GotAny())
		{
		int nFacenames = fontEnumerator.GetFacenames().GetCount ();
		
		wxString facename;
   
		int n;
		for (n = 0; n < nFacenames; n++)
			{
			facename = fontEnumerator.GetFacenames().Item (n);
			//textwf.SetFaceName (facename);
			//m_textsw->SetFont (textwf);
			}
  
		return true;
		
		}	// end "if (fontEnumerator.GotAny())"
	  
	return false;
	
}	// end "DoEnumerateFamilies"



//------------------------------------------------------------------------------------
//								 Copyright (1988-2020)
//								c Purdue Research Foundation
//									All rights reserved.
//
//	Function name:		Boolean ListString
//
//	Software purpose:	The purpose of this routine is to list the input
//							information to the output text window.
//							Adapted from Windows code.
//
//	Parameters in:		Pointer to 'c' string.
//
//	Parameters out:	None
//
//	Value Returned:	True if operation is okay
//							False if the text limit was reached
//
// Called By:			ListString in SStrings.cpp
//
//	Coded By:			Larry L. Biehl			Date: 03/30/1988
//	Revised By:			Larry L. Biehl			Date: 06/19/2017

bool CMTextView::ListString (
				HPtr									textPtr,
				UInt32								textLength,
				SInt16								charFormatCode)

{
			// Make certain that there is a 'c' terminator at the end of the string.

	textPtr[textLength] = 0;
   wxString strtext (textPtr, wxConvUTF8);
	//GetEditCtrl().ReplaceSel (textPtr);
	if (m_textsw != NULL)
		m_textsw->AppendText (strtext);
	
	//GetEditCtrl().SetModify (TRUE);
	
	if (m_frame != NULL)		// It could be null if the application is being closed.
		m_frame->SetTitle (wxT ("Text Output"));
	
	return (true);

}	// end "ListString"



// This function is called when we call wxView::Activate ()
// Inherited from wxView
void CMTextView::OnActivateView (
				bool 									bActivate,
				wxView* 								pActivateView,
				wxView* 								pDeactiveView)

{
	if (m_frame != NULL)
		{
		if (bActivate)
			{
			wxASSERT (pActivateView == (wxView*)this);
			
			}	// end "if (bActivate)"
		  
				// If the window is being activated, outside of a processing operating,
				// make sure the global active image information is up to date.
				
		if (gProcessorCode == 0 && bActivate)
			{
			gActiveWindowType = kOutputWindowType;
			gTheActiveWindow = (WindowPtr)gOutputViewCPtr;
			
			}	// end "if (gProcessorCode == 0 && bActivate)"
		
		m_frame->EnableCloseButton (false);
		
		}	// end "if (m_frame != NULL)"

}	// end "OnActivateView"



// Handled by wxTextWindow
void CMTextView::OnDraw (
				wxDC*									WXUNUSED (dc))

{

}	// end "OnDraw"



void CMTextView::OnUpdate (
				wxView*								WXUNUSED (sender),
				wxObject*							WXUNUSED (hint))

{

}	// end "OnUpdate"



bool CMTextView::OnClose (
				bool 									deleteWindow)

{
			// Need to check the m_applicationExitFlag to verify that this call
			// is actually coming from an application quit event instead of a
			// close text window event which is not allowed. The close button
			// in the text window is sometimes activated for MacOS when
			// MultiSpec is brought to the front.
	
	if (((CMTextDoc*)GetDocument())->m_applicationExitFlag)
		{
		//if (!GetDocument()->Close ())
		//	return false;

		Activate (false);

		if (deleteWindow)
			{
			delete m_frame;
			m_frame = NULL;
																							return true;
			
			}	// end "if (deleteWindow)"
		
		return true;
		
		}	// end "if (((CMTextDoc*)GetDocument())->m_applicationExitFlag)"
	
	return false;
	
}	// end "OnClose"



// Currently not used
void CMTextView::OnTextChange (
				wxCommandEvent& 					event)

{
	((CMTextDoc*)GetDocument())->Modify (true);

	event.Skip ();
	
}	// end "OnTextChange"



TextWindow::TextWindow (
				wxView*								v,
				wxDocChildFrame*					frame,
				const wxPoint& 					pos,
				const wxSize& 						size,
				long 									style)
		: wxTextCtrl (frame, wxID_ANY, _T(""), pos, size, style)

{
  m_view = v;
	
}	// end "TextWindow"



TextWindow2::TextWindow2 (
				wxView*								v,
				wxDocChildFrame*					frame,
				const wxPoint& 					pos,
				const wxSize& 						size,
				long 									style)
		: wxStyledTextCtrl (frame, ID_TextWindowStyled, pos, size, style)

{
  m_view = v;
	
}	// end "TextWindow2"
