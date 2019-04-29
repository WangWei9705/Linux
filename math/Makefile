.PHONY:clean main

main:main.o add.o sub.o mul.o div.o
	ar -rc $@ $^  

%.O:%.C
	gcc -c $^ -o $@

clean:
	rm -rf *.o    // 去掉所有.o文件
