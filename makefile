#
#	File:		makefile
#	Project:	AtomView
#	Author:		Douglas C. McIlrath
#	Date:		December 2013
#	Contents:
#		make instructions
#

LEXER=		Lexer.lex

SOURCE=		Main.cpp \
		UI.cpp \
		Element.cpp \
		Bond.cpp \
		Group.cpp \
		Functional.cpp \
		Generate.cpp \
		Color.cpp \
		Keys.cpp \
		Text.cpp \
		Trig.cpp \
		Triple.cpp \
		Anchor.cpp \
		DrawingObject.cpp \
		DrawingTools.cpp \
		Tables.cpp \

OBJECTS=	$(SOURCE:.cpp=.o) lex.yy.o

CFLAGS=		-g
CC=		g++

GLLIBS=		-lX11 -lGL -lGLU -lglut
LEXLIBS=	-lfl
LIBS=		$(GLLIBS) $(LEXLIBS)

all:
	make atom-view

atom-view: $(OBJECTS) $(LEXER)
	$(CC) -o atom-view $(OBJECTS) $(LIBS)

lex.yy.o: $(LEXER)
	flex $(LEXER)
	$(CC) -c $(CFLAGS) lex.yy.c

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

clean:
	rm *.o
	rm atom-view
