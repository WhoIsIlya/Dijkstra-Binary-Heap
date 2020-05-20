<h1>Алгоритм Дейкстры на бинарной куче</h1>

<h2>Описание</h2>
<p>Имеются города с номерами от 1 до N и дороги между некоторыми из них. По дороге можно ехать в любом направлении. Известна длина каждой дороги. Нужно найти кратчайший путь из города S в город T.</p>

<h2>Ввод</h2>
<p>Из файла INPUT.TXT. Первая строка содержит количество городов N, дорог M, номера начального S и конечного города T. В каждой из следующих M строк находится по 3 числа. Первые два из них i и j задают дорогу, а третье Cij – ее длину.</p>

<h2>Вывод</h2>
<p>В файл OUTPUT.TXT. В первой строке протяженность кратчайшего пути, а во второй последовательность вершин этого пути. Если пути не существует единственную строку со словом No.</p>

<h2>Ограничения</h2>
2 ≤ N ≤ 104; 2 ≤ M ≤ 105; 0 ≤ Cij ≤ 105.

<h2>Ввод</h2>

```
4 5 4 2
1 2 3
1 3 2
1 4 7
2 4 10
3 4 4
```

<h2>Вывод</h2>

```
9
4 3 1 2
```
