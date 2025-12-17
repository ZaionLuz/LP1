"""
QUESTÃO 1 (5,0 pontos)

Implemente um programa em Python que solicite uma frase ao usuário e uma letra para busca.
Use o método count para mostrar quantas vezes a letra aparece na frase.
Em seguida, exiba uma mensagem dizendo se a letra é:
- "muito comum" (5 ou mais ocorrências),
- "pouco comum" (entre 1 e 4 ocorrências),
- ou "inexistente" (0 ocorrências).
"""

frase = input("Digite uma frase: ")
letra = input("Digite uma letra: ")

quantidade = frase.count(letra)

print("Quantidade de ocorrências:", quantidade)

if quantidade >= 5:
    print("A letra é muito comum")
elif quantidade >= 1:
    print("A letra é pouco comum")
else:
    print("A letra é inexistente")

"""
QUESTÃO 2 (5,0 pontos)

Escreva um programa que leia 10 números inteiros, armazene todos em uma lista e,
ao final, exiba:
a) A quantidade de números pares
b) A quantidade de números ímpares
c) A soma apenas dos números maiores que 50
"""

numeros = []
pares = 0
impares = 0
soma_maiores_50 = 0

for i in range(10):
    numero = int(input(f"Digite o {i+1}º número: "))
    numeros.append(numero)

    if numero % 2 == 0:
        pares += 1
    else:
        impares += 1

    if numero > 50:
        soma_maiores_50 += numero

print("Quantidade de números pares:", pares)
print("Quantidade de números ímpares:", impares)
print("Soma dos números maiores que 50:", soma_maiores_50)
