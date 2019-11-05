step1:step1.cpp dictionary.cpp dictionary.h
	g++ -o step1 step1.cpp dictionary.cpp
step3:step3.cpp dictionary.cpp dictionary.h
	g++ -o step3 step3.cpp dictionary.cpp
step4:step4.cpp dictionary.cpp dictionary.h
	g++ -o step4 step4.cpp dictionary.cpp
printdict:printdict.cpp dictionary.cpp dictionary.h
	g++ -o printdict printdict.cpp dictionary.cpp
consult:consult.cpp dictionary.cpp dictionary.h
	g++ -o consult consult.cpp dictionary.cpp
step5:step5.cpp dictionary.cpp dictionary.h
	g++ -o step5 step5.cpp dictionary.cpp
step6:step6.cpp dictionary.cpp dictionary.h
	g++ -o step6 step6.cpp dictionary.cpp

all:
	make step1
	make step3
	make step4
	make step5
	make step6
	make printdict
	make consult
setIR:
	step1|sort|step3|step4
	step5|sort|step6
