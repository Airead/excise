# 学习 requirejs
目标: requirejs 是如何实现异步加载的？

### 2级目标：整体了解 requirejs 代码组织

```js
// utils functions

function newContext(contextName){
    // utils functions
    handlers = {require: function (){}, exports: function(){}, module: function(){}};

    Module = function() {};
    Module.prototype = {any: function(){}};
    // Module functions:
    // init / defineDep / fetch / load / check / callPlugin / enable / on / emit

    context = { /* ... with functions */};
    context.require = context.makeRequire();
    // context function:
    // configure / makeShimExports / makeRequire / enable / completeLoad / nameToUrl
    //           / load / execCb / onScriptLoad / onScriptError
};

req = requirejs = function(deps, callback, errback, optional) {
    // 配置 context
    // call context.require(deps, ccallback, errback)
}
req({}); // Create default context.
// req.someFunction

define = function(name, deps, callback) {}

req(cfg); // main enterpoint
```

两大块，
1. 如何定义模块？ `Module`
2. 如何加载依赖？ `context.require`

## 2级目标
requirejs 是如何加载一个js的？

```js
context.require(deps, callback, errback)

```

发现最终调用了 req.load()

### 3级目标 轮廓 makeRequire

```js
function makeRequire(relMap, options) {
    function localRequire(deps, callback, errback) {
        // first deal deps=string and relMap
        // 处理 require('util');

        // deal ['util', 'jquery']
        intakeDefines();
        context.nextTick(function () {
            intakeDefines();

            // getmod / initmod /  checkloaded
            requireMod = getModule(makeModuleMap(null, relMap));

            requireMod.init(deps, callback, errback, {
                enabled: true
            });

            checkLoaded();
        });
    }

    mixin = (localRequire, {
        toUrl: function (){},
        defined: function (){},
        specified: function (){},
    });

    // add undef for top level require calls,  if !relMap
    localRequire.undef = function(){};

    return localRequire;
}
```

### 3级目标 轮廓 intakeDefines()
猜想：加载了所有在 globalQueue 和 defQueue 里的
```js
// 将 globalQueue 里的 item 移到 context.defQueue
takeGlobalQueue();

// 如果已经 defined 那就 skip, defined 在 Module.check 里设置
// 否则就调用 getModule
callGetModule(args);

context.defQueueMap = {}; // reset
```

#### 4级目标 globalDefQueue 有什么用？如何操作的？
只有在 define 的时候会修改 globalDefQueue

需知道 define 都做了什么

## 2级目标 轮廓 define

```js
define = function (name, deps, callback) {}
```

1. 定义模块
2. 加入队列
    2.1 有 context 加入 context.defQueue
    2.2 否则加入 globalDefQueue

context 通过 currentlyAddingScript 中的 data-requirecontext 获取，
而 data-requirecontext 在 req.load 中设置

猜想：req.load 加载哪个就能设备哪个

### 3级目标 轮廓 如何获取可以 init 的 requireMod

```js
getModule(makeModuleMap(null, relMap));

// 根据 depMap 获取 mod
//    1. registry 中有就拿 ， registry 作为一个 cache 存在
//    2. 没有就生成一个
function getModule(depMap){};

// moduleMap 描述了 mod 的一切
function makeModuleMap(name, parentModuleMap, isNormalized, applyMap) {};
```

### 3级目标 轮廓 如何 module.init
```js
// 只有 module 才能init, 就先模拟一个 requireMod 然后 init
// ModuleMap -> Module.init()
init = function (depMaps, factory, errback, options) {
    // 配置信息 如上参数信息
    this.enable() || this.check()

    // context enable 短一些，最终调用 Module.enable
    // Module enable 长一些
};
```

#### 4级目标 轮廓 Module.enable
1. enable 每个依赖的 depMap
2. 注册 `defined` 和 `error` 事件
3. 添加 `registry[id]`

```js
on(depMap, 'defined', function() {
    this.check();
})
```
#### 4级目标 轮廓 Module.check
1. 只 Module.fetch
2. 出错
3. defining
    3.1 设置 exports
    3.2 加入 defined[id]
    3.3 清理 gobal|Registry[id]
    3.4 emit `defined` once

仅 emit defined 一次

enable 注册 defined , check emit defined

#### 4级目标 轮廓 fetch
1. shim or not
2. skip plugin, Module.load()  加载 module

Moulde.load call context.load call req.load with context

## 2级目标 轮廓 req.load 加载一个js
```js
req.load = function (context, moduleName, url) {
    // 创建 script
    // set data-someAttr
    // 添加 load / error 事件
    // set script.src 加载
    // head.appendChild(script)
};

// 脚本加载完成后
onScriptLoad = function (evt) {}
completeLoad = function (moduleName) {
    // 加载所有 defQueue 中的 module
    // 加载 moduleName module

    // 1. 检查加载的 module
    // 2. 超时判断
    // 3. 其它工作
    checkLoaded();
}
```

### 3级目标 轮廓 factory 在哪调用了
在 Module.check() 里调用了 context.execCb(id, factory, depExports, exports)

## 感性认识
1. requirejs 是什么？
    它实现了 AMD
2. requirejs 怎么样？
3. 他有什么好处？为什么？
5. 他有什么坏处？为什么？

## 2级目标 轮廓 数据结构有哪些？如何表示？
globalDefQueue and context.defQueue

```js
defQueue = [
    [name, deps, factory],
    [name, deps, factory],
];

```

### 3级目标 轮廓 哪些函数使用了 defQueue
```js
var defQueue = [
    [name, deps, factory],
    [name, deps, factory],
];

define() // 最初的添加

makeRequire() // 的 relMap 分支
    intakeDefines() // callGet defQueue Modules
        takeGlobalQueue()

// onScriptLoad()
    takeGlobalQueue()
    completeLoad() // callGet defQueue Modules && callGetModule(name)
```

#### 4级目标 轮廓 callGetModule 做了什么

## 理性认识
AMD -> define
          |-- id
          |-- deps
          |-- factory

require ->

```js
define(['require'], function (require) {
    //the require in here is a local require.
});

define(function (require, exports, module) {
    //the require in here is a local require.
});
```

---

# 学习 AMD

# 参考资料
https://github.com/amdjs/amdjs-api

