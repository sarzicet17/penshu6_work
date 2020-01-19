#ifndef _TEACHER_ISENTRY_HDR_
#define _TEACHER_ISENTRY_HDR_

typedef struct _teacherISEntryWindowhandleData{
    GtkWidget *entryWindow;


    //エントリー登録画面
    GtkEntry *stuIdEntry;
    GtkEntry *isIdEntry;
    GtkLabel *regStatLabel;
    //年度別検索画面
    // GtkComboBox *yearCombo;
    GtkEntry *yearEntry_search;
    GtkTreeView *yearSearchTree;
    GtkLabel *searchByYearStatus;
    //学生エントリ情報取得画面
    GtkRadioButton *sortSelectRadioButton[2];
    GtkEntry *yearEntry_foundEntry;
    GtkTreeView *studentEntryTree;
    GtkTreeView *companyEntryTree;
    GtkLabel *foundEntryInfo;

    GtkTreeViewColumn *entrycolumn1;
    GtkTreeViewColumn *entrycolumn2;
    GtkTreeViewColumn *entrycolumn3;
    GtkTreeViewColumn *entrycolumn4;
    GtkTreeViewColumn *entrycolumn5;
    GtkTreeViewColumn *entrycolumn6;
    GtkTreeViewColumn *entrycolumn7;

}TeacherISEntryWindowHandleData;

#define ENTRY "ENTRY"
#define ISLIST_T "ISLIST_T"
#define STUBRO "STUBRO"
#define SORT_BY_STUDENT_FLAG "0"
#define SORT_BY_COMAPNY_FLAG "1"


//extern void TeacherIsEntryErrorMessage(GtkLabel *errorLabel, int errorCode);

#endif