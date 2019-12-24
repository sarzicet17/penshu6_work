/**
 * intern_client.h
 **/

#ifndef _INCLUDE_INTERN_
#define _INCLUDE_INTERN_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <gtk/gtk.h>

#include "login.h"
#include "teacher_isentry_func.h"
#include "com_isreg_func.h"
#define BUFSIZE 1024
#define BUFSIZE_MAX 4096
#define RECORD_MAX 1000
#define ENTER "\n"
#define DATA_END ".\n" //レスポンスデータの最終デリミタ

// プロトコルコマンド 
#define LOGIN_T  "LOGIN_T"  //ユーザ認証(教員)
#define LOGIN_C  "LOGIN_C"  //ユーザ認証(企業)
#define LOGIN_S  "LOGIN_S"  //ユーザ認証(学生)


// レスポンスステータス 
#define OK_STAT   "+OK"     //成功
#define ER_STAT   "-ERR"    //失敗

// エラーコード 
#define E_CODE_1    100  //リクエストコマンドの引数エラー
#define E_CODE_2    200  //リクエストコマンドが存在しない
#define E_CODE_3    300  //データベースエラー
#define E_CODE_4    400  //パスワードが８桁未満
#define E_CODE_5    500  //[認証] ユーザ名またはパスワードが一致しない
#define E_CODE_6    600  //[パスワード変更] ユーザ名またはパスワードが一致しない
#define E_CODE_9    900  //[権限] 許可されていない機能のプロトコルコマンド使用

#define E_CODE_1100     1100  //[学生] すでに学生が登録済み
#define E_CODE_1200     1200  //[企業] すでに企業が登録済み
#define E_CODE_1300     1300  //[企業担当者] すでに企業担当者が登録済み
#define E_CODE_1301     1301  //[企業担当者] 入力された企業IDが存在しない
#define E_CODE_1400     1400  //[IS] 入力された企業担当者IDが存在しない
#define E_CODE_1401     1401  //[IS] 入力された年度のIS情報がない
#define E_CODE_1402     1402  //[IS] 所属企業のIS情報がない
#define E_CODE_1500     1500  //[ISエントリ] すでにISエントリが登録済み
#define E_CODE_1501     1501  //[ISエントリ] 入力された学生IDが存在しない
#define E_CODE_1502     1502  //[ISエントリ] 入力されたISIDが存在しない
#define E_CODE_1600     1600  //[ISイベント] 入力されたISIDが存在しない
#define E_CODE_1601     1601  //[ISイベント] 入力されたISIDに対するISエントリが存在しない
#define E_CODE_1602     1602  //[ISイベント] 当該学生IDに対するISイベント(IS情報）が存在しない
#define E_CODE_1700     1700  //[自己評価] 入力されたISIDと学生IDに対するISイベントが存在しない
#define E_CODE_1701     1701  //[自己評価] 入力実施日が入力可能期間ではない 
#define E_CODE_1702     1702  //[自己評価] 自己評価の評価値が適切な値でない
#define E_CODE_1703     1703  //[自己評価] 入力当日が入力可能期間ではない
#define E_CODE_1704     1704  //[自己評価] 入力されたISIDと学生IDの自己評価が存在しない
#define E_CODE_1800     1800  //[評定] 入力されたISIDと学生IDに対するISイベントが存在しない
#define E_CODE_1801     1801  //[評定] 評定書の評価値が適切な値でない
#define E_CODE_1802     1802  //[評定] 評定はすでに確定済み
#define E_CODE_1803     1803  //[評定] 入力されたISIDと学生IDに対する評定が存在しない
#define E_CODE_1804     1804  //[評定] 入力されたISIDに関する評定が存在しない
#define E_CODE_1805     1805  //[評定] 入力された年度に関する評定が存在しない
#define E_CODE_1806     1806  //[評定] 入力されたISIDと学生IDに対するアドバイスが存在しない
#define E_CODE_1900     1900  //[IS参加学生] 入力年度のIS参加学生がいない
#define E_CODE_1901     1901  //[IS参加学生] 入力年度のIS情報がない
#define E_CODE_2000     2000  //[IS提供企業] 入力年度のIS提供企業がない


// 権限 

extern int g_soc;             //通信用ソケットディスクリプタ
extern int g_permissionId;    //権限ID 教員:1 企業:2 学生:3


//*** メイン画面のWidget with ログイン画面のWidget ***//
typedef struct _mainHandleData{
  GtkWidget  *mainWindow;             //メインウィンドウ
  GtkLabel   *userIdLabel;            //UserIdラベル
  GtkLabel   *userNameLabel;          //UserNameラベル
  GtkLabel   *serverInfoLabel;        //サーバ接続表示ラベル
  /*** 教員 ***/
  GtkButton  *studentRegisterButton;  //学生登録ボタン
  GtkButton  *companyRegisterButton;  //企業・企業担当者登録ボタン
  GtkButton  *internEntryButton;      //インターンシップエントリ/ボタン
  GtkButton  *internStudentDisplayButton;  //インターンシップ参加決定学生閲覧ボタン
  GtkButton  *gradeDisplayButton;     //評定閲覧ボタン
  
  TeacherISEntryWindowHandleData *isentryhData;
  
  /*** 企業 ***/
  GtkButton  *internRegisterButton;   //インターンシップ登録ボタン
  GtkButton  *entryStudentDisplayButton; //インターンシップエントリ学生閲覧ボタン
  GtkButton  *particicationDecideButton; //インターンシップ詳細登録参加学生決定ボタン
  GtkButton  *gradeInputButton;       //評定入力ボタン
  GtkButton  *passwordChangeButton;   //パスワード変更ボタン

  ComISRegHandleData *isreghData;

  /*** 学生 ***/
  GtkButton  *internDisplayButton;    //参加インターンシップ情報閲覧
  GtkButton  *selfEvaluationButton;   //評定入力
  GtkButton  *adviceDisplayButton;    //アドバイス参照
  GtkButton  *stuPasswordChangeButton; //パスワード変更（学生）ボタン
  LoginHandleData *loginHData;      //ログイン画面の主要Widget保持用構造体
}MainHandleData;


extern int setup_connect( char *__target, u_short __port);
extern int recv_data(int s, char *recvBuf, int bufSize);
extern int record_division(char *block, char *records[]);
#endif
