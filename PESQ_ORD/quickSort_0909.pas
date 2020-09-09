var vetor : array[1..10] of integer; { vetor de tamanho 10 vazio}

procedure quicksort(inicio, fim : integer); { Função de ordenação do vetor}
var i, j, pivo, aux : integer;
begin
  i := inicio;
  j := fim;
  pivo := vetor[(inicio + fim) div 2];

  while (i <= j) do
  begin
    while (vetor[i] < pivo) and (i < fim) do
      i := i+1;

    while (vetor[j] > pivo) and (j > inicio) do
      j := j-1;

    if (i <= j) then
    begin
      aux := vetor[i];
      vetor[i] := vetor[j];
      vetor[j] := aux;
      i := i+1;
      j := j-1;
    end;
  end;

  if (j > inicio) then
    quicksort(inicio, j);

  if (i < fim) then
    quicksort(i, fim);
end;

procedure cria_vetor; { Função preenche um vetor com numeros randomicos de 0 a 100}
var i : integer;
begin
  randomize;
  for i:=1 to 10 do
    vetor[i] := random(10)+1;
end;

procedure imprime_vetor; { Função que impreime valor do vetor}
var i : integer;
begin
  for i:=1 to 10 do
    write(vetor[i], ' ');
  writeln;
end;

begin  { execução do programa chamando as funções criadas }
  cria_vetor;

  writeln('Vetor desordenado:');
  imprime_vetor;
  writeln;

  quicksort(1, 10);

  writeln('Vetor ordenado:');
  imprime_vetor;
end.