void varTxt(const char* texto, char** nome);
void varInt(const char* texto, int* num);
Aluno* dadosAluno(Lista** curso);
Disciplina* dadosDisciplina(char* nomeD, Lista** curso);
Professor* dadosProfessor(void);
Turma* dadosTurma(Lista** discip, Lista** curso, int cod);
AulasM* dadosAulaM(void);
Curso* dadosCurso(char* nome);
Avaliacao* dadosAvaliacao(char* m, char* nome);
