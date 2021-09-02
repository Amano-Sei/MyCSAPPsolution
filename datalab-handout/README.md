# Data Lab

2021-09-02 午 突然想起来`isTmax`好像之前也出过问题的样子，阅读19年9月16日的记录发现果然...然后我用`gcc-7 (Ubuntu 7.5.0-6ubuntu2) 7.5.0`编译了一次果然bug消失了，懒得去求证最新版本的gcc修复了么（说实话自从博客关掉之后我就很少会打开ubuntu了...所以就这样吧。

2021-08-31 夜 时隔两年了，说起来这个文档当初我还不怎么会写markdown来着...另外data lab出新版本了，看眼release notes，好像就多了个write up。然后是关于`floatPower2`超时我想有了最终的结论，详细可见[这里](https://github.com/Amano-Sei/MyCSAPPsolution/issues/2)。另外我现机器环境不需要修改超时时间即可全过，但是出现了一个奇怪的小bug，详细可以阅读`isTmax`部分的注释。

2019-09-16 下 更新：突然意识到自己之前太浮躁了，所以简单地把fpu的教程过了下，成功读懂了m32的test\_floatPower2的机器代码，确认了没有（本来就知道没有的）死循环，也感受了fpu的寄存器栈有多麻烦，但是（重点来了，我还是不会写fpu的汇编代码←说的你好像会写avx2版本的一样。嘛csapp如是说，"现在不再要求程序员会写汇编，只要会读就可以了"，如果需要更进一步的学习指令集什么的到需要的时候再说  
另外因为这周末有ccpc现场赛，和专业课有一丢丢迷糊的地方（虽然只要一两个小时应该就可以完全搞定，只是在找借口，所以csapp会稍稍降低一点比重，c4（含lab）的期望完成时间是十一前  
另外还有一点诡异的事情，我在同学新装的ubuntu 19.04(gcc 8.3)上用-m64编译的话isTmax过不了...仔细确认了自己的代码没有逻辑错误之后，猜想可能和gcc版本导致的运算符优先级不同有关...但是不好意思再拉下脸请求他再去试一次了...反正逻辑没有错，就这样吧...  
  
2019-09-15 午 更新：观察了-m32和-m64产生的tests.c的机器代码，发现m32似乎是从第一个参数开始就是用栈传递的...和一堆不知道是什么的浮点指令...姑且当做是m32的浮点指令比较慢的原因导致的吧（  
  
2019-09-14 夜 更新：改掉了一个爆蠢的地方...惊了，居然有人看我的solution的，大概不会再在自己solution里随意倒情绪垃圾了QAQ  
  
这里是喜欢睡觉的室友终于早起去建模了的as，虽然就算他们不去今天我也要在早上把lab做完的，不管怎样，比他们晚起好多了  
下午还要打网络赛...这一周一个字的oj都没碰（不过位运算比起之前要好多了  
现在再看位运算，我有种所有的控制语句都可以只用位运算来实现的感觉，虽然自己不会证明，但是我想应该不会是错的  
  
说句实话，自己一直都有种看不起自己的同学的感觉，每次看到他们一早就学完了做完了什么东西的时候就感觉到自己和他们的差距  
但是当我自己埋头干完去看他们做出来的东西的时候，“哇，这是什么垃圾，你好意思么”，诸如这样的想法就冒出来了  
（虽然我自己写的也是垃圾，但是还是在可以好意思范围的垃圾！  
  
不过不管怎样，做完的比做不完的强，我就是做的慢的人  
但是我相信做精的最后一定比做得快的强，慢慢做脚踏实体地前进最后一定会比急躁的家伙强的多的  
  
# dlc检查结果
```
dlc:bits.c:147:bitXor: 8 operators  
dlc:bits.c:158:tmin: 1 operators  
dlc:bits.c:169:isTmax: 9 operators  
dlc:bits.c:181:allOddBits: 9 operators  
dlc:bits.c:191:negate: 2 operators  
dlc:bits.c:204:isAsciiDigit: 8 operators  
dlc:bits.c:214:conditional: 10 operators  
dlc:bits.c:226:isLessOrEqual: 16 operators  
dlc:bits.c:238:logicalNeg: 7 operators  
dlc:bits.c:271:howManyBits: 31 operators  
dlc:bits.c:299:floatScale2: 15 operators  
dlc:bits.c:328:floatFloat2Int: 19 operators  
dlc:bits.c:351:floatPower2: 10 operators  
```
   
# btest 结果
```
Score	Rating	Errors	Function  
 1	1	0	bitXor  
 1	1	0	tmin  
 1	1	0	isTmax  
 2	2	0	allOddBits  
 2	2	0	negate  
 3	3	0	isAsciiDigit  
 3	3	0	conditional  
 3	3	0	isLessOrEqual  
 4	4	0	logicalNeg  
 4	4	0	howManyBits  
 4	4	0	floatScale2  
 4	4	0	floatFloat2Int  
 4	4	0	floatPower2  
Total points: 36/36  
```

# driver.pl 结果
```
Correctness Results	Perf Results  
Points	Rating	Errors	Points	Ops	Puzzle  
1	1	0	2	8	bitXor  
1	1	0	2	1	tmin  
1	1	0	2	9	isTmax  
2	2	0	2	9	allOddBits  
2	2	0	2	2	negate  
3	3	0	2	8	isAsciiDigit  
3	3	0	2	10	conditional  
3	3	0	2	16	isLessOrEqual  
4	4	0	2	7	logicalNeg  
4	4	0	2	31	howManyBits  
4	4	0	2	15	floatScale2  
4	4	0	2	19	floatFloat2Int  
4	4	0	2	10	floatPower2  
  
Score = 62/62 [36/36 Corr + 26/26 Perf] (145 total operators)  
```

