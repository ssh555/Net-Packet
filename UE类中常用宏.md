在 Unreal Engine 中，`UCLASS`、`UPROPERTY`、`UFUNCTION` 等宏用于实现反射、蓝图支持和序列化等功能。它们是 Unreal Engine 的反射系统的核心部分，允许 Unreal 引擎的编辑器、蓝图和其他工具识别类和成员，并提供一些额外的功能和元数据。

### 1. **UCLASS**
`UCLASS` 是用来声明 Unreal Engine 类的宏，它提供了 Unreal Engine 反射系统和其他功能（如序列化、蓝图支持等）。它通常用于类定义的前面。

#### 常见参数：
- `Blueprintable`：表示该类可以作为蓝图类进行继承。
- `BlueprintType`：表示该类可以在蓝图中使用（不一定能作为基类）。
- `Abstract`：表示该类是抽象类，不能被实例化，只能作为基类。
- `NotBlueprintable`：表示该类不能被用作蓝图基类。
- `Transient`：表示该类的实例不会被保存到磁盘。
- `PerObjectConfig`：表示该类的配置是每个对象独立的。
- `MinimalAPI`：表示该类将暴露给其他模块，并限制暴露的 API。
- `EditInlineNew`：表示可以在编辑器中创建该类的实例。

#### 示例：
```cpp
UCLASS(Blueprintable, Abstract)
class MYPROJECT_API UMyClass : public UObject
{
    GENERATED_BODY()

public:
    UMyClass();
};
```

### 2. **UPROPERTY**
`UPROPERTY` 宏用于定义 Unreal Engine 中的属性，允许引擎进行序列化、编辑器支持和反射等功能。它可以附加到类成员变量上，以启用对这些变量的控制。

#### 常见参数：
- `VisibleAnywhere`：该属性在任何地方都是可见的（包括编辑器）。
- `VisibleInstanceOnly`：仅在实例中可见。
- `EditAnywhere`：允许该属性在编辑器中编辑。
- `EditDefaultsOnly`：只能在默认对象中编辑。
- `BlueprintReadOnly`：该属性在蓝图中是只读的。
- `BlueprintReadWrite`：该属性在蓝图中是可读写的。
- `Transient`：该属性不会被序列化。
- `Config`：该属性值会被写入配置文件。
- `Category`：设置该属性在编辑器中的分类。
- `meta`：附加额外的元数据，比如 `DisplayName` 或 `ClampMin`。
- `AdvancedDisplay`：表示该属性为高级设置，通常被折叠起来。

#### 示例：
```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
int32 MyIntValue;
```

### 3. **UFUNCTION**
`UFUNCTION` 用于声明 Unreal Engine 的方法。它用于启用蓝图支持、远程调用（例如网络）、反射等。

#### 常见参数：
- `BlueprintCallable`：表示该方法可以在蓝图中调用。
- `BlueprintPure`：表示该方法没有副作用，仅返回值，适合用在蓝图中。
- `BlueprintImplementableEvent`：表示该函数是一个蓝图事件，可以在蓝图中实现。
- `BlueprintNativeEvent`：表示该方法是一个原生事件，可以在 C++ 中实现，也可以在蓝图中实现。
- `Server`：用于网络编程，表示该方法只能从服务器端调用。
- `Client`：用于网络编程，表示该方法只能从客户端调用。
- `Reliable`：表示该方法的调用是可靠的，会确保调用到达目标。
- `Unreliable`：表示该方法的调用是非可靠的，可能会丢失。
- `NetMulticast`：表示该方法会在客户端和服务器端广播执行。
- `Category`：设置方法所属类别（仅用于编辑器和蓝图）。

#### 示例：
```cpp
UFUNCTION(BlueprintCallable, Category = "MyCategory")
void MyFunction();

UFUNCTION(BlueprintImplementableEvent, Category = "MyCategory")
void MyEvent();
```

### 4. **UMETA**
`UMETA` 是用来附加元数据的宏，可以与 `UPROPERTY`、`UCLASS` 和 `UFUNCTION` 结合使用，用来提供额外的信息给引擎。

#### 常见参数：
- `DisplayName`：设置属性的显示名称。
- `ClampMin`、`ClampMax`：限制数值的最小值和最大值。
- `ToolTip`：为属性提供提示文本。
- `MakeEditWidget`：表示属性是一个可以在编辑器中交互的控件。

#### 示例：
```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory", meta = (ClampMin = "0", ClampMax = "100"))
int32 MyClampedValue;
```

### 5. **UENUM**
`UENUM` 用于声明枚举类型，并使其与 Unreal Engine 的反射系统兼容，可以在蓝图中使用。

#### 常见参数：
- `BlueprintType`：使该枚举类型在蓝图中可用。
- `Meta = (DisplayName = "My Enum")`：为枚举类型设置显示名称。

#### 示例：
```cpp
UENUM(BlueprintType)
enum class EMyEnum : uint8
{
    Value1 UMETA(DisplayName = "First Value"),
    Value2 UMETA(DisplayName = "Second Value"),
    Value3 UMETA(DisplayName = "Third Value")
};
```

### 6. **USTRUCT**
`USTRUCT` 用于声明结构体，并使其与 Unreal Engine 的反射系统兼容，可以在蓝图中使用。

#### 常见参数：
- `BlueprintType`：使该结构体类型在蓝图中可用。
- `Meta = (DisplayName = "My Struct")`：为结构体设置显示名称。
- `Transient`：表示该结构体的实例不会被序列化。

#### 示例：
```cpp
USTRUCT(BlueprintType)
struct FMyStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MyValue;
};
```

### 7. **UINTERFACE**
`UINTERFACE` 用于声明接口类，通常与 `I` 开头的接口类结合使用。接口类不能实例化，但可以被其他类实现。

#### 示例：
```cpp
UINTERFACE(MinimalAPI)
class UMyInterface : public UInterface
{
    GENERATED_BODY()
};

class MYPROJECT_API IMyInterface
{
    GENERATED_BODY()

public:
    virtual void MyFunction() = 0;
};
```

### 8. **UDELEGATE**
`UDELEGATE` 用于声明代理（delegate）。代理在 Unreal Engine 中常用于事件和回调机制。

#### 常见参数：
- `BlueprintCallable`：使代理在蓝图中可用。
- `Category`：设置代理的类别。

#### 示例：
```cpp
DECLARE_DYNAMIC_DELEGATE(FMyDelegate);

UFUNCTION(BlueprintCallable, Category = "MyCategory")
void RegisterDelegate(FMyDelegate MyDelegate);
```

### 总结

- **UCLASS**: 声明类的宏，控制类的反射、序列化、蓝图支持等。
- **UPROPERTY**: 用于类成员的宏，允许属性在编辑器、蓝图等中暴露并控制其行为。
- **UFUNCTION**: 用于函数声明的宏，使函数能够在蓝图中调用或参与反射等。
- **UMETA**: 附加元数据的宏，提供额外的信息给引擎。
- **UENUM**: 用于枚举类型的宏，使其在反射系统中可用。
- **USTRUCT**: 用于结构体类型的宏。
- **UINTERFACE**: 用于声明接口类的宏。
- **UDELEGATE**: 用于声明代理的宏。

这些宏可以帮助你将 Unreal Engine 的类、属性、函数等集成到引擎的编辑器、蓝图和反射系统中，从而使游戏开发更加高效。