#include "intern_client.h"
#include "com_isreg_func.h"

extern int isRegWindowShowFlag; //インターン登録画面表示フラグ


G_MODULE_EXPORT void cb_cancel_com_isreg(GtkButton *button,gpointer data){
    MainHandleData *hData;
    ComISRegHandleData *isreghData;

    hData = (ComISRegHandleData *)data;

    isreghData = hData->isreghData;

    //ウィンドウを隠す
    gtk_widget_hide(isreghData->comRegWindow);
    free(hData->isreghData);

    isRegWindowShowFlag = 0;
}


//自社インターン情報検索機能
G_MODULE_EXPORT void cb_com_islist_search(GtkButton *button,gpointer data){
    MainHandleData *hData;
    GtkTreeSelection *isreg_selection;
    GtkTreeIter isreg_iter;
    GtkListStore *isreg_model;

    ComISRegHandleData *isreghData;

    //送受信用バッファ
    char sendBuf[BUFSIZE];
    char recvBuf[BUFSIZE_MAX];

    char *records[RECORD_MAX];
    char response[BUFSIZE];
    int recordCount,sendLen,recvLen,i,n;

    //リストストアセット用バッファ

    char param1[BUFSIZE];
    char param2[BUFSIZE]; //開催年度
    char param3[BUFSIZE]; //ISID
    char param4[BUFSIZE]; //担当ID
    char param5[BUFSIZE]; //インターン名
    char param6[BUFSIZE]; //予定実施日
    char param7[BUFSIZE]; //予定実施日数

    hData = (MainHandleData *)data;
    isreghData = hData ->isreghData;

    isreg_model = GTK_LIST_STORE(gtk_tree_view_get_model(isreghData->isResList));

    if(g_soc > 0){
        sendLen = sprintf(sendBuf,"%s %s",ISLIST_C,ENTER);
        send(g_soc,sendBuf,sendLen,0);
        printf("C->S: %s\n",sendBuf);
        recvLen = recv_data(g_soc,recvBuf,BUFSIZE_MAX);
        //レコードに分割
        recordCount = record_division(recvBuf,records);
        printf("S->C: %s\n",recvBuf);

        memset(response,0,BUFSIZE);
        memset(param1,0,BUFSIZE);
        memset(param2,0,BUFSIZE);
        memset(param3,0,BUFSIZE);
        memset(param4,0,BUFSIZE);
        memset(param5,0,BUFSIZE);
        memset(param6,0,BUFSIZE);
        memset(param7,0,BUFSIZE);

        n = sscanf(records[0],"%s %s",response,param1);

        //エラーチェック
        if(strcmp(response,OK_STAT) != 0){
            showErrorMsg(isreghData->isListStatusLabel,atoi(param1));
            gtk_list_store_clear(isreg_model);
            return;
        }
        
        //受信した学生リストをツリービューに表示する
        gtk_list_store_clear(isreg_model);
        for(i=1;i<atoi(param1)+1;i++){
            n = sscanf(records[i],"%s %s %s %s %s %s",param2,param3,param4,param5,param6,param7);
            gtk_list_store_append(isreg_model,&isreg_iter);
            gtk_list_store_set(isreg_model,&isreg_iter,0,param2,1,param3,2,param4,3,param5,4,param6,5,param7,-1);
        }

    }    

}

G_MODULE_EXPORT void cb_isreg_exec(GtkButton *button,gpointer data){
    MainHandleData *hData;
    ComISRegHandleData *isreghData;

    //入力文字列バッファ
    const gchar *internThemeStr;
    const gchar *yearStr,*monthStr,*dayStr,*daycountStr;

    char sendBuf[BUFSIZE_MAX];
    char recvBuf[BUFSIZE_MAX];
    char *records[RECORD_MAX];

    char response[BUFSIZE];
    char param1[BUFSIZE]; //インターンシップID


    int recordCount,n,dateValidatedFlag;
    int sendLen,recvLen;
    extern int g_soc;

    printf("call:cb_isreg_exec\n");

    hData = (ComISRegHandleData *)data;
    isreghData = hData ->isreghData;

    internThemeStr = gtk_entry_get_text(isreghData->IsThemeEntry);
    yearStr = gtk_entry_get_text(isreghData->yearEntry);
    monthStr = gtk_entry_get_text(isreghData->monthEntry);
    dayStr = gtk_entry_get_text(isreghData->dayEntry);
    daycountStr = gtk_entry_get_text(isreghData->daycountEntry);

    if( strlen(internThemeStr) < 1){
        gtk_label_set_text(isreghData->comisRegStatLabel,"ERROR:インターン名がありません");
        return;
    }

    dateValidatedFlag = dateEntryValidation(yearStr,monthStr,dayStr);

    if(dateValidatedFlag < 0){
        gtk_label_set_text(isreghData->comisRegStatLabel,"ERROR:有効な日付ではありません。");
        return;
    }

    sendLen = sprintf(sendBuf,"%s %s %s-%s-%s %s %s",REGIS,internThemeStr,yearStr,monthStr,dayStr,daycountStr,ENTER);

    if(g_soc > 0){
        send(g_soc,sendBuf,sendLen,0);
        printf("C->S: %s\n",sendBuf);
        recvLen = recv_data(g_soc,recvBuf,BUFSIZE_MAX);
        recordCount = record_division(recvBuf,records);
        printf("S->C: %s\n",recvBuf);

        memset(response,0,BUFSIZE);
        memset(param1,0,BUFSIZE);

        n = sscanf(records[0],"%s %s",response,param1);

        if(strcmp(response,OK_STAT) != 0){
            showErrorMsg(isreghData->comisRegStatLabel,atoi(param1));
            return;
        }else{
            gtk_label_set_text(isreghData->comisRegStatLabel,"登録完了");
        }
    }
}

/*
int dateEntryValidation(const gchar * __year,const gchar * __month, const gchar * __day)
    日付エントリの入力値の検証を行う（うるう年の考慮もあり）
    返り値:0(正常)
    返り値:-1(日付に誤りあり)
*/

int dateEntryValidation(const gchar * __year,const gchar * __month, const gchar * __day){
    int year,month,day,last_day;
    year = atoi(__year);
    month = atoi(__month);
    day = atoi(__day);

    printf("dateEntryValidation:args __year:%d,__month,%d,__day:%d\n",year,month,day);

    int fin_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // 月の範囲
    if( month < 1 || month > 12 ){
        printf("WrongMonthLength:%d\n",month);
        return -1;
    }
    // 日の範囲
    last_day = fin_days[ month -1 ];
    if( month == 2 ) {
        if( year % 4 == 0 && year % 100 != 0 || year % 400 == 0 )
            last_day = 29;  // うるう年なら末日は29
    }
    if( day < 1 || day > last_day ){
        printf("WrongDayLength:day = %d,last_day = %d\n",day,last_day);
        return -1;
    }

    return 0;
}
