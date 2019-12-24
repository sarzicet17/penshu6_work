/**
 *  login.h
 **/

#ifndef _INCLUDE_LOGIN_
#define _INCLUDE_LOGIN_

//*** ログイン画面のWidget ***//
typedef struct _loginHandleData{
  GtkWidget *loginWindow;   //ウィンドウ
  GtkLabel  *loginLabel;    //ログインラベル
  GtkEntry  *idEntry;       //ID
  GtkEntry  *passwordEntry; //パスワード
  GtkLabel  *errorLabel;    //エラー表示用ラベル
}LoginHandleData;

#endif
