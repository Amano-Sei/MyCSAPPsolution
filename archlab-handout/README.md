# archlab
emmm怎么说呢...这次的lab可以说是目前我做过的lab中最难的了  
（虽然在运行benchmark.pl之前我的想法完全是反过来的）  
可以说的点还是蛮多的，当然不是说partA和partB  
这两个依然是最简单的，内心评价不变，毕竟是做过一遍的东西  
  
先来讲一下自己的心路历程  
这个东西估计实现iaddq就差不多了 => 好简单，跑下benchmark吧，诶我怎么零分??? => emmm循环展开，好像有印象在以前的gcc出来的汇编里见过类似的东西 => 哇，我有分了，虽然不到一半 => 哇，我怎么把load/use hazard忘了...40多分了! => 哇，dalao的做法好妙 => 难道不删xorq %rax, %rax 就不能满分了么 => 还是去修改hcl吧 => 终于...
差不多就这样吧，自己写完展开之后发现分数没有一半就去搜dalao的做法，然后在大量的尝试和修改之后，终于达到了59.8分...随后在各种意义不大的尝试之后，最终还是去修改hcl了，然后成功60...  
emmm个人来说拒绝删掉xorq %rax, %rax的语句的做法，实际运行时rax的值是任意的，初始化是必须的  
  
## 下面开始讲自己注意到的优化点:  
  
### 首先是不动hcl的情况下:  
1.第一次计算长度是否大于等于9时，条件跳转到余数判断部分，这样会使得0~8的周期数变少，在更长长度的时钟数已经比较短的情况下，短长度的时钟数的缩小对于结果的优化效果显然更高  
2.树内跳转基本上遵循着单叶的情况下小余数优先级大于大余数，多叶的情况下不定，但是整体还是小余数优先级大于大余数，但是当大余数子树和小余数子树的叶个数差比较大时有可能反过来  
3.余数内使用比自己高一位的余数的条件跳转避免use/load hazard，这使得我们必须在条件码满足le的情况下进入剩余处理阶段，当然这也使得余数8不能回避use/load hazard的气泡  
4.借助上一条，每次进入余数我们会有一条必然执行的条件跳转，借助这一点，我们可以预执行本应该rmmovq语句把进入剩余处理阶段的跳转点设为那次必然执行的条件跳转的目的地，同时可以去掉必须在条件码满足le的情况下进入剩余处理阶段的限制，这是9位的充裕空间才能做到的事情，借助这一点，我也让分数达到了59.8  
  
### 修改hcl的情况下：  
因为mrmovq直到memory阶段才会使用valA的值，所以修改hcl避免那个use/load hazard(这也是在homework中做过的事情)，在充分利用树跳转的情况下，很轻易就把我们的代码修改为7.48版本  
  
差不多就这么多了，做完的时候说实话成就感有限，更多的是解脱感...终于做完了第四章相关，可以继续推csapp进度了QAQ  
  
## benchmark.pl结果
    ncopy  
0	20  
1	22	22.00  
2	31	15.50  
3	38	12.67  
4	43	10.75  
5	50	10.00  
6	58	9.67  
7	61	8.71  
8	70	8.75  
9	76	8.44  
10	81	8.10  
11	87	7.91  
12	97	8.08  
13	99	7.62  
14	109	7.79  
15	114	7.60  
16	120	7.50  
17	126	7.41  
18	131	7.28  
19	133	7.00  
20	142	7.10  
21	149	7.10  
22	154	7.00  
23	161	7.00  
24	169	7.04  
25	172	6.88  
26	181	6.96  
27	183	6.78  
28	188	6.71  
29	194	6.69  
30	204	6.80  
31	206	6.65  
32	216	6.75  
33	221	6.70  
34	227	6.68  
35	233	6.66  
36	238	6.61  
37	240	6.49  
38	249	6.55  
39	256	6.56  
40	261	6.53  
41	268	6.54  
42	276	6.57  
43	279	6.49  
44	288	6.55  
45	290	6.44  
46	295	6.41  
47	301	6.40  
48	311	6.48  
49	313	6.39  
50	323	6.46  
51	328	6.43  
52	334	6.42  
53	340	6.42  
54	345	6.39  
55	347	6.31  
56	356	6.36  
57	363	6.37  
58	368	6.34  
59	375	6.36  
60	383	6.38  
61	386	6.33  
62	395	6.37  
63	397	6.30  
64	402	6.28  
Average CPE	7.48  
Score	60.0/60.0  
  
补了下benchmark.pl的输出结果，需要注意这个是实现了iaddq和避免访存阶段才需要valA值的加载/使用冒险的pipe版本的运行结果  
只实现了iaddq的pipe的话可以看同目录下的ncopy598.ys版本，虽然不是满分（  
  
