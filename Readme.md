# Фундаментальное изучение ЭВМ
Этот репозиторий содержит теорминимумы и проекты по следующим разделам информатики: операционные системы, 3D графика.
Проекты, представленные здесь: процессорный растеризатор. 

# English version
You can find english version of this README [here](https://github.com/timattt/Computer-science-knowledge/blob/master/README_EN.md)

# Схема кратокого обзора задач из этого репозитория по 3D графике
![](https://github.com/timattt/Computer-science-knowledge/blob/master/about/SYNOPSIS_SCHEME.png)

# Растеризатор на CPU

## Постановка задачи
Мы хотим сэмулировать работу GPU на CPU, а также построить весь цикл операций классического OpenGL.
У нас имеются исходные данные о пространстве и объектах в нем (в примере куб, значит у нас есть координаты его вершин в его локальном пространстве, на куб натянута текстура,
значит у нас есть текстурные координаты вершин и сама картинка), наша задача спроецировать это все из трехмерного пространства в двумерное и нарисовать в буфере экрана.
Буфер экрана предоставляется ОС. В данном случае используем winapi.

## Пример
![](https://github.com/timattt/Computer-science-knowledge/blob/master/CpuRasterizer/about/NiceExample.gif)

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

## Организация работы
Логика следующая: код делится на две части - сам растеризатор и системное окно для тестирования.
Код написан таким образом, что растеризатор можно легко имплементировать на любую систему, достаточно указать функцию для прорисовки пикселя и вызывать необходимые прорисовочные функции.
### Диаграмма
![](https://github.com/timattt/Computer-science-knowledge/blob/master/CpuRasterizer/about/Concept.png)


