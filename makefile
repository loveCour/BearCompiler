YACC=bison -dy
LEX=flex
a.exe:	lex.yy.c y.tab.c y.tab.h ast.h
	$(CXX) lex.yy.c y.tab.c
lex.yy.c:	bearLex.l
	$(LEX) bearLex.l
y.tab.c:	bearBison.y
	$(YACC) bearBison.y
y.tab.h:	bearBison.y
	$(YACC) bearBison.y
clean:
	$(RM) a.exe lex.yy.c y.tab.c y.tab.h
