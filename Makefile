# プログラム名、ソースコードファイル名、リンクライブラリを指定
# この部分を修正すればほかは修正をしなくても基本的には使える
PROGRAM = denden
SRC = denden.c display.c
OBJ = $(SRC:%.c=%.o)
LNK = -lncurses

# 定義済みマクロの再定義
CC = gcc
CFLAGS = -Wall -O2

# サフィックスルール適用対象の拡張子の定義
.SUFFIXES: .c .o

# プライマリターゲット
.PHONY: all
all: $(PROGRAM)

# プログラムの生成ルール
$(PROGRAM): $(OBJ)
	$(CC) $(LNK) -o $(PROGRAM) $^

# サフィックスルール
.c.o:
	$(CC) $(CFLAGS) -c $<

# ファイル削除用ターゲット
.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJ)
