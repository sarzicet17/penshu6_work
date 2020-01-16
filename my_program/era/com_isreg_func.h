#ifndef _COM_ISREG_HDR_
#define _COM_ISREG_HDR_

extern void comRegIsErrorMessageShow(GtkLabel *,int);
extern int dateEntryValidation(const gchar *__year,const gchar *__month,const gchar *__day);


typedef struct _ComISRegHandleData{
    GtkWidget *comRegWindow;

    //企業インターンシップ登録画面
    GtkEntry *yearEntry;
    GtkEntry *monthEntry;
    GtkEntry *dayEntry;
    GtkEntry *daycountEntry;
    // GtkLabel *yearLabel;
    // GtkLabel *monthLabel;
    // GtkLabel *dayLabel;
    // GtkLabel *daycountLabel;
    GtkEntry *IsThemeEntry;
    GtkButton *isRegistButton;
    GtkButton *isRegCancelButton;
    GtkLabel *comisRegStatLabel;
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
#define REGIS "REGIS"

#endif