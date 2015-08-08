## Qt学习笔记与代码

阅读《Qt5 开发与实例》过程中记录Qt学习过程中一些笔记以及相应的代码

1. 计算圆面积: Dialog
**Note**: 书中P15页代码笔误：

```cpp
ui->areaLabel_2->setText(tempStr.setNum(area));
```

应更正为：

```cpp
ui->radiusLabel->setText(tempStr.setNum(area));
```

2015年7月17日读完第一章。

2. QHash类：STL风格迭代器。

3. 控件：按钮组。`setGeometry(x, y, w, h)`，`(x, y)`表示左上顶点。
**Note**: P56页:

```cpp
connect(quit, SINAL(clicked()), aApp, SLOT(quit()))
```
中`qApp`所指得槽对象是哪个？



