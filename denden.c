/*	クオリティＣプログラミング　中級編
**
**	例題：
**		住所録管理表・第6版
**
**		file name：	denden.c
**
**		コンパイルする場合、ライブラリのリンクオプション　-lncursesw をつけること
**
**		composed by Naohiko Takeda
**					ver. 1.00.	1990.5.30.
**		composed by Yoshihide Chubachi
**					ver. 1.10.	2003.4.27.
**		composed by Shinsuke Kobayashi
**					ver. 2.10.	2019.10.09.
**
*/
#define GLOBAL_VALUE_DEFINE
#include "denden.h"

/*-----------------------*/
/*	グローバル変数の宣言 */
/*-----------------------*/
char	cmd_list[] = {
			APPEND,
			EDIT,
			DELETE,
			BEFORE,
			NEXT,
			UP_PAGE,
			DOWN_PAGE,
			LOAD,
			SAVE,
			QUIT
		};

/* main */
/*----------------------------------------------------*/

int	main()
{
	char command;

	/* 初期化する */
	init_disp();
	init_buff();
	show_one_page();

	/* コマンドの入力と実行 */
	while(( command = input_cmd() ) != QUIT ){
		exec_cmd( command );
		/* データの再表示 */
		show_one_page();
	}

	/* 後始末する */
	clear();
	endwin();
	return 0;
}

/* input_cmd */
/*----------------------------------------------------*/
/*
	書式：	char	input_cmd()

	機能：	住所録のコマンドを入力し，妥当なコマンドであれば，入力されたコマンド
			を返す．もしも，不適当なコマンドであれば，再入力を要求する．

	返値：	入力されたコマンド
*/

char	input_cmd()
{
	int		cmd;
	int		match = FALSE;
	int		i;
	char	buffer[BUFFER_LEN];

	/* 前処理 */
	move( CMD_MSG_LINE, 1 );
	printw( CMD_MSG );

	/* コマンドの入力 */
	for( ; ; ){
		move( CMD_LINE, 1 );	/* コマンドを1文字入力する */
		clrtoeol();
		printw( CMD_PROMPT );
		getstr( buffer );
		cmd = toupper( buffer[0] );
		for( i = 0 ; i < CMD_MAX ; i++ ){	/* 妥当なコマンドか？ */
			if( cmd == cmd_list[i] ){
				match = TRUE;
				break;
			}
		}
		if( !match ){
			move( CMD_ERR_LINE, 1 );
			printw( CMD_ERR_MSG );
		} else {
			break;
		}
	}

	/* 後始末 */
	del_lines( CMD_MSG_LINE, CMD_LINE );
	return( cmd );
}


/* exec_cmd */
/*----------------------------------------------------*/
/*
	書式：	void	exec_cmd( char cmd )

	機能：	変数cmdで，指定されたコマンドを実行する．

	返値：	なし
*/
void exec_cmd(
	char	cmd		/* コマンド */
)
{
	switch( cmd ){
	case	APPEND:
		data_append();		/* 追加 */
		break;
	case	EDIT:
		data_edit();		/* データの編集 */
		break;
	case	DELETE:
		data_delete();		/* データの削除 */
		break;
	case	UP_PAGE:
		paging( UP );		/* 次ページ */
		break;
	case	DOWN_PAGE:
		paging( DOWN );		/* 前ページ */
		break;
	case	NEXT:
		cur_move( UP );		/* 次のデータ */
		break;
	case	BEFORE:
		cur_move( DOWN );	/* 前のデータ */
		break;
	case	LOAD:
		data_load();		/* データのロード */
		break;
	case	SAVE:
		data_save();		/* データのセーブ */
		break;
	default:
		break;
	}
}


/* paging */
/*----------------------------------------------------*/
/*
	書式：	void	paging( int direction )

	機能：	注目行を前，あるいは次ページに移動する．移動できない時は，そのまま．

	返値：	なし
*/

void paging(
	int	direction	/* ページングの方向 */
)
{
	int next = 0;

	if(rec_qty == 0)	/* データなし */
		return;

	switch( direction ){
	case	UP:
		next = cursor + DISP_REC_MAX;
		if( next > rec_qty )
			next = rec_qty;
		break;
	case	DOWN:
		next = cursor - DISP_REC_MAX;
		if( next <= 0 )
			next = 1;
		break;
	default:
		break;
	}
	cursor = next;
}


/* cur_move */
/*----------------------------------------------------*/
/*
	書式：	void	cur_move( int direction )

	機能：	注目行を前，あるいは次データに移動する．移動できない時は，そのまま．

	返値：	なし
*/

void	cur_move(
	int	direction	/* 注目行の移動方向 */
)
{
	int		next = 0;

	if( rec_qty == 0 )	/* データなし */
		return;

	switch( direction ){
	case	UP:
		next = cursor + 1;
		if( next > rec_qty )
			next = rec_qty;
		break;
	case	DOWN:
		next = cursor - 1;
		if( next <= 0 )
			next = 1;
		break;
	default:
		break;
	}
	cursor = next;
}


/* init_buff */
/*----------------------------------------------------*/
/*
	書式：	void	init_buff( )

	機能：	住所録の文字列を初期化する

	返値：	なし
*/

void	init_buff()
{
	CARD	*tmp;
	int i;
	//  住所録データの初期化
	for (i = 0; i < RECORD_MAX; i++) {
		tmp = &note[i];
		tmp->k_name[0] = '\0';
		tmp->j_name[0] = '\0';
		tmp->zip[0] = '\0';
		tmp->address[0] = '\0';
		tmp->tel_no[0] = '\0';
	}
}
