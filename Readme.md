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

## Пример кода
### Fixed pipeline
```
int init() {
	// Init context
	InitContext();

	// Set pixel draw function
	SetFrameBufferCallFunction(SetFbPixel);

	// Set texture loader
	SetTextureLoader(loadTexture);

	// Texture
	LoadTexture((char*)(L"Texture.bmp"), &txtr);

	// Set vbo recognition mask
	SetVBOMask(VERTEX_COORDS | COLOR | TEXTURE_COORDS);

	// Create VBO
	CreateVertexBuffer(TOTAL_CUBE_VERTS, &vbo);

	// Bind vbo
	BindBuffer(vbo);

	// load into vbo
	LoadIntoVertexBuffer((char*) SOME_BUFFER, TOTAL_CUBE_VERTS);

	// Unbind vbo
	UnbindBuffer();

	// Set projection matrix
	SetProjectionMaxtrix(CreateProjection_mat4f(3.1415f / 2.0f, 1.0f, 0.5f, 6.0f));

	// Set model matrix
	SetModelMatrix(CreateTranslationMatrix_mat4f(0, 0, 4.0f));

	return 0;
}

int draw() {
	// Flush depth buffer
	FlushDepthBuffer();

	// Set buffer mask
	SetVBOMask(VERTEX_COORDS | COLOR | TEXTURE_COORDS);

	// Bind buffer
	BindBuffer(vbo);

	// Bind texture
	BindTexture(txtr);

	// Draw call
	Draw(TOTAL_CUBE_VERTS);

	// Unbin texture
	UnbindTexture();

	// Unbind buffer
	UnbindBuffer(vbo);

	return 0;
}

int destroy() {
	DestroyVertexBuffer(vbo);
	DestroyContext();
	return 0;
}
```
### Simple shader example
```
VERTEX_SHADER(TEST, {
		// Attributes
		//------------------
		// IN
		V_IN_ATTRIBUTE_F(3, POS, 0);
		V_IN_ATTRIBUTE_F(4, COL, 3);
		V_IN_ATTRIBUTE_F(2, TXTR_POS, 7);

		// OUT
		V_OUT_ATTRIBUTE_F(4, OUT_COL, 0);
		V_OUT_ATTRIBUTE_F(2, OUT_TXTR_POS, 4);
		//------------------

		// Code
		VEC(4) ps = VEC4(POS, 1);

		OUT_ATTRIBUTE(CVV_POS) = MUL_MV(4, PROJ_MAT, MUL_MV(4, MODEL_MAT, ps));
		OUT_ATTRIBUTE(OUT_COL) = COL;
		OUT_ATTRIBUTE(OUT_TXTR_POS) = TXTR_POS;

});

FRAGMENT_SHADER(TEST, {
		// Attributes
		//------------------
		// IN
		F_IN_ATTRIBUTE_F(4, COL, 0);
		F_IN_ATTRIBUTE_F(2, TXTR_POS, 4);
		//------------------

		// Code
		OUT_ATTRIBUTE(FRAG_COLOR) = ADD_VV(4, SAMPLER_2D(TEXTURE, TXTR_POS), COL);
});
```

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


