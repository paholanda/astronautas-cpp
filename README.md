# Astronautas

Sistema de uma agência espacial em C++: astronautas, voos e o que acontece com
cada missão. Atividade da Unidade 1 de Linguagem de Programação I.

Leia `ENUNCIADO.md` até o fim antes de programar.

## O que já existe

```text
.
├── AGENTS.md          regras que a IA lê antes de cada pedido (Parte 2)
├── ENUNCIADO.md       a atividade inteira: Parte 1, Parte 2, entrega
├── README.md          este arquivo
├── docs/
│   └── diario.md      o que você registra ao longo da atividade
├── src/
│   └── main.cpp       laço de comandos pronto; as classes são suas
└── testes/
    ├── testar.sh      compila e roda os testes de uma pasta
    ├── parte1/        seis testes da Parte 1
    ├── missao1/       testes da Missão 1
    ├── missao2/       testes da Missão 2
    └── missao3/       testes da Missão 3
```

## Compilar, executar e testar

```bash
g++ -std=c++11 -Wall -Wno-sign-compare src/main.cpp -o agencia
./agencia < testes/parte1/01_cadastros.in
bash testes/testar.sh parte1
```

Se você separar o código em `include/` e `src/`, o comando passa a ser:

```bash
g++ -std=c++11 -Wall -Wno-sign-compare src/*.cpp -Iinclude -o agencia
```

O script de teste aceita os dois formatos. Se o comando de compilação mudar,
atualize esta seção. Na correção eu vou usar o que estiver escrito aqui.
