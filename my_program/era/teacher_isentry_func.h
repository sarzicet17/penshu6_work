#ifndef _TEACHER_ISENTRY_HDR_
#define _TEACHER_ISENTRY_HDR_

typedef struct _teacherISEntryWindowhandleData{
    GtkWidget *entryWindow;


    //エントリー登録画面
    GtkEntry *stuIdEntry;
    GtkEntry *isIdEntry;
    GtkLabel *regStatLabel;
    //年度別検索画面
    GtkComboBox *yearCombo;
    GtkTreeView *yearSearchTree;
    GtkLabel *searchByYearStatus;
    //学生エントリ情報取得画面
    GtkRadioButton *sortbyStu;
    GtkRadioButton *sortbyCom;
    GtkTreeView *studentEntryTree;
    GtkTreeView *companyEntryTree;
    GtkLabel *foundEntryInfo;

}TeacherISEntryWindowHandleData;

#define ENTRY "ENTRY"
#define ISLIST_T "ISLIST_T"
#define STUBRO "STUBRO"

extern void TeacherIsEntryErrorMessage(GtkLabel *errorLabel, int errorCode);

#endif