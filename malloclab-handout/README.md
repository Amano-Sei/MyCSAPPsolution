# malloc lab

呀，真是一波三折啊hhh...终于算是完成了，虽然某两个数据利用率很低。

(居然写了半个多月...不愧是我...

因为现在博客已经好好在运行了，所以这边就多说点正事吧。

起初的时候尝试了推迟合并，当时写的很烂，虽然最后调通了，但是利用率极低，可以断言自己无论任何时候都推迟合并肯定是不合适的。

然后在实现realloc时，感觉立即和并的话会比较好写，所以直接推翻了推迟合并的想法。

关于空闲链表，是普通的分离适配，每个size class的链表内部从小到大存，并且同大小低地址在前。

realloc的策略是能不挪动就不挪动，哪怕可以减少一点堆大小，最少这两个测试数据来说加上一点小trick会有很不错的利用率。

实现过程中遇到的困难，呀，说苦难也不为过（

开始的时候基本上是随便一个可能有坑的地方都能被我踩了，所以最后一遍实现的时候没怎么debug就通了还是很开心的，但是相应的也没有仔细检查所有的内容，所以可能会有错，欢迎指出。

CHUNKSIZE设的很小是故意的，这样会使得realloc和4号文件的利用率大幅提高，即使不加trick也只有非常小的差距。

最后是分数，如果再加上一点小作弊，两个realloc利用率会来到100和99，这样的分数会高一分是94分，但是已经没什么意义了hhh

```
Results for mm malloc:
trace  valid  util     ops      secs  Kops
 0       yes   99%    5694  0.000145 39215
 1       yes  100%    5848  0.000137 42780
 2       yes   99%    6648  0.000188 35456
 3       yes  100%    5380  0.000125 43040
 4       yes   99%   14400  0.000164 87966
 5       yes   95%    4800  0.000791  6067
 6       yes   94%    4800  0.000706  6803
 7       yes   55%   12000  0.033775   355
 8       yes   51%   24000  0.040190   597
 9       yes  100%   14401  0.000147 98166
10       yes   87%   14401  0.000124116419
Total          89%  112372  0.076490  1469

Perf index = 53 (util) + 40 (thru) = 93/100
```

7号和8号数据的模式我一时也想不出很好的既可以让他们有很好的利用率又对其他数据影响比较小的方法，所以就这么放着吧，猜想实现的比较好的简单分离存储会有比较不错的表现，但是我不知道该怎么组织会比较好（其实主要是懒...

另外猜测小块推迟合并可以同样达成我的小作弊对realloc的效果，但是不知道该怎么写（其实还是因为懒...主要自己写的代码有很多地方都是建立在不存在连续的空闲块的基础之上在写的，虽然改应该也很快就改完了（但是这个lab我是真不想再看了...
