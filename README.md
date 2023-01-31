# PingApp
Programa ping em c++

Passos para executar o programa:

BUILD

1. baixe o projeto

2. builde o projeto com o Cmake para ele gerar o makefile.

3. rode o make no projeto.

EXECUÇÂO

Feito os passos anteriores serão criados 2 arquivos na pasta raíz, estes são chamados
ClientServerAppC e ClientServerAppS.

1. abra um terminal e vá ao diretório dos 2 arquivos anteriormente citados.

2. Execute o ClientServerAppS, este é o Server, e ele ficará esperando uma conexão.

3. Execute em outra aba o ClientServerAppC com o ip local de argumento
	exemplo: "./ClientServerAppC IP_LOCAL"

4. Verifique o ping realizado.

As portas foram pré dispostas no próprio código então não há necessidade de digitá-la no argumento.
