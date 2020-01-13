/**
 * cb_login.c
 **/

#include "intern_client.h"
#include "login.h"

void showErrorMsg(GtkLabel *erroLabel, int errorCode);
void set_capability_enable(MainHandleData *hData, char *userId, char *userName, int permissionId);
/**
 * コールバック関数：「キャンセル」ボタンのクリックによりウィンドウを非表示にする
 * cb_login_cancel
 **/
G_MODULE_EXPORT void cb_login_cancel(GtkButton *button, gpointer data){
  MainHandleData *hData;  //メイン画面の主要Widget保持用
  LoginHandleData *loginHData; //ログイン画面の主要Widget保持用

  printf("call: cb_login_cancel\n");

  /* 引数(data)をメイン画面主要Wiget保持用構造体型にキャスト */  
  hData = (MainHandleData *)data;
  /* ログイン画面主要Widget保持用構造体を取得 */
  loginHData = hData->loginHData;

  /* ログイン画面（ウィンドウ）を非表示 */
  gtk_widget_hide(loginHData->loginWindow);
  /* ログイン画面主要Widget保持構造体を破棄（メモリ開放) */
  free(hData->loginHData);
}

/**
 * コールバック関数：「ログイン」ボタンのクリックによるログイン処理
 * cb_login_exec
 **/
G_MODULE_EXPORT void cb_login_exec(GtkButton *button, gpointer data){
  MainHandleData  *hData;      //メイン画面の主要Widget保持用
  LoginHandleData *loginHData; //ログイン画面の主要Widget保持用
  const gchar *loginStr;
  const gchar *userIdStr;
  const gchar *userPassStr;
  char sendBuf[BUFSIZE_MAX], recvBuf[BUFSIZE_MAX];
  char *records[RECORD_MAX];
  char response[BUFSIZE], param1[BUFSIZE], param2[BUFSIZE];
  int recordCount, n;
  int sendLen, recvLen;
  int permissionId;
  extern int g_soc;

  printf("call: cb_login_exec\n");
  
  /* 引数(data)をメイン画面主要Widget保持用構造体型にキャスト */
  hData = (MainHandleData *)data;
  loginHData = hData->loginHData;

  loginStr = gtk_label_get_text(loginHData->loginLabel);
  userIdStr = gtk_entry_get_text(loginHData->idEntry);
  userPassStr = gtk_entry_get_text(loginHData->passwordEntry);

  if(strlen(userIdStr) < 1){
    gtk_label_set_text(loginHData->errorLabel, "ERROR: ユーザIDを入力してください");
    return;
  }
  if(strlen(userPassStr) < 1){
    gtk_label_set_text(loginHData->errorLabel, "ERROR: パスワードを入力してください");
    return;
  }

  if(strcmp(loginStr, "教員ログイン") == 0){
    permissionId = 1;
    sendLen = sprintf(sendBuf, "%s %s %s %s",LOGIN_T, userIdStr, userPassStr, ENTER);
  }else if(strcmp(loginStr, "企業ログイン") == 0){
    permissionId = 2;
    sendLen = sprintf(sendBuf, "%s %s %s %s",LOGIN_C, userIdStr, userPassStr, ENTER);
  }else if(strcmp(loginStr, "学生ログイン") == 0){
    permissionId = 3;
    sendLen = sprintf(sendBuf, "%s %s %s %s",LOGIN_S, userIdStr, userPassStr, ENTER);
  }else{
    permissionId = -1;
    return;
  }

  if(g_soc > 0){
    send(g_soc, sendBuf, sendLen, 0);
    printf("C->S: %s",sendBuf);
    recvLen = recv_data(g_soc, recvBuf,BUFSIZE_MAX);
    recordCount = record_division(recvBuf, records);
    printf("S->C: %s\n",recvBuf);

    memset(response,0,BUFSIZE);
    memset(param1,0,BUFSIZE);
    memset(param2,0,BUFSIZE);

    n = sscanf(records[0],"%s %s %s",response,param1,param2);

    if(strcmp(response, OK_STAT) != 0){
      /* エラーメッセージを表示 */
      showErrorMsg(loginHData->errorLabel, atoi(param1));
      return;
    }

    /* set_capability_enable関数を呼び出す */
    set_capability_enable(hData,param1,param2,permissionId);
  }

  /* ログイン画面（ウィンドウ）を非表示 */
  gtk_widget_hide(loginHData->loginWindow);
  /* ログイン画面主要Widget保持構造体を破棄（メモリ開放) */
  free(hData->loginHData);
}

/**
 * 権限によるメイン画面機能の使用許可設定
 * set_capability_enable 
 *  [PARAMETER]
 *   MainHandleData *hData :  メイン画面主要Widget保持用構造体のポインタ
 *   char *userId          :  ユーザID
 *   char *userName        :  ユーザ名
 *   int permissionId      :  権限ID
 *  [RETURN]
 *    NONE
 **/
void set_capability_enable(MainHandleData *hData, char *userId, char *userName, int permissionId){
  
  gtk_label_set_text(hData->userIdLabel, userId);
  gtk_label_set_text(hData->userNameLabel, userName);

  switch(permissionId){
  case 1: //教員
    gtk_widget_set_sensitive( GTK_WIDGET(hData->studentRegisterButton), TRUE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->companyRegisterButton), TRUE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->internEntryButton), TRUE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->internStudentDisplayButton), TRUE );
    gtk_widget_set_sensitive( GTK_WIDGET(hData->gradeDisplayButton ), TRUE );
    
    gtk_widget_set_sensitive( GTK_WIDGET(hData->internRegisterButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->entryStudentDisplayButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->particicationDecideButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->gradeInputButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->passwordChangeButton), FALSE );

    gtk_widget_set_sensitive( GTK_WIDGET(hData->internDisplayButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->selfEvaluationButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->adviceDisplayButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->stuPasswordChangeButton), FALSE );  
    break;  
  case 2: //企業
    gtk_widget_set_sensitive( GTK_WIDGET(hData->studentRegisterButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->companyRegisterButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->internEntryButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->internStudentDisplayButton), FALSE );
    gtk_widget_set_sensitive( GTK_WIDGET(hData->gradeDisplayButton ), FALSE );
    
    gtk_widget_set_sensitive( GTK_WIDGET(hData->internRegisterButton), TRUE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->entryStudentDisplayButton), TRUE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->particicationDecideButton), TRUE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->gradeInputButton), TRUE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->passwordChangeButton), TRUE );

    gtk_widget_set_sensitive( GTK_WIDGET(hData->internDisplayButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->selfEvaluationButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->adviceDisplayButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->stuPasswordChangeButton), FALSE );  
    break;

  case 3: //学生
    gtk_widget_set_sensitive( GTK_WIDGET(hData->studentRegisterButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->companyRegisterButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->internEntryButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->internStudentDisplayButton), FALSE );
    gtk_widget_set_sensitive( GTK_WIDGET(hData->gradeDisplayButton ), FALSE );
    
    gtk_widget_set_sensitive( GTK_WIDGET(hData->internRegisterButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->entryStudentDisplayButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->particicationDecideButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->gradeInputButton), FALSE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->passwordChangeButton), FALSE );

    gtk_widget_set_sensitive( GTK_WIDGET(hData->internDisplayButton), TRUE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->selfEvaluationButton), TRUE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->adviceDisplayButton), TRUE );  
    gtk_widget_set_sensitive( GTK_WIDGET(hData->stuPasswordChangeButton), TRUE );  
    break;

  }
  
  g_permissionId = permissionId;  //権限IDをグローバル変数に設定

}

/**
 * ログインエラーメッセージ表示
 * showErrorMsg 
 *  [PARAMETER]
 *   GtkLabel *errorLabel   :  ログイン画面のエラー表示用GtkLabelのポインタ
 *   int errorCode          :  エラーレスポンスコード
 *  [RETURN]
 *    NONE
 **/
void showErrorMsg(GtkLabel *errorLabel, int errorCode){
  
  switch(errorCode){
  case E_CODE_1 :
    gtk_label_set_text(errorLabel, "ERROR:コマンドリクエストの引数エラー");
    break;
  case E_CODE_3 :
    gtk_label_set_text(errorLabel, "ERROR:データベースエラー");
    break;
  case E_CODE_5 :
    gtk_label_set_text(errorLabel, "ERROR:ログインエラー");
    break;
  default:
    gtk_label_set_text(errorLabel, "ERROR:致命的なエラーが発生しました");
  }
}
