
// HabitInternshipDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "HabitInternship.h"
#include "HabitInternshipDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <iostream>
#include "User.h"
#include "ToDo.h"
#include "SuggestionsRepository.h"
#include <pqxx/pqxx>
#include "HabitRepository.h"

CHabitInternshipDlg::CHabitInternshipDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HABITINTERNSHIP_DIALOG, pParent)
	, combo_t(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHabitInternshipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_TEXT, textLayout);
	DDX_Control(pDX, ID_LIST_SUGGESTIONS, suggestions);
	DDX_Control(pDX, IDC_LIST_TODO, todos);
	DDX_Control(pDX, IDC_LIST_HABITS, habits);
	DDX_Control(pDX, IDC_MOVE, move);
	DDX_Control(pDX, IDC_CATEGORY, combo_box);
	DDX_CBString(pDX, IDC_CATEGORY, combo_box_text);
	DDX_Control(pDX, ID_points, points);
	DDX_Control(pDX, IDC_SEARCHBAR, searchBar);

	DDX_Control(pDX, IDC_COMBO_C, combo_c);
	DDX_CBString(pDX, IDC_COMBO_C, combo_t);
	DDX_Control(pDX, IDC_SEARCHBAR3, description);
	DDX_Control(pDX, IDC_SEARCHBAR2, name);
}

	
BEGIN_MESSAGE_MAP(CHabitInternshipDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MOVE, &CHabitInternshipDlg::OnBnClickedMove)
	ON_EN_CHANGE(IDC_SEARCHBAR, &CHabitInternshipDlg::OnEnChangeSearchbar)
	ON_CBN_SELCHANGE(IDC_CATEGORY, &CHabitInternshipDlg::OnCbnSelchangeCategory)
	ON_BN_CLICKED(IDC_ADD, &CHabitInternshipDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DONE, &CHabitInternshipDlg::OnBnClickedDone)
//	ON_LBN_SELCHANGE(IDC_LIST_HABITS, &CHabitInternshipDlg::OnLbnSelchangeListHabits)
END_MESSAGE_MAP()


// CHabitInternshipDlg message handlers

BOOL CHabitInternshipDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	writeInText();
	loadSugestions(repoSugestion.find_all_suggestions());
	loadToDos();
	loadHabits();
	initialize_combo_box();
	points.SetWindowTextW(CString(std::to_string(repoToDo.find_score()).c_str()));
	initialize_combo_c();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHabitInternshipDlg::loadSugestions(vector<Habit> allSugestions) {
	suggestions.ResetContent();
	for (auto sugestion : allSugestions) {
		auto index = suggestions.AddString(CString(sugestion.toString().c_str()));
		suggestions.SetItemData(index, sugestion.get_ID());
	}
}

void CHabitInternshipDlg::loadToDos() {
	todos.ResetContent();
	for (auto todo : repoToDo.find_all_to_dos()) {
		auto index = todos.AddString(CString(todo.toString().c_str()));
		todos.SetItemData(index, todo.getId());
	}
}

void CHabitInternshipDlg::loadHabits() {
	habits.ResetContent();
	for (auto habit : repoHabit.find_all_habits()) {
		auto index = habits.AddString(CString(habit.toString().c_str()));
		habits.SetItemData(index, habit.get_ID());
	}
}

void CHabitInternshipDlg::writeInText() {
	UserRepository repo = UserRepository();
	textLayout.SetWindowTextW(CString(repo.findOne().toString().c_str()));
	ToDoRepository repoToDo = ToDoRepository();
	repoToDo.find_all_to_dos();
}

void CHabitInternshipDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CHabitInternshipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHabitInternshipDlg::OnBnClickedMove()
{
	auto setIndex = suggestions.GetCurSel();
	if (setIndex != LB_ERR) {
		Habit selectedSugestion = repoSugestion.find_suggestion(suggestions.GetItemData(setIndex));
		auto indexToDo = repoToDo.save_to_do(selectedSugestion);
		auto todo = repoToDo.find_one_to_do(indexToDo);
		auto index = todos.AddString(CString(todo.toString().c_str()));
		todos.SetItemData(index, todo.getId());
	}
}


void CHabitInternshipDlg::OnEnChangeSearchbar()
{
	CString text;
	searchBar.GetWindowTextW(text);
	CT2CA str(text);
	loadSugestions(repoSugestion.find_all_starting_with(string(str)));
}

void CHabitInternshipDlg::OnCbnSelchangeCategory() {
	combo_box.GetLBText(combo_box.GetCurSel(), combo_box_text);
	UpdateData(FALSE);
	suggestions.ResetContent();
	CT2CA str(combo_box_text);
	std::string cat(str);
	if (cat != "All") {
		int category = repoCategory.find_category(cat).get_ID();
		for (auto sugestion : repoSugestion.find_by_category(category))
			suggestions.AddString(CString(sugestion.get_name().c_str()));
	}
	else loadSugestions(repoSugestion.find_all_suggestions());
}

void CHabitInternshipDlg::initialize_combo_box() {
	vector<Category> categories = repoCategory.find_all_category();
	for (auto category : categories)
		combo_box.AddString(CString(category.get_name().c_str()));
	combo_box.AddString(_T("All"));
}


void CHabitInternshipDlg::OnBnClickedDone()
{
	auto selIndex = todos.GetCurSel();
	if (selIndex != LB_ERR) {
		auto todoID = todos.GetItemData(selIndex);
		repoToDo.done_to_do(todoID);
		todos.DeleteString(todos.GetCurSel());
		loadToDos();
		loadHabits();
		points.SetWindowTextW(CString(std::to_string(repoToDo.find_score()).c_str()));
	}
}

void CHabitInternshipDlg::initialize_combo_c() {
	vector<Category> categories = repoCategory.find_all_category();
	for (auto category : categories)
		combo_c.AddString(CString(category.get_name().c_str()));
}


void CHabitInternshipDlg::OnBnClickedAdd() {
	CString h_name;
	name.GetWindowTextW(h_name);
	CT2CA habit_name(h_name);
	CString h_description;
	description.GetWindowTextW(h_description);
	CT2CA habit_description(h_description);
	CString h_category;
	combo_c.GetLBText(combo_c.GetCurSel(), combo_t);
	UpdateData(FALSE);
	CT2CA habit_category(combo_t);
	int category_id = repoCategory.find_category(std::string(habit_category)).get_ID();
	ToDo toDo = ToDo(std::string(habit_name), std::string(habit_description), category_id, false, Date(1, 1, 1));
	repoToDo.save_to_do(toDo);
	loadSugestions(repoSugestion.find_all_suggestions());
	loadToDos();
}

