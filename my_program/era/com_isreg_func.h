#ifndef _COM_ISREG_HDR_
#define _COM_ISREG_HDR_

#include <gtk/gtk.h>

typedef struct _ComISRegHandleData{
    GtkWidget *comRegWindow;

    //企業インターンシップ登録画面
    GtkComboBox *yearCombo;
    GtkComboBox *monthCombo;
    GtkComboBox *dayCombo;
    GtkComboBox *daycountCombo;
    GtkLabel *yearLabel;
    GtkLabel *monthLabel;
    GtkLabel *dayLabel;
    GtkLabel *daycountLabel;
    GtkButton *isRegistButton;
    GtkButton *isRegCancelButton;
    GtkTreeSelection *selection;
    //自社インターン情報取得画面
    GtkButton *isListSearchButton;
    GtkTreeView *isInfoResList;

}ComISRegHandleData;

typedef struct _ComISRegInfo{
    gint resRow;
    gint Year;
    gint isDays;
    gchararray isId;
    gchararray comId;
    gchararray isTheme;
    gchararray isDate;
}ComISRegInfo;

#endif