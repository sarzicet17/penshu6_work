#include "intern_client.h"
#include "teacher_isentry_func.h"
#include <time.h>

extern int teacherisEntryWindowShowFlag;


//画面を閉じる処理
G_MODULE_EXPORT void cb_t_isentry_close(GtkButton *button,gpointer data){
    MainHandleData *hData;
    TeacherISEntryWindowHandleData *isentryhData;

    hData = (TeacherISEntryWindowHandleData *)data;

    isentryhData = hData ->isentryhData;

    gtk_widget_hide(isentryhData->entryWindow);
    free(hData->isentryhData);

}


//ラジオボタン

//年度別検索を行う際、コンボボックスに年度をセットする

// G_MODULE_EXPORT void cb_set_year_combo(GtkComboBox *combobox, gpointer data){
//     MainHandleData *hData;
//     TeacherISEntryWindowHandleData *isentryhData;

//     hData = (TeacherISEntryWindowHandleData *)data;
//     isentryhData = hData ->isentryhData;
//     GtkTreeModel  *model;
//     GtkTreeIter   　iter;

//     const gchar *yearValue = NULL;

//     //現在年の取得
//     time_t timer;
//     struct tm *local;
//     int year,i;

//     timer = time(NULL);
//     local = localtime(&timer);
//     year = local->tm_year + 1900;

//     yearValue = year;

//     gtk_list_store_append(model, &iter);
//     gtk_list_store_set(model, &iter, 0, yearValue, -1);

// }



G_MODULE_EXPORT void cb_submit_entry(GtkButton *button, gpointer data){
    MainHandleData *hData;
    TeacherISEntryWindowHandleData *isentryhData;

    //文字入力
    const gchar *internIDStr;
    const gchar *studentIDStr;

    //送受信バッファ
    char sendBuf[BUFSIZE_MAX];
    char recvBuf[BUFSIZE_MAX];
    char *records[RECORD_MAX];
    
    //レスポンス格納バッファ
    char response[BUFSIZE];
    char param1[BUFSIZE],param2[BUFSIZE];

    int recordCount,n;
    int sendLen,recvLen;
    extern int g_soc;

    printf("call:cb_submit_entry\n");
    //引数をメイン画面主要構造体にキャスト
    hData = (TeacherISEntryWindowHandleData *)data;
    isentryhData = hData ->isentryhData;

    internIDStr = gtk_entry_get_text(isentryhData->isIdEntry);
    studentIDStr = gtk_entry_get_text(isentryhData->stuIdEntry);
    
    if(strlen(internIDStr) < 1 || strlen(studentIDStr) < 1){
        gtk_label_set_text(isentryhData->regStatLabel,"ERROR:未記入の項目があります");
        return;
    }

    sendLen = sprintf(sendBuf,"%s %s %s %s",ENTRY,internIDStr,studentIDStr,ENTER);

    if (g_soc > 0){
        send(g_soc,sendBuf,sendLen,0);
        printf("C->S: %s",sendBuf);
        recvLen = recv_data(g_soc,recvBuf,BUFSIZE_MAX);
        recordCount = record_division(recvBuf,records);
        printf("S->C: %s\n",recvBuf);

        memset(response,0,BUFSIZE);
        memset(param1,0,BUFSIZE);
        memset(param2,0,BUFSIZE);

        n = sscanf(records[0],"%s %s %s",response,param1,param2);

        if(strcmp(response,OK_STAT) != 0){
            TeacherIsEntryErrorMessage(isentryhData->regStatLabel,atoi(param1));
            return;
        }
    }
}


//年度別検索
G_MODULE_EXPORT void cb_t_isentry_foryearsearch(GtkButton *button, gpointer data){
    printf("call: cb_t_isentry_foryearsearch\n");
    MainHandleData *hData;
    TeacherISEntryWindowHandleData *isentryhData;

    hData = (TeacherISEntryWindowHandleData *)data;

    isentryhData = hData ->isentryhData;

    const gchar *yearStr;

    //ツリービューモデル
    GtkListStore *model;
    GtkTreeIter iter;

    //送受信バッファ
    char sendBuf[BUFSIZE],recvBuf[BUFSIZE_MAX];
    char *records[RECORD_MAX];
    char response[BUFSIZE];
    int i,n,recordCount;
    int sendLen,recvLen;

    char param1[BUFSIZE];
    char param2[BUFSIZE]; //インターンID
    char param3[BUFSIZE]; //担当者ID
    char param4[BUFSIZE]; //企業名
    char param5[BUFSIZE]; //インターンタイトル
    char param6[BUFSIZE]; //インターン開催日
    char param7[BUFSIZE]; //日数

    yearStr = gtk_entry_get_text(isentryhData->yearEntry_search);

    model = GTK_LIST_STORE(gtk_tree_view_get_model(isentryhData->yearSearchTree));

    if(strlen(yearStr) < 1){
        gtk_list_store_clear(model);
        gtk_label_set_text(isentryhData->searchByYearStatus,"ERROR:年度指定がありません");
        return;
    }

    if(g_soc > 0){
        sendLen = sprintf(sendBuf,"%s %s %s",ISLIST_T,yearStr,ENTER);
        send(g_soc,sendBuf,sendLen,0);
        printf("C->S: %s\n",sendBuf);
        recvLen = recv_data(g_soc,recvBuf,BUFSIZE_MAX);

        recordCount = record_division(recvBuf,records);
        printf("S->C: %s\n",recvBuf);
        //受信結果を分割する
        memset(response,0,BUFSIZE);

        memset(param1,0,BUFSIZE);
        memset(param2,0,BUFSIZE);
        memset(param3,0,BUFSIZE);
        memset(param4,0,BUFSIZE);
        memset(param5,0,BUFSIZE);
        memset(param6,0,BUFSIZE);
        memset(param7,0,BUFSIZE);

    //レスポンス解析
        n = sscanf(records[0],"%s %s",response,param1);

    //エラーチェク
        if(strcmp(response,OK_STAT) != 0){
            TeacherIsEntryErrorMessage(isentryhData->searchByYearStatus,atoi(param1));
            gtk_list_store_clear(model);
            return;
        }

        gtk_label_set_text(isentryhData->searchByYearStatus,param1);

    //ツリービューに受信データの反映

        for(i=1;i<atoi(param1)+1;i++){
            n = sscanf(records[i],"%s %s %s %s %s %s",param2,param3,param4,param5,param6,param7);
            gtk_list_store_append(model,&iter);
            gtk_list_store_set(model,&iter,0,param2,1,param3,2,param4,3,param5,4,param6,5,param7,-1);
        }
    }
}

//学生エントリ情報取得

// G_MODULE_EXPORT void cb_t_isentry_find_stuentry(GtkButton *button, gpointer data){
//     MainHandleData *hData;
//     TeacherISEntryWindowHandleData *isentryhData;

//     hData = (TeacherISEntryWindowHandleData *)data;

//     isentryhData = hData ->isentryhData;

//     //ツリービューモデル
//     GtkListStore *forStuFindModel;
//     GtkTreeIter forStuFindIter:

//     //送受信バッファ
// }

G_MODULE_EXPORT void cb_t_stuentry_search(GtkButton *button,gpointer data){
    MainHandleData *hData;

    GtkTreeIter stu_entry_iter;
    GtkTreeIter com_entry_iter;

    GtkListStore *stu_entry_list_model;
    GtkListStore *com_entry_list_model;

    const gchar *yearStr;

    TeacherISEntryWindowHandleData *isentryhData;

    char sendBuf[BUFSIZE];
    char recvBuf[BUFSIZE_MAX];

    char *records[RECORD_MAX];
    char response[BUFSIZE];
    int recordCount,sendLen,recvLen,i,n;

    char param1[BUFSIZE];
    char param2[BUFSIZE];
    char param3[BUFSIZE];
    char param4[BUFSIZE];
    char param5[BUFSIZE];
    char param6[BUFSIZE];
    char param7[BUFSIZE];
    char param8[BUFSIZE];

    printf("call:cb_t_stuentry_search\n");

    hData = (MainHandleData *)data;
    isentryhData = hData->isentryhData;

    yearStr = gtk_entry_get_text(isentryhData->yearEntry_foundEntry);

    stu_entry_list_model = GTK_LIST_STORE(gtk_tree_view_get_model(isentryhData->studentEntryTree));

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(isentryhData->sortSelectRadioButton[0])) == TRUE){
        sendLen = sprintf(sendBuf,"%s %s %s %s",STUBRO,yearStr,SORT_BY_STUDENT_FLAG,ENTER);
    }else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(isentryhData->sortSelectRadioButton[1])) == TRUE){
        sendLen = sprintf(sendBuf,"%s %s %s %s",STUBRO,yearStr,SORT_BY_COMAPNY_FLAG,ENTER);
    }

    if(strlen(yearStr) < 1){
        gtk_list_store_clear(stu_entry_list_model);
        gtk_label_set_text(isentryhData->foundEntryInfo,"ERROR:年度が入力されていません");
        return;
    }

    if(g_soc > 0){
        send(g_soc,sendBuf,sendLen,0);
        printf("C->S: %s",sendBuf);
        recvLen = recv_data(g_soc,recvBuf,BUFSIZE_MAX);
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
        memset(param8,0,BUFSIZE);

        n = sscanf(records[0],"%s %s",response,param1);

        if(strcmp(response,OK_STAT) != 0){
            TeacherIsEntryErrorMessage(isentryhData->foundEntryInfo,atoi(param1)); 
            gtk_list_store_clear(stu_entry_list_model);
            return;
        }

        gtk_list_store_clear(stu_entry_list_model);

        for(i=1;i<atoi(param1)+1;i++){
            n = sscanf(records[i],"%s %s %s %s %s %s %s",param2,param3,param4,param5,param6,param7,param8);
            gtk_list_store_append(stu_entry_list_model,&stu_entry_iter);
            gtk_list_store_set(stu_entry_list_model,&stu_entry_iter,0,param2,1,param3,2,param4,3,param5,4,param6,5,param7,6,param8,-1);
        }

    }

}

void TeacherIsEntryErrorMessage(GtkLabel *statLabel, int statusCode){
    switch(statusCode){
        break;
        default:
            gtk_label_set_text(statLabel,"ERROR:FATAL");
            break;
        case 100:
            gtk_label_set_text(statLabel,"ERROR:コマンドリクエストの引数エラー");
            break;
        case 200:
            gtk_label_set_text(statLabel,"ERROR:リクエストコマンドがありません");
            break;       
        case 300:
            gtk_label_set_text(statLabel,"ERROR:データベースエラーです");
            break;
        case 1500:
            gtk_label_set_text(statLabel,"ERROR:すでにエントリ登録されています");
            break;
        case 1501:
            gtk_label_set_text(statLabel,"ERROR:学生IDがありません");
            break;
        case 1600:
            gtk_label_set_text(statLabel,"ERROR:インターンシップIDがありません");
            break;
        case 1601:
            gtk_label_set_text(statLabel,"ERROR:インターンシップIDに対するエントリがありません");
    }
}