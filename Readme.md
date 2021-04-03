# Растеризатор на CPU

## Теорминимум

### CMake
Хорошее видео [тут](https://www.youtube.com/watch?v=gSTLzOmFChs)   
А вот [тут](https://stackoverflow.com/questions/59095842/cmake-mingw-compilation-on-windows-without-needing-the-g-mingw-makefiles-f) написано о том, как использовать с MinGW

### Матрица перспективной проекции
Хорошая статья [тут](https://habr.com/ru/post/252771/)

### GDI
Примеры использования [тут](https://zetcode.com/gui/winapi/gdi/)

### Проверка на принадлежность точки треугольнику
Хорошая статья [тут](https://cpp.mazurok.com/triangle/)

### Общая концепция
Отличная статья [тут](https://habr.com/ru/post/257107/)

### Алгоритм интерполяции цвета по треугольнику
* Проецируем тругольник (он состоит из точек A, B, C) на CVV-плоскость z = -1.
* Счиатаем его площадь - S.
* Разбиваем его точкой, которая в данный момент прорисовывается на три треугольника.
* Считаем площади получившихся треугольников - S1, S2, S3.
* Тогда интерполяционный коэффициент: Mi = Si / S.
* Тогда цвет текущей вершины: Color(P) = Color(A) * M1 + Color(B) * M2 + Color(C) * M3.

## Организация работы
Логика следующая: код делится на две части - сам растеризатор и системное окно для тестирования.
Код написан таким образом, что растеризатор можно легко имплементировать на любую систему, достаточно указать функцию для прорисовки пикселя и вызывать необходимые прорисовочные функции.
### Диаграмма
![](https://github.com/timattt/Computer-science-knowledge/blob/master/CpuRasterizer/about/Concept.png)

## Пример
![](https://github.com/timattt/Computer-science-knowledge/blob/master/CpuRasterizer/about/NiceExample.gif)

