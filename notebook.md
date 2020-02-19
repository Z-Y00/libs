# cpp
## Virtual/pure virtual explained
https://stackoverflow.com/questions/2156634/why-is-a-pure-virtual-function-initialized-by-0
https://stackoverflow.com/questions/1306778/virtual-pure-virtual-explained

    virtual void foo(const T& oo) {}//this will make the runtime call the actual
Unlike a non-virtual function, when a virtual function is overridden the most-derived version is used at all levels of the class hierarchy, rather than just the level at which it was created. Therefore if one method of the base class calls a virtual method, the version defined in the derived class will be used instead of the version defined in the base class. 

This is in contrast to non-virtual functions, which can still be overridden in a derived class, but the "new" version will only be used by the derived class and below, but will not change the functionality of the base class at all.
or 

 What virtual does is to give you polymorphism, that is, the ability to select at run-time the most-derived override of a method.
 
 I hope this wasn't too confusing. In short, any method can be overridden, but only virtual methods give you polymorphism, that is, run-time selection of the most derived override. In practice, however, overriding a non-virtual method is considered bad practice and rarely used, so many people (including whoever wrote that Wikipedia article) think that only virtual methods can be overridden.
 
    virtual void foo(void* oo) = 0;//this would turn it & derived to abstract, untill the derived define it
    
https://www.cnblogs.com/wanqieddy/p/4369367.html

## default construct POD
https://stackoverflow.com/questions/12979529/default-constructors-and-pod

things like Foo(){}, will make this no longer POD
so, we should use Foo()=default


std::is_pod<A>::value 
assert this
## static_cast & dynamic_cast
https://blog.csdn.net/u014624623/article/details/79837849
```
if(Derived *dp = dynamic_cast<Derived *>(bp)){
  //使用dp指向的Derived对象  
}
else{
  //使用bp指向的Base对象  
}
void f(const Base &b){
 try{
   const Derived &d = dynamic_cast<const Base &>(b);  
   //使用b引用的Derived对象
 }
 catch(std::bad_cast){
   //处理类型转换失败的情况
 }
}
```

## hack the long class and obj 
in Class.h
```
static uint64_t iter;
```
in Class.cc
```
 uint64_t GPUBFCAllocator::iter=0;

```
in Target.cc
```
  GPUBFCAllocator::iter=step_id;//this is how to make the GPUBFCAllocator get the step_id
```
