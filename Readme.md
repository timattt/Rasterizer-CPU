# Растеризатор на CPU

## Теорминимум

### Матрица перспективной проекции
Хорошая статья [тут](https://habr.com/ru/post/252771/)

### GDI
Примеры использования [тут](https://zetcode.com/gui/winapi/gdi/)

### Проверка на принадлежность точки треугольнику
Хорошая статья [тут](https://cpp.mazurok.com/triangle/)

### Алгоритм интерполяции цвета по треугольнику
* Проецируем тругольник (он состоит из точек A, B, C) на CVV-плоскость z = -1.
* Счиатаем его площадь - S.
* Разбиваем его точкой, которая в данный момент прорисовывается на три треугольника.
* Считаем площади получившихся треугольников - S1, S2, S3.
* Тогда интерполяционный коэффициент: Mi = Si / S.
* Тогда цвет текущей вершины: Color(P) = Color(A) * M1 + Color(B) * M2 + Color(C) * M3.

## Организация работы
![](https://github.com/timattt/Computer-science-knowledge/blob/master/CpuRasterizer/Concept.png)

## Пример
![](https://github.com/timattt/Computer-science-knowledge/blob/master/CpuRasterizer/Example.png)

