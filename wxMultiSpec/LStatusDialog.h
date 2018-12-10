// LStatusDialog.h : header file
// CShortStatusDlg dialog 
//
// Revised by Larry Biehl on 06/21/2017
//

#include "SMultiSpec.h"

#include "LDialog.h"
#include "LImageView.h"
#include "wx/wx.h"

typedef long unsigned int UINT;

class CShortStatusDlg : public CMDialog {
    DECLARE_DYNAMIC_CLASS( CShortStatusDlg )
    // Construction
public:
    CShortStatusDlg();
    CShortStatusDlg(UInt16 identifier, wxWindow* pParent = NULL); // standard constructor

    //	Boolean			Initialize(void);

    Boolean m_initializedFlag;

    // Dialog Data
    //{{AFX_DATA(CShortStatusDlg)

    enum {
        IDD = IDD_GraphicsStatus
    };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA
    wxBoxSizer* bSizer35;
    wxBoxSizer* bSizer93;
    wxBoxSizer* bSizer195;
    // Implementation
protected:
    UInt16 m_identifier;
    //virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
    wxStaticText* m_staticText39;
    wxStaticText* m_staticText40;
    wxStaticText* m_staticText41;
    wxStaticText* m_staticText42;
    wxStaticText* m_staticText43;
    wxStaticText* m_staticText44;
    wxStaticText* m_staticText45;
    wxStaticText* m_staticText46;
    wxStaticText* m_staticText47;
    wxStaticText* m_staticText48;
    wxStaticText* m_staticText49;
    wxStaticText* m_staticText50;
    wxStaticText* m_staticText51;
    wxStaticText* m_staticText52;
    wxStaticText* m_staticText53;
    wxStaticText* m_staticText54;
    wxStaticText* m_staticText55;
    wxStaticText* m_staticText56;
    wxStaticText* m_staticText57;
    wxStaticText* m_staticText59;
    wxStaticText* m_staticText58;
    
    wxStaticText* m_staticText105;
    wxStaticText* m_staticText106;
    wxStaticText* m_staticText308;
    wxStaticText* m_staticText309;
    wxStaticText* m_staticText310;
    wxStaticText* m_staticText311;
    wxStaticText* m_staticText312;
    wxButton* m_button11;
    
    wxGauge* m_gauge3;
    wxButton* m_button28;
    wxButton* m_button6;
    // Generated message map functions
    //{{AFX_MSG(CShortStatusDlg)
    void OnInitDialog(wxInitDialogEvent& event);
    //void OnButtonPress(wxKeyEvent& event);
    //virtual void OnCancel();
    void CreateControl();
    void CreateControl_Short();
    void CreateControl_Graphics();
    //}}AFX_MSG
    DECLARE_EVENT_TABLE()

    // Overrides
    //void PostNcDestroy();

    // Implementation
private:

};