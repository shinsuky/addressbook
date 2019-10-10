/*	クオリティＣプログラミング　中級編
**
**	例題：
**		住所録管理表・第5版
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

/*-----------------------*/
/*	住所録管理コマンド群 */
/*-----------------------*/

/* data_append */
/*----------------------------------------------------*/
/*
	書式：	void	data_append( void )

	機能：	住所録データの末尾に，新しいデータを追加する．

	返値：	なし
*/

void	data_append( void )
{
	move( APPEND_LINE, 1 );

	/* データが一杯かどうか調べる */
	if( rec_qty >= RECORD_MAX ){
		disp_err( ERR_APPEND );
		return;
	}

	/* データを入力する */
	printw( "名前		>>" );
	getnstr( note[rec_qty].j_name, NAME_LEN );
	printw( "フリガナ	>>" );
	getnstr( note[rec_qty].k_name, NAME_LEN );
	printw( "住所		>>" );
	getnstr( note[rec_qty].address, ADDR_LEN );
	printw( "郵便番号	>>" );
	getnstr( note[rec_qty].zip, ZIP_LEN );
	printw( "電話番号	>>" );
	getnstr( note[rec_qty].tel_no, TEL_LEN );

	cursor = ++rec_qty;

	/* 後始末 */
	del_lines( APPEND_LINE, APPEND_END_LINE );
}


/* data_edit */
/*----------------------------------------------------*/
/*
	書式：	void	data_edit( void )

	機能：	注目行のあるレコードに対して，編集作業を行う．
			まず，レコードのどの項目を修正するか入力する．
			入力された項目について，入力プロンプトを出力し，全部入力しなおす．
			もとのデータの一部分のみ，修正，変更，削除などは，サポートしない．
			編集項目の選択のところで，終了を選択すると，画面上の注目行のみ，再表
			示し，編集を終了する．

	返値：	なし
*/

void	data_edit( void )
{
	int	disp_pos;		/* 注目行の表示位置 */
	int	c;
	char	buffer[BUFFER_LEN];

	if( cursor == 0 )	/* データがない時の処理 */
		return;

	for( ; ; ){
		move( MSG_LINE, 1 );	/* 編集項目の選択 */
		printw( EDIT_MSG );
		move( MSG_LINE+2, 1 );
		printw( ">>" );
		getstr(buffer);
		if(( c = toupper( buffer[0] )) == QUIT )
			break;

		/* 各項目の編集 */
		switch( c ){
		case	NAME:
			printw("\n名前	>>");
			getnstr( note[cursor-1].j_name, NAME_LEN );
			break;
		case	KANA_NAME:
			printw("\nフリガナ	>>");
			getnstr( note[cursor-1].k_name, NAME_LEN );
			break;
		case	ADDR:
			printw("\n住所	>>");
			getnstr( note[cursor-1].address, ADDR_LEN );
			break;
		case	ZIP_NO:
			printw("\n郵便番号	>>");
			getnstr( note[cursor-1].zip, ZIP_LEN );
			break;
		case	TELPHONE:
			printw("\n電話番号	>>");
			getnstr( note[cursor-1].tel_no, TEL_LEN );
			break;
		default:
			break;
		}
		/* 注目行の再表示 */
		disp_pos = DATA_LINE + (( cursor-1 )% DISP_REC_MAX)*3;
		show_record( cursor, disp_pos );
		del_lines( MSG_LINE+2, MSG_LINE+4 );
	}
	del_lines( MSG_LINE, MSG_LINE+4 );
}


/* data_delete */
/*----------------------------------------------------*/
/*
	書式：	void	data_delete( void )

	機能：	注目行のデータを削除し，空いたところを詰め合わせる．

	返値：	なし
*/

void data_delete()
{
	CARD	*tmp;

	/* データ無しのチェック */
	if( cursor <= 0 )
		return;

	/* 注目行の削除 */
	pack_data( &cursor, &rec_qty );	/* まず，データの詰め合わせ */
	tmp = &note[rec_qty];
	tmp->k_name[0] = '\0';	/* 末尾データの削除 */
	tmp->j_name[0] = '\0';
	tmp->zip[0] = '\0';
	tmp->address[0] = '\0';
	tmp->tel_no[0] = '\0';
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


/* data_load */
/*----------------------------------------------------*/
/*
	書式：	void	data_load( void )

	機能：	住所録データを，指定されたファイルからロードする．

	返値：	なし
*/

void	data_load( void )
{
	char	buffer[FBUF_MAX];
	FILE	*fp;
	wchar_t   name[NAME_LEN], kana[NAME_LEN], zip_tmp[ZIP_LEN], addr_tmp[ADDR_LEN], tel_tmp[TEL_LEN];

	/* ファイル名の入力 */
	move( MSG_LINE, 1 );
	printw("ファイルをロードします");
	move( CMD_LINE, 1 );
	printw("ファイル名を入力してください >>");
	getstr( data_file );

	/* データファイルからの読み込み */
	if( (fp=fopen( data_file, "r" )) == NULL){
		disp_err( ERR_FILE );
		return;
	}

	rec_qty = 0;
	printw("ロード中");
	while( fgets( buffer, FBUF_MAX, fp ) != NULL ){
		addch('*');
		//sscanf( buffer, "%s %s %s %s %s", note[rec_qty].j_name, note[rec_qty].k_name, note[rec_qty].zip, note[rec_qty].address, note[rec_qty].tel_no );
		//
		//  元は上記のコードだけだったが、UTF-8 を扱う場合に、char で読み込むと、
		//  文字によってスペースと誤って認識されてしまうケースで文字化けが起こっていた。
		//  その問題に対処するため、ワイド文字列で読み込み、マルチバイト文字に変換して記録することとした。
		sscanf( buffer, "%S %S %S %S %S", name, kana, zip_tmp, addr_tmp, tel_tmp );
		wcstombs(note[rec_qty].j_name, name, sizeof(name));
		wcstombs(note[rec_qty].k_name, kana, sizeof(kana));
		wcstombs(note[rec_qty].zip, zip_tmp, sizeof(zip_tmp));
		wcstombs(note[rec_qty].address, addr_tmp, sizeof(addr_tmp));
		wcstombs(note[rec_qty].tel_no, tel_tmp, sizeof(tel_tmp));

		rec_qty++;
	}

	/* 後始末 */
	fclose( fp );
	cursor = 1;
	del_lines( MSG_LINE, CMD_LINE+1 );
}


/* data_save */
/*----------------------------------------------------*/
/*
	書式：	void	data_save( void )

	機能：	住所録データを，指定されたファイルにセーブする．

	返値：	なし
*/

void	data_save( void )
{
	int		i, end;
	FILE	*fp;

	/* ファイル名の入力 */
	move( MSG_LINE, 1 );
	printw("ファイルをセーブします");
	move( CMD_LINE, 1 );
	printw("ファイル名を入力してください >>" );
	getstr( data_file );

	/* データファイルへの書き出し */
	if( ( fp=fopen( data_file, "w" ) ) == NULL){
		disp_err( ERR_FILE );
		return;
	}
	end = rec_qty-1;
	printw("セーブ中");
	for( i=0 ; i<=end ; i++ ){
		fprintf( fp, "%s %s %s %s %s\n", note[i].j_name, note[i].k_name, note[i].zip, note[i].address, note[i].tel_no );
	}

	/* 後始末 */
	fclose( fp );
	del_lines( MSG_LINE, CMD_LINE+1 );
}


/* pack_data */
/*----------------------------------------------------*/
/*
	書式：	void	pack_data( int *rec_no, int *tail )

	機能：	指定されたレコード番号より後ろのデータを，前に詰め合わせる．指定した
			レコード番号のデータは，失われる．詰め合わせる最後のレコード番号も
			引数で指定する．

	返値：	なし
*/

void	pack_data(
	int		*rec_no,	/* 詰め合わせる最初のレコード番号 */
	int		*tail		/* 詰め合わせる最後のレコード番号 */
)
{
	int		i;

	if( *rec_no == *tail ){	/* 一番最後の要素を消す時 */
		*rec_no = *rec_no - 1;
		*tail = *tail - 1;
		return;
	}
	for( i = *rec_no - 1; i < *tail; i++ ){
		strcpy( note[i].j_name, note[i+1].j_name );
		strcpy( note[i].k_name, note[i+1].k_name );
		strcpy( note[i].tel_no, note[i+1].tel_no );
		strcpy( note[i].zip, note[i+1].zip );
		strcpy( note[i].address, note[i+1].address );
	}
	*tail = *tail - 1;
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
