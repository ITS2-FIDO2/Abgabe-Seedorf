---
title: "Aktuelle Themen der IT-Sicherheit: RIOT Challenges"
subtitle: "WS 22/23: Prof. Dr. Jan Seedorf"  
author: [Thomas Jakkel (Mat. Nr), Severin Nonenmann (Mat. Nr), Lukas Reinke (1001213) (Mat. Nr), Lars Weiß (Mat. Nr)]
date: "29. Januar 2023"
keywords: [Markdown, Example]
lang: "de"
titlepage: true
titlepage-background: "images/background6.pdf"
titlepage-rule-color: "AAAAAA"
toc: true
toc-title: "Inhalt"
toc-own-page: true
footer-left: "WS 22/23: Prof. Dr. Jan Seedorf"
---

# Woche 1

## Challenge 1: VM installation

Das VM setup wird hier nicht genauer beschrieben.

## Challenge 2: Erste schritte mit RIOT

Die Anleitung zum setup von RIOT OS aus den RIOT Tutorials wurde durchlaufen und ein funktionierender Workspace erstellt.

Wir haben das setup Insofern verändert, dass unsere Änderungen in einem separaten Ordner neben dem von GitHub geklonten RIOT Dateien stattfanden.

### First_test Application

Das Ziel ist ein erstes RIOT-OS selber zu kompilieren, mit einer eigen Funktion zu versehen und zu starten.

Im default Makefile mussten zwei Änderungen vorgenommen werden:
1. In der Variable `APPLICATION` der Name der Ausführbaren binary zu setzen
2. Die `RIOTBASE`, dem Pfad zu den Hauptdateien des RIOT-OS, zu setzen.

![](./images/1_2_3-Makefile.png)


