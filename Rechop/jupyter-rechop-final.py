#!/usr/bin/env python
# coding: utf-8

# In[2]:


from typing import Tuple, TextIO
import numpy as np
import random as ran
from operator import itemgetter, attrgetter, methodcaller
import itertools
import copy as cp
import matplotlib.pyplot as plt


# Inputs :

# On créer les parsers. Le premier parser traduit le fichier nodes avec la position des points.  

# In[3]:


def parser_nodes(file):
    lines = file.readlines()
    lines.pop(0)
    lines = [line.strip().split(";") for line in lines]
    for line in lines:
        line[0] = float(line[0])
        line[1] = float(line[1])
        line[2] = line[2][0]

    return lines


# Le second parser pour avoir les distances. nous donne une matrice.

# In[4]:


def parser_distances(file):
    lin = distances_file.readlines()
    DataIn = np.loadtxt(lin)
    return DataIn


# nodes_file = open("/home/azam/Documents/instances/grenoble/nodes.csv")
# 
# instances_file = open("/home/azam/Documents/instances/grenoble/distances.csv")
# #output = open("grenoble/output.csv","w+")
# #parser_nodes(nodes_file)
# #parser_distances(distances_file)
# lines = instances_file.readlines()
# lines = [float(float_) for float_ in lines ]
# lines = np.array(lines)
# lines = lines.reshape(13,13)
# lines

# On va faire une classe Instance qui contient toutes les informations et les transformations nécessaires pour utiliser les instances

# In[5]:


class Instances:
    
    def __init__(self,nodes_file,distances_file):
        self.nodes,self.distances = self.parser(nodes_file,distances_file)
        self.terminal = self.list_terminal()
        self.distribution = self.list_distribution()
        self.rangement=self.cluster()
        
    def parser(self,nodes_file,distances_file):
        nodes = nodes_file.readlines()
        nodes.pop(0)
        nodes = [line.strip().split(";") for line in nodes]
        for line in nodes:
            line[0] = float(line[0])
            line[1] = float(line[1])
            line[2] = line[2][0]
        nb_lines = len(nodes)
        distances = distances_file.readlines()
        distances = [float(float_) for float_ in distances ]
        distances = np.array(distances)
        distances = distances.reshape(nb_lines,nb_lines)
        return nodes, distances
        
        
    def nodes_sorting(self):
        terminal = []
        distribution = []
        i = 0

        for i in range(len(self.nodes)):
            if self.nodes[i][2] == 't':
                terminal.append([i, float(self.nodes[i][0]), float(self.nodes[i][1])])
            if self.nodes[i][2] == 'd':
                distribution.append([i, float(self.nodes[i][0]), float(self.nodes[i][1])])
        return terminal, distribution

    def list_terminal(self):
        return self.nodes_sorting()[0]

    def list_distribution(self):
        return self.nodes_sorting()[1]
    
    def xy(self,i):
        return(self.nodes[i][0],self.nodes[i][1])
    def l(self, i, j):
        return self.distances[i,j]
    def l2(self,i,j):
        return self.distances[i,j]+self.distances[j,i]
    def cluster(self):#rangement[i] est le cluster de la distribution i
        rangement = [[] for i in range(len(self.distribution))]
        maximum = 30+ 5*30
        for point in self.terminal:
            d = 1000000
            i0=0
            for i in range(len(self.distribution)):
                if self.l2(self.distribution[i][0],point[0])<d:
                    i0=i
                    d = self.l2(self.distribution[i][0],point[0])
            rangement[i0].append(point)
        return rangement
    def antenne_distribution(self,n):
        return self.rangement[n],self.distribution[n]
        


# In[6]:


nodes_file = open("/home/azam/Documents/instances/grenoble/nodes.csv")
distances_file = open("/home/azam/Documents/instances/grenoble/distances.csv")
I = Instances(nodes_file,distances_file)
I.distribution
I.antenne_distribution(1)

I.rangement


# On commence par se représenter les points avec numpy. Ensuite, la fonction cluster rassemble les points par distributions. Ainsi chaque distribution est un problème indépendant. 

# In[7]:


def trace(I):
    for i in range(len(I.terminal)):
        plt.plot(I.terminal[i][1],I.terminal[i][2],color = 'blue',marker ='o')
    for i in range(len(I.distribution)):
        plt.plot(I.distribution[i][1],I.distribution[i][2],color = 'red',marker = 'o' )
    plt.axis = "equal"
    
#test
def trace_cluster(I,n):
    for i in range(len(I.rangement[n])):
        plt.plot(I.rangement[n][i][1],I.rangement[n][i][2],color = 'green',marker ='o')
        plt.plot(I.distribution[n][1],I.distribution[n][2],color = 'yellow',marker = 'o' )
    plt.axis = "equal"
    plt.show()


# In[8]:


nodes_file = open("/home/azam/Documents/instances/grenoble/nodes.csv")
distances_file = open("/home/azam/Documents/instances/grenoble/distances.csv")
I = Instances(nodes_file,distances_file)
trace(I)
trace_cluster(I,0)
#I.rangement[6]


# Maintenant que le clustering est fait, on va s'occuper de trouver la solution. Les points de distribution sont tous indépendants. On part donc en entrée d'une distribution et de points associés. On va faire une métaheuristique à partir de là. On commence par une métaheuristique vraiment bourrine. L'objectif de la métaheuristique est de faire varier les points mais aussi la longueur de la boucle principale. 

# class solution_pour_une_distribution:#bouclesize = ran.randint(int(len(self.antennes)/6)+1,min(30,len(self.antennes)))
#     def __init__(self,I,n):#antennes = I.rangement[n],distribution = I.distribution[n]
#         self.I = I
#         self.n=n
#         self.distribution,self.antennes = self.antennes_distribution()
#         self.boucle,self.branche = self.first_solution()#branche[j] donne la branche raccrochée au point 
#         #self.cout = self.cout_non_incremental()
#     #boucle est la une liste de points
#     #branche est une liste de liste de branches.
#         
#     def antennes_distribution(self):
#         return self.I.distribution[self.n],self.I.rangement[self.n]
#     def first_solution(self):
#         boucle=[]
#         liste_antennes = cp.deepcopy(self.antennes)
#         boucle_size = ran.randint(int(len(self.antennes)/6)+1,min(30,len(self.antennes)))
#         for i in range(boucle_size):#on rempli la boucle
#             j = ran.randint(0,len(liste_antennes)-1)
#             boucle.append(liste_antennes.pop(j))
#         
#         branche = [[] for i in range(len(boucle))]
#         
#         for i in range(len(liste_antennes)):
#                 a = True
#                 while(a):
#                     j = ran.randint(0,len(boucle)-1)
#                     if (len(branche[j])>4):
#                         a = True
#                     else:
#                         a = False
#                         branche[j].append(liste_antennes[i])
#                 
#                 
#                 #debug +=1
#                 #if debug == 100 :
#                 #   print(boucle)
#         return boucle,branche
#     
#     def trace_solution(self):
#         #tracer de la boucle
#         Xdi = [self.distribution[1]]
#         Ydi = [self.distribution[2]]
#         Xboucle = [pt[1] for pt in self.boucle]
#         Yboucle = [pt[2] for pt in self.boucle]
#         
#         plt.plot(Xdi+Xboucle+Xdi,Ydi+Yboucle+Ydi,color = 'red')
#         for i in range(len(self.antennes)):
#             plt.plot(self.antennes[i][1],self.antennes[i][2],color = 'green',marker ='o')
#         plt.plot(self.distribution[1],self.distribution[2],color = 'yellow',marker = 'o' )
#         # on trace les branches
#         
#         for j in range (len(self.branche)):
#             Xi = [self.boucle[j][1]]
#             Yi = [self.boucle[j][2]]
#             X = [pt[1] for pt in self.branche[j]]
#             Y = [pt[2] for pt in self.branche[j]]
#             plt.plot(Xi+X,Yi+Y, color = 'blue')
#         
#         
#         
#         #plt.axis = "equal"
#         #plt.show()
#     def cout_non_incremental(self):
#         cout = self.I.l(self.distribution[0],self.boucle[0][0])
#         for i in range(len(self.boucle)-1):
#             cout+= self.I.l(self.boucle[i][0],self.boucle[i+1][0])
#         cout += self.I.l(self.boucle[len(self.boucle)-1][0],self.distribution[0])
#         for i in range(len(self.branche)):
#             if (len(self.branche[i])>0):
#                 cout += self.I.l(self.boucle[i][0],self.branche[i][0][0])
#                 for j in range(len(self.branche[i])-1):
#                     cout+=self.I.l(self.branche[i][j][0],self.branche[i][j+1][0])
#                              
#                                   
#         return cout
#             
#     def creer_un_fichier_from_distribution(self):
#         return 0

# nodes_file = open("/home/azam/Documents/instances/grenoble/nodes.csv")
# distances_file = open("/home/azam/Documents/instances/grenoble/distances.csv")
# I = Instances(nodes_file,distances_file)
# sol1 = solution_pour_une_distribution(I,0) 
# #sol1.boucle,sol1.branche
# #print(sol1.cout)
# #print(sol1.boucle)
# #print(sol1.cout)
# #print(sol1.branche)
# sol1.trace_solution()
# print(sol1.cout_non_incremental())
# plt.show()
# sol1.boucle[0],sol1.boucle[1]=sol1.boucle[1],sol1.boucle[0]#on test les échanges
# sol1.branche[0],sol1.branche[1]=sol1.branche[1],sol1.branche[0]
# print(sol1.cout_non_incremental())
# #sol1.branche[0],sol1.branche[1]=sol1.branche[1],sol1.branche[0]
# sol1.trace_solution()
# plt.show()
# #sol1.branche[0],sol1.branche[1]=sol1.branche[1],sol1.branche[0]
# #sol1.trace_solution()
# #plt.show()

# ### Dans la suite on s'occupe de créer la solution complète

# class solution_complete:
#     def __init__(self,nodes_file,distances_file):
#         self.I = Instances(nodes_file,distances_file)
#         self.cout = 0
#     def final(self):
#         for n in range(len(self.I.distribution)):
#             sol = solution_pour_une_distribution(self.I,n)
#             self.cout += sol.cout_non_incremental()
#             sol.trace_solution()
#         plt.axis ="equal"
#         plt.show()
#         print(self.cout)
#         
#     

# nodes_file = open("/home/azam/Documents/instances/paris/nodes.csv")
# distances_file = open("/home/azam/Documents/instances/paris/distances.csv")
# s = solution_complete(nodes_file,distances_file)
# #print(a1.I.distribution)
# s.final()

# ### On implémente un premier programme aléatoire très gourmand

# class heuristique_distribution:
#     def __init__(self,I,n):
#         self.taille = 500
#         self.I = I
#         self.n = n
#         self.distribution,self.antennes = self.antennes_distribution()
#         self.x = self.simple_heuristique()
#     def antennes_distribution(self):
#         return self.I.distribution[self.n],self.I.rangement[self.n]
#     def simple_heuristique(self):
#             #heuristique à partir d'ici
#         x = solution_pour_une_distribution(self.I,self.n)
#         
#         for i1 in range(self.taille):
#             y = solution_pour_une_distribution(self.I,self.n)
#             if y.cout_non_incremental() < x.cout_non_incremental():
#                 x = y
#         return x
#     

# nodes_file = open("/home/azam/Documents/instances/paris/nodes.csv")
# distances_file = open("/home/azam/Documents/instances/paris/distances.csv")
# I = Instances(nodes_file,distances_file)
# sol1 = heuristique_distribution(I,0) 
# #sol1.boucle,sol1.branche
# #print(sol1.x.cout)
# #print(sol1.x.boucle)
# #print(sol1.x.cout)
# #print(sol1.x.branche)
# sol1.x.trace_solution()
# print(sol1.x.cout_non_incremental())
# 

# class solution_complete_heuristique:
#     def __init__(self,nodes_file,distances_file):
#         self.I = Instances(nodes_file,distances_file)
#         self.cout = 0
#     def final(self):
#         for n in range(len(self.I.distribution)):
#             sol = heuristique_distribution(self.I,n)
#             self.cout += sol.x.cout_non_incremental()
#             sol.x.trace_solution()
#         plt.axis ="equal"
#         plt.show()
#         print(self.cout)

# nodes_file = open("/home/azam/Documents/instances/paris/nodes.csv")
# distances_file = open("/home/azam/Documents/instances/paris/distances.csv")
# a1 = solution_complete_heuristique(nodes_file,distances_file)
# #print(a1.I.distribution)
# a1.final()

# ## Partie test !

# In[9]:


class solution_pour_une_distribution2:
    def __init__(self,I,n,bouclesize):#antennes = I.rangement[n],distribution = I.distribution[n]
        self.I = I
        self.n=n
        self.bouclesize = bouclesize
        self.distribution,self.antennes = self.antennes_distribution()
        self.boucle,self.branche = self.first_solution()#branche[j] donne la branche raccrochée au point 
        #self.cout = self.cout_non_incremental()
         
    #boucle est la une liste de points
    #branche est une liste de liste de branches.
    def antennes_distribution(self):
        return self.I.distribution[self.n],self.I.rangement[self.n]
    def first_solution(self):
        boucle=[]
        liste_antennes = cp.deepcopy(self.antennes)
        #boucle_size = ran.randint(int(len(self.antennes)/6)+1,min(30,len(self.antennes)))
        for i in range(self.bouclesize):#on rempli la boucle
            j = ran.randint(0,len(liste_antennes)-1)
            boucle.append(liste_antennes.pop(j))
        
        branche = [[] for i in range(len(boucle))]
        
        for i in range(len(liste_antennes)):
                a = True
                while(a):
                    j = ran.randint(0,len(boucle)-1)
                    if (len(branche[j])>4):
                        a = True
                    else:
                        a = False
                        branche[j].append(liste_antennes[i])
                
                
                #debug +=1
                #if debug == 100 :
                #   print(boucle)
        return boucle,branche
    
    def trace_solution(self):
        #tracer de la boucle
        Xdi = [self.distribution[1]]
        Ydi = [self.distribution[2]]
        Xboucle = [pt[1] for pt in self.boucle]
        Yboucle = [pt[2] for pt in self.boucle]
        
        plt.plot(Xdi+Xboucle+Xdi,Ydi+Yboucle+Ydi,color = 'red')
        for i in range(len(self.antennes)):
            plt.plot(self.antennes[i][1],self.antennes[i][2],color = 'green',marker ='o')
        plt.plot(self.distribution[1],self.distribution[2],color = 'yellow',marker = 'o' )
        # on trace les branches
        
        for j in range (len(self.branche)):
            Xi = [self.boucle[j][1]]
            Yi = [self.boucle[j][2]]
            X = [pt[1] for pt in self.branche[j]]
            Y = [pt[2] for pt in self.branche[j]]
            plt.plot(Xi+X,Yi+Y, color = 'blue')
        
        
        
        #plt.axis = "equal"
        #plt.show()
    def cout_non_incremental(self):
        cout = self.I.l(self.distribution[0],self.boucle[0][0])
        for i in range(len(self.boucle)-1):
            cout+= self.I.l(self.boucle[i][0],self.boucle[i+1][0])
        cout += self.I.l(self.boucle[len(self.boucle)-1][0],self.distribution[0])
        for i in range(len(self.branche)):
            if (len(self.branche[i])>0):
                cout += self.I.l(self.boucle[i][0],self.branche[i][0][0])
                for j in range(len(self.branche[i])-1):
                    cout+=self.I.l(self.branche[i][j][0],self.branche[i][j+1][0])
                             
                                  
        return cout
            
    


# class recuit_simule_test:
#     def __init__(self,I,n):
#         self.taille = 5000
#         self.I = I
#         self.n = n
#         self.distribution,self.antennes = self.antennes_distribution()
#         self.xb = self.heuristique_recuit()
#         
#     def antennes_distribution(self):
#         return self.I.distribution[self.n],self.I.rangement[self.n]
#     def heuristique_recuit(self):
#         #for boucle_size in range(int(len(self.antennes)/6)+1,min(30,len(self.antennes))+1):
#         boucle_size = 30
#             #heuristique à partir d'ici
#             #on échange deux points et on actualise le cout
#         x0= solution_pour_une_distribution2(self.I,self.n,boucle_size)
#         print(x0.cout_non_incremental())
#         xb = cp.deepcopy(x0)
#         for compteur in range(self.taille):
#                 xprime = cp.deepcopy(xb)
#                 i = ran.randint(0,boucle_size-1)
#                 j = ran.randint(0,boucle_size-1)
#                 
#                 if (i!=j):   
#                     xprime.boucle[i],xprime.boucle[j]=xprime.boucle[j],xprime.boucle[i]
#                     xprime.branche[i],xprime.branche[j]=xprime.branche[j],xprime.branche[i]
#                     cxprime = xprime.cout_non_incremental()
#                     
#                     
#                 if cxprime < xb.cout_non_incremental() :
#                     xb = cp.deepcopy(xprime)
#                     print(xb.cout_non_incremental())
#                     
#                 
#                 
#                     
#         return xb

# nodes_file = open("/home/azam/Documents/instances/paris/nodes.csv")
# distances_file = open("/home/azam/Documents/instances/paris/distances.csv")
# I = Instances(nodes_file,distances_file)
# sol1 = recuit_simule_test(I,0) 
# #sol1.boucle,sol1.branche
# #print(sol1)
# #print(sol1.xb.cout_non_incremental())
# #print(sol1.xb.boucle)
# #print(sol1.x.cout)
# #print(sol1.xb.branche)
# sol1.xb.trace_solution()

# ### Recuit simulé

# On veut une différence de 200.
# On lui impose une probabilité de 0.5
# donc T final = $\frac{200}{-ln(0.5)}$
# Tf = 288

# In[10]:


class recuit_simule:
    def __init__(self,I,n,fichier=False):
        self.taille = 2000
        self.I = I
        self.n = n
        self.distribution,self.antennes = self.antennes_distribution()
        self.T = 100
        self.alpha = 0.7
        self.bestsol = self.heuristique_recuit()
        self.fichier = fichier
        
    def antennes_distribution(self):
        return self.I.distribution[self.n],self.I.rangement[self.n]
    def heuristique_recuit(self):
        xbfinal = solution_pour_une_distribution2(self.I,self.n,int(len(self.antennes)/6)+1)
        boucle_size_saved = int(len(self.antennes)/6)+1
        for boucle_size in range(int(len(self.antennes)/6)+1,min(30,len(self.antennes))+1):
            x= solution_pour_une_distribution2(self.I,self.n,boucle_size)
            xb =solution_pour_une_distribution2(self.I,self.n,boucle_size) 
            self.T=100
            proba = boucle_size/len(self.antennes)
            while (self.T>1):
                for compteur in range(self.taille):
                    if x.cout_non_incremental() < xb.cout_non_incremental() :
                        xb = cp.deepcopy(x)
                        print(boucle_size)
                        print(xb.cout_non_incremental())
                    #on se place dans un voisinage de x
                    xprime = cp.deepcopy(x)
                    a = True
                    
                    while(a):
                        
                        
                        #on construit le voisinage
                        p = ran.random()
                        if (p < proba*proba):#on échange deux points de la boucle de x
                            i = ran.randint(0,boucle_size-1)
                            j = ran.randint(0,boucle_size-1)
                            
                            if (i!=j):
                                xprime = cp.deepcopy(x)
                                xprime.boucle[i],xprime.boucle[j]=xprime.boucle[j],xprime.boucle[i]
                                xprime.branche[i],xprime.branche[j]=xprime.branche[j],xprime.branche[i]
                                a=False
                        elif (p<proba*proba +2*proba*(1-proba)):
                            i = ran.randint(0,boucle_size-1)
                            j = ran.randint(0,boucle_size-1)
                            if len(xprime.branche[j]) ==0:
                                a = True
                            else:
                                j1 = ran.randint(0,len(xprime.branche[j])-1)
                                xprime.boucle[i],xprime.branche[j][j1]=xprime.branche[j][j1],xprime.boucle[i]
                        
                        else:#on échange deux antennes
                            i = ran.randint(0,boucle_size-1)
                            j = ran.randint(0,boucle_size-1)
                            if len(xprime.branche[i]) ==0:
                                if len(xprime.branche[j])==0:
                                    a=True
                                else:
                                    j1 = ran.randint(0,len(xprime.branche[j])-1)
                                    xprime.branche[i].append(xprime.branche[j].pop(j1))
                                    a=False
                            elif len(xprime.branche[j])==0:
                                if len(xprime.branche[i])==0:
                                    a=True
                                else:
                                    i1 = ran.randint(0,len(xprime.branche[i])-1)
                                    xprime.branche[j].append(xprime.branche[i].pop(i1))
                                    a=False
                            else:
                                i1 = ran.randint(0,len(xprime.branche[i])-1)
                                j1 = ran.randint(0,len(xprime.branche[j])-1)
                                xprime.branche[i][i1],xprime.branche[j][j1] = xprime.branche[j][j1],xprime.branche[i][i1]
                                a=False
                                
                    cxprime = xprime.cout_non_incremental()
                    cx = x.cout_non_incremental()
                    #fin voisinage
                    if cxprime<cx:
                        x = cp.deepcopy(xprime)
                        #print(x.cout_non_incremental())
                    else:
                        p1 = ran.random()
                        if p1<np.exp(-(cxprime-cx)/self.T):
                            #print(np.exp(-(cxprime-cx)/self.T))
                            x = cp.deepcopy(xprime)
                      
                self.T = self.alpha*self.T
                coutfinal = xbfinal.cout_non_incremental()
            if xb.cout_non_incremental() < coutfinal:
                xbfinal = cp.deepcopy(xb)
                print("endblock")
                print(coutfinal)
                print(boucle_size)
                boucle_size_saved = boucle_size
        ##### MAINTENANT ON SE FOCUS SUR LA MEILLEURE BOUCLE_SIZE
        print("on commence la recherche profonde")
        x= cp.deepcopy(xbfinal)
        xb =cp.deepcopy(xbfinal)
        self.T=100
        proba = boucle_size_saved/len(self.antennes)
        while (self.T>1):
            for compteur in range(15000):
                if x.cout_non_incremental() < xb.cout_non_incremental() :
                    xb = cp.deepcopy(x)
                    print("nouvelle boucle")
                    print(xb.cout_non_incremental())
                #on se place dans un voisinage de x
                xprime = cp.deepcopy(x)
                a = True
                
                while(a):
                        
                        
                        #on construit le voisinage
                    p = ran.random()
                    if (p < proba*proba):#on échange deux points de la boucle de x
                        i = ran.randint(0,boucle_size_saved-1)
                        j = ran.randint(0,boucle_size_saved-1)
                            
                        if (i!=j):
                            xprime = cp.deepcopy(x)
                            xprime.boucle[i],xprime.boucle[j]=xprime.boucle[j],xprime.boucle[i]
                            xprime.branche[i],xprime.branche[j]=xprime.branche[j],xprime.branche[i]
                            a=False
                    elif (p<proba*proba +2*proba*(1-proba)):
                        i = ran.randint(0,boucle_size_saved-1)
                        j = ran.randint(0,boucle_size_saved-1)
                        if len(xprime.branche[j]) ==0:
                            a = True
                        else:
                            j1 = ran.randint(0,len(xprime.branche[j])-1)
                            xprime.boucle[i],xprime.branche[j][j1]=xprime.branche[j][j1],xprime.boucle[i]
                        
                    else:#on échange deux antennes
                        i = ran.randint(0,boucle_size_saved-1)
                        j = ran.randint(0,boucle_size_saved-1)
                        if len(xprime.branche[i]) ==0:
                            if len(xprime.branche[j])==0:
                                a=True
                            else:
                                j1 = ran.randint(0,len(xprime.branche[j])-1)
                                xprime.branche[i].append(xprime.branche[j].pop(j1))
                                a=False
                        elif len(xprime.branche[j])==0:
                            if len(xprime.branche[i])==0:
                                a=True
                            else:
                                i1 = ran.randint(0,len(xprime.branche[i])-1)
                                xprime.branche[j].append(xprime.branche[i].pop(i1))
                                a=False
                        else:
                            i1 = ran.randint(0,len(xprime.branche[i])-1)
                            j1 = ran.randint(0,len(xprime.branche[j])-1)
                            xprime.branche[i][i1],xprime.branche[j][j1] = xprime.branche[j][j1],xprime.branche[i][i1]
                            a=False
                            
                cxprime = xprime.cout_non_incremental()
                cx = x.cout_non_incremental()
                #fin voisinage
                if cxprime<cx:
                    x = cp.deepcopy(xprime)
                    #print(x.cout_non_incremental())
                else:
                    p1 = ran.random()
                    if p1<np.exp(-(cxprime-cx)/self.T):
                        #print(np.exp(-(cxprime-cx)/self.T))
                        x = cp.deepcopy(xprime)
                      
            self.T = self.alpha*self.T
        return xb
    def creer_un_fichier_from_distribution(self):# on rajoute au fichier les lignes de la best solution
        chaine = "b"+" "+str(self.bestsol.distribution[0])
        for boucle in self.bestsol.boucle:
            chaine = chaine+" "+ str(boucle[0])
        self.fichier.write(chaine+'\n')
        for i in range(len(self.bestsol.boucle)):
            chain = str(self.bestsol.boucle[i][0])
            if len(self.bestsol.branche[i])>0:
                for antenne in self.bestsol.branche[i]:
                    chain = chain+" "+str(antenne[0])
                self.fichier.write("c"+" "+chain+ '\n')
        
    


# nodes_file = open("/home/azam/Documents/instances/nice/nodes.csv")
# distances_file = open("/home/azam/Documents/instances/nice/distances.csv")
# I = Instances(nodes_file,distances_file)
# sol1 = recuit_simule(I,1) 
# #print(sol1.bestsol.boucle),print(sol1.bestsol.branche)
# #print(sol1.x.cout)
# print("final")
# print(sol1.bestsol.cout_non_incremental())
# sol1.bestsol.trace_solution()

# In[11]:


class solution_complete_recuit:
    def __init__(self,nodes_file,distances_file,fichier):
        self.I = Instances(nodes_file,distances_file)
        self.cout = 0
        self.fichier = fichier
    def final(self):
        for n in range(len(self.I.distribution)):
            sol = recuit_simule(self.I,n,fichier)
            self.cout += sol.bestsol.cout_non_incremental()
            sol.bestsol.trace_solution()
            sol.creer_un_fichier_from_distribution()
            print(n)
            print ("fin n")
        plt.axis ="equal"
        plt.show()
        print(self.cout)
    


# In[62]:


nodes_file = open("/home/azam/Documents/instances/grenoble/nodes.csv")
distances_file = open("/home/azam/Documents/instances/grenoble/distances.csv")
fichier = open("/home/azam/Documents/results/grenoble","w")
a1 = solution_complete_recuit(nodes_file,distances_file,fichier)
#print(a1.I.distribution)
a1.final()
fichier.close()


# In[17]:


nodes_file = open("/home/azam/Documents/instances/nice/nodes.csv")
distances_file = open("/home/azam/Documents/instances/nice/distances.csv")
fichier = open("/home/azam/Documents/results/nice","w")
a1 = solution_complete_recuit(nodes_file,distances_file,fichier)
#print(a1.I.distribution)
a1.final()
fichier.close()


# In[12]:


nodes_file = open("/home/azam/Documents/instances/paris/nodes.csv")
distances_file = open("/home/azam/Documents/instances/paris/distances.csv")
fichier = open("/home/azam/Documents/results/paris","w")
a1 = solution_complete_recuit(nodes_file,distances_file,fichier)
#print(a1.I.distribution)
a1.final()
fichier.close()


# Recherche Locale :
# On cherche à voir ce que l'on peut faire à partir d'une très bonne première solution. 

# In[ ]:




