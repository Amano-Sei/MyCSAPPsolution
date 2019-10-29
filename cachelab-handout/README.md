# Cache Lab
2019-10-27 夜 partA可以说一帆风顺，partB如做c6的时候所料进入自闭（不过还是有一半分的（哭）满分是接近极限的1/8的不命中率的，所以有点茫然，看了write up提示说看网络旁注，好吧接下来会先把网络旁注看了，另外partA提示中的getopt也很让人在意，man有300多行晚点看了在更新下partA部分

终于结束了...partB真的写自闭了（一开始我没好好看writeup，准备写一个能同时拿到三种情况满分的方法...结果在我的64x64满分版本上怎么优化，32x32都跨不过300这条线...还就多了3个QAQ。

64x64一开始没想到这样挪，是从dalao那里学来的，重新看writeup之后其实提示挺明显的，"however, do whatever you want with the contents of array B."（一开始只看了前半句我还曲解成了不能随便修改B...)，dalao已经讲过的就不重复了，说下我这么长时间来关于64x64中第二部分优化的结论

取A中左下角到B右上角部分那里，仅就A来说有两种取法，横着取和竖着取4个，同时B的右上角那里必然与这个方向相反，至于从B的右上角存到B的左下角可以随意，只需要调整存到B右上角时候的顺序即可。但是因为这里4行一循环，所以要尽量减少竖着取的情况，所以目前我认为的比较可行的方案只有两个，简称横竖横，
竖横横，分别对应A左下，B右上，B左下。但是分析一下我们会发现竖横横比起另一个有一个大优势就是他会给A的右下留下前三行的缓存（曾经我考虑过在前面做点小动作地把第四行第四个给提前取出来，但是当时的我在考虑普适性...所以被理念否决了，其实如果可以再多一个变量的话应该就可以做到跨过300线了），最少就64x64的表现来说，竖横横的话是比横竖横要好的，我的写法的话在32x32下两者有一样的300整，在加上3个额外miss，跨不过去300呢（

发觉网上别人的答案都是判断了长度之后，重读了writeup的我发现里面有这么一句（ 
    "Your code only needs to be correct for these three cases and you can optimize it specifically for these three cases. In particular, it is perfectly OK for your function to explicitly check for the input sizes and implement separate code optimized for each case."
（（（不好好读题是自找的呢

随后迅速地随便选了一对数字进行分块完成了61x67，啊说道分块，网络旁注看了之后感觉自己绝望了，我知道这个啊，但是为什么block能带来这些优化我不知道啊QAQ

本来是想穷举下所有的分块的，但是编译出来的test-trans注册的函数一多要么出bug要么段错误（emmm等理解test-trans.c的话或许还可以试一试，但是我有点累了（

getopt文档看的一知半解的感觉，网上找了不少博客看，但是总觉得看的有点懵逼，大概还需要把posix什么的补一下...

差不多就这么多了吧（这次的体验一点也不比archlab好到哪里去呢（顺便貌似后面没有新的网络旁注了所以接下来会随着新章的推进把前面的网络旁注补下吧。

文件夹下有一个表格感觉对我推算miss和hit产生了很大的帮助（被一次次的展开分析和展开循环搞快自闭了

emmm虽然想说想缓口气什么的（不过大概接下来还是会写performance lab

顺便./driver.py运行结果如下：

    Part A: Testing cache simulator
    Running ./test-csim
                            Your simulator     Reference simulator
    Points (s,E,b)    Hits  Misses  Evicts    Hits  Misses  Evicts
         3 (1,1,1)       9       8       6       9       8       6  traces/yi2.trace
         3 (4,2,4)       4       5       2       4       5       2  traces/yi.trace
         3 (2,1,4)       2       3       1       2       3       1  traces/dave.trace
         3 (2,1,3)     167      71      67     167      71      67  traces/trans.trace
         3 (2,2,3)     201      37      29     201      37      29  traces/trans.trace
         3 (2,4,3)     212      26      10     212      26      10  traces/trans.trace
         3 (5,1,5)     231       7       0     231       7       0  traces/trans.trace
         6 (5,1,5)  265189   21775   21743  265189   21775   21743  traces/long.trace
        27


    Part B: Testing transpose function
    Running ./test-trans -M 32 -N 32
    Running ./test-trans -M 64 -N 64
    Running ./test-trans -M 61 -N 67

    Cache Lab summary:
                            Points   Max pts      Misses
    Csim correctness          27.0        27
    Trans perf 32x32           8.0         8         259
    Trans perf 64x64           8.0         8        1147
    Trans perf 61x67          10.0        10        1906
              Total points    53.0        53

