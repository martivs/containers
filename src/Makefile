gcov_report:
	g++ -Wall -Werror -Wextra --coverage  s21_containers_test.cc -lgtest -lgmock -pthread -o gcovreport \
	`pkg-config --cflags --libs check`
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	
clean: 
	rm -rf *.o *.gcno *.gcda gcovreport gcovreport.info rm report
