# Performance Lab
2019-10-24 夜 突然三天连续沉默不是因为零进度，是因为这几天都没怎么在宿舍待，也是拜第六章不怎么需要电脑和没怎么在宿舍待，这章进度应该是最近最好的一次了，所以performance lab会留待c6和cache lab写完再做（虽然感觉之前不是不能做，但是现在来看如果当时我二话不说直接做说不好会自闭（  

emmm貌似这个lab要在什么Pentium III Xeon Fish上跑（但是我并没有这样机子，所以随便做做好了

rotate这个（之前被cache lab搞自闭了，但是这里我们没有详细的参数，不能像在cache lab中那样进行分析然后优化，而且当时只关注miss数，而不是运行的CPE。

但是我的机子上什么都不做naive_transpose就有很好的分数，所以我们以自己机子上跑出的cpe为参照

简单地选了几组2的k次方分块，发现在16x16分块时有综合最好的cpe。正如webaside中所说，在较少的数据规模时，分块会比不分要稍差一点一些，但是随着数据规模的提升，分块的表现会明显优于不分，这是分块提升了代码的空间局部性导致的。而且分块并不是越大越好的，当分块出现conflict miss时，缓存的命中率会大幅下降，所以首先直接映射并不是一个很好的方式，正如我们在cache lab中看到的那样QAQ，其次如果分块比缓存大小还大时，效果就会下降，这种情况下缓存会经历capacity miss，但是因为没有实际体验过，所以这里我一直不是非常明白。

我们可以看到最后相较于naive版本平均优化了2倍左右（

至于smooth这里，emmm为了性能分开写了，但是感觉到了各种不方便，结构体不能随意初始化，赋值起来超麻烦。嘛，主要思想是避免重复计算，因为即使只保存前面计算出来的每列值，每次计算下一个平均值时，只需要求和新的一列中的最多三个数即可，这样平均每个元素进行了4个加，比起avg的平均9个少了一半，如果求前缀和的话，事实上每个元素是1个加2个减，在加上求前缀和的一个加，所以和我们的做法差别有限。关于这里要不要分块，这里访问的时候最多同时访问三行，每行一个一个地访问，拥有很好的空间局部性，所以我觉得没有必要分块，或者说分块或许反而会降低空间局部性。

（其实应该还可以循环展开优化，但是太麻烦了不想写了，不过如果展开两行的话，求nxt列时可以先求中间两个数，再分别加上下，这样可以使得平均再少半个加，更多行的话需要更多的变量，因为本身变量已经很多了，这也是不愿意进一步展开的原因之一（其实主要还是懒）

最后我们可以看到较于naive版本提升了接近4倍

最后是没有什么意义的driver运行结果：

    Teamname: THE ALOGORITHM@STER
    Member 1: Amano Sei
    Email 1: Amano_Sei@outlook.com

    Rotate: Version = naive_rotate: Naive baseline implementation:
    Dim		64	128	256	512	1024	Mean
    Your CPEs	2.0	3.1	5.9	10.4	10.6
    Baseline CPEs	14.7	40.1	46.4	65.9	94.5
    Speedup		7.3	13.1	7.8	6.3	8.9	8.4

    Rotate: Version = rotate: Current working version:
    Dim		64	128	256	512	1024	Mean
    Your CPEs	2.4	2.6	2.8	3.1	4.7
    Baseline CPEs	14.7	40.1	46.4	65.9	94.5
    Speedup		6.1	15.7	16.4	21.2	20.0	14.6

    Smooth: Version = smooth: Current working version:
    Dim		32	64	128	256	512	Mean
    Your CPEs	11.6	11.4	11.4	11.4	11.3
    Baseline CPEs	695.0	698.0	702.0	717.0	722.0
    Speedup		60.1	61.1	61.3	63.1	63.9	61.9

    Smooth: Version = naive_smooth: Naive baseline implementation:
    Dim		32	64	128	256	512	Mean
    Your CPEs	43.6	43.6	43.6	43.0	44.0
    Baseline CPEs	695.0	698.0	702.0	717.0	722.0
    Speedup		16.0	16.0	16.1	16.7	16.4	16.2

    Summary of Your Best Scores:
      Rotate: 14.6 (rotate: Current working version)
      Smooth: 61.9 (smooth: Current working version)

