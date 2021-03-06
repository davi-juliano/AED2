# -*- coding: utf-8 -*-
"""Trabalho Computacional 3.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1A06Xw6_SM3cbeF5lLil7keuBF82uQF9M
"""

# Commented out IPython magic to ensure Python compatibility.
# %pip install networkx

"""# Teste do Grafo de 4 vertices"""

import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import time
import networkx as nx
import random

G = nx.DiGraph()
G.add_edge('A', 'B', weight=4)
G.add_edge('B', 'D', weight=2)
G.add_edge('A', 'C', weight=3)
G.add_edge('C', 'D', weight=4)
#nx.shortest_path(G, 'A', 'D', weight='weight')

nx.draw(G, with_labels=True, font_weight='bold')
plt.savefig("grafo.png")

"""# Leitura do Arquivo .txt

Irei utilizar a função random para gerar um valor de peso de 0 a 10 entre cada um dos vértices, visto que o peso de cada vértice não é dado e nem pode ser calculado por meio dos vértices.

Agora a leitura dos arquivos:
"""

vertice1=[]
vertice2=[]

with open('facebook_combined.txt', 'r') as f:
  for line in f.readlines():
      vet = line.split(' ')
      vertice1.append(int(float(vet[0])))
      vertice2.append(int(float(vet[1])))

print(vertice1)
print(vertice2)

weight=[]

for i in range(len(vertice1)):
  weight.append(random.randint(0,10))

print(weight)

"""# Aplicando o grafo no NetworkX"""

import plotly.offline as py
import plotly.graph_objs as go
import functools
py.init_notebook_mode(connected=True)

#A estrutura de grafo pelo NetworkX é dado pelo link 
# Link: https://networkx.org/documentation/networkx-1.10/_modules/networkx/classes/digraph.html#DiGraph

Grafo = nx.DiGraph()

for i in range(len(vertice1)):
  Grafo.add_edge(vertice1[i], vertice2[i], weight=weight[i])

vertices=[i for i in range(4038)]

print(vertices)

options = {
    'node_color': 'black',
    'node_size': 10,
    'width': 1,
}
nx.draw(Grafo, **options)
plt.savefig("grafo.png")
plt.show()

"""Função de Closeness:"""

#Pela documentação do NetworkX módulo do Python, temos que a função de Closeness é dada por:

__author__ = "\n".join(['Aric Hagberg <aric.hagberg@gmail.com>',
                        'Pieter Swart (swart@lanl.gov)',
                        'Sasha Gutfraind (ag362@cornell.edu)'])

def closeness_centrality(G, u=None, distance=None, normalized=True):
    if distance is not None: 
   
        #Usar o Algoritmo de Dijkstra para atributos específicos com peso
        path_length = functools.partial(nx.single_source_dijkstra_path_length, 
                                        weight=distance) 
    else:
        #Usar o Algoritmo de Bellman-Ford para atributos sem peso
        path_length = nx.single_source_shortest_path_length 
  
    if u is None: 
        nodes = G.nodes() 
    else: 
        nodes = [u] 
    closeness_centrality = {} 
    for n in nodes: 
        sp = path_length(G,n) 
        totsp = sum(sp.values()) 
        if totsp > 0.0 and len(G) > 1: 
            closeness_centrality[n] = (len(sp)-1.0) / totsp 
   
            # normalizar o numero de nós-1 na parte conectada
            if normalized: 
                s = (len(sp)-1.0) / ( len(G) - 1 ) 
                closeness_centrality[n] *= s 
        else: 
            closeness_centrality[n] = 0.0
    if u is not None: 
        return closeness_centrality[u] 
    else: 
        return closeness_centrality

"""Aplicação do Closeness no grafo dado:"""

import operator

close = closeness_centrality(Grafo)

close_list = sorted(close.items(), key=operator.itemgetter(1))

print(close_list)

"""Funções complementares da função Betweenness:"""

def _single_source_shortest_path_basic(G, s):
    #Algoritmo de caminho mínimo de Bellman-Ford
    S = []
    P = {}
    for v in G:
        P[v] = []
    sigma = dict.fromkeys(G, 0.0)    #sigma[v]=0 para v no grafo G
    D = {}
    sigma[s] = 1.0
    D[s] = 0
    Q = [s]
    while Q:   #Usa busca em largura para encontrar os menores caminhos
        v = Q.pop(0)
        S.append(v)
        Dv = D[v]
        sigmav = sigma[v]
        for w in G[v]:
            if w not in D:
                Q.append(w)
                D[w] = Dv + 1
            if D[w] == Dv + 1:   #Esse é o menor caminho, contar caminhos
                sigma[w] += sigmav
                P[w].append(v)  # Precessores
    return S, P, sigma


def _single_source_dijkstra_path_basic(G, s, weight='weight'):
    #Algoritmo de caminho mínimo de Dijkstra
    # Modificado por Eppstein
    S = []
    P = {}
    for v in G:
        P[v] = []
    sigma = dict.fromkeys(G, 0.0)    #sigma[v]=0 para v no grafo G
    D = {}
    sigma[s] = 1.0
    push = heappush
    pop = heappop
    seen = {s: 0}
    c = count()
    Q = []   #Usar a Q como heap com tuplas (distance,node id) 
    push(Q, (0, next(c), s, s))
    while Q:
        (dist, _, pred, v) = pop(Q)
        if v in D:
            continue  #Já foi achado esse nó
        sigma[v] += sigma[pred]  # contar caminhos
        S.append(v)
        D[v] = dist
        for w, edgedata in G[v].items():
            vw_dist = dist + edgedata.get(weight, 1)
            if w not in D and (w not in seen or vw_dist < seen[w]):
                seen[w] = vw_dist
                push(Q, (vw_dist, next(c), v, w))
                sigma[w] = 0.0
                P[w] = [v]
            elif vw_dist == seen[w]:  # Lidar com caminhos iguais
                sigma[w] += sigma[v]
                P[w].append(v)
    return S, P, sigma


def _accumulate_basic(betweenness, S, P, sigma, s):
    delta = dict.fromkeys(S, 0)
    while S:
        w = S.pop()
        coeff = (1.0 + delta[w]) / sigma[w]
        for v in P[w]:
            delta[v] += sigma[v] * coeff
        if w != s:
            betweenness[w] += delta[w]
    return betweenness


def _accumulate_endpoints(betweenness, S, P, sigma, s):
    betweenness[s] += len(S) - 1
    delta = dict.fromkeys(S, 0)
    while S:
        w = S.pop()
        coeff = (1.0 + delta[w]) / sigma[w]
        for v in P[w]:
            delta[v] += sigma[v] * coeff
        if w != s:
            betweenness[w] += delta[w] + 1
    return betweenness

def _rescale(betweenness, n, normalized, directed=False, k=None):
    if normalized is True:
        if n <= 2:
            scale = None  # Não normalização de b=0 para todos os nós
        else:
            scale = 1.0 / ((n - 1) * (n - 2))
    else:  # Redimensionar em 2 para gráficos não direcionados
        if not directed:
            scale = 1.0 / 2.0
        else:
            scale = None
    if scale is not None:
        if k is not None:
            scale = scale * n / k
        for v in betweenness:
            betweenness[v] *= scale
    return betweenness

"""Função Principal Betweenness:"""

#Pela documentação do NetworkX módulo do Python, temos que a função de Betweenness é dada por:

__author__ = """Aric Hagberg (hagberg@lanl.gov)"""

def betweenness_centrality(G, k=None, normalized=True, weight=None, endpoints=False, seed=None):
    betweenness = dict.fromkeys(G, 0.0)  # b[v]=0 para v no grafo G 
    if k is None: 
        nodes = G 
    else: 
        random.seed(seed) 
        nodes = random.sample(G.nodes(), k) 
        
    for s in nodes: 
        # Caminho mais curto de fonte única
        if weight is None:  # Usar o algorítmo de Bellman-Ford
            S, P, sigma = _single_source_shortest_path_basic(G, s) 
        else:  # Usar o algoritmo de Dijkstra 
            S, P, sigma = _single_source_dijkstra_path_basic(G, s, weight) 
  
        # Acumulação
        if endpoints: 
            betweenness = _accumulate_endpoints(betweenness, S, P, sigma, s) 
        else: 
            betweenness = _accumulate_basic(betweenness, S, P, sigma, s) 
  
    # Reescalando 
    betweenness = _rescale(betweenness, len(G), normalized=normalized, 
                           directed=G.is_directed(), k=k) 
    return betweenness

"""Aplicação do Betweenness no grafo dado:"""

bet = betweenness_centrality(Grafo)

bet_list = sorted(bet.items(), key=operator.itemgetter(1))

print(bet_list)