# Compilador da linguaxe Go para a asignatura de Compiladores e Interpretes.

## Compilación
 1. Para a compilación do código debemos situarnos no directorio **cmake-build-debug**
 2. Unha vez dentro usando unha terminal de linux executaremos o comando:

    <pre><code>make</code></pre>
3. Para a execución necesitaremos a ruta do arquivo a analizar. Polo tanto executaremos o seguinte comando na mesma
terminal e directorio:

    <pre><code>./P1Compiladores [ruta do arquivo analizado]</code></pre>

## Estrutura do proxecto
O proxecto foi elaborado usando CLion, polo que si se precisa facer debug o codigo recomendo usar ese IDE para realizalo.

As partes que compoñen este proxecto son as seguintes:

### Main
A esta parte pertence o ficheiro **main.c**.

Tratase do main do proxecto, no cal se inician todas as partes do analise e o rematar liberanse.
### Sistema de entrada
A esta parte pertencen os ficheiros **sistemaEntrada.h** e **sistemaEntrada.c**.

Nestes ficheiros desarrollase un sistema de entrada baseado no dobre centinela que sirve para pasar o analizador lexico
o caracteres que forman o ficheiro.

### Sistema de Erros
A esta parte pertencen os ficheiros **sistemaErros.h** e **sistemaErros.c**.

Este sistema de erros implementa as funcions necesarias para notificar os erros que se atopen no ficheiro pasado por
argumento ou o realizar o analise lexico das compoñentes de dito ficheiro.

### Táboa de Símbolos
A esta parte pertencen os ficheiros **taboaSimbolos.h** e **taboaSimbolos.c**.

Estos ficheiros implementan unha táboa de simbolos baseada nunha linked list, para almacenar os identificadores e
palabras reservadas do compilador.

### Análise Léxico
A esta parte pertencen os ficheiros **analizadorLexico.h** e **analizadorLexico.c**.

É a parte principal do proxecto e a máis elaborada. Nela están implementados os automatas que detectan os compoñentes
léxicos do programa pasado como argumento e envíallos o analizador léxico.
### Análise Sintáctico
A esta parte pertencen os ficheiros **analizadorSintactico.h** e **analizadorSintactico.c**.

Esta composto solo por unha función que pide compoñentes lexicos o analizador léxico e logo imprimeos. Esta feita coa
idea de emular da forma máis real a un compilador, pero o código contido nesta parte do proxecto podría estar no main
perfectamente sen que a estrutura e funcionamento se viran afectadas en gran medida.

### Ficheiros de Macros
A esta parte pertencen os ficheiros **palabrasReservadas.h** e **valoresAuxiliares.h**.

Estos ficheiros conteñen macros de utilidade para o sistema, como as palabras reservadas, as cales se introducen na taboa
de simbolos o comezo da execución e os valores auxiliares, os cales sirven para identificar simbolos ou tipos numericos.

## Saida de exemplo do programa co ficheiro concurrentSum.go
<pre><code>
--------INICIO TÁBOA DE SÍMBOLOS--------
################################
0: Key->var         Value->424
################################
1: Key->return         Value->423
################################
2: Key->for         Value->422
################################
3: Key->continue         Value->421
################################
4: Key->type         Value->420
################################
5: Key->range         Value->419
################################
6: Key->if         Value->418
################################
7: Key->fallthrough         Value->417
################################
8: Key->const         Value->416
################################
9: Key->switch         Value->415
################################
10: Key->goto         Value->414
################################
11: Key->else         Value->413
################################
12: Key->chan         Value->412
################################
13: Key->struct         Value->411
################################
14: Key->map         Value->410
################################
15: Key->go         Value->409
################################
16: Key->defer         Value->408
################################
17: Key->case         Value->407
################################
18: Key->select         Value->406
################################
19: Key->interface         Value->405
################################
20: Key->func         Value->404
################################
21: Key->default         Value->403
################################
22: Key->break         Value->402
################################
23: Key->import         Value->401
################################
24: Key->package         Value->400
--------FIN TÁBOA DE SÍMBOLOS--------
1 : < package , 400 >

1 : < main , 500 >

3 : < import , 401 >

3 : < Cadena de caracteres , 526 >

5 : < func , 404 >

5 : < sum , 500 >

5 : < ( , 503 >

5 : < s , 500 >

5 : < [ , 506 >

5 : < ] , 507 >

5 : < float32 , 500 >

5 : < , , 501 >

5 : < c , 500 >

5 : < chan , 412 >

5 : < float32 , 500 >

5 : < ) , 502 >

5 : < { , 505 >

6 : < var , 424 >

6 : < sum , 500 >

6 : < float32 , 500 >

6 : < = , 510 >

6 : < 0 , 521 >

7 : < for , 422 >

7 : < _ , 500 >

7 : < , , 501 >

7 : < v , 500 >

7 : < := , 515 >

7 : < range , 419 >

7 : < s , 500 >

7 : < { , 505 >

8 : < sum , 500 >

8 : < += , 514 >

8 : < v , 500 >

9 : < } , 504 >

10 : < c , 500 >

10 : < <- , 516 >

10 : < sum , 500 >

10 : < Linea de comentario , 519 >

11 : < } , 504 >

13 : < func , 404 >

13 : < main , 500 >

13 : < ( , 503 >

13 : < ) , 502 >

13 : < { , 505 >

17 : < Bloque comentario , 520 >

18 : < s , 500 >

18 : < := , 515 >

18 : < [ , 506 >

18 : < ] , 507 >

18 : < float32 , 500 >

18 : < { , 505 >

18 : < 2 , 521 >

18 : < , , 501 >

18 : < real , 500 >

18 : < ( , 503 >

18 : < 1.e0 , 522 >

18 : < + , 511 >

18 : < 0i , 523 >

18 : < ) , 502 >

18 : < , , 501 >

18 : < real , 500 >

18 : < ( , 503 >

18 : < 1.e+0i , 523 >

18 : < ) , 502 >

18 : < , , 501 >

18 : < 0xBadFace42 , 524 >

18 : < * , 527 >

18 : < 1e-11 , 521 >

18 : < , , 501 >

18 : < - , 512 >

18 : < 9 , 521 >

18 : < , , 501 >

18 : < 4.e+0 , 522 >

18 : < , , 501 >

18 : < .1273E2 , 522 >

18 : < } , 504 >

20 : < c , 500 >

20 : < := , 515 >

20 : < make , 500 >

20 : < ( , 503 >

20 : < chan , 412 >

20 : < float32 , 500 >

20 : < ) , 502 >

21 : < go , 409 >

21 : < sum , 500 >

21 : < ( , 503 >

21 : < s , 500 >

21 : < [ , 506 >

21 : < : , 509 >

21 : < len , 500 >

21 : < ( , 503 >

21 : < s , 500 >

21 : < ) , 502 >

21 : < / , 517 >

21 : < 2 , 521 >

21 : < ] , 507 >

21 : < , , 501 >

21 : < c , 500 >

21 : < ) , 502 >

22 : < go , 409 >

22 : < sum , 500 >

22 : < ( , 503 >

22 : < s , 500 >

22 : < [ , 506 >

22 : < len , 500 >

22 : < ( , 503 >

22 : < s , 500 >

22 : < ) , 502 >

22 : < / , 517 >

22 : < 2 , 521 >

22 : < : , 509 >

22 : < ] , 507 >

22 : < , , 501 >

22 : < c , 500 >

22 : < ) , 502 >

23 : < i , 500 >

23 : < , , 501 >

23 : < j , 500 >

23 : < := , 515 >

23 : < <- , 516 >

23 : < c , 500 >

23 : < , , 501 >

23 : < <- , 516 >

23 : < c , 500 >

23 : < Linea de comentario , 519 >

25 : < fmt , 500 >

25 : < . , 518 >

25 : < Println , 500 >

25 : < ( , 503 >

25 : < Cadena de caracteres , 526 >

25 : < ) , 502 >

25 : < ; , 508 >

26 : < fmt , 500 >

26 : < . , 518 >

26 : < Println , 500 >

26 : < ( , 503 >

26 : < i , 500 >

26 : < , , 501 >

26 : < j , 500 >

26 : < , , 501 >

26 : < i , 500 >

26 : < + , 511 >

26 : < j , 500 >

26 : < ) , 502 >

27 : < } , 504 >

--------INICIO TÁBOA DE SÍMBOLOS--------
################################
0: Key->Println         Value->500
################################
1: Key->fmt         Value->500
################################
2: Key->j         Value->500
################################
3: Key->i         Value->500
################################
4: Key->len         Value->500
################################
5: Key->make         Value->500
################################
6: Key->real         Value->500
################################
7: Key->v         Value->500
################################
8: Key->_         Value->500
################################
9: Key->c         Value->500
################################
10: Key->float32         Value->500
################################
11: Key->s         Value->500
################################
12: Key->sum         Value->500
################################
13: Key->main         Value->500
################################
14: Key->var         Value->424
################################
15: Key->return         Value->423
################################
16: Key->for         Value->422
################################
17: Key->continue         Value->421
################################
18: Key->type         Value->420
################################
19: Key->range         Value->419
################################
20: Key->if         Value->418
################################
21: Key->fallthrough         Value->417
################################
22: Key->const         Value->416
################################
23: Key->switch         Value->415
################################
24: Key->goto         Value->414
################################
25: Key->else         Value->413
################################
26: Key->chan         Value->412
################################
27: Key->struct         Value->411
################################
28: Key->map         Value->410
################################
29: Key->go         Value->409
################################
30: Key->defer         Value->408
################################
31: Key->case         Value->407
################################
32: Key->select         Value->406
################################
33: Key->interface         Value->405
################################
34: Key->func         Value->404
################################
35: Key->default         Value->403
################################
36: Key->break         Value->402
################################
37: Key->import         Value->401
################################
38: Key->package         Value->400
--------FIN TÁBOA DE SÍMBOLOS--------
</code></pre>
