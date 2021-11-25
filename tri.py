# -*- coding: utf-8 -*-
"""
Created on Fri Nov 19 01:49:34 2021

@author: Julien
"""

import numpy as np
from random import randint as rand 
from time import time as tm

def copie_tableau(tb_a, tb_b, taille_tb):
    for i in range(0,taille_tb):
        tb_b[i] = tb_a[i]

def tri_bulles(tb, taille_tb):
    i= taille_tb
    echange =1
    begin = tm()
    while i>0 and echange:
        echange = 0
        for j in range(0,i-1):
            if tb[j]>tb[j+1]:
                temp = tb[j]
                tb[j] = tb[j+1]
                tb[j+1] = temp
                echange = 1
        i -= 1
    end = tm()
    return (end-begin)*1000

def tri_selection(tb, taille_tb):
    tb_temp = np.empty(taille_tb, dtype=int)
    copie_tableau(tb, tb_temp, taille_tb)
    j= taille_tb-1
    begin = tm()
    while j>=0:
        max=0
        for i in range(0,taille_tb):
            if tb_temp[i]> max:
                max_pos = i
                max = tb_temp[i]
        tb[j]= tb_temp[max_pos]
        j -= 1
        tb_temp[max_pos]=-1
    end = tm()
    return (end-begin)*1000

def fusion(tb, tb_tmp, debut, mil, fin):
    i = debut
    j= mil+1
    for k in range(debut, fin+1):
        if j>fin or i<= mil and tb[i]<tb[j]:
            tb_tmp[k] =tb[i]
            i+=1
        else:
            tb_tmp[k] =tb[j]
            j+=1
    for k in range(debut, fin+1):
        tb[k]=tb_tmp[k]

def tri_fusion(tb, taille_tb):
    tb_tmp = np.empty(taille_tb, dtype=int)
    i =1
    begin = tm()
    while i<= taille_tb:
        debut = 0;
        while debut+i-1 < taille_tb:
            fin = debut+(i*2)-1
            if fin > taille_tb-1:
                fin = taille_tb-1
            fusion(tb, tb_tmp, debut, debut+i-1, fin)
            debut = debut+(i*2)
        i += i
    end = tm()
    return (end-begin)*1000

def comparaison_tri(tb, taille_tb):
    tb_res = np.empty(taille_tb, dtype=int)
    tb_tmp = np.empty(taille_tb, dtype=int)
    copie_tableau(tb, tb_tmp, taille_tb)
    for i in range(0,3):
        copie_tableau(tb_tmp, tb, taille_tb)
        if i ==0:     
            tps_b = tri_bulles(tb, taille_tb)
            tb_res[i] = tps_b 
        if i==1:
            tps_f = tri_fusion(tb, taille_tb)
            tb_res[i] = tps_f
        if i==2:
            tps_s = tri_selection(tb, taille_tb)
            tb_res[i] = tps_s
    tri_bulles(tb_res, taille_tb)
    for pos,i in enumerate(tb_res):
        if i == tps_b:
            print("position", pos+1, " : tri a bulles avec une duree d'execution de", tb_res[i],"ms \n")
            tps_b = -1
        elif i == tps_f:
            print("position", pos+1, " : tri fusion avec une duree d'execution de", tb_res[i],"ms \n")
            tps_f = -1
        elif i == tps_s:
            print("position", pos+1, " : tri selection avec une duree d'execution de", tb_res[i],"ms \n")
            tps_s = -1

def main():
    types=[
           "tri a bulles",
           "tri selection",
           "tri fusion"
           ]
    taille_tb = -1
    while taille_tb<1:
        taille_tb = int(input("Veuiller indiquer la taille du tableau(superieur a 0): \n"))
        if taille_tb < 1:
            print("le nombre indique n'est pas bon \n")
    choix_tri = -1
    while choix_tri<1 or choix_tri>4:
        choix_tri = int(input("Veuillez selectionner le type de tri (1:tri a bulle, 2:tri selection, 3: tri fusion, 4: comparaison tri): \n"))
        if choix_tri<1 or choix_tri>4:
            print("Le choix n'est pas bon \n")
    choix_mode = -1
    while choix_mode < 0 or choix_mode > 1:
        choix_mode = int(input("Veuillez selectionner le mode de tri (0: ordre croissant, 1: ordre decroissant): \n"))
        if choix_mode < 0 or choix_mode > 1:
            print("Le choix n'est pas bon \n")
            
    tb_in = np.empty(taille_tb, dtype=int)
    tb_out = np.empty(taille_tb, dtype=int)
    for i in range(0,taille_tb):
        temp = rand(0,10000)
        tb_in[i]= temp
        tb_out[i] = temp
    
    if choix_tri == 1:
        tps = tri_bulles(tb_out, taille_tb)
    elif choix_tri == 2:
        tps = tri_selection(tb_out, taille_tb)
    elif choix_tri == 3:
        tps = tri_fusion(tb_out, taille_tb)
    elif choix_tri == 4:
        comparaison_tri(tb_out, taille_tb)
    
    print("tableau de depart:", tb_in, " \n")
    if choix_mode:
        print("tableau trié:", np.flip(tb_out), " \n")
    else:
        print("tableau trié:", tb_out, " \n")
    if choix_tri>=1 and choix_tri<=3:
    	print("type de tri:", types[choix_tri-1])
    	print("temps d'execution", tps, "ms")

main()
    