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