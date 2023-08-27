CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
SRC_LIB = backend
TESTFILE = s21_test
GCOV_FLAG = -fprofile-arcs -ftest-coverage

ifeq ($(shell uname), Linux)
	LIBS_FOR_CHECK=-lcheck -lsubunit -lrt -lpthread -lm
else
	LIBS_FOR_CHECK=-lcheck
endif

RDIR = ./release
APP = $(RDIR)/SmartCalcV1

all: clean gcov_report install

install:
	mkdir $(RDIR)
	cd $(RDIR); qmake ../SmartCalcV1.pro
	cd $(RDIR); make
	cd $(RDIR); make clean
	$(RDIR)/SmartCalcV1
#	cp $(RDIR)s21_SmartCalc.app/Contents/MacOS/s21_SmartCalc $(RDIR)s21_SmartCalc


uninstall:
	rm -rf $(RDIR)


dist:
	tar -czf $(RDIR)/SmartCalcV1.tgz $(RDIR)/SmartCalcV1


dvi:
	open ./documentation/dvi.html

clean: uninstall
	rm -f *.a *.o *.so *.out *.info *.gcno *.gcda main $(TESTFILE)
	rm -rf report manual
	rm -rf *.tgz


test: s21_smart_calc.a
	$(CC) $(FLAGS) -c tests/*.c s21_test.c
	$(CC) $(CFLAGS) --coverage s21_test*.o s21_smart_calc.a $(LIBS_FOR_CHECK) -o s21_test


s21_smart_calc.a:
	$(CC) -c $(FLAGS) $(GCOV_FLAG) $(SRC_LIB)/*.c
	ar rcs s21_smart_calc.a *.o
	ranlib $@


gcov_report: test
	./s21_test
	lcov -o $(TESTFILE).info -c -d .
	genhtml -o report $(TESTFILE).info
	open ./report/index.html

leaks: test
ifeq ($(shell uname), Linux)
	CK_FORK=no valgrind --tool=memcheck --leak-check=no ./$(TESTFILE)
else
	CK_FORK=no leaks --atExit -- ./$(TESTFILE)
endif

style-check:
	clang-format -n ./backend/* *.cpp *.h

style-set:
	clang-format -i ./backend/* *.cpp *.h