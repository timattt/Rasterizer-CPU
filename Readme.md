# Фундаментальное изучение компьютерной графики
Этот репозиторий содержит теорминимумы и проекты по 3D графике.

Хорошая книга по графике [тут](https://drive.google.com/file/d/1Lv1zbpjWPlhq8kvIf6lOIHLKNXTcEg9V/view?usp=sharing)

# English version
You can find english version of this README [here](https://github.com/timattt/Project-fundamental-graphics/blob/master/README_EN.md)

# Схема задач из этого репозитория
![](https://github.com/timattt/Project-fundamental-graphics/blob/master/about/SYNOPSIS_SCHEME.png)

# Растеризатор на CPU

## Постановка задачи
Мы хотим сэмулировать работу GPU на CPU, а также построить весь цикл операций классического OpenGL.
У нас имеются исходные данные о пространстве и объектах в нем (в примере куб, значит у нас есть координаты его вершин в его локальном пространстве, на куб натянута текстура,
значит у нас есть текстурные координаты вершин и сама картинка), наша задача спроецировать это все из трехмерного пространства в двумерное и нарисовать в буфере экрана.
Буфер экрана предоставляется ОС. В данном случае используем winapi.

## Пример
![](https://github.com/timattt/Project-fundamental-graphics/blob/master/CpuRasterizer/about/NiceExample.gif)

## Более сложный пример
![](https://github.com/timattt/Project-fundamental-graphics/blob/master/CpuRasterizer/about/FINAL_EXAMPLE.gif)

## Теорминимум

### CMake
Хорошее видео [тут](https://www.youtube.com/watch?v=gSTLzOmFChs)   
А вот [тут](https://stackoverflow.com/questions/59095842/cmake-mingw-compilation-on-windows-without-needing-the-g-mingw-makefiles-f) написано о том, как использовать с MinGW
А вот [тут](https://stackoverflow.com/questions/52255867/adding-a-dll-to-cmake) сказано, как подключать библиотеки
А вот [тут](https://stackoverflow.com/questions/34799916/copy-file-from-source-directory-to-binary-directory-using-cmake) и [тут](https://stackoverflow.com/questions/697560/how-to-copy-directory-from-source-tree-to-binary-tree) информация о том, как копировать файлы

### Assimp
Примеры для начала использования [здесь](http://assimp.sourceforge.net/lib_html/usage.html)

### Матрица перспективной проекции
Хорошая статья [тут](https://habr.com/ru/post/252771/)

### GDI
Примеры использования [тут](https://zetcode.com/gui/winapi/gdi/)

### Проверка на принадлежность точки треугольнику
Хорошая статья [тут](https://cpp.mazurok.com/triangle/)

### Общая концепция
Отличная статья [тут](https://habr.com/ru/post/257107/)

### Модель освещения Фонга
Две хорошие статьи [тут](https://compgraphics.info/3D/lighting/phong_reflection_model.php) и [тут](https://ravesli.com/urok-11-bazovoe-osveshhenie-v-opengl/)

## Организация работы
Логика следующая: код делится на две части - сам растеризатор и системное окно для тестирования.
Код написан таким образом, что растеризатор можно легко имплементировать на любую систему, достаточно указать функцию для прорисовки пикселя и вызывать необходимые прорисовочные функции.

# Shader toy
Shader toy - программа для тестирования простых шейдоров на glsl.
Хорошее видео [тут](https://www.youtube.com/watch?v=u5HAYVHsasc&ab_channel=TheArtofCodeTheArtofCode)

# Ray marching
Хорошее видео [тут](https://www.youtube.com/watch?v=PGtv-dBi2wE&list=LL&index=7&ab_channel=TheArtofCode), и [тут](https://www.youtube.com/watch?v=Ff0jJyyiVyw&ab_channel=TheArtofCode), и [тут](https://www.youtube.com/watch?v=AfKGMUDWfuE&ab_channel=TheArtofCode).
А вот [тут](https://www.shadertoy.com/view/ssBXzw) мой мини-шейдер.

![](https://github.com/timattt/Project-fundamental-graphics/blob/master/about/RAY_MARCHING_EXAMPLE.gif)

# Cube marching

Хорошая статья [тут](https://m.habr.com/ru/post/358658/)
