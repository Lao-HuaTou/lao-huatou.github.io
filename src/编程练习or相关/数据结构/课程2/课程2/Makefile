# 1. 定义变量
CC = gcc
CFLAGS = -Wall -g
TARGET = his_system

# 2. 自动获取所有 .c 文件，并生成对应的 .o 列表
SRCS = main.c ui.c crud.c file_io.c business_clinical.c
OBJS = $(SRCS:.c=.o)

# 3. 最终目标：链接所有的 .o 文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	@echo "编译完成！直接运行 ./$(TARGET) 即可。"

# 4. 模式规则：将每个 .c 编译成 .o
# $< 代表依赖文件 (.c)，$@ 代表目标文件 (.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 5. 伪目标：清理垃圾文件
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)