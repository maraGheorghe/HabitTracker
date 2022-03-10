
// HabitInternshipDlg.h : header file
//

#pragma once
#include <pqxx/pqxx>
#include "User.h"
#include "SuggestionsRepository.h"
#include "HabitRepository.h"
#include "ToDoRepository.h"
#include "UserRepository.h"
#include "CategoryRepository.h"
#include "Habit.h"
#include "ToDo.h"
#include "Category.h"

// CHabitInternshipDlg dialog
class CHabitInternshipDlg : public CDialogEx
{
// Construction
public:
	CHabitInternshipDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HABITINTERNSHIP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	void writeInText();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void loadHabits();
	void loadToDos();
	void loadSugestions(vector<Habit> allSugestions);
	void initialize_combo_box();
	void initialize_combo_c();
	CStatic textLayout;
	SuggestionsRepository repoSugestion;
	ToDoRepository repoToDo;
	UserRepository repoUser;
	HabitRepository repoHabit;
	CategoryRepository repoCategory;
	CListBox suggestions;
	CListBox todos;
	CListBox habits;
	CButton move;
	CStatic points;
	CEdit searchBar;
	CComboBox combo_box;
	CString combo_box_text;
	afx_msg void OnBnClickedMove();
	afx_msg void OnEnChangeSearchbar();
	afx_msg void OnCbnSelchangeCategory();
public:
	CComboBox combo_c;
	CString combo_t;
	CEdit description;
	CEdit name;
	afx_msg void OnBnClickedAdd();
//	afx_msg void OnCbnSelchangeComboC();
//	afx_msg void OnCbnSelchangeComboC();
	CProgressCtrl progress;
	afx_msg void OnBnClickedDone();
//	afx_msg void OnLbnSelchangeListHabits();
};
