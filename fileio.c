/*
**
**	例題：
**		住所録管理表・第6版
**
**		file name：	fileio.c
**
**		ファイル操作用関数
**		composed by Shinsuke Kobayashi
**					ver. 2.10.	2019.10.09.
**
*/
#include "denden.h"

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
