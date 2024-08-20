# Grammar for compiler
<ALPHANUM> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|
			A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|"|'|$

<DIGIT> ::= 0|1|2|3|4|5|6|7|8|9

<NUMBER> ::= <DIGIT>
           | <DIGIT> <NUMBER> 

<WORD> ::= <ALPHA> <WORD>
		 | <ALPHA> <WORD> <NUMBER> <WORD>
		 | EMPTY


<WORD-LIST> ::= <WORD>
             |  <WORD> <WORD-LIST>

<REDIRECTION> ::=  '>' <WORD>
                |  '<' <WORD>
                |  <NUMBER> '>' <WORD>
                |  <NUMBER> '<' <WORD>
                |  '>>' <WORD>
                |  <NUMBER> '>>' <WORD>
                |  '<<' <WORD>
                |  <NUMBER> '<<' <WORD>

<REDIRECTION-LIST> ::= <REDIRECTION>
                    |  <REDIRECTION> <REDIRECTION-LIST>

<SIMPLE-COMMAND-ELEMENT> ::= <WORD>  |  <REDIRECTION-LIST>

<SIMPLE-COMMAND> ::=  <SIMPLE-COMMAND-ELEMENT>
                   |  <SIMPLE-COMMAND-ELEMENT> <SIMPLE-COMMAND>


<PIPELINE> ::= <SIMPLE-COMMAND> '|' <PIPELINE>  |  <SIMPLE-COMMAND>

START ::= <PIPELINE>