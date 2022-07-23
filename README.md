# Parade

Parade é um jogo de cartas, numeradas de 0 a 10 com 6 naipes (ou cores), totalizando 66 cartas. Parade simboliza um desfile onde 6 convidados estão na 
lista, sendo cada convidado representado por uma carta única do baralho. 

## Jogabilidade

Os naipes são representados por letras de A à F. O jogador da vez escolhe uma carta da mão e a coloca ao fim do desfile, que está na mesa. 
O número da nova carta dirá quantas cartas do desfile serão "protegidas". <br>
Após isso, todas as cartas não protegidas de mesmo naipe e/ou valor igual ou menor que o valor da carta que o jogador jogou serão removidas e irão 
para a coleção do jogador.. <br>
No fim da jogada, o jogador compra uma carta do baralho.<br><br>

Exemplo de jogada:<br>
[NOVA CARTA] -> [5 A] -> [6 B] -> [9 A] -> [3 F] -> [8 C] | Inicío do desfile | Baralho (56 cartas)<br><br>

O Jogador joga a a carta [2 B], logo a mesa atualiza:<br>
[NOVA CARTA] -> [2 B] -> [5 A] -> [6 B] -> [9 A] -> [3 F] -> [8 C] | Inicío do desfile | Baralho (55 cartas)<br><br>
O jogador não pega nenhuma carta, pois  a carta [2 B] protege as cartas [5 A] e [6 B]. Das cartas restantes, nenhuma possui mesmo naipe e/ou valor igual ou menor que 2.
O jogador compra uma carta, ficando 55 no baralho e o passa a vezpara opróximo jogador.<br>

O jogo segue a partir disso. Há 4 possibilidades para o fim do jogo:<br><br>
<ul>
  <li> O jogador perdeu: tem todas as cores na coleção; </li>
  <li> O jogador fez pontos: jogou até ficar com as 4 cartas e baixar 2 na mesa; </li>
  <li> O jogador venceu: jogou até ficar com 4 cartas e na coleção tinha zero pontos; </li>
  <li> O jogador venceu perfeitamente: jogou até ficar com 4 cartas e na coleção tinha zero pontos e na mão tinha dois zeros. </li>
</ul>

O jogo original foi pensado para várias pessoas, porém o do programa foi feito para apenas uma pessoa, que jogará contra o PC.<br>
Mais informações sobre o jogo original nesse [vídeo informativo](https://www.youtube.com/watch?v=M4rGJDqmOSU).

## Sobre o projeto

Projeto desenvolvido como segunda e última nota da cadeira de Algoritmo e Estrutura de Dados I da UFCA. Seu objetivo é a avaliar a manipução de 
ponteiros e o uso de structs e listas encadeadas (linked lists).
Os requisitos necessários para o projeto estão no arquivo projeto.txt. Recomendado o uso do Code::BLocks para compilar e rodar o programa.
