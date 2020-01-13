#ifndef _COM_ISREG_HDR_
#define _COM_ISREG_HDR_

extern void comRegIsErrorMessageShow(GtkLabel *,int);

typedef struct _ComISRegHandleData{
    GtkWidget *comRegWindow;

    //企業インターンシップ登録画面
    GtkComboBox *yearCombo;
    GtkComboBox *monthCombo;
    GtkComboBox *dayCombo;
    // GtkComboBox *daycountCombo;
    GtkLabel *yearLabel;
    GtkLabel *monthLabel;
    GtkLabel *dayLabel;
    // GtkEntry *IsThemeEntry;
    // GtkLabel *daycountLabel;
    GtkButton *isRegistButton;
    GtkButton *isRegCancelButton;
    GtkTreeSelection *selection;
    //自社インターン情報取得画面
    GtkButton *isListSearchButton;
    GtkTreeView *isResList;
    GtkLabel *isListStatusLabel;


}ComISRegHandleData;



// typedef struct _ComISRegInfo{
//     gint resRow;
//     gint Year;
//     gint isDays;
//     gchararray isId;
//     gchararray comId;
//     gchararray isTheme;
//     gchararray isDate;
// }ComISRegInfo;

//プロトコルコマンド

#define ISLIST_C "ISLIST_C"

#endif